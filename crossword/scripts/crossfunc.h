/*crossfunc.h
  file header function prototypes*/

// protopypes...
#define BD 15
typedef struct {
	int row;
	int col;
	char pword[20];
	char locate[7];
} Clue;

void initialize (char[BD][BD], char[BD][BD]);
void print_bd (char[BD][BD], FILE *save);
void upper(char [20][BD], int);
void print_uL(char [20][BD], int, FILE *save);
void sort_big(char [20][BD], int);
void p_init(char [BD[BD], char [20][BD], Clue [20]);
void next_word(char [BD][BD], char [20][BD], int, Clue [20], int);
void mPuz(char[BD][BD], char [BD]BD]);
void print_clues(Clue [20], FILE *save);
