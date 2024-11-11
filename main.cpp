#include <iostream>
#include <list>
#include <iomanip>  // used to seed in rnd 
#include <stack>
#include <algorithm> // used for fill
//#include <string>
//remove using namespace std;
using namespace std;

class gameBoard{
    static const int max_rows=6;
    static const int max_cols=7;
    int slots_left=-1;
    //int rounds= max_rows*max_cols;

    list <int> colsRange= {0,1,2,3,4,5,6};
    pair<string,char> player;
    pair<string,char> opponent;
    stack <char> checkWin;
 
    char board[max_rows][max_cols];
    public:
     gameBoard(){
        fill(board[0],board[0]+max_cols*max_rows,' ');
    };
    
    void print(){
        cout<<" 1  2  3  4  5  6  7\n";
        for (unsigned int i=0; i <max_rows; i++){
            for (unsigned int j=0; j <max_cols; j++){     
                        cout<< setw(1) << "[" <<board[i][j] <<"]";
                }
                cout<<endl;
            }

        cout<< endl;

    }
    void playTurn(){

        int col_input;
        displayTurn();
   
        if ( player.first == "Computer"){
            cout<< "..... waiting on opponent...."<<endl;
            col_input= computerTurn();
        }
        else{
        cout<< "Enter column ( 1-7): ";
        cin >> col_input;
    
            while (board[0][col_input-1] != ' '){
                cout<< "COLUMN IS FULL. Please enter a valid column.\n";
                cin >> col_input;
            }
            
            if( col_input <0 || col_input>7){
                throw out_of_range("player entered a value out of range");
            }
        }
        // change_board;
        updateBoard(col_input-1);
        //--rounds;
        //cout<< rounds <<endl;
        swap(player,opponent);

    }
    void displayTurn(){
        cout<< "*****************************************************"<<endl;
        cout<< player.first << "'s turn.    checker piece:   "<<player.second <<"\n\n";

        print();

        cout<< "****************************************************"<<endl;


    }
    void displayMenu(){
        int choose_option;
        string  username;
        int    checkerPiece;
        cout<< "------------------------------------------------------------------------";
       cout<< "\n" <<setw(46)<<"STARTING CONNECT 4 GAME" <<"\n";
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<< "RULES:"<<endl;
        cout<< "Each player gets a turn to drop their checkers on the board\n";
        cout<< "You can only drop your checker into a column\n";
        cout<< "The first to connect 4 same colored checkers\nhorizontally/vertically/diagonally wins!\n";
        cout<<"\nChoose:\n1- to play with someone else\n2- to play against a computer\n";

        cin>> choose_option;

       cout<< endl;

        cout<< "Please enter a name for player 1: ";
        cin>> username;
        player.first=username;

        if ( choose_option == 1){
            cout<<"\nPlease enter a name for the opponent (player 2): ";
            cin>>username;
            opponent.first=username;
            cout<<endl;
        }
        else {
            cout<<"Your opponent is the Computer." <<endl;
            opponent.first= "Computer";
        }

        cout<< player.first; 
        // validation for checkPiece input
        while (true){
           cout<< " choose your checker piece " <<"\n1- X\n2- O"<<endl;
           cin>> checkerPiece;

           if ( checkerPiece ==1 || checkerPiece == 2){
            break;
           }
           else{
            cout<<" Invalid range, Please ";
           }

        }

        player.second='X';
        opponent.second='O';
        if ( checkerPiece== 2){
            swap(player.second, opponent.second);

        }
        cout<< endl;
        
        cout<< ".......Choosing who goes first....."<<endl;
        if ( randomTurn() ==1){
            cout<< " Player 1: " << player.first << " goes first!"<<endl;
        }
        else {
            cout<< " Player 2: " << opponent.first << " goes first!"<<endl;
            swap(player,opponent);
        }

    }
    void updateBoard(int column){
        int row= max_rows;
       
        while ( row >=0 ){
            if (board[row][column]== ' '){
                 board[row][column]= player.second;
                break;
            }
            --row;
        }
   
    }

    bool endGame(){
        //only declare draw here.
        cout<< slots_left<< "rounds left" << endl;
        if ( slots_left==0){
            cout<< "DRAW! "<<endl;
            slots_left-=2;
        }
    //HORIZONTAL ONLY BOUNDS AT COL 3  VERT BOUNDS AT  ROW3        DIAG LOW-HIGH  COL:3 ROW:3       no more rounds     
        return checkOutcome(0,1,-1,4,0) || checkOutcome(-1,0,2,7,0) || checkOutcome(-1,1,2,4,0)||  slots_left==-2 || checkOutcome(-1,-1,2,7,3);
        
    }

    bool checkOutcome(int x, int y, int row_bounds, int col_bounds, int col_start){
        //a player can win if they get 4 checkers horizontally, vertically, or diagonally
        // the linear combination for each case is:
        // horizontal:   x+0, y+1
        // vertical:     x-1, y+0
        // diagonally (lower left to upper right):   x-1, y+1
        // diagonally  (upper left to lower right):   x-1, y-1   i must be between 
        //traverse through the height from the last row.
        for ( int i=5; i>row_bounds; --i){
            slots_left = count(board[0],board[0]+max_cols*max_rows,' ');
            if(slots_left ==0 )return true;               
            for(unsigned int j=col_start; j<col_bounds; ++j){
                //changed char fill
               if(board[i][j] != ' ' && (board[i][j] == board[i+x][j+y]) && (board[i][j] == board[i+2*x][j+2*y]) && (board[i+3*x][j+3*y] == board[i][j]) ){
                         print();
                         cout<< board[i][j] << " "<< board[i+x][j+y]<< " "<< board[i+2*x][j+2*y]<< " "<< board[i+3*x][j+3*y]<<endl;
                         // because we swap one time and we check outcome outside of playing turn.
                        cout<< opponent.first << " WON! "<<endl;
                        return true;
                }
            }
        }
        return false;

    }

    int computerTurn(){    

        int availableCol= rand()% max_cols;
        //check whether col is available. If not, find one that is. 
        while ( board[0][availableCol] != ' '){
            availableCol= rand()% max_cols;
        }
    return availableCol;

    }

    int randomTurn(){
        int player= rand()%2;
        return player;
    }

};


int main() {

    gameBoard connect4;
    srand(time(0)); // seed rnd with respect to time
    
    cout<< "PLAYING CONNECT 4"<<endl;
    connect4.displayMenu();

    while ( !connect4.endGame()){
        cout<<endl;
        connect4.playTurn();
    }

    return 0;
}