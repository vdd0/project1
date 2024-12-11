/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Victoria
 *
 * Created on December 9, 2024, 2:08 AM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <stack>
#include <limits>
#include <queue>
#include<list>

using namespace std;


class connect4{
    static const int rows=6;
    static const int cols=7;
    
    // these store the players name and checker pieces.
    pair <string,char> player;
    pair <string, char> opponent;
    
    /// set the slots available, with the  cols as the key, 
    //and the row as the values;
    map <int, int> slots= {{0,rows-1},{1,rows-1},{2,rows-1},
    {3,rows-1},{4,rows-1},{5,rows-1}, {6,rows-1}};
    // the count variable is used to determine how many col slots
    // are full. It is used in the end class function.
    int count=0;
    
    
public:
     // the winner is initialized to draw but changed if otherwise;
    // these member variables are accessible so that they can be stored by another
    // class to print
    string winner="draw";
    string opp=opponent.first;
    map <pair<int,int>, char> board;
    // the setUsers flag is directly used  by the parameterized constructor   
    bool setUsers=false;
    
    // constructor sets the board ONLY.
    connect4(){
        setBoard();
    }
    
    // this constructor with arguments for players
    // sets the boad, players, and the setUser flag used
    // in the playTurn function;
    connect4( string player1, string player2){
        setBoard();
        player.first =player1;
        opponent.first =player2;
        if( player1 == ""&& player2=="")setUsers=false;
        else{
        setUsers=true;
        }
    }
  
