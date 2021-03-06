#include <assert.h>
#include <stdio.h>
#include "Uberzahl2.h"

void uberzahl_init(uberzahl* const self) {
  char i;
  for(i=0;i<=DIGITS;i++)
    self->value[i] = 0;
}

void uberzahl_init_long(longUberzahl* const self) {
  char i;
  for(i=0;i<2*DIGITS;i++)
    self->value[i] = 0;
}

void uberzahl_init_i (uberzahl* const self, smallType number){
  uberzahl_init(self);
  self->value[0] = number;
}

void uberzahl_init_l (uberzahl* const self, largeType number){
  uberzahl_init(self);
  char i=0;
  do{
    self->value[i] = number & mask;
    number = number >> maxBits;
    i++;
  } while( number != 0 );
}

void uberzahl_init_u_u (uberzahl* const self, const uberzahl* const number ){
  char i;
  for (i=0; i <= DIGITS; ++i )
    self->value[i] = number->value[i];
}

void uberzahl_init_u_long (uberzahl* const self, const longUberzahl* const number ){
  char i;
  for (i=0; i <= DIGITS; ++i )
    self->value[i] = number->value[i];
}

void uberzahl_init_long_u (longUberzahl* const self, const uberzahl* const number ){
  char i;
  for (i=0; i <= DIGITS; ++i )
    self->value[i] = number->value[i];
  for (i=DIGITS+1;i<2*DIGITS;++i)
    self->value[i] = 0;
}

void uberzahl_init_long_long (longUberzahl* const self, const longUberzahl* const number ){
  char i;
  for (i=0; i < 2*DIGITS; ++i )
    self->value[i] = number->value[i];
}

char uberzahl_gt (const uberzahl* const self, const uberzahl* const rhs) {
  char i;
  for(i=DIGITS;i>=0;i--) {
    if(self->value[i]>rhs->value[i])
      return 1;
    if(self->value[i]<rhs->value[i])
      return 0;
  }
  return 0;
}

char uberzahl_eq (const uberzahl* const self, const uberzahl* const rhs) {
  char i;
  for(i=DIGITS;i>=0;i--)
    if(self->value[i]!=rhs->value[i])
      return 0;
  return 1;
}

char uberzahl_lt (const uberzahl* const self, const uberzahl* const rhs) {
  return uberzahl_gt(rhs,self);
}
char uberzahl_ge (const uberzahl* const self, const uberzahl* const rhs) {
  return uberzahl_gt(self,rhs)||uberzahl_eq(self,rhs);
}
char uberzahl_le (const uberzahl* const self, const uberzahl* const rhs) {
  return uberzahl_lt(self,rhs)||uberzahl_eq(self,rhs);
}
char uberzahl_neq (const uberzahl* const self, const uberzahl* const rhs) {
  return !uberzahl_eq(self,rhs);
}

char uberzahl_gt_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  char i;
  for(i=2*DIGITS-1;i>=0;i--) {
    if(self->value[i]>rhs->value[i])
      return 1;
    if(self->value[i]<rhs->value[i])
      return 0;
  }
  return 0;
}

char uberzahl_eq_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  char i;
  for(i=2*DIGITS-1;i>=0;i--)
    if(self->value[i]!=rhs->value[i])
      return 0;
  return 1;
}

char uberzahl_lt_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  return uberzahl_gt_long(rhs,self);
}
char uberzahl_ge_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  return uberzahl_gt_long(self,rhs)||uberzahl_eq_long(self,rhs);
}
char uberzahl_le_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  return uberzahl_lt_long(self,rhs)||uberzahl_eq_long(self,rhs);
}
char uberzahl_neq_long (const longUberzahl* const self, const longUberzahl* const rhs) {
  return !uberzahl_eq_long(self,rhs);
}

smallType max(smallType a,smallType b) {
  return a>b?a:b;
}

void uberzahl_a (uberzahl* const retval, const uberzahl* const self, const uberzahl* const input )
{
  largeType workbench = 0;
  // perform addition operation
  char i;
  for (i = 0; i < DIGITS; ++i ){
    workbench = workbench + self->value[i] +input->value[i];
    retval->value[i] = workbench & mask;
    workbench = workbench >> maxBits;
  }
  retval->value[DIGITS] = workbench;
}

