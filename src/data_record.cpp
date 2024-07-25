#include "../include/data_record.h"

using namespace std; 

DataRecord parseCSVLine(const string &line) {
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