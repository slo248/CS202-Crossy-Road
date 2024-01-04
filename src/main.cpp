#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Application.hpp"

int main() {
    srand(time(NULL));
    try {
        Application app;
        app.run();
    } catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
