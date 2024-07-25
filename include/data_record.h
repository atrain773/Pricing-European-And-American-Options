#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

struct DataRecord {
  long QUOTE_UNIXTIME;
  string QUOTE_READTIME;
  string QUOTE_DATE;
  int QUOTE_TIME_HOURS;
  double UNDERLYING_LAST;
  string EXPIRE_DATE;
  long EXPIRE_UNIX;
  int DTE;
  double C_DELTA;
  double C_GAMMA;
  double C_VEGA;
  double C_THETA;
  double C_RHO;
  int C_VOLUME;
  int C_LAST;
  string C_SIZE;
  double C_BID;
  double C_ASK;
  int STRIKE;
  double P_BID;
  double P_ASK;
  string P_SIZE;
  double P_LAST;
  double P_DELTA;
  double P_GAMMA;
  double P_VEGA;
  double P_THETA;
  double P_RHO;
  int P_VOLUME;
  double STRIKE_DISTANCE;
  double STRIKE_DISTANCE_PCT;
};

DataRecord parseCSVLine(const string &line);