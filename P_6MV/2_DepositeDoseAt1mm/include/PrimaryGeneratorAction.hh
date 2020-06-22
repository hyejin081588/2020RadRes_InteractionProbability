
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4INCLParticleTable.hh"
#include "globals.hh"
#include "G4ElementVector.hh"

using namespace std;
class G4ParticleGun;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	virtual ~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event* );

	G4ParticleGun* GetParticleGun() {return fParticleGun;}
	//inter- & extra-polation
	G4double interpolate( vector <G4double> &xData, vector<G4double> &yData, G4double x, G4bool extrapolate);

private:
	G4ParticleGun*          fParticleGun;

	//from 150kVp pdf
	ifstream ifp;
	G4int length_spec;
	G4double energy, pdf;
	vector <G4double> X, Y;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
