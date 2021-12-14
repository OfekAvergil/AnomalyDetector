//
// Hod Amar and Ofek Avergil
//

#ifndef ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
#define ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H

#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"


struct correlatedFeatures{
    correlatedFeatures() : circ_reg(Point(0,0),0){};
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle circ_reg;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{

protected:
    void fillCf(const TimeSeries& ts);

    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    void fillLinearCorr(correlatedFeatures* couple, Point **array, int size);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

    bool detectLinearCorr(correlatedFeatures couple, Point *p);
};

#endif //ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
