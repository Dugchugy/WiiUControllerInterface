#include <iostream>
#include "Device.hpp"
#include<unistd.h>

using namespace Controller;

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
            controllerPath = evDevice::findDevicePath("Nintendo");

            //stops saerching
            searching = false;
        }catch(DeviceNotFoundError){

            //continues searching
            searching = true;

            //informs the user the controller wasn't found and it will try to find it again in 3 seconds
            std::cout << "failed to find device attempting again in 3 seconds\n";

            //waits 3 seconds
            sleep(3);

        }
    }

    //prints path the controller was found at
    std::cout << "found at path: " << controllerPath << "\n";

    //creates a new controller
    evDevice controller(controllerPath);

    


    //ends program
    return 0;
}