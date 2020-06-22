
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4GeometryManager.hh"
#include "G4GeometryTolerance.hh"

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // nm scale tolerance
    G4double fWorldLength = 100.*nm;
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
         G4cout << "Surface tolerance = " << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/nm
                << " nm - Radial tolerance = " << G4GeometryTolerance::GetInstance()->GetRadialTolerance()/nm << " nm" << G4endl;


    // parameters
    G4double worldlength = 20*nm;
    G4double golddiameter = 1.9*nm;

 /*--------------------------------------------------------------------------------------------------*/
    // World
    G4VSolid* sol_World = new G4Box("World", worldlength/2, worldlength/2, worldlength/2);
    G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");		//("G4_WATER")
    G4LogicalVolume* lv_World = new G4LogicalVolume(sol_World, water, "World");
    G4VPhysicalVolume* pv_World =
            new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_World, "World", 0, false, 0);


    //gold nanoparticle
    G4VSolid* sol_Gold = new G4Sphere("gold", 0, golddiameter/2, 0, 360*deg, 0, 180*deg);
    G4Material* gold = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
    G4LogicalVolume* lv_Gold = new G4LogicalVolume(sol_Gold, gold, "gold");		//water -> gold!!!!!!!
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lv_Gold, "gold", lv_World, false, 0);


 /*--------------------------------------------------------------------------------------------------*/
	// Visualization
    G4VisAttributes* white = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); 	white->SetForceWireframe(true);
    G4VisAttributes* blue = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));	blue->SetForceWireframe(true);

    lv_World->SetVisAttributes(white);
    lv_Gold->SetVisAttributes(blue);

	return pv_World;
}

void DetectorConstruction::ConstructSDandField()
{
	SensitiveDetector* mySD = new SensitiveDetector("detector");
	G4SDManager::GetSDMpointer()->AddNewDetector(mySD);
	SetSensitiveDetector("gold", mySD);

}
