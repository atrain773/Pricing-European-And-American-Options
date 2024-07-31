#include "../include/crr_binomial_model.h"

#include <stdexcept>
using namespace std;

// To Implement (Jiaqi)

//option = C - calls, option = P - puts
//K - strike
//T time to maturity
//S_0 - initial stock price
//v - volatility
//r - continuous compounding risk free interest rate
//q - continuous dividend yield
//N - the number of time steps
//exercise = A - American options, exercise = E - European options

//Constructor
CrrBinomial::CrrBinomial(char option, float K, float T, float S_0, float v, float r, float q, float N, char exercise){

    //Error detect
    if(exercise != 'A' && exercise != 'E'){
        //Neither American options or European options, return error message 0
        throw std::invalid_argument("Error 0: The option type is neither European or American");
    }
    if(option != 'C' && option != 'P'){
        //Neither call options or put options, return error message 1
        throw std::invalid_argument("Error 1: The option type is neither European or American");
    }

    //?
    if(N <= 0){
        //at lease 1 step, return error 2
        throw std::invalid_argument("Error 2: N <= 0");
    }

    //assign value to parameter
    c_p = option;
    A_E = exercise;
    Strike = K;
    step = N;
    delta = T/N;
    u = exp(v*sqrt(delta));
    d = 1/u;
    r_ = r;
    p = (exp((r-q)*delta)-d)/(u-d);
    p_ = 1-p;
    start = createNode(S_0,0,0);
}

//Function nCr - N choose R
// float CrrBinomial::nCr(int N, int R){
//     if(R>N) return 0;
//     if(R == 0 || R == N) return 1;
//     return nCr(N-1,R-1) + nCr(N-1,R);
// }

float CrrBinomial::nCr(int N, int R){
    if(R==0) return 1;
    return (N*nCr(N-1,R-1))/R;
}

//Function Max - return larger number
float CrrBinomial::max(float a, float b){
    if(a>b) return a;
    return b;
}

//Function buildTree - build the binomia tree
void CrrBinomial::buildTree(node* N){
    //command in next line - use to print all the node(for test only)
    //cout << "Node(" << N->t.n << ',' << N->t.j << ") - price: " << N->price << endl;
    if(N  == NULL){
        //Error 3: tree_build, head node is NULL
        throw std::invalid_argument("Error 3: tree_build, pre node is NULL");
    }

    //we need n steps, for node(n,j) if n == step we stop build the tree
    if(N->t.n < step){
        //go one step downward
        //float tempPrice = nCr(N->t.n+1,N->t.j)*pow(p,N->t.j)*pow(p_,N->t.n+1 - N->t.j)*max(d*N->price - Strike,0);
        struct node* step_downward = createNode(d*N->price,(N->t.n)+1,N->t.j);
        
        step_downward->pre_up = N;
        N->down = step_downward;
        if(step_downward->t.j != 0 ){
            step_downward->pre_down = N->pre_down->down;
            N->pre_down->down->up = step_downward;
        } 
        buildTree(step_downward);

        //when reach Node(n,n) go one step upward
        if(N->t.n == N->t.j){
            struct node* step_upward = createNode(u*N->price,(N->t.n)+1,N->t.j+1);

            step_upward->pre_down = N;
            N->up = step_upward;

            buildTree(step_upward);
        }
    }

    if(N->t.n == step){
        end = N;
    }
   
}

//Function freeTree - delete binomial tree after used
void CrrBinomial::freeTree(node* N){

    if(N->t.j == step) return;
    if(N->t.n == N->t.j) temp_ = N->up;
    if(N->down != NULL) freeTree(N->down);
    else freeTree(temp_);
    delete(N);

    // cout << test << " : Node(" << N->t.n << ',' << N->t.j << ")";
    // test++;
    // cout << " is Null: " << (N == NULL) << endl;
    
}

//Function American Option - return call or put price of American Option
void CrrBinomial::American(node* N){

    //call
    if(c_p =='C'){
        if(N->t.n == step) N->american = max(N->price-Strike,0);
        else {
            N->american = max(max(N->price-Strike,0),exp(-1*r_*delta)*(p*N->up->american+p_*N->down->american));
        }
    }
    //put
    else{
        if(N->t.n == step) N->american = max(Strike-N->price,0);
        else N->american = max(max(Strike-N->price,0),exp(-1*r_*delta)*(p*N->up->american+p_*N->down->american));
    }

    //print each node for testing only
    //cout << "Node(" << N->t.n << ',' << N->t.j << ") | american price: " << N->american <<endl;

    if(N->t.n == 0) return;

    if(N->t.j == N->t.n) temp = N->pre_down;
    if(N->pre_down != NULL) American(N->pre_down->down);
    else American(temp);
    
}

//Function European Option - return call or put price of European Option
void CrrBinomial::European(node* N){
    if(N == NULL) return;

    //star from node(N,N) with N steps upward
    //call
    if(c_p == 'C'){
        option_price += nCr(N->t.n,N->t.j)*pow(p,N->t.j)*pow(p_,N->t.n - N->t.j)*max(N->price - Strike,0);
    }
    else{
        option_price += nCr(N->t.n,N->t.j)*pow(p,N->t.j)*pow(p_,N->t.n - N->t.j)*max(Strike - N->price,0);
    }

    //print each node for testing only
    //cout << "Node(" << N->t.n << ',' << N->t.j << ") | price:" << nCr(N->t.n,N->t.j)*pow(p,N->t.j)*pow(p_,N->t.n - N->t.j)*max(N->price - Strike,0) << " | option price:" << option_price << endl;

    if(N->pre_down != NULL){
        European(N->pre_down->down);
    }
}

//Function GetPrice - return the price of option
float CrrBinomial::GetPrice(){

    // auto begin = high_resolution_clock::now();

    float result;

    buildTree(start);

    //detect American option or European option
    if(A_E == 'A'){
        //American Options
        American(end);
        result = start->american;
    }
    else{
        //European Options
        European(end);
        result = exp(-1*r_*(delta*step))*option_price;
    }

    freeTree(start);

    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - begin);
    //cout << "(used time(microseconds): " <<duration.count()<< ") ";
    return result;
}

//Function GetPlot - return the plot

//for testing
// int main(){
//     CrrBinomial test_e_put = CrrBinomial('P', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'E');
//     CrrBinomial test_e_call = CrrBinomial('C', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'E');
//     CrrBinomial test_a_put = CrrBinomial('P', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'A');
//     CrrBinomial test_a_call = CrrBinomial('C', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'A');
//     cout << "European put: " << test_e_put.GetPrice() << endl;
//     cout << "European call: " << test_e_call.GetPrice() << endl;
//     cout << "American put: " << test_a_put.GetPrice() << endl;
//     cout << "American call: " << test_a_call.