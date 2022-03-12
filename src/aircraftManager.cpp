//
// Created by abder on 21/02/2022.
//

#include "aircraftManager.h"
#include "airport.hpp"


void AircraftManager::move()
{
    std::function<bool(std::unique_ptr<Aircraft>&)> predicat = [](std::unique_ptr<Aircraft>& aircraft){
        aircraft->move();
        return aircraft->if_destroy() || aircraft->get_not_fuel();
    };

    auto sup = std::remove_if(aircrafts.begin(),aircrafts.end(),predicat);
    aircrafts.erase(sup,aircrafts.end());
    /*for (auto it = aircrafts.begin(); it != aircrafts.end();)
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
    }*/
}
void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}

void AircraftManager::count_airline(const unsigned int& x){
    //int count = 0;
    /*for(auto& aircraft : aircrafts){
        if(airlines[x] == aircraft->get_flight_num().substr(0,2))
        {
            count++;
        }
    }*/
    std::function<bool(std::unique_ptr<Aircraft>&)> count = [x](std::unique_ptr<Aircraft>& aircraft){
        return aircraft->get_indice() == x;
    };
    auto size = std::count_if(aircrafts.begin(),aircrafts.end(),count);
    std::cout << "Airlines " << airlines[x] << " : " << size << std::endl;
}
