#include <iostream>
#include "Controller.hpp"

int main(){

    //prints a message to show that the program is starting
    std::cout << "starting wii u controller interface\n";

    //device /dev/input/event4, name "Nintendo Wii Remote Pro Controller"

    //attempts to find the path of the input device
    std::string controllerPath = Controller::WiiUProController::findDevicePath("Nintendo");





    //ends program
    return 0;
}