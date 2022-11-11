
#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  //按照此方法确定的动量分配方式为：
  //x方向：分配|a|/sqrt(a^2+b^2+c^2)的动量
  //y方向：分配|b|/sqrt(a^2+b^2+c^2)的动量
  //z方向：分配|c|/sqrt(a^2+b^2+c^2)的动量
  //如果a/b/c为负数，则表示与对应坐标轴正方向相反
  //e.g.a=0,b=0,c=1表示粒子仅在z轴方向有速度，粒子源沿着z轴方向发射。
  //也可以采用随机分布的方法确定动量方向，与确定位置类似
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  fParticleGun->SetParticleEnergy(1.46*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event

  G4double envSizeXY = 120*cm;
  G4double envSizeZ = 30*cm;
  G4double envHeightZ = 65*cm;
  
  G4double x0 = envSizeXY * (G4UniformRand()-0.5);
  G4double y0 = envSizeXY * (G4UniformRand()-0.5);
  G4double z0 = envHeightZ - envSizeZ  *(G4UniformRand()-0.5);

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



