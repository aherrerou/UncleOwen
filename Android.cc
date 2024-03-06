#include "Android.h"
#include <stdexcept>
using namespace std;
const int NUMDROIDMODELS=25;

typedef struct {
    string modelName;
    int hoursMaintenance;
} AndroidData;

const AndroidData ANDROIDDATA[NUMDROIDMODELS] = 
  {
    "x-75", 8,
    "fx-7", 10,
    "JK9", 15,
    "XAR-25", 5,
    "HC-2", 12,
    "Xj 23 v7.5", 10,
    "c3p0-2", 20,
    "r2d2", 15,
    "f9-x d27", 10,
    "-v65 +23", 11,
    "@prog2ua", 13,
    "#h45ht4g", 18,
    "fx-9", 10,
    "x-7", 12,
    "JK10", 7,
    "GHR tdi9", 10,
    "fx-8", 20,
    "fx-75", 5,
    "JK9-75", 14,
    "HC-3.7", 12,
    "xw-a87", 17,
    "tiDef 8", 25,
    "fx-5", 10,
    "fx-3", 8,
    "fx-4", 9
 }; 
 
int Android::nextSerialNumber=100;

bool Android::compareModel(string model){
    bool encontrado=false;
    for(int i=0;i<NUMDROIDMODELS;i++){
        if(model == ANDROIDDATA[i].modelName){
            encontrado=true;
        }
    }
    return encontrado;
}

Android::Android(){
    this->model="";
    this->speed=-1;
}

Android::Android(string model, int speed){
    
    if(compareModel(model)){
        if(speed > 0){
            this->speed=speed;
            this->model=model;
            this->serialNumber=nextSerialNumber;
            Android::nextSerialNumber=Android::nextSerialNumber+1;
            this->status=ST_IDLE;
            this->hoursWorked=0;
            this->assigned=false;
        }
        else{
            throw invalid_argument("wrong speed");
        }
    }
    else{
        throw invalid_argument("wrong android model");
    }
}

string Android::getModel() const{
    return model;
}

int Android::getSpeed() const{
    return speed;
}

int Android::getSerialNumber(){
    return nextSerialNumber;
}

int Android::getHoursWorked() const{
    return hoursWorked;
}

Status Android::getStatus() const{
    return status;
}

bool Android::isAssigned() const{
    return assigned;
}

void Android::setAssigned(bool assigned){
    this->assigned=assigned;
}

void Android::setStatus(Status status){
    this->status=status;
}

void Android::resetHoursWorked(){
    this->hoursWorked=0;
}

bool Android::isIdle() const{
    bool idle=false;
    if(status==ST_IDLE){
        idle=true;
    }
    return idle;
}

void Android::oneMoreHour(){
    this->hoursWorked=hoursWorked+1;
}

bool Android::isMaintenanceTime() const{
    bool needMaintenance=false;
        for(int j=0;j<NUMDROIDMODELS;j++){
            if(model == ANDROIDDATA[j].modelName){
                if (hoursWorked==ANDROIDDATA[j].hoursMaintenance){
                 needMaintenance=true;
                }
            }
        }
    return needMaintenance;
}

ostream& operator<< (ostream &os, const Android& a){
    os << "[" << a.model << " sn=" << a.serialNumber << " s=" << a.speed << " hw=" << a.hoursWorked << " st=" << a.status << " a=" << a.assigned << "]" << endl;
    return os;
}














