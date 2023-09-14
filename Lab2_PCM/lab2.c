// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()



// user-defined header files
#include "mypcm.h"
#include "mypcm.c"


// function prototypes
void run(asignal * inputsignal);

int count, amplitude, levels;


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);

    //call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal *inputsignal)
{
    int encoderbits, interval;
    scanf("%f %f %f %d %d %d", &(inputsignal->A), &(inputsignal->omega), &(inputsignal->sigma), &(inputsignal->duration), &interval, &encoderbits);
    amplitude = inputsignal->A;

    count = inputsignal->duration / interval + 1;

    float *samples = (float *)malloc(count * sizeof(float));
    sampler(samples, interval, *inputsignal);

    // for (int i = 0; i < count; i++)
    // {
    //     printf("%f ", samples[i]);
    // }

    int *pcmpulses = (int *)malloc(count * sizeof(int));
    levels = (int)pow(2, encoderbits);
    quantizer1(samples, pcmpulses, levels);

    for (int i = 0; i < count; i++)
    {
        printf("%d ", pcmpulses[i]);
    }

    int noOfBits = count * encoderbits;
    int *dsignal = (int *)malloc(noOfBits * sizeof(int));
    encoder(pcmpulses, dsignal, encoderbits);

    for (int i = 0; i < noOfBits; i++)
    {
        printf("%d", dsignal[i]);
    }

    free(samples);
    free(pcmpulses);
    free(dsignal);
}

