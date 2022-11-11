
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
  //自定义rock材料
    G4Material* rock = new G4Material("ROCK", 2.8 * g / cm3, 8, kStateSolid,  1. * atmosphere);
    G4String name, symbol;             // a=mass of a mole;
    G4double a, z;            // z=mean number of protons;
    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);
    a = 28.09*g/mole;
    G4Element* elSi = new G4Element(name="Silicon", symbol="Si", z=14., a);
    a = 26.98*g/mole;
    G4Element* elAl = new G4Element(name="Aluminum",symbol="Al", z=13., a);
    a = 55.85*g/mole;
    G4Element* elFe = new G4Element(name="Iron"    ,symbol="Fe", z=26., a);
    a = 40.078*g/mole;
    G4Element* elCa = new G4Element(name="Calcium", symbol="Ca", z=20., a);
    a = 22.9898*g/mole;
    G4Element* elNa = new G4Element(name="Sodium", symbol="Na", z=11., a);
    a = 39.0983*g/mole;
    G4Element* elK = new G4Element(name="Potassium", symbol="K", z=19., a);
    a = 24.3050*g/mole;
    G4Element* elMg = new G4Element(name="Magnesium", symbol="Mg", z=12., a);
    rock->AddElement(elO, 46.9 * perCent);
    rock->AddElement(elSi, 28.2 * perCent);
    rock->AddElement(elAl, 8.2 * perCent);
    rock->AddElement(elFe, 5.6 * perCent);
    rock->AddElement(elCa, 3.6 * perCent);
    rock->AddElement(elNa, 2.8 * perCent);
    rock->AddElement(elK, 2.6 * perCent);
    rock->AddElement(elMg, 2.1 * perCent);
  //
  // World
  //
  G4double world_sizeXY = 1.2*m;
  G4double world_sizeZ  = 1.2*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  //
  // RockSeam
  //
  G4double RockSeam_sizeX = 120*cm,RockSeam_sizeY = 120*cm, RockSeam_sizeZ = 30*cm;
  G4Material* RockSeam_mat = rock;
  G4Box* solidRockSeam =
    new G4Box("RockSeam",                    //its name
        0.5*RockSeam_sizeX, 0.5*RockSeam_sizeY, 0.5*RockSeam_sizeZ); //its size

  G4LogicalVolume* logicRockSeam =
    new G4LogicalVolume(solidRockSeam,            //its solid
                        RockSeam_mat,             //its material
                        "RockSeam");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,65*cm),         //at (0,0,0)
                    logicRockSeam,                //its logical volume
                    "RockSeam",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // CoalSeam
  //
  G4double CoalSeam_sizeX = 120*cm,CoalSeam_sizeY = 120*cm, CoalSeam_sizeZ = 30*cm;
  G4Material* CoalSeam_mat = nist->FindOrBuildMaterial("G4_C");
  G4Box* solidCoalSeam =
    new G4Box("CoalSeam",                    //its name
        0.5*CoalSeam_sizeX, 0.5*CoalSeam_sizeY, 0.5*CoalSeam_sizeZ); //its size

  G4LogicalVolume* logicCoalSeam =
    new G4LogicalVolume(solidCoalSeam,            //its solid
                        CoalSeam_mat,             //its material
                        "CoalSeam");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,35*cm),         //at (0,0,0)
                    logicCoalSeam,                //its logical volume
                    "CoalSeam",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  // detector 
  //
  G4double detector_sizeX = 60*cm,detector_sizeY = 60*cm, detector_sizeZ = 10*cm;
  G4Material* detector_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4Box* soliddetector =
    new G4Box("detector",                    //its name
        0.5*detector_sizeX, 0.5*detector_sizeY, 0.5*detector_sizeZ); //its size

  G4LogicalVolume* logicDetector =
    new G4LogicalVolume(soliddetector,            //its solid
                        detector_mat,             //its material
                        "detector");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,5*cm),         //at (0,0,0)
                    logicDetector,                //its logical volume
                    "detector",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Set detector as scoring volume
  //
  fScoringVolume = logicDetector;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

