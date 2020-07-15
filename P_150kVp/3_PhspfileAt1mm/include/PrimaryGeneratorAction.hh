#ifndef PrimaryGeneratorAction_hh_
#define PrimaryGeneratorAction_hh_

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	virtual ~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);
private:
	G4GeneralParticleSource* fPrimary;
};

#endif
