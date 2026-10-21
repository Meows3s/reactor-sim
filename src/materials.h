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
 *   FFF              : -         fast fission factor excess, eps - 1: the fractional
 *                      gain of fast neutrons per fast generation in this material.
 *                      0 for anything that cannot fission (see the note below)
 *   moderation       : 0-1       fast -> thermal moderation efficiency: the fraction
 *                      of fast neutrons that reach 0.025 eV instead of being absorbed
 *                      while slowing. 1 = all of them, 0 = none (see the note below)
 *   density          : g/cm^3
 *   color            : 0-255 per channel display color; unique per material
 *
 * Two-group neutron model. Every fast neutron is taken to be at 1.5 MeV and every
 * thermal neutron at 0.025 eV, so both constants below are materials properties of
 * that two-group spectrum. Cross sections are ENDF/B-VIII.0 at 294 K and neutrons
 * per fission (nubar) is ENDF/B-VII.1, both read on the evaluations' own lin-lin grid.
 *
 *   FFF        = [sigma_f / sigma_tot](1.5 MeV) * (nubar(1.5 MeV) - 1), with
 *                sigma_tot = elastic + inelastic + capture + fission. It is the chance
 *                that a fast neutron's collision in this material is a fission times
 *                the excess neutrons that fission adds, so a fast flux F leaves
 *                F * (1 + FFF) behind and the textbook fast fission factor is
 *                eps = 1 + FFF (Pu-239 1.59, U-233 1.47, U-235 1.29, U-238 1.08).
 *                These are pure-material, undiluted values: a fast neutron that
 *                diffuses out of the cell is the neighbours' problem, so a lattice of
 *                fuel plus moderator settles lower than a solid fuel cell does.
 *   moderation = exp(-u / MR), moderating ratio MR = xi * sigma_s / sigma_a for an
 *                infinite medium with 1/E slowing down; u = ln(1.5 MeV / 0.025 eV)
 *                = 17.91 is the lethargy between the two group energies, xi the mean
 *                lethargy gain per elastic scatter (exact formula, scattering-weighted
 *                over the nuclides), sigma_s the free-atom elastic cross section at
 *                ~1 keV and sigma_a the thermal sigmaA listed above. Only real
 *                moderators light up: D2O 1.00, Be 0.88, H2O 0.75, glass 0.05, every
 *                metal, fuel and absorber ~0. It reproduces the textbook moderating
 *                ratios (H2O 62, D2O 4460, Be 138) at the two stated energies.
 */

// Display color, 0-255 per channel (straight into QColor / any RGB sink).
struct colorRGB {
  int r;
  int g;
  int b;
};

class material {
public:
  char name[32];
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
  double FFF;        // fast fission factor excess, eps - 1 (0 = no fast fission)
  double moderation; // 0-1, fraction of fast neutrons thermalised (1 = all, 0 = none)
  double density;    // g/cm^3

  // display
  colorRGB color; // RGB, unique per material
};

