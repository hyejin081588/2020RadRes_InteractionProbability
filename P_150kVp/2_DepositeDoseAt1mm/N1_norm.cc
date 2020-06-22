#include "DetectorConstruction.hh"
#include "G4PhysListFactory.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv)
{
	// Random engine and seed setting
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(time(NULL));

#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads(20);
#else
	G4RunManager* runManager = new G4RunManager;
#endif

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();

    // Construct ui and visualization manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    if(argc==1)     // GUI (qt) based interactive mode
    {
        G4UIExecutive* UI = new G4UIExecutive(argc, argv, "qt");
        UImanager->ApplyCommand("/control/execute vis.mac");
        UI->SessionStart();
        delete UI;
    }
    else            // Batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    // Free the store
    delete runManager;

    return 0;
}
