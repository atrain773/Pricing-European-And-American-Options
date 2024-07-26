#include "../include/data_record.h"
#include "../include/black-scholes_formula.h"

using namespace std;

int main() {


    // Testing Part 1 Implement CRR Binomial Model (Jiaqi)


    // Testing Part 2 Implement Black-Scholes Merton Formula (Anton)

    char c = 'c';
    double T = 1;
    double K = 100;
    double S_0 = 100;
    double r = 0.05;
    double q = 0.04;
    double sigma = 0.2;

    double black_scholes = blackScholes(c, S_0, K, r, q, sigma, T);

    cout << "Black Scholes Value: " << black_scholes << endl;
 
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