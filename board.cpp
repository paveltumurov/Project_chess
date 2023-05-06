#include <iostream>
using namespace std;
void board() {
    for (int row = 7; row >= 0; row--) {

        // Draws Horizontal Row Dividers
        cout << "   ";
        for (int col = 0; col < 8; col++) {
            cout << "-----";
        }
        cout << "-" << endl;


        // Draws Vertical Row Divider and Chess Piece
        cout << row + 1 << "  ";
        for (int col = 0; col < 8; col++) {
            cout << "| ";
            
            cout << "  ";
            
            cout << " ";
        }

        // Draws Divider for end of Row
        cout << "|" << endl;

    }

    // Draws Horitonal Divider for last Row
    cout << "   ";
    for (int col = 0; col < 8; col++) {
        cout << "-----";
    }
    cout << "-" << endl;

    // Draws Letters on botton of board
    cout << "   ";
    for (int col = 0; col < 8; col++) {
        cout << "  " << (char) (col + 97) << "  ";
    }
    cout << endl << endl;

}
int main()
{
    board();
}