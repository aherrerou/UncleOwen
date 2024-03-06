#ifndef _android
#define _android
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

enum Status {
  ST_WORKING, 
  ST_IDLE, 
  ST_MAINTENANCE0,
  ST_MAINTENANCE1 
};

class Android{
            
    protected:
        string model;
        int speed;
        int serialNumber;
        int hoursWorked;
        static int nextSerialNumber;
        Status status;
        bool assigned;
    
    public:
        Android();
        Android(string model,int speed);
        string getModel() const;
        int getSpeed() const;
        static int getSerialNumber();
        int getHoursWorked() const;
        void resetHoursWorked();
        Status getStatus() const;
        bool isAssigned() const;
        void setAssigned(bool assigned);
        void setStatus(Status status);
        bool isIdle() const;
        void oneMoreHour();
        bool isMaintenanceTime() const;
        bool compareModel(string model);
        friend ostream &operator<<(ostream &os, const Android& a);
    
};
#endif