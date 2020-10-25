/**
This is a pretty basic command line Tic-Tac-Toe game.
Its been totally done to death, but I felt like it would
be a relatively easy way to apply what I've learned with
C++ so far.

Author: CKilburn12 (Colin Kilburn)
**/
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


/**
The board class serves to create a board object with
ways to check if anyone has won the game of Tic-Tac-Toe
**/
class Board
{
    private:   
        //Starts out with a blank board.
        vector<vector<string>> board = {{" ", " ", " "}, 
                                       {" ", " ", " "}, 
                                       {" ", " ", " "}};      
    public:
        /**
        Returns the 2D board vector.
        **/
        vector<vector<string>> getArray()
        {
            return board;
        }


        /**
        Ensures a valid move by the player, if it is,
        the board is updated and true is returned. Otherwise it does nothing
        and returns false.
        **/
        bool setArray(int row, int col, string player)
        {
            bool safeRow = row < 3 && row >= 0;
            bool safeCol = col < 3 && row >=0;
            bool safeIndex = safeRow && safeCol;
            
            if(safeIndex) 
            {
                if(board[row][col] == " ") //checking for a blank place within the board.
                {
                    board[row][col] = player;
                    return true;
                }
            }
            return false;
        }


        /**
        Calls the functions to check if someone has won on rows, columns, or diagonal.
        **/
        bool checkWinStatus()
        {
            return (checkRow() || checkCol() || checkDiag());
        }


        /**
        Checks if either player has won on any of the three rows.
        **/
        bool checkRow()
        {
            for(int col = 0; col<3; col++)
            {
                bool twoEqual = !board[col][0].compare(board[col][1]);
                bool threeEqual = !board[col][1].compare(board[col][2]);
                bool notBlank = board[col][0].compare(" ");

                if(twoEqual && threeEqual && notBlank)
                    return true;
            }
            return false;
        }


        /**
        Checks if either player has won on any of the three columns.
        **/
        bool checkCol()
        {
            for(int row = 0; row<3; row++)
            {
                bool twoEqual = !board[0][row].compare(board[1][row]);
                bool threeEqual = !board[1][row].compare(board[2][row]);
                bool notBlank = board[0][row].compare(" ");
                
                if(twoEqual && threeEqual && notBlank)
                    return true;
            }
            return false;
        }


        /**
        Checks if either player has won on either diagonal.
        **/
        bool checkDiag()
        {
            bool leftToRight{false};
            bool rightToLeft{false};
            bool twoEqual{false};
            bool threeEqual{false};
            
            
            bool notBlank = board[1][1].compare(" ");

            twoEqual = !board[0][0].compare(board[1][1]);
            threeEqual = !board[2][2].compare(board[1][1]);

            leftToRight = twoEqual && threeEqual;
            
            twoEqual = !board[0][2].compare(board[1][1]);
            threeEqual = !board[2][0].compare(board[1][1]);

            rightToLeft = twoEqual && threeEqual;
            
            return ((rightToLeft || leftToRight) && notBlank);
        }
};


/**
Overloading the << operator for a board object to display
the values divided by | characters.
**/
ostream& operator<<(ostream& os, Board& b)
{   
    vector<vector<string>> board = b.getArray();
    
    for(int i = 0; i < 3; i++)
    {
        os << "|";
        for(int j = 0; j < 3; j++)
        {
            os << board[i][j] + "|";
        }
        os << "\n";
    }
    return os;
}


/**
This function takes input of rows and cols and puts it into a map.
Using a map is probably overkill for this, but I'm trying to learn C++
**/
map<string, int> userInput()
{
    map<string, int> position;
    int row{};
    int col{};
    
    cout << "Row: ";
    cin >> row;

    cout << "Column: ";
    cin >> col;

    position.insert(make_pair("Row", --row));
    position.insert(make_pair("Col", --col));

    return position;
}


/**
This goes through everything that needs to happen on each turn,
including clearing the screen, displaying the board, and taking the input
**/
void playerTurn(string player, Board& b)
{
    map<string, int> position;
    string playerName{};
    bool validMove{};
    
    do
    {
        if(player == "X") playerName = "Player 1";
        else playerName = "Player 2";

        cout << playerName << "\n";
        position = userInput();
        validMove = b.setArray(position["Row"], position["Col"], player);
        
        system("clear");
        cout << b;
        if(!validMove) cout << "Not a valid move!\n";

    } while(!validMove);

}


/**
Main function,
just shows the blank board then starts calling the turn function.
Stops running once someone wins.
**/
int main()
{
    Board newBoard;

    system("clear");
    cout << newBoard;
    
    while(true)
    {
        playerTurn("X", newBoard);
        if(newBoard.checkWinStatus()) 
        {
            system("clear");
            cout << "Player 1 Wins!";
            break;
        }
        
        playerTurn("O", newBoard);
        if(newBoard.checkWinStatus()) 
        {
            system("clear");
            cout << "Player 2 Wins!";
            break;
        }
    }         
    return 0;
}