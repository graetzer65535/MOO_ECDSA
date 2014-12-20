//Actual version

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

void uberzahl_a_long_mut (longUberzahl* const self, const longUberzahl* const input )
{
  largeType workbench = 0;
  // perform addition operation
  char i;
  for (i = 0; i < 2*DIGITS; ++i ){
    workbench = workbench + self->value[i] +input->value[i];
    self->value[i] = workbench & mask;
    workbench = workbench >> maxBits;
  }
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
  uberzahl_s(&r,&r,&one);
  uberzahl_and(&a,&a,&r);
  longUberzahl b;
  uberzahl_m(&b,&a,&RED_Np);
  uberzahl_init_u_long(&a,&b);
  uberzahl_and(&a,&a,&r);
  uberzahl_m(&b,&a,&RED_n);
  uberzahl_a_long_mut(&b,self);
  uberzahl_rs_long_mut(&b,RED_bits);
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
  if(uberzahl_eq(&zero,z1)) {
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
  if(uberzahl_gt(&x1z,&x0z)) {
    uberzahl_a(&xp,&x0z,&RED_n);
    uberzahl_s(&xm,&xp,&x1z);
  } else {
    uberzahl_s(&xm,&x0z,&x1z);
  }
  uberzahl_a(&xp,&x0z,&x1z);
  if(uberzahl_ge(&xp,&RED_n))
    uberzahl_s(&xp,&xp,&RED_n);
  if(uberzahl_gt(&y1z,&y0z)) {
    uberzahl_a(&yp,&y0z,&RED_n);
    uberzahl_s(&ym,&yp,&y1z);
  } else {
    uberzahl_s(&ym,&y0z,&y1z);
  }
  uberzahl_a(&yp,&y0z,&y1z);
  if(uberzahl_ge(&yp,&RED_n))
    uberzahl_s(&yp,&yp,&RED_n);
  
  if(
  uberzahl z;
  uberzahl_m(&temp,z0,z1);
  uberzahl_red(&z,&temp);
  
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

