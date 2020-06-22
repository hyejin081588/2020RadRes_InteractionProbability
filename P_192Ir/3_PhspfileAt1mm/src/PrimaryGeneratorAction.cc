
#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():
    G4VUserPrimaryGeneratorAction()
{
	fPrimary = new G4GeneralParticleSource();

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

    fPrimary->GeneratePrimaryVertex(anEvent);
}
