#include <iostream>
#include <cmath>
#include <string>
using namespace std;

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };      // Pieces.
enum Color { WHITE, BLACK, NONE };                                  // Colors.

class Square
{
    Piece piece;
    Color color;
    int x, y;
public:
    void setSpace(Square*);
    void setEmpty();
    void setPieceAndColor(Piece, Color);
    Piece getPiece();
    Color getColor();
    void setX(int ex) { x = ex; }
    void setY(int why) { y = why; }
    int getX() { return x; }
    int getY() { return y; }
    Square();
};

class Board
{
    Square square[8][8];
    Color turn=WHITE;
    bool moveKing(Square* thisKing, Square* thatSpace);
    bool moveQueen(Square* thisQueen, Square* thatSpace);
    bool moveBishop(Square* thisBishop, Square* thatSpace);
    bool moveKnight(Square* thisKnight, Square* thatSpace);
    bool moveRook(Square* thisRook, Square* thatSpace);
    bool movePawn(Square* thisPawn, Square* thatSpace);
    bool makeMove(int x1, int y1, int x2, int y2);
    void printBoard();
public:
    Square* getSquare(int x, int y) {
        return &square[x][y];
    }
    void setSquare(Square * s, int x, int y){
        square[x][y]=*s;
    }
    bool doMove();
    
    void setBoard();
    bool playGame();
};

Square::Square()
{
    piece = EMPTY;
    color = NONE;
}

void Square::setSpace(Square* space)
{
    color = space->getColor();
    piece = space->getPiece();
}

void Square::setEmpty()
{
    color = NONE;
    piece = EMPTY;
}

Piece Square::getPiece()
{
    return piece;
}

Color Square::getColor()
{
    return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
    piece = p;
    color = c;
    
}


void Board::printBoard() {
//    cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
    cout<<endl<<"     Y->"<<"   0     1     2     3     4     5     6     7   "<<endl;
    cout<<" X       _____ _____ _____ _____ _____ _____ _____ _____ "<<endl;
    for (int i = 0; i < 8; i++)
    {
        cout<<"        |     |     |     |     |     |     |     |     |"<<endl;
        cout << " " << i << "      ";
        for (int j = 0; j < 8; j++)
        {
            Piece p = square[i][j].getPiece();
            Color c = square[i][j].getColor();
            
            switch (p)
            {
                case KING: (c == WHITE) ? cout << "|  K  " : cout << "|  k  ";
                    break;
                case QUEEN: (c == WHITE) ? cout << "|  Q  " : cout << "|  q  ";
                    break;
                case BISHOP:(c == WHITE) ? cout << "|  B  " : cout << "|  b  ";
                    break;
                case KNIGHT:(c == WHITE) ? cout << "|  N  " : cout << "|  n  ";
                    break;
                case ROOK: (c == WHITE) ? cout << "|  R  " : cout << "|  r  ";
                    break;
                case PAWN: (c == WHITE) ? cout << "|  P  " : cout << "|  p  ";
                    break;
                case EMPTY: cout << "|     ";
                    break;
                default: cout << "XXX";
                    break;
            }
        }
        cout<<"|";
        cout<<endl<<"        |_____|_____|_____|_____|_____|_____|_____|_____|"<<endl;
    }
    
}

bool Board::doMove() {
    string move;
    int x1=0, x2=0, y1=0, y2=0;
    bool stop = false;
    while (!stop)
    {
        (turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
        cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
        cin >> move;
        x1 = move[0] - 48;
        y1 = move[1] - 48;
        x2 = move[2] - 48;
        y2 = move[3] - 48;
        if (getSquare(x1, y1)->getColor() == turn)
        {
            
            
            if (makeMove(x1, y1, x2, y2) == false)
            {
                cout << "Invalid move, try again." << endl;
            }
            else
                stop = true;
        }
        else
            cout << "That's not your piece. Try again." << endl;
    }
    if (getSquare(x2, y2)->getPiece() == KING){
        if (getSquare(x1, y1)->getColor() == WHITE){
            cout << "WHITE WINS" << endl;
            return false;
        }
        else{
            cout << "BLACK WINS" << endl;
            return false;
        }
    }
    
    if (turn == BLACK)
        turn = WHITE;
    else
        turn = BLACK;
    
    return true;
    
}

void Board::setBoard()
{
    square[0][0].setPieceAndColor(ROOK, WHITE);
    square[1][0].setPieceAndColor(KNIGHT, WHITE);
    square[2][0].setPieceAndColor(BISHOP, WHITE);
    square[3][0].setPieceAndColor(QUEEN, WHITE);
    square[4][0].setPieceAndColor(KING, WHITE);
    square[5][0].setPieceAndColor(BISHOP, WHITE);
    square[6][0].setPieceAndColor(KNIGHT, WHITE);
    square[7][0].setPieceAndColor(ROOK, WHITE);
    
    square[0][7].setPieceAndColor(ROOK, BLACK);
    square[1][7].setPieceAndColor(KNIGHT, BLACK);
    square[2][7].setPieceAndColor(BISHOP, BLACK);
    square[3][7].setPieceAndColor(QUEEN, BLACK);
    square[4][7].setPieceAndColor(KING, BLACK);
    square[5][7].setPieceAndColor(BISHOP, BLACK);
    square[6][7].setPieceAndColor(KNIGHT, BLACK);
    square[7][7].setPieceAndColor(ROOK, BLACK);
    
    for (int i = 0; i < 8; i++)
    {
        square[i][1].setPieceAndColor(PAWN, WHITE);
        square[i][6].setPieceAndColor(PAWN, BLACK);
        
    }
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
            square[j][i].setPieceAndColor(EMPTY, NONE);
        
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            square[i][j].setX(i);
            square[i][j].setY(j);
        }
    
}

