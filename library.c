#include "library.h"

#include <stdio.h>
#include <malloc.h>


int* run_layer(struct layer* current, int* x) {
    if (current->next == NULL) return NULL;

    int* y = (int*)malloc(sizeof(int) * current->next->size);
    for (int i = 0; i < current->next->size; i++) {
        y[i] = 0;
        for (int j = 0; j < current->size; j++) {
            y[i] += x[j] * current->weight[i][j];
        }
        y[i] += current->bias[i];
    }

    if (current->next->next == NULL) {
        return y;
    } else {
        return run_layer(current->next, y);
    }
}


int* run_network(struct network* net, int* x) {
    return run_layer(net->start, x);
}
