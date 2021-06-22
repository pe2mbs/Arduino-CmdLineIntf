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
*	Command line interface class constructor for Stream interface
*
*/
CommandLineIntf::CommandLineIntf( Stream* s, command_t* c, unsigned int l ) : line(), args()
{
    /***
     *  This runs the command line interface on a stream provided by the main application.
     *  Functions used on stream are:
     *  - print()
     *  - println()
     *  - available()
     *  - readStringUntil()
     */
    this->console     	= s;
    this->commands    	= c;
    this->cmdCount  	= l;
    return;
}
