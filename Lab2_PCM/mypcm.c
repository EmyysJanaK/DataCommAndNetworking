// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
extern int count,amplitude,levels;

float analog_signal_generator(asignal signal, int t)
{
    //TODO
    float sinVal = sin(signal.omega * t + signal.sigma);
    return signal.A*sinVal;
}
void sampler(float *samples, int interval, asignal signal)
{
    //TODO
    for (int i = 0; i < count; i++){
        samples[i] = analog_signal_generator(signal,i*interval);
    }
}
void quantizer1(float *samples, int *pcmpulses, int levels)
{
    //TODO
    for (int i =0;i < count; i++){
        pcmpulses[i] = (int) floorf(samples[i] + amplitude)*levels / (2*amplitude);
    }

}
/*void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
    //TODO
}*/
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
    //TODO
    for (int j = 0; j < count; j++){
        for(int i = encoderbits - 1; i >= 0; i--){
            int k = *(pcmpulses + j) >> i;
            if ( k & 1)
                *dsignal =1;
            else
                *dsignal = 0;
            dsignal++;
        }
    }
    dsignal -= count*encoderbits;
}