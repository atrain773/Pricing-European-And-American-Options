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



DataRecord parseCSVLine(const std::string &line) {
    stringstream ss(line);
    string item;
    DataRecord record;

    getline(ss, item, ','); record.QUOTE_UNIXTIME = stol(item);
    getline(ss, item, ','); record.QUOTE_READTIME = item;
    getline(ss, item, ','); record.QUOTE_DATE = item;
    getline(ss, item, ','); record.QUOTE_TIME_HOURS = stoi(item);
    getline(ss, item, ','); record.UNDERLYING_LAST = stod(item);
    getline(ss, item, ','); record.EXPIRE_DATE = item;
    getline(ss, item, ','); record.EXPIRE_UNIX = stol(item);
    getline(ss, item, ','); record.DTE = stoi(item);
    getline(ss, item, ','); record.C_DELTA = stod(item);
    getline(ss, item, ','); record.C_GAMMA = stod(item);
    getline(ss, item, ','); record.C_VEGA = stod(item);
    getline(ss, item, ','); record.C_THETA = stod(item);
    getline(ss, item, ','); record.C_RHO = stod(item);
    getline(ss, item, ','); record.C_VOLUME = ((item.empty() || item == " ") ? 0 : stoi(item));
    getline(ss, item, ','); record.C_LAST = stoi(item);
    getline(ss, item, ','); record.C_SIZE = item;
    getline(ss, item, ','); record.C_BID = stod(item);
    getline(ss, item, ','); record.C_ASK = stod(item);
    getline(ss, item, ','); record.STRIKE = stoi(item);
    getline(ss, item, ','); record.P_BID = stod(item);
    getline(ss, item, ','); record.P_ASK = stod(item);
    getline(ss, item, ','); record.P_SIZE = item;
    getline(ss, item, ','); record.P_LAST = stod(item);
    getline(ss, item, ','); record.P_DELTA = stod(item);
    getline(ss, item, ','); record.P_GAMMA = stod(item);
    getline(ss, item, ','); record.P_VEGA = stod(item);
    getline(ss, item, ','); record.P_THETA = stod(item);
    getline(ss, item, ','); record.P_RHO = stod(item);
    getline(ss, item, ','); record.P_VOLUME = ((item.empty() || item == " ") ? 0 : stoi(item));
    getline(ss, item, ','); record.STRIKE_DISTANCE = stod(item);
    getline(ss, item, ','); record.STRIKE_DISTANCE_PCT = stod(item);

    return record;
}

int main() {
    std::ifstream file("data/cleaned/ProjectOptionData.csv");
    std::string line;
    std::vector<DataRecord> records;

    // Skip header line
    std::getline(file, line);

    // Read and parse each line
    while (std::getline(file, line)) {
        records.push_back(parseCSVLine(line));
    }

  return 0;
}