// --- fuel / fissile metals ---------------------------------------------------
// Fissiles are green. U-238 is fertile (capture only), so it gets a non-green
// color to stay distinguishable from the fissile isotopes at a glance.
// Pu-239: alpha phase; melting 639.4 C, boiling 3232 C. sigmaA is the isotope
// total (fission 748 + capture 269 b). At 1.5 MeV: sigma_f 1.94 b of 6.89 b total,
// nubar 3.097 -> eps = 1.589, the most fast-fissioning material in the list.
const inline material pu239 = {
    .name = "pu239",
    .specificHeat = 0.13,
    .meltPoint = 912.5,
    .boilPoint = 3505,
    .conductance = 6.7,
    .thermalExpansion = 49.6e-6,
    .z = 94,
    .atomicMass = 239.05,
    .sigmaA = 1017,
    .FFF = 0.5894,
    .moderation = 0.0,
    .density = 19.86,
    .color = {.r = 34, .g = 139, .b = 34}
}; // forest green
// Uranium metal (U-233/235/238 share metal thermophysical properties):
// melting 1132.2 C, boiling 4131 C, k ~27 W/(m*K). sigmaA is the isotope total:
// U-233 579 b, U-235 681 b, U-238 2.68 b (capture only, not fissile). Fast fission
// at 1.5 MeV: sigma_f 1.93/1.24/0.36 b of ~6.8 b total, nubar 2.648/2.594/2.599 ->
// eps = 1.469/1.291/1.083. U-238 is the pure fast-fission case: it has no thermal
// fission, so its whole FFF is the fast part, and it moderates nothing either.
const inline material u233 = {
    .name = "u233",
    .specificHeat = 0.12,
    .meltPoint = 1405.3,
    .boilPoint = 4404,
    .conductance = 27,
    .thermalExpansion = 13.9e-6,
    .z = 92,
    .atomicMass = 233.04,
    .sigmaA = 579,
    .FFF = 0.4695,
    .moderation = 0.0,
    .density = 19.05,
    .color = {.r = 0, .g = 200, .b = 0}
}; // bright green
const inline material u235 = {
    .name = "u235",
    .specificHeat = 0.12,
    .meltPoint = 1405.3,
    .boilPoint = 4404,
    .conductance = 27,
    .thermalExpansion = 13.9e-6,
    .z = 92,
    .atomicMass = 235.04,
    .sigmaA = 681,
    .FFF = 0.2909,
    .moderation = 0.0,
    .density = 19.05,
    .color = {.r = 60, .g = 179, .b = 113}
}; // medium sea green
const inline material u238 = {
    .name = "u238",
    .specificHeat = 0.12,
    .meltPoint = 1405.3,
    .boilPoint = 4404,
    .conductance = 27,
    .thermalExpansion = 13.9e-6,
    .z = 92,
    .atomicMass = 238.05,
    .sigmaA = 2.68,
    .FFF = 0.0827,
    .moderation = 0.0,
    .density = 19.05,
    .color = {.r = 139, .g = 69, .b = 19}
}; // saddle brown (fertile)

// --- coolant / moderator -----------------------------------------------------
// Waters are blue.
// Light water, liquid: freezing 0 C, boiling 100 C. sigmaA is per H2O molecule
// (H 0.332 b x2). thermalExpansion is volumetric.
// moderation 0.749 (MR 62, xi 0.925, sigma_s 1.48 cm^-1): ~1 fast neutron in 4 is
// absorbed on the way down, which is the whole reason moderating ratio != power.
const inline material water = {
    .name = "water",
    .specificHeat = 4.18,
    .meltPoint = 273.15,
    .boilPoint = 373.15,
    .conductance = 0.606,
    .thermalExpansion = 207e-6,
    .z = 7,
    .atomicMass = 18.015,
    .sigmaA = 0.664,
    .FFF = 0.0,
    .moderation = 0.7485,
    .density = 0.997,
    .color = {.r = 65, .g = 105, .b = 225}
}; // royal blue
// Heavy water (D2O): freezing 3.82 C, boiling 101.4 C. sigmaA per molecule
// (D 0.0005 b x2); the low absorption is why D2O moderates with natural uranium.
// moderation 0.996 (MR = xi*sigma_s/sigma_a = 4464, xi 0.506): the top of the scale.
const inline material waterHeavy = {
    .name = "waterHeavy",
    .specificHeat = 4.22,
    .meltPoint = 276.97,
    .boilPoint = 374.55,
    .conductance = 0.60,
    .thermalExpansion = 140e-6,
    .z = 7,
    .atomicMass = 20.028,
    .sigmaA = 0.0012,
    .FFF = 0.0,
    .moderation = 0.996,
    .density = 1.106,
    .color = {.r = 0, .g = 0, .b = 139}
}; // dark blue

