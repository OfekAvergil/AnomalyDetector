
#include "HybridAnomalyDetector.h"
#include "minCircle.h"

// Auto-generated constructor stub
HybridAnomalyDetector::HybridAnomalyDetector() {
}

//  Auto-generated destructor stub
 HybridAnomalyDetector:: ~HybridAnomalyDetector() {
}

/**
 * get the training data and arrange it's correlated features.
 * @param ts - TimeSeries object with the data
 */
void HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int i;
    size_t size=0;
    this->SimpleAnomalyDetector::fillCf(ts);
    for(correlatedFeatures& couple : cf) {
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = data1.size();
        //create a point array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        if(couple.corrlation >= 0.9) {
            fillLinearCorr(&couple,array,data1.size());
        } else{
            fillCircCorr(&couple,array,size);
        }
    }
}


/**
 * fills the circ_Reg feild of the linear correlated features
 * @param couple - correlatedfeature object
 * @param array  - array of pointer to points
 * @param size   - the size of the array;
 */
void HybridAnomalyDetector:: fillCircCorr(correlatedFeatures* couple, Point** array, size_t size) {
    float temp = 0 , maxDev = 0;
    int i;
    couple->circ_reg = findMinCircle(array,size);
}


/**
 * gets the tested data and check each correlated features if there anomaly in their data
 * @param ts - the data
 * @return vector with all the reports of anomaly
 */
vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {
    int i,time, size = 0;
    float dist = 0, maxDist =0;
    vector<AnomalyReport> report;
    for(correlatedFeatures& couple : cf) {
        time = 1;
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = (int)data1.size();
        //create points array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        for(Point* p :array) {
            if(couple.corrlation >= 0.9 ) {
                if( detectLinearCorr(couple,p)) {
                    string desc = (couple.feature1 + "-" + couple.feature2);
                    //long timeStamp = (long) ts.returnTime(i);
                    AnomalyReport* r = new AnomalyReport(desc ,time);
                    report.push_back(*r);
                }
            }else {
                if(detectCircularCorr(couple,p)) {
                    string desc = (couple.feature1 + "-" + couple.feature2);
                    //long timeStamp = (long) ts.returnTime(i);
                    AnomalyReport* r = new AnomalyReport(desc ,time);
                    report.push_back(*r);
                }
            }
            time++;
        }
    }
    return report;
}

/**
 * check if there is anomaly in point p of a circular correlated couple
 * @param couple - correlatedfeatures object
 * @param p      - the checked point
 * @return True is there is an anomaly, false otherwise.
 */
bool HybridAnomalyDetector:: detectCircularCorr(correlatedFeatures couple, Point *p ) {
    Circle bigger = couple.circ_reg;
    bigger.radius = bigger.radius * 1.1;
    return (!isInside(bigger,*p));
}