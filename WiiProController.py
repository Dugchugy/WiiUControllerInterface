import os
import time
from itertools import cycle
import argparse
import evdev
from evdev import ecodes
import yaml

class BluetoothDevice:
    device = None

    def get_input_device(self, path):
        return evdev.InputDevice(path)

    def find_input_device(self, search_term):
        """
        Return the input device if there is only one that matches the search term.
        """
        all_devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
        likely_devices = []
        for device in all_devices:
            if search_term in device.name.lower():
                likely_devices.append(device)

        if len(likely_devices) == 1:
            print(likely_devices[0])
            # correct device was likely found
            return likely_devices[0]

        if len(likely_devices) >= 2:
            raise ValueError("Found multiple device possible devices. Please specify the specific event_input_path.")

    def load_device(self, search_term):
        """
        Try to load the device until one that matches the search term exists.
        """
        device = None
        while device is None:
            device = self.find_input_device(search_term)
            if device is None:
                print("Device matching '{}' couldn't be found. Trying again in 3 seconds.".format(search_term))
                time.sleep(3)
        self.device = device

class BluetoothController(BluetoothDevice):

    def __init__(self, config_path=None, device_search_term=None):

        self.connected = True

        #records the current state of the controller
        self.state = {
            "A": 0,
            "B": 0,
            "Y": 0,
            "X": 0,
            "LEFT_BOTTOM_TRIGGER": 0,
            "LEFT_TOP_TRIGGER": 0,
            "RIGHT_TOP_TRIGGER": 0,
            "RIGHT_BOTTOM_TRIGGER": 0,
            "PAD_RIGHT": 0,
            "PAD_LEFT": 0,
            "PAD_UP": 0,
            "PAD_DOWN": 0,
            "START": 0,
            "SELECT": 0,
            "HOME": 0,
            "LEFT_STICK_PRESS": 0,
            "LEFT_STICK_X": 0,
            "LEFT_STICK_Y": 0,
            "RIGHT_STICK_PRESS": 0,
            "RIGHT_STICK_X": 0,
            "RIGHT_STICK_Y": 0
        }

        #reads the config file
        if config_path is None:
            config_path = self._get_default_config_path()
        self.config = self._load_config(config_path)

        #creates a button map for the one from the config file
        self.btn_map = self.config.get('button_map')

        #finds the search term to find the device by
        self.device_search_term = self.config.get('device_search_term', 1280)

        self.load_device(self.device_search_term)
        print(self.device.name)

    def _get_default_config_path(self):
        return os.path.join(os.path.dirname(__file__), 'wiiu_config.yml')


    def _load_config(self, config_path):
        #opesn the config file
        with open(config_path, 'r') as f:
            #reads the config file to a config object
            config = yaml.full_load(f)
        return config

    def readEvents(self):
        try:
            for event in self.device.read_loop():
                btn = self.btn_map.get(event.code)

                val = event.value

                self.state[btn] = val;

                if(event.code > 4):
                    print(btn)

                else:
                    if(val > 150 or val < -150):
                        print(val)
                        print(btn)
        except OSError:
            self.load_device(self.device_search_term)


    def update(self):
        while True:
            self.readEvents()

if __name__ == "__main__":
    ctl = BluetoothController()
    ctl.update()
