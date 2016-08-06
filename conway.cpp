#include <stdio.h>

struct Cell {
    bool alive;
};

struct Board {
    Cell boardContents[64];
    bool existsLife;
};

void initializeEmptyBoard(Board &gameBoard) {
    int i,j;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            gameBoard.boardContents[8*i+j].alive = false;
        }
    }
    gameBoard.existsLife = false;
}

void greeting() {
    printf("Hello! This is a simple Conway's Game of Life simulator!\n");
    printf("The rules are simple:\n");
    printf("The board is 8x8, but the edges are stuck together, so actually you play on a torus.\n");
    printf("Each cell has 8 neighbors: 2 horizontal, 2 vertical and 4 diagonal.\n");
    printf("Each cell is either alive or dead. On each step the board updates according to the following rules:\n");
    printf("(note that the rules depend on the information you enter after this introduction)\n");
    printf("1. If a dead cell has N alive neighbors, it becomes alive.\n");
    printf("2. If an alive cell has less than M or more than L alive neighbors, it dies, otherwise it stays alive.\n");
    printf("Now you have to provide N,M and L.\n");
}

int getDeadToAliveThreshold() {
    int N;
    printf("Enter N (Conway's canonical N = 3):\n");
start:
    scanf("%d", &N);
    if ((N<0)||(N>8)) {
        printf("N has to be between 0 and 8. Enter N (Conway's canonical N = 3):\n");
        goto start;
    }
    return N;
}

int getAliveToDeadMinimum() {
    int M;
    printf("Enter M (Conway's canonical M = 2):\n");
start:
    scanf("%d", &M);
    if ((M<0)||(M>8)) {
        printf("M has to be between 0 and 8. Enter M (Conway's canonical M = 2):\n");
        goto start;
    }
    return M;
}

int getAliveToDeadMaximum() {
    int L;
    printf("Enter L (Conway's canonical L = 3):\n");
start:
    scanf("%d", &L);
    if ((L<0)||(L>8)) {
        printf("L has to be between 0 and 8. Enter L (Conway's canonical L = 3):\n");
        goto start;
    }
    return L;
}

void introBoard() {
    printf("Now you will enter the starting position for the board.\n");
    printf("You will have to type in an 8x8 matrix containing 0 and 1. 0 is a dead cell, 1 is an alive cell.\n");
    printf("Remember to make a space between cells in a single row.\n");
}

void getBoard(Board &gameBoard) {
    int i,j;
    int cell;
    printf("Enter starting board:\n");
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
        start:
            scanf("%d", &cell);
            if ((cell<0)||(cell>1)) {
                printf("You have to enter either a 0 or a 1");
                goto start;
            }
            if(cell == 1){
                gameBoard.boardContents[8*i+j].alive = true;
                gameBoard.existsLife = true;
            }
        }
    }
}

void finalIntro() {
    printf("Great, all information needed is provided and we are ready to start.\n");
    printf("But before we start the simulation, here are the informations about the controls:\n");
    printf("Each step is executed individually. To progress to the next step press \"n\" on your keyboard.\n");
    printf("To exit the simulation, press \"q\".\n");
    printf("OK, we are ready to start! Press \"n\" to start after you see your initial board.\n");
}

