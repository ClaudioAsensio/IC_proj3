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
          fcm -> close();
          return b;
        }

        bool compare(string fPath)
        {
            bool path = open(fPath);
            if(!path)
                return path;
            string buffer = "";
            char character;
            double bits = 0;
            // start reading file
            while(inputFile >> noskipws >> character)
            {
                // only consider letters and spaces
                if(!isalpha(character))
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
                    buffer = buffer.substr(1, k);
                    buffer += character;
                }
                totalCharacters++;
              //  fcm -> printCharProbability();

            }
            cout<<"Estimativa:"<<bits<<endl;
            // this->estimate = bits;
            // this->bits_per_char = bits /= totalCharacters;
            bits /= totalCharacters;
            cout <<"bits por caracter: " << bits << endl;
            // cout << "Total characters read from destiny: " << totalCharacters << endl;
            // cout << "Average bits / symbol (Destiny): " << bits << endl;
            close();
            return true;
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
