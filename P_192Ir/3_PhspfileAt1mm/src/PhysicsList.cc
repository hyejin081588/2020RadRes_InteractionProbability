#include "PhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmPenelopePhysics.hh"

PhysicsList::PhysicsList()
    : G4VModularPhysicsList()
{
    SetDefaultCutValue(1.*nanometer);
    SetVerboseLevel(1);

    RegisterPhysics(new G4EmPenelopePhysics());
}

PhysicsList::~PhysicsList()
{

}
