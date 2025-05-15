//
// Created by eldon on 5/13/25.
//
#include <iostream>
#include <stdio.h>


#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;



int test;

int get_test() {
    return test;
}

int set_test(int* aa) {
    test = *aa;
}

class layer {
public:

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

private:
};

class network {

public:

    layer* start;
    int depth;

    network(layer *initial) {
       start = initial;
    }
    int* run(int* x) {
        return start->run(x);
    }
private:
};

int main(){

    return 1;

}

PYBIND11_MODULE(Eldon_Neural_Network, handle){

    handle.doc() = "module docs...?";
    handle.def("bindings_py", &main);

    py::class_<network>(handle, "Network")
            .def(py::init<const std::string&>())
            .def("getName", &network::getName)
            .def("bark", &network::bark);

    //py:class
    
}