//
// Created by Hod Amar on 17/11/2021.
//

#ifndef ANOMALYDETECTOR_TIMESERIES_H
#define ANOMALYDETECTOR_TIMESERIES_H
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>


using namespace std;

class TimeSeries{
    map<string, vector<float>> data;
    vector<string> features;

public:
    TimeSeries(const char* CSVfileName) {
        string line, token;
        map<string, vector<float>> data;
        ifstream file;
        stringstream ss;

        /// open file and check it
        file.open(CSVfileName);
        if (!file.is_open()) {
            throw std::runtime_error("Couldn't open file\n");
        }

        /// getting features name
        if (file.good()) {
            getline(file, line);
            ss.str(line);
            while (getline(ss, line, ',')) {
                features.push_back(line);
            }
        }

        /// making map of lines
        while (getline(file, line)) {
            std::stringstream ss1(line);
            /// making the vector and initial keymap
            for (auto element : features) {
                getline(ss1, token, ',');
                data[element].push_back(stof(token));
            }
        }
        file.close();
    }



    const vector<string> getFeaturesNames() const;

    float returnTime(int i);

    vector<float> getData(string s) const;

    map<string, vector<float>> getMap() const;
};



#endif //ANOMALYDETECTOR_TIMESERIES_H
