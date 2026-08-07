# Hilliard_smart_lighting
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
### Broker
The MQTT broker is run by Mosquitto on the Raspberry PI 
### Node-RED
Node-RED is run on the Raspberry PI, and is used to provide a user interface to control various settings for the lighting boxes.
#### Code Explanation

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
  - SPEAKER STATUS?
  - RGB Box Status
    - Shows the connection status of all RGB boxes
  - Number of Boxes Online
    - A dial that shows the amount of boxes that are online
  - Testing
    - Has a button to send a test signal to the lights
- Advanced Controls
  - RGB Color Pickers
    - HSV color pickers for each individual box
  - RGB Modes
    - Mode selectors for each individual box
  - RGB Advanced Controls
    - Toggles to turn on or off advanced controls for each individual box
  
## RGB Lighting Control Boxes  
The RGB lighting control boxes (RGB boxes) are stored inside waterproof boxes, and comprised of one ESP32 microcontroller to run the code, a 5V power supply to power the ESP32, and an RGB connection cable.
## A/C Lighting Control Boxes
The A/C lighting control boxes (A/C boxes) are designed to have six outlets to connect to one large Christmas tree. They are comprised of one ESP8266 microcontroller, three programmable A/C PWM dimmers, one 5V power supply, and six outlets. The ESP8266 controls the three dimmers, each of which outputs the controlled power to two outlets.
