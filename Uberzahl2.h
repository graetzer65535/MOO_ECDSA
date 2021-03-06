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
#define maxBits 2

// mask is used to truncate numbers to the correct bitlength
// mask must be a value of all 1's maxBits long
#define mask 0x3L

#define RAND_BITS 16


typedef struct {
  smallType value[DIGITS+1];
  smallType size;
} uberzahl;

typedef struct {
  smallType value[2*DIGITS];
  smallType size;
} longUberzahl;

// UBERZAHL DEFINITIONS :
    //Modifies: initialize input to 0
    void uberzahl_init(uberzahl* const);
    void uberzahl_init_long(longUberzahl* const);
    
    //Modifies: initialize first input to value of second input
    void uberzahl_init_i(uberzahl* const, smallType);
    //void uberzahl_free(uberzahl*);
    void uberzahl_init_l(uberzahl* const, largeType);
    void uberzahl_init_u_u(uberzahl* const, const uberzahl* const);
    void uberzahl_init_u_long(uberzahl* const, const longUberzahl* const);
    void uberzahl_init_long_u(longUberzahl* const, const uberzahl* const);
    void uberzahl_init_long_long(longUberzahl* const, const longUberzahl* const);
    
    //Modifies: initialize first input to random value with second input bits
    // uses the rand function - to seed use srand (unsigned int seed);
    void random (uberzahl* const, smallType);
    void random_long (longUberzahl* const, smallType);

    // standard numeric comparators
    //Effect: returns 1 if designated comparitor returns true given the same inputs
    char uberzahl_gt (const uberzahl* const, const uberzahl* const);
    char uberzahl_lt (const uberzahl* const, const uberzahl* const);
    char uberzahl_ge (const uberzahl* const, const uberzahl* const);
    char uberzahl_le (const uberzahl* const, const uberzahl* const);
    char uberzahl_eq (const uberzahl* const, const uberzahl* const);
    char uberzahl_neq (const uberzahl* const, const uberzahl* const);
    char uberzahl_gt_long (const longUberzahl* const, const longUberzahl* const);
    char uberzahl_lt_long (const longUberzahl* const, const longUberzahl* const);
    char uberzahl_ge_long (const longUberzahl* const, const longUberzahl* const);
    char uberzahl_le_long (const longUberzahl* const, const longUberzahl* const);
    char uberzahl_eq_long (const longUberzahl* const, const longUberzahl* const);
    char uberzahl_neq_long (const longUberzahl* const, const longUberzahl* const);

    // standard arithmetic operations
    //Modifies: first = second +- third
    void uberzahl_a (uberzahl* const, const uberzahl* const, const uberzahl* const);
    void uberzahl_s (uberzahl* const, const uberzahl* const, const uberzahl* const);
    //Modifies: first = first +- second
    char uberzahl_a_long_mut (longUberzahl* const, const longUberzahl* const);
    void uberzahl_s_long_mut (longUberzahl* const, const longUberzahl* const);
    //void uberzahl_s_mut (uberzahl* const, const uberzahl* const);
    
    //Modifies: first = second * third
    void uberzahl_m (longUberzahl* const, const uberzahl* const, const uberzahl* const);
    //Modifies: first = third / fourth, second = third % fourth
    void uberzahl_d (longUberzahl* const, uberzahl* const, const longUberzahl* const, const uberzahl* const);
    static uberzahl RED_n,RED_Np;
    static smallType RED_bits;
    //Modifies: first = second*R^-1 mod n
    void uberzahl_red (uberzahl* const, const longUberzahl* const);
    
    //void uberzahl_rs (uberzahl* const, const uberzahl* const, smallType );
    //void uberzahl_rs_long (longUberzahl* const, const longUberzahl* const, smallType );
    //void uberzahl_ls (longUberzahl* const, const uberzahl* const, smallType );
    //Modifies: first = first >> or << second
    void uberzahl_ls_long_mut (longUberzahl* const,smallType );
    void uberzahl_ls_mut (uberzahl* const,smallType );
    void uberzahl_rs_long_mut (longUberzahl* const,smallType );

    void uberzahl_and (uberzahl* const, const uberzahl* const, const uberzahl* const);
    
    void uberzahl_inverse (uberzahl* const, const uberzahl* const, const uberzahl* const);
    char uberzahl_inverse_helper (uberzahl* const, uberzahl* const, const uberzahl* const, const uberzahl* const);
    
    //Modifies: (x2/z2,y2/z2) = (x0/z0,y0/z0) + (x1/z1,y1/z1)
    void ECC_add(uberzahl* const x2,uberzahl* const y2,uberzahl* const z2,const uberzahl* const x0,const uberzahl* const y0,const uberzahl* const z0,const uberzahl* const x1,const uberzahl* const y1,const uberzahl* const z1);
    //Modifies: (x2/z2,y2/z2) = a*(x1/z1,y1/z1)
    void ECC_mult(uberzahl* const x2,uberzahl* const y2,uberzahl* const z2,const uberzahl* const x1,const uberzahl* const y1,const uberzahl* const z1,const uberzahl* const a);
    
    //Effect: prints input to data stream MSB first
    void uberzahl_print(const uberzahl* const,FILE*);
    void longUberzahl_print(const longUberzahl* const,FILE*);
    void RED_init(int,int,int);

#endif