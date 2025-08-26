#ifndef LAYER_H
#define LAYER_H

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


    Layer(int* si, int* so);
    
    ~Layer();

    void start_with_random_weights();
    void apply_gradients(double learn_rate);
    double* calculate_outputs(double* inputs);
    
    double activation_function(double weighted_input);
    double activation_function_derivative(double weighted_input);
    
    double node_cost(double output_activation, double expected_output);
    double* hidden_layer_backpropigation(double* next_layer_errors);
    void update_gradient(double* errors);
    double* calculate_output_layer(double* expected_outputs);
};

#endif