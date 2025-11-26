#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <lib/argparser.h>

int main(int argc, char** argv) {
    ArgParser parser;

    std::vector<std::string> output;
    std::vector<std::string> mode;

    // bool into;
    // bool power;

    parser.AddArgument("-o", "--output", &output, 3);
    parser.AddArgument(nullptr, "--mode", &mode);

    parser.AddFlag(nullptr, "--into", nullptr);
    parser.AddFlag("-p", nullptr, nullptr);

    try {
        parser.Parse(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << "Error occured: " << err.what() << std::endl;
        return 1;
    }

    // if (into) std::cout << "into!" << "\n\n";
    // if (power) std::cout << "power!" << "\n\n";

    std::cout << "Flags: \n";
    for (const auto& flag : parser.included_flags) {
        if (flag.short_name.length() != 0) std::cout << flag.short_name << '\n';
        if (flag.long_name.length() != 0) std::cout << flag.long_name << '\n';
    }
    std::cout << "\n";

    for (const auto& out : output) std::cout << out << "\n\n";
    
    std::cout << "mode: ";
    if (mode.size() > 0) std::cout << mode[0] << std::endl;

    for (const auto& name : parser.positional_args) std::cout << name << ' ';

    return 0;
}