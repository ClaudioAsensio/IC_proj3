#include "locatelang.h"

int main(int argc, char **argv)
{
   if(argc < 6)
    {
        cerr << "Invalid parameters. Use: ./mainRun <int k value> <float smoothing parameter value> <sourceFile1> <sourceFile2> ... <destinyFile>" << endl;
        exit(1);
    }
    int k = atoi(argv[1]);
    float alpha = stof(argv[2]);
    string sourceFile = argv[3];
    string sFile = argv[4];
    string destinyFile = argv[argc - 1];
    //map to store the segments of the destiny file
    map<int,string> segments; 
    //map to store and id and a map with segment and language
    map<int,map<string,string>> segmentsLang;
    cout << "Choosen k value: " << k << endl;
    cout << "Choosen smoothing parameter: " << alpha << endl;
    cout << "--------------------------" << endl;
 

    //build the models
    locatelang locatelang(k, alpha,destinyFile);
    for(int i = 3; i < argc - 1; i++)
    {
        sourceFile = argv[i];
        cout << "Choosen text file for model: " << sourceFile << endl;
        locatelang.buildModelLocate(sourceFile);
        cout << "--------------------------" << endl;
    }
    //find the language
    // locatelang.printSegmentsLang();
    locatelang.locate();

    return 0;
}

