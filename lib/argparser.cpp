#include "argparser.h"
#include <iostream>
#include <string>
#include <vector>

void ArgParser::PrintArgv() const {
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
}
