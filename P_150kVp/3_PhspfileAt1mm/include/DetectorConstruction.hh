#ifndef DetectorConstruction_hh_
#define DetectorConstruction_hh_

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();
private:

};

#endif
