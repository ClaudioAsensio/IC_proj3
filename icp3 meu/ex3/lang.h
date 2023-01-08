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
                    segmentsLang[offset][lang] = -log2(fcm->getCharProbability(buffer, character));
                    buffer = buffer.substr(1, k);
                    buffer += character;
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
