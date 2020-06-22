#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent*){

}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){


	G4double dE = aStep->GetTotalEnergyDeposit();


	if (dE != 0)
	{
		FILE* myFile;
		myFile=fopen("N1_D_6MV_E7_s.txt","a");
		fprintf(myFile,"%e\n",dE/keV);
		fclose(myFile);
	}

	return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*){

}
