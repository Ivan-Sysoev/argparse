#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <lib/argparser.h>

int main(int argc, char** argv) {
    ArgParser parser;

    // std::vector<std::string> output;
    // std::vector<std::string> mode;

    // bool into;
    // bool power;

    std::string mode = "nigga";
    
    parser.AddArgument("-o", "--output", nullptr, 3);
    parser.AddArgument("-m", "--mode", &mode);
    // parser.AddArgument("-m", nullptr, &mode);

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

    // std::cout << "Flags: \n";
    // for (const auto& flag : parser.included_flags) {
    //     if (!flag->short_name.empty()) std::cout << flag->short_name << '\n';
    //     if (!flag->long_name.empty()) std::cout << flag->long_name << '\n';
    // }
    // std::cout << "\n";

    // for (const auto& out : output) std::cout << out << "\n\n";
    
    // std::cout << "mode: ";
    // if (mode.size() > 0) std::cout << mode[0] << std::endl;

    // std::cout << "Named args:\n";
    // for (const auto& na : parser.parsed_named_args) {
    //     if (!na->short_name.empty()) std::cout << na->short_name << '\n';
    //     if (!na->long_name.empty()) std::cout << na->long_name << '\n';

    //     for (const auto& value : *(na->free_args)) {
    //         std::cout << value << ' ';
    //     }
    //     std::cout << "\n\n";
    // }

    std::cout << "Mode = \"" << mode << "\"\n";

    // std::cout << "Positional args:\n";
    // for (const auto& name : parser.positional_args) std::cout << name << ' ';

    return 0;
}