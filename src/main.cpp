#include "plots.h"
#include "sim.h"
#include <qapplication.h>
#include <qobject.h>
#include <qtimer.h>

int main(int argc, char** argv) {
  QApplication Qapp(argc, argv);

  sim reactorSim(SETUP_FILENAME); // load the setup
  reactorSim.dump();              // display every cell for debugging

  fastFluxPlot FFP(SIM_CELLS_X, SIM_CELLS_Y);
  FFP.resize(600, 600); // a parentless QWidget is a top-level window, but it has to be given a size
  FFP.show();           // ...and shown, or nothing is ever mapped to the screen

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&] {
    reactorSim.neutronTick();
    FFP.setData(reactorSim.state);
    FFP.redraw();
  });
  timer.start(20);

  Qapp.exec();
}
