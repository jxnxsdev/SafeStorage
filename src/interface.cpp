#include "interface.hpp"
#include "encrypt.hpp"
#include "storageParser.hpp"

namespace SafeStorage::Interface {

    void insert(std::string mod_id, std::string key, std::string value) {
        std::string encryptedValue = Encryption::process(value, mod_id);
        std::string storageKey = mod_id + "_" + key;
        Parser::setEntry(storageKey, encryptedValue);
    }

    void remove(std::string mod_id, std::string key) {
        std::string storageKey = mod_id + "_" + key;
        Parser::removeEntry(storageKey);
    }

    std::string get(std::string mod_id, std::string key) {
        std::string storageKey = mod_id + "_" + key;
        std::string encryptedValue = Parser::getEntry(storageKey);
        std::string decryptedValue = Encryption::process(encryptedValue, mod_id);
        return decryptedValue;
    }
}