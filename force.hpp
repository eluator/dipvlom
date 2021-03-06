#ifndef FORCE
#define FORCE

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <functional>
#include<vector>
#include<iterator>

#include<iostream>

#include"basic_types.hpp"
#include"functions.hpp"

using namespace boost::numeric::ublas;


typedef double data_type;
typedef vector<data_type> state_vector;

struct Body_t;
struct masspt_t;
struct Body_position_t;

struct Force_t{
    
    data_type G, &time;
    unsigned &current, number_bodies;
    
    Body_t& Body;
    std::vector<std::vector<state_vector> > &planet_ephemeris;
    std::vector<state_vector> planets;
    std::vector<data_type> planet_mass;
    state_vector momentum;

    Force_t(data_type G, data_type &time, unsigned &current, Body_t& Body, 
    std::vector<std::vector<state_vector> > &planet_ephemeris, 
    const std::vector<data_type>& planet_mass) : G(G), time(time), current(current), Body(Body),
    planet_ephemeris(planet_ephemeris), planet_mass(planet_mass) {
        number_bodies = planet_mass.size();
        momentum = state_vector(3, 0.);
    }

    void operator()(const state_vector& R, state_vector& A) const;
    //void operator()(const state_vector& R, state_vector& A) const;    
    state_vector operator()(const masspt_t& masspt) const;
    state_vector Full_Torque(); 
    state_vector Full_Torque_Test();
    state_vector external_potential(unsigned number_body) const;
    void operator()(const Body_position_t& R, Body_position_t& Derivative_Body_Position);
    void fill_ephemeris();
    void fill_planets();
};
#endif