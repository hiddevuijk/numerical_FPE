#ifndef GUARD_DENSITY_H
#define GUARD_DENSITY_H

#include <vector>

#include "flux.h"

class Density{
public:

    Density(int N, double L, double dt) : N(N), L(L), dt(dt),
        P(std::vector<std::vector<double> >(N,
            std::vector<double>(N,0)) )
        { d=L/N; d2i=1./(2*d); P[N/2][N/2]=L*L; }

    double operator() (int xi, int yi) const { return P[xi%N][yi%N]; }

    template<class F>
    void update( const Flux& flux );

    int N;
    double L;
    double dt;
    std::vector<std::vector<double> > P;

    double d;
    double d2i;
    

};


template<class F>
void Density::update( const F& flux )
{

    for(int xi;xi<N; ++xi) {
        for(int yi; yi<N; ++yi) {
           P[xi][yi] -= dt*(flux(xi+1, yi).x + flux(xi, yi+1).y -
                            flux(xi-1, yi).x - flux(xi, yi-1).y ) 
        }
    }
}


#endif
