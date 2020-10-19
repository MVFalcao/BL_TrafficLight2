#include "mbed.h"

enum states{RED, GREEN, YELLOW , BLINK}; //States enumeration
int state = RED; // Defining first state as green
PwmOut lights[]={(p5), (p6), (p7)}; //LED ports definition, associated with the enum
float times[] = {10.0, 20.0, 4.0}; // States timing definition, associated with the enum
InterruptIn bt_pedestrian (p8); // Buttom interrupt object
Timeout timeout; // State timer object
Ticker btt;
int i = 0;
int previous;

//***Function prototypes***
void BtCall();
void clear_all ();
void transition();
void calloff();
void count();

int main() {
    lights[state] = 1.0; // Turning on the first state
    bt_pedestrian.rise(&BtCall); // Defining buttom interrupt behavior and function
    bt_pedestrian.fall(&calloff);
    timeout.attach (&transition, times[state]); // Defining state timing interruption
}
void calloff(){
    btt.detach();
    i = 0;
}
void BtCall(){
    btt.attach(&Count, 1.0);
    if (state == GREEN || i =< 3){
        transition();
        timeout.attach (&transition, times[state]);
    }else if(i >= 3 && i <= 10){
        if(previous == -1){
            previous = state;
            state = BLINK;
        }else{
            state = previous;
        }
    }else if(i > 10){
        if(state != -1){
            state = -1;
        }else{
            state = RED;
        }
    }
}
void count(){
	i++;
}
void alert(){
    lights[YELLOW] = 1.0;
    wait(1000);
    lights[YELLOW] = 0.0;
}
void clear_all (){
    int j;
    for(j=0;j<3;j++){
         lights [j]=0;
        }
 }

void transition(){
       clear_all ();
       if (state != 3){
           state++;
       }
       else {
           state =0;
       }
       if(state == BLINK){
           alert();
       }
       lights[state] = 1;
       timeout.attach (&transition, times[state]);
    }
