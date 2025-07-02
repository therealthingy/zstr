#include "zstr.hpp"
#include <iostream>
#include <string>

int main() {
    //
    // Create zstr::istream feeding off std::cin.
    //
    zstr::istream is(std::cin);
    //
    // Main loop
    //
    std::string s;
    while (getline(is, s)) {
        std::cout << s << std::endl;
    }
}
