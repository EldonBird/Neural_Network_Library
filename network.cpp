#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <layer.h>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


class network{

    layer *layers;

    network() {

    }

    ~network(){

    }

};

int* run(layer layer1, layer layer2){

    int* y = new int[layer2->size];

    for(int i = 0; i < layer2->size; i++){

        for(int j = 0; j < layer1->size; j++){

            y[i] += layer1[

        }

    }



}


void* test(){

}
