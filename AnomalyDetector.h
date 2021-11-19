//
// Created by Hod Amar on 16/11/2021.
//

#ifndef ANOMALYDETECTOR_ANOMALYDETECTOR_H
#define ANOMALYDETECTOR_ANOMALYDETECTOR_H

class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
#endif //ANOMALYDETECTOR_ANOMALYDETECTOR_H
