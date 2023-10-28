#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "modloader/shared/modloader.hpp"

namespace SafeStorage::Interface {
    void insert(ModInfo modInfo, std::string key, std::string value);
    void remove(ModInfo modInfo, std::string key);
    std::string get(ModInfo modInfo, std::string key);
}