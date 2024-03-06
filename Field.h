#ifndef _field
#define _field
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include "Android.h"
using namespace std;

class Field{
    
    protected:   
        string name;
        int products;
        int hoursLeft;
        int droidsCapacity() const;
        vector <Android *> androids;
    public:
        const static int WORKINGHOURS=10;
        Field(string fieldName);
        string getName() const;
        int getProducts() const;
        int getHoursLeft() const;
        unsigned int numAndroids() const;
        void setProducts(int products);
        void addProducts(int products);
        bool needsDroids() const;
        void addDroid(Android *newAndroid);
        void collect();
        friend ostream &operator<<(ostream &os, const Field& f);
};
#endif
