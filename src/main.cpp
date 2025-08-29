#include "GameCore/Controller.h"
#include <iostream>
#include <exception>
#include "Utils/ExitCodes.h"

int main() {
    try {
        Controller controller;
        controller.run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return RUNTIME_ERROR; 
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
        return GENERAL_ERROR;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return UNKNOWN_ERROR;
    }

    return SUCCESS;
}
