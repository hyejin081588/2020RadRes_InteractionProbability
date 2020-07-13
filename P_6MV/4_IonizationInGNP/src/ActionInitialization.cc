#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
:G4VUserActionInitialization()
{

}

ActionInitialization::~ActionInitialization()
{

}

void ActionInitialization::BuildForMaster() const
{

}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new SteppingAction());
}
