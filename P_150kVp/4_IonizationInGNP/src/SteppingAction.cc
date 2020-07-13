#include "SteppingAction.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4ThreeVector.hh"
#include "G4ProcessManager.hh"
#include "G4RunManager.hh"


SteppingAction::SteppingAction():
G4UserSteppingAction()
{
	pre_EventID = 0;
	totaldE = 0;

	// G4cout << "########## pre_EventID is initialized." << G4endl;
}

SteppingAction::~SteppingAction()
{

}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4int EventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	G4double dE = aStep->GetTotalEnergyDeposit();

	if(pre_EventID == EventID){
		totaldE = totaldE + dE;

		// G4cout << "########## totaldE : " << totaldE/MeV << G4endl;
	}
	else{ //new event starts.
		if(totaldE != 0){
			FILE* myFile;
			myFile=fopen("N2_dE_GNP_6MV_electron_E6_2cm.txt","a");
			fprintf(myFile,"%e\n", totaldE/keV);
			fclose(myFile);

			// G4cout << "########## this event has an interactions with gold." << G4endl;
		}
		totaldE = 0;	//initialization

		// G4cout << "########## totaldE : " << totaldE/MeV << G4endl;
		// G4cout << "########## totaldE has been initialized." << G4endl;
	}

	// G4cout << "########## pre_EventID : " << pre_EventID << "\tEventID : " << EventID << G4endl;

	pre_EventID = EventID;
}
