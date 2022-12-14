#include "PhysicsList.hh" //包含此源文件对应的头文件

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
//包含将要指定的物理过程的头文件

PhysicsList::PhysicsList() 
: G4VModularPhysicsList(){ 
//定义构造函数
  SetVerboseLevel(1);//指定输出信息的复杂度，越高越复杂，一般设置为1即可

  RegisterPhysics(new G4DecayPhysics());//指定基本粒子衰变物理过程

  RegisterPhysics(new G4EmStandardPhysics());//指定电磁相互作用物理过程

  RegisterPhysics(new G4RadioactiveDecayPhysics());//指定放射性核素衰变物理过程
}


PhysicsList::~PhysicsList()
//定义析构函数，一般为空
{ 
}

void PhysicsList::SetCuts()
//定义成员函数SetCuts()
{
  G4VUserPhysicsList::SetCuts();//将粒子的截断设置为默认
}  