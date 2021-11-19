//
// Created by Hod Amar on 17/11/2021.
//

#include "timeseries.h"

const vector<string> TimeSeries::getFeaturesNames() const {
    return features;
}

float TimeSeries::returnTime(int i) {

    smatch m1;
    regex r("[A-Za-z]*[Tt][Ii][Mm][Ee].*");
    float temp;
    int flag = 0;

    /// searching for "TIME" in features vector
    for (std:: string element : features){
        std:: regex_match(element,m1,r);
        if (!m1.empty()){
            flag = 1;
             temp = data[element][i];
             break;
        }
    }

    if (flag) {
        return temp;
    }

    /// if doesnt exist - def.
    return 1.0;
}


vector<float> TimeSeries::getData(string s) const{
    /// we assome that the string is valid
    std::vector<float> v;
    v = data.find(s)-> second;
    return v;
}

map<string, vector<float>> TimeSeries::getMap() const {
    return this->data;
}

vector<float> TimeSeries::getData(string feature) const {
    return vector<float>();
}

