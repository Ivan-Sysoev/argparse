#include "argparser.h"
#include <string>
#include <vector>
#include <stdexcept>

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

bool IsSpecArg(const std::string& arg) {
    return arg[0] == '-';
}

bool ArgParser::WriteLongFlag(const std::string& long_name) {
    for (auto& f : flags) {
        if (f.long_name == long_name) {
            f.include = true;
            return true;
        }
    }
    return false;
}

bool ArgParser::WriteLongArg(const std::string& long_name, const std::string& value) {
    for (auto& na : named_args) {
        if (na.long_name == long_name) {
            na.free_args.push_back(value);
            return true;
        }
    }
    return false;
}


void ArgParser::Parse(int argc, char** argv) {
    if (argc < 2) {
        throw std::runtime_error("Provide arguments");
    }
    
    for (int i = 1; i < argc; i++) {
        const std::string& arg = argv[i];

        // positional arg
        if (IsSpecArg(arg)) {
            positional_args.push_back(arg);
            continue;
        }

        if (arg[1] != '-') {
            // short flag / short named arg
            if (!WriteFlag(arg)) {
                std::vector<std::string> free_args;
                if (!FindShortArg(arg, free_args)) {
                    throw std::runtime_error("Unspecified flag / argument provided");
                }
                
                while (i + 1 < argc && !IsSpecArg(argv[i + 1])) {
                    free_args.push_back(argv[i + 1]);
                }
            }
            continue;
        }

        size_t pos = arg.find('=');
        if (pos == std::string::npos) {
            // long flag
            if (!WriteLongFlag(arg.substr(2))) {
                throw std::runtime_error("Unknown flag provided");
            }
        } else {
            // long named arg
            if (!WriteLongArg(arg.substr(2, pos-2), arg.substr(pos + 1))) {
                throw std::runtime_error("Unknown argument provided");
            }
        }
    }
}
