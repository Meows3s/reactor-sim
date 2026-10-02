#include "constants.h"
#include <vector>
/*
 * assumptions:
 *  PWR
 *  uranium in core does not deplete (looking at short timescale)
 *  containment vessel does not heat up meaningfully
 *
 */
class reactor {
public:
  // setters
  void setWaterFlowRate(float);
  void setControlRodPos(float);
  void setNeutronsExternal(long long);
  // getters / calc-ers
  void calcCoreTemp(void);

private:
  // nuclear parameters, fixed
  float enrichment = 0.1; // how much of fuel is u235 (normalized)
  float fuelXSize = 0.25; // m
  float fuelYSize = 0.25; // m
  float fuelXOrigin = 0.25;
  float fuelYOrigin = 0.25;

  float vesselXSize = 3; // m
  float vesselYSize = 3; // m

  // core nuclear state
  float k;
  std::vector<std::vector<float>> coreTemp;
  std::vector<std::vector<float>> nFlux;

  // core coolant state
  float waterFlowRate; // l/s through core
  float boronConcentration;

  // core power state
  float thermalPower; // MW

  // turbine state
  float turbinePower; // MW
  float turbineSpeed; // rpm
};

// set by control loop:
void reactor::setWaterFlowRate(float flowSetpoint) { this->waterFlowRate = flowSetpoint; }

void reactor::setControlRodPos(float posSetpoint) { this->controlRodPos = posSetpoint; }

// derived from core conditions:
void reactor::calcCoreTemp(void) {

  for (int x = 0; x < SIM_CELLS_X; x++) {
    for (int y = 0; y < SIM_CELLS_Y; y++) {
    }
  }

  return 0.0;
}

void reactor::calcNFlux() { return 0.0; }
