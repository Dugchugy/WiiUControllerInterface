#include "Controller.hpp"

#include<libevdev-1.0/libevdev/libevdev.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string>
#include<filesystem>

namespace fs = std::filesystem

namespace Controller{

    WiiUProController::WiiUProController() : WiiUProController("path"){}

    WiiUProController::WiiUProController(const std::string& filePath){

        //initializes device to null
        device = NULL;

        //attempts to open the file
        int fd = open(filePath.c_str(), O_RDONLY);

        //checks if the file was opened
        if(fd < 0){
            //throws a device access error
            throw DeviceAccessError(1);
        }

        //creates a new libevdev device
        device = libevdev_new();

        //checks if the device was created properly
        if(!device){
            //throws an error
            throw DeviceAccessError();
        }

        //sets the device to the accosiated file device
        int err = libevdev_set_fd(device, fd);

        //checks if the set fd failed
        if(err < 0){
            //throws an error
            throw DeviceAccessError(err);
        }
    }

    WiiUProController::~WiiUProController(){
        //deletes the device
        libevdev_free(device);
    }

    WiiUProController::WiiUProController(const WiiUProController& toCopy){
        //allcoates memory for the device
        //device = new (struct libevdev);

        //copies thedevice data from toCopy to device
        //*device = *toCopy.device;
    }

    WiiUProController& WiiUProController::operator =(WiiUProController& toCopy){
        //copies thedevice data from toCopy to device
        //*device = *toCopy.device;
        
        //returns toCopy
        return toCopy;
    }

    std::string findDevicePath(const std::string& searchTerm){
        //creates a sting storing the path for the bluetooth devices
        std::string pathBase = "/dev/input/";

        //iterates through each device in the folder
        for (const auto & entry : fs::directory_iterator(path)){
            //prints the path
            std::cout << entry.path() << std::endl;
        }

        return pathBase;
    }

    //createsa device access error with error number 0
    DeviceAccessError::DeviceAccessError() : DeviceAccessError(0) {}

    DeviceAccessError::DeviceAccessError(int EN) {
        //sets the error number to 0
        ErrorNum = EN;
    }

} //Controller end

