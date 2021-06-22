#include <args.hpp>

#define __version__		"1.0.0"
/*
*	Print the arguments onto the stream interface.
*/
void ArgumentsIntf::print( Stream* stream )
{
	for ( int i = 0; i < this->cnt; i++ )
    {
        stream->print( F( "Argument " ) );
        stream->print( i );
        stream->print( " = " );
        stream->println( this->args[ i ] );
    }
    return;
}