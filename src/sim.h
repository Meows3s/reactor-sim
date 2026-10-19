#pragma once
#include "constants.h"
#include "materials.h"
#include <vector>

class simCell {
public:
  // parameters
  material cellMaterial;

  // current nuclear state
  double fastFlux;
  double thermalFlux; // thermal neutrons, not temperature !

  // current mechanical state
  double temp;

  void dump();
};

class sim {
public:
  int fastTick();
  int thermalTick();
  void dump();
  sim(const char* filename); // constructor, also loads the sim from a file

  std::vector<simCell> state;
};
