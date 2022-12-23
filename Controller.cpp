#include "Controller.hpp"

#include<libevdev-1.0/libevdev/libevdev.h>

namespace Controller{

    WiiUProController::WiiUProController(){

    }

    WiiUProController::~WiiUProController(){
        //deletes the device
        delete device;
    }

    WiiUProController::WiiUProController(const WiiUProController& toCopy){
        //allcoates memory for the device
        device = new libevdev;

        //copies thedevice data from toCopy to device
        *device = *toCopy.device;
    }

    WiiUProController& WiiUProController::operator =(const WiiUProController& toCopy){
        //copies thedevice data from toCopy to device
        *device = *toCopy.device;
        
        //returns toCopy
        return toCopy;
    }

} //Controller end

