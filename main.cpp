#include <iostream>
#include "pt-api.hpp"
#include "pt-errors.hpp"

int main(int argc, char* argv[]) {
    try {
        PtAPI ptAPI("10.30.137.11");
        std::cout << ptAPI.get("status") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown general exception!" << std::endl;
        return 1;
    }
    return 0;
}
