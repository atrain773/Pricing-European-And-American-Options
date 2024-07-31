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
    cout <