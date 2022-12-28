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

    //private variables:map of languages and their models estimative

    private:
    //map to store the models and the distance to the file2 after compare
    map<string, float> models;
    string lModel;//file path to build the model
    string text;
    // FCM *model;
    LANG *language;
    string lang;
    
    public:

    //constructor
    findlang(int k, float alpha,string text){
        // model = new FCM(k, alpha);
        language = new LANG(k, alpha);
        this->text = text;
    }

    //build the model and store it in the map the model and the file name

    void buildModel(string fPath){
        cout<<fPath<<endl;
        language->build(fPath);
        language->compare(text);
        models[fPath] = language->getEstimate(); // estimativa de bits
        printModels();
        textLanguage();
        cout<<"Model built"<<endl;
        cout<<"Model closed"<<endl;
        //get bits per char      
    }

    //print the models map

    void printModels(){
        for(auto it = models.begin(); it != models.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }

    //function to go trough the map and find the language with the smallest distance

    void textLanguage(){
        
       //get minimum value from the map
        float min = models.begin()->second;
        this->lang = models.begin()->first;
        for(auto it = models.begin(); it != models.end(); it++){
            if(it->second < min){
                min = it->second;
                this->lang = it->first;
            }
        }
        
    }

    void calculateDistance(){
        //get the distance from the model
        // model->compare(text);
        // models[lModel] = model->getEstimate();
        // printModels();
        // textLanguage();
    }

    string getlang(){
        return this->lang;
    }


};