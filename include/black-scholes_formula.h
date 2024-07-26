#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std; 

/**
 * @brief Calculates the price of a European call or put option using the Black-Scholes formula.
 * 
 * @param put_or_call A character indicating the type of option. Use 'c' or 'C' for a call option and 'p' or 'P' for a put option.
 * @param S_0 The current price of the underlying asset (stock).
 * @param K The strike price of the option.
 * @param r The risk-free interest rate, assumed to be constant over the life of the option.
 * @param q The continuous dividend yield of the underlying asset.
 * @param sigma The volatility of the underlying asset's returns, expressed as a standard deviation.
 * @param T The time to maturity of the option, expressed in years.
 * @return The price of the European call or put option. If an invalid option type is provided (i.e., not 'c', 'C', 'p', or 'P'), the function returns -1.0.
 */
double blackScholes(char put_or_call, double S_0, double K, double r, double q, double sigma, double T); 

/**
 * @brief Calculates the d1 parameter used in the Black-Scholes formula.
 * 
 * @param S_0 The current price of the underlying asset (stock).
 * @param K The strike price of the option.
 * @param r The risk-free interest rate, assumed to be constant over the life of the option.
 * @param q The continuous dividend yield of the underlying asset.
 * @param sigma The volatility of the underlying asset's returns, expressed as a standard deviation.
 * @param T The time to maturity of the option, expressed in years.
 * @return The value of d1 used in the Black-Scholes formula.
 */
double d1(double S_0, double K, double r, double q, double sigma, double T); 

/**
 * @brief Calculates the d2 parameter used in the Black-Scholes formula.
 * 
 * @param d1 The d1 value calculated using the Black-Scholes formula.
 * @param sigma The volatility of the underlying asset's returns, expressed as a standard deviation.
 * @param T The time to maturity of the option, expressed in years.
 * @return The value of d2 used in the Black-Scholes formula.
 */
double d2(double d1, double sigma, double T); 

/**
 * @brief Calculates the cumulative distribution function (CDF) for the standard normal distribution.
 * 
 * @param value The value at which to evaluate the CDF.
 * @return The value of the CDF at the given value.
 */
double normalCDF(double value);