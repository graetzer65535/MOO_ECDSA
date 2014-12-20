//Features from C++ that may not be implemented yet

// RAND_MAX can be different between compilers and so it is handled here
// If your RAND_MAX is different from below (not 16, 32, 64 bit) you should add it below
// and compile with the correct RAND_MAX length
// ( specifying a smaller RAND_MAX than you have will result in a non-uniform distribution
typedef struct {
  char* chars;
  char len;
} string;

typedef struct {
  uberzahl* c1;
  uberzahl* c2;
  bool negative;
}  inverse_struct;

    void uberzahl_init_c(uberzahl*, const char*);
    uberzahl uberzahl_d (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_d_i (const uberzahl*, smallType);
    uberzahl uberzahl_mod (const uberzahl*, const uberzahl*);
    smallType uberzahl_mod_i (const uberzahl*, smallType);


    // standard c/c++ bitwize operators
    uberzahl uberzahl_or (const uberzahl*, const uberzahl*);
    uberzahl uberzahl_xor (const uberzahl*, const uberzahl*);

    //uberzahl extract ( smallType, smallType );
    //uberzahl rotateLeft (uberzahl*, smallType, smallType, smallType );
    //uberzahl rotateRight ( smallType, smallType, smallType );
    //void setBit ( smallType );
    //void clearBit ( smallType );
    //void toggleBit ( smallType );

    // auxilary functions
    uberzahl gcd (const uberzahl*, const uberzahl*);

    //smallType bit ( smallType ) const;
    smallType bitLength (const uberzahl*);

    string convert_to_string (const uberzahl*);


uberzahl random ( const uberzahl*, const uberzahl* );
bool rabinmiller ( const uberzahl*, smallType );
uberzahl nextprime ( const uberzahl*, smallType );
