#include "options.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string.h>

Options::Options(){
    in1 = "";
    in2 = "";
    jsonFile = "";
}

bool Options::isFastqFile(string filename) {
    if(ends_with(filename, ".fq") || ends_with(filename, ".fastq") || ends_with(filename, ".fq.gz")|| ends_with(filename, ".fastq.gz"))
        return true;

    return false;
}

bool Options::validate() {
    if(in1.empty()) {
        error_exit("read1 input should be specified by --in1");
    } else {
        check_file_valid(in1);
    }

    if(in2.empty()) {
        error_exit("read2 input should be specified by --in2");
    } else {
        check_file_valid(in2);
    }

    return true;
}
