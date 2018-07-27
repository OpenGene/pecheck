# pecheck
A tool to check paired-end FASTQ data integrity

# usage
Just specify the read1 file by `-i` and the read2 file by `-I`. The input file can be gzipped (i.e. R1.fq.gz).
```
pecheck -i R1.fq -I R2.fq
```
A JSON report will be then generated. If the check is passed, the JSON result will be like:
```json
{
	"result":"passed",
	"message":"",
	"read1_num":1000,
	"read2_num":1000,
	"read1_bases":108040,
	"read2_bases":109141
}
```
And if it's failed, the JSON result will be like:
```json
{
	"result":"failed",
	"message":"Numbers of read1 and read2 are different",
	"read1_num":999,
	"read2_num":1000,
	"read1_bases":107923,
	"read2_bases":109141
}
```
The file name of the JSON report is `report.json` by default, and it can be specified by `-j`. The JSON result is also printed on the terminal (STDOUT).

# get pecheck
## download binary 
This binary is only for Linux systems: http://opengene.org/pecheck/pecheck
```shell
# this binary was compiled on CentOS, and tested on CentOS/Ubuntu
wget http://opengene.org/pecheck/pecheck
chmod a+x ./pecheck
```
## or compile from source
```shell
# get source (you can also use browser to download from master or releases)
git clone https://github.com/OpenGene/pecheck.git

# build
cd pecheck
make

# Install
sudo make install
```