void uberzahl_s (uberzahl* const retval, const uberzahl* const self, const uberzahl* const input )
{
  largeType workbench = 0;

  // constraint that left side !< right side
  //if ( uberzahl_lt(self, input) )
//    return retval;
  char i;
  for (i = 0; i <= DIGITS; ++i ){
    workbench = self->value[i] - (input->value[i] + workbench);
    retval->value[i] = workbench & mask;
    workbench = workbench >> maxBits;
    if ( workbench ) workbench = 1;
  }
  if(workbench)
    uberzahl_init(retval);
}
void uberzahl_s_mod (uberzahl* const retval, const uberzahl* const self, const uberzahl* const input ) {
  if(uberzahl_gt(input,self)) {
    uberzahl_a(retval,self,&RED_n);
    uberzahl_s(retval,retval,input);
  } else
    uberzahl_s(retval,self,input);
}
void uberzahl_a_mod (uberzahl* const retval, const uberzahl* const self, const uberzahl* const input ) {
  uberzahl_a(retval,self,input);
  if(uberzahl_ge(retval,&RED_n))
    uberzahl_s(retval,retval,&RED_n);
}

char uberzahl_a_long_mut (longUberzahl* const self, const longUberzahl* const input )
{
  largeType workbench = 0;
  // perform addition operation
  char i;
  for (i = 0; i < 2*DIGITS; ++i ){
    workbench = workbench + self->value[i] +input->value[i];
    self->value[i] = workbench & mask;
    workbench = workbench >> maxBits;
  }
  return (char)workbench;
//  assert(!workbench);
}

void uberzahl_s_long_mut (longUberzahl* const self, const longUberzahl* const input )
{
  largeType workbench = 0;

  // constraint that left side !< right side
  //if ( uberzahl_lt(self, input) )
//    return retval;
  char i;
  for (i = 0; i < 2*DIGITS; ++i ){
    workbench = self->value[i] - (input->value[i] + workbench);
    self->value[i] = workbench & mask;
    workbench = workbench >> maxBits;
    if ( workbench ) workbench = 1;
  }
  if(workbench)
    uberzahl_init_long(self);
}

void uberzahl_m (longUberzahl* const retval, const uberzahl* const self, const uberzahl* const y )
{
  largeType workbench;
  char i,j;
  for(i=0;i<2*DIGITS;i++)
    retval->value[i] = 0;
  for(i=0;i<DIGITS;i++) {
    workbench = 0;
    for(j=0;j<DIGITS;j++) {
      workbench = retval->value[i+j] + ((largeType) self->value[j])*y->value[i] + workbench;
      retval->value[i+j] = workbench & mask;
      workbench = workbench>>maxBits;
    }
    retval->value[i+DIGITS] += workbench;
  }
}

void random (uberzahl* const self, smallType bits ){
  assert( bits > 0 );
  assert(bits <= maxBits*DIGITS);
  uberzahl_init(self);
  smallType shortbits = bits % maxBits;
  smallType longbits = bits / maxBits;

  // compiler fix for 32k RAND generators
  // fill the value vector with randomly generated bits
  char i,j;
  for (j = 0; j <= longbits; ++j ){
    for (i = 0; i <= maxBits / RAND_BITS; ++i ){
      self->value[j] = self->value[j] << RAND_BITS/2;
      self->value[j] = self->value[j] << RAND_BITS/2;
      self->value[j] = (self->value[j] + rand()) & mask;
    }
  }

  // shave off the extra bits that were placed
  if ( shortbits ){
    self->value[longbits] = self->value[longbits] >> (maxBits - shortbits);
    //self->value[longbits] = self->value[longbits] | (1 << (shortbits - 1));
  }
  else{
    self->value[longbits] = 0;
    //value[longbits-1] = value[longbits-1] | (1 << (maxBits - 1));
  }

}

void random_long (longUberzahl* const self, smallType bits ){
  assert( bits > 0 );
  assert(bits < maxBits*DIGITS*2);
  uberzahl_init_long(self);
  smallType shortbits = bits % maxBits;
  smallType longbits = bits / maxBits;

  // compiler fix for 32k RAND generators
  // fill the value vector with randomly generated bits
  char i,j;
  for (j = 0; j <= longbits; ++j ){
    for (i = 0; i <= maxBits / RAND_BITS; ++i ){
      self->value[j] = self->value[j] << RAND_BITS/2;
      self->value[j] = self->value[j] << RAND_BITS/2;
      self->value[j] = (self->value[j] + rand()) & mask;
    }
  }

  // shave off the extra bits that were placed
  if ( shortbits ){
    self->value[longbits] = self->value[longbits] >> (maxBits - shortbits);
    //self->value[longbits] = self->value[longbits] | (1 << (shortbits - 1));
  }
  else{
    self->value[longbits] = 0;
    //value[longbits-1] = value[longbits-1] | (1 << (maxBits - 1));
  }

}

