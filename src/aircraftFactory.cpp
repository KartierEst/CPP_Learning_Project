#include "aircraftFactory.h"


// note: textures have to be initialized after initializing glut, so we'll need
// our own init here
std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Airport* airport)
{
    assert(airport); // make sure the airport is initialized before creating aircraft
    const unsigned int indice = std::rand() % 8;
    //const std::string airline = airlines[std::rand() % 8];
    const std::string flight_number = airlines[indice] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0.f } * 3 + Point3D { 0.f, 0.f, 2.f };
    const Point3D direction = (-start).normalize();

    std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>(type, flight_number, indice, start, direction, airport->get_tower());
    return aircraft;
}
std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport* airport)
{
    auto aircraft = create_aircraft(*(aircraft_types[rand() % NUM_AIRCRAFT_TYPES]),airport);
    return aircraft;
}
void AircraftFactory::init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .10f, .04f, MediaPath { "concorde_af.png" } };
}
void AircraftFactory::add_name(const std::string& name)
{
    assert(!name.empty());
    uniqueAircrafts.emplace(name);
}
