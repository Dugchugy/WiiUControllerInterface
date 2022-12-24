#include "Device.hpp"

#include<libevdev-1.0/libevdev/libevdev.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string>
#include<experimental/filesystem>
#include<iostream>

namespace fs = std::experimental::filesystem;

namespace Controller{

    evDevice::evDevice() : evDevice("path"){}

    evDevice::evDevice(const std::string& filePath){

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

    evDevice::~evDevice(){
        //deletes the device
        libevdev_free(device);
    }

    evDevice::evDevice(const evDevice& toCopy){
        //allcoates memory for the device
        //device = new (struct libevdev);

        //copies thedevice data from toCopy to device
        //*device = *toCopy.device;
    }

    evDevice& evDevice::operator =(evDevice& toCopy){
        //copies thedevice data from toCopy to device
        //*device = *toCopy.device;
        
        //returns toCopy
        return toCopy;
    }

    std::string evDevice::findDevicePath(const std::string& searchTerm){
        //creates a sting storing the path for the bluetooth devices
        std::string pathBase = "/dev/input/";

        //creates a string to store the file path
        std::string finalPath = "";

        //creates an int to store how many matchs to the search term were found
        int matchCount = 0;

        //iterates through each device in the folder
        for (const auto & entry : fs::directory_iterator(pathBase)){
            //records the path
            std::string path = entry.path();

            //opens the file at the path
            int fd = open(path.c_str(), O_RDONLY);

            //creates a new input device
            struct libevdev *dev = libevdev_new();

            //sets the input file device to the device at the path 
            libevdev_set_fd(dev, fd);

            //reads the device name
            std::string name = libevdev_get_name(dev);

            //frees the device
            libevdev_free(dev);

            //checks if the name contians the search term
            if(name.find(searchTerm) != std::string::npos){

                //sets the final path to path
                finalPath = path;

                //increases the number of matches found
                matchCount++;
            }
        }

        //checks if more than one device was found (or no devices found)
        if(matchCount != 1){
            //throws the device not found error
            throw DeviceNotFoundError();
        }

        //returns the pathbase
        return finalPath;
    }

    //createsa device access error with error number 0
    DeviceAccessError::DeviceAccessError() : DeviceAccessError(0) {}

    DeviceAccessError::DeviceAccessError(int EN) {
        //sets the error number to 0
        ErrorNum = EN;
    }

} //Controller end

