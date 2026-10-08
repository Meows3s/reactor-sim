#include "sim.h"
#include <iostream>
#include <string>

sim::sim(const char* filename) {
  FILE* fptr = std::fopen(filename, "w");
  if (fptr == NULL) {
    return; // failed
  }

  double nFlux, temp;
  std::string cellMaterialName;
  for (int i = 0; i < (SIM_CELLS_X * SIM_CELLS_Y); i++) {
    fscanf(fptr, "MAT=%s TEMP=%lf NF=%lf", &cellMaterialName, &nFlux, &temp);

    this->thisFrame[i].temp = temp;
    this->thisFrame[i].nFlux = nFlux;
  }
}

int sim::tick(double dt) {

  simCell nextFrame[SIM_CELLS_X * SIM_CELLS_Y];

  for (int x = 1; x < SIM_CELLS_X - 1; x++) {
    for (int y = 1; y < SIM_CELLS_Y - 1; y++) {

      simCell top = this->thisFrame[x + (y + 1) * SIM_CELLS_X];
      simCell bottom = this->thisFrame[x + (y - 1) * SIM_CELLS_X];
      simCell left = this->thisFrame[(x - 1) + y * SIM_CELLS_X];
      simCell right = this->thisFrame[(x + 1) + y * SIM_CELLS_X];

      simCell thisCell = this->thisFrame[x + (y * SIM_CELLS_X)];
      simCell thisCellNext = nextFrame[x + (y * SIM_CELLS_X)];

      thisCellNext.temp = (dt * thisCell.cellMaterial.conductance *
                           ((top.temp - thisCell.temp) + (bottom.temp - thisCell.temp) + (left.temp - thisCell.temp) +
                            (right.temp - thisCell.temp)));
    }
  }

  // copy nextframe into the current frame after everything is updated
  std::copy(nextFrame[0], nextFrame[SIM_CELLS_X * SIM_CELLS_Y], this->thisFrame);

  return 1;
}
