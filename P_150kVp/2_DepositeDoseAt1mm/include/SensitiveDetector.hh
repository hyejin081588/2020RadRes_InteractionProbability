#ifndef SensitiveDetector_hh_
#define SensitiveDetector_hh_

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SensitiveDetector: public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String name);
	virtual ~SensitiveDetector();

	void Initialize(G4HCofThisEvent*);
	G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*);
	void EndOfEvent(G4HCofThisEvent*);

private:

};

#endif
