#include "constants.h"
#include "materials.h"

class simCell {
public:
  // parameters
  material cellMaterial;

  // current nuclear state
  double nFlux;

  // current mechanical state
  double temp;
};

class sim {
public:
  simCell* getCell(int, int);
  int tick(double);

  simCell thisFrame[SIM_CELLS_X * SIM_CELLS_Y]; // fully updated physics tick

  sim(const char* filename);
  ~sim();
};
