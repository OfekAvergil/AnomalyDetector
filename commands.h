

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
        makeFileFromVector(test, testName);
        TimeSeries* ts2 = new TimeSeries(testName);
        this->data->TestDate = ts2;
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
        this->data->reports = this->data->detector->detect(*this->data->TestDate);
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
    int TP;
    int FP;
public:
    AnalyzeCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){
        this->description = "5.upload anomalies and analyze results.\n";
        this->TP = 0;
        this->FP = 0;
    }
    void add(vector<pair<int,int>>* v, string line, vector<pair<long,long>> testvec){
        int xtest, ytest;
        int flag = 0;
        int sizeTest = testvec.size();
        vector<float> temp;
        stringstream ss(line);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            temp.push_back(stof(substr));
        }
        int x  = temp[0];
        int y = temp[1];
        pair<int,int> pnt(temp[0], temp[1]);
        v->push_back(pnt);

        /// check the interval with the test intervals.
        for (int i = 0; i < sizeTest; ++i) {
            xtest = testvec[i].first;
            ytest = testvec[i].second;
            if(x <= xtest && y <= ytest || x > xtest && y > ytest || x < xtest && y < ytest || x < xtest && y > ytest){
                this->TP++; // there is intersection between intervals
                flag = 1;
            }
        }
        if (flag == 0){
            this->FP++;
        }
    }

    int intervalSum(vector<pair<int,int>>* points){
        int t = 0;
        int size = (points->size());

        return t;
    }


    virtual void execute(){
        string line;
        long s, e;
        int N, P, sum = 0;
        vector<pair<int,int>>* points = new vector<pair<int,int>>();
        vector<AnomalyReport> reports = this->data->reports;
        vector<pair<long,long>> intervalsFromTest;
        int sizeOfReports = reports.size();

        /// making vector of intervals from test.
        for(int i = 0 ; i < sizeOfReports ; ++i) {
            if (0 == i) {
                s = reports[i].timeStep;
            }
            if (sizeOfReports == i) {
                e = reports[i].timeStep;
                intervalsFromTest.push_back({s, e});
            }
            if ((reports[i + 1].timeStep != (reports[i].timeStep + 1))) {
                e = reports[i].timeStep;
                intervalsFromTest.push_back({s, e});
                s = reports[i + 1].timeStep;
            }
        }

        //// reading the file into vector.
        this->dio->write("Please upload your local anomalies file.\n");
        line = this->dio->read();
        while(line != "done"){
            add(points, line, intervalsFromTest);
            line = this->dio->read();
        }
        dio->write("Upload complete.\n");

        /// making N - time steps without exceptions, P- Amount of exceptions.
        int n = this->data->TestDate->lineSize(); // all data lines.
        for(pair<int,int> p : *points) {
            sum += (p.second - p.first);
        }

        N = n - sum;

        P = points->size();

        //// print to user
        float tpRate = this->TP / P;
        float fpRate = this-> FP / N;
        this->dio->write("True Positive Rate: ");
        float rounded_down = floorf(tpRate * 1000) / 1000;
        this->dio->write(rounded_down);
        this->dio->write("\n");
        rounded_down = floorf(fpRate * 1000) / 1000;
        this->dio->write("False Positive Rate: ");
        this->dio->write(rounded_down);
        this->dio->write("\n");

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
