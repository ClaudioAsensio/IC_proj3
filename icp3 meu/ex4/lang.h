#include "fcm.h"

class LANG {

    private:

        int k;
        float alpha;
        int totalCharacters = 0;

        ifstream inputFile;
        FCM *fcm;

        float estimate = 0;
        float bits_per_char = 0;
        int offset = 0;

        map <int,map<string, float> > segmentsLang;
        // buffer offset in file <bits,lang>

    public:

        LANG(int k, float alpha)
        {
          this-> k = k;
          this -> alpha = alpha;
          fcm = new FCM(k,alpha);
        }

        bool build(string fPath)
        {
          bool b = fcm -> build(fPath);
        //   fcm -> close();
          return b;
        }

        bool compare(string fPath)
        {
            totalCharacters = 0;
            bool path = open(fPath);
            if(!path)
                return path;
            string buffer = "";
            char character;
            double bits = 0;
            // start reading file
            while(inputFile >> noskipws >> character)
            {
                // only consider letters and letters with accents

                

                if(isdigit(character)||character == ' ')  
                    continue;
                character = tolower(character);
                if(totalCharacters < k)
                {
                    // initial context
                    buffer += character;
                    offset++;
                }
                else
                {
                    // compute bits based on model
                    bits -= log2(fcm->getCharProbability(buffer, character));
                    cout<<"buffer: "<<buffer<<endl;
                    cout << "bits: " << bits << endl;
                    buffer = buffer.substr(1, k);
                    buffer += character;
                    cout<<"buffer: "<<buffer<<endl;
                }
                totalCharacters++;
              //  fcm -> printCharProbability();

            }
            cout<<"Estimativa:"<<bits<<endl;
            this->estimate = bits;
            this->bits_per_char = bits /= totalCharacters;
            // bits /= totalCharacters;
            cout <<"bits por caracter: " << this->bits_per_char << endl;
            // cout << "Total characters read from destiny: " << totalCharacters << endl;
            // cout << "Average bits / symbol (Destiny): " << bits << endl;
            close();
            return true;
        }

        bool compareBits(string fPath,string lang){

            totalCharacters = 0;
            offset = 0;
            bool path = open(fPath);
            if(!path)
                return path;
            string buffer = "";
            char character;
            double bits = 0;
            // start reading file
            while(inputFile >> noskipws >> character)
            {
                // only consider letters and letters with accents
                offset++;
                if(isdigit(character)||character == ' ')
                    continue;
                character = tolower(character);
                if(totalCharacters < k)
                {
                    // initial context
                    
                    buffer += character;
                    
                }
                else
                {
                    // compute bits based on model
                    bits -= log2(fcm->getCharProbability(buffer, character));
                    //store in the the segmentsLang map
                    
                    // segmentsLang[buffer][bits] = lang;
                    //if map is not empty in that offset check if the value bits is smaller than the one in the map
                    // if(!segmentsLang[totalCharacters].empty()){
                    //     //if the value is smaller than the one in the map, replace it
                    //     if(bits < segmentsLang[totalCharacters][lang]){
                    //         segmentsLang[totalCharacters][lang] = bits;
                    //     }
                    // }else{
                    //     //if the map is empty, insert the value
                    // }
                    segmentsLang[offset][lang] = bits;
                    
                    // cout<<"buffer: "<<buffer<<endl;
                    // cout<<"bits: "<<bits<<endl;
                    buffer = buffer.substr(1, k);
                    buffer += character;
                    // cout<<"buffer: "<<buffer<<endl;
                }
                totalCharacters++;
                cout<<"offset: "<<offset<<endl;
              //  fcm -> printCharProbability();

            }
            cout<<"Estimativa:"<<bits<<endl;
            this->estimate = bits;
            this->bits_per_char = bits /= totalCharacters;
            // bits /= totalCharacters;
            cout <<"bits por caracter: " << this->bits_per_char << endl;
            // cout << "Total characters read from destiny: " << totalCharacters << endl;
            // cout << "Average bits / symbol (Destiny): " << bits << endl;
            close();
            return true;

        }

        //print the segmentsLang map
        void printSegmentsLang(){
            for(auto it = segmentsLang.begin(); it != segmentsLang.end(); it++){
                cout<<"Offset: "<<it->first<<endl;
                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
                    cout<<"Lang: "<<it2->first<<" Bits: "<<it2->second<<endl;
                }
            }
        }

        //get the segmentsLang map
        map <int,map<string, float> > getSegmentsLang(){
            return segmentsLang;
        }

        float getBits()
        {
          return this->bits_per_char;
        }

        float getEstimate()
        {
          return this->estimate;
        }

        // open file
        bool open(string fPath)
        {
            if(inputFile.is_open())
                close();
            inputFile.open(fPath);
            if(inputFile.bad())
                return false;
            return true;
        }

        // close file
        bool close()
        {
            if(!inputFile.is_open())
                return 1;
            inputFile.close();
            
            return true;
        }

};
