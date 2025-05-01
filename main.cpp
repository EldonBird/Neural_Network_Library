#include <iostream>
#include <stdio.h>

struct connected_network {
    int x[];
    int w1[][];
    int a[];
    int w2[][];
    int b;

};





// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
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