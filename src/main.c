
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zoundx.h"

int
main( int argc, char ** argv )
{
    int i;
    char * thing;

    if( argc != 2 )
    {
        printf( "NO!\n" );
        return 1;
    }

    thing = zoundx_encode( argv[1] );
    printf( "%s\n", thing );
    free( thing );

    return 0;

    return 0;
}
