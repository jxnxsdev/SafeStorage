#include "storageParser.hpp"
#include "main.hpp"
#include "scotland2/shared/modloader.h"

namespace SafeStorage::Parser {
    std::string_view filepath = "";

    void findPath() {
        std::string destPath = modloader_get_files_dir();
        filepath = destPath + "/SafeStorage_DO_NOT_SHARE_THIS_OR_THE_CONTENTS_OF_THIS_FILE.dat";
    }

    void validateStorage() {
        if (access(filepath.data(), F_OK) != -1) {
            getLogger().info("Storage file exists");
        }else {
            std::ofstream file(filepath.data());
            file << "--- SafeStorage ---\n";
            file.close();
        }
    }

    void clearStorage() {
        std::ofstream file(filepath.data());
        if (!file.is_open()) {
            return;
        }

        file << "--- SafeStorage ---\n";
        file.close();
    }

    void setEntry(std::string key, std::string value) {
        removeEntry(key);

        std::ofstream file(filepath.data(), std::ios_base::app);
        if (!file.is_open()) {
            return;
        }

        // this code relies on the fact that there is a new line at the end of the file
        // let's hope that's the case and the user (or other mods) didn't fuck around with it
        // TODO: Add validation

        file << key << ":" << value << "\n";

        file.close();
    }


    std::string getEntry(std::string key) {
        std::ifstream file(filepath.data(), std::ios_base::binary);
        if (!file.is_open()) {
            return "";
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        std::string entry = "";
        std::string line;
        std::istringstream fileStream(fileContents);
        while (std::getline(fileStream, line)) {
            if (line.find(key) != std::string::npos) {
                entry = line.substr(line.find(":") + 1);
                break;
            }
        }

        return entry;
    }


    void removeEntry(std::string key) {
        std::ifstream file(filepath.data(), std::ios_base::binary);
        if (!file.is_open()) {
            return;
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        std::string line;
        std::istringstream fileStream(fileContents);
        while (std::getline(fileStream, line)) {
            if (line.find(key) != std::string::npos) {
                fileContents.erase(fileContents.find(line), line.length() + 1);
                break;
            }
        }

        std::ofstream file2(filepath.data());
        file2 << fileContents;
        file2.close();
    }

    std::vector<std::string> getAllKeys() {
        std::vector<std::string> keys;

        std::ifstream file(filepath.data(), std::ios_base::binary);
        if (!file.is_open()) {
            return keys;
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        std::string line;
        std::istringstream fileStream(fileContents);
        while (std::getline(fileStream, line)) {
            if (line.find(":") != std::string::npos) {
                keys.push_back(line.substr(0, line.find(":")));
            }
        }

        return keys;
    }
}
