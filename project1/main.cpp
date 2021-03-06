#include <iostream>
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
    int start = clock();

    int flops = 0;  //floating point operator counter
    int n;          //matrix and array size
    double D;       //main diagonal numbers
    double E;       //secondary diagonal numbers
    double h;       //step length
    n = atoi(argv[1]);
    D = atoi(argv[2]);
    E = atoi(argv[3]);

    vec d(n);       //vector containing main diagonal numbers
    vec e(n-1);     //vector containing secondary diagonal numbers
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
    d.fill(D);
    e.fill(E);

    u(0) = 0;
    u(n-1) = 0;
    d_tilde[0] = d[0];
    f_tilde[0] = f[0];

    for(int i=1; i<n; i++){     //forwards substitution
        d_tilde[i] = d[i] - (e[i-1]*e[i-1])/d_tilde[i-1];
        flops += 3;
        f_tilde[i] = f[i] - (e[i-1]*f_tilde[i-1])/d_tilde[i-1];
        flops += 3;
    }

    u(n-2) = f_tilde(n-2)/d_tilde(n-2);
    flops += 3;
    for(int i=n-2; i>0; i--){   //backwards substitution
        u(i) = (f_tilde[i] - e[i]*u[i+1])/d_tilde[i];
        flops += 4;
    }

    vec cfs(n);
    for(int i=1; i<n; i++){
        cfs[i] = 1 - (1-exp(-10))*x[i] - exp(-10*x[i]);
    }
    ofstream myfile;
    string name = "pls" + to_string(n) + ".txt";
    myfile.open(name);

    for(int i = 0; i<n; i++){
        myfile << x[i] << "\t" << u[i] << "\t" << cfs[i] << "\n";
    }

    myfile.close();
    cout << "Program run time: "<<(clock()-start)/float(CLOCKS_PER_SEC)<< " seconds" << endl;

    return 0;
}
