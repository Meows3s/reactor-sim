#include "constants.h"
#include "materials.h"

class simCell {
public:
  // parameters
  material cellMaterial;

  // current nuclear state
  double fastFlux;
  double thermalFlux; // thermal neutrons, not temperature !

  // current mechanical state
  double temp;
};

class sim {
public:
  int fastTick();
  int thermalTick();

  simCell state[SIM_CELLS_X * SIM_CELLS_Y]; // fully updated physics tick

  sim(const char* filename); // constructor, also loads the sim from a file
  ~sim();
};
