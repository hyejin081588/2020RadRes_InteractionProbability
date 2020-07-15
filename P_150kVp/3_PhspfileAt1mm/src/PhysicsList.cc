#include "PhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmPenelopePhysics.hh"

PhysicsList::PhysicsList()
    : G4VModularPhysicsList()
{
    RegisterPhysics(new G4EmPenelopePhysics());
}

PhysicsList::~PhysicsList()
{

}
