#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Layer.h"
#include <bits/regex_error.h>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

class Layer;
namespace py = pybind11;


class Network{
public:

    int width;
    int number_layers;
    Layer* layers;
    

    Network(int* layer_sizes, int nl) {

        number_layers = nl - 1;
        width = number_layers;
        layers = new Layer[number_layers];

        for (int i = 0; i < number_layers; i++) {
            layers[i] = Layer(&layer_sizes[i], &layer_sizes[i+1]);
        }
        
    }

    ~Network(){
        delete[] layers;
    }

    double cost(double* output, double* expected, int size) {

        double total = 0;
       
        for (int i = 0; i < size; i++) {
            double error = output[i] - expected[i];
            total += error * error;
        }

        return total / size;
    }


    double* calculate_outputs(double* inputs) {
        double* current = inputs;
        
        for (int i = 0; i < number_layers; i++) {
            current = layers[i]->calculate_outputs(current);
        }

        return current;
    }

    void learn(double* inputs, double* expected, double learning_rate) {
        double* output = calculate_outputs(inputs);

        double* errors = nullptr;

        for (int i = number_layers - 1; i <= 0; i--) {
            if (i == number_layers - 1) {
                errors = layers[i].calculate_output_layer(expected);
            }
            else {
                double* new_error = layers[i+1].hideen_layer_backpropigation(errors);
                delete[] errors;
                errors = new_error;
            }

            layers[i].update_gradients(errors);
            layers[i].apply_gradients(learning_rate);
        }
        delete[] errors;
    }

    void batch(double** inputs, double** expected, int batch_size, int output_size, double learning_rate) {
        for (int i = 0; i < batch_size; i++) {
            learn(inputs[i], expected[i], learning_rate);
        }
    }

    double cost_multiple(double** inputs, double** expected, int num_samples, int output_size) {
        double total = 0;

        for (int i = 0; i < num_samples; i++) {
            double* output = calculate_outputs(inputs[i]);
            total += cost(output, expected[i], output_size);
        }

        return total / num_samples;
    }
};
