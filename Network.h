
#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"

class Network {
public:
    int* width;
    Layer* layers;
    int num_layers;

    Network(int* layer_sizes, int num_layers_param);
    
    ~Network();

    double* calculate_outputs(double* inputs);
    double cost(double* output, double* expected, int size);
    double cost_multiple(double** inputs, double** expected_outputs, int num_samples, int output_size);

    void learn(double* inputs, double* expected_outputs, double learning_rate);
    void batch(double** inputs, double** expected_outputs, int batch_size, int output_size, double learning_rate);
};

void example_usage();

#endif