#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace SafeStorage::Interface {
    void insert(std::string mod_id, std::string key, std::string value);
    void remove(std::string mod_id, std::string key);
    std::string get(std::string mod_id, std::string key);
}