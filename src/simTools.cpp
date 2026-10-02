#include "constants.h"
#include <vector>

class material {
public:
  // heat
  double specificHeat; // j/k
  double meltPoint;    // k
  double boilPoint;    // k
  double conductance;  // W / (m*k)

  // nuclear structure
  int z;          // protons
  double density; // g/cm^3
};

material pu233 = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material u233 = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material u235 = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material u238 = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material water = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material waterHeavy = {
    .specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material boron = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material steel = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material aluminum = {
    .specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};
material glass = {.specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27, .z = 0, .density = 19.05};

class simCell {

public:
private:
  double temp;
  double nFlux;
};
