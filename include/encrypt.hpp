#include <iostream>
#include <string>

namespace Encryption {
    std::string process(std::string &input, std::string &key) {
        std::string in = input;
        int keyIndex = 0;

        for (char &c : in) {
            c ^= key[keyIndex];
            keyIndex = (keyIndex + 1) % key.length();
        }

        return in;
    }
}