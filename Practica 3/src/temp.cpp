#include <iostream>

int main (  ) { 

    int w, x, y , z;
    int i = 3; int j = 4;
    {
        int i = 5;
        w = i + j;
    }
    x = i + j;
    {
        int j = 6;
        i = 7;
        y = i + j;
    }
    z = i + j;

    std::cout << "i " << i << "\n";
    std::cout << "j " << j << "\n";
    std::cout << "w " << w << "\n";
    std::cout << "x " << x << "\n";
    std::cout << "y " << y << "\n";
    std::cout << "z " << z << "\n";



}