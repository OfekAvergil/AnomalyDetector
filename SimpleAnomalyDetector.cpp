//
// Hod Amar and Ofek Avergil
//

#include "SimpleAnomalyDetector.h"
#include <vector>
#include <algorithm>
using namespace std;

const float MIN_THRESHOLD = 0.83;
//find correlative couples.
void SimpleAnomalyDetector::fillCf(const TimeSeries &ts) {
    int size = 0, i, j;
    float maxCorr = 0, temp = 0, *data1, *data2;
    string corrFeature, other, feature;
    vector<float> featureData, otherData;
    //get the names of the features
    vector<string> features = ts.getFeaturesNames();
    int featuresNum = (int)features.size();
    //for every feature in the list look for correlative feature.
    for(i=0; i<featuresNum; i++) {
        maxCorr = 0;
        feature = features.at(i);
        featureData = ts.getData(feature);
        data1 = &featureData[0];
        size = (int)featureData.size();
        //calculate with all the other features
        for (j = i + 1; j < featuresNum; j++) {
            other = features.at(j);
            otherData = ts.getData(other);
            data2 = &otherData[0];
            //find the correlation
            temp = pearson(data1 ,data2 ,size);
            //if correlation is bigger in absolute mark this feature as the correlated one.
            if(abs(temp) > abs(maxCorr)) {
                maxCorr = temp;
                corrFeature = other;
            }
        }
        //if we found correlative feature, create new correlatedFeatures
        if(maxCorr >= MIN_THRESHOLD) {
            correlatedFeatures couple;
            //fill data
            couple.feature1 = feature;
            couple.feature2 = corrFeature;
            couple.corrlation = maxCorr;
            //add to the correlative couples vector.
            cf.push_back(couple);
        }
    }
}

//auto-generated constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {}

//auto-generated destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int i, size=0;
    float temp = 0 , maxDev = 0;
    fillCf(ts);
    for(correlatedFeatures& couple : cf) {
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = (int)data1.size();
        //create a point array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        couple.lin_reg = linear_reg(array, size);
        for(Point* p :array) {
            temp = dev(*p, couple.lin_reg);
            if (abs(temp) > abs(maxDev)){
                maxDev = temp;
            }
        }
        couple.threshold = abs(maxDev);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    int i,time = 1, size = 0;
    float dist = 0, maxDist =0;
    vector<AnomalyReport> report;
    for(correlatedFeatures& couple : cf) {
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = (int)data1.size();
        //create points array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        maxDist = 1.1 * abs(couple.threshold);
        for(Point* p :array) {
            dist = dev(*p, couple.lin_reg);
            if (abs(dist) > maxDist){
                string desc = (couple.feature1 + "-" + couple.feature2);
                //long timeStamp = (long) ts.returnTime(i);
                AnomalyReport* r = new AnomalyReport(desc ,time);
                report.push_back(*r);
            }
            time++;
        }
    }
    return report;
}



vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return cf;
}


