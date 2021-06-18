#include <cli.hpp>

// Prototype functions
int cmd_millis( args_t args );
int cmd_about( args_t args );

// All aliases for commands
const char * m[] = {"m", "clk", "time", "millis", NULL};
const char * a[] = {"a", "abt", "about", NULL};

// Commands structure array 
command_t cmds[] = {
    {
        "millis", cmd_millis, m
    },
    {
        "about", cmd_about, a
    }
};

CommandLineIntf cmdLine( &Serial, (command_t*)cmds, sizeof( cmds ) / sizeof( command_t ) );

// SPECIFIC COMMANDS
int cmd_about( args_t args )
{
    // Check if user called "help about" and displays a help message
    if ( cmdLine.help( args, "about", "Displays a message" ) == CMD_OK )
    {
        return ( CMD_OK );
    }
    Serial.println( "A sample for CLI" );
    return ( CMD_OK );
}

int cmd_millis( args_t args )
{
    if ( cmdLine.help( args, "millis", "Displays milliseconds since board began running this program." ) == CMD_OK ) 
    {
        return ( CMD_OK );
    }

    Serial.println( millis() );
    return ( CMD_OK );
}

void setup() 
{
    Serial.begin( 115200 );
    while( !Serial );
}

void loop() 
{
    // put your main code here, to run repeatedly:
    cmdLine.run();
}
