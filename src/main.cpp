#include "lib/qcustomplot.h"
#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QCustomPlot neutronFlux; // heatmap
  QCustomPlot coreTemp;    // heatmap, literally
  QCustomPlot k;           // xy plot with respect to t

  auto* neutronFluxMap = new QCPColorMap(neutronFlux.xAxis, neutronFlux.yAxis);
  auto* coreTempMap = new QCPColorMap(coreTemp.xAxis, coreTemp.yAxis);

  k.addGraph();

  QVector<double> x, y;
  for (int i = 0; i < 200; ++i) {
    x << i * 0.05;
    y << std::sin(i * 0.05);
  }

  k.graph(0)->setData(x, y);
  k.setWindowTitle("k effective");
  k.xAxis->setLabel("");
  k.yAxis->setLabel("deg c");
  k.rescaleAxes();

  k.resize(800, 500);
  k.show();

  return app.exec();
}