// --- reflector / moderator ---------------------------------------------------
// Beryllium: melting 1287 C, boiling 2470 C; low neutron absorption (0.0092 b),
// used as a neutron reflector/moderator. moderation 0.878 (MR 138, xi 0.206): it
// gains less lethargy per scatter than H, but it hardly ever absorbs on the way.
const inline material beryllium = {
    .name = "beryllium",
    .specificHeat = 1.82,
    .meltPoint = 1560,
    .boilPoint = 2743,
    .conductance = 190,
    .thermalExpansion = 11.3e-6,
    .z = 4,
    .atomicMass = 9.012,
    .sigmaA = 0.0092,
    .FFF = 0.0,
    .moderation = 0.8781,
    .density = 1.848,
    .color = {.r = 255, .g = 215, .b = 0}
}; // gold
// Lithium: liquid-metal coolant; melting 180.5 C, boiling 1342 C. Natural Li is
// 71 b (Li-6 940 b, Li-7 0.045 b) -> isotopically separate Li-7 for coolant use;
// Li-6 is the tritium-breeding isotope. moderation 0: natural Li is 7.6% Li-6, whose
// 940 b absorbs fast neutrons before they slow (MR 0.004). Isotopically pure Li-7
// alone would only reach MR 6, moderation 0.05 - Li is a coolant, not a moderator.
const inline material lithium = {
    .name = "lithium",
    .specificHeat = 3.57,
    .meltPoint = 453.69,
    .boilPoint = 1615,
    .conductance = 85,
    .thermalExpansion = 46e-6,
    .z = 3,
    .atomicMass = 6.94,
    .sigmaA = 71,
    .FFF = 0.0,
    .moderation = 0.0,
    .density = 0.535,
    .color = {.r = 255, .g = 105, .b = 180}
}; // hot pink

// --- structural / control ----------------------------------------------------
// Boron, crystalline: melting 2076 C, boiling 3927 C. sigmaA is natural boron
// (B-10 3840 b at 19.9%); the control-rod / poison element. moderation 0
// (MR 0.001): it scatters less than it eats, so fast neutrons do not survive it.
const inline material boron = {
    .name = "boron",
    .specificHeat = 1.026,
    .meltPoint = 2349,
    .boilPoint = 4200,
    .conductance = 27.4,
    .thermalExpansion = 6e-6,
    .z = 5,
    .atomicMass = 10.81,
    .sigmaA = 760,
    .FFF = 0.0,
    .moderation = 0.0,
    .density = 2.34,
    .color = {.r = 128, .g = 0, .b = 128}
}; // purple
// Carbon steel: melting ~1425-1530 C, k ~50 W/(m*K). atomicMass / sigmaA /
// expansion are for iron (the dominant element). moderation 0 (MR 0.13): iron is a
// heavy nucleus (xi 0.035), so it absorbs more neutrons than it slows down.
const inline material steel = {
    .name = "steel",
    .specificHeat = 0.486,
    .meltPoint = 1750,
    .boilPoint = 3134,
    .conductance = 50,
    .thermalExpansion = 12e-6,
    .z = 26,
    .atomicMass = 55.845,
    .sigmaA = 2.56,
    .FFF = 0.0,
    .moderation = 0.0,
    .density = 7.85,
    .color = {.r = 105, .g = 105, .b = 105}
}; // dim gray
// Aluminum: melting 660.3 C, boiling 2519 C. moderation 0 (MR 0.42): it scatters
// fine, but at A = 27 the mean lethargy gain per hit (xi 0.072) is hopeless.
const inline material aluminum = {
    .name = "aluminum",
    .specificHeat = 0.897,
    .meltPoint = 933.5,
    .boilPoint = 2792,
    .conductance = 237,
    .thermalExpansion = 23.1e-6,
    .z = 13,
    .atomicMass = 26.982,
    .sigmaA = 0.233,
    .FFF = 0.0,
    .moderation = 0.0,
    .density = 2.70,
    .color = {.r = 192, .g = 192, .b = 192}
}; // silver
// Soda-lime glass; melting is ill-defined (softens ~730 C, melts ~1400 C).
// atomicMass / sigmaA are for SiO2 (the dominant oxide). moderation 0.053 (MR 6.1):
// SiO2 scatters plenty but O and Si are far too heavy to slow neutrons usefully.
const inline material glass = {
    .name = "glass",
    .specificHeat = 0.84,
    .meltPoint = 1673,
    .boilPoint = 2573,
    .conductance = 1.05,
    .thermalExpansion = 9e-6,
    .z = 12,
    .atomicMass = 60.08,
    .sigmaA = 0.171,
    .FFF = 0.0,
    .moderation = 0.0534,
    .density = 2.52,
    .color = {.r = 175, .g = 238, .b = 238}
}; // pale turquoise
