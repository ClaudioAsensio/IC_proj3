#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <map>

using namespace std;

class FCM
{

    private:

        //container to hold the information of a symbol from a context
        struct Symbols
        {
            //total number of symbols
            int count = 0;
            // map of counts for each symbol in context
            map<char, int> Map;

        };


        int k;  // order of the model
        float alpha;    // smoothing parameter
        // files
        ifstream inputFile;
        // model
        map<string, Symbols> *context;
        map<string, map<char, double>> *probability;
        map<char, int> *contextMap;
        //map of total number of context
        map<string, int> totalCtx;
        int totalCharacters;
        double modelEntropy=0;
        //array to count the different characters 
        int charCount=0;
        

    public:

        // constructor
        FCM(int k, float alpha)
        {
            this->k = k;
            this->alpha = alpha;
            context = new map<string, Symbols>();
            probability = new map<string, map<char, double>>();
            totalCharacters = 0;
        }

        // returns the current probability for context model
        map<string, map<char, double>> getContextProbability()
        {
            return *probability;
        }

        // returns the current context model
        map<string, Symbols> getContext()
        {
            return *context;
        }

        

        // computes probability distribution from context model
        void getProbability()
        {
            if(totalCharacters == 0)
            {
                cerr << "Context model is empty." << endl;
                return;
            }
            // loop all keys
            for(auto key : *context)
            {
                // loop all maps in every Symbols struct
                for(auto value : key.second.Map)
                {
                    // cout << "key.first: " << key << "vaal"<<value.second << endl;
                    double prob = ((double) value.second + alpha) / (key.second.count + charCount * alpha);
                    // probability of each next char
                    (*probability)[key.first][value.first] = prob;
                }
            }

            
        }

        // build model
        bool build(string fPath)
        {
            bool path = open(fPath);
            if(!path)
                return path;
            string buffer = "";
            char character;

            //array to store the different characters
            string diffchars="";
            // start reading file
            while(inputFile >> noskipws >> character)
            {
                // only consider letters
                if(isdigit(character)||character == ' ')
                    continue;
                character = tolower(character);
                // cout<<"totalCharacters:"<<totalCharacters<<endl;
                //array to store the different characters
                if(totalCharacters < k)
                {
                    // initial context
                    buffer += character;
                   

                }
                else
                {
                    // add symbol to context
                    (*context)[buffer].Map[character]++;
                    (*context)[buffer].count++;
                    buffer = buffer.substr(1, k);
                    buffer += character;
                    //cout << "buffer: " << buffer << endl;
                }
                totalCharacters++;
            }
            
            //get all the first characters of each context to the string diffchars if they are not already in it
            for(auto key : *context)
            {
                if(diffchars.find(key.first[0]) == string::npos && isalpha(key.first[0]))
                {
                    diffchars+=key.first[0];
                    charCount++;
                }
            }

            cout << "Total characters read: " << totalCharacters << endl;
            // countCharacters(fPath);
            cout<<"Alphabet:"<<diffchars<<endl;
            cout << "Total different characters: " << charCount << endl;
            getProbability();
            calcmodelEntropy();
            return true;
        }

        // prints current built context model
        // from this, you can see how many times the combination of two letters appers
        // and how many times the next characters appers after those 2 letters combined
        void printContext()
        {

            for(auto key : *context)
            {
                cout << key.first << " (" << key.second.count << " items)" << ": { ";
                for(auto value : key.second.Map)
                {
                    cout << value.first << " : " << value.second << "; ";
                }
                cout << "}" << endl;
            }
        }

        // prints current built model probability distribution
        // from this, you can see the probability of each next characters that appers after
        // the combination of two letters
        void printProbability()
        {
            for(auto key : *probability)
            {
                //context probability is the sum of all the next characters probability * log2 of the probability
                
                for(auto value : key.second)
                {
                    cout << value.first << " : " << value.second << "; ";
                }
                cout << "}" << endl;
            }
        }



        //model entropy = sum pcontect * entropy of context

        // computes entropy of a context

        // computes entropy of a context
        double entropy(string context)
        {
            double contextEntropy = 0;
            for(auto key : (*probability)[context])
            {
                contextEntropy += (-log2(key.second) * key.second);
            }
            return contextEntropy;
        }

        // computes entropy of a model
        void calcmodelEntropy()
        {
            int totalContxts=0;//total number of contexts
            for(auto key : *context)
            {   
                totalContxts+=key.second.count;
            }

            

            for(auto key : *context)
            {
                //totalconxtxs/sum the ocurrencis of 1 context
                double contextProbability = (double)key.second.count/totalContxts;
                modelEntropy += contextProbability * entropy(key.first);

            }

            cout << "Model entropy: " << modelEntropy << endl;
            cout<<"Alphabet size: "<<charCount<<endl;
            
        }

        // count all the diffrent characters in the file
        
        // returns a probability associated with the given context character based on model information
        double getCharProbability(string cont, char character)
        {
            if(context->find(cont) != context->end())
            {
                //cout << "string context: " << cont << endl;
                //cout << "character: " << character << endl;
                contextMap = &(*context)[cont].Map;
                // cout<< "contextMap: " << contextMap << endl;
                // character found -> return probability from model
                // else character was not found in given context -> compute probability with alpha
                if(contextMap->find(character) != contextMap->end())
                    return (*probability)[cont][character];

            }
            // given context was not found -> compute probability based on alphabet only
            return (((double) alpha) / ((*context)[cont].count + charCount * alpha));
            // return (1.0 / charCount);
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
            totalCharacters = 0;
            charCount = 0;
            return true;
        }

};
