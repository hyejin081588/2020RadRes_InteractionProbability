
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
	// 150kVp pdf loading as an array
	ifp.open("N1_150kVp_phsp_1mm_s.txt");

	// initialization
	par = 0; x = 0; y = 0; z = 0; dirx = 0; diry = 0; dirz = 0; energy = 0; length_spec = 0;

	while(!ifp.eof()){
		ifp >> par >> x >> y >> z >> dirx >> diry >> dirz >> energy;

		PAR.push_back(par);
		X.push_back(x*nm);
		Y.push_back(y*nm);
		Z.push_back(z*nm);
		DIRX.push_back(dirx*nm);
		DIRY.push_back(diry*nm);
		DIRZ.push_back(dirz*nm);
		KE.push_back(energy*keV);

		length_spec = length_spec + 1;
	}
	ifp.close();

	G4cout << "the total beam number should be : " << length_spec << G4endl;

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
	G4double rand = G4UniformRand();
	G4int i = round(length_spec*rand);

	// 1. type
	if(PAR[i] == 0)
	{
		G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
		fParticleGun->SetParticleDefinition(particleDefinition);
	}
	else
	{
		G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
		fParticleGun->SetParticleDefinition(particleDefinition);
	}


	// 2. energy
	fParticleGun->SetParticleEnergy(KE[i]);

	// 3. position
	fParticleGun->SetParticlePosition(G4ThreeVector(X[i], Y[i], Z[i]));


	// 4. direction
	// 1/cos(theta) calculation; 1/cos(theta) = length(a)*length(b)/a*b(dot)
	G4double newdirx = 0, newdiry = 0, newdirz = 1;
	G4double l1 = sqrt(DIRX[i]*DIRX[i] + DIRY[i]*DIRY[i] + DIRZ[i]*DIRZ[i]);
	G4double inv_cos = 1*l1/(newdirx*DIRX[i] + newdiry*DIRY[i] + newdirz*DIRZ[i]);
	fParticleGun->SetParticleMomentumDirection(inv_cos*G4ThreeVector(newdirx, newdiry, newdirz));

	// 5. to make gun
	fParticleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
