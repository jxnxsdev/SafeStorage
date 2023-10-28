#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace SafeStorage::Parser {
    void findPath();
    void validateStorage();
    void setEntry(std::string key, std::string value);
    std::string getEntry(std::string key);
    void removeEntry(std::string key);
    void clearStorage();
    std::vector<std::string> getAllKeys();
}