#pragma once

#include <iostream>
#include <print>
#include <string>

inline void burn_string(std::string& s) {
    std::fill_n(const_cast<volatile char*>(s.data()), s.size(), 0);
    s.clear();
}

inline void clear_line() {
    std::print("\033[1A\033[2K\r");
    std::fflush(stdout);
}

inline void safeprint(const std::string& str) {
    std::string _;
    std::print("{}", str);
    std::getline(std::cin, _);
    clear_line();
}
