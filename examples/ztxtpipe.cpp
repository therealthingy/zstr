#include "zstr.hpp"
#include <iostream>
#include <string>

#ifdef _WIN32
#    include <fcntl.h>    // for _O_BINARY
#    include <io.h>       // for _setmode
#endif

int main() {
#ifdef _WIN32
    // Don't touch line endings
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif
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