void showBoard(Board gameBoard) {
    int i,j;
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            if (gameBoard.boardContents[8*i+j].alive) {
                printf("1 ");
            }
            else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int searchNeighbors(Cell neighbors[]){
    int i;
    int number = 0;
    for (i=0; i<8; i++) {
        if (neighbors[i].alive){
            number++;
        }
    }
    return number;
}

void processStep(Board &gameBoard, int N, int M, int L) {
    int i,j,k;
    int number;
    Board tempBoard;
    Cell neighbors[8];
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            if ((i!=0)&&(i!=7)&&(j!=0)&&(j!=7)) {
                neighbors[0] = gameBoard.boardContents[8*(i-1)+j];
                neighbors[1] = gameBoard.boardContents[8*(i-1)+(j+1)];
                neighbors[2] = gameBoard.boardContents[8*i+(j+1)];
                neighbors[3] = gameBoard.boardContents[8*(i+1)+(j+1)];
                neighbors[4] = gameBoard.boardContents[8*(i+1)+j];
                neighbors[5] = gameBoard.boardContents[8*(i+1)+(j-1)];
                neighbors[6] = gameBoard.boardContents[8*i+(j-1)];
                neighbors[7] = gameBoard.boardContents[8*(i-1)+(j-1)];
            }
            if ((i==0)&&(j!=0)&&(j!=7)) {
                neighbors[0] = gameBoard.boardContents[8*7+j];
                neighbors[1] = gameBoard.boardContents[8*7+(j+1)];
                neighbors[2] = gameBoard.boardContents[8*0+(j+1)];
                neighbors[3] = gameBoard.boardContents[8*1+(j+1)];
                neighbors[4] = gameBoard.boardContents[8*1+j];
                neighbors[5] = gameBoard.boardContents[8*1+(j-1)];
                neighbors[6] = gameBoard.boardContents[8*0+(j-1)];
                neighbors[7] = gameBoard.boardContents[8*7+(j-1)];
            }
            if ((i==7)&&(j!=0)&&(j!=7)) {
                neighbors[0] = gameBoard.boardContents[8*6+j];
                neighbors[1] = gameBoard.boardContents[8*6+(j+1)];
                neighbors[2] = gameBoard.boardContents[8*7+(j+1)];
                neighbors[3] = gameBoard.boardContents[8*0+(j+1)];
                neighbors[4] = gameBoard.boardContents[8*0+j];
                neighbors[5] = gameBoard.boardContents[8*0+(j-1)];
                neighbors[6] = gameBoard.boardContents[8*7+(j-1)];
                neighbors[7] = gameBoard.boardContents[8*6+(j-1)];
            }
            if ((j==0)&&(i!=0)&&(i!=7)) {
                neighbors[0] = gameBoard.boardContents[8*(i-1)+0];
                neighbors[1] = gameBoard.boardContents[8*(i-1)+1];
                neighbors[2] = gameBoard.boardContents[8*i+1];
                neighbors[3] = gameBoard.boardContents[8*(i+1)+1];
                neighbors[4] = gameBoard.boardContents[8*(i+1)+0];
                neighbors[5] = gameBoard.boardContents[8*(i+1)+7];
                neighbors[6] = gameBoard.boardContents[8*i+7];
                neighbors[7] = gameBoard.boardContents[8*(i-1)+7];
            }
            if ((j==7)&&(i!=0)&&(i!=7)) {
                neighbors[0] = gameBoard.boardContents[8*(i-1)+7];
                neighbors[1] = gameBoard.boardContents[8*(i-1)+0];
                neighbors[2] = gameBoard.boardContents[8*i+0];
                neighbors[3] = gameBoard.boardContents[8*(i+1)+0];
                neighbors[4] = gameBoard.boardContents[8*(i+1)+7];
                neighbors[5] = gameBoard.boardContents[8*(i+1)+6];
                neighbors[6] = gameBoard.boardContents[8*i+6];
                neighbors[7] = gameBoard.boardContents[8*(i-1)+6];
            }
            if ((i==0)&&(j==0)) {
                neighbors[0] = gameBoard.boardContents[8*7+0];
                neighbors[1] = gameBoard.boardContents[8*7+1];
                neighbors[2] = gameBoard.boardContents[8*0+1];
                neighbors[3] = gameBoard.boardContents[8*1+1];
                neighbors[4] = gameBoard.boardContents[8*1+0];
                neighbors[5] = gameBoard.boardContents[8*1+7];
                neighbors[6] = gameBoard.boardContents[8*0+7];
                neighbors[7] = gameBoard.boardContents[8*7+7];
            }
            if ((i==0)&&(j==7)) {
                neighbors[0] = gameBoard.boardContents[8*7+7];
                neighbors[1] = gameBoard.boardContents[8*7+0];
                neighbors[2] = gameBoard.boardContents[8*0+0];
                neighbors[3] = gameBoard.boardContents[8*1+0];
                neighbors[4] = gameBoard.boardContents[8*1+7];
                neighbors[5] = gameBoard.boardContents[8*1+6];
                neighbors[6] = gameBoard.boardContents[8*0+6];
                neighbors[7] = gameBoard.boardContents[8*7+6];
            }
            if ((i==7)&&(j==0)) {
                neighbors[0] = gameBoard.boardContents[8*6+0];
                neighbors[1] = gameBoard.boardContents[8*6+1];
                neighbors[2] = gameBoard.boardContents[8*7+1];
                neighbors[3] = gameBoard.boardContents[8*0+1];
                neighbors[4] = gameBoard.boardContents[8*0+0];
                neighbors[5] = gameBoard.boardContents[8*0+7];
                neighbors[6] = gameBoard.boardContents[8*7+7];
                neighbors[7] = gameBoard.boardContents[8*6+7];
            }
            if ((i==7)&&(j==7)) {
                neighbors[0] = gameBoard.boardContents[8*6+7];
                neighbors[1] = gameBoard.boardContents[8*6+0];
                neighbors[2] = gameBoard.boardContents[8*7+0];
                neighbors[3] = gameBoard.boardContents[8*0+0];
                neighbors[4] = gameBoard.boardContents[8*0+7];
                neighbors[5] = gameBoard.boardContents[8*0+6];
                neighbors[6] = gameBoard.boardContents[8*7+6];
                neighbors[7] = gameBoard.boardContents[8*6+6];
            }
            
            number = searchNeighbors(neighbors);
            if (!gameBoard.boardContents[8*i+j].alive) {
                if (number==N) {
                    tempBoard.boardContents[8*i+j].alive = true;
                    tempBoard.existsLife = true;
                }
                else {
                    tempBoard.boardContents[8*i+j].alive = false;
                }
            }
            else {
                if ((number>=M)&&(number<=L)) {
                    tempBoard.boardContents[8*i+j].alive = true;
                    tempBoard.existsLife = true;
                }
                else {
                    tempBoard.boardContents[8*i+j].alive = false;
                }
            }
        }
    }
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            gameBoard.boardContents[8*i+j].alive = tempBoard.boardContents[8*i+j].alive;
        }
    }
    gameBoard.existsLife = tempBoard.existsLife;
    showBoard(gameBoard);
}

int main(){
    int i;
    int j;
    int N,M,L;
    char flag;
    Board gameBoard;
    initializeEmptyBoard(gameBoard);
    greeting();
    N = getDeadToAliveThreshold();
    M = getAliveToDeadMinimum();
    L = getAliveToDeadMaximum();
    introBoard();
    getBoard(gameBoard);
    finalIntro();
    showBoard(gameBoard);
    while (true) {
        scanf("%c", &flag);
        if (flag == 'n') {
            processStep(gameBoard,N,M,L);
        }
        if (flag == 'q') {
            break;
        }
    }
    printf("Thanks for playing our Conway's Game of Life simulator!\n");
    return 0;
}












