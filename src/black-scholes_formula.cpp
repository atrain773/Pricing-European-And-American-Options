
#include "../include/black-scholes_formula.h"

double blackScholes(char put_or_call, double S_0, double K, double r, double q, double sigma, double T) {
  
  double d_1 = d1(S_0, K, r, q, sigma, T); 
  double d_2 = d2(d_1, sigma, T);

  char c = (char)tolower(put_or_call);

  if (c == 'c') {
    return (S_0 * exp(-1 * q * T) * normalCDF(d_1)) - (K * exp(-1 * r * T) * normalCDF(d_2));
  }

  if (c == 'p') {
    return ((-1 * S_0 * exp(-1 * q * T) * normalCDF(-1 * d_1)) + (K * exp(-1 * r * T) * normalCDF(-1 * d_2) )); 
  }

  return -1.0; 
}

double d1(double S_0, double K, double r, double q, double sigma, double T) {
  return ((log(S_0/K)) + (r - q + .5 * sigma * sigma) * T) / (sigma * sqrt(T));
}

double d2(double d1, double sigma, double T) {
  return d1 - (sigma * sqrt(T)); 
}

double normalCDF(double value) {
   return 0.5 * erfc(-value * M_SQRT1_2);
}