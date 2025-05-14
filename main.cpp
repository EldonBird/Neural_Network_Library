#include <iostream>
#include <stdio.h>

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
