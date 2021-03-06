#include <stdio.h>
#include "DetectorConstruction.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");		//("G4_WATER")
	G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");

	G4double wantDepth = 0.1*cm;			//depth from the surface of water
	G4double replicaradius = 0.95*cm;		//as same as gnp radius
	G4double replicaheight = 0.1*cm;
	G4double phantomradius = replicaradius*5;
	G4double phantomheight = (replicaradius + replicaheight)*3;
	G4double worldlength = phantomradius*3;

	G4cout << "Check the run.mac file. The phantomheight is " << phantomheight/cm << " [cm]." << G4endl;

	// World
	G4VSolid* sol_World = new G4Box("World", worldlength/2, worldlength/2, worldlength/2);
	G4LogicalVolume* lv_World =	new G4LogicalVolume(sol_World, vacuum, "World");
	G4VPhysicalVolume* pv_World =
            new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm), lv_World, "World", 0, false, 0);

	// water phantom
	G4VSolid* sol_Phantom = new G4Tubs("Phantom", 0.0*cm, phantomradius, phantomheight/2, 0.0*deg, 360.0*deg);

	G4LogicalVolume* lv_Phantom = new G4LogicalVolume(sol_Phantom, water, "Phantom");
	new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, -phantomheight/2), lv_Phantom, "Phantom", lv_World, false, 0, false);

	// replica geometry
    G4VSolid* sol_MyGeom = new G4Tubs("Geometry", 0.0*cm, replicaradius, replicaheight/2, 0.0*deg, 360.0*deg);
	G4LogicalVolume* lv_MyGeom = new G4LogicalVolume(sol_MyGeom, water, "Geometry");
    new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, -phantomheight/2-replicaheight/2+wantDepth), lv_MyGeom, "Geometry", lv_Phantom, false, 200);


	// Visualization
	G4VisAttributes* va_World = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_World->SetForceWireframe(true);
	lv_World->SetVisAttributes(va_World);

    G4VisAttributes* va_Phantom = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    va_Phantom->SetForceWireframe(true);
	lv_Phantom->SetVisAttributes(va_Phantom);

    G4VisAttributes* va_MyGeom = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.3));
    va_MyGeom->SetForceSolid(true);
    lv_MyGeom->SetVisAttributes(va_MyGeom);

    return pv_World;
}

void DetectorConstruction::ConstructSDandField()
{

}
