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
        layers = new Layer[*width];

        for (int i = 0; i < *width; i++) {
            layers[i] = new Layer(&Layer_sizes[i], &Layer_sizes[i+1]);
        }
        
    }

    ~Network(){

        delete[] layers;
        delete width;
        
    }

    double cost(double* output, double* expected, int size) {

        double* total = 0;
       
        for (int i = 0; i < *width; i++) {
            double error = output[i] - expected[i];
            total += error * error;
        }

        return total;
    }


    double* calculate_outputs(double* inputs) {
        double result = *inputs;
        
        for (int i = 0; i < *width; i++) {
            result = layers[i].calculate_outputs(inputs);
        }

        return &result;
    }

    double cost_multiple(double* input, double* expected, int num) {

        double total = 0;

        for (int i = 0; i < num; i++) {
            total += cost(input[i], expected[i]);
        }
        
        return total;
    }

    

    

};
