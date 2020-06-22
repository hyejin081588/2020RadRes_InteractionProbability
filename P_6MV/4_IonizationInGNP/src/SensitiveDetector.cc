#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{
	totaldE = 0;
}

SensitiveDetector::~SensitiveDetector()
{

}

void SensitiveDetector::Initialize(G4HCofThisEvent*){

	totaldE = 0;
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){

	G4double dE = aStep->GetTotalEnergyDeposit();
	totaldE = totaldE + dE;

	return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*){

	if (totaldE != 0)
	{
		FILE* myFile;
		myFile=fopen("N2_dE_GNP_6MV_s.txt","a");
		fprintf(myFile,"%e\n", totaldE/keV);
		fclose(myFile);
	}
}
