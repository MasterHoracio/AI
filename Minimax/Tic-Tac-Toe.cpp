#include <iostream>
#include <cstring>

#define INF 99999999

using namespace std;

int play_O(char[3][3], int);
int play_X(char[3][3], int);

typedef struct{
    int x, y;
}points;

points tiro;

void printBoard(char board[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << board[i][j] << " ";
        }cout << endl;
    }
}

void cpyBoard(char to[3][3], char from[3][3]){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            to[i][j] = from[i][j];
}

bool empate(char board[3][3]){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == '-')
                return false;
    return true;
}

int eval(char board[3][3], char c){
    //Nosotros somos X
    if(board[0][0] == c && board[1][1] == c && board[2][2] == c)
        return 1;
    if(board[2][0] == c && board[1][1] == c && board[0][2] == c)
        return 1;
    for(int i = 0; i < 3; i++)
        if( (board[i][0] == c && board[i][1] == c && board[i][2] == c) || (board[0][i] == c && board[1][i] == c && board[2][i] == c))
            return 1;

    return 0;
}

int play_X(char board[3][3], int depth){
    int value, min = INF;
    if(eval(board, 'O')){
        return INF;
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '-'){
                board[i][j] = 'X';
                value = play_O(board, depth + 1);
                board[i][j] = '-';
                if(value <= min){
                    min = value;
                }
            }
        }
    }
    if(min == INF)
        return 0;
    return min;
}

int play_O(char board[3][3], int depth){
    int value, max = -INF;
    if(eval(board, 'X')){
        return -INF;
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '-'){
                board[i][j] = 'O';
                value = play_X(board, depth + 1);
                board[i][j] = '-';
                if(value >= max){
                    max = value;
                    if(depth == 0){
                        tiro.x = i;
                        tiro.y = j;
                    }
                }
            }
        }
    }
    if(max == -INF)
        return 0;
    return max;
}

int main(){
    char originalBoard[3][3], cpyOfBoard[3][3];
    int x, y, ret;

    memset(originalBoard, '-', sizeof(originalBoard));
    printBoard(originalBoard);

    while(!eval(originalBoard, 'X') && !eval(originalBoard, 'O') && !empate(originalBoard)){
        cout << endl << "Dame las coordenadas de tu tiro(x, y) -> ";
        cin >> x >> y;
        originalBoard[x][y] = 'X';
        cout << "Tiro Humano ->" << endl;
        printBoard(originalBoard);
        cpyBoard(cpyOfBoard, originalBoard);
        ret = play_O(cpyOfBoard, 0);
        //cout << ret << endl;
        originalBoard[tiro.x][tiro.y] = 'O';
        cout << "Tiro Maquina ->" << endl;
        printBoard(originalBoard);
    }

    return 0;
}