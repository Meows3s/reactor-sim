/*
 * assumptions:
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
  float calcWaterTemp(void);
  float calcFuelTemp(void);

private:
  // nuclear parameters, fixed
  float enrichment; // percent u235
  float fuelID;     // m
  float fuelOD;     // m

  // core nuclear state
  float k;
  long long neutronsFast;
  long long neutronsThermal;
  long long neutronsExternal; // non-fission neutrons injected by neutron source

  // core mechanical state
  float controlRodPos; // m extended from top
  float fuelTemp;

  // core coolant state
  float waterTemp; // deg C
  float waterVoids;
  float waterFlowRate; // l/s through core
  float waterPressure; // bar
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

void reactor::setNeutronsExternal(long long neutronSetpoint) {}

// derived from core conditions:
float reactor::calcWaterTemp() { return 0.0; }

float reactor::calcFuelTemp() { return 0.0; }
