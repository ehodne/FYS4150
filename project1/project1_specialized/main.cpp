#include <iostream>
#include <armadillo>
#include <fstream>
#include <ctime>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
    int start = clock();

    int flops = 0;  //floating point operator counter
    int n;          //matrix and array size
    double h;       //step length
    n = atoi(argv[1]);

    vec x;          //integration area
    vec f(n);       //known function
    vec d_tilde(n); //modified main diagonal
    vec f_tilde(n); //modified known functions
    vec u(n);       //unknown variables, want to find these

    x = linspace(0, 1, n);
    h = (x[n-1] - x[0])/n;
    flops += 2;

    f = h*h*100*exp(-10*x);
    flops += 4;

    u(0) = 0;
    u(n-1) = 0;
    d_tilde[0] = 2;
    f_tilde[0] = f[0];

    vec cfs(n);
    cfs = 1 - (1-exp(-10))*x - exp(-10*x);

    for(double i=1; i<n; i++){     //forwards substitution
        d_tilde[i] = (i+1)/i;
        flops += 2;
        f_tilde[i] = f[i] + f_tilde[i-1]/d_tilde[i-1];
        flops += 2;
    }

    u(n-2) = f_tilde(n-2)/d_tilde(n-2);
    flops += 1;
    for(int i=n-2; i>0; i--){   //backwards substitution
        u(i) = (f_tilde[i] + u[i+1])/d_tilde[i-1];
        flops += 2;
    }

    vec error(n);
    error = log10( abs( (u - cfs)/cfs ) );
    error[0] = error[1];
    //cout << error;

    mat A(n,n);
    A(0,0) = 2;

    for(int i=1; i<n; i++){
        A(i,i) = 2;
        A(i,i-1) = -1;
        A(i-1,i) = -1;
    }
    cout << A << endl;



    ofstream myfile;
    string name = "pls_special" + to_string(n) + ".txt";
    myfile.open(name);

    for(int i = 0; i<n; i++){
        myfile << x[i] << "\t" << u[i] << "\t" << cfs[i] << "\t" << error[i] << "\n";
    }

    myfile.close();

    cout << "Program run time: "<<(clock()-start)/float(CLOCKS_PER_SEC)<< " seconds" << endl;

    cout << "FLOPS:" << flops;
    return 0;
}
