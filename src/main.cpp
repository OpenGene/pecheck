#include <stdio.h>
#include <time.h>
#include "cmdline.h"
#include "common.h"
#include "options.h"
#include "unittest.h"
#include <sstream>
#include "pecheck.h"
#include "util.h"

string command;

int main(int argc, char* argv[]){
    // display version info if no argument is given
    if(argc == 1) {
        cout << "A tool to check paired-end FASTQ data integrity" << endl << "version " << VERSION_NUM << endl;
    }
    if (argc == 2 && strcmp(argv[1], "test")==0){
        UnitTest tester;
        tester.run();
        return 0;
    }
    cmdline::parser cmd;
    // input/output
    cmd.add<string>("in1", 'i', "read1 file name", true, "");
    cmd.add<string>("in2", 'I', "read2 file name", true, "");
    cmd.add<string>("json", 'j', "json report file name", true, "pecheck.json");

    cmd.parse_check(argc, argv);
    
    stringstream ss;
    for(int i=0;i<argc;i++){
        ss << argv[i] << " ";
    }
    command = ss.str();

    time_t t1 = time(NULL);

    Options opt;

    opt.in1 = cmd.get<string>("in1");
    opt.in2 = cmd.get<string>("in2");
    opt.jsonFile = cmd.get<string>("json");

    opt.validate();

    PECheck pecheck(&opt);
    pecheck.run();

    time_t t2 = time(NULL);

    cerr << endl << "JSON report: " << opt.jsonFile << endl;
    cerr << endl << command << endl;
    cerr << "pecheck v" << VERSION_NUM << ", time used: " << (t2)-t1 << " seconds" << endl;

    return 0;
}