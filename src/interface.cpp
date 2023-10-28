#include "interface.hpp"
#include "encrypt.hpp"
#include "storageParser.hpp"

namespace SafeStorage::Interface {

    void insert(ModInfo modInfo, std::string key, std::string value) {
        std::string encryptedValue = Encryption::process(value, modInfo.id);
        std::string storageKey = modInfo.id + "_" + key;
        Parser::setEntry(storageKey, encryptedValue);
    }

    void remove(ModInfo modInfo, std::string key) {
        std::string storageKey = modInfo.id + "_" + key;
        Parser::removeEntry(storageKey);
    }

    std::string get(ModInfo modInfo, std::string key) {
        std::string storageKey = modInfo.id + "_" + key;
        std::string encryptedValue = Parser::getEntry(storageKey);
        std::string decryptedValue = Encryption::process(encryptedValue, modInfo.id);
        return decryptedValue;
    }
}