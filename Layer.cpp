#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


class Layer {

public:

    double* biases;
    double** weights;
    int* size_in;
    int* size_out;

    Layer(int* si, int* so) {

        size_in = si;
        size_out = so;
        
        biases = new double[*size_out];
        
        weights = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ weights[i] = new double[*size_out]; }

    }


    ~Layer(){

        delete[] biases;
        for (int i = 0; i < *size_out; i++) { delete[] weights[i]; } delete[] weights;
        free(size_in);
        free(size_out);

    }

    double* calculate_outputs(double* inputs) {

        double* activations = new double[*size_out];

        for (int x = 0; x < *size_out; x++) {

            double weighted_input = biases[x];
            for (int y = 0; y < *size_in; y++) {
                weighted_input += inputs[y] * weights[x][y];
            }
            activations[x] = activation_function(weighted_input);
        }
        return activations;
    
    }

    double activation_function(double weighted_input) {
        return 1 / (1 + exp(-weighted_input));
    }

    double node_cost(double output_activation, double expected_output) {
        double error = output_activation - expected_output;
        return error * error;
    }

};




