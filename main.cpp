#include <iostream>
#include "Device.hpp"
#include "Controller.hpp"
#include<unistd.h>

using namespace Controllers;

int main(){

    //prints a message to show that the program is starting
    std::cout << "starting wii u controller interface\n";

    //device /dev/input/event4, name "Nintendo Wii Remote Pro Controller"

    //creates a bool to control how long it loops for
    bool searching = true;

    //loops for as long as its searching for
    while(searching){
        try{
            std::cout << "starts loop\n";    
            //apttempts to create a new controller
            Controller WiiUPro;

            std::cout << "created object\n";

            //updates the controllers state every second
            while(true){
                std::cout << "starting update\n";
                //updates the state
                WiiUPro.UpdateState();

                std::cout << "current state of A: " << WiiUPro.QueryKey("A") << "\n";

                //waits one second
                sleep(1);
            }

            //stops saerching
            searching = false;
        }catch(DeviceNotFoundError){

            //continues searching
            searching = true;

            //informs the user the controller wasn't found and it will try to find it again in 3 seconds
            std::cout << "failed to find device attempting again in 3 seconds\n";

            //waits 3 seconds
            sleep(3);

        }catch(DeviceAccessError){

            //continues searching
            searching = true;

            //informs the user the controller wasn't found and it will try to find it again in 3 seconds
            std::cout << "Device access error. something went wrong, trying again in 3 seconds\n";

            //waits 3 seconds
            sleep(3);
        }
    }

    return 0;
}