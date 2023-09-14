#include <stdlib.h>
#include <math.h>

// function prototypes
void run(asignal * inputsignal);

// Implement functions here

extern int count,amplitude,levels;

/**
 * Generates an analog signal.
 *
 * @param signal The signal to generate.
 * @param t The time at which to generate the signal.
 * @return The value of the signal at time t.
 */
float analog_signal_generator(asignal signal, int t)
{
    //TODO
    float sinVal = sin(signal.omega * t + signal.sigma);
    return signal.A*sinVal;
}

/**
 * Samples an analog signal.
 *
 * @param samples The array to store the sampled values.
 * @param interval The sampling interval.
 * @param signal The analog signal to sample.
 */
void sampler(float *samples, int interval, asignal signal)
{
    //TODO
    for (int i = 0; i < count; i++){
        samples[i] = analog_signal_generator(signal,i*interval);
    }
}

/**
 * Quantizes a sampled signal.
 *
 * @param samples The array of sampled values.
 * @param pcmpulses The array to store the quantized values.
 * @param levels The number of quantization levels.
 */
void quantizer1(float *samples, int *pcmpulses, int levels)
{
    //TODO
    for (int i =0;i < count; i++){
        pcmpulses[i] = (int) floorf(samples[i] + amplitude)*levels / (2*amplitude);
    }

}

/**
 * Encodes a quantized signal.
 *
 * @param pcmpulses The array of quantized values.
 * @param dsignal The array to store the encoded signal.
 * @param encoderbits The number of bits per encoded symbol.
 */
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

/**
 * The main function.
 */
int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

/**
 * Runs the program.
 *
 * @param inputsignal The input signal.
 */
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
