//
// Created by abder on 21/02/2022.
//

#include "aircraftManager.h"
#include "airport.hpp"


void AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();)
    {
        auto& aircraft = **it;
        aircraft.move();
        if (!aircraft.if_destroy())
        {
            ++it;
        }
        else
        {
            it = aircrafts.erase(it);
        }
    }
}
void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}
