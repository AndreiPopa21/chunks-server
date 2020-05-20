#include "utils.h"

using namespace std;

#define ARGC 2

int main (int argc, char* argv[]) {

    if (argc != ARGC) {
        cout << "Wrong number of arguments (" << argc << ") should be "<< ARGC << endl;
        exit(0); 
    }

    return 0;
}