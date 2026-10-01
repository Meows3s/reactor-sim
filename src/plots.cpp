/*

#include "../third_party/qcustomplot/qcustomplot.h"
#include <QApplication>

void plot(void) {
  QApplication app(argc, argv);

  QCustomPlot plot;
  plot.addGraph();

  QVector<double> x, y;
  for (int i = 0; i < 200; ++i) {
    x << i * 0.05;
    y << std::sin(i * 0.05);
  }
  plot.graph(0)->setData(x, y);
  plot.xAxis->setLabel("t");
  plot.yAxis->setLabel("value");
  plot.rescaleAxes();

  plot.resize(800, 500);
  plot.show();
  return app.exec();
}

*/