   // this function sets the Board to empty slots
    void setBoard(){
        for (int i=0; i < rows; i++){
            for ( int j=0; j < cols; ++j){
                board[{i,j}]=' ';
            }
        }
    }

    
    //  this function  plays one Turn and is repeatedly called until the 
    // game end condition has been met.
    void playTurn() {
      int col_input;
      cout<< "*****************************************************"<<endl;
      cout<< player.first << "'s turn.\t\t\tchecker piece: "<<player.second <<"\n\n";
      print();
    
        
      if( player.first== "Computer"){
          cout<< "............waiting on opponent.........."<<endl;
          col_input= computerTurn();
        }  
      else {
          cout<< "Enter column (1-7): ";
          cin>> col_input;
         
        /// validate input by checking edge cases:
        // 1) if the value is not the right type, clear the err state and try again
        // 2) if the column is full ( slots[col_input-1] returns the row, if it is -1
        //    the column is full
        // 3) if the column input is greater than the board or less than, request
        //    for a valid entry          
          while (slots[col_input-1]<0 || col_input>7 || col_input<0 || cin.fail()){
              if (slots[col_input-1]<0 ){
                cout<< "COLUMN IS FULL. Please enter a valid column.\n";
              }
              else{
                  cout<< " Please enter a valid column between (1-7)\n";
                  cin.clear();
                  cin.ignore(numeric_limits<std::streamsize>::max(),  '\n');
              }
                
                cin >> col_input;
            }
             
      }
        
        // update board
        updateBoard(col_input-1);
        // if at that specified column, the row value is -1, then
        // we can add that to the count of cols filled
        // once all columns are filled, we end the game if not done so already.
        if(slots[col_input-1]==-1)++count;
       
        if(!end()){
         swap(player,opponent);
       }
    }
    
    
    void updateBoard (int col){
        // instead of iterating through each row and finding an empty slot in
        // that column, we will iterate through the key:col  value and 
        // directly insert the chip at row= slots[col] (value) and 
        // col= col
        // then update the value of the row slot for the column.
        // this assumes all slots are zero bc we are updating the value
        // in key everytime
        board[{slots[col],col}]=player.second;
        slots[col]= slots[col]-1;
        
    }
    
    
    bool end(){
        // the condition to end the game is as follows:
        // 1) there exists a winner ( check horizontal, vertical, and diagnols)
        // 2) no winner exists (all slots are filled)
        return count==7 || checkOutcome(0,1,-1,4,0) || checkOutcome(-1,0,2,7,0) || checkOutcome(-1,1,2,4,0) || checkOutcome(-1,-1,2,7,3);
        
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
               
            for(int j=col_start; j<col_bounds; ++j){
                
               if(board[{i,j}] != ' ' && (board[{i,j}] == board[{i+x,j+y}]) && (board[{i,j}] == board[{i+2*x,j+2*y}]) && (board[{i+3*x,j+3*y}] == board[{i,j}]) ){
          
                        return true;
                }
            }
        }
        return false;

    }
    
   void displayWin(){ 
       // print the board and the appropriate winner
       print();
       cout<< endl;
        if ( count ==7){
        cout<<setw(30)<< "ITS A DRAW !" <<endl;
        }
       // store these values into the public variables 
       // such that if playing another round, they are accessible
       // and/or useful for displaying the winner after the game ends.
       winner=player.first;
       opp= opponent.first;
       cout<<setw(15)<<" " <<"FINAL BOARD : "<< winner<< " WON!"<<endl;
        print();
        
        
    }
    
   // this function is called every time a player plays a Turn
   // so that they can see where each checker is placed
   // and place there's elsewhere.
    void print(){
        cout<< "*****************************************************"<<endl;
        cout<<setw(36)<<" 1  2  3  4  5  6  7\n";
        for (int i=0; i <rows; i++){
            cout<<setw(15)<<" ";
            for ( int j=0; j <cols; j++){     
                        cout<< setw(1) << "[" <<board[{i,j}] <<"]";
                }
                cout<<endl;
            }
        cout<< "*****************************************************"<<endl;

    }
    
    // this is the first function called from the connect4 class that is called.
    // it displays the menu and sets up key pieces of the game
    // such as players, checker pieces (chips), and who goes first.
    void displayMenu(){
        char choose_option;
        string  username;
        int    checkerPiece;
        cout<< "------------------------------------------------------------------------";
        cout<< "\n" <<setw(46)<<"STARTING CONNECT 4 GAME" <<"\n";
        cout<<"-------------------------------------------------------------------------"<<endl;
        cout<< "RULES:"<<endl;
        cout<< "Each player gets a turn to drop their checkers on the board\n";
        cout<< "You can only drop your checker into a column\n";
        cout<< "The first to connect 4 same colored checkers\nhorizontally/vertically/diagonally wins!\n";
        
        // in the case that multiple games are played (rounds)
        // check if users have been preset. If they have then we can skip
        // having to ask our user for input and instead ask them
        // to choose thier checker piece.
        if(!setUsers){
            cout<<"\nChoose:\n1- to play with someone else\n2- to play against a computer\n";
            cin>> choose_option;
            cout<< endl;

            cout<< "Please enter a name for player 1: ";
            cin>> username;
            player.first=username;

            if ( choose_option == '1'){
                cout<<"\nPlease enter a name for the opponent (player 2): ";
                cin>>username;
                opponent.first=username;
                cout<<endl;
            }
            else {
                cout<<"Your opponent is the Computer." <<endl;
                opponent.first= "Computer";
                cout<<endl;
            }
        } 
        // END OF INTITIALZIATION of players and opponent type.
        /// display the player to choose their checker piece.
        // automatically choose the first player and then randomly choose
        // which player takes the first turn
        
        cout<<endl;
        cout<< player.first; 
        
        //validate that the player chooses a checker piece
        // if the user inputs a rndm key, clear the error state/buffer
        // and try again until the condition is met
       
        while(true){
            cout<< " enter your checker piece 1-X and 2-O"<<endl;
            cin>>checkerPiece;

            if(checkerPiece == 1 || checkerPiece ==2)break;

             cout<< " Please enter a valid piece"<<endl;

             cin.clear();
             cin.ignore(numeric_limits<std::streamsize>::max(),  '\n');

        }
        // set checker pieces
       
        player.second='X';
        opponent.second='O';
        if ( checkerPiece==2){
           swap(player.second, opponent.second);
          
         }
        cout<< endl;
        
        cout<< "...............Choosing who goes first............."
                ".."<<endl;
        if ( randomTurn() =='1'){
            cout<< " Player 1: " << player.first << " goes first!"<<endl;
        }
        else {
            cout<< " Player 2: " << opponent.first << " goes first!"<<endl;
            swap(player,opponent);
        }

    }
     
    // this is a simple rnd function for playing against the computer
    // if the board at is not empty then choose from any of the columns;
    int computerTurn(){
        srand(time(0));
         int availableCol= rand()% cols;
        //check whether col is available. If not, find one that is. 
        while ( board[{0,availableCol}] != ' '){
            availableCol= rand()% cols;
        }
       // cout<< " computer col choosen is "<< availableCol<<endl;
        return availableCol;
    
    }
    
    // this decides which player goes first. this is a helper function
     int randomTurn(){
        int player= rand()%2;
        return player;
    }
    
};
// END OF connect4 GAME CLASS

