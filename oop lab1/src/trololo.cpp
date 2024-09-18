#include <iostream>
#include <string>
#include <unordered_set>
#include "../include/trololo.h"


std::string trololo(const std::string comment){
    std::string result = std::string();
    std::unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    for (char c : comment){
        if (vowels.find(c) == vowels.end()){
            result += c;
        }  
    }
    return result;
}

