// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>



// Converts vector of strings to vector char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& command, char delimiter = ' '); 

#endif