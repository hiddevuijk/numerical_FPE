#ifndef GUARD_FLUX_H
#define GUARD_FLUX_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class XY{
public:
    XY():x(0), y(0) {}
    XY(double x, double y): x(x), y(y) {}

    double x,y;
};

class DensityFlux{
public:
 
    DensityFlux(int N, double L, double dt, double D)
        : N(N), L(L), dt(dt), D(D),
          P(std::vector<std::vector<double> >(N, std::vector<double>(N,0)) ),
          J(std::vector<std::vector<XY> >(N, std::vector<XY> (N,XY(0,0)) ) )
        { d = L/N; d2i = 1./(2*d); P[N/2][N/2]=L*L; }     

    void update_flux();
    void update_density();
    void save_flux(std::string name);
    void save_density(std::string name);

    int N;
    double L;
    double dt;
    double D;

    std::vector<std::vector<XY> > J;
    std::vector<std::vector<double> > P;

    double d;
    double d2i;
};


void DensityFlux::update_flux()
{
    double xip1, xim1, yip1, yim1;

    for(int xi=0; xi<N; ++xi) {
        for(int yi=0; yi<N; ++yi) {
            xip1 = xi == N-1 ? 0 : xi+1;
            //xim1 = xi == 0 ? N-1 : xi-1;
            yip1 = yi == N-1 ? 0 : yi+1;
            //yim1 = yi == 0 ? N-1 : yi-1;
            J[xi][yi].x = -D*d2i*( P[xip1][yi] - P[xi][yi] );
            J[xi][yi].y = -D*d2i*( P[xi][yip1] - P[xi][yi] );
            
        }
    }


}

void DensityFlux::update_density()
{
    double xip1, xim1, yip1, yim1;
    for(int xi=0;xi<N; ++xi) {
        for(int yi=0; yi<N; ++yi) {
            //xip1 = xi == N-1 ? 0 : xi+1;
            xim1 = xi == 0 ? N-1 : xi-1;
            //yip1 = yi == N-1 ? 0 : yi+1;
            yim1 = yi == 0 ? N-1 : yi-1;
            P[xi][yi] -= dt*( J[xi][yi].x - J[xim1][yi].x 
                             +J[xi][yi].y - J[xi][yim1].y );
        }
    }
}

void DensityFlux::save_density(std::string name)
{
    std::ofstream out(name.c_str());
    for(int xi=0;xi<N;++xi) {
        for(int yi=0;yi<N;++yi) {
            out << P[xi][yi];
            if(yi<(N-1)) out << '\t';
        }
        if(xi<(N-1) ) out << '\n';
    }
}

#endif
