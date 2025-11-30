#include "argparser.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

void ArgParser::AddFlag(const char* short_name, const char* long_name, bool* include) {
    Flag f;
    if (short_name != nullptr) f.short_name = short_name;
    if (long_name != nullptr) f.long_name = long_name;
    f.include = include;
    required_flags.push_back(f);
}

void ArgParser::AddArgument(const char* short_name, const char* long_name, std::vector<std::string>* free_args, int args_count) {
    NamedArg arg;
    if (short_name != nullptr) arg.short_name = short_name;
    if (long_name != nullptr) arg.long_name = long_name;
    arg.free_args = free_args;
    arg.single_arg = nullptr;
    arg.args_count = args_count;
    required_named_args.push_back(arg);
}

// перегрузка для single arg
void ArgParser::AddArgument(const char* short_name, const char* long_name, std::string* single_arg) {
    NamedArg arg;
    if (short_name != nullptr) arg.short_name = short_name;
    if (long_name != nullptr) arg.long_name = long_name;
    arg.single_arg = single_arg;
    arg.args_count = 1;
    required_named_args.push_back(arg);
}

bool ArgParser::WriteShortFlag(const std::string& short_name) {
    for (auto& f : required_flags) {
        if (f.short_name == short_name) {
            if (f.include != nullptr) *f.include = true;
            included_flags.push_back(&f);
            return true;
        }
    }
    return false;
}

bool ArgParser::FindShortArg(const std::string& short_name, NamedArg*& out) {
    for (auto& na : required_named_args) {
        if (na.short_name == short_name) {
            out = &na;
            return true;
        }
    }
    return false;
}

bool IsSpecArg(const std::string& arg) {
    return arg[0] == '-';
}

bool ArgParser::WriteLongFlag(const std::string& long_name) {
    for (auto& f : required_flags) {
        if (f.long_name == long_name) {
            if (f.include != nullptr) *f.include = true;
            included_flags.push_back(&f);
            return true;
        }
    }
    return false;
}

bool ArgParser::WriteLongArg(const std::string& long_name, const std::string& value) {
    for (auto& na : required_named_args) {
        if (na.long_name == long_name) {
            if (na.free_args == nullptr) {
                na.free_args = new std::vector<std::string>();
            }
            na.free_args->push_back(value);

            if (na.single_arg != nullptr) {
                *(na.single_arg) = value;
            }
            
            parsed_named_args.push_back(&na);
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
        if (!IsSpecArg(arg)) {
            positional_args.push_back(arg);
            continue;
        }

        if (arg[1] != '-') {
            // short flag / short named arg
            if (!WriteShortFlag(arg)) {
                NamedArg* found_arg = nullptr;
                if (!FindShortArg(arg, found_arg)) {
                    throw std::runtime_error("Unspecified flag / argument provided");
                }
                // std::cout << found_arg->long_name << std::endl;
                
                // if (found_arg->single_arg != nullptr) {
                //     if (i + 1 < argc && !IsSpecArg(argv[i + 1])) {
                //         *(found_arg->single_arg) = argv[i + 1];
                //         parsed_named_args.push_back(found_arg);
                //         continue;
                //     } else {
                //         throw std::runtime_error("Not enough argument values provided\nTarget argument: \"" + found_arg->short_name + "\"");
                //     }
                // }

                if (found_arg->free_args == nullptr) {
                    found_arg->free_args = new std::vector<std::string>();
                }

                int counter = 0;
                while (i + 1 < argc && !IsSpecArg(argv[i + 1])) {
                    if (found_arg->args_count > 0 && counter >= found_arg->args_count) break;

                    found_arg->free_args->push_back(argv[i + 1]);
                    
                    counter++;
                    i++;
                }

                if (found_arg->args_count > 0 && counter != found_arg->args_count) {
                    throw std::runtime_error("Not enough argument values provided\nTarget argument: \"" + found_arg->short_name + "\"");
                }
                
                if (found_arg->single_arg != nullptr) {
                    // *(found_arg->single_arg) = (*(found_arg->free_args))[0];
                    *(found_arg->single_arg) = argv[i];
                }

                parsed_named_args.push_back(found_arg);
            }
            continue;
        }

        size_t pos = arg.find('=');
        if (pos == std::string::npos) {
            // long flag
            if (!WriteLongFlag(arg)) {
                throw std::runtime_error("Unknown flag provided");
            }
        } else {
            // long named arg
            if (!WriteLongArg(arg.substr(0, pos), arg.substr(pos + 1))) {
                throw std::runtime_error("Unknown argument provided");
            }
        }
    }
}
