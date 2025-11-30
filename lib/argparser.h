#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>
#include <vector>

class ArgParser {
private:
    struct Flag {
        std::string short_name;
        std::string long_name;
        bool* include;
    };

    struct NamedArg {
        std::string short_name;
        std::string long_name;
        std::vector<std::string>* free_args;
        std::string* single_arg;
        int args_count;
    };

    std::vector<Flag> required_flags;
    std::vector<NamedArg> required_named_args;

    bool WriteShortFlag(const std::string& short_name);
    bool FindShortArg(const std::string& short_name, NamedArg*& out);
    
    bool WriteLongFlag(const std::string& long_name);
    bool WriteLongArg(const std::string& long_name, const std::string& value);

public:
    std::vector<Flag*> included_flags;
    std::vector<NamedArg*> parsed_named_args;
    std::vector<std::string> positional_args;
    
    ~ArgParser() {
        for (NamedArg* na : parsed_named_args) {
            delete na->free_args;
        }
    }

    void AddFlag(const char* short_name, const char* long_name, bool* include);
    void AddArgument(const char* short_name, const char* long_name, std::vector<std::string>* free_args, int args_count=-1);
    void AddArgument(const char* short_name, const char* long_name, std::string* single_arg);

    void Parse(int argc, char** argv);
};

#endif