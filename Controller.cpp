#include "Controller.hpp"
#include "Device.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<node.h>


namespace Controllers{

    //creates an empty controller state
    ControllerState::ControllerState(){
        //sets head to null
        head = NULL;
    }

    //destroys the current controller state
    ControllerState::~ControllerState(){
        //creates a temporary pointer to the head
        ControllerStateNode*  temp = head;

        //sets head to NULL
        head = NULL;

        //loops while there is a item in the list
        while(temp != NULL){
            //creates a pointer to the next item in the list
            ControllerStateNode* next = temp->next;

            //deletes the current element of the list
            delete temp;

            //sets temp to the next item in the list
            temp = next;
        }
    }

    //creates a copy of a specified controller state
    ControllerState::ControllerState(const ControllerState& toCopy) : ControllerState(){
        //creates a pointer to traverse the new list
        ControllerStateNode* current = head;

        //creates a pointer to traverse the list to copy
        ControllerStateNode* curCopy = toCopy.head;

        while(curCopy != NULL){
            //inserts a node after the current node with the values from the list to copy
            insertAfter(current, curCopy->ID, curCopy->val);

            //moves both pointers to the next item in the list
            current = current->next;
            curCopy = curCopy->next;
        }
    }

    //sets one controller state to a copy of another
    ControllerState& ControllerState::operator = (const ControllerState& toCopy){
        //creates a copy of the state to copy
        ControllerState copy(toCopy);

        //swaps the heads of the copy and the calling list
        ControllerStateNode* temp = copy.head;
        copy.head = head;
        head = temp;

        //returns this
        return *this;
    }

    bool ControllerState::insertAfter(ControllerStateNode* Behind, std::string ID, int val){
        //creates a pointer to hold the new node
        ControllerStateNode* newNode;

        try{
            //attempts to allocate memory for the new node
            newNode = new ControllerStateNode;
        //catchs the allocation fail and returns false
        }catch(std::bad_alloc){
            return false;
        }

        //sets the new nodes ID and value to the ones provided
        newNode->ID = ID;
        newNode->val = val;

        //sets the node after the new node to the one after the node it will be placed behind
        newNode->next = Behind->next;

        //sets the node after the node provided to be the new node
        Behind->next = newNode;

        //returns true
        return true;
    }

    bool ControllerState::updateKey(std::string ID, int val){
        //creates a node to traverse the list with
        ControllerStateNode* current = head;

        //creates a pointer to track the previous item in the list
        ControllerStateNode* prev = NULL;

        //loops until all item in the list have been visited
        if(current != NULL){
            //sets prev to current
            prev = current;

            //checks if the current ID is the same as the one to update
            if(current->ID == ID){
                //sets the current value to the desired value
                current->val = val;

                //returns true (operation was successful)
                return true;
            }
        }
        //no node with specifed ID was found

        //inserts a new node with the specifed ID and value at the end of the list
        return insertAfter(prev, ID, val);
    }

    int ControllerState::QueryKey(std::string ID){
        //creates a node to traverse the list with
        ControllerStateNode* current = head;

        //loops through each item of the list
        while(current != NULL){
            //checks if the current item has the desired ID
            if(current->ID == ID){
                //returns the value of the found node
                return current->val;
            }
        }

        //if the key is not found, it is assumed to have a value of 0
        return 0;
    }

    //creates a new controller object with the search term nintendo
    Controller::Controller(): Controller("wiiu_config.yml"){}

    Controller::Controller(std::string yamlPath){

        std::cout << "looking for device\n";

        YAML::Node yamlFile = YAML::LoadFile(yamlPath);

        //sets the search term from the ymal file
        std::string searchTerm = yamlFile["device_search_term"];

        sensitivity = yamlFile["sensitivity"];

        //looks for a device with the specifed search term
        std::string path = evDevice::findDevicePath(searchTerm);

        //reports the found device path
        std::cout << "found at path: " << path << "\n";

        //sets device to a new device at the found path
        device = evDevice(path);

        //sets the current controller state to a new controller state
        state = ControllerState();

        //reports that the validity of the deivce is being checked
        std::cout << "checking device validity\n";

        //checks the validity of the device
        device.checkValidity();
    }

    //gets the current state of the controller
    ControllerState Controller::getControllerState(){
        //returns the current controller state
        return state;
    }

    int Controller::QueryKey(std::string keyCode){
        //querys the key in the controllers ControllerState
        return state.QueryKey(keyCode);
    }

    bool Controller::UpdateState(){
        //reads all the current events
        std::vector<struct input_event> events = device.getEvents();

        for(int i = 0; i < events.size(); i++){
            std::cout << "event: " << events[i].code << " with value " << events[i].value << "\n";
        }

        return true;
    }

}//end of controller namespace