#include <args.hpp>
/*
*	This are the core functions of the argument class.
*
*/
#define __version__		"1.0.0"
/*
*	Argument interface class
*/
ArgumentsIntf::ArgumentsIntf( void )
{
	this->clear();
	return;
}
/*
*	Clear the arguments
*/
void ArgumentsIntf::clear( void )
{
	memset( this->args, 0, sizeof( char ) * MAX_NUM_ARGS * ARG_BUF_SIZE );
	this->cnt = 0;
	return;
}
/*
*	Return number of arguments
*/
uint8_t	ArgumentsIntf::count( void )
{
	return ( this->cnt );
}
/*
*	Compare argument at index (idx) with text
*/
int ArgumentsIntf::cmp( int8_t idx, const char* text )
{
	if ( idx < this->cnt )
	{
		return ( strcmp( this->args[ idx ], text ) );
	}
	return ( 1 );
}
/*
*	Push new argument onto the argument array
*/
void ArgumentsIntf::push( char* argument )
{
	// Copy the argument into the args array
	if ( this->cnt < MAX_NUM_ARGS )
	{
		strcpy( this->args[ this->cnt ], argument );
		this->cnt++;
	}
	return;
}
/*
*	Return string (c_str) of argument at position idx
*/
const char* ArgumentsIntf::toString( int8_t idx )
{
	if ( idx < this->cnt )
	{
		return ( this->args[ idx ] );
	}
	return ( NULL );
}
