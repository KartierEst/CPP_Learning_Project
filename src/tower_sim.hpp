#pragma once

#include "aircraftManager.h"
#include "aircraftFactory.h"
class Airport;
struct AircraftType;

struct ContextInitializer
{
private:
    int _argc;
    char** _argv;
public:
    ContextInitializer(int argc,char** argv) :
        _argc {argc},
        _argv {argv}
    {
        MediaPath::initialize(argv[0]);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
    int getArgc() { return _argc;}
    char** getArgv() { return _argv;}
};

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager aircraft_manager;
    ContextInitializer _contextInitializer;
    AircraftFactory aircraft_factory;
    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_aircraft();

    void create_keystrokes();
    void display_help() const;

    void init_airport();
    void init_aircraftManager();

public:
    TowerSimulation(ContextInitializer& contextInitializer) :
        help {(contextInitializer.getArgc() > 1) && (std::string { contextInitializer.getArgv()[1] } == "--help" || std::string { contextInitializer.getArgv()[1] } == "-h") },
        _contextInitializer {contextInitializer}
    {
        create_keystrokes();
    }
    ~TowerSimulation();

    void launch();
};
