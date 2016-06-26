#include <SevenSeg.h>


int a= 7 , b=8 , c=9 , d= 10, e=11 ,f=12 , g=13;   
int  i = 0 ;
SevenSeg seg = SevenSeg ( a, b, c, d, e, f, g );
void setup() {

  seg.setCommonAnode();
  //seg.setCommonCathode();
  
}

void loop() {

  /*for(int i = 0 ; i < 10 ; i++  )
  {
    seg.writeDigit(i);
    delay(1000);
    }
  */
  seg.writeDigit(i);
    delay(1000);
     i++ ;
     if (i == 10)
     {
      i = 0 ;
      }
 
  
}
