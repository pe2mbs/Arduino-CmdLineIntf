# Arduino-CmdLineIntf
This is a Command Line Interface library, original code from [A CLI for Arduino](https://eugeniopace.org/arduino/cli/2020/10/30/A-CLI-for-Arduino-followup.html)

Improvements from the orignal code:
* Decreased RAM usage.
* Improved speed.
* Handle also other console than Serial.
* General cleanup of the code, added comments. 
* Made library package

## Building the library
First you need to clone the repository

    # git clone https://github.com/pe2mbs/Arduino-CmdLineIntf.git

    # python build-package.py


Now in ARDUINO ide 
    > select Scetch > Include library >  Add .ZIP library 
    > Find the folder where the repository is and step into the build folder
    > select cli.zip


## Using the library
In the File > Examples menu the CommandLineInterface example can be found.

Initial it supports 10 arugments with a maximun length 20 characters. To 
change this find the file %PATFORMATH%/libraries/CommandLineIntf/src/args.hpp
There you can change the defines ARG_BUF_SIZE and MAX_NUM_ARGS, when increasing these more memory shall be used, by decreasing less memory shall be used.

## Example
In the menu File->Examples->CommandLineIntf the example CommandLineInterface.ino 
can be found. 


