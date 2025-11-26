#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <lib/argparser.h>

int main(int argc, char** argv) {
    ArgParser parser;

    std::vector<std::string> output;
    std::vector<std::string> mode;

    bool into;
    bool power;

    parser.AddArgument("-o", "--output", output);    
    parser.AddArgument(nullptr, "--mode", mode);

    parser.AddFlag(nullptr, "--into", into);
    parser.AddFlag("-p", nullptr, power);

    try {
        parser.Parse(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << "Error occured: " << err.what() << std::endl;
        return 1;
    }

    if (into) std::cout << "into!" << "\n\n";
    if (power) std::cout << "power!" << "\n\n";

    for (const auto& out : output) std::cout << out << "\n\n";
    if (mode.size() > 0) std::cout << mode[0] << std::endl;

    for (const auto& name : parser.positional_args) std::cout << name << ' ';

    return 0;
}