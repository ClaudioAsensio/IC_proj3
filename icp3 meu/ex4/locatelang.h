#include "lang.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <math.h>

using namespace std;

//class
class locatelang{


    private:
    //variables
    int k;
    float alpha;
    string destinyFile;
    string *languagesTo;
    LANG *language;
    //array to store the segments of the destiny file
    // string *segments;
    //map to store the segments and the language and the offset of the segment in the destiny file
    map <int,map<string, float> > segmentsLang;
    map<int,string> located;
    // contex <bits,lang>
    //segment array
    map<int, string> segments;



    // map<string, string> segmentsLang;


    public:

    //constructor
    locatelang(int k, float alpha,string destinyFile){
        this->k = k;
        this->alpha = alpha;
        this->destinyFile = destinyFile;
        // this->languagesTo = languagesTo;
        language = new LANG(k, alpha);
        // this->findLang = new findlang(k,alpha,destinyFile);
        cout<<"Locate lang constructor"<<endl;
        
    }

    void buildModelLocate(string fPath){
        cout<<fPath<<endl;
        language->build(fPath);
        language->compareBits(this->destinyFile,fPath);
        // language->compareBits(text, fPath);
        cout<<"Model built"<<endl;
        // locate();
    }

    void locate(){
        cout<<"Locate"<<endl;
        this->segmentsLang = language->getSegmentsLang();
        cout<<"Size of segmentsLang: "<<this->segmentsLang.size() <<endl;
        

        //go through the segmentLang map and get the language with the less bits
        for(auto it = segmentsLang.begin(); it != segmentsLang.end(); it++){
            cout<<"ofsset: "<<it->first<<endl;
            string Slang=it->second.begin()->first;
            float min=it->second.begin()->second;
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                if(it2->second < min){
                    min = it2->second;
                    Slang = it2->first;
                }
                
                
                



            }
            located[it->first] = Slang;
            cout<<"Final lang:"<<Slang<<" offset"<<it->first <<endl;
        }
        //print the located map to a file
        ofstream myfile;
        myfile.open ("located.txt");
        for(auto it = located.begin(); it != located.end(); it++){
            myfile<<"offset: "<<it->first<<" lang: "<<it->second<<endl;
        }
        myfile.close();
        // for(auto it = located.begin(); it != located.end(); it++){
        //     cout<<"offset: "<<it->first<<" lang: "<<it->second<<endl;
        // }
        language->printSegmentsLang();
    }

    

    // void locateLang(){
    //     //get the language->segmentsLang and make the comparation in each entry of the map,if the bits for a lang is less than the bits of the other lang, then the lang is the one with the less bits
    //     for(auto it = segmentsLang.begin(); it != segmentsLang.end(); it++){
    //         cout << it->first << " " << it->second << endl;

    //     } 
    // }


    
};