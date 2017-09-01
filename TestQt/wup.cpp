#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

double f(double x){
    double arc = atan(x);
    return arc;
}

int main(){
    double x = sqrt(4);
    int N = 100;
    double h[100];

    for(i=1; i<N; i++){
        h[i] = 1.0/i

    }
    double fder2c = (f(x + h) - f(x))/h;
    double fder3c = (f(x + h) - f(x - h))/(2*h);

    cout << fder2c << " " << fder3c << endl;
    return 0;
}

