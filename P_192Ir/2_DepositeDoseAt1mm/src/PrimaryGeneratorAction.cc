
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
//NEW
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "math.h"

#define PI 3.1415926535897


PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// 1. type
	G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	fParticleGun->SetParticleDefinition(particleDefinition);

	// 2. energy
	fParticleGun->SetParticleEnergy(356*keV);

	// 3. position
	G4double theta = 2*PI*G4UniformRand();
	G4double r = 0.95*G4UniformRand()*cm;
	G4double pos_x = r*cos(theta);
	G4double pos_y = r*sin(theta);

	fParticleGun->SetParticlePosition(G4ThreeVector(pos_x, pos_y, -10*cm));


	// 4. direction
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));


	// 5. to make gun
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
