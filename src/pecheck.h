#ifndef REPAQ_H
#define REPAQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "options.h"

using namespace std;

class PECheck{
public:
    PECheck(Options* opt);
    void run();

private:
    void report();

private:
    Options* mOptions;
    bool mPassed;
    long mRead1Num;
    long mRead2Num;
    long mRead1Bases;
    long mRead2Bases;
    string mFailedMessage;
};

#endif