#ifndef LANDER_H
#define LANDER_H
#include <iostream>
using namespace std;

const int TIME = 1;
const double C = 1.62;

class lander {
public:
    lander(double=0, double=0, double=0,
        double = 0, double=0, int=0);
    double get_velocity () const;
    double get_altitude () const;
    double get_fuel_amount () const;
    int get_id () const;
    double get_mass () const;
    char get_status () const;
    bool change_flow_rate (double);
    void simulate ();
    bool operator >(const lander &) const;

private:
    double flow_rate; //throttle percentage
    double velocity; //vel of lander; pos = moving surface, neg = moving towards
    double altitude; // alt = height from surface, 0 = contact made
    double fuel_amount; // amount of fuel in tank
    bool stillLanding; // true = airborne, false = not airborne
    int id; // lander id
    int timesSimulated; // amount of times processed by central tower
    double LANDER_MASS; // mass of lander
    double MAX_FUEL_CONSUMPTION_RATE; // max amount of fuel
    double MAX_THRUST; // max amount of thrust at max thruttle 
};

lander::lander(double mass, double max_thrust, double max_fuel, 
    double alt, double fuel, int id):LANDER_MASS(mass), 
    MAX_THRUST(max_thrust), MAX_FUEL_CONSUMPTION_RATE(max_fuel),
    altitude(alt), fuel_amount(fuel), id(id){
        if(alt>0)
            stillLanding = true;
        else
            stillLanding = false;
        flow_rate=0;
        velocity=0;
        timesSimulated=0;
    };

double lander::get_velocity() const{
    return this->velocity;
}

double lander::get_altitude() const{
    return this->altitude;
}

double lander::get_mass() const{
    return this->LANDER_MASS;
}

double lander::get_fuel_amount() const{
    return this->fuel_amount;
}

int lander::get_id() const{
    return this->id;
}



char lander::get_status() const{
    // not airborne
    if(!stillLanding){
        if(this->velocity <= -2)
            return 'c';
        else
            return 'l';
    }

    // still airborne
    return 'a';
}

//  if r is between 0 and 1 (inclusive), then set flow rate
// with r if fuel amount is larger than 0 and the return true, 
// return false if r is not between 0 and 1
// (inclusive) and do not set flow rate
bool lander::change_flow_rate(double r){
    if(r>= 0 && r<=1){
        if(fuel_amount>0){
            flow_rate = r;
            return true;
        }
    }

    return false;
}

void lander::simulate(){
    double v;
    if(this->stillLanding == true){
        v = TIME * ((this->flow_rate * this->MAX_THRUST)/
            (this->LANDER_MASS + this->fuel_amount)) - C;
        
        velocity += v;

        altitude += TIME * velocity;
        
        if(altitude<=0)
            stillLanding = false;
        
        fuel_amount -= (TIME * MAX_FUEL_CONSUMPTION_RATE * abs(v));
        if(fuel_amount<0)
            fuel_amount=0;

        timesSimulated++;
    }
}

bool lander::operator>(const lander& rhs) const{
    //check times simulated, only check next thing
    //altitude if ==
    //repeat same idea for other conditions
    if(this->timesSimulated<rhs.timesSimulated)
        return true;
    if(rhs.timesSimulated<this->timesSimulated)
        return false;
    
    //check for bigger altitude
    if(this->altitude<rhs.altitude)
        return true;
    if(rhs.altitude<this->altitude)
        return false;

    //check for less fuel
    if(this->fuel_amount<rhs.fuel_amount)
        return true;
    if(rhs.fuel_amount<this->fuel_amount)
        return false;

    // check for greater mass
    if(this->LANDER_MASS > rhs.LANDER_MASS)
        return true;
    if(rhs.LANDER_MASS > this->LANDER_MASS)
        return false;

    if(this->id < rhs.id)
        return true;
    if(rhs.id < this->id)
        return false;

    //if function hasn't returned, then everything is =
    return false;
}

#endif
