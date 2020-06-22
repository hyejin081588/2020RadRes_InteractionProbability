#include "SteppingAction.hh"

SteppingAction::SteppingAction():
G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{

}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4int StepStatus = aStep->GetPostStepPoint()->GetStepStatus();

	if (StepStatus > 0)		//stepstatus = 0; fWorldBoundary
	{

		G4String PreVol = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
		G4String NextVol = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

		if(PreVol == "Geometry" && NextVol == "Phantom")
		{

			G4double KE = aStep->GetTrack()->GetKineticEnergy();

			if(KE != 0){
				G4String ParName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();

				if(ParName == "gamma")
				{
					G4double xpos = aStep->GetPostStepPoint()->GetPosition().x();
					G4double ypos = aStep->GetPostStepPoint()->GetPosition().y();
					G4double zpos = aStep->GetPostStepPoint()->GetPosition().z();

					G4double xdir = aStep->GetPostStepPoint()->GetMomentumDirection().x();
					G4double ydir = aStep->GetPostStepPoint()->GetMomentumDirection().y();
					G4double zdir = aStep->GetPostStepPoint()->GetMomentumDirection().z();

					FILE* myFile;
					myFile=fopen("N1_6MV_phsp_s.txt","a");
					fprintf(myFile,"%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n",0.,xpos/cm,ypos/cm,zpos/cm,xdir/cm,ydir/cm,zdir/cm,KE/keV);
					fclose(myFile);
				}
				else if(ParName == "e-")
				{
					G4double xpos = aStep->GetPostStepPoint()->GetPosition().x();
					G4double ypos = aStep->GetPostStepPoint()->GetPosition().y();
					G4double zpos = aStep->GetPostStepPoint()->GetPosition().z();

					G4double xdir = aStep->GetPostStepPoint()->GetMomentumDirection().x();
					G4double ydir = aStep->GetPostStepPoint()->GetMomentumDirection().y();
					G4double zdir = aStep->GetPostStepPoint()->GetMomentumDirection().z();

					FILE* myFile;
					myFile=fopen("N1_6MV_phsp_s.txt","a");
					fprintf(myFile,"%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n",1.,xpos/cm,ypos/cm,zpos/cm,xdir/cm,ydir/cm,zdir/cm,KE/keV);
					fclose(myFile);
				}
			}
		}
	}
}
