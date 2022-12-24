#include <iostream>
#include "Controller.hpp"

int main(){

    std::cout << "starting wii u controller interface\n";

    //device /dev/input/event4, name "Nintendo Wii Remote Pro Controller"

    Controller::WiiUProController::findDevicePath("Nintendo");





    //ends program
    return 0;
}