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
 

    // //open destiny file
    // ifstream file(destinyFile);
    // string line;
    // int i = 0;
    // //read the file and split on the .
    // while(getline(file,line,'.') && !line.empty()){
    //     //store the segments in the segments map
    //     cout<<"line: "<<line<<endl;
    //     segments[i] = line;
    //     i++;
    // }

    // file.close();

    //write 1 segment at a time to a aux file and call findlang
    // for(int i = 0; i < segments.size(); i++){
    //     ofstream auxFile;
    //     //if file not empty delete the content
    //     if(auxFile.is_open()){
    //         auxFile.close();
    //         auxFile.open("auxFile.txt", ios::trunc);
    //     }
    //     else
    //         auxFile.open("auxFile.txt");
    //         auxFile << segments[i];
    //         auxFile.close();
    //         findlang findlang(k, alpha, "auxFile.txt");
    //         for (int i = 3; i < argc - 1; i++)
    //         {
    //             sourceFile = argv[i];
    //             cout << "Choosen text file for model: " << sourceFile << endl;
    //             cout << "--------------------------" << endl;
    //             findlang.buildModel(sourceFile);
    //             cout << "--------------------------" << endl;
    //         }
    //         cout << "Choosen destiny file: " << destinyFile << endl;
    //         cout << "--------------------------" << endl;
    //         // findlang.getlang();
    //         //fill the map with the segment and the language
    //         segmentsLang[i][segments[i]] = findlang.getlang();
    //         //destroy the object
    //         // findlang.~findlang();
    //     // findlang("auxFile.txt", sFile, destinyFile, k, alpha);
    // }

    // //print the segments and the language
    // for(int i = 0; i < segmentsLang.size(); i++){
    //     cout<<"segment: "<<segmentsLang[i].begin()->first<<endl;
    //     cout<<"language: "<<segmentsLang[i].begin()->second<<endl;
    // }

    //build the models
    locatelang locatelang(k, alpha,destinyFile);
    for(int i = 3; i < argc - 1; i++)
    {
        sourceFile = argv[i];
        cout << "--------------------------" << endl;    
        cout << "Choosen text file for model: " << sourceFile << endl;
        locatelang.buildModelLocate(sourceFile);
        cout << "--------------------------" << endl;
    }
    //find the language
    locatelang.locate();

    return 0;
}

