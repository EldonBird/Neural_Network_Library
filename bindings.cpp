//
// Created by eldon on 5/13/25.
//
#include <iostream>
#include <stdio.h>


#include <pybind11/pybind11.h>

namespace py = pybind11;

struct layer {

    layer* previous;
    layer* next;

    int size;
    int* bias;
    int** weight;
    // int* x; riding myself of this, the inputs are taken at runtime instead, they are recersibly applied through the function and carried along, use them in teh funciton call instead


    layer(layer* prev, layer* n, int s, int* b, int** w) {

        previous = prev;
        next = n;

        size = s;
        bias = b;
        weight = w;

    }

    int* run(int* x) {

        int* y = new int[next->size];

        for (int i = 0; i < next->size; i++) {
            for (int j = 0; j < size; j++) {
                y[i] += x[j] * weight[i][j];
            }
            y[i] += bias[i];
        }

        if (next == nullptr) {
            return y;
        }
        else {
            return next->run(y);
        }

    }



};

struct network {

    layer* start;
    int depth;

    network(layer *initial) {
       start = initial;
    }

    int* run(int* x) {

        return start->run(x);

    }


};

int main(){

    int* test = new int[10];
    for (int i = 0; i < 10; i++) {
        test[i] = 0 + i;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << test[i] << std::endl;
    }

    std::cout << test[0] << std::endl;
    std::cout << test << std::endl;
    std::cout << &test << std::endl;
    std::cout << &test[0] << std::endl;

}

PYBIND11_MODULE(module_name, handle){

    handle.doc() = "module docs...?";
    handle.def("bindings_py", &main);
}