#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class PhysicsList: public G4VModularPhysicsList
{
public:
    PhysicsList();
virtual ~PhysicsList();
};

#endif
