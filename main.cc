#include <iostream>
#include "MPRNG.h"
#include "config.h"

using namespace std;

struct E {};

MPRNG rng;

void uMain::main() {
    
    //get arguments and parameters
    int seed = getpid();
    char* filename;
    struct ConfigParms parms;
    
    try {
        switch(argc) {
            case 3:
                seed = atoi(argv[2]);
                if(seed <= 0) {
                    throw E();
                }
            case 2:
                filename = argv[1];
            case 1:
                filename = "soda.config";
                break;
            default:
                throw E();
                
        } //switch  
    } catch(...) {
        cerr << "Usage: ./soda  config-file  Seed (> 0)" << endl;
        return;
    } //try
    
    processConfigFile(filename, parms);

    rng.seed(seed);
}