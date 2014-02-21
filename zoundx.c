
#include "zoundx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.c"

//#define DEBUG 0

/*
    (from wikipedia)
    The correct value can be found as follows:

    1. 
        Retain the first letter of the name and
        drop all other occurrences of a, e, i, o, u, y, h, w.

    2.
        Replace consonants with digits as follows
        (after the first letter):
        b, f, p, v => 1
        c, g, j, k, q, s, x, z => 2
        d, t => 3
        l => 4
        m, n => 5
        r => 6
    3.
        If two or more letters with the same
        number are adjacent in the original
        name (before step 1), only retain the
        first letter; also two letters with
        the same number separated by 'h' or 'w'
        are coded as a single number, whereas
        such letters separated by a vowel are
        coded twice. This rule also applies
        to the first letter.

    4.
        Iterate the previous step until you
        have one letter and three numbers.
        If you have too few letters in your
        word that you can't assign three
        numbers, append with zeros until
        there are three numbers. If you
        have more than 3 letters, just
        retain the first 3 numbers.

    Algorithm has been slightly altered
    inspired by the paper found here:
    http://www.creativyst.com/Doc/Articles/SoundEx1/SoundEx1.htm
*/
char * 
zoundx_encode( const char * query )
{
    char * buffer;
    char * lower;
    int i, j, l, val;

    l = strlen( query );
    lower = calloc( l, sizeof(char) );

    for( i = 0; i < l; ++i )
    {
        lower[i] = tolower( query[i] );
    }
#ifdef DEBUG
    printf( "after lowering: %s. l:%d\n", lower, l );
#endif

    /*
        If two or more letters with the same
        number are adjacent in the original
        name (before step 1), only retain the
        first letter
    */
    for( i = 0; i < l; ++i )
    {
        if( (i+1) < l
         && i > 1
         && ( ( value_1( lower[i] ) && value_1( lower[i+1] ) )
           || ( value_2( lower[i] ) && value_2( lower[i+1] ) )
           || ( value_3( lower[i] ) && value_3( lower[i+1] ) )
           || ( value_4( lower[i] ) && value_4( lower[i+1] ) )
           || ( value_5( lower[i] ) && value_5( lower[i+1] ) )
           || ( value_6( lower[i] ) && value_6( lower[i+1] ) ) ) )
        {
            lower[i+1] = ' ';
        }
    }
    // shift whitespace to the far right
    l = trim( & lower, shift_whitespaces( lower ) );
#ifdef DEBUG
    printf( "after removing doubles: %s. l:%d\n", lower, l );
#endif

    /*
        two letters with
        the same number separated by 'h' or 'w'
        are coded as a single number
    */
    for( i = 0; i < l; ++i )
    {
        if( (i+1) < l
         && i > 1
         && ( lower[i] == 'h' || lower[i] == 'w' )
         && ( ( value_1( lower[i-1] ) && value_1( lower[i+1] ) )
           || ( value_2( lower[i-1] ) && value_2( lower[i+1] ) )
           || ( value_3( lower[i-1] ) && value_3( lower[i+1] ) )
           || ( value_4( lower[i-1] ) && value_4( lower[i+1] ) )
           || ( value_5( lower[i-1] ) && value_5( lower[i+1] ) )
           || ( value_6( lower[i-1] ) && value_6( lower[i+1] ) ) ) )
        {
            lower[i] = lower[i+1] = ' ';
        }
    }
    // shift whitespace to the far right
    l = trim( & lower, shift_whitespaces( lower ) );
#ifdef DEBUG
    printf( "after removing pseudo doubles: %s. l:%d\n", lower, l );
#endif

    /*
        Drop a, e, i, o, u, y.
        Preserve the first character.
    */
    for( i = 1; i < l; ++i )
    {
        if( drop_it( lower[i] ) )
        {
            lower[i] = ' ';
        }
    }
    // shift whitespace to the far right
    l = trim( & lower, shift_whitespaces( lower ) );
#ifdef DEBUG
    printf( "after removing vowels: %s. l:%d\n", lower, l );
#endif

    /*
        Change characters according to their value.
    */
    for( i = 1; i < l; ++i )
    {
        if( ( value_1( lower[i] ) && (val = 1) )
         || ( value_2( lower[i] ) && (val = 2) )
         || ( value_3( lower[i] ) && (val = 3) )
         || ( value_4( lower[i] ) && (val = 4) )
         || ( value_5( lower[i] ) && (val = 5) )
         || ( value_6( lower[i] ) && (val = 6) ) )
        {
            lower[i] = '0' + (char)val;
        }
    }
#ifdef DEBUG
    printf( "after encoding: %s. l:%d\n", lower, l );
#endif


    // if word had more than 4 characters
    // drop them
    if( l > 4 )
    {
        buffer = calloc( 4, sizeof(char) );
        for( i = 0; i < 4; ++i )
        {
            buffer[i] = lower[i];
        }
        free( lower );
        lower = buffer;
    }
    // else if the word had less then 4 characters
    // fill up with zeros
    else if( l < 4 && l > 0 )
    {
        buffer = calloc( 4, sizeof(char) );
        for( i = 0; i < l; ++i )
        {
            buffer[i] = lower[i];
        }
        free( lower );
        lower = buffer;

        for( i = l; i < 4; ++i )
        {
            lower[i] = '0';
        }
    }

    // change the first character to be upper case
    lower[0] = toupper( lower[0] );

    return lower;
}
