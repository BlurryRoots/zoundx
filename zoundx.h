// b, f, p, v => 1
#define value_1( c )\
    ( c == 'b'      \
   || c == 'f'      \
   || c == 'p'      \
   || c == 'v' )

// c, g, j, k, q, s, x, z => 2
#define value_2( c )\
    ( c == 'c'      \
   || c == 'g'      \
   || c == 'j'      \
   || c == 'k'      \
   || c == 'q'      \
   || c == 's'      \
   || c == 'x'      \
   || c == 'z' )

// d, t => 3
#define value_3( c )\
    ( c == 'd'      \
   || c == 't' )

// l => 4
#define value_4( c )\
    ( c == 'l' )

// m, n => 5
#define value_5( c )\
    ( c == 'm'      \
   || c == 'n' )

// r => 6
#define value_6( c )\
    ( c == 'r' )
    
#define drop_it( c )\
    ( c == 'a' \
   || c == 'e' \
   || c == 'i' \
   || c == 'o' \
   || c == 'u' \
   || c == 'y' \   
   || c == 'h' \
   || c == 'w' )

char * 
zoundx_encode( const char * query );
