#include "sim.h"
#include "constants.h"
#include "materials.h"
#include <fstream>

sim::sim(const char* filename) {
  std::ifstream setupFile(filename);

  for (int i = 0; i < N_CELLS; i++) {
    simCell thisCell;
    thisCell.cellMaterial = u235;

    this->state[i] =
  }
}
