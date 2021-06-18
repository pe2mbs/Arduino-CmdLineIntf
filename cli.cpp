/***
 * Command line interface for Arduino boards
 * 
 * Copyright (C) 2020  Eugenio Pace <eugeniop@auth0.com>
 * Copyright (C) 2021  Marc Bertens-Nguyen <m.bertens@pe2mbs,nl>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Orginal idea by Eugenio from his techincal blog https://eugeniopace.org/arduino/cli/2020/10/30/A-CLI-for-Arduino-followup.html
 * 
 * Improvements for speed, size (RAM), flexability and reuseability.
 * 
 */
#include "cli.hpp"

CommandLineIntf::CommandLineIntf( Stream* s, command_t* c, unsigned int l ) : line()
{
    /***
     *  This runs the command line interface on a stream provided by the main application.
     *  Functions used on stream are:
     *  - print()
     *  - println()
     *  - available()
     *  - readStringUntil()
     */
    this->console     = s;
    this->commands    = c;
    this->noCommands  = l;
    return;
}

CommandLineIntf::CommandLineIntf( command_t* c, unsigned int l ) : line()
{
    /***
     *  This runs the command line interface on the serial port of the Ardiuno
     */
    this->console     = &Serial;
    this->commands    = c;
    this->noCommands  = l;
    return;
}

int CommandLineIntf::run( void )
{
    int ret = CMD_OK;
    // Display the prompt for the user
    this->console->print( "> " );
    // Wait for the user to enter a command
    if ( this->readLine() )
    {
        // Process the command line entered by the user
        ret = this->parseLine( this->line.c_str(), this->args ); 
        if ( ret > CMD_OK )
        {
            ret = executeCommand( this->args );
        }
    }
    // Clear the command line data
    this->line = "";
    memset( this->args, 0, sizeof( char ) * MAX_NUM_ARGS * ARG_BUF_SIZE );
    return ( ret );
}

int CommandLineIntf::help( args_t args, const char * cmd, const char * helpString )
{
    if ( !strncmp( args[ 1 ], "help", 4 ) )
    {
        this->console->print( "Usage " );
        this->console->print( cmd );
        this->console->print( ". " );
        this->console->println( helpString );
        return ( CMD_OK );
    }
    return ( CMD_SKIP ); 
}

int CommandLineIntf::parseLine( char* line, args_t args )
{
    char* argument;
    int counter = 0;
    // Get the first token until the space character
    argument = strtok( line, " " );
    while ( ( argument != NULL ) )
    {
        // Check the number of arguments not exceeded
        if ( counter < MAX_NUM_ARGS )
        {
            // Check the argument length not exceed the buffer space.
            if ( strlen( argument ) < ARG_BUF_SIZE )
            {
                // Copy the argument into the args array
                strcpy( args[ counter ], argument );
                counter++;
                // Get the next token until the space character
                argument = strtok( NULL, " " );
            }
            else
            {
                this->console->print( argument );
                this->console->println( F( ": Argument too long." ) );
                return ( CMD_ERROR );
            }
        }
        else
        {
            this->console->print( F( "Too many arguments, max " ) );
            this->console->println( MAX_NUM_ARGS );
            return ( CMD_ERROR );
        }
    }
    return ( counter );
}

char* CommandLineIntf::readLine( void )
{
    while( !this->console->available() );
    if ( this->console->available() )
    {
        // Read the actual string from the user until the newline character.
        this->line = this->console->readStringUntil( '\n' );
        // Remove any trailing space, carrage return or tab characters
        this->line.trim(); 
        this->console->println( this->line );
        // Return a pointer to the string
        return ( this->line.c_str() );
    }
    return ( NULL );
}

command_t* CommandLineIntf::findCommand( char* command )
{
    // Check for empty command 
    if ( !command || strlen( command ) == 0 )
    {
        // Nothing to process, so just return NULL
        return ( NULL );
    }
    // Walk the commands array to find the command 
    for ( int i = 0; i < this->noCommands; i++ )
    {
        // Search by name
        if ( !strcmp( command, this->commands[ i ].cmd_name ) )
        {
            // Found it, return the command structure
            return ( &this->commands[ i ] );
        }
        // Search all aliases
        if ( this->commands[ i ].aliases ) 
        {
            int j = 0;
            while ( this->commands[ i ].aliases[ j ] )
            {
                if ( !strcmp( command, this->commands[ i ].aliases[ j++ ] ) )
                {
                    // Found it, return the command structure
                    return ( &this->commands[ i ] );
                }
            }
        }
    }
    // No command recognized, return NULL
    return ( NULL );
}

int CommandLineIntf::executeCommand( args_t args )
{  
    command_t* c = findCommand( args[ 0 ] );
    if ( c )
    {
        return ( *c->cmd_handler )( args );
    }
    if ( !strcmp( args[ 0 ], "help" )|| !strcmp( args[ 0 ], "h" ) )
    {
        return ( this->cmdHelp( args ) );
    }   
    this->console->println( F( "Invalid command. Type \"help\" for more." ) );
    return ( CMD_ERROR );
}

int CommandLineIntf::cmdHelp( args_t args )
{
    if ( args[ 1 ][ 0 ] == 0 )
    {
        this->console->println( F( "The following commands are available:" ) );
        for( int i = 0; i < this->noCommands; i++ )
        {
            this->console->print( "  " );
            this->console->print( this->commands[ i ].cmd_name );
            if ( this->commands[ i ].aliases )
            {
                this->console->print( "  (" );
                int j = 0;
                while ( this->commands[ i ].aliases[ j ] )
                {
                    this->console->print( this->commands[ i ].aliases[ j ] );
                    if ( this->commands[ i ].aliases[ j + 1 ] )
                    {
                        this->console->print( ", " );
                    }
                    j++;
                }
                this->console->print( ")" );
            }
            this->console->println( "" );
        }
        this->console->println( "" );
        return ( CMD_OK );
    } 
    else 
    {
        command_t* c = findCommand( args[ 1 ] );
        // char _args[ MAX_NUM_ARGS ][ ARG_BUF_SIZE ];
        char _args[ 2 ][ ARG_BUF_SIZE ];
        if ( c == NULL || !strcmp( "help", c->cmd_name ) )
        {
            if ( c == NULL ) 
            { 
                this->console->println( F( "Command not found" ) ); 
            }
            strcpy( _args[ 0 ], "help" );
            strcpy( _args[ 1 ], "" );
            return ( this->cmdHelp( _args ) );
        }
        strcpy( _args[ 0 ], c->cmd_name );
        strcpy( _args[ 1 ], "help" );
        return ( (*c->cmd_handler)( _args ) );
    }
}
