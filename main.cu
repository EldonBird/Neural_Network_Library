#include "Network.h"


__global__ void Vectoraddition(int* a, int* b, int* c, int n){

    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if(i < n){
        c[i] = a[i] + b[i];
    }
}

__global__ void calculate_outputs(double* last_activation, double* last_weight_inputs; double** weights, double* biases, double* last_inputs, double* inputs, double* outputs, int size_in, int size_out){

    for(int i = 0; i < size_in; i++){
        last_inputs[i] = inputs[i];
    }

    for(int x = 0; x < size_out; x++){
        double weighted_input = biases[x];
        for(int y = 0; y < size_in; y++){
            weighted_input += inputs[y] * weights[x][y];
        }
        last_weighted_inputs[x] = weighted_input;
        last_activation[x] = 1.0 / (1.0 + (-weighted_input * -weighted_input));
    }
}


int main(){

    int N = 10;
    size_t size = N * sizeof(float);


    float* h_A = (float*)malloc(size);
    float* h_B = (float*)malloc(size);
    float* h_C = (float*)malloc(size);

    float* d_A;
    cudaMalloc(&d_A, size);
    float* d_B;
    cudaMalloc(&d_B, size);
    float* d_C;
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    Vectoraddition<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);



    return 1;
}