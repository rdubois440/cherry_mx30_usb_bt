# Hybrid USB and Bluetooth Keyboard based on a Cherry MX 3.0 

##1- Objectives

I have multiple repositories on this github on the topic of keyboards, and keyboard hacking. Here are my objectives

* Use a good quality keyboard. Mechanical keyboard is preferred   
* Should be compact. I consider the numeric keypad to be a waste of space.   
The numeric keypad has the extra nuisance that it more or less fores you to misalign the center of your screen to the left of the center of the screen. Which is not ergonomic 
* Restrict the usage of the mouse to a strict minimum. Whenever possible, use the keyboard, or keyboard shortcuts instead of the mouse.  
When there is no keyboard alternative, a pointing device is necessary. 
But this pointing device cannot be a mouse. After years of using a mouse, my right hand would find the mouse if there is on, and use it when it is it would be better avoided. A simple and small touchpad is preferred
* Remap the keyboard
Caps Lock is a useless key. Remap it as left mouse key
My Europen Cherry MX has an extra key between the left shift and the "Z" key. This key is a duplicate of the "\" key, which is not strictly required. Remap it as a mouse right click
 
##2- Original Cherry MX 3.0 Mechanical Keyboard with Brown Switches

I already owned a Cherry MX 3.0, and like the quality. I was about to buy a second one, but was lucky to find one at a good price on an local auction web site


![Legend](images/Cherry_mx_30.jpg)
##2- Components
One Mechanical Keyboard. I used a Cherry MX 3.0, which provides good quality for a good price. Other mechanical keyboards can probably be used as well
Avoid rubber dome / film layers keyboards, as they are very difficult to modify

Ergo Touchpad
http://www.ergonomictouchpad.com/ergonomic_touchpad.php
![Legend](images/ergonomictouchpad3.jpg)

Arduino Micro Pro without headers 

Bluefruit EZ-Link - Bluetooth Serial Link & Arduino Programmer - v1.3
https://www.adafruit.com/products/1588
Adafruit reports the item to be out of stock, I could find one device available at a local store


Future extension
3.3" Touch Screen Panel Digitizer Film to Glass 70x56mm MP4 MP5 GPS Replacement
http://www.ebay.ch/itm/371593680880?euid=e4055c0f5092443bba7906763dcfad3e&bu=44011322663&cp=1&sojTags=bu=bu

![Legend](images/touchscreen.jpg)

Thin wires, screws and this sort of things


##3- Modifications to the original Cherry MX 3.0

Mechanical keyboards are good for typing, but also good for hacking. the keys are soldered on a single layer printed circuit board (PCB). 
It makes it possible to cut and rewire keys as desired   

* Cut away the numeric keypad    
* Keep the 4 arrow keys, and cut away the 9 keys above the arrow keys (page up, page down, delete, print screen etc)
Use the space left by the 9 keys and install a USB Ergo Touchpad

![Legend](images/cherrymx_cut.jpg)


##4- Wiring the modified Cherry MX 3.0

A keyboard is a matrix of rows and columns.
The cutting operations above probably interrupted some of these connections. Just reconnect them according to you best guess
In my case, this is how the rows and columns look like

![Legend](images/cherrymx_wiring.jpg)


##5- Schematic


##5- Arduino Program

##5- Future Extensions 

##5- Limitations

The very nice Adafruit Bluefruit EZ HID module has one strong limitation: it can only be paired to one target
It is not possible to switch from one device to another one without a (simple) repairing 
Trying to get more information from Adafruit. 

```
Testing some code    
```


