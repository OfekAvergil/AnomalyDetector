

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};
/**
 * the class hold all the data relevant to the Anomaly Detector
 */
class AnomalyDetectorData{
public:
    TimeSeries* learnData;
    TimeSeries* TestDate;
    SimpleAnomalyDetector* detector = new HybridAnomalyDetector();
    vector<AnomalyReport> reports;
    virtual ~AnomalyDetectorData(){};
};

class Command{
protected:
	DefaultIO* dio;
    AnomalyDetectorData* data;
    string description;
public:
	Command(DefaultIO* dio, AnomalyDetectorData* data):dio(dio), data(data){}
	virtual void execute()=0;
	virtual ~Command(){}
    virtual string getDes () {
        return this->description;
    };
};


class UploadCommand : public Command{
public:
    UploadCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "1. upload a time series csv file";
    };
    virtual void execute(){
        vector<string> train;
        vector<string> test;
        string line;
        FILE f;
        const char* trainName = "anomalyTrain.csv";
        const char* testName = "anomalyTest.csv";
        ///// do it with loop - it will be better

        /// read train.
        dio->write("Please upload your local train CSV file.\n");
        line = dio->read();
        while ("done" != line){
            train.push_back(line);
            line = dio->read();
        }
        makeFileFromVector(train, trainName);
        TimeSeries* ts1 = new TimeSeries(trainName);
        this->data->learnData = ts1;
        dio->write("Upload complete.\n");

        /// test train
        dio->write("Please upload your local test CSV file.\n");
        line = dio->read();
        while ("done" != line){
            test.push_back(line);
            line = dio->read();
        }
        TimeSeries* ts2 = new TimeSeries(trainName);
        this->data->TestDate = ts2;
        makeFileFromVector(train, testName);
        dio->write("Upload complete.\n");

    };



    virtual string getDes () {
        return this->description;
    };

    void makeFileFromVector(vector<string> vec, const char* fileName){
        ofstream file(fileName);
        ofstream output_file(fileName);
        ostream_iterator<std::string> output_iterator(output_file, "\n");
        copy(vec.begin(), vec.end(), output_iterator);
    }

};

class SettingsCommand : public Command {
public:
    SettingsCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "algorithm settings";
    };

    /**
     * the function presents the current correlation and allows to replace it with a value in the range 0-1
     */
    virtual void execute(){
        //print the current corr
        this->dio->write("The current correlation threshold is " );
        this->dio->write(this->data->detector->GetMinThresh() );
        this->dio->write("\n" );
        //get new corr
        float corr;
        this->dio->read(&corr);
        //while the correlation entered isn't in the right range, show alert and start over.
        if (corr < 0 || corr > 1) {
            this->dio->write("please choose a value between 0 and 1" );
            this->execute();
        } else {
            this->data->detector->ChangeMinThresh(corr);
            return;
        }
    };
};

class AnomalyDetectionCommand : public Command{
public:
    AnomalyDetectionCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "detect anomalies";
    };

    /**
    * the function implements the anomaly detector's algorithm on the input data
    */
    virtual void execute(){
        //learn
        this->data->detector->learnNormal(*this->data->learnData);
        //detect
        this->data->reports = this->data->detector->detect(*this->data->TestDate);
        this->dio->write("anomaly detection complete.\n" );
    };
};

class ResultCommand : public Command{
public:
    ResultCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "display results";
    };

    /**
     * the function print the anomaly found in the data.
     */
    virtual void execute(){
        for(AnomalyReport& r : this->data->reports) {
            this->dio->write(r.timeStep);
            this->dio->write("/t");
            this->dio->write(r.description);
            this->dio->write("/n");
        }
        this->dio->write("Done./n");
    };
};

class AnalyzeCommand : public Command{
public:
    AnalyzeCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};

class ExitCommand : public Command{
public:
    ExitCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "6.exit\n";
    };
    virtual void execute(){};
    virtual string getDes () {
        return this->description;
    };

};

#endif /* COMMANDS_H_ */