/*void uberzahl_ls (longUberzahl* const retval, const uberzahl* const self, smallType shift )
{
  // binary left shift
  for(char i=0;i<2*DIGITS;i++)
    retval->value[i] = 0;
  
  smallType largeshift = shift / maxBits;
  smallType smallshift = shift % maxBits;

//  for ( char i=0; i < largeshift + self->size + 1; ++i )
//   push_back(retval, 0);

  for ( char i=0; i < DIGITS; ++i )
    retval->value[i+largeshift] = (self->value[i] << smallshift) & mask;
  for ( char i=0; i < DIGITS && smallshift; ++i ){
    smallType workspace = self->value[i];
    workspace = workspace >> ( maxBits - smallshift );
    retval->value[i+largeshift+1] |= workspace;
  }

  //clean_bits(retval);
  return retval;
}*/

/*void uberzahl_rs (uberzahl* const retval, const uberzahl* const self, smallType shift )
{
  // binary right shift
  uberzahl_init(&retval);
  smallType largeshift = shift / maxBits;
  smallType smallshift = shift % maxBits;
  //for ( char i=0; i + largeshift + 1 < self->size; ++i )
//    push_back(retval, 0);

  for ( char i=0; i + largeshift < DIGITS; ++i )
    retval->value[i] = value[i + largeshift] >> smallshift;
  for ( char i=0; i + largeshift + 1 < DIGITS; ++i ){
    smallType workspace = self->value[i + largeshift + 1];
    workspace = workspace << ( maxBits - smallshift );
    retval->value[i] |= workspace & mask;
  }

  //clean_bits(retval);
  return retval;
}*/

void uberzahl_ls_long_mut (longUberzahl* const self,smallType shift) {

  smallType largeshift = shift / maxBits;
  smallType smallshift = shift % maxBits;
  
  char i;
  for (i=2*DIGITS-1; i+1 > largeshift; --i ) {
    self->value[i] = (self->value[i-largeshift]<<smallshift) & mask;
    if(i>largeshift)
      self->value[i] |= self->value[i-largeshift-1]>>(maxBits-smallshift);
  }
  for (i=largeshift-1;i>=0;i--) {
    self->value[i] = 0;
  }
}

void uberzahl_ls_mut (uberzahl* const self,smallType shift) {

  smallType largeshift = shift / maxBits;
  smallType smallshift = shift % maxBits;
  
  char i;
  for (i=DIGITS; i+1 > largeshift; --i ) {
    self->value[i] = (self->value[i-largeshift]<<smallshift) & mask;
    if(i>largeshift)
      self->value[i] |= self->value[i-largeshift-1]>>(maxBits-smallshift);
  }
  for (i=largeshift-1;i>=0;i--) {
    self->value[i] = 0;
  }
}

void uberzahl_rs_long_mut (longUberzahl* const self, smallType shift ) {
  // binary right shift
//  uberzahl_init(&retval);
  smallType largeshift = shift / maxBits;
  smallType smallshift = shift % maxBits;
  //for ( char i=0; i + largeshift + 1 < self->size; ++i )
//    push_back(retval, 0);
  char i;
  for (i=0; i + largeshift < 2*DIGITS; ++i ) {
    self->value[i] = self->value[i + largeshift] >> smallshift;
    if(i+largeshift+1<2*DIGITS) {
      self->value[i] |= (self->value[i+largeshift+1]<<(maxBits-smallshift)) & mask;
    }
  }
  for(i=2*DIGITS-largeshift;i<2*DIGITS;++i) {
    self->value[i]=0;
  }
  /*for ( char i=0; i + largeshift + 1 < DIGITS; ++i ){
    smallType workspace = self->value[i + largeshift + 1];
    workspace = workspace << ( maxBits - smallshift );
    retval->value[i] |= workspace & mask;
  }

  //clean_bits(retval);
  return retval;*/
}

void uberzahl_and (uberzahl* const retval, const uberzahl* const a, const uberzahl* const b) {
  smallType i;
  for(i=0;i<=DIGITS;i++) {
    retval->value[i] = a->value[i] & b->value[i];
  }
}

