#include <stdlib.h>
#include <math.h>

// function prototypes
void run(asignal * inputsignal);

// Implement functions here

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


//-------------------------------------------------------------

int count, amplitude, levels;

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
	//todo
	 int encoderbits, interval;
    scanf("%f %f %f %d %d %d", &(inputsignal->A), &(inputsignal->omega), &(inputsignal->sigma), &(inputsignal->duration), &interval, &encoderbits);
    amplitude = inputsignal->A;

    count = inputsignal->duration / interval + 1;

    float *samples = (float *)malloc(count * sizeof(float));
    sampler(samples, interval, *inputsignal);

    int *pcmpulses = (int *)malloc(count * sizeof(int));
    levels = (int)pow(2, encoderbits);
    quantizer1(samples, pcmpulses, levels);

    int noOfBits = count * encoderbits;
    int *dsignal = (int *)malloc(noOfBits * sizeof(int));
    encoder(pcmpulses, dsignal, encoderbits);

    if (dsignal != NULL) {
        for (int i = 0; i < noOfBits; i++)
        {
            printf("%d", dsignal[i]);
        }
    }

    free(samples);
    free(pcmpulses);
    free(dsignal);
}
