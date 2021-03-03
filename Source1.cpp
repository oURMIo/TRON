#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 */

int main()
{
    // game loop

    int X0; // starting X coordinate of lightcycle (or -1)
    int Y0; // starting Y coordinate of lightcycle (or -1)
    int X1; // starting X coordinate of lightcycle (can be the same as X0 if you play before this player)
    int Y1; // starting Y coordinate of lightcycle (can be the same as Y0 if you play before this player)

    int pole[20][30] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };       // [higth][width]
    int PX = -100;
    int PY = -100;
    int move = 0;
    while (1) {
        move++;
        int N; // total number of players (2 to 4).
        int P; // your player number (0 to 3).
        cin >> N >> P; cin.ignore();
        cerr << "ХОД " << move << endl;
        //cerr << "Наш игрок "<< P << endl;

        for (int i = 0; i < N; i++) {

            cin >> X0 >> Y0 >> X1 >> Y1; cin.ignore();
            if (P == i) {
                cerr << " -----ЭТО НАШ----- " << P << endl;

                cerr << "Игрок " << i << " стартоваяX " << X0 << endl;
                cerr << "Игрок " << i << " стартоваяY " << Y0 << endl;
                cerr << "Игрок " << i << " текущаяX " << X1 << endl;
                cerr << "Игрок " << i << " текущаяX " << Y1 << endl;
            }
            else {
                cerr << " ---ENEMY--- " << endl;

                cerr << "Игрок " << i << " стартоваяX " << X0 << endl;
                cerr << "Игрок " << i << " стартоваяY " << Y0 << endl;
                cerr << "Игрок " << i << " текущаяX " << X1 << endl;
                cerr << "Игрок " << i << " текущаяX " << Y1 << endl;

            }
            if (PX == -100 && PY == -100)
            {
                PX = X0;
                PY = Y0;
            }
        }

        // cout << "UP" << endl; // A single line with UP, DOWN, LEFT or RIGHT
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (PX <= 2)
        {
            if (PY <= 2)    // if |_
            {
                cout << "RIGHT" << endl;
                PX += 1;
                cout << "UP" << endl;
                PY += 1;

                continue;
            }

            if (PY >= 3 && PY <= 17)   // if |
            {
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

            if (PY >= 18)   // if |?
            {
                cout << "RIGHT" << endl;
                PX += 1;
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

        }

        if (PX >= 28)
        {
            if (PY <= 2)    // if ?|
            {
                cerr << "if ?|" << endl;
                cout << "LEFT" << endl;
                PX -= 1;
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

            if (PY >= 3 && PY <= 17)   // if |
            {
                cerr << "if |" << endl;
                cout << "UP" << endl;
                PY += 1;
                continue;
            }
            if (PY >= 18)   // if _|  
            {
                cerr << "if |?" << endl;
                cout << "LEFT" << endl;
                PX -= 1;
                cout << "UP" << endl;
                PY += 1;
                continue;
            }
        }


        //hs
        if (PX >= 3 && PX <= 27)
        {
            if (PY >= 18)   // if _  
            {
                cerr << "if _" << endl;
                if (PX <= 4) {
                    cout << "LEFT" << endl;
                    PX -= 1;
                }
                if (PX >= 26) {
                    cout << "RIGHT" << endl;
                    PX += 1;
                }

                continue;
            }
            if (PY <= 2)    // if ?
            {
                cerr << "if ?" << endl;
                if (PX <= 4) {
                    cout << "LEFT" << endl;
                    PX -= 1;
                }
                if (PX >= 26) {
                    cout << "RIGHT" << endl;
                    PX += 1;
                }
            }
            cout << "RIGHT" << endl;
            PX += 1;
            continue;
            //------------alg presledovaniya no otstoy
            /*
            if(PX < X1){
                cout << "RIGHT" << endl;
                PX+=1;
                if(PY < Y1){
                    cout << "UP" << endl;
                    PY+=1;
                    continue;
                }
                if(PY > Y1){
                    cout << "DOWN" << endl;
                    PY-=1;
                    continue;
                }
            }
            if(PX > X1){
                cout << "LEFT" << endl;
                PX-=1;
                if(PY < Y1){
                    cout << "UP" << endl;
                    PY+=1;
                    continue;
                }
                if(PY > Y1){
                    cout << "DOWN" << endl;
                    PY-=1;
                    continue;
                }
            }
            //*/
        }
    }
}