void uberzahl_d (longUberzahl* const retval, uberzahl* const mod, const longUberzahl* const self, const uberzahl* const y) {
  longUberzahl ty;
  longUberzahl x;
  uberzahl_init_long_long(&x,self);
  uberzahl_init_long_u(&ty,y);
  char largeshift=0,smallbits=0;
  while(y->value[DIGITS-largeshift-1]==0)
    largeshift++;
  smallType t = y->value[DIGITS-largeshift-1];
  while(t) {
    smallbits++;
    t = t>>1;
  }
  smallType shift = (DIGITS+largeshift)*maxBits+(maxBits-smallbits);
  uberzahl_ls_long_mut(&ty,shift);
  smallType i;
  uberzahl_init_long(retval);
  longUberzahl one;
  uberzahl_init_long(&one);
  one.value[0]=1;
  for(i=0;i<=shift;i++) {
    uberzahl_ls_long_mut(retval,1);
    if(uberzahl_ge_long(&x,&ty)) {
      uberzahl_s_long_mut(&x,&ty);
      uberzahl_a_long_mut(retval,&one);
    }
    uberzahl_rs_long_mut(&ty,1);
  }
  uberzahl_init_u_long(mod,&x);
}

void uberzahl_inverse (uberzahl* const a_inv, const uberzahl* const a, const uberzahl* const b) {
  uberzahl zero,one;
  uberzahl_init(&zero);
  uberzahl_init_i(&one,1);
  if(uberzahl_eq(a,&one)) {
    uberzahl_init_i(a_inv,1);
    return;
  }
  uberzahl t_a_inv, b_inv;
  char negative = uberzahl_inverse_helper(&t_a_inv,&b_inv,a,b);
  longUberzahl t,tt_a_inv;
  uberzahl_init_long_u(&tt_a_inv,&t_a_inv);
  uberzahl_d(&t,&t_a_inv,&tt_a_inv,b);
  if(negative==1 && uberzahl_neq(&t_a_inv,&zero)) {
    uberzahl_s(a_inv,b,&t_a_inv);
  } else {
    uberzahl_init_u_u(a_inv,&t_a_inv);
  }
}
char uberzahl_inverse_helper (uberzahl* const a_inv, uberzahl* const b_inv, const uberzahl* const a, const uberzahl* const b) {
  longUberzahl bt,coefft;
  uberzahl nexta,coeff;
  uberzahl_init_long_u(&bt,b);
  uberzahl_d(&coefft,&nexta,&bt,a);
  uberzahl_init_u_long(&coeff,&coefft);
  uberzahl zero,one;
  uberzahl_init(&zero);
  uberzahl_init_i(&one,1);
  if(uberzahl_eq(&nexta,&zero)) {
    uberzahl_init(a_inv);
    uberzahl_init(b_inv);
    return 1;
  } else if(uberzahl_eq(&nexta,&one)) {
    uberzahl_init_u_u(a_inv,&coeff);
    uberzahl_init_u_u(b_inv,&one);
    return 1;
  } else {
    uberzahl next_a_inv,next_b_inv;
    char next = uberzahl_inverse_helper(b_inv,&next_b_inv,&nexta,a);
    uberzahl_m(&coefft,b_inv,&coeff);
    uberzahl_init_u_long(&coeff,&coefft);
    uberzahl_a(a_inv,&next_b_inv,&coeff);
    return 1-next;
  }
}

void uberzahl_red (uberzahl* const retval, const longUberzahl* const self) {
  uberzahl a;
  uberzahl_init_u_long(&a,self);
  uberzahl one;
  uberzahl_init_i(&one,1);
  uberzahl r;
  uberzahl_init_i(&r,1);
  uberzahl_ls_mut(&r,RED_bits);
  longUberzahl k;
  uberzahl_init_long_u(&k,&r);
  uberzahl_s(&r,&r,&one);
  uberzahl_and(&a,&a,&r);
  longUberzahl b;
  uberzahl_m(&b,&a,&RED_Np);
  uberzahl_init_u_long(&a,&b);
  uberzahl_and(&a,&a,&r);
  uberzahl_m(&b,&a,&RED_n);
  char t = uberzahl_a_long_mut(&b,self);
  uberzahl_rs_long_mut(&b,RED_bits);
  if(t) {
    uberzahl_a_long_mut(&b,&k);
  }
  uberzahl_init_u_long(retval,&b);
  if(uberzahl_ge(retval,&RED_n))
    uberzahl_s(retval,retval,&RED_n);
}

