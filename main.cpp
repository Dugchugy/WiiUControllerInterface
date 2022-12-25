#include <iostream>
#include "Device.hpp"
#include "Controller.hpp"
#include<unistd.h>

using namespace Controller;

int main(){

    //prints a message to show that the program is starting
    std::cout << "starting wii u controller interface\n";

    //device /dev/input/event4, name "Nintendo Wii Remote Pro Controller"

    //creates a bool to control how long it loops for
    bool searching = true;

    //loops for as long as its searching for
    while(searching){
        try{
                
            //apttempts to create a new controller
            Controller WiiUPro;

            //updates the controllers state every second
            while(true){
                //updates the state
                WiiUPro.UpdateState();

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

        }
    }

    return 0;
}