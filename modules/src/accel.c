#include <stdio.h>

#include <intelfpgaup/accel.h>

int main()
{

printf("print aleatorio");
int a=1;
int b=2;
int c;
int d=0;
float rate = 0.78;
int e;
int ptr_x;
int ptr_y;
int ptr_z;
int ptr_ready;
int ptr_tap;
int ptr_dtap;
int ptr_msg;
    int retorno[6];
   
    accel_open();
   
    accel_init();
   
    accel_format(a, b);
    //accel_rate(rate);
    accel_calibrate();

while(d<10){
d++;
accel_read(&ptr_ready, &ptr_tap, &ptr_dtap, &ptr_x, &ptr_y, &ptr_z, &ptr_msg);
    //accel_device();
    printf("valor %d \n" , ptr_x);
sleep(1);
}
   
    printf("print aleatorio");
    accel_close();
   
return 0;
}
