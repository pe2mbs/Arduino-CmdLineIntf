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
#include <cli.hpp>
/*
*	This are the core functions of the command line interface class.
*/
#define __version__		"1.1.0"

/*
*	Command line interface class generic functions
*
*/
int CommandLineIntf::run( void )
{
    int ret = CMD_OK;
    // Display the prompt for the user
    this->console->print( "> " );
    // Wait for the user to enter a command
    if ( this->readLine() )
    {
        // Process the command line entered by the user
        ret = this->parseLine(); 
        if ( ret > CMD_OK )
        {
            ret = executeCommand();
        }
    }
    // Clear the command line data
    this->line = "";
    this->args.clear();
    return ( ret );
}

int CommandLineIntf::help( ArgumentsIntf* args, const char * cmd, const char * helpString )
{
    if ( !args->cmp( 1, "help" ) )
    {
        this->console->print( "Usage " );
        this->console->print( cmd );
        this->console->print( ". " );
        this->console->println( helpString );
        return ( CMD_OK );
    }
    return ( CMD_SKIP ); 
}

int CommandLineIntf::parseLine( void )
{
    char* argument;
    // Get the first token until the space character
    argument = strtok( this->line.c_str(), " " );
    while ( ( argument != NULL ) )
    {
        // Check the number of arguments not exceeded
        if ( this->args.count() < MAX_NUM_ARGS )
        {
            // Check the argument length not exceed the buffer space.
            if ( strlen( argument ) < ARG_BUF_SIZE )
            {
				this->args.push( argument );
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
    return ( this->args.count() );
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
    for ( int i = 0; i < this->cmdCount; i++ )
    {
        // Search by name
        if ( !strcmp( command, this->commands[ i ].name ) )
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

int CommandLineIntf::executeCommand( void )
{  
    command_t* c = findCommand( this->args.toString( 0 ) );
    if ( c )
    {
        return ( *c->handler )( &this->args );
    }
    if ( !this->args.cmp( 0, "help" ) || !this->args.cmp( 0, "h" ) )
    {
        return ( this->cmdHelp( &this->args ) );
    }   
    this->console->println( F( "Invalid command. Type \"help\" for more." ) );
    return ( CMD_ERROR );
}

int CommandLineIntf::cmdHelp( ArgumentsIntf* args )
{
    if ( args->toString( 1 )[ 0 ] == 0 )
    {
        this->console->println( F( "The following commands are available:" ) );
        for( int i = 0; i < this->cmdCount; i++ )
        {
            this->console->print( "  " );
            this->console->print( this->commands[ i ].name );
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
        command_t* c = findCommand( args->toString( 1 ) );
        if ( c == NULL || !strcmp( "help", c->name ) )
        {
            if ( c == NULL ) 
            { 
                this->console->println( F( "Command not found" ) ); 
            }
			this->args.clear();
            this->args.push( "help" );
            this->args.push( "" );
            return ( this->cmdHelp( &this->args ) );
        }
		this->args.clear();
        this->args.push( c->name );
        this->args.push( "help" );
        return ( (*c->handler)( &this->args ) );
    }
}
