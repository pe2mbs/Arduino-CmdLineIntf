/*
	Command line interface for arduino

	Provides the command line interface for the user to the program on the 
	Arduino board (not to be confused with Arduino CLI).


	Created 25 Jan 2020
	Engenio Pace
	Modified 21 Jun 2021
	Marc Bertens-Nguyen

	https://eugeniopace.org/arduino/epaper/eink/stoicism/cli/2020/01/25/A-Simple-Command-Line-Interface-for-Arduino.html
	https://eugeniopace.org/arduino/cli/2020/10/30/A-CLI-for-Arduino-followup.html
	
	https://github.com/pe2mbs/Arduino-CmdLineIntf

*/
#include <cli.hpp>

// Prototype functions
int cmd_millis( ArgumentsInterface* args );
int cmd_about( ArgumentsInterface* args );

// All aliases for commands, must be NULL terminated
const char * m[] = { "m", "clk", "time", "millis", NULL };
const char * a[] = { "a", "abt", "about", NULL };

// Commands structure array 
command_t cmds[] = {
    {
		// Command name
        .name = "millis", 
		// Command callback function 
		.handler = cmd_millis, 
		// Command aliasses
		.aliases = m
    },
    {
        .name = "about", 
		.handler = cmd_about, 
		.aliases = a
    }
};

#ifdef SOME_OTHER_STREAM 
// Instanciate the command line interface on the serial port.
CommandLineInterface cmdLine( &Serial, (command_t*)cmds, sizeof( cmds ) / sizeof( command_t ) );

#else
// Can also be done like this
CommandLineInterface cmdLine( (command_t*)cmds, sizeof( cmds ) / sizeof( command_t ) );

#endif

// Specific commands
int cmd_about( ArgumentsInterface* args )
{
    // Check if user called "help about" and displays a help message
    if ( cmdLine.help( args, "about", "Displays a message" ) == CMD_OK )
    {
        return ( CMD_OK );
    }
	// Execute the command.
    Serial.println( "A sample for CLI" );
    return ( CMD_OK );
}

int cmd_millis( ArgumentsInterface* args )
{
    if ( cmdLine.help( args, "millis", "Displays milliseconds since board began running this program." ) == CMD_OK ) 
    {
        return ( CMD_OK );
    }
    Serial.println( millis() );
    return ( CMD_OK );
}

// Generic functions of the Arduino platform
void setup() 
{
	// Start the serial port with 115200 Bps
    Serial.begin( 115200 );
	// Wait for serial port be be ready.
    while( !Serial );
}

void loop() 
{
    // Run repeatedly the run function on the command line interface.
    cmdLine.run();
}
