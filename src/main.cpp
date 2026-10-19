#include "sim.h"
int main(int argc, char** argv) {
  sim reactorSim(SETUP_FILENAME);
  reactorSim.dump(); // display every cell for debugging
}
