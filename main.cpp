#include <iostream>
#include <vector>
#include <string>

#include "density_flux.h"

using namespace std;


int main()
{
    int N = 100;
    double L = 10;
    double dx = L/N;
    double dt = 0.001;
    double D = 4.;
    cout << 2*dt/(dx*dx*D) << endl;
    DensityFlux rhoJ(N, L,dt ,D);
    for(int i=0; i<1000; ++i) {
        rhoJ.update_flux();
        rhoJ.update_density();
    }
    cout << rhoJ.P[4][5] << endl;
    rhoJ.save_density("rho.dat");
    return 0;
}
