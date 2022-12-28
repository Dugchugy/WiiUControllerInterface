#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "Device.hpp"
#include<unordered_map>
#include<list>

namespace Controllers{

    class ControllerStateNode{
    public:
        ControllerStateNode* next;
        std::string ID;
        int val;
    };

    class ControllerState{
    public:
        //creates an empty state list
        ControllerState();

        //destroys the current Controller state list
        ~ControllerState();

        //creates a copy of the current Controller state
        ControllerState(const ControllerState& toCopy);

        //copies one controller state onto another
        ControllerState& operator =(const ControllerState& toCopy);

        //inserts a new key into the end the state list
        bool insertAfter(ControllerStateNode* Behind, std::string ID, int val);

        //updates the specifed key with a new value
        bool updateKey(std::string ID, int val);

        //attempts to query the specified key (returns 0 if key is not listed (assumed unpressed))
        int QueryKey(std::string ID);

    private:
        ControllerStateNode* head;
    };

    class Controller{
    public:
        //constructs a controller object for a wii u pro controller
        Controller();

        //construcnts a wii u pro controller with the specified search term
        Controller(std::string CSVPath);

        //gets the current state of the controller
        ControllerState getControllerState();

        //querys the state of a specifed key
        int QueryKey(std::string keyCode);

        //updates the current state of the controller in the code
        bool UpdateState();

        //reads the data from the config file to interptret the data from the controller
        void readConfigFile(std::string filePath, std::string& searchTerm);

    private:
        evDevice device;
        ControllerState state;

        int sensitivity;

        std::list<std::string> joysticks;

        std::unordered_map<int, std::string> eventMap;
    };

    class FileAccessError{};

}//end of Controller

#endif