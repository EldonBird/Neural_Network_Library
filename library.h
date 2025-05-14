#ifndef NEURAL_NETWORK_LIBRARY_H
#define NEURAL_NETWORK_LIBRARY_H


struct layer {
    struct layer* previous;
    struct layer* next;

    int size;
    int* bias;
    int** weight;
};

struct network {
    struct layer* start;
    int depth;
};

int* run_network(struct network* net, int* x);

#endif //NEURAL_NETWORK_LIBRARY_H