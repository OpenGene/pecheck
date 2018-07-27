#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Options{
public:
    Options();
    bool validate();

    static bool isFastqFile(string filename);

public:
    // IO
    string in1;
    string in2;
    string jsonFile;

};

#endif