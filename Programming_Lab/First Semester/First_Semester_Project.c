#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int RXR; 

#define RED     "\033[31m"   
#define GREEN   "\033[32m"   
#define YELLOW  "\033[33m"  
#define BLUE    "\033[34m"   
#define RESET   "\033[0m"   
#define MAGENTA   "\033[35m"  
#define CYAN    "\033[36m" 

#define BOARD_SIZE 9
#define PIECE_COUNT 10

// Function prototypes 
void ChooseYourBoard();
void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]);
void generatePiece(int piece[4][4], int *piece_w,int *piece_h);
void cleanCompleted(int board[BOARD_SIZE][BOARD_SIZE],int mod,int place);
int placePiece(int board[BOARD_SIZE][BOARD_SIZE], int piece[4][4], int piece_w,int piece_h, int row, int col);
int checkAndUpdateScore(int board[BOARD_SIZE][BOARD_SIZE], int *score);
bool gameIsOver(int board[BOARD_SIZE][BOARD_SIZE],int piece[4][4],int piece_w,int piece_h ,int score);
int columnConverter(char col_c);
int binaryToDecimal(int binary[]);
void slowPrint(const char *text, unsigned int delay);
void showIntro();
void clearConsole();


int main() {    
    ChooseYourBoard();
   
    if(RXR==1){
    clearConsole();
    int board[BOARD_SIZE][BOARD_SIZE];
    int piece[4][4];
    int piece_w; // Piece width
    int piece_h; // Piece height
    int score = 0;
    int row, col;
    int pieceIndex = 0;
    int pieceCount = -1;
    bool error_ = true;
    char col_c;
    srand(time(NULL));
    initializeBoard(board);
    showIntro();
    clearConsole();

    slowPrint(RED "PLEASE DO NOT ENTER ANY TURKISH CHARACTER!!!!\nAND PLEASE FOR 'I' COLUMN ENTER 'I' OR 'i' \n\n" RESET, 20000);

    while (1) {
          // Display board and score
        slowPrint(MAGENTA "    A B C   D E F   G H I\t" RESET, 10000);
        if (error_)
        {
            generatePiece(piece, &piece_w,&piece_h);
            printf(GREEN "New Piece\t" RESET);
            pieceCount++;
        }
        else 
        {
            printf(MAGENTA "Piece\t" RESET);
            error_ = true;
        }
        printf(RED "Score:\t%d\n" RESET, score);

        for (int i = 0; i < BOARD_SIZE; i++) {
            if (i % 3 == 0) {
                slowPrint(GREEN "  +-------+-------+-------+\n" RESET, 10000);
            }
            printf(MAGENTA "%d " RESET, i + 1);
              for (int j = 0; j < BOARD_SIZE; j++) {
                  if (j % 3 == 0) printf(GREEN "| " RESET);
                  if (board[i][j] != 2)
                  {            
                      if(board[i][j]==0){
                           printf(CYAN "%d " RESET, board[i][j]);
                      }
                      else if(board[i][j]==1){
                          printf(YELLOW "%d " RESET, board[i][j]);
                      }
                  }
                  else {slowPrint(". ",10000);}

              }
              if (pieceIndex < piece_h)
              {
                  printf(GREEN "|\t" RESET);
                  for (int j = 0; j < piece_w; j++)
                  {
                      if (piece[pieceIndex][j] != 2)
                      {
                         
                          if(piece[pieceIndex][j]==0){
                              printf(CYAN "%d " RESET, piece[pieceIndex][j]);
                          }
                          else if(piece[pieceIndex][j]==1){
                              printf(YELLOW "%d " RESET, piece[pieceIndex][j]);
                          }
                      }
                      else{
                          printf("  ");
                      }
                  }
                  pieceIndex++;
                  if(i != 0) printf("\n");
              }
              else printf(GREEN "|\n" RESET);

              if(i == 0) printf(MAGENTA "\t\tPiece:\t%d\n" RESET,pieceCount);
          }
          slowPrint(GREEN "  +-------+-------+-------+" RESET, 10000);

          if (gameIsOver(board,piece,piece_w,piece_h,score)) break;

          slowPrint(CYAN "\tEnter location:" RESET, 10000);

          // This is due to Turkish characters. When a Turkish character is entered, scanf fails to recognize it.
          // So this function when a nonrecognizeable character enter, it clears to buffer so next scanf work properly.
          if (scanf(" %c%d", &col_c, &row) != 2) { 
              error_=false;
              printf(MAGENTA "\nTurkish character detected. Clearing buffer...\n" RESET);
              while (1)
              {
                  char c = getchar();
                  if (c == '\n') break; 
              }
              row = 1;
              col_c = 'A';
          }

          pieceIndex = 0;

          if (row < 1 || row > 9)
          {
              printf(MAGENTA "Please Enter a valid row. Rows are in the range of [1 , 9] \n\n" RESET);
              error_ = false;
          }

          col = columnConverter(col_c);

          if (col == -1)error_=false;

          row--; // Convert to 0-based indexing
          col--;
          if (error_)
          {
              printf("\n");
              if (placePiece(board, piece, piece_w,piece_h, row, col)) {
                  // Check and update the score
                  checkAndUpdateScore(board, &score);
              } else {
                  printf(MAGENTA "Invalid placement!\n\n" RESET);
                  error_ = false;
              }
          }
      }
      printf(MAGENTA "\n\n\nGame is Over !!! Your score : %d" RESET,score);
      int exit;
      while (1)
      {
          printf(MAGENTA "\nEnter -1 to exit: " RESET);
          scanf("%d",&exit);
          if (exit == -1)
          {
              break;
          }   
      }
  }
else if(RXR==2){
    clearConsole();
    int board[BOARD_SIZE][BOARD_SIZE];
    int piece[4][4];
    int piece_w; // Piece width
    int piece_h; // Piece height
    int score = 0;
    int row, col;
    int pieceIndex = 0;
    int pieceCount = -1;
    bool error_ = true;
    char col_c;
        srand(time(NULL));
        initializeBoard(board);
        showIntro();
        clearConsole();
        slowPrint(RED "PLEASE DO NOT ENTER ANY TURKISH CHARACTER!!!!\nAND PLEASE FOR 'I' COLUMN ENTER 'I' OR 'i' \n\n" RESET, 20000);

        while (1) {
            // Display board and score
            slowPrint(CYAN "    A B C   D E F   G H I\t" RESET, 10000);
            if (error_)
            {
                generatePiece(piece, &piece_w,&piece_h);
                printf(CYAN "New Piece\t" RESET);
                pieceCount++;
            }
            else 
            {
                printf(CYAN "Piece\t" RESET);
                error_ = true;
            }
            printf(CYAN "Score:\t" RESET YELLOW "%d\n" RESET, score);

            // Inside the main game loop where the board is printed
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i % 3 == 0) {
                    slowPrint(BLUE "  +-------+-------+-------+\n" RESET, 10000);
                }
                printf(CYAN "%d " RESET, i + 1);
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (j % 3 == 0) printf(BLUE "| " RESET);
                    if (board[i][j] == 1) {
                        printf(GREEN "1 " RESET);
                    } else if (board[i][j] == 0) {
                        printf(RED "0 " RESET);
                    } else {
                        slowPrint(". ", 10000);
                    }
                }
                if (pieceIndex < piece_h) {
                    printf(BLUE "|\t" RESET);
                    for (int j = 0; j < piece_w; j++) {
                        if (piece[pieceIndex][j] == 1) {
                            printf(GREEN "1 " RESET);
                        } else if (piece[pieceIndex][j] == 0) {
                            printf(RED "0 " RESET);
                        } else {
                            printf("  ");
                        }
                    }
                    pieceIndex++;
                    if (i != 0) printf("\n");
                } else printf(BLUE "|\n" RESET);

                if (i == 0) printf(CYAN "\t\tPiece:\t" RESET YELLOW "%d\n" RESET, pieceCount);
            }

            slowPrint(BLUE "  +-------+-------+-------+" RESET, 10000);

            if (gameIsOver(board,piece,piece_w,piece_h,score)) break;

            slowPrint(CYAN "\tEnter location:" RESET, 10000);

            // This is due to Turkish characters. When a Turkish character is entered, scanf fails to recognize it.
            // So this function when a nonrecognizeable character enter, it clears to buffer so next scanf work properly.
            if (scanf(" %c%d", &col_c, &row) != 2) { 
                error_=false;
                printf(RED "\nTurkish character detected. Clearing buffer...\n" RESET);
                while (1)
                {
                    char c = getchar();
                    if (c == '\n') break; 
                }
                row = 1;
                col_c = 'A';
            }

            pieceIndex = 0;

            if (row < 1 || row > 9)
            {
                printf(RED "Please Enter a valid row. Rows are in the range of [1 , 9] \n\n" RESET);
                error_ = false;
            }

            col = columnConverter(col_c);

            if (col == -1)error_=false;

            row--; // Convert to 0-based indexing
            col--;
            if (error_)
            {
                printf("\n");
                if (placePiece(board, piece, piece_w,piece_h, row, col)) {
                    // Check and update the score
                    checkAndUpdateScore(board, &score);
                } else {
                    printf(RED "Invalid placement!\n\n" RESET);
                    error_ = false;
                }
            }
        }
        printf(RED "\n\n\nGame is Over !!! Your score : %d" RESET,score);
        int exit;
        while (1)
        {
            printf(RED "\nEnter -1 to exit: " RESET);
            scanf("%d",&exit);
            if (exit == -1)
            {
                break;
            }   
        }

    }
}

