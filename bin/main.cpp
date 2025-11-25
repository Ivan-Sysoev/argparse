#include <iostream>
#include <lib/argparser.h>

int main(int argc, char** argv) {
    ArgParser parser;

    bool output = false;
    parser.AddFlag("-o", "--output", output); 

    return 0;
}