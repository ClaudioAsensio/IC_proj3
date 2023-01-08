#include "fcm.h"

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << "Invalid parameters. Use: ./mainRun <int k value> <float smoothing parameter value> <textFile>" << endl;
        exit(1);
    }
    int k = atoi(argv[1]);
    float alpha = stof(argv[2]);
    string fPath = argv[3];
    cout << "Choosen k value: " << k << endl;
    cout << "Choosen smoothing parameter: " << alpha << endl;
    cout << "Text file path: " << fPath << endl;
    FCM fcm(k, alpha);
    fcm.build(fPath);
    // fcm.getContext();
    // fcm.printContext();
    // fcm.printProbability();
    // fcm.getContextProbability();
    // fcm.entropy();
    // fcm.calcmodelEntropy();
    fcm.close();
    return 0;
}

