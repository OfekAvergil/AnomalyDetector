//
// Created by Hod Amar on 17/11/2021.
//

#include "timeseries.h"

const vector<string> TimeSeries::getFeaturesNames() const {
    return features;
}

float TimeSeries::returnTime(int i) {
    /// searching for 'time' feature
    string ret = nullptr;
    char *regex = "[A-Za-z]*[Tt][Ii][Mm][Ee]";
    if (find(features.begin(), features.end(), "time") != features.end()) {
        return data["time"][i];
    } else if (find(features.begin(), features.end(), "Time") != features.end()) {
        return data["Time"][i];
    } else if (find(features.begin(), features.end(), "TIME") != features.end()) {
        return data["TIME"][i];
    } else {
        throw "time doesn't exist";
    }

}

vector<float> TimeSeries::getData(string feature) const {
    return vector<float>();
}

