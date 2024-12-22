#include <iostream>
#include "pt-api.hpp"
#include "pt-errors.hpp"

int main(int argc, char* argv[]) {
    try {
        PtAPI ptAPI("192.168.42.143");
        std::cout << ptAPI.get("/status") << std::endl;

        // Change turnout to reverse position
        nlohmann::json turnoutState = ptAPI.get("/blockState/125")["blockState"];
        std::cout << turnoutState << std::endl;
        std::string newPosition = (turnoutState["position"] == "+" ? "-" : "+");
        std::cout << ptAPI.put("/blockState/125", {
            {"blockState", {{"position", newPosition}}}
        }) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown general exception!" << std::endl;
        return 1;
    }
    return 0;
}
