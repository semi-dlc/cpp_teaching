#include<iostream>
#include"Particle.hpp"


using namespace std;


unsigned int Particle::counter = 0;
int main() {
    Simulation sim;

    Particle p1 = Particle(Pair<double>(0,10));
    Particle p2 = Particle(Pair<double>(1,7));
    Particle p3 = Particle(Pair<double>(1,3));
    sim.addParticle(p1);
    sim.addParticle(p2);
    sim.addParticle(p3);

    while(Particle::counter > 0) {
        cout << "Counter: " << Particle::counter << endl;
        sim.update();
    }

    return 0;

}