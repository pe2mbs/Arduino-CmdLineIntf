#include <args.hpp>

#define __version__		"1.0.0"
/*
*	Return integer value of argument at position idx, default value
*/
int ArgumentsIntf::toInteger( int8_t idx, int def )
{
	if ( idx < this->cnt )
	{
        int result = atoi( this->args[ idx ] );
        if ( result != 0 )
        {
            return ( result );
        }
    }
    return ( def );
}