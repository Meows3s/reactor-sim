#include "constants.h"
#include <vector>

/*
 * Material properties. Values are at ~25 C and 1 atm unless noted.
 *
 *   specificHeat     : J/(g*K)   mass-specific heat capacity
 *   meltPoint        : K         melting point at 1 atm
 *   boilPoint        : K         boiling point at 1 atm
 *   conductance      : W/(m*K)   thermal conductivity
 *   thermalExpansion : 1/K       linear (solids) or volumetric (liquids), at ~25 C
 *   z                : atomic number; for compounds the electron-fraction weighted
 *                      effective atomic number (Mayneord), not a proton count
 *   atomicMass       : g/mol     molecular mass for compounds, dominant element for alloys
 *   sigmaA           : barns     thermal (2200 m/s) neutron absorption cross section,
 *                      per molecule for compounds, natural isotopic mix unless noted
 *   density          : g/cm^3
 */
class material {
public:
  // heat
  double specificHeat;     // J/(g*K)
  double meltPoint;        // K
  double boilPoint;        // K
  double conductance;      // W/(m*K)
  double thermalExpansion; // 1/K

  // nuclear structure
  int z;             // protons (atomic number, or Z_eff for compounds)
  double atomicMass; // g/mol
  double sigmaA;     // barns
  double density;    // g/cm^3
};

// --- fuel / fissile metals ---------------------------------------------------
// Pu-239: alpha phase; melting 639.4 C, boiling 3232 C. sigmaA is the isotope
// total (fission 748 + capture 269 b).
material pu239 = {
    .specificHeat = 0.13, .meltPoint = 912.5, .boilPoint = 3505, .conductance = 6.7,
    .thermalExpansion = 49.6e-6, .z = 94, .atomicMass = 239.05, .sigmaA = 1017, .density = 19.86};
// Uranium metal (U-233/235/238 share metal thermophysical properties):
// melting 1132.2 C, boiling 4131 C, k ~27 W/(m*K). sigmaA is the isotope total:
// U-233 579 b, U-235 681 b, U-238 2.68 b (capture only, not fissile).
material u233 = {
    .specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27,
    .thermalExpansion = 13.9e-6, .z = 92, .atomicMass = 233.04, .sigmaA = 579, .density = 19.05};
material u235 = {
    .specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27,
    .thermalExpansion = 13.9e-6, .z = 92, .atomicMass = 235.04, .sigmaA = 681, .density = 19.05};
material u238 = {
    .specificHeat = 0.12, .meltPoint = 1405.3, .boilPoint = 4404, .conductance = 27,
    .thermalExpansion = 13.9e-6, .z = 92, .atomicMass = 238.05, .sigmaA = 2.68, .density = 19.05};

// --- coolant / moderator -----------------------------------------------------
// Light water, liquid: freezing 0 C, boiling 100 C. sigmaA is per H2O molecule
// (H 0.332 b x2). thermalExpansion is volumetric.
material water = {
    .specificHeat = 4.18, .meltPoint = 273.15, .boilPoint = 373.15, .conductance = 0.606,
    .thermalExpansion = 207e-6, .z = 7, .atomicMass = 18.015, .sigmaA = 0.664, .density = 0.997};
// Heavy water (D2O): freezing 3.82 C, boiling 101.4 C. sigmaA per molecule
// (D 0.0005 b x2); the low absorption is why D2O moderates with natural uranium.
material waterHeavy = {
    .specificHeat = 4.22, .meltPoint = 276.97, .boilPoint = 374.55, .conductance = 0.60,
    .thermalExpansion = 140e-6, .z = 7, .atomicMass = 20.028, .sigmaA = 0.0012, .density = 1.106};

// --- reflector / moderator ---------------------------------------------------
// Beryllium: melting 1287 C, boiling 2470 C; low neutron absorption (0.0092 b),
// used as a neutron reflector/moderator.
material beryllium = {
    .specificHeat = 1.82, .meltPoint = 1560, .boilPoint = 2743, .conductance = 190,
    .thermalExpansion = 11.3e-6, .z = 4, .atomicMass = 9.012, .sigmaA = 0.0092, .density = 1.848};
// Lithium: liquid-metal coolant; melting 180.5 C, boiling 1342 C. Natural Li is
// 71 b (Li-6 940 b, Li-7 0.045 b) -> isotopically separate Li-7 for coolant use;
// Li-6 is the tritium-breeding isotope.
material lithium = {
    .specificHeat = 3.57, .meltPoint = 453.69, .boilPoint = 1615, .conductance = 85,
    .thermalExpansion = 46e-6, .z = 3, .atomicMass = 6.94, .sigmaA = 71, .density = 0.535};

// --- structural / control ----------------------------------------------------
// Boron, crystalline: melting 2076 C, boiling 3927 C. sigmaA is natural boron
// (B-10 3840 b at 19.9%); the control-rod / poison element.
material boron = {
    .specificHeat = 1.026, .meltPoint = 2349, .boilPoint = 4200, .conductance = 27.4,
    .thermalExpansion = 6e-6, .z = 5, .atomicMass = 10.81, .sigmaA = 760, .density = 2.34};
// Carbon steel: melting ~1425-1530 C, k ~50 W/(m*K). atomicMass / sigmaA /
// expansion are for iron (the dominant element).
material steel = {
    .specificHeat = 0.486, .meltPoint = 1750, .boilPoint = 3134, .conductance = 50,
    .thermalExpansion = 12e-6, .z = 26, .atomicMass = 55.845, .sigmaA = 2.56, .density = 7.85};
// Aluminum: melting 660.3 C, boiling 2519 C.
material aluminum = {
    .specificHeat = 0.897, .meltPoint = 933.5, .boilPoint = 2792, .conductance = 237,
    .thermalExpansion = 23.1e-6, .z = 13, .atomicMass = 26.982, .sigmaA = 0.233, .density = 2.70};
// Soda-lime glass; melting is ill-defined (softens ~730 C, melts ~1400 C).
// atomicMass / sigmaA are for SiO2 (the dominant oxide).
material glass = {
    .specificHeat = 0.84, .meltPoint = 1673, .boilPoint = 2573, .conductance = 1.05,
    .thermalExpansion = 9e-6, .z = 12, .atomicMass = 60.08, .sigmaA = 0.171, .density = 2.52};

class simCell {

public:
private:
  double temp;
  double nFlux;
};