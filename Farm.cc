#include "Farm.h"
#include "Util.h"
#include "Field.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
using namespace std;

//---------------------------------------------------------------
const string HEADER1="---- start ----";
const string HEADER2="---- distribution ----";
const string HEADER3="---- end ----";
const string HOUR="Hour: ";
const string SEPARATOR="===============================================";
const string INTRODUCESPEED="Enter android speed: ";
const string INTRODUCEFIELD="Enter field name: ";
const string INTRODUCEMODEL="Enter android model: ";
const string INTRODUCEPRODUCTS="Products: " ;
//---------------------------------------------------------------
void Farm::ObtenerAndroidMasRapido(int &idMaxSpeed){
int MaxSpeed=0;
    for(unsigned int j=0;j<numAndroids;j++){
        if(androids[j].getSpeed() > MaxSpeed && androids[j].getStatus() == ST_IDLE){
            MaxSpeed=androids[j].getSpeed();
            idMaxSpeed=j;
        }
    }
}

void Farm::ObtenerMinimo(int &idMinimo){
bool encontrado=false;
    for(unsigned int i=0;i<fields.size();i++){

        if(fields[i].needsDroids()){
            
            if(encontrado == false){
                encontrado = true;
                idMinimo = i;
            }
            else{
                if(fields[i].numAndroids() == fields[idMinimo].numAndroids() && fields[i].getProducts() > fields[idMinimo].getProducts()){
                    idMinimo = i;
                }
                if(fields[i].numAndroids() < fields[idMinimo].numAndroids()){
                    idMinimo = i;
                }
            }
        }
    }
}

void Farm::searchingFieldsName(string &products, string &field, size_t &posinicial){
field="";
char delimitador='"';
posinicial=products.find(delimitador,posinicial);
    if(posinicial!=string::npos){
        posinicial=posinicial+1;
        unsigned int posfinal=products.find(delimitador,posinicial);
            if(posfinal!=string::npos){
                for(size_t i=posinicial;i<posfinal;i++){
                    field+=products[i];
                }
            posinicial=posfinal+1;
            }
            else{
                   // cout << "No se ha encontrado la posicion '' FINAL" << endl;
            }
    }
    else{
        // cout << "No se ha encontrado '' INICIAL" << endl;
    }
}


void Farm::searchingNumProducts(string &products, unsigned int &numProducts, size_t posinicial){
string sProducts="";
char delimitador=':';
bool encontrado=true;
size_t pos=products.find(delimitador,posinicial);
    if(pos!=string::npos){
        pos=pos+1;
            do{
                if(products[pos]==' '){
                    pos=pos+1;
                    encontrado=true;
                }
                else{
                    encontrado=false;
                }
            }while(encontrado==true);
            
            while(products[pos]>='0' && products[pos]<='9'){
            sProducts+=products[pos];
            pos=pos+1;
            } 
            numProducts=atoi(sProducts.c_str());
                    
    }
    else{
       // cout << "No se ha encontrado :" << endl;
    }
}


Farm::Farm(string name){
    this->name=name;
    this->numAndroids=0;
}

string Farm::getName() const {
    return name;
}

unsigned int Farm::numFields() const {
return fields.size();    
}

unsigned int Farm::getNumAndroids() const{
return numAndroids;
}

void Farm::createField(string name){
string n;
bool encontrado=false;
    if(name==""){
            cout << INTRODUCEFIELD;
            getline(cin,n);
    }
    else{
     n=name;
    }
    for(unsigned int i=0;i<fields.size();i++){
        if(fields[i].getName() == n){
            encontrado=true;   
        }
    }
    if(encontrado==true){
        Util::error(ERR_NAME);
    }
    else{
        Field f(n);
        fields.push_back(f);
    }
}
    
