#define CELL_SIZE_XY 0.1                         // m, cells are always squares
#define CELL_HEIGHT 1                            // m, only used for calculating cell-cell area
#define CELL_CELL_AREA CELL_HEIGHT* CELL_SIZE_XY // its in the name

#define SETUP_FILENAME "setup.dat"

#define SIM_CELLS_X 4 // sim width x axis, number of cells
#define SIM_CELLS_Y 4 // sim width y axis. number of cells
#define N_CELLS SIM_CELLS_X* SIM_CELLS_Y