void ECC_add(uberzahl* const x2,uberzahl* const y2,uberzahl* const z2,const uberzahl* const x0,const uberzahl* const y0,const uberzahl* const z0,const uberzahl* const x1,const uberzahl* const y1,const uberzahl* const z1) {
  uberzahl zero;
  uberzahl_init(&zero);
  if(uberzahl_eq(&zero,z1)) {
    uberzahl_init_u_u(x2,x0);
    uberzahl_init_u_u(y2,y0);
    uberzahl_init_u_u(z2,z0);
    return;
  }
  if(uberzahl_eq(&zero,z0)) {
    uberzahl_init_u_u(x2,x1);
    uberzahl_init_u_u(y2,y1);
    uberzahl_init_u_u(z2,z1);
    return;
  }
  uberzahl x0z,x1z,y0z,y1z;
  longUberzahl temp;
  uberzahl_m(&temp,x0,z1);
  uberzahl_red(&x0z,&temp);
  uberzahl_m(&temp,x1,z0);
  uberzahl_red(&x1z,&temp);
  uberzahl_m(&temp,y0,z1);
  uberzahl_red(&y0z,&temp);
  uberzahl_m(&temp,y1,z0);
  uberzahl_red(&y1z,&temp);
  
  uberzahl xp,xm,yp,ym;
  uberzahl_s_mod(&xm,&x0z,&x1z);
  uberzahl_a_mod(&xp,&x0z,&x1z);
  uberzahl_s_mod(&ym,&y0z,&y1z);
  uberzahl_a_mod(&yp,&y0z,&y1z);
  
  if(uberzahl_eq(&zero,&xm)) {
    if(uberzahl_eq(&zero,&ym)) {
      //CURRENT
      uberzahl xmz,xpz,lambda,two,three,four,eight;
      uberzahl_init_l(&two,62);
      uberzahl_init_l(&three,93);
      uberzahl_init_l(&four,27);
      uberzahl_init_l(&eight,54);
      uberzahl_s_mod(&xmz,x0,z0);
      uberzahl_a_mod(&xpz,x0,z0);
      uberzahl_m(&temp,&xmz,&xpz);
      uberzahl_red(&lambda,&temp);
      uberzahl_m(&temp,&lambda,&three);
      uberzahl_red(&lambda,&temp);
      uberzahl lambda2;
      uberzahl_m(&temp,&lambda,&lambda);
      uberzahl_red(&lambda2,&temp);
      uberzahl yz,yyz,xyyz,xyyz8;
      uberzahl_m(&temp,y0,z0);
      uberzahl_red(&yz,&temp);
      uberzahl_m(&temp,&yz,y0);
      uberzahl_red(&yyz,&temp);
      uberzahl_m(&temp,&yyz,x0);
      uberzahl_red(&xyyz,&temp);
      uberzahl_m(&temp,&xyyz,&eight);
      uberzahl_red(&xyyz8,&temp);
      uberzahl x2t;
      uberzahl_s_mod(&x2t,&lambda2,&xyyz8);
      uberzahl_m(&temp,&x2t,&yz);
      uberzahl_red(x2,&temp);
      uberzahl_m(&temp,x2,&two);
      uberzahl_red(x2,&temp);
      uberzahl_m(&temp,&xyyz,&four);
      uberzahl_red(&xyyz,&temp);
      uberzahl_s_mod(&xyyz,&xyyz,&x2t);
      uberzahl_m(&temp,&xyyz,&lambda);
      uberzahl_red(&xyyz,&temp);
      uberzahl_m(&temp,&yyz,&yz);
      uberzahl_red(&x2t,&temp);
      uberzahl_m(&temp,&x2t,z0);
      uberzahl_red(z2,&temp);
      uberzahl_m(&temp,z2,&eight);
      uberzahl_red(z2,&temp);
      uberzahl_m(&temp,&yyz,&yyz);
      uberzahl_red(&yyz,&temp);
      uberzahl_m(&temp,&yyz,&eight);
      uberzahl_red(&yyz,&temp);
      uberzahl_s_mod(y2,&xyyz,&yyz);
      return;
    } else if(uberzahl_eq(&zero,&yp)) {
      uberzahl_init(z2);
      uberzahl_init_i(x2,1);
      uberzahl_init_i(y2,1);
      return;
    }
  }
  
  uberzahl z;
  uberzahl_m(&temp,z0,z1);
  uberzahl_red(&z,&temp);
  
  uberzahl xm2,ym2z;
  uberzahl_m(&temp,&xm,&xm);
  uberzahl_red(&xm2,&temp);
  uberzahl_m(&temp,&ym,&ym);
  uberzahl_red(&ym2z,&temp);
  uberzahl_m(&temp,&ym2z,&z);
  uberzahl_red(&ym2z,&temp);
  
  uberzahl xpxm2;
  uberzahl_m(&temp,&xp,&xm2);
  uberzahl_red(&xpxm2,&temp);
  
  uberzahl x2t;
//  if(uberzahl_lt(&ym2z,&xpxm2))
//    uberzahl_a(&ym2z,&ym2z,&RED_n);
//  uberzahl_s(&x2t,&ym2z,&xpxm2);
  uberzahl_s_mod(&x2t,&ym2z,&xpxm2);
  uberzahl_ls_mut(&x2t,1);
  if(uberzahl_ge(&x2t,&RED_n))
    uberzahl_s(&x2t,&x2t,&RED_n);
  uberzahl_m(&temp,&x2t,&xm);
  uberzahl_red(x2,&temp);
  
  uberzahl_m(&temp,&xm2,&xm);
  uberzahl_red(&xm2,&temp);
  uberzahl_m(&temp,&xm2,&z);
  uberzahl_red(z2,&temp);
  uberzahl_ls_mut(z2,1);
  if(uberzahl_ge(z2,&RED_n))
    uberzahl_s(z2,z2,&RED_n);
  
  uberzahl_m(&temp,&xm2,&yp);
  uberzahl_red(&xm2,&temp);
//  if(uberzahl_lt(&xpxm2,&x2t))
//    uberzahl_a(&xpxm2,&xpxm2,&RED_n);
//  uberzahl_s(&xpxm2,&xpxm2,&x2t);
  uberzahl_s_mod(&xpxm2,&xpxm2,&x2t);
  uberzahl_m(&temp,&xpxm2,&ym);
  uberzahl_red(&xpxm2,&temp);
//  if(uberzahl_lt(&xpxm2,&xm2))
//    uberzahl_a(&xpxm2,&xpxm2,&RED_n);
//  uberzahl_s(y2,&xpxm2,&xm2);
  uberzahl_s_mod(y2,&xpxm2,&xm2);
  
}

