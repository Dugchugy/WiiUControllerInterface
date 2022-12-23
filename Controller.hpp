#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<libevdev.h>

namespace Controller{

    class WiiUProController{
    public:
        //defulat contstructor
        WiiUProController()

        //destroys dynamic memory for the class
        ~WiiUProController()

        //creates a copy of the class
        WiiUProController(const WiiUProController& toCopy);

        //overloads the equals operator
        WiiUProController& operator =(const WiiUProController& toCopy);
        

    private:
        struct libevdev* device;

    };

} //Controller end

#endif