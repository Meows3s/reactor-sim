#include "lib/qcustomplot.h"
#include "sim.h"
#include <vector>
#pragma once

class tempPlot : public QCustomPlot {
public:
  tempPlot(int sizeX, int sizeY, QWidget* parent = nullptr);
  void setData(std::vector<simCell>);
  void redraw();

private:
  QCPColorMap* map;
  int sizeX, sizeY;
  std::vector<simCell> data;
};
