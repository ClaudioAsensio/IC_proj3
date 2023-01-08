// #include <fcm.h>
#include "lang.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>


using namespace std;

//class
class findlang{


    private:
    map<string, float> models;
    string text;
    LANG *language;
    string lang;
    int k;
    float alpha;
    
    public:

    //constructor
    findlang(int k, float alpha,string text){
        this->k = k;
        this->alpha = alpha;
        this->text = text;
    }

    //build the model and store it in the map the model and the file name

    void buildModel(string fPath){
        language = new LANG(this->k, this->alpha);
        language->build(fPath);
        language->compare(text);
        models[fPath] = language->getEstimate(); // estimativa de bits
        cout<<"Model built"<<endl;
    }

    //print the models map

    void printModels(){
        for(auto it = models.begin(); it != models.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }


    void textLanguage(){        
        float min = models.begin()->second;
        this->lang = models.begin()->first;
        for(auto it = models.begin(); it != models.end(); it++){
            if(it->second < min){
                min = it->second;
                this->lang = it->first;
            }
        }
    }

    string getlang(){
        return this->lang;
    }


};