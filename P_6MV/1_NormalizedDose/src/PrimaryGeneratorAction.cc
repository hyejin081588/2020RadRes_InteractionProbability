
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


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double PrimaryGeneratorAction::interpolate(vector<double> &xData, vector<double> &yData, double x, bool extrapolate )
{
	int size = xData.size();

	int i = 0;                                                                  // find left end of interval for interpolation
	if ( x >= xData[size - 2] )                                                 // special case: beyond right end
	{
		i = size - 2;
	}
	else
	{
		while ( x > xData[i+1] ) i++;
	}
	double xL = xData[i], yL = yData[i], xR = xData[i+1], yR = yData[i+1];      // points on either side (unless beyond ends)
	if ( !extrapolate )                                                         // if beyond ends of array and not extrapolating
	{
		if ( x < xL ) yR = yL;
		if ( x > xR ) yL = yR;
	}

	double dydx = ( yR - yL ) / ( xR - xL );                                    // gradient

	return yL + dydx * ( x - xL );                                              // linear interpolation
}


PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
	// 150kVp pdf loading as an array
	ifp.open("pdf_6MV_linac2.txt");

	// initialization
	energy = 0; pdf = 0; length_spec = 0;

	while(!ifp.eof()){
		ifp >> energy >> pdf;

		X.push_back(energy*MeV);
		Y.push_back(pdf);

		length_spec = length_spec + 1;
	}
	ifp.close();

	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);

	G4cout << "##########particlegun end!!!##########" << G4endl << G4endl;
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
	G4double rand = G4UniformRand();
	if(rand == 1) rand = G4UniformRand();
	G4double en = interpolate( Y, X, rand, true);

	fParticleGun->SetParticleEnergy(en);

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
