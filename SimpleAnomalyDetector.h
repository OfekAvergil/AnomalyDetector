//
// Hod Amar and Ofek Avergil
//

#ifndef ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
#define ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H

#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"



struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
    void fillCf(const TimeSeries& ts);

    public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
};

#endif //ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
