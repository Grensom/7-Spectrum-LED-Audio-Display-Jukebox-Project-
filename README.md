# Please Read these instructions for setting up the 7-Spectrum-LED-Display-Jukebox Project
This is the code and schematics used for the Jukebox YouTube video
Here is the link to the YouTube video this code is based off of: https://youtu.be/znEBoHUX1LQ

## STEP 1: Wire the MSGEQ7 sound module with the Arduino, LED strip and 5VDC Power Supply
** see Schematic file

## STEP 2: Download the needed Libraries
You will need the following libraries:

- FastLED.h

You can get these by going to Arduino IDE >> Sketch >> Include Library >> Manage Libraries >> "search for" FastLED and install library

## STEP 3: Upload the code file to Arduino
 - JukeboxV4.ino

Note that you will want to determine the beginning and end of each spectrum and set the addressable LED accordingly - this will take trial and error. 

In my project the LEDs were snaked back and forth so in the code you will notice there is two main functions LEDShowUp and LEDShowDown. This is to account for the spectrum going both ways to always show the correct orientation. This may need to be adjusted based on the direction of your setup.

Once adjusted, Upload to the arduino.

Some adjustment variables:
- colorAdj: this changes the color pallete (0-255)
- BRIGHTNESS: changes brightness (0-255), keep in mind more brightness requires larger power supply
- LED_TYPE, this project uses WS2811 but can be adapted to similar LED types

## STEP 4: Plug in Music to your sound module
You will need an auxilary cable coming from your sound source into the module so that the chip can do the audio analyzing.

## STEP 5: Enjoy the show!
