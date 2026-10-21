#include "plots.h"
#include "lib/qcustomplot.h"
#include <qwidget.h>

/*

class materialPlot : public QCustomPlot {
public:
  materialPlot(int sizeX, int sizeY, QWidget* parent = nullptr);
  void setData(std::vector<simCell>);
  void redraw();

private:
  QCPColorMap* map;
  int sizeX, sizeY;
  std::vector<simCell> data;
}
vecto*/

fastFluxPlot::fastFluxPlot(int sizeX, int sizeY, QWidget* parent) {
  this->sizeX = sizeX; // params shadow the members, so copy them in before redraw() uses them
  this->sizeY = sizeY;
  map = new QCPColorMap(xAxis, yAxis);
  map->data()->setSize(sizeX, sizeY);
  map->data()->setRange(QCPRange(0, sizeX), QCPRange(0, sizeY));
  map->setDataRange(QCPRange(0, 2000));
  map->setGradient(QCPColorGradient::gpHot);
  rescaleAxes();
}

void fastFluxPlot::setData(std::vector<simCell> input) { data = input; }

void fastFluxPlot::redraw() {
  for (int x = 0; x < sizeX; x++) {
    for (int y = 0; y < sizeY; y++) {
      map->data()->setCell(x, y, data[x + (y * sizeX)].fastFlux);
    }
  }
  replot(QCustomPlot::rpQueuedReplot); // filling the color map's data does not repaint the widget on its own
}
