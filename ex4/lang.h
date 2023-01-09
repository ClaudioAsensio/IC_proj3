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
                    buffer = buffer.substr(1, k);
                    buffer += character;
                }
                totalCharacters++;
              //  fcm -> printCharProbability();

            }
            this->estimate = bits;
            this->bits_per_char = bits / totalCharacters;
            cout<<"Estimativa:"<<bits<<endl;
            cout <<"bits por caracter: " << this->bits_per_char << endl;
            close();
            return true;
        }

        bool compareBits(string fPath,string lang){ //only used in ex4
            double tmp=0.0;
            int counter=0;
            totalCharacters = 0;
            offset = this->k;
            bool path = open(fPath);
            if(!path)
                return path;
            string buffer = "";
            char character;
            double bits = 0;
            // start reading file
            while(inputFile >> noskipws >> character)
            {
                //get length of the file
                
                                
                

                if(isdigit(character)||character == ' '|| ispunct(character)){
                    //special chars are counting for 2 offset
                    // offset++;
                    continue;
                }
                character = tolower(character);
                if(totalCharacters < k)
                {
                    // initial context
                    
                    buffer += character;
                    
                }
                else
                {
                    offset=inputFile.tellg();
                    // compute bits based on model
                    
                    
                    tmp+=-log2(fcm->getCharProbability(buffer, character));
                    bits -= log2(fcm->getCharProbability(buffer, character));
                    //if counter ==10 or end of file do the average

                    if (counter == 10|| (offset-totalCharacters)<10){

                        segmentsLang[offset][lang] = tmp/counter;
                        counter=0;
                        tmp=0.0;
                        // special=0;
                    }
                    buffer = buffer.substr(1, k);
                    buffer += character;
                    counter ++;
                }
                totalCharacters++;
                

            }
            this->estimate = bits;
            this->bits_per_char = bits / totalCharacters;
            cout<<"Estimativa:"<<bits<<endl;
            cout <<"bits por caracter: " << this->bits_per_char << endl;
            close();
            return true;

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
