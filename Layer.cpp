#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>





class Layer {

public:

    double* biases;
    double** weights;
    int* size_in;
    int* size_out;

    double** cost_gradient_w;
    double* cost_gradient_b;

    double* last_inputs;
    double* last_activations;
    double* last_weighted_inputs;

    Layer(int* si, int* so) {

        size_in = si;
        size_out = so;
        
        biases = new double[*size_out];
        last_activations = new double[*size_out];
        last_weighted_inputs = new double[*size_out];
        last_inputs = new double[*size_in];
        cost_gradient_b = new double[*size_out];
        
        weights = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ weights[i] = new double[*size_out]; }

        cost_gradient_w = new double*[*size_in];
        for (int i = 0; i < *size_in; i++){ cost_gradient_w[i] = new double[*size_out]; }

        start_with_random_weights();

    }
    Layer() {
        
    }


    ~Layer(){

        delete[] biases;
        delete[] cost_gradient_b;
        delete[] last_activations;
        delete[] last_weighted_inputs;
        delete[] last_inputs;
        for (int i = 0; i < *size_out; i++) { delete[] weights[i]; } delete[] weights;
        for (int i = 0; i < *size_out; i++) { delete[] cost_gradient_w[i]; } delete[] cost_gradient_w;
        delete size_in;
        delete size_out;

    }

    void start_with_random_weights() {
        for (int x = 0; x < *size_in; x++) {
            for (int y = 0; y < *size_out; y++) {
                double rng = ((double) rand() / RAND_MAX) * 2.0 - 1.0;
                weights[x][y] = rng / sqrt(*size_in);
            }
        }

        for (int i = 0; i < *size_out; i++) {
            biases[i] = ((double) rand() / RAND_MAX) * 0.1 - 0.05;
        }
    }

    void apply_gradients(double learn_rate) {

        for (int i = 0; i < *size_out; i++) {
            biases[i] -= cost_gradient_b[i] * learn_rate;
            for (int j = 0; j < *size_in; j++) {
                weights[i][j] -= cost_gradient_w[i][j] * learn_rate;
            }
        }
    }

    double* calculate_outputs(double* inputs) {

        for (int i = 0; i < *size_in; i++) {
            last_inputs[i] = inputs[i];
        }
        for (int x = 0; x < *size_out; x++) {
            double weighted_input = biases[x];
            for (int y = 0; y < *size_in; y++) {
                weighted_input += inputs[y] * weights[x][y];
            }
            last_weighted_inputs[x] = weighted_input;
            last_activations[x] = activation_function(weighted_input);
        }

        return last_activations;
    }

    double activation_function(double weighted_input) {
        return 1.0 / (1.0 + exp(-weighted_input));
    }

    double activation_function_derivative(double weighted_input) {

        double sigmoid = activation_function(weighted_input);
        return sigmoid * (1.0 - sigmoid);
        
    }

    double node_cost(double output_activation, double expected_output) {
        double error = output_activation - expected_output;
        return error * error;
    }

    double* hidden_layer_backpropigation(double* next_layer_error) {
        double* error = new double[*size_in];
        for (int i = 0; i < *size_in; i++ ) {
            error[i] = 0;
            for (int j =0; j < *size_out; j++) {
                error[i] += weights[i][j] * next_layer_error[j];
            }
        }

        return error;
        
    }

    void update_gradient(double* errors) {

        for (int i = 0; i < *size_out; i++) {
            double node_error = errors[i] * activation_function_derivative(last_weighted_inputs[i]);

            cost_gradient_b[i] = node_error;
            for (int j = 0; j < *size_in; j++) {
                cost_gradient_w[j][i] = last_inputs[j] * node_error;
            }
        }

        
    }

    double* calculate_output_layer(double* expected_outputs) {
        double* errors = new double[*size_in];

        for (int i = 0; i < *size_out; i++) {
            double cost_d = 2.0 * (last_activations[i] - expected_outputs[i]);
            errors[i] = cost_d * activation_function_derivative(last_weighted_inputs[i]);
        }

        return errors;
    }

};




