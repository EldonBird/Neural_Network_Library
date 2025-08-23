#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <Layer.h>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

class Layer;
namespace py = pybind11;


class Network{
public:

    int* width;
    Layer* layers;

    Network(int* Layer_sizes, int* w) {

        width = w;
        Layer* l = new Layer[width];

        for (int i = 0; i < *width; i++) {
            l[i] = new Layer(Layer_sizes[i], Layer_sizes[i+1]);
        }
    }

    ~Network(){

        delete[] layers;
        free(width);
        
    }



    double* calculate_outputs(double* inputs) {
        double* result = inputs;
        
        for (int i = 0; i < *width; i++) {
            result = layers[i].calculate_outputs(inputs);
        }

        return result;
    }

    double cost_multiple(double* input, double* expected, int num) {

        double total = 0;

        for (int i = 0; i < num; i++) {
            total += cost(input[i], expected[i]);
        }
        
        
    }

    double cost(double input, double expected_output) {

        double* output = calcuate_output(input);
        Layer output_layer = layers[*width];
        double cost = 0;

        for (int out = 0; out < *width; out++) {
            cost += output_layer.node_cast(output[out], expected_output[out]);
        }

        return cost;
    }

};
