#include <stdio.h>
#include <time.h>
//#include <gmp.h>
#include <assert.h>
#include "Uberzahl2.h"


int main(void) {
  srand(time(0));
  //WDTCTL = WDTPW + WDTHOLD;
  //P4DIR |= 0x04;
  //P4OUT = 4;
  /*int num;
  uberzahl a,b,e,f,g,h;
  longUberzahl c,d,i;
  //uberzahl b;
  //uberzahl c;
  //longUberzahl d;
  //unsigned int a2,b2;
  //unsigned long c2, d2;
  for(num=0;num<50000000;num++) {
    //a2 = rand()&0xf;
    //b2 = rand()&0xffffL;
    //printf("a: %d\nb: %d\n",a2,b2);
    //uberzahl_init_i(&a,a2);
    //uberzahl_init_i(&b,b2);
    random(&a,DIGITS*maxBits);
    random(&h,DIGITS*maxBits-1);
    random(&g,DIGITS*maxBits-1);
    uberzahl_init_long_u(&i,&g);
    uberzahl_a(&b,&h,&g);
    //c2 = ((unsigned long)a2)+b2;
    //uberzahl_a(&c,&a,&b);
    //d2 = ((unsigned long)a2)*b2;
    //uberzahl_m(&d,&a,&b);
    printf("%d: \n",i);
    uberzahl_print(&a,stdout);printf("\n");
    uberzahl_print(&b,stdout);printf("\n");
    uberzahl_m(&c,&a,&b);
    uberzahl_a_long_mut(&c,&i);
    longUberzahl_print(&c,stdout);printf("\n");
    uberzahl_d(&d,&e,&c,&b);
    longUberzahl_print(&d,stdout);printf("\n");
    uberzahl_print(&e,stdout);printf("\n");
    uberzahl_init_u_long(&f,&d);
    uberzahl_print(&g,stdout);printf("\n");
    assert(uberzahl_eq(&a,&f));
    assert(uberzahl_eq(&g,&e));
    
    //assert(c2 == ((((((((unsigned long)c.value[4]<<maxBits)+c.value[3])<<maxBits)+c.value[2])<<maxBits)+c.value[1])<<maxBits)+c.value[0]);
    //assert(d2 == ((((((((((((((unsigned long)d.value[7]<<maxBits)+d.value[6])<<maxBits)+d.value[5])<<maxBits)+d.value[4])<<maxBits)+d.value[3])<<maxBits)+d.value[2])<<maxBits)+d.value[1])<<maxBits)+d.value[0]);
  }*/
  /*uberzahl one,zero;
  uberzahl_init_i(&one,1);
  uberzahl_init(&zero);
  uberzahl n;
  random(&n,DIGITS*maxBits-1);
  if(n.value[0]%2==0)
    uberzahl_a(&n,&n,&one);
  uberzahl r;
  uberzahl_init_i(&r,1);
  int bits = 0;
  while(uberzahl_lt(&r,&n)) {
    uberzahl_ls_mut(&r,1);
    bits++;
  }
  uberzahl t,np;
  uberzahl_inverse(&t,&n,&r);
  uberzahl_s(&np,&r,&t);*/
  int num;
  uberzahl a,b,d,f;
  longUberzahl c,e;
//  uberzahl n,np;
  random(&RED_n,DIGITS*maxBits);
  random(&RED_Np,DIGITS*maxBits);
  for(num=0;num<100000;num++) {
    random(&a,DIGITS*maxBits);
    random(&b,DIGITS*maxBits);
    random(&d,DIGITS*maxBits);
    uberzahl_m(&c,&a,&b);
    uberzahl_d(&e,&f,&c,&d);
    //uberzahl_red(&d,&c,&n,DIGITS*maxBits-1,&np);
    //uberzahl_print(&a,stdout);printf("\n");
    //uberzahl_print(&d,stdout);printf("\n");
    //uberzahl_print(&n,stdout);printf("\n\n");
    //assert(uberzahl_eq(&d,&a));
  }
  //P4OUT = 0;
}