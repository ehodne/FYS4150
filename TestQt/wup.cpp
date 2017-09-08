#include <iostream>
#include <stdio.h>
#include <cmath>
#include <fstream>

using namespace std;

std::ofstream ofile;

double f(double x){
    double arc = atan(x);
    return arc;
}

int main(){
    double x = sqrt(2.0);
    int N = 10000;
    double h[N];
    double fder2c[N];
    double fder3c[N];
    double epsilon2c[N];
    double epsilon3c[N];
    int i;

    for(i=1; i<N; i++){
        h[i] = 1.0/(i*10);
        fder2c[i] = (f(x + h[i]) - f(x))/h[i];
        fder3c[i] = (f(x + h[i]) - f(x - h[i]))/(2*h[i]);

        epsilon2c[i] = log(abs( (fder2c[i] - 1.0/3)/(1.0/3) ));
        epsilon3c[i] = log(abs( (fder3c[i] - 1.0/3)/(1.0/3) ));
    }

    ofile.open("errors.txt", std::ios::out);
    for (i=1; i<N; i++){
        ofile << h[i] << " " << fder2c[i] << " " << fder3c[i] << " " << epsilon2c[i] << " " << epsilon3c[i] << endl;

    }
    ofile.close();
    return 0;
}
