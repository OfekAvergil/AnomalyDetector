

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    void fillCf(const TimeSeries& ts);

public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    AnomalyReport detectCircular(correlatedFeatures couple,Point p,int time);
    bool detectCircularCorr(correlatedFeatures couple, Point *p );
    void fillCircCorr(correlatedFeatures* couple, Point** array, size_t size);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
