#include "utility.h"

#include <sstream>



std::vector<char *> castArgs(const std::vector<std::string> &cmd) {
    std::vector<char*> argv; 

    for(const auto& arg : cmd) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }

    argv.push_back(nullptr); 
    return argv; 
}

std::vector<std::string> cmd2vec(const std::string &command, char delimiter) {
    std::vector<std::string> result; 
    std::istringstream stream(command); 
    std::string token; 

    while(std::getline(stream, token, delimiter)) {
        if(!token.empty()) {
            result.push_back(token); 
        }
    }

    return result; 
}