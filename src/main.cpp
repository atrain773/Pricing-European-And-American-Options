#include "../include/data_record.h"

using namespace std;

int main() {
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