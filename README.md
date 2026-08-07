# Hilliard Smart Lighting
## Rasperry PI IP address:
192.168.60.6
## MQTT Usernames and Passwords
### RGB boxes:
n = the number of the box  
Username: RGBn  
Password: HilliardRGB#n
### AC boxes:
Username: ACn  
Password: HilliardAC#n
### Node-RED Broker
Username: Node-RED  
Password: HilliardNode-RED
### Music Processing
Username: MusicBox  
Password: HilliardMusicBox

## Other Usernames and Passwords
### Node-RED Admin Account
Username: intern  
Password: Nut-3nact-D3pict!
### Node-RED UI/User Account
Username: Hilliard  
Password: Sm3lls-Lik3-Sad!
# System Explanation  
## Music Processing
## MQTT
### Topics
### Broker
The MQTT broker is run by Mosquitto on a Raspberry PI 
### Node-RED
Node-RED provides configuration of the lights. It runs the user interface, which is hosted by a Raspberry PI alongside the code itself. The code menu can be accessed by entering the ip of the Raspberry PI alongside the 1880 port into the search bar: "(IP address):1880". The UI can be accessed by typing in the same address alongside "/ui": "(IP address):1880/ui"
#### Code Explanation
##### Overview
The Node-RED code works by receiving some input signal from the MQTT broker, sequentially checking all of the settings configured in the UI, and outputting the appropriate signal to send to the boxes. 
##### User Interface
The UI is built using the UIBUILDER Node-RED addon. Through these nodes the different options in the UI are configured. This includes the on/off toggles for all the boxes, the advanced mode toggles for the RGB boxes, the HSV color pickers, the mode selectors for all the boxes, the speed and brightness sliders for the RGB boxes, the test lights buttons, and the total boxes online display.
##### RGB 
- The bulk of the RGB code is checking the settings to see what should be sent to the different boxes. It works in eight phases to check for all of the settings:
  1. The code receives a trigger from an MQTT node (the contents of the signal do not matter)
  2. The code sets a variable "time" to the current UNIX time
  3. The code sets a "delayTime" variable to the sum of "time," and a "delay" variable. It then sets the message payload to a string of "mode " + delayTime.
  4. The message is sent to eight different switches (for eight different boxes), all of which check if their assigned box is turned on. 
  5. The message is sent through a switch which checks if advanced mode is turned on for the assigned box. It then sends the messages to either the regular mode, or advanced mode switches.
  6. Both regular and advanced mode switches check if the mode is set to custom. They then send to either the mode changer, or the custom color changer for their respective complexity.
  7. Both changers will change the "mode" part of the message payload into the mode set in the UI. The color changer will send an HSV value, and the mode will send a value from 1-5. If this is the advanced mode, it will be specific to that box. If it is regular mode, it will be the generalized mode.
  8. The resulting messages payload is sent to an MQTT node which publishes to the proper topic for their respective box.
- The RGB speed and brightness sliders both send the result directly onto their respective topics, which are read by the boxes.
- The RGB connection
##### AC

#### List of Utilities
- Controls
  - A/C
    - On/off control for A/C boxes
  - Modes
    - RGB Mode
      - Fire
      - Grass
      - Ocean
      - Rainbow
      - Christmas
      - Custom
    - RGB Color
      - A color picker, used alongside the "Custom" RGB mode to allow for the user to pick a custom color
    - RGB Speed
      - Used to choose the speed at which the RGB pulses travel
    - RGB Brightness
      - Used to choose the brightness of the RGB LEDs
    - A/C Mode
      - Twinkle
      - Flash
  - RGB
    - On/off control of RGB boxes
  - Testing
    - Has a button to send a test signal to the lights
- Status
  - A/C Box Status
    - Shows the connection status of all A/C boxes
  - RGB Box Status
    - Shows the connection status of all RGB boxes
  - Total Online
    - Has a dial that shows the amount of boxes that are online
  - Testing
    - Has a button to send a test signal to the lights
- Advanced Controls
  - RGB Color Pickers
    - HSV color pickers for each individual box
  - RGB Modes
    - Mode selectors for each individual box
  - RGB Advanced Controls
    - Toggles to turn on or off advanced controls for each individual box
  - Testing
    - Has a button to send a test signal to the lights
  
## RGB Lighting Control Boxes  
The RGB lighting control boxes (RGB boxes) are stored inside waterproof boxes, and comprised of one ESP32 microcontroller to run the code, a 5V power supply to power the ESP32, and an RGB connection cable.
## A/C Lighting Control Boxes
The A/C lighting control boxes (A/C boxes) are designed to have six outlets to connect to one large Christmas tree. They are comprised of one ESP8266 microcontroller, three programmable A/C PWM dimmers, one 5V power supply, and six outlets. The ESP8266 controls the three dimmers, each of which outputs the controlled power to two outlets.

