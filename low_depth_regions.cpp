// Given a samtools depth file, output all regions below the threshold
// Version: 1.0.0
// Compile: g++ -O3 -o low_depth_regions low_depth_regions.cpp

// constants
#define DEFAULT_MIN_DEPTH 10

// includes
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// main function
int main(int argc, char* argv[]) {
    // parse user args
    unsigned long MIN_DEPTH;
    if(argc == 3) {
        MIN_DEPTH = DEFAULT_MIN_DEPTH;
    } else if(argc == 4) {
        MIN_DEPTH = stoul(string(argv[3]));
    } else {
        cerr << "USAGE: " << argv[0] << " <input_depth_file> <output_file> [min_depth=" << DEFAULT_MIN_DEPTH << ']' << endl; exit(1);
    }

    // open input and output files
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    // create temporary holding variables
    string line;
    string tmp;
    string chrom;
    unsigned long pos;
    unsigned long depth;

    // compute low-depth regions
    bool mask = false;
    while(getline(infile,line)) {
        // parse next line
        istringstream ss(line);
        getline(ss, chrom, '\t');
        getline(ss, tmp, '\t'); pos = stoul(tmp);
        getline(ss, tmp, '\n'); depth = stoul(tmp);

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
