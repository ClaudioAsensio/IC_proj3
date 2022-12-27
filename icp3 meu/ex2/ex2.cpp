#include "lang.h"
//#include "fcm.hpp"

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        cerr << "Invalid parameters. Use: ./mainRun <int k value> <float smoothing parameter value> <sourceFile> <destinyFile>" << endl;
        exit(1);
    }
    int k = atoi(argv[1]);
    float alpha = stof(argv[2]);
    string sourceFile = argv[3];
    string destinyFile = argv[4];
    cout << "Choosen k value: " << k << endl;
    cout << "Choosen smoothing parameter: " << alpha << endl;
    cout << "--------------------------" << endl;
    cout << "Choosen text file for model: " << sourceFile << endl;
    LANG lang(k, alpha);
    lang.build(sourceFile);
    cout << "--------------------------" << endl;
    cout << "Choosen text file to compare: " << destinyFile << endl;
    lang.compare(destinyFile);

    return 0;
}
