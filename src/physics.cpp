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
      double newFastFlux += (top.fastFlux + bottom.fastFlux + right.fastFlux + left.fastFlux) * 0.25;

      // fast fission may occur
      newFastFlux += (newFastFlux * thisCell.cellMaterial.FFF);

      // moderation may occur

      // assume neutrons flow out to all sides equally, divide by 4
    }
  }
}

// update material temperatures
void sim::tempTick() {}
