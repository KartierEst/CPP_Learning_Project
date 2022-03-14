#pragma once

#include "aircraft_types.hpp"
#include "config.hpp"
#include "geometry.hpp"
#include "tower.hpp"
#include "waypoint.hpp"

#include <string>
#include <string_view>

class Aircraft : public GL::Displayable
{
private:
    const AircraftType& type;
    const std::string flight_number;
    const unsigned int airline_indice;
    unsigned int fuel = 150 + rand() % 2851;
    Point3D pos, speed; // note: the speed should always be normalized to length 'speed'
    WaypointQueue waypoints = {};
    Tower& control;
    bool landing_gear_deployed = false; // is the landing gear deployed?
    bool is_at_terminal        = false;
    bool already_serviced = false;
    bool redeployed = false;
    bool not_fuel = false;

    // turn the aircraft to arrive at the next waypoint
    // try to facilitate reaching the waypoint after the next by facing the
    // right way to this end, we try to face the point Z on the line spanned by
    // the next two waypoints such that Z's distance to the next waypoint is
    // half our distance so: |w1 - pos| = d and [w1 - w2].normalize() = W and Z
    // = w1 + W*d/2
    void turn_to_waypoint();
    void turn(Point3D direction);

    // select the correct tile in the plane texture (series of 8 sprites facing
    // [North, NW, W, SW, S, SE, E, NE])
    unsigned int get_speed_octant() const;
    // when we arrive at a terminal, signal the tower
    void arrive_at_terminal();
    // deploy and retract landing gear depending on next waypoints
    void operate_landing_gear();
    void add_waypoint(const Waypoint& wp, const bool front);
    float max_speed() const { return is_on_ground() ? type.max_ground_speed : type.max_air_speed; }

    Aircraft(const Aircraft&) = delete;
    Aircraft& operator=(const Aircraft&) = delete;

public:
    Aircraft(const AircraftType& type_, const std::string_view& flight_number_, const unsigned int& airline_indice_, const Point3D& pos_,
             const Point3D& speed_, Tower& control_) :
        GL::Displayable { pos_.x() + pos_.y() },
        type { type_ },
        flight_number { flight_number_ },
        airline_indice { airline_indice_ },
        pos { pos_ },
        speed { speed_ },
        control { control_ }
    {
        speed.cap_length(max_speed());
    }
    ~Aircraft()
    {
        //control.dereserve_terminal(*this);
        control.terminal_finish(*this);
    }

    const std::string& get_flight_num() const { return flight_number; }
    const unsigned int& get_indice() const { return airline_indice; }
    float distance_to(const Point3D& p) const { return pos.distance_to(p); }
    bool if_destroy() { return redeployed; }//already_serviced; }
    bool get_not_fuel() { return not_fuel;} // if dont have fuel
    unsigned int get_fuel() { return fuel;} // the fuel


    void display() const override;
    void move();

    friend class Tower;
    void update();

    bool has_terminal() const;
    bool is_circling() const;
    bool is_low_on_fuel() const;
    void refill(unsigned int& fuel_stock);
    bool is_on_ground() const { return pos.z() < DISTANCE_THRESHOLD; }
};
