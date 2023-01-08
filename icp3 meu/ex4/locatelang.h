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
    LANG *language;
    map <int,map<string, float> > segmentsLang;
    map<int,string> located;



    // map<string, string> segmentsLang;


    public:

    //constructor
    locatelang(int k, float alpha,string destinyFile){
        this->k = k;
        this->alpha = alpha;
        this->destinyFile = destinyFile;
        cout<<"Locate lang constructor"<<endl;
        
    }

    void buildModelLocate(string fPath){
        language = new LANG(k, alpha);
        language->build(fPath);
        language->compareBits(this->destinyFile,fPath);
        
        if(this->segmentsLang.empty()){
            this->segmentsLang = language->getSegmentsLang();
        }else{
            map <int,map<string, float> > segmentsLang2 = language->getSegmentsLang();
            for(auto it = segmentsLang2.begin(); it != segmentsLang2.end(); it++){
                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                    this->segmentsLang[it->first][it2->first] = it2->second;
                }
            }

        }
        cout<<"Model built"<<endl;
       
    }

    void printSegmentsLang(){
            for(auto it = segmentsLang.begin(); it != segmentsLang.end(); it++){
                // cout<<"Offset: "<<it->first<<endl;
                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                    // cout<<"Lang: "<<it2->first<<" Bits: "<<it2->second<<endl;
                }
            }
        }

    void locate(){
        cout<<"Locate"<<endl;
        
        

        //go through the segmentLang map and get the language with the less bits
        for(auto it = segmentsLang.begin(); it != segmentsLang.end(); it++){
            string Slang=it->second.begin()->first;
            float min=it->second.begin()->second;
            for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                if(it2->second < min ){
                    // cout<<"diff: "<<min-(it2->second)<<endl;
                    min = it2->second;
                    Slang = it2->first;
                }

            }
            located[it->first] = Slang;
            // cout<<"Final lang:"<<Slang<<" offset"<<it->first <<endl;
        }
        //print the located map to a file
        ofstream myfile;
        myfile.open ("located.txt");
        int o  = 0;
        for(auto it = located.begin(); it != located.end(); it++){
            myfile<<"offset: "<<it->first<<" lang: "<<it->second<<endl;
            //print in the terminal the offset interval and the lang
            if (it->second != next(it)->second  || next(it) == located.end()){
                cout<<"Offset interval: "<<o <<"-"<<it->first<<" Lang Model: "<<it->second<<endl;
                o = it->first;
            }
            
        }
        myfile.close();
        
    }

};