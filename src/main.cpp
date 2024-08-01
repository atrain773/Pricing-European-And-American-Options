#include "../include/data_record.h"
#include "../include/black-scholes_formula.h"
#include "../include/crr_binomial_model.h"

using namespace std;

int main() { 

    // Testing Part 1 Implement CRR Binomial Model (Jiaqi)
    //question 2

    cout << "CRR Binomial Model" << endl;
    cout << "-------------------" << endl; 
    cout << "European_Call: " << binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 5000, 'E') << endl;
    cout << "European_Put: " << binomialOptionPrice('P', 100, 1, 100, 0.2, 0.05, 0.04, 5000, 'E') << endl;
    cout << "American_Call: " << binomialOptionPrice('C', 100, 1, 100, 0.2, 0.05, 0.04, 5000, 'A') << endl;
    cout << "Ameican_Put: " << binomialOptionPrice('P', 100, 1, 100, 0.2, 0.05, 0.04, 5000, 'A') << endl << endl;


    // Testing Part 2 Implement Black-Scholes Merton Formula (Anton)

    double T = 1;
    d