bool Board::playGame(){
    printBoard();
    return doMove();
}

bool Board::moveKing(Square* thisKing, Square* thatSpace) {
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)
    if (abs(thatSpace->getX() - thisKing->getX()) == 1)
        if (abs(thatSpace->getY() - thisKing->getY()) == 1)
        {
            thatSpace->setSpace(thisKing);
            thisKing->setEmpty();
            return true;
        }
        else return false;
        else return false;
}
bool Board::moveQueen(Square* thisQueen, Square* thatSpace) {
    //there might be problems with numbers of brackets
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)
    
    int queenX = thisQueen->getX();
    int queenY = thisQueen->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    cout << "this";
    int yIncrement;
    int xIncrement;
    
    bool invalid = false;
    if (queenX != thatX || queenY != thatY)
    {
        
        if (queenX == thatX)
        {
            yIncrement = (thatY - queenY) / (abs(thatY - queenY));
            for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
            {
                
                if (square[thatX][i].getColor() != NONE)
                    return false;
                
            }
        }
        else
            if (queenY == thatY)
            {
                
                xIncrement = (thatX - queenX) / (abs(thatX - queenX));
                for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
                {
                    if (square[i][thatY].getColor() != NONE)
                        return false;
                }
            }
            else
                if (abs(queenX - thatX) == abs(queenY - thatY))
                {
                    xIncrement = (thatX - queenX) / (abs(thatX - queenX));
                    yIncrement = (thatY - queenY) / (abs(thatY - queenY));
                    
                    for (int i = 1; i < abs(queenX - thatX); i++)
                    {
                        std::cout << "It got here somehow";
                        if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
                            return false;
                        
                    }
                }
                else return false;
    }
    
    
    
    if (invalid == false)
    {
        thatSpace->setSpace(thisQueen);
        thisQueen->setEmpty();
        return true;
    }
    else return false;
}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) {
    //there might be problems with number of brackets
    int bishopX = thisBishop->getX();
    int bishopY = thisBishop->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    bool invalid = false;

    if (abs(bishopX - thatX) == abs(bishopY - thatY))
    {
        int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
        int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));
        
        for (int i = 1; i < abs(bishopX - thatX); i++)
        {
            std::cout << "It got here somehow";
            if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
                return false;
            
        }
    }
    else
        return false;
    
    if (invalid == false)
    {
        thatSpace->setSpace(thisBishop);
        thisBishop->setEmpty();
        return true;
    }
    else
    {
        return false;
    }
}
bool Board::moveKnight(Square* thisKnight, Square* thatSpace)
{
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)
    int knightX = thisKnight->getX();
    int knightY = thisKnight->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    
    if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
    {
        thatSpace->setSpace(thisKnight);
        thisKnight->setEmpty();
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::moveRook(Square* thisRook, Square* thatSpace)
{
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)
    int rookX = thisRook->getX();
    int rookY = thisRook->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    bool invalid = false;
    if (rookX != thatX || rookY != thatY)
    {
        
        if (rookX == thatX)
        {
            int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
            for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
            {
                
                if (square[thatX][i].getColor() != NONE)
                    return false;
                
            }
        }
        else
            if (rookY == thatY)
            {
                
                int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
                for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
                {
                    if (square[i][thatY].getColor() != NONE)
                        return false;
                }
            }
            else
                return false;
    }
    if (invalid == false)
    {
        thatSpace->setSpace(thisRook);
        thisRook->setEmpty();
        return true;
    }
    else
    {//Return some erorr or something. Probably return false;
        cout << "That is an invalid move for rook";
        return false;
    }
}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) {
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)

    int pawnX = thisPawn->getX();
    int pawnY = thisPawn->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();
    
    
    if (thisPawn->getColor() == WHITE)
    {
        
        if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
        {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
        else
            if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getColor() == BLACK)
            {
                thatSpace->setSpace(thisPawn);
                thisPawn->setEmpty();
                return true;
            }
            else
                return false;
    }
    else
        if (thisPawn->getColor() == BLACK)
        {
            if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
            {
                thatSpace->setSpace(thisPawn);
                thisPawn->setEmpty();
                return true;
            }
            else
                if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getColor() == WHITE)
                {
                    thatSpace->setSpace(thisPawn);
                    thisPawn->setEmpty();
                    return true;
                }
                else
                    return false;
        }
        else
            return false;
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
    //Checking for turns will be done previous to this
    if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
    {
        cout << "One of your inputs was our of bounds" <<endl;
        return false;
    }
    Square* src = getSquare(x1, y1);
    Square* dest = getSquare(x2, y2);
    
    if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
    {
        cout << "Invalid move: cannot land on your own piece" << endl;
        return false;
    }
    
    switch (src->getPiece())
    {
        case KING: return moveKing(src, dest);
            break;
        case QUEEN: return moveQueen(src, dest);
            break;
        case BISHOP: return moveBishop(src, dest);
            break;
        case KNIGHT: return moveKnight(src, dest);
            break;
        case ROOK: return moveRook(src, dest);
            break;
        case PAWN: return movePawn(src, dest);
            break;
        case EMPTY: cout << "You do not have a piece there" << endl;  return false;
            break;
        default: cout << "Something went wrong in the switch statement in makeMove()" << endl;
            break;
    }
    return false;
}

int main()
{
    Board b;
    string s;
    bool newgame = true;
    
    cout << "A 2 player chess game by Shivanshu Chaubey !"<<endl<<endl;
    
//    cout << "Enter any key to continue" << endl;
//    cin >> s;
    
    while(newgame){
        b.setBoard();
        while (b.playGame());
        cout << "Do you want to play again? ('y' for yes, anything else for no) ";
        cin >> s;
        if (s != "y") newgame = false;
    }
}
