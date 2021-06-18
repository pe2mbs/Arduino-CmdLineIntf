#ifndef CLI_H
#define CLI_H
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
#include <Arduino.h>

#define ARG_BUF_SIZE 20
#define MAX_NUM_ARGS 10

enum { CMD_ERROR, CMD_EXIT, CMD_SKIP, CMD_OK = 0 };

typedef char args_t[][ ARG_BUF_SIZE ];
typedef int  (*handler_t)( args_t args );

typedef struct 
{
    const char*   cmd_name;
    handler_t     cmd_handler;
    const char**  aliases;
} command_t;


class CommandLineIntf 
{
    String      line;
    char        args[ MAX_NUM_ARGS ][ ARG_BUF_SIZE ];
    command_t*  commands;
    int         noCommands;
    Stream*     console;
 
public:
    CommandLineIntf( Stream* s, command_t* c, unsigned int l );
    CommandLineIntf( command_t* c, unsigned int l );

    int run( void );
    int help( args_t args, const char * cmd, const char * helpString );

protected:
    int parseLine( char* line, args_t args );
    char* readLine( void );
    command_t* findCommand( char* command );
    int executeCommand( args_t args );
    int cmdHelp( args_t args );
};

#endif
