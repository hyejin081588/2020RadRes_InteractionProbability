
#ifndef SteppingAction_hh_
#define SteppingAction_hh_

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class SteppingAction: public G4UserSteppingAction
{
public:
    SteppingAction();
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

private:
    G4double pre_EventID, totaldE;
};

#endif
