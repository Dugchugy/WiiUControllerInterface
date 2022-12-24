#include <iostream>
#include "Controller.hpp"

int main(){

    //prints a message to show that the program is starting
    std::cout << "starting wii u controller interface\n";

    //device /dev/input/event4, name "Nintendo Wii Remote Pro Controller"

    //creates a bool to control how long it loops for
    bool searching = true;

    std::string controllerPath = "";

    //loops for as long as its searching for
    while(searching){
        try{
                
            //attempts to find the path of the input device
            controllerPath = Controller::WiiUProController::findDevicePath("Nintendo");

            //stops saerching
            searching = false;
        }catch(DeviceNotFoundError){

            //continues searching
            searching = true;

        }
    }

    std::cout << "found at path: " << controllerPath << "\n";


    //ends program
    return 0;
}