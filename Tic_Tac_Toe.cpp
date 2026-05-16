//Tic Tac Toe with two players

#include <iostream>
#define O 'O'
#define X 'X'
#define BOARD 3

class TicTacToe{
    private:
        char board[BOARD*BOARD];
        char player;
    public:
        TicTacToe(){
            for(int i = 0 ; i < BOARD*BOARD ; i++){
                board[i] = ' ';
            }
            player = '0';
        }

        void PrintBoard(){
            for(int i = 0 ; i < BOARD*BOARD ; i++){
                char board_ = board[i];
                if( board_ == ' '){
                    std::cout << i << ' ';
                }else{
                    std::cout << board_ << ' ';
                }
                if( (i+1) % BOARD == 0 ){
                    std::cout << std::endl;
                }
            }
        }
        //这个函数还有值得优化的地方，因为确定是赢的排列方式中一定包含了place位置的棋子
        bool Is_Win(){
            auto three_equal = [](char a, char b, char c){
                return a != ' ' && a == b && b == c;
            };

            // rows
            for(int i = 0; i < BOARD; i++){
                if(three_equal(board[i*BOARD], board[i*BOARD+1], board[i*BOARD+2]))
                    return true;
            }
            // columns
            for(int i = 0; i < BOARD; i++){
                if(three_equal(board[i], board[i+BOARD], board[i+6]))
                    return true;
            }
            // main diagonal
            if(three_equal(board[0], board[4], board[8]))
                return true;
            // sub diagonal
            if(three_equal(board[2], board[4], board[6]))
                return true;

            return false;
        }

        int game(){
            PrintBoard();

            int place = 0;
            std::cout << "请玩家'" << player << "'放置棋子:";
            std::cin >> place;
            while( (place < 0 || place > 8) || !(board[place] == ' ') ){
                std::cout << "请重新输入:";
                std::cin >> place;
            }
            board[place] = (player == '0') ? (O) : (X);

            if(!Is_Win()){
                player = ( (player == '0') ? ('1') : ('0') );
                return game();
            }else{
                PrintBoard();
                std::cout << "player'" << player << "'wins!" << std::endl;
                return 0;
            }
        }
};

int main(){
    TicTacToe Game;
    Game.game();
    return 0;
}