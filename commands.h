

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

class AnomalyDetectorData{
public:
    TimeSeries* learnData;
    TimeSeries* TestDate;
    HybridAnomalyDetector* detector = new HybridAnomalyDetector();
    AnomalyReport* report;
    virtual ~AnomalyDetectorData(){};
};

class Command{
protected:
	DefaultIO* dio;
    AnomalyDetectorData* data;
    string description;
    FILE trainFile;
    FILE testFile;
public:
	Command(DefaultIO* dio, AnomalyDetectorData* data):dio(dio), data(data){}
	virtual void execute()=0;
	virtual ~Command(){}
    virtual string getDes () = 0;
};

// implement here your command classes
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
        ///// TODO: do it with loop - it will be better

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

    FILE makeFileFromVector(vector<string> vec, const char* fileName){
        ofstream file(fileName);
        ofstream output_file(fileName);
        ostream_iterator<std::string> output_iterator(output_file, "\n");
        copy(vec.begin(), vec.end(), output_iterator);
    }

};
class SettingsCommand : public Command {
    SettingsCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};
class AnomalyDetectionCommand : public Command{


AnomalyDetectionCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
    this->description = "3.detect anomalies\n";
};
    virtual void execute(){

        this->data->detector->learnNormal(*(this->data->learnData));
        this->data->detector->learnNormal(*(this->data->TestDate));
        this->dio->write("anomaly detection complete.\n");

    };
    virtual string getDes () {
        return this->description;
    };

};
class ResultCommand : public Command{
    ResultCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};
class AnalyzeCommand : public Command{
    AnalyzeCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};

class ExitCommand : public Command{
    ExitCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "6.exit\n";
    };
    virtual void execute(){};
    virtual string getDes () {
        return this->description;
    };

};

#endif /* COMMANDS_H_ */
