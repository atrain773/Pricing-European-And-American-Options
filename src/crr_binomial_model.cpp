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

//check the aurrency
int checkAccuracy(char option, double K, double T, double S0, double sigma, double r, double q) {
    char exercise = 'A';//In question 3 and 4, we only need to predict American option price.
    double tolerance = 1e-3;
    double prev_price = 0.0;
    double price = 0.0;

    int N = 100;//let N starts with 100

    while(true){
        price = binomialOptionPrice(option, K, T, S0, sigma, r, q, N, exercise);

        //once the error between price and previous price is less than tolerance, break;
        if(fabs(price - prev_price) < tolerance){
            return N;
        }

        N *= 2;
        prev_price = price;
    }

    //Finding failure
    return -1;
}

//find critical stock price
double findCriticalStockPrice(char Option, double K, double T, double sigma, double r, double q, char Exercise) {
    double S0 = 90;
    double epsilon = 0.005;
    double intrinsicValue, optionPrice;

    while (true) {
        if(Option == 'P') S0 += 5;// Increment stock price by small interval
        if(Option == 'C') S0 -= 5;// decrement stock price by small interval
        int N = checkAccuracy(Option,100, T, S0, 0.2, 0.05, q);
        optionPrice = binomialOptionPrice(Option, K, T, S0, sigma, r, q, N, Exercise);
        if (Option == 'P') {
            intrinsicValue = max(K - S0,0.0);
        } else if (Option == 'C') {
            intrinsicValue = max(S0 - K,0.0);
        }
        //cout << S0 << " | option price " << optionPrice << " | intrinsicValue:" << intrinsicValue << "| differnce: " << fabs(optionPrice - intrinsicValue) << endl;
        if (fabs(optionPrice - intrinsicValue) < epsilon) {
            return S0;
        }
    }

    if(S0 > 300) return -1;
    if(S0 < 0) return -1;
}


//result outputer
//question 2
std::vector<std::vector<double> > question_2(){
    
    //row 0 - # of time steps - (i*10)
    //row 1 - option price with time step (i*10)
    //row 2 - computational time - (unit: seconds)
    std::vector<std::vector<double> > arr(3, std::vector<double>(101));

    for(int i = 0; i <= 100; i++){
        auto start = high_resolution_clock::now();
        double price = binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 10*i, 'E');
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);//computational time
        arr[0][i] = i*10;//N - # of time steps
        arr[1][i] = price;//option price with i*100 steps
        arr[2][i] = duration.count()*1e-6;//seconds
        cout << i << "| N: " << arr[0][i] << "| price: " << arr[1][i] << "| time: " << arr[2][i]<< endl;
    }

    return arr;
}

void question_34(double q, char option){
    double T = 1;

    for (int i = 1; i <= 12; ++i) {
        T = i / 12.0;
        // double Price = binomialOptionPrice(option, 100, T, 100, 0.2, 0.05, q, 3000, 'A');
        // double aPrice = binomialOptionPrice(option, 100, T, 100, 0.2, 0.05, q, checkAccuracy(option,100, T, 100, 0.2, 0.05, 0), 'A');
        // cout << "Time to maturity: " << T << " years, Put price with 3000 steps(q = " << q << "): " << Price  << " | ";
        // cout << "N = " << checkAccuracy(option,100, T, 100, 0.2, 0.05, q) << " Put price with N steps(q = " << q << "): " << aPrice  << " | difference: " << abs(Price-aPrice) << endl;

        double criticalPrice = findCriticalStockPrice(option, 100, T, 0.2, 0.05, q,'A');
        std::cout << "Time to maturity: " << T << " years, Critical stock price(q = " << q << "): " << criticalPrice << std::endl;
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