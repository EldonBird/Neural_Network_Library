#include <complex>
#include <iostream>
#include <stdio.h>
#include "Network.h"

int main() {

    int layer_sizes[] = {3, 5, 2};

    Network network(layer_sizes, 3);

    double input1[] = {0.5, 0.3, 0.8};
    double expected1[] = {0.5, 0.3, 0.8};

    double input2[] = {0.1, 0.7, 0.8};
    double expected2[] = {0.2, 0.8};

    double learning_rate = 0.001;

    for (int i = 0; i < 1000; i++) {
        network.learn(input1, expected2, learning_rate);
        network.learn(input2, expected2, learning_rate);

        if (i % 100 == 0) {
            double* output1 = network.calculate_outputs(input1);
            double* output2 = network.calculate_outputs(input2);

            double cost1 = network.cost(output1, expected1, 2);
            double cost2 = network.cost(output2, expected2, 2);

            std::cout << "i " << i << "- cost: " << (cost1+cost2) / 2 << std::endl;
        }
    }

    return 1;
}
