#include "sim.h"

// remember: all neutrons are produced fast. The flux should be: fast -> thermal -> fission -> repeat. I may add a fast
// assumptions: all fast neutrons begin at
// fission factor for a small amount of fast fission

// update fast neutron fluxes
void sim::neutronTick() {
  std::vector<simCell> newState = this->state;

  // fission based on neutron flux

  for (int x = 1; x < SIM_CELLS_X - 1; x++) {
    for (int y = 1; y < SIM_CELLS_Y - 1; y++) {

      simCell thisCell = this->state[indexOf(x, y)];
      simCell top = this->state[indexOf(x, y + 1)];
      simCell bottom = this->state[indexOf(x, y - 1)];
      simCell right = this->state[indexOf(x + 1, y)];
      simCell left = this->state[indexOf(x - 1, y)];

      // because neutrons diffuse equally, the flux in should be about 1/4 of the flux of all adjacent cells...?
      double newFastFlux = (top.fastFlux + bottom.fastFlux + right.fastFlux + left.fastFlux) * 0.25;
      double newThermalFlux = (top.thermalFlux + bottom.thermalFlux + right.thermalFlux + left.thermalFlux) * 0.25;

      // we also need to actually remove this flux from neighboring cells for conservation of mass n stuff
      newState[indexOf(x, y + 1)].fastFlux -= 0.25 * newFastFlux;       // fast top
      newState[indexOf(x, y - 1)].fastFlux -= 0.25 * newFastFlux;       // fast bottom
      newState[indexOf(x + 1, y)].fastFlux -= 0.25 * newFastFlux;       // fast right
      newState[indexOf(x - 1, y)].fastFlux -= 0.25 * newFastFlux;       // fast left
      newState[indexOf(x, y + 1)].thermalFlux -= 0.25 * newThermalFlux; // thermal top
      newState[indexOf(x, y - 1)].thermalFlux -= 0.25 * newThermalFlux; // thermal bottom
      newState[indexOf(x + 1, y)].thermalFlux -= 0.25 * newThermalFlux; // thermal right
      newState[indexOf(x - 1, y)].thermalFlux -= 0.25 * newThermalFlux; // thermal left

      // fast fission may occur
      newFastFlux += (newFastFlux * thisCell.cellMaterial.FFF);

      // moderation may occur
      newFastFlux -= thisCell.fastFlux * thisCell.cellMaterial.moderation;
      newThermalFlux += thisCell.fastFlux * thisCell.cellMaterial.moderation;

      // thermal absorption may occur
      newThermalFlux -= thisCell.thermalFlux * thisCell.cellMaterial.sigmaA * 0.01; // yeah idk about this one cheif

      // thermal fission may occur
      newFastFlux += thisCell.thermalFlux * thisCell.cellMaterial.FFF;
    }
  }

  // update everything at once
  this->state = newState;
}

// update material temperatures
void sim::tempTick() {}
