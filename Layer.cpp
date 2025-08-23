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

    double** cost_gradient_w;
    double* cost_gradient_b;

    Layer(int* si, int* so) {

        size_in = si;
        size_out = so;
        
        biases = new double[*size_out];

        cost_gradient_b = new double[*size_out];
        
        weights = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ weights[i] = new double[*size_out]; }

        cost_gradient_w = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ cost_gradient_w[i] = new double[*size_out]; }

    }

    Layer(int* si, int* so, double* b, double** w) {

        size_in = si;
        size_out = so;
        biases = b;
        weights = w;

        cost_gradient_b = new double[*size_out];
        cost_gradient_w = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ cost_gradient_w[i] = new double[*size_out]; }
    }


    ~Layer(){

        delete[] biases;
        delete[] cost_gradient_b;
        for (int i = 0; i < *size_out; i++) { delete[] weights[i]; } delete[] weights;
        for (int i = 0; i < *size_out; i++) { delete[] cost_gradient_w[i]; } delete[] cost_gradient_w;
        delete size_in;
        delete size_out;

    }

    void start_with_random_weights() {


        for (int x = 0; x < *size_in; x++) {
            for (int y = 0; y < *size_out; y++) {

                double rng = ((double) rand() / RAND_MAX) * 2.0 - 1.0;

                weights[x][y] = rng / sqrt(*size_in);
                
            }
        }

        
    }

    void apply_gradients(double learn_rate) {

        for (int i = 0; i < *size_out; i++) {
            biases[i] -= cost_gradient_b[i] * learn_rate;
            for (int j = 0; j < *size_in; j++) {
                weights[i][j] -= cost_gradient_w[i][j] * learn_rate;
            }
        }
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




