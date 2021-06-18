# Arduino-CmdLineIntf
This is a Command Line Interface library, original code from [A CLI for Arduino|https://eugeniopace.org/arduino/cli/2020/10/30/A-CLI-for-Arduino-followup.html] 

Improvements from the orignal code:
* Decreased RAM usage.
* Improved speed.
* Handle also other console than Serial.
* General cleanup of the code, added comments. 
* Made library package

## Building the library
First you need to clone the repository

    # git clone https://github.com/pe2mbs/Arduino-CmdLineIntf.git

    # cd Arduino-CmdLineIntf
On Linux:     
    # ./build-package.sh

On Windows
    # build-package.cmd

Now in ARDUINO ide 
    > select Scetch > Include library >  Add .ZIP library 
    > Find the folder where the repository is and step into the build folder
    > select cli.zip


## Using the library
In the File > Examples menu the CommandLineInterface example can be found.