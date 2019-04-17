#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>
#include <vector>
#include <functional>

#include <iostream>
#include <memory>
#ifndef VEHICLES_1_VEHICLE_1_HPP
#define VEHICLES_1_VEHICLE_1_HPP
static std::int64_t next_vin;

enum class Gender{
    Male,
    Female
};
class Vehicle{

private:
    std::string id;
    std::string brand;
    std::int64_t vin_;
    Gender gender;
public:

    Vehicle():vin_(++next_vin){};
    Vehicle(std::string ID, std::string BRAND, Gender& g):id(std::move(ID)),brand(std::move(BRAND)), vin_(++next_vin),gender(g){};
    std::string get_id()const {return id;};
    std::string get_brand()const {return brand;};
    virtual double get_max_speed()const=0;
    Gender get_gender(){return gender;};
    ~Vehicle() = default;
};
std::string to_string(const Vehicle& v);
class Car: public Vehicle{
public:
    Car(std::string ID, std::string BRAND, Gender g, double ENGINE_HP): Car::Vehicle (std::move(ID), std::move(BRAND),g), engine_hp(ENGINE_HP){};
    double get_max_speed()const override{ return engine_hp;}

private:
    double engine_hp;


};
class Bicycle:public Vehicle{
public:
    Bicycle(std::string id, std::string brand,Gender g, int n_gears):Bicycle::Vehicle(std::move(id), std::move(brand),g), n_gears(n_gears){};
    double get_max_speed()const override { return n_gears*3;}
private:
    int n_gears ;
};
class Driver
        {

public:
    Driver(std::string Name): Driver(Name, nullptr){}
    Driver( std::string Name, std::unique_ptr<Vehicle> Vehicle_ptr): name(Name),vehicle_ptr(std::move(Vehicle_ptr)){}

    Driver(Driver& other): name(other.name),vehicle_ptr(std::move(other.vehicle_ptr)){}
    Driver& operator=(Driver& other);
    void assign_vehicle(std::unique_ptr<Vehicle> Vehicle_ptr){
        vehicle_ptr=std::move(Vehicle_ptr);
    }
     std::string get_name() const {return name;}
    Vehicle* get_vehicle() const {return vehicle_ptr.get();}

private:
    std::string name;
    std::unique_ptr<Vehicle> vehicle_ptr;
};
std::string to_string(const Driver& driver);
void assign_vehicle_to_driver(std::vector<std::unique_ptr<Vehicle>>& vehicles, Driver& owner);
double compute_min_travel_duration(double distance,const Vehicle& v);
std::string compute_min_travel_duration_as_string(double distance, const Vehicle &vehicle);
std::string to_string(std::vector<Vehicle*>::const_iterator vehicles_begin,
                      std::vector<Vehicle*>::const_iterator vehicles_end);
bool Contain (std::string search,Vehicle& v,bool SizeMatter);
std::vector<Vehicle*> filter_vehicles(
        std::vector<Vehicle*>::const_iterator vehicles_begin,
        std::vector<Vehicle*>::const_iterator vehicles_end,
        std::function<bool (Vehicle&)> predicate);

#endif //VEHICLES_1_VEHICLE_1_HPP
