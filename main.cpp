#include <iostream>
#include <stdio.h>
#include <pybind11/pybind11.h>

PYBIND11_MODULE(simple_module, m) {
    m.def("simple_cpp_function", &simple_cpp_function);
}

struct layer {

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
    
    layer* previous;
    layer* next;

    int size;
    int* bias;
    int** weight;
    // int* x; riding myself of this, the inputs are taken at runtime instead, they are recersibly applied through the function and carried along, use them in teh funciton call instead

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



int* neural_net_3(int* x, int size_x, int* x_bias, int** w1, int size_a, int* a_bias, int** w2, int size_r) {

    int* a = new int[size_a];

    for (int i = 0; i < size_a; i++) {
        a[i] = 0;

        for (int j = 0; j < size_x; j++) {

            a[i] += x[j] * w1[i][j];
        }
        a[i] += x_bias[i];
    }

    int* r = new int[size_r];

    for (int i = 0; i < size_r; i++) {

        r[i] =0;

        for (int j = 0; j < size_a; j++) {

            r[i] += a[j] * w2[i][j];
        }
        r[i] += a_bias[i];
    }

    return r;

}