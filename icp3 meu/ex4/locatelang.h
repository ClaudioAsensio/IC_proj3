#include "findlang.h"
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
    findlang *findLang;
    //array to store the segments of the destiny file
    // string *segments;
    //map to store the segments and the language and the offset of the segment in the destiny file
    map <string,map<string, int> > segmentsLang;

    //segment array
    map<int, string> segments;



    // map<string, string> segmentsLang;


    public:

    //constructor
    locatelang(int k, float alpha,string destinyFile, string *languagesTo){
        this->k = k;
        this->alpha = alpha;
        this->destinyFile = destinyFile;
        this->languagesTo = languagesTo;
        // this->findLang = new findlang(k,alpha,destinyFile);
        cout<<"Locate lang constructor"<<endl;
        
    }

    //methods

    //compare segments of the destiny file with the models

    //open destiny file and read it and split it in segments on the .

    void getSegments(){
        //open destiny file
        ifstream file(destinyFile);
        string line;
        int i = 0;
        //read the file and split on the .
        while(getline(file,line,'.')){
            //store the segments in the segments array
            cout<<"line: "<<line<<endl;
            this->segments[i] = line;
            cout<<"destiny file: "<<destinyFile<<endl;
            i++;


        }






        // while(getline(file,line)){
        //     //split the line in segments
        //     cout<<"line: "<<line<<endl;
        //     this->segments[i] = line;
        //     cout<<"destiny file: "<<destinyFile<<endl;
        //     i++;
        // }
        //close the file
        file.close();
        //compare the segments with the models
    }

    void compareSegment(){
       
        //go trough the segments array
        for(int i = 0; i < sizeof(segments); i++){
            //for each segment write it to a text file
            ofstream file("text.txt");
            file<<segments[i];
            file.close();
            //compare the segment with the models
            findlang *findLang = new findlang(k,alpha,"text.txt"); //the text is a file path with one segment of the destiny file
            cout<<"segment: "<<segments[i]<<endl;
            //go trough the languagesTo array and build the models
            for(int i = 0; i < sizeof(this->languagesTo); i++){
                findLang->buildModel(this->languagesTo[i]);
            }

            //get the language with the smallest distance
            string lang = findLang->getlang();
            cout<<"segment: "<<segments[i]<<" language: "<<lang<<endl;

            //store the segment and the language in the segmentsLang map
            // segmentsLang[content][sizeof(segmentsLang)] = lang;  

            //store the segment and the language in the segmentsLang map
            // segmentsLang[segments[i]][lang] = sizeof(segments[i]);  
        }

        //for each segment write it to a text file

        
        

        // findlang *findLang = new findlang(k,alpha,text); //the text is a file path with one segment of the destiny file
        // //go trough the languagesTo array and build the models
        // for(int i = 0; i < sizeof(languagesTo); i++){
        //     findLang->buildModel(languagesTo[i]);
        // }

        // //get the language with the smallest distance
        // string lang = findLang->getlang();
        // cout<<"segment: "<<content<<" language: "<<lang<<endl;

        //store the segment and the language in the segmentsLang map
        // segmentsLang[content][sizeof(segmentsLang)] = lang;  

        //store the segment and the language in the segmentsLang map
               


    }




    
};