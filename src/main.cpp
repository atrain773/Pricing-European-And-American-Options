#include "../include/data_record.h"
#include "../include/black-scholes_formula.h"
#include "../include/crr_binomial_model.h"

using namespace std;

int main() { 

    // Testing Part 1 Implement CRR Binomial Model (Jiaqi)
    CrrBinomial test_e_put = CrrBinomial('P', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'E');
    CrrBinomial test_e_call = CrrBinomial('C', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'E');
    CrrBinomial test_a_put = CrrBinomial('P', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'A');
    CrrBinomial test_a_call = CrrBinomial('C', 100, 1, 100, 0.2, 0.05, 0.04, 125, 'A');
    cout << "CRR Binomial Model" << endl;
    cout << "-------------------" << endl;
    cout << "European put: " << test_e_put.GetPrice() << endl;
    cout << "European call: " << test_e_call.GetPrice() << endl;
    cout << "American put: " << test_a_put.GetPrice() << endl;
    cout << "American call: " << test_a_call.GetPrice() << endl << endl;

    // Testing Part 2 Implement Black-Scholes Merton Formula (Anton)

    double T = 1;
    double K = 100;
    double S_0 = 100;
    double r = 0.05;
    double q = 0.04;
    double sigma = 0.2;

    double black_scholes_european_put = blackScholes('p', S_0, K, r, q, sigma, T);
    double black_scholes_european_call = blackScholes('c', S_0, K, r, q, sigma, T);

    cout << "Black Scholes (European)" << endl;
    cout << "-------------------" << endl; 
    cout << "Put Value: " << black_scholes_european_put << endl;
    cout << "Call Value: " << black_scholes_european_call << endl;
 
    // E.C
    // Testing Part 6 

    ifstream file("../data/cleaned/ProjectOptionData.csv");
    string line;
    vector<DataRecord> records;

    // Skip header line
    getline(file, line);

    // Read and parse each line
    while (getline(file, line)) {
        records.push_back(parseCSVLine(line));
    }


  return 0;
}