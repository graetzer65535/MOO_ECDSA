//BACKUP OF MOSTLY C++ VERSION

#ifndef UBERZAHL_H
#define UBERZAHL_H

// CONFIGURATIONS :
// smallType is used for storage -- uberzahl.value[i]
//    * Adjusting this will adjust the memory efficiency
//    * For most efficient use of memory use your processor's word size
//  mediumType and largeType should be capable of holding 2x MAX(smallType)
//    * These are used mainly for bit manipulation
#define smallType unsigned int
#define largeType unsigned long long
#define DIGITS 4

// maxBits controls how many bits to use our of your smallType container
// you must ensure that maxBits <= BITLEN(smallType)
#define maxBits 16

// mask is used to truncate numbers to the correct bitlength
// mask must be a value of all 1's maxBits long
#define mask 0xffffL

// RAND_MAX can be different between compilers and so it is handled here
// If your RAND_MAX is different from below (not 16, 32, 64 bit) you should add it below
// and compile with the correct RAND_MAX length
// ( specifying a smaller RAND_MAX than you have will result in a non-uniform distribution
#if RAND_MAX == 32767
  #define RAND_BITS 16
#elif RAND_MAX == 2147483647
  #define RAND_BITS 32
#else
  #define RAND_BITS 64
#endif

typedef struct {
  char* chars;
  char len;
} string;

typedef struct {
  uberzahl* c1;
  uberzahl* c2;
  bool negative;
}  inverse_struct;

typedef struct {
  smallType value[DIGITS+1];
  smallType size;
} uberzahl;

typedef struct {
  smallType value[2*DIGITS];
  smallType size;
} longUberzahl;

// UBERZAHL DEFINITIONS :
    void uberzahl_init(uberzahl*);
    void uberzahl_init_i(uberzahl*, smallType);
    //void uberzahl_free(uberzahl*);
    void uberzahl_init_c(uberzahl*, const char*);
    void uberzahl_init_l(uberzahl*, largeType);
    void uberzahl_init_u(uberzahl*, const uberzahl*);
    // uses the rand function - to seed use srand (unsigned int seed);
    void random (uberzahl*, smallType);

    // standard arithmetic operations
    uberzahl uberzahl_a (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_s (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_m (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_d (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_d_i (const uberzahl*, smallType);
    uberzahl uberzahl_mod (const uberzahl*, const uberzahl*);
    smallType uberzahl_mod_i (const uberzahl*, smallType);
    
    // standard numeric comparators
    bool uberzahl_gt (const uberzahl*, const uberzahl*);
    bool uberzahl_lt (const uberzahl*, const uberzahl*);
    bool uberzahl_ge (const uberzahl*, const uberzahl*);
    bool uberzahl_le (const uberzahl*, const uberzahl*);
    bool uberzahl_eq (const uberzahl*, const uberzahl*);
    bool uberzahl_neq (const uberzahl*, const uberzahl*);

    // standard c/c++ bitwize operators
    uberzahl uberzahl_or (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_and (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_xor (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_rs (const uberzahl*, smallType );
    longUberzahl uberzahl_ls (const uberzahl*, smallType );

    //uberzahl extract ( smallType, smallType );
    //uberzahl rotateLeft (uberzahl*, smallType, smallType, smallType );
    //uberzahl rotateRight ( smallType, smallType, smallType );
    //void setBit ( smallType );
    //void clearBit ( smallType );
    //void toggleBit ( smallType );

    // auxilary functions
    uberzahl inverse (const uberzahl*, const uberzahl*);
    uberzahl gcd (const uberzahl*, const uberzahl*);

    //smallType bit ( smallType ) const;
    smallType bitLength (const uberzahl*);

    string convert_to_string (const uberzahl*);


uberzahl random ( const uberzahl*, const uberzahl* );
bool rabinmiller ( const uberzahl*, smallType );
uberzahl nextprime ( const uberzahl*, smallType );

#endif