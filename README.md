# 2020RadRes_InteractionProbability (Geant4.10.5)
*Calculation of interaction probability with 150kVp, 6MV, and Ir-192.
*Each folder(P_150kVp, P_6MV, P_192Ir) has the same configuration.
*Calculation depth : change "wantDepth" in folder of 2&3./src/DetecctorConstruction.cc.
*Weighting factor  : check "// 4. direction" part in folder of 4./src/PrimaryGeneratorAction.cc.


#################################### Geant4 codes #####################################
1. Normalized Dose
  - physics   : G4EmPenelopePhysics
  - input     : -
  - output    : [distance(cm) dE(keV)] "N1_norm_X*_E7_s.txt"
  - histories : E7
  - how to run: ./N1_norm run.mac
  
2. Deposited Dose at 1mm
  - physics   : G4EmPenelopePhysics
  - input     : -
  - output    : [dE(keV)] "N1_D_X*_E7_s.txt"
  - histories : E7
  - how to run: ./N1_norm run.mac
  
3. Phase space file at 1mm
  - physics   : G4EmPenelopePhysics, rangecut(1nm)
  - input     : -
  - output    : [particle x y z(cm) dirx diry dirz(cm) KE(keV)] "N1_X*_phsp_s.txt"
  - histories : E7
  - how to run: ./N1_phsp run.mac
  
4. Inoization number in GNP
  - physics   : G4EmPenelopePhysics, rangecut(1nm)
  - input     : "N1_X*_phsp_s.txt" (from 3.)
  - output    : [dE(keV)] "N2_dE_GNP_X*_s.txt"
  - histories : E7
  - how to run: ./phspfromGNP run.mac

(X*: 150kVp, 6MV, 192Ir)


##################################### matlab code #####################################
%% loading 2~4 output files in matlab
output2 = loading("N1_D_X*_E7_s.txt");    % Deposited Dose at 1mm
output3 = loading("N1_X*_phsp_s.txt");    % Phase space file at 1mm
output4 = loading("N2_dE_GNP_X*_s.txt");  % ionization number in GNP

%% calculation of Deposited dose at 1 mm
dE = sum(output2);
h = 0.1;                                  % cm
r = 0.95;                                 % cm
c = 1.60218*10^-16;                       % 1 keV = 1.60218*10^-16 J
D = c*dE/(pi()*r^2*h*10^-3);              % Gy

scale1 = ((1.9*10^-9)/(1.9*10^-2))^2;     % phsp file beam area correction (cm to nm)
scale2 = length(output3)/10^7;            % phsp file beam number correction

p = length(output4)*scale1*scale2/D;
