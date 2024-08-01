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

//CRR Binomial Model
double binomialOptionPrice(char option, double K, double T, double S0, double sigma, double r, double q, int N, char exercise) {
    
    //Error detect
    if(exercise != 'A' && exercise != 'E'){
        //Neither American options or European options, return error message 0
        throw std::invalid_argument("Error 0: The option type is neither European or American");
    }
    if(option != 'C' && option != 'P'){
        //Neither call options or put options, return error message 1
        throw std::invalid_argument("Error 1: The option type is neither European or American");
    }

    if(N < 0){
        //at lease 1 step, return error 2
        throw std::invalid_argument("Error 2: N < 0");
    }

    double dt = T / N;
    double u = exp(sigma * sqrt(dt));
    double d = 1 / u;
    double p = (exp((r - q) * dt) - d) / (u - d);

    vector<double> assetPrices(N + 1);
    vector<double> optionPrices(N + 1);

    // Initialize asset prices at maturity
    for (int i = 0; i <= N; ++i) {
        assetPrices[i] = S0 * pow(u, N - i) * pow(d, i);
    }

    // Compute option values at maturity
    for (int i = 0; i <= N; ++i) {
        if (option == 'C') {
            optionPrices[i] = max(0.0, assetPrices[i] - K);
        } else if (option == 'P') {
            optionPrices[i] = max(0.0, K - assetPrices[i]);
        }
    }

    // Backward induction for option pricing
    for (int j = N - 1; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            assetPrices[i] = S0 * pow(u, j - i) * pow(d, i);
            optionPrices[i] = exp(-r * dt) * (p * optionPrices[i] + (1 - p) * optionPrices[i + 1]);

            if (exercise == 'A') {
                if (option == 'C') {
                    optionPrices[i] = max(optionPrices[i], assetPrices[i] - K);
                } else if (option == 'P') {
                    optionPrices[i] = max(optionPrices[i], K - assetPrices[i]);
                }
            }
        }
    }

    return optionPrices[0];
}

//result outputer
//{0 - 1500}
std::vector<std::vector<double> > question_2(){
    
    //row 0 - # of time steps - (i*100)
    //row 1 - option price with time step (i*100)
    //row 2 - computational time - (unit: seconds)
    std::vector<std::vector<double> > arr(3, std::vector<double>(31));

    ofstream outputFile("../plot/convergence.csv");  // Open file for writing

     if (!outputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return arr;
    }

    for(int i = 1; i <= 300; i++){
        //auto start = high_resolution_clock::now();
        double price = binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 10*i, 'E');
        //auto end = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds>(end - start);//computational time
        arr[0][i] = i*10;//N - # of time steps
        arr[1][i] = price;//option price with i*100 steps
        //arr[2][i] = duration.count()*1e-6;//seconds
        outputFile << i*10 << "," << price << "," << endl;
    }

    return arr;
}

void qestion_3(){
    double T;
    for (int i = 1; i <= 12; ++i) {
        T = i / 12.0;
        double putPrice = binomialOptionPrice('P', 100, T, 100, 0.2, 0.05, 0, 1000, 'A');
        std::cout << "Time to maturity: " << T << " years, Put price: " << putPrice << std::endl;

        double criticalPrice = binomialOptionPrice('P', 100, T, 100, 0.2, 0.05, 0.04, 1000, 'A');
        std::cout << "Time to maturity: " << T << " years, Critical stock price: " << criticalPrice << std::endl;
    }
}

//for testing
// int main(){

//     //question 2
//     question_2();

//     // cout << "European_Call: " << binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 1500, 'E') << endl;
//     // cout << "European_Put: " << binomialOptionPrice('P', 100, 1, 100, 0.2, 0.05, 0.04, 1500, 'E') << endl;
//     // cout << "American_Call: " << binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 1500, 'A') << endl;
//     // cout << "Ameican_Put: " << binomialOptionPrice('P', 100, 1, 100, 0.2, 0.05, 0.04, 1500, 'A') << endl;

//     //question 3
//     //qestion_3();

//     return 0;
// }