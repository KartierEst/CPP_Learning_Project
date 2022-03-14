#pragma once

#include "airport.hpp"
//#include "aircraftManager.h"

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    void init_aircraft_types();
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type,Airport* airport);
    std::set<std::string> uniqueAircrafts;

public:
    AircraftFactory()
    {
        init_aircraft_types();
    }
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
    void add_name(const std::string& basicString);
    std::set<std::string> getUniqueAircrafts() {return uniqueAircrafts;}
};


