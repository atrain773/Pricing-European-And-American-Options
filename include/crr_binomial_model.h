#pragma once

#include <iostream>
#include <math.h>

#include <vector>
#include <fstream>
#include <chrono>
using namespace std::chrono;

//#include "../matplotlib-cpp/matplotlibcpp.h"

// To Implement (Jiaqi)

double binomialOptionPrice(char option, double K, double T, double S0, double sigma, double r, double q, int N, char exercise);
int checkAccuracy(char option, double K, double T, double S0, double sigma, double r, double q);
double findCriticalStockPrice(char Option, double K, double T, double sigma, double r, double q, char Exercise);
std::vector<std::vector<double> > question_2();
void question_3_4(double q, char option);