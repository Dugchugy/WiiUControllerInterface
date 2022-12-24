#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<libevdev-1.0/libevdev/libevdev.h>
#include<string>

namespace Controller{

    class evDevice{
    public:
        //defulat contstructor
        evDevice();

        //creates device for the controller at the specified path
        evDevice(const std::string& filePath);

        //destroys dynamic memory for the class
        ~evDevice();

        //creates a copy of the class
        evDevice(const evDevice& toCopy);

        //overloads the equals operator
        evDevice& operator =(evDevice& toCopy);

        //finds the path for the file device
        static std::string findDevicePath(const std::string& searchTerm);
        

    private:
        struct libevdev *device;

    };

    class DeviceAccessError{
    public:
        DeviceAccessError();

        DeviceAccessError(int EN);

        int ErrorNum;
    };

    class DeviceNotFoundError{};

} //Controller end

#endif