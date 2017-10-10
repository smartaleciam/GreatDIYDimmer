# GreatDIYDimmer
I had a Great idea the other night, an since been jotting down notes everyware.

Picture This "DMX Controller, Midi Controller, Pixel Controller, Live Pattern/sequence Player"

- 3.5" Touch Screen LCD, (or Bigger)
- 4x Access buttons with Led's,
- 4x4 Silicone Touch Pixel Matrix (with RGB Pixels in each),
- 8x 10mm Sliders,
- 4x JoySticks,
- USD Stick Storage,
- RFID Scanner,
- Onboard Clock.
- Mic Sensor,

-= Rear Panel =-

- 2x DMX In/Out,
- 1x MIDI In/Out,
- 2x Pixel Out (ws2811),
- {maybe E1.31 Out Ethernet}
- {maybe Esp8266 Module for Remote control Via Phone}

-= The following is a Discription of the Folders for the different Arduino Images =-

- dimmer_colour_buttons = arduino mini pro {serial}, controlling 4x4 button matrix an rgb ws2811 pixel for each button
- dimmer_sliders = arduino mini pro {serial}- using I2C to 4 ---- enabling 1 joystick an 2 fader sliders per ----
- dimmer_usb = arduino uno + USB Host Shield {serial+I2C}, Enable's USB storage an playback of sequences
- dimmer_lcd = arduino mega + 3.5" TouchScreen + (SD LCD Graphix) + RFID {Serial buttons}{Serial sliders}{Serial+I2C usb}{Serial+I2C Output) - Main Controler
- dimmer_output = arduino mega {serial+I2C}, Enabling 2x DMX In/Out, 1x Midi In/Out, 2x Ws2811 Pixel Output of 500pixels


The output being a arduino mega could be replace with a Raspberry Pi to do the Outputs

This same project could be programed using a raspberry pi as a output to be a live music sequencer


There are many possabilities

I only have a basic level of arduino programming,

But i hope with the Above project an the different levels of coding needed, this could turn out great

- Faders, Joystick's, Buttons could be colour changers, whipe's, scene setups/playbacks, mainly due to the arduino mini pro sending its raw data to the main LCD Brain to interpret what that data should realy be used for
- the Output board could be programmed to play directly from the USB Stick sequence, or to be a normal dimmer board
- The LCD main brain, can be the heart/thinker for everything, directing what information goes where an what that information means
- The {Serial+I2C} for the Output, USB & LCD. I was thinking the I2C could be like the control word or future instructions, while the serial communications could continue un-interupted
 