void Farm::createAndroid(int speed, string model){
bool error=false;
    if(numAndroids<MAXANDROIDS){
        if(speed==-1){
                cout << INTRODUCESPEED;
                cin >> speed;
                cin.get();
        }
        if(speed<=0){
            Util::error(ERR_WRONG_SPEED);
            error=true;
        }
        
        else{
            if(model==""){
            cout << INTRODUCEMODEL;
            getline(cin,model);
            }
        }
        
        if(error == false){
            try{
             Android a(model,speed);
             androids[numAndroids]=a;
             numAndroids++;
            }
            catch(invalid_argument &ex){
                    if(strcmp(ex.what(),"wrong speed")== 0){
                        Util::error(ERR_WRONG_SPEED);   
                    }
                    else{
                        Util::error(ERR_WRONG_MODEL);
                    }
            }    
        }
    }
    else{
        Util::error(ERR_MAXANDROIDS);
    }
}

void Farm::processProducts(string products){
unsigned int tamProducs=products.length();
string field="";
unsigned int numProducts=0;
int idencontrado=0;
size_t posinicial=0;
    do{
        searchingFieldsName(products,field,posinicial);
        if(field!=""){
            bool encontrado=false;
            for(unsigned int i=0;i<fields.size();i++){
                if(fields[i].getName() == field){
                encontrado=true;
                idencontrado=i;
                }
            }
            if(encontrado==true){
                searchingNumProducts(products,numProducts,posinicial);
                if(numProducts!=0){
                    fields[idencontrado].addProducts(numProducts);
                }
                else{
                    Util::error(ERR_WRONG_PRODUCTS);
                }
            }
            else{
            Util::error(ERR_WRONG_FIELD); 
            }
        }
    }while(posinicial<=tamProducs);
}

void Farm::distributeAndroids(){

int idMinimo=999999;
int idMaxSpeed=999999;
    ObtenerMinimo(idMinimo);
    ObtenerAndroidMasRapido(idMaxSpeed);
    // ponemos al androide en modo trabajo y le decimos que está asignado
    if(idMaxSpeed!=999999 && idMinimo!=999999){
    androids[idMaxSpeed].setStatus(ST_WORKING);}
    // insertamos al android mas rapido en el campo que con mas productos y menos androides
    if(idMaxSpeed!=999999 && idMinimo!=999999){
    fields[idMinimo].addDroid(&androids[idMaxSpeed]);}

}

void Farm::collect(int &hour){

bool productsup=false;
for(unsigned int l=0;l<fields.size();l++){
        if(fields[l].getProducts()>0){
            productsup=true;
        }
}
    cout << SEPARATOR << endl;
    cout << HOUR << hour << endl;
    cout << HEADER1 << endl;
    cout << *this;
    if(productsup==true){
        for(unsigned int i=0;i<numAndroids;i++){
        distributeAndroids();
        }
    }
    cout << HEADER2 << endl;
    cout << *this;
    if(productsup==true){
        for(unsigned int b=0;b<fields.size();b++){
            fields[b].collect();
        }
    }
    hour=hour+1;
    cout << HEADER3 << endl;
    cout << *this;        
        if(hour==11){
            
            hour=1;
            for(unsigned int x=0; x < numAndroids; x++){
             
                if(androids[x].getStatus() == ST_MAINTENANCE0){
                    androids[x].setStatus(ST_MAINTENANCE1);
                }
                else{
                    if(androids[x].getStatus() == ST_MAINTENANCE1){
                        androids[x].setStatus(ST_IDLE);
                        androids[x].resetHoursWorked();
                    }
                }
            }
        }
}

void Farm::startWorkingHour(int &hour){

string products;    

	if(fields.size()>0){
    	if(hour==1){
            cout << INTRODUCEPRODUCTS;
            getline(cin,products);
            processProducts(products);
        }
    		// iniciamos la recoleccion de la granja una vez hemos asignado los productos al campo
            collect(hour);
    
	}
	else{
            Util::error(ERR_NO_FIELDS);   
	}
}

ostream &operator<<(ostream &os, Farm& f){
    
    os << "Farm: " << f.name << endl;
    
    for(unsigned int i=0;i<f.fields.size();i++){
        os << f.fields[i];
    }
    for(unsigned int j=0;j<f.numAndroids;j++){
        if(f.androids[j].isAssigned() == false){
            os << f.androids[j]; 
        }
    }
return os;
}