// BEGINNING OF HELPER FUNCTIONS
//
//
// this function takes the result board after a win/draw was declared
// and prints it.
void printMap( map<pair<int,int>,char> g){
    
     cout<< "*****************************************************"<<endl;
        cout<<setw(36)<<" 1  2  3  4  5  6  7\n";
        for (int i=0; i <6; i++){
            cout<<setw(15)<<" ";
            for ( int j=0; j <7; j++){     
                        cout<< setw(1) << "[" <<g[{i,j}] <<"]";
                }
                cout<<endl;
            }
        cout<< "*****************************************************"<<endl;
}
//
// this function prints the leaderboard of wins, draws.
void printLeaderboard(map<string,int> b, list<int> score){
    cout<<endl;
    cout<< "LEADERBOARD"<<endl;
    cout<< "name         wins "<<endl;
    
    stack<int> orderedSc;
    stack<string>name;
    
    score.sort();
    
    for (const int& sc : score) {
        orderedSc.push(sc);
        
       for (auto& in : b) {
        // If mapped value is K,
        // then print the key value
          // cout<< in.second << " finding val "<<endl;
        if (in.second == sc) {
          //  cout<< " name assoc is "<< in.first <<endl;
            name.push(in.first);
            auto it=b.find(in.first);
            if ( it!=b.end()){
                b.erase(it);
                break;
            }
        }
      
        }
    }
    
    while ( !orderedSc.empty()){
//        name.pop();
//        cout<< " - ";
        int top= orderedSc.top();
        orderedSc.pop();
        string  og= name.top();
        name.pop();
        cout<< og <<setw(6) <<"-"<<setw(6) << top <<endl; 
    }
//    
    
    cout<<endl;
    
    // player.first, with 5 
}

// this one is the unsorted leaderboard, its in the order of the games played.
void unsortedLead(map<string,int> led){
    
   cout << " this is leadb: "<<endl;
    
    for ( auto j: led){
        cout<< j.first << " "<< j.second <<endl;
    }
    
}

// this function takes the gameHistory queue and prints the board, the winner and
// the total games played.

void print(queue<pair<map<pair<int,int>,char>,string>> h){
    cout<< "GAME HISTORY: "<<endl;
    cout<<endl;
    int i=1;
    map<string,int> leaderboard;
    string name;
    
    int sc;
   list<int> score;
    // iterate through the records of games until empty
    while(!h.empty() ){
        cout<< "round: " <<i;
        // starting from the inside of the queue, we take 
        // the top element and intialize a pair to access the board
        // and the winner
       pair< map<pair<int,int>,char> ,string> obj= h.front();
       // set a map to the first element in pair. this is the board!!
       map<pair<int,int>,char> gb= obj.first;
       // print out the winner
       cout<< setw(40)<<obj.second<< " WON! "<<endl;
       // push into a leaderboard;
       name= obj.second;
       auto ij= leaderboard.find(name);
       if( ij != leaderboard.end()){
           sc= leaderboard[name];
           leaderboard[name]+=1;
           auto it = find(score.begin(), score.end(), sc);
           if ( it!= score.end()) {
              // auto distance(score.begin(), it);
                replace(score.begin(),score.end(), sc, leaderboard[name] );
           }
       }else{
       leaderboard.insert({name,1});
       sc=leaderboard[name];
       
       score.push_back(sc);
       }
       // send the map to the printMap
       printMap(gb);
        ++i;
        // increase the rounds counter for the game;
        h.pop();
        // remove the previous game; 
    }
    printLeaderboard(leaderboard,score);
 
}

int main(int argc, char** argv) {
    
    char def;
    bool validinp=false;
    //connect4 game;
    queue <pair<  map<pair<int,int>,char> ,string>> gameHistory;
    
    int inp;
    char samePlayers='N';
    string p1="";
    string p2="";
    
    cout<< " welcome! how many games will you play? "<<endl;
    cout<< " choose between 1-5"<<endl;
    cin >> inp;
   
    // Play as many rounds as specified unless player chooses to quit.
    for( int i=0; i < inp; ++i){
        cout<< " ROUND "<<i+1 <<endl;
        // check if the game is being played with the same person.
        connect4 game(p1,p2);

        game.displayMenu();
        while ( ! game.end()){
            cout<<endl;
            game.playTurn();
        }
        game.displayWin();
        // after that game is finished, push the game into the gameHistory queue
       gameHistory.push(make_pair(game.board, game.winner));
       // if we are not on the last round, ask user if they
       // will play with the same opponent or switch
        if ( i+1!= inp){
        cout<<endl;
        cout<< " will you be playing the next round with the same person?"<<endl;
        cout<< " press Y for yes, press N for No"<<endl;
        cout<< " if you would like to quit press any key"<<endl;

        cin>> samePlayers;
        samePlayers= toupper(samePlayers);

        // if they choose to continue playing with the same person
        // then set the players
            if ( samePlayers =='Y' ){
                p1=game.winner;
                p2=game.opp;
            }
        // if not, reset the players names and the flag
            else if ( samePlayers =='N'){
                cout<<endl;
                cout<< " Got it! you'll be asked for player's & opponent's name."<<endl;
                samePlayers='N';
                p1="";
                p2="";
            }
            else{
                break;
            }
        }
    }    
    cout<<".............................EXITING........................."<<endl;
    
   cout<<endl;
   cout<<endl;
   cout<< setw(30)<<"Thanks for playing! "<<endl<<endl;
   print(gameHistory);

    return 0;
}

