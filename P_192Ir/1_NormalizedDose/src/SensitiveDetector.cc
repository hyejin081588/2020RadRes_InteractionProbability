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

	G4double replicaheight = 0.1;	//cm

	G4double dE = aStep->GetTotalEnergyDeposit();
	G4int PrePV_copyNo = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(0);
	G4double dist = PrePV_copyNo*replicaheight+replicaheight/2;


	if (dE != 0)
	{

		FILE* myFile;
		myFile=fopen("N1_norm_192Ir_E7_s.txt","a");
		fprintf(myFile,"%e\t%e\n",dist/cm, dE/keV);
		fclose(myFile);

	}

	return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*){

}
