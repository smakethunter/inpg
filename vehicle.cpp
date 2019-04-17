//
// Created by wojte on 15.03.2019.
//
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vehicle-2.hpp>

#include "vehicle-2.hpp"
std::string to_string(const Vehicle& v) {
    std::ostringstream print;
    print << "<" << v.get_id() << ">" << " : <" << v.get_brand() << ">";
    return print.str();
}

double compute_min_travel_duration(double distance,const Vehicle &v) {
    return distance/v.get_max_speed();
}

std::string compute_min_travel_duration_as_string(double distance, const Vehicle &vehicle) {
    std::ostringstream print;
    print<<std::setprecision(3)<<std::fixed;
    print<<"<"<<compute_min_travel_duration(distance,vehicle)<<">";
    return print.str();
}

std::vector<Vehicle *> filter_vehicles(std::vector<Vehicle *>::const_iterator vehicles_begin,
                                                std::vector<Vehicle *>::const_iterator vehicles_end,
                                                std::function<bool( Vehicle &)> predicate) {
    std::vector<Vehicle*> result;
    std::copy_if(vehicles_begin,vehicles_end,std::back_inserter(result),[&predicate](Vehicle* v){ return predicate(*v);}
    );
    return result;
}
std::string to_string(std::vector<Vehicle*>::const_iterator vehicles_begin,std::vector<Vehicle*>::const_iterator vehicles_end){
std::string print;

for(auto i=vehicles_begin;i!=vehicles_end; ++i){
    const auto& vehicle=**i;
    print+=to_string(vehicle);
    print+="\n";
}
return print;
}

bool Contain (std::string search,Vehicle& v, bool SizeMatter){
    bool contain;
    if(!SizeMatter){
    std::string search_trans;
    std::string v_name=v.get_id();
    std::string v_name_trans;
    std::transform(search.begin(),search.end(),search_trans.begin(),::tolower);
    std::transform(v_name.begin(),v_name.end(),v_name_trans.begin(),::tolower);
   contain= (v_name_trans.find(search_trans)!=std::string::npos);
    }
    else{

        contain=(v.get_id().find(search)!=std::string::npos);
    }
   return contain;
}

std::string to_string(const Driver& driver){
    std::ostringstream print;
    print<<"<"<<driver.get_name()<<">"<<" "<<"{"<<((driver.get_vehicle()== nullptr)? "brak pojazdu" :to_string(*(driver.get_vehicle())))<<"]";
    return  print.str();
}

void assign_vehicle_to_driver(std::vector<std::unique_ptr<Vehicle>> &vehicles, Driver &owner) {

owner.assign_vehicle(std::move(*(vehicles.end()-1)));
}


Driver &Driver::operator=(Driver &other) {
    name=other.name;
    vehicle_ptr=std::move(other.vehicle_ptr);
    return(*this);
}
