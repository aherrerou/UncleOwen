#include "Field.h"
#include <cstring>
#include "Farm.h"
using namespace std;

const int DAILY_WORKING_HOURS=10;

Field::Field(string name){
    
    this->name=name;
    this->products=0;
    this->hoursLeft=DAILY_WORKING_HOURS;
}

string Field::getName() const{
    return name;
}

int Field::getProducts() const{
    return products;
}

int Field::getHoursLeft() const{
    return hoursLeft;
}

unsigned int Field::numAndroids() const{
    return androids.size();
}

void Field::setProducts(int products){
    if(products>0){
        this->products=products;
    }
    else{
        this->products=0;
    }
}

void Field::addProducts(int products){
    if(products>0){
        this->products=this->products+products;
    }
    else{
        this->products=0;
    }
}

bool Field::needsDroids() const{
    bool needDroid=false;
    int total;
    total=droidsCapacity();
        if(total<products){
            needDroid=true;
        }
    return needDroid;
}

void Field::addDroid(Android *newAndroid){
    newAndroid->setAssigned(true);
    newAndroid->setStatus(ST_WORKING);
    androids.push_back(newAndroid);
}

int Field::droidsCapacity() const{
    int droidCapacity=0;
    for(unsigned int i=0;i<androids.size();i++){
     droidCapacity=droidCapacity+androids[i]->getSpeed();
    }
    
    return droidCapacity;
}

void Field::collect(){
    
int sumaandroids=0;
const int KNUMHORAS=1;
    for(unsigned int j=0;j<androids.size();j++){
        sumaandroids=androids[j]->getSpeed()+sumaandroids;
        androids[j]->oneMoreHour();
        if(androids[j]->isMaintenanceTime() == true){
            androids[j]->setStatus(ST_MAINTENANCE0);
            androids[j]->setAssigned(false);
            androids.erase(androids.begin() + j);
            j--;
        }
    }
    this->products=this->products-(sumaandroids*KNUMHORAS);
    
    if(this->products<0){
        this->products=0;
    }
    if(this->hoursLeft>0 && this->products > 0){
     this->hoursLeft=this->hoursLeft-1;   
    }

        if(this->products == 0 || this->hoursLeft == 0){
            unsigned int y=0;
            while (y < androids.size()){
                androids[y]->setStatus(ST_IDLE);
                androids[y]->setAssigned(false);
                y++;
                }
                this->hoursLeft=DAILY_WORKING_HOURS;
                androids.clear();
            }
}

ostream& operator<<(ostream &os, const Field& f){
     
    os << "{Field: " << f.name << "(" << f.products << " " << f.hoursLeft << ")" << endl;
           
    for(unsigned int j=0;j<f.androids.size();j++){
        if(f.androids[j]->getStatus()==ST_WORKING){
        cout << "  ";
        os << *(f.androids[j]);
        }
    }
    os << "}" << endl;
    return os;
    
}
