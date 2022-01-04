

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

//command 1
class UploadCommand : public Command{
public:
    UploadCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "upload a time series csv file";
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

        /// read test
        dio->write("Please upload your local test CSV file.\n");
        line = dio->read();
        while ("done" != line){
            test.push_back(line);
            line = dio->read();
        }
        TimeSeries* ts2 = new TimeSeries(testName);
        this->data->TestDate = ts2;
        makeFileFromVector(train, testName);
        dio->write("Upload complete.\n");
    };

    void makeFileFromVector(vector<string> vec, const char* fileName){
        ofstream file(fileName);
        ofstream output_file(fileName);
        ostream_iterator<std::string> output_iterator(output_file, "\n");
        copy(vec.begin(), vec.end(), output_iterator);
    }

};

//command 2
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
        this->dio->write(this->data->detector->GetLinThresh() );
        this->dio->write("\n" );
        //get new corr
        float corr;
        this->dio->read(&corr);
        //while the correlation entered isn't in the right range, show alert and start over.
        if (corr < 0 || corr > 1) {
            this->dio->write("please choose a value between 0 and 1" );
            this->execute();
        } else {
            this->data->detector->ChangeLinThresh(corr);
            return;
        }
    };
};

//command 3
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
        this->data->reports = this->data->detector->detect(*this->data->TestData);
        this->dio->write("anomaly detection complete.\n" );
    };
};

//command 4
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
        this->dio->write("Done. /n");
    };
};

//command 5
class AnalyzeCommand : public Command{
public:
    AnalyzeCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "5.upload anomalies and analyze results.\n";
    }
    void add(vector<Point>* v, string line){
        vector<float> temp;
        stringstream ss(line);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            temp.push_back(stof(substr));
        }
        Point pnt(temp[0], temp[1]);
        v->push_back(pnt);
    }

    int intervalSum(vector<Point>* points){
        int temp = 0;
        for (Point p : *points) {
            temp += p.y - p.x;
        }
        return temp;
    }



    virtual void execute(){
        vector<Point>* points = new vector<Point>();
        string line;
        int N, P, TP = 0, FN = 0;

        int n = this->data->TestDate->lineSize();
        //// reading the file into vector.
        this->dio->write("Please upload your local anomalies file.\n");
        line = this->dio->read();
        while(line != "done"){
            add(points, line);
            line = this->dio->read();
        }
        dio->write("Upload complete.\n");
        N = n - intervalSum(points);
        P = points->size();

        this->data->detector->

    }

    virtual string getDes () {
        return this->description;
    }

};

//command 6
class ExitCommand : public Command{
public:
    ExitCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "exit";
    };
    virtual void execute(){};
    virtual string getDes () {
        return this->description;
    };

};

#endif /* COMMANDS_H_ */