char getbit(const uberzahl* coeff,largeType index) {
  smallType temp = coeff->value[index/maxBits];
  return temp & (1<<(index%maxBits));
}

void ECC_mult(uberzahl* const x2,uberzahl* const y2,uberzahl* const z2,const uberzahl* const coeff,const uberzahl* const x1,const uberzahl* const y1,const uberzahl* const z1) {
  uberzahl x3,y3,z3;
  uberzahl_init_i(x2,1);
  uberzahl_init_i(y2,1);
  uberzahl_init(z2);
  uberzahl_init_u_u(&x3,x1);
  uberzahl_init_u_u(&y3,y1);
  uberzahl_init_u_u(&z3,z1);
  largeType i;
  for(i=maxBits*DIGITS;i>0;i--) {
    if(getbit(coeff,i-1)) {
      ECC_add(x2,y2,z2,x2,y2,z2,&x3,&y3,&z3);
      ECC_add(&x3,&y3,&z3,&x3,&y3,&z3,&x3,&y3,&z3);
    } else {
      ECC_add(&x3,&y3,&z3,&x3,&y3,&z3,x2,y2,z2);
      ECC_add(x2,y2,z2,x2,y2,z2,x2,y2,z2);
    }
  }
}

void uberzahl_print(const uberzahl* const self, FILE* out) {
  char i;
  for(i=DIGITS;i>=0;i--) {
    fprintf(out,"%d ",self->value[i]);
  }
}

void longUberzahl_print(const longUberzahl* const self, FILE* out) {
  char i;
  for(i=DIGITS*2-1;i>=0;i--) {
    fprintf(out,"%d ",self->value[i]);
  }
}

void RED_init(int a,int b,int c) {
    uberzahl_init_l(&RED_n,a);
    uberzahl_init_l(&RED_Np,b);
    RED_bits = c;
}

