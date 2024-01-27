#include<iostream>
#include<vector>
#include<cmath>

#define DEBUG

#define AIR_RESISTANCE

#ifdef DEBUG
#endif

using std::endl;
using std::cout;
using std::vector;

template <typename T>
struct Pair {
    T x;
    T y;
    Pair<T> (const T& a, const T& b): x(a), y(b) /*todo*/ {
        #ifdef DEBUG
        cout << "Pair created " << *this << endl;
        #endif
    }
    ~Pair<T> () {
        cout << "Pair destroyed" << endl;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Pair<T>& pair) {
    os << "(" << pair.x << ", " << pair.y << ")";
    return os;
}

struct Particle {
    Pair<double> * arrays[3];
    
    public:
        //Particle(Pair<double> pos, Pair<double> arrays[VEL]);  Zusatz, freiwillig. Vgl. Würfe aus dem Physikunterricht.
        Particle(const Pair<double>& pos);
        Particle(const Pair<double>& pos, const Pair<double>& vel, const Pair<double>& acl);
        ~Particle();

        int POS = 0;
        int VEL = 1;
        int ACL = 2;
        static unsigned int counter;
        //friend void Simulation::update(void);
};

Particle::Particle(const Pair<double>& pos) {
    //todo
    //increase counter
    Particle::counter += 1;

    arrays[POS] = new Pair<double>(pos);
    arrays[VEL] = new Pair<double>(0,0);//todo;
    arrays[ACL] = new Pair<double>(0,0);//todo;

    cout << "Particle created at arrays[POS] " << pos << endl;
}

Particle::Particle(const Pair<double>& pos, const Pair<double>& vel, const Pair<double>& acl) {
        //todo
    //increase counter
    Particle::counter += 1;

    arrays[POS] = new Pair<double>(pos);
    arrays[VEL] = new Pair<double>(vel);//todo;
    arrays[ACL] = new Pair<double>(acl);//todo;

    cout << "Particle created at arrays[POS] " << pos << "with values" << vel << acl << endl;
}



Particle::~Particle() {
    //deallocate correctly!
    delete arrays[POS];
    delete arrays[VEL];
    delete arrays[ACL];

    Particle::counter -= 1;

    cout << "Particle destroyed. " << counter << " particles left." << endl;
    
}


class Simulation {
    std::vector<Particle*> p_array;
    double timestep;
    
    const double g = 10.0;

    const double c_air = 0.05;

    public:
        Simulation();
        Simulation(double t);

        void addParticle(const Particle& particle);

        void operator += (Particle p);
        void operator -= (Particle p);

        void update();
        void setTimestep(const double& t);
};

Simulation::Simulation() {
    timestep = 0.02;
    p_array.reserve(5);
}

Simulation::Simulation(double t) {
    timestep = t;
    p_array.reserve(5);
}

void Simulation::addParticle(const Particle& particle) {
    Particle* p = new Particle(particle);  // Assuming Particle has a copy constructor
    p->arrays[particle.ACL]->y = -g;
    p_array.push_back(p);
}


void Simulation::update() {
    int POS = 0;
    int VEL = 1;
    int ACL = 2;

    for (vector<Particle*>::iterator p_i = p_array.begin(); p_i != p_array.end(); p_i++) {
        cout << "Particle at " << *((*p_i)->arrays[POS]) << endl;

        (*p_i)->arrays[POS]->x += timestep * (*p_i)->arrays[VEL]->x;
        (*p_i)->arrays[POS]->y += timestep * (*p_i)->arrays[VEL]->y;

        (*p_i)->arrays[VEL]->x += timestep * (*p_i)->arrays[ACL]->x;
        (*p_i)->arrays[VEL]->y += timestep * (*p_i)->arrays[ACL]->y;


        //(*p_i)->arrays[ACL]->x = 0; //provisorisch
        //(*p_i)->arrays[ACL]->y = -g;

        if ((*p_i)->arrays[POS]->y <= 0.00) {
            delete (*p_i);
        }

    }
}

void Simulation::setTimestep(const double& t) {
    timestep = t;
}