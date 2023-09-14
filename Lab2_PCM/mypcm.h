/*
	You can modify this file for your testing purpose 
	but note that we will use our own copies of this file for testing during grading 
	so changes in this file will be overwritten
*/

typedef struct {
	float A;
	float omega;
    float sigma;
    int duration;
} asignal;

// function prototypes
float analog_signal_generator(asignal signal, int t);
void sampler(float *samples, int interval, asignal signal);
void quantizer1(float *samples, int *pcmpulses, int levels);
void quantizer(float *samples, int *pcmpulses, int levels, float A);
void encoder(int *pcmpulses, int *dsignal, int encoderbits);

