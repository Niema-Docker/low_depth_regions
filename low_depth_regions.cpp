// Given a samtools depth file, output all regions below the threshold
// Compile: g++ -O3 -o low_depth_regions low_depth_regions.cpp

// constants
#define DEFAULT_MIN_DEPTH 10

// includes
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// main function
int main(int argc, char* argv[]) {
    // parse user args
    int MIN_DEPTH;
    if(argc == 3) {
        MIN_DEPTH = DEFAULT_MIN_DEPTH;
    } else if(argc == 4) {
        MIN_DEPTH = atoi(argv[3]);
        if(MIN_DEPTH == 0) {
            cerr << "ERROR: Invalid minimum depth threshold: " << argv[3] << endl; exit(1);
        }
    } else {
        cerr << "USAGE: " << argv[0] << " <input_depth_file> <output_file> [min_depth=10]" << endl; exit(1);
    }

    // open input and output files
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    // create temporary holding variables
    string line;
    string tmp;
    string chrom;
    int pos;
    int depth;

    // compute low-depth regions
    bool mask = false;
    while(getline(infile,line)) {
        // parse next line
        istringstream ss(line);
        getline(ss, chrom, '\t');
        getline(ss, tmp, '\t'); pos = stoi(tmp);
        getline(ss, tmp, '\n'); depth = stoi(tmp);

        // check if low-depth or not
        if(depth < MIN_DEPTH) {
            if(!mask) {
                mask = true; outfile << chrom << '\t' << pos << '\t';
            }
        } else {
            if(mask) {
                mask = false; outfile << (pos-1) << endl;
            }
        }
    }

    // close trailing mask region
    if(mask) {
        mask = false; outfile << pos << endl;
    }
    return 0;
}
