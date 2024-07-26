#include "../include/data_record.h"

using namespace std;

int main() {


    // Testing Part 1 Implement CRR Binomial Model (Jiaqi)


    // Testing Part 2 Implement Black-Scholes Merton Formula (Anton)




 
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