#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <lib/argparser.h>

int main(int argc, char** argv) {
    ArgParser parser;

    bool output = false;
    std::vector<std::string> files;

    parser.AddFlag("-o", "--output", output); 
    parser.AddArgument("-f", "--file", files);

    try {
        parser.Parse(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << "Error occured: " << err.what() << std::endl;
        return 1;
    }

    std::cout << (output ? "files to output" : "files to input") << '\n';
    for (const auto& filename : files) std::cout << filename << '\n';

    return 0;
}