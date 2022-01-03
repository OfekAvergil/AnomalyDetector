

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
public:
	Command(DefaultIO* dio, AnomalyDetectorData* data):dio(dio), data(data){}
	virtual void execute()=0;
	virtual ~Command(){}
    virtual string getDes () = 0;
};

// implement here your command classes
class UploadCommand : public Command{
public:
    UploadCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};
class SettingsCommand : public Command {
    SettingsCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};
class AnomalyDetectionCommand : public Command{
    AnomalyDetectionCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

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
    ExitCommand (DefaultIO* dio, AnomalyDetectorData* data) : Command(dio,data){};
    virtual void execute(){};
    virtual string getDes () {};

};

#endif /* COMMANDS_H_ */
