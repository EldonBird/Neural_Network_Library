#include <cstdlib>
#include <iostream>
#include <stdio.h>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


class layer {

    int* size;
    int* biases;
    int** weights;

    layer(int s, int* b, int** w) {

        size = s;
        biases = b;
        weights = w;

    }


    ~layer(){

        free(size);
        free(biases);
        free(weights);

    }

};


void* run(layer layer1, layer layer2) {




}

