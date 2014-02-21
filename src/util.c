
#include <string.h>

/*
    Shifts all whitespaces to the right.
    Returns the number of shifted whitespaces.
*/
int
shift_whitespaces( char * str )
{
    char * raw = str;
    char * shifted = str;
    int whitespaces = 0;

    while( *raw != '\0' )
    {
        if( *raw != ' ' )
        {
            *shifted++ = *raw;
        }
        else
        {            
            ++whitespaces;
        }

        ++raw;
    }

    while( *shifted != '\0' )
    {
        *shifted++ = ' ';
    }

    return whitespaces;
}

/*
    trims n places at the end of the string
    returns new length
*/
int
trim( char ** str, int n )
{
    char * s;
    int i, l;

    l = strlen( *str );

    s = calloc( l-n+1, sizeof(char) );
    for( i = 0; i < l-n; ++i )
    {
        s[i] = (*str)[i];
    }
    s[l-n] = '\0';

    free( *str );
    *str = s;

    return strlen( *str );
}
