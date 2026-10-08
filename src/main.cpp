#include "constants.h"
#include "lib/qcustomplot.h"
#include "sim.h"
#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  sim reactorSim;
  // reactorSim.tick(0.01);

  QCustomPlot coreTemp; // heatmap, literally
  auto* coreTempMap = new QCPColorMap(coreTemp.xAxis, coreTemp.yAxis);

  coreTempMap->data()->setSize(SIM_CELLS_X, SIM_CELLS_Y); // set pixel size
  coreTempMap->data()->setRange(QCPRange(0, SIM_CELLS_X), QCPRange(0, SIM_CELLS_Y));

  for (int x = 0; x < SIM_CELLS_X; x++) {
    for (int y = 0; y < SIM_CELLS_Y; y++) {
      coreTempMap->data()->setData(x, y, (x * y) - (y * y * 3));
    }
  }

  coreTempMap->setGradient(QCPColorGradient::gpThermal);
  coreTempMap->rescaleDataRange();

  coreTemp.rescaleAxes();
  coreTemp.resize(400, 400);
  coreTemp.show();

  return app.exec();
}
