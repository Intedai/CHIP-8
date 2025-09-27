#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <string_view>
#include <unordered_map>
#include <cstddef>
#include <cctype>
#include <algorithm>
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>
#include <toml.hpp>
#include "keyboard.hpp"

class ConfigLoader {
    private:
        static size_t getIndex(std::string_view key);
    public:
        static void load(std::string_view path, Keyboard& keyboard);
};

#endif