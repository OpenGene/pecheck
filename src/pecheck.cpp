#include "pecheck.h"
#include "fastqreader.h"
#include "util.h"
#include <stdio.h>

PECheck::PECheck(Options* opt){
    mOptions = opt;
    mPassed = true;
}

void PECheck::run() {
    FastqReader reader1(mOptions->in1);
    FastqReader reader2(mOptions->in2);

    bool r1Finished = false;
    bool r2Finished = false;
    while(true) {
        Read* r1 = NULL;
        Read* r2 = NULL;
        if(!r1Finished)
            r1 = reader1.read();
        if(!r2Finished)
            r2 = reader2.read();
        if(!r1 && !r2)
            break;
        int namePos1=0;
        int namePos2=0;
        if(r1) {
            mRead1Num++;
            mRead1Bases += r1->length();
            if(r1->mSeq.mStr.length() != r1->mQuality.length()) {
                mFailedMessage = "Read1 is broken (sequence and quality have different length): " + r1->toString(false);
                mPassed = false;
                break;
            }
            for(int i=0; i<r1->mName.length(); i++) {
                if(r1->mName[i] == ' ') {
                    namePos1 = i;
                    break;
                }
            }
        } else
            r1Finished = true;

        if(r2) {
            mRead2Num++;
            mRead2Bases += r2->length();
            if(r2->mSeq.mStr.length() != r2->mQuality.length()) {
                mFailedMessage = "Read2 is broken (sequence and quality have different length): " + r2->toString(false);
                mPassed = false;
                break;
            }
            for(int i=0; i<r2->mName.length(); i++) {
                if(r2->mName[i] == ' ') {
                    namePos2 = i;
                    break;
                }
            }
        } else
            r2Finished = true;

        if(r1 && r2) {
            bool nameConsistent = true;
            if(namePos1 == namePos2){
                for(int i=0; i<namePos1; i++) {
                    if(r1->mName[i] != r2->mName[i]) {
                        nameConsistent = false;
                        break;
                    }
                }
            }
            if(!nameConsistent || (namePos1 != namePos2)) {
                mFailedMessage = "Read1 and read2 have different names: " + r1->mName + ", " + r2->mName;
                mPassed = false;
                break;
            }
        }

        if(r1)
            delete r1;
        if(r2)
            delete r2;
    }
    if(mRead1Num != mRead2Num) {
        mFailedMessage = "Numbers of read1 and read2 are different";
        mPassed = false;
    }

    report();
}

void PECheck::report() {
    string json = "{\n";
    if(mPassed)
        json += "\t\"result\":\"passed\",\n";
    else
        json += "\t\"result\":\"failed\",\n";

    json += "\t\"message\":\"" + mFailedMessage + "\",\n";

    json += "\t\"read1_num\":" + to_string(mRead1Num) + ",\n";
    json += "\t\"read2_num\":" + to_string(mRead2Num) + ",\n";
    json += "\t\"read1_bases\":" + to_string(mRead1Bases) + ",\n";
    json += "\t\"read2_bases\":" + to_string(mRead2Bases) + "\n";

    json += "}\n";

    if(!mOptions->jsonFile.empty()) {
        ofstream out(mOptions->jsonFile);
        out.write(json.c_str(), json.length());
        out.flush();
        out.close();
    }

    cout << json;
}