void clearConsole() {
    // ANSI escape code to clear the screen
    printf("\033[H\033[J");
}
void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 2;
        }
    }
}
int columnConverter(char col_c)
{
    int col;
    switch (col_c)
        {
        case 'A':
        case 'a':
            col = 1;
            break;
        case 'B':
        case 'b':
            col = 2;
            break;
        case 'C':
        case 'c':
            col = 3;
            break;
        case 'D':
        case 'd':
            col = 4;
            break;
        case 'E':
        case 'e':
            col = 5;
            break;
        case 'F':
        case 'f':
            col = 6;
            break;
        case 'G':
        case 'g':
            col = 7;
            break;
        case 'H':
        case 'h':
            col = 8;
            break;
        case 'I':
        // I cannot use Ã„Â± here because it is not detecting it, And reason for this I think Ã„Â± is not An english alphabet.
        case 'i':
            col = 9;
            break;
        default:
            printf(RED "Please Enter a valid column. \n\n" RESET);
            col = -1;
            break;
        }
    return col;
}
void generatePiece(int piece[4][4], int *piece_w,int *piece_h) {
    // Clear the piece array
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece[i][j] = 2;
        }
    }
    // Select one of the 10 predefined shapes
    int shape = rand() % PIECE_COUNT; // Random number between 0 and 9
    switch (shape) {
        case 0: // Single square
            *piece_h = 1;
            *piece_w = 1;
            piece[0][0] = rand() % 2;
            break;
        case 1: // Two squares in a row
            *piece_h = 1;
            *piece_w = 2;
            piece[0][0] = rand() % 2;
            piece[0][1] = rand() % 2;
            break;
        case 2: // Two squares in a column
            *piece_h = 2;
            *piece_w = 1;
            piece[0][0] = rand() % 2;
            piece[1][0] = rand() % 2;
            break;
        case 3: // Three squares in a row
            *piece_h = 1;
            *piece_w = 3;
            piece[0][0] = rand() % 2;
            piece[0][1] = rand() % 2;
            piece[0][2] = rand() % 2;
            break;
        case 4: // Three squares in an L-shape 1
            *piece_h = 2;
            *piece_w = 2;
            piece[0][0] = rand() % 2;
            piece[1][0] = rand() % 2;
            piece[1][1] = rand() % 2;
            break;
        case 5: // Three squares in an L-shape 2
            *piece_h = 2;
            *piece_w = 2;
            piece[0][0] = rand() % 2;
            piece[0][1] = rand() % 2;
            piece[1][0] = rand() % 2;
            break;
        case 6: // Three squares in an L-shape 3
            *piece_h = 2;
            *piece_w = 2;
            piece[0][0] = rand() % 2;
            piece[0][1] = rand() % 2;
            piece[1][1] = rand() % 2;
            break;
        case 7: // Three squares in an L-shape 4
            *piece_h = 2;
            *piece_w = 2;
            piece[0][1] = rand() % 2;
            piece[1][0] = rand() % 2;
            piece[1][1] = rand() % 2;
            break;
        case 8: // Three squares in a straight line (vertical)
            *piece_h = 3;
            *piece_w = 1;
            piece[0][0] = rand() % 2;
            piece[1][0] = rand() % 2;
            piece[2][0] = rand() % 2;
            break;
        case 9: // Four squares in a 2x2 block
            *piece_h = 2;
            *piece_w = 2;
            piece[0][0] = rand() % 2;
            piece[0][1] = rand() % 2;
            piece[1][0] = rand() % 2;
            piece[1][1] = rand() % 2;
            break;
    }

}
int placePiece(int board[BOARD_SIZE][BOARD_SIZE], int piece[4][4], int piece_w,int piece_h, int row, int col) {
    // Check if the piece can be placed
   // Check if the piece can be placed
    if (row + piece_h > BOARD_SIZE || col + piece_w - ((piece[0][0] == 2) ? 1 : 0)> BOARD_SIZE || col - (piece[0][0] == 2 ? (piece_w - 1) : 0) < 0) {
        return 0; // Invalid placement
    }
    for (int i = 0; i < piece_h; i++) {
        for (int j = 0; j < piece_w; j++) {

            if (board[row + i][col + j - ((piece[0][0] == 2) ? 1 : 0)] != 2 && piece[i][j] != 2)
            {  
                    return 0; // This place already filled.
            }

        }
    }
    // Place the piece Changed
    for (int i = 0; i < piece_h; i++) {
        for (int j = 0; j < piece_w; j++) {

            if (board[row + i][col + j - ((piece[0][0] == 2) ? 1 : 0)] == 2)
                {
                    board[row + i][col + j - ((piece[0][0] == 2) ? 1 : 0)] = piece[i][j];
                } 
        }
    }
    return 1;
}
int checkAndUpdateScore(int board[BOARD_SIZE][BOARD_SIZE], int *score) {
    int completed = 0;
    int row_Pos[BOARD_SIZE] ,col_Pos[BOARD_SIZE] ,block_Pos[BOARD_SIZE] ,point_B[BOARD_SIZE] ,point_R[BOARD_SIZE] ,point_C[BOARD_SIZE], allPoint[BOARD_SIZE]; 
    int boardScore = 0;
    int Last_index_For_allPoint = -1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        row_Pos[i] = -1;
        col_Pos[i] = -1;
        block_Pos[i] = -1;
        point_B[i] = -1;
        point_R[i] = -1;
        point_C[i] = -1;
        allPoint[i] = 0;
    }
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        int row[BOARD_SIZE] = {0};
        int col[BOARD_SIZE] = {0};
        int block[BOARD_SIZE] = {0};
        int Checking_block_row = 0;

        for (int j = 0; j < BOARD_SIZE; j++) {
            row[j] = board[i][j];
            col[j] = board[j][i];
        }
        point_R[i] = binaryToDecimal(row);

        if (point_R[i] != -1) { // Full row
            row_Pos[i] = i;
            allPoint[completed++] = point_R[i];
            boardScore += point_R[i];
            if (completed==1)printf(YELLOW "\nCalculations: \n" RESET);
            printf(YELLOW " (" RESET);
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                printf(YELLOW "%d" RESET,row[i]);
            }
            printf(YELLOW ")2 = (%d)10\n" RESET,point_R[i]);
        }
        point_C[i] = binaryToDecimal(col);
        if (point_C[i] != -1) { // Full column
            col_Pos[i] = i;
            allPoint[completed++] = point_C[i];
            boardScore += point_C[i];
            if (completed==1)printf(YELLOW "\nCalculations: \n" RESET);
            printf(YELLOW " (" RESET);
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                printf(YELLOW "%d" RESET,col[i]);
            }
            printf(YELLOW ")2 = (%d)10\n" RESET,point_C[i]);
        }
        bool isFinished = false;
        int j = 0;
        int k = 0;
        int l = 0;
        while (!isFinished)
        {
            switch (Checking_block_row)
            {
            case 0:
                block[l] = board[j + 3*(i / 3)][k + 3*(i - 3*(i / 3))];
                l++;
                k++;
                if (k > 2)
                {
                    Checking_block_row = 1;
                    k = 2;
                    j++;
                }
                break;
            case 1:
                block[l] = board[j + 3*(i / 3)][k + 3*(i - 3*(i / 3))];
                k--;
                l++;
                if (k < 0)
                {
                    Checking_block_row = 2;
                    k = 0; 
                    j++;
                }
                break;    
            case 2:
                block[l] = board[j + 3*(i / 3)][k + 3*(i - 3*(i / 3))];
                l++;
                k++;
                if (k > 2)
                {
                    isFinished =  true;
                }
                break;  
            }
        }
        point_B[i] = binaryToDecimal(block);
        if (point_B[i] != -1) { // Full Block
            block_Pos[i] = i;
            allPoint[completed++] = point_B[i];
            boardScore += point_B[i];
            if (completed==1)printf(YELLOW "\nCalculations: \n" RESET);
            printf(YELLOW " (" RESET);
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                printf(YELLOW "%d" RESET,block[i]);

            }
            printf(YELLOW ")2 = (%d)10\n" RESET,point_B[i]);
        }
    }

    for (int i = 0; i < sizeof(allPoint) / sizeof(int); i++)
    {
        if (allPoint[i] != 0)
        {
            printf(YELLOW "%d" RESET,allPoint[i]);
            if (i != completed - 1) printf(" + ");
        }
    }

    if (completed)
    {
        if(completed != 1) printf(YELLOW " = %d\n%d * %d = %d \n" RESET,boardScore,boardScore,completed,boardScore*completed);
        else printf("\n");
        for (int i = 0; i < BOARD_SIZE; i++)
        {
                /* code */
            if (row_Pos[i] != -1)
                {  
                    cleanCompleted(board,0,i);
                }
            if (col_Pos[i] != -1)
                {
                    cleanCompleted(board,1,i);
                }
            if (block_Pos[i] != -1)
                {
                    cleanCompleted(board,2,i);
                }
        }
    }    

    *score += boardScore * completed;

    return completed;
}
void cleanCompleted(int board[BOARD_SIZE][BOARD_SIZE],int mod,int place)
{
    bool isFinished = false;
    int Checking_block_row = 0;
    int k = 0;
    int j = 0;
    int l = 0;
    switch (mod)
    {
    case 0:
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            board[place][i] = 2;
        }
        break;
    case 1:
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            board[i][place] = 2;
        }
        break;
    case 2:
        while (!isFinished)
        {
            switch (Checking_block_row)
            {
            case 0:
                board[j + 3*(place / 3)][k + 3*(place - 3*(place / 3))] = 2;
                l++;
                k++;
                if (k > 2)
                {
                    Checking_block_row = 1;
                    k = 2;
                    j++;
                }
                break;
            case 1:
                board[j + 3*(place / 3)][k + 3*(place - 3*(place / 3))] = 2;
                k--;
                l++;
                if (k < 0)
                {
                    Checking_block_row = 2;
                    k = 0; 
                    j++;
                }
                break;    
            case 2:
                board[j + 3*(place / 3)][k + 3*(place - 3*(place / 3))] = 2;
                l++;
                k++;
                if (k > 2)
                {
                    isFinished =  true;
                }
                break;  
            }
        }
        break;
    default:
        break;
    }
}
int binaryToDecimal(int binary[]) {
    int decimal = 0;
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        if (binary[i] == 2)
        {
            return -1;
        }

        decimal += binary[i] * pow(2,BOARD_SIZE - i - 1);
    }
    return decimal;
}
bool gameIsOver(int board[BOARD_SIZE][BOARD_SIZE],int piece[4][4],int piece_w,int piece_h ,int score){

    bool gameIsGoing = false;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            bool canPlaceable = true;
            if (row + piece_h > BOARD_SIZE || col + piece_w > BOARD_SIZE)
            {
                break;
            }
            else{
                for (int i = 0; i < piece_h; i++) {
                    for (int j = 0; j < piece_w; j++) {
                        if (board[row + i][col + j] != 2 && piece[i][j] != 2)
                        {
                            canPlaceable = false;
                            break;
                        }
                    }
                    if (!canPlaceable) break;
                }
                if (canPlaceable)
                {
                    gameIsGoing = true;
                    break;
                }
            }
            if (gameIsGoing) break;
        }
    }
    if (!gameIsGoing)
    {
        return true;
    }
    return false;
}
void ChooseYourBoard(){

    srand(time(NULL));
    char board[9][9];
      for(int i=0;i<9;i++){

        for(int j=0;j<9;j++){

          board[i][j]='.';
        }

      }  
      printf(BLUE "--------------------TEMPLATE 1--------------------\n" RESET);
    printf(MAGENTA "  A B C D E F G H J\t" GREEN "New Piece\t" RESET RED "Score:\t0\n" RESET);
    printf(GREEN " +-----+-----+-----+\n" RESET);
    int c;
    int x;
      for(int i=0; i<9; i++){
        printf(MAGENTA "%d" RESET GREEN"|" RESET, i+1); 
        for(int j=0; j<9; j++){
          if((j+1)%3!=0){
          printf(MAGENTA "%c " RESET, board[i][j]);

          }
          else if(j==8){
              printf(MAGENTA "%c" RESET GREEN "|" RESET, board[i][j]);
            switch(i){
                case 0:

                c = 0;
                if(c==0){
                    printf(CYAN " \t%d" RESET MAGENTA "\t\tPiece:\t0\n" RESET, c);
                }
                else{
                    printf(YELLOW " \t%d" RESET MAGENTA "\t\tPiece:\t0\n" RESET, c);
                }

                break;

                case 1:

                x= 1;
                if(x==0){
                    printf(CYAN " \t%d\n"RESET, x);
                }
                if(x==1){
                 printf(YELLOW " \t%d\n" RESET, x);   

                }

                break;

                default:
                printf("\n");
            }

          }
          else{
            printf(MAGENTA"%c" GREEN "|" RESET, board[i][j]);
          }

        }
        if((i+1)%9==0){
            printf(GREEN" +-----+-----+-----+\t" RESET CYAN "Enter Location:\t\n" RESET);
        }
        else if((i+1)%3==0 && (i+1)%9!=0)

        {
          printf(GREEN " +-----+-----+-----+\n" RESET);
        }
      }
      printf("\n\n");
      for(int i=0;i<9;i++){

        for(int j=0;j<9;j++){

          board[i][j]='.';
        }

      }  
      printf(BLUE "--------------------TEMPLATE 2--------------------\n" RESET);
    printf(CYAN"  A B C D E F G H J" RESET  CYAN "\tNew Piece\tScore:\t" RESET  YELLOW "0\n" RESET);
    printf(BLUE " +-----+-----+-----+\n" RESET);
    int m;
    int k;
      for(int i=0; i<9; i++){
        printf(CYAN "%d" RESET BLUE "|" RESET, i+1); 
        for(int j=0; j<9; j++){
          if((j+1)%3!=0){
          printf("%c ", board[i][j]);
          }
          else if(j==8){
              printf("%c" BLUE "|" RESET, board[i][j]);
            switch(i){

                case 0:
                m = 0;
                    printf(RED " \t%d" RESET CYAN "\t\tPiece:" RESET YELLOW "\t0\n" RESET, m);
                break;

                case 1:
                k = 1;
                    printf(GREEN " \t%d\n" RESET, k);
                
                break;

                default:
                printf("\n");
            }

          }
          else{
            printf("%c" BLUE "|" RESET, board[i][j]);
          }

        }
        if((i+1)%3==0 && (i+1)%9!=0){

            printf(BLUE " +-----+-----+-----+\n" RESET);
        }

        else if((i+1)%9==0){
          printf(BLUE " +-----+-----+-----+" RESET CYAN "\tChoose A Color Template(Enter 1 or 2):\t" RESET);
          
            if((scanf("%d", &RXR)) !=1){
                while (getchar() != '\n');  // Reads and discards characters until '\n'
                clearConsole();
                printf(RED "Please Enter a Valid Input\n" RESET);
                ChooseYourBoard();
                
            }
           else if(RXR!=1 && RXR!=2){

               while (getchar() != '\n');  // Reads and discards characters until '\n'
               clearConsole();
               printf(RED "Please Enter a Valid Number\n" RESET);
               ChooseYourBoard();
           }
        }
      }

    }
void slowPrint(const char *text, unsigned int delay) {
    static int callCount = 0; // Keeps track of the number of function calls

    callCount++; // Increment the counter on every function call

    struct timespec ts;
    ts.tv_sec = delay / 1000000;
    ts.tv_nsec = (delay % 1000000) * 1000;

    if (callCount <= 95) {
        // For the first 95 calls, print character by character with a delay
        for (int i = 0; text[i] != '\0'; i++) {
            putchar(text[i]);    // Print each character
            fflush(stdout);      // Flush the buffer immediately
            nanosleep(&ts, NULL); // Apply the specified delay
        }
    } else {
        // After 95 calls, print the text directly without delay
        printf("%s", text);
    }
}
void showIntro() {
    slowPrint(BLUE "\n*******************************\n" RESET, 10000);
    slowPrint(BLUE "*        " RESET, 10000);
    slowPrint(RED "BINARY SUDOKU" RESET, 40000);
    slowPrint(BLUE "        *\n" RESET, 10000);
    slowPrint(BLUE "*******************************\n" RESET, 10000);
    sleep(0.5);
    slowPrint(BLUE "\nGET READY!\n" RESET, 40000);
    sleep(0.5);
    slowPrint(BLUE "LOADING " RESET, 40000);
    for (int i = 0; i < 3; i++) {
        printf(RED "." RESET);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    printf("\n");
}

