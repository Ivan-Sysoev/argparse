#pragma once
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
    };
    
    std::vector<Flag> flags;
    std::vector<NamedArg> named_args;
    
public:
    std::vector<std::string> positional_args;

    void AddFlag(const char* short_name, const char* long_name, bool& include);
    void AddArgument(const char* short_name, const char* long_name, std::vector<std::string>& free_args);

    void Parse(int argc, char** argv);

    bool WriteFlag(const std::string& short_name);
    bool FindShortArg(const std::string& short_name, std::vector<std::string>*& free_args);

    bool WriteLongFlag(const std::string& long_name);
    bool WriteLongArg(const std::string& long_name, const std::string& value);
};
