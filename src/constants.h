#define CELL_SIZE_XY 0.1                         // m, cells are always squares
#define CELL_HEIGHT 1                            // m, only used for calculating cell-cell area
#define CELL_CELL_AREA CELL_HEIGHT* CELL_SIZE_XY // its in the name

#define SETUP_FILENAME "src/setup.dat"

#define DEFAULT_MATERIAL "water"
#define DEFAULT_FASTFLUX 0
#define DEFAULT_THERMALFLUX 0
#define DEFAULT_TEMP 300

#define SIM_CELLS_X 3 // sim width x axis, number of cells
#define SIM_CELLS_Y 3 // sim width y axis. number of cells
#define N_CELLS SIM_CELLS_X* SIM_CELLS_Y
