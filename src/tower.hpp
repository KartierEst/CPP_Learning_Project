#pragma once

#include "waypoint.hpp"
#include "airport_type.hpp"
//#include "aircraftManager.h"

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class Airport;
class Aircraft;
class Terminal;

class Tower
{
private:
    using AircraftToTerminal      = std::unordered_map<const Aircraft*,size_t>;//std::vector<std::pair<const Aircraft*, size_t>>;
    using AircraftAndTerminalIter = AircraftToTerminal::iterator;

    Airport& airport;
    // aircrafts may reserve a terminal
    // if so, we need to save the terminal number in order to liberate it when the craft leaves
    //AircraftToTerminal reserved_terminals = {};
    AircraftToTerminal reserved_terminals = {};

    WaypointQueue get_circle() const;

    /*AircraftAndTerminalIter find_craft_and_terminal(const Aircraft& aircraft)
    {
        return std::find_if(reserved_terminals.begin(), reserved_terminals.end(),
                            [&aircraft](const auto& x) { return x.first == &aircraft; });
    }*/
public:
    Tower(Airport& airport_) : airport { airport_ } {}
    // produce instructions for aircraft
    WaypointQueue get_instructions(Aircraft& aircraft);
    void arrived_at_terminal(Aircraft& aircraft);
    AircraftToTerminal get_reserved_terminal() { return reserved_terminals; }

    WaypointQueue reserve_terminal(Aircraft& aircraft);
    void terminal_finish(Aircraft& aircraft);
};
