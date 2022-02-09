// Nicholas Newton nnewton2
// lifefunc.h header file

#define BOARD 40
//prototypes

void initialize(char [BOARD][BOARD]); // makes blank initial board
void update(char [BOARD][BOARD]); // prints current version of the board
void addCell(char [BOARD][BOARD], int, int); // adds a cell to board
void delCell(char [BOARD][BOARD], int, int); // deletes a cell
void step(char [BOARD][BOARD]); //iterates the game
int live_test(char [BOARD][BOARD], int, int); // tests living cells
