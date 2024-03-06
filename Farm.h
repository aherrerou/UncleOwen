#ifndef _farm
#define _farm
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include "Util.h"
#include "Field.h"
#include "Android.h"
using namespace std;

class Farm{
    
    protected:
        static const int MAXANDROIDS=30;
        string name;
        unsigned int numAndroids;
        void distributeAndroids();
        void collect(int &hour);
        vector<Field> fields;
        Android androids[MAXANDROIDS];
        void searchingFieldsName(string &products, string &field, size_t &posinicial);
        void searchingNumProducts(string &products, unsigned int &numProducts, size_t posinicial);
        void ObtenerMinimo(int &idMinimo);
        void ObtenerAndroidMasRapido(int &idMaxSpeed);
        
    public:
        Farm(string name);
        string getName() const;
        unsigned numFields() const;
        unsigned getNumAndroids() const;
        void createField(string name="");
        void createAndroid(int speed=-1, string model="");
        void processProducts(string products);
        void startWorkingHour(int &hour);
        friend ostream &operator<<(ostream &os, Farm& f);
};
#endif
