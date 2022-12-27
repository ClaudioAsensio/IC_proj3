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
    cout << "Choosen k value: " << k << endl;
    cout << "Choosen smoothing parameter: " << alpha << endl;
    cout << "--------------------------" << endl;
    // cout << "Choosen text file for model: " << sourceFile << endl;

    //array of languages to check with size of the arguments - 3
    string languages[argc-3];


    // findlang findLang(k, alpha,destinyFile);

    // findLang.buildModel(sourceFile);
    // findLang.buildModel(sFile);

    //while have arguments use them to build the models
    for(int i = 3; i < argc - 1; i++)
    {
        // string sourceFile = argv[i];
        // cout << "--------------------------" << endl;    
        // cout << "Choosen text file for model: " << sourceFile << endl;
        // locatelang.findlang.buildModel(sourceFile);
        //store the languages in the array
        languages[i-3] = argv[i];
        cout << "--------------------------" << endl;
        cout << "Choosen text file for model: " << languages[i-3] << endl;
    }
    cout << "--------------------------" << endl;
    locatelang locatelang(k, alpha,destinyFile,languages);
    locatelang.getSegments();
    cout << "---------------------2-----" << endl;
    locatelang.compareSegment();


    // findLang.buildModel("ENG.txt");
    // findLang.buildModel("FR.txt");
    // findLang.buildModel("ITA.txt");
    cout << "--------------------------" << endl;
    cout << "Choosen text file to compare: " << destinyFile << endl;
    
    // cout<< "the language is:"<<findLang.getlang()<<endl;
    // LANG lang(k, alpha);
    // lang.build(sourceFile);
    // cout << "--------------------------" << endl;
    // cout << "Choosen text file to compare: " << destinyFile << endl;
    // lang.compare(destinyFile);

    return 0;
}

