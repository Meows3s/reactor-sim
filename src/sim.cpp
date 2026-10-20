#include "sim.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream> //sure, let's just include all the streams why not
#include <string>

#define DEFAULT_MATERIAL "water"
#define DEFAULT_FASTFLUX 0
#define DEFAULT_THERMALFLUX 0
#define DEFAULT_TEMP 300

sim::sim(const char* filename) {

  // build the map
  // TODO: make this extensible... somehow
  std::map<std::string, material> matMap = {
      {"pu239",      pu239     },
      {"u233",       u233      },
      {"u235",       u235      },
      {"u238",       u238      },
      {"water",      water     },
      {"waterHeavy", waterHeavy},
      {"beryllium",  beryllium },
      {"lithium",    lithium   },
      {"boron",      boron     },
      {"steel",      steel     },
      {"aluminum",   aluminum  },
      {"glass",      glass     }
  };

  std::ifstream setupFile(filename);

  /*
   * setup.dat file format:
   * int xpos, int ypos, string material, double fastFluxInit, double thermalFluxInit, double tempInit.
   * <other cells>
   *
   * note: if unspecified, everything is assumed to be DEFAULT_MATERIAL. Don't question it
   * */

  this->state.resize(N_CELLS);
  simCell defaultCell = {.cellMaterial = matMap.find(DEFAULT_MATERIAL)->second,
                         .fastFlux = DEFAULT_FASTFLUX,
                         .thermalFlux = DEFAULT_THERMALFLUX,
                         .temp = DEFAULT_TEMP};

  for (int i = 0; i < N_CELLS; i++) {
    this->state[i] = defaultCell;
  }

  std::string thisLine;
  while (std::getline(setupFile, thisLine)) {

    std::istringstream lineStream(thisLine);

    std::string xpos;
    std::string ypos;
    std::string cellMaterial;
    std::string fastFlux;
    std::string thermalFlux;
    std::string temp;

    if (!(lineStream >> xpos >> ypos >> cellMaterial >> fastFlux >> thermalFlux >> temp)) {
      std::cerr << "!!! setup parse fail !!!" << std::endl; // epic parse fail
    }

    auto lookup = matMap.find(cellMaterial);
    material thisMaterial = lookup->second;
    if (lookup == matMap.end()) {
      std::cerr << "!!! material lookup failed for material '" << cellMaterial << "' !!!\n";
      thisMaterial = glass;
    }

    simCell thisCell = {.cellMaterial = thisMaterial,
                        .fastFlux = std::stod(fastFlux),
                        .thermalFlux = std::stod(thermalFlux),
                        .temp = std::stod(temp)};
    int thisCellIndex = std::stoi(xpos) + std::stoi(ypos) * SIM_CELLS_X;

    this->state[thisCellIndex] = thisCell; // update
  }
  std::cout << "done loading." << std::endl;
}

int sim::indexOf(int x, int y) { return (x + SIM_CELLS_X * y); }

// debug utils
void simCell::dump() {
  std::cout << "cell material: " << this->cellMaterial.name << "\n cell fast neutron flux: " << this->fastFlux
            << "\n cell thermal neutron flux: " << this->thermalFlux << "\ncell temperature: " << this->temp << std::endl;
}

void sim::dump() {
  for (int i = 0; i < N_CELLS; i++) {
    std::cout << "\ncell number " << i << std::endl;
    this->state[i].dump();
  }
}
