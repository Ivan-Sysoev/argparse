#include "argparser.h"
#include <iostream>
#include <string>
#include <vector>

void ArgParser::AddFlag(const std::string& short_name, const std::string& long_name, bool& include) {
    flags.push_back({short_name, long_name, include});
}

void ArgParser::AddArgument(const std::string& short_name, const std::string& long_name, std::vector<std::string>& free_args) {
    named_args.push_back({short_name, long_name, free_args});
}

bool ArgParser::WriteFlag(const std::string& short_name) {
    for (auto& f : flags) {
        if (f.short_name == short_name) {
            f.include = true;
            return true;
        }
    }
    return false;
}

bool ArgParser::FindShortArg(const std::string& short_name, std::vector<std::string>& free_args) {
    for (auto& na : named_args) {
        if (na.short_name == short_name) {
            free_args = na.free_args;
            return true;
        }
    }
    return false;
}

bool IsSpecArg(char* arg) {
    return arg[0] == '-';
}

void ArgParser::Parse(int argc, char** argv) {
    if (argc < 2) {
        throw std::runtime_error("Provide arguments");
    }
    
    for (int i = 1; i < argc; i++) {
        // positional arg
        if (IsSpecArg(argv[i])) {
            positional_args.push_back(argv[i]);
            continue;
        }

        if (argv[i][1] != '-') {
            // short flag / short named arg
            if (!WriteFlag(argv[i])) {
                std::vector<std::string> free_args;
                if (!FindShortArg(argv[i], free_args)) {
                    throw std::runtime_error("Unspecified flag / argument provided");
                }
                
                while (i + 1 < argc && !IsSpecArg(argv[i + 1])) {
                    free_args.push_back(argv[i + 1]);
                }
            }
            continue;
        }
    }
}
