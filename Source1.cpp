﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // game loop
    int X0; // starting X coordinate of lightcycle (or -1)
    int Y0; // starting Y coordinate of lightcycle (or -1)
    int X1; // starting X coordinate of lightcycle (can be the same as X0 if you play before this player)
    int Y1; // starting Y coordinate of lightcycle (can be the same as Y0 if you play before this player)

    int pole[20][30] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };       // [height][width]
    int PX = -100;
    int PY = -100;
    int move = 0;
    while (1) {
        move++;
        int N; // total number of players (2 to 4).
        int P; // your player number (0 to 3).
        cin >> N >> P; cin.ignore();
        cerr << "STEP " << move << endl << endl;
        //cerr << "Наш Player "<< P << endl;

        for (int i = 0; i < N; i++) {

            cin >> X0 >> Y0 >> X1 >> Y1; cin.ignore();
            if (P == i) {
                cerr << " -----THIS MY----- " << P << endl << endl;

                cerr << "Player " << i << " Start_X " << X0 << endl;
                cerr << "Player " << i << " Start_Y " << Y0 << endl;
                cerr << "Player " << i << " Now_X " << X1 << endl;
                cerr << "Player " << i << " Now_Y " << Y1 << endl << endl;
            }
            else {
                cerr << " ---ENEMY--- " << endl << endl;

                cerr << "Player " << i << " Start_X " << X0 << endl;
                cerr << "Player " << i << " Start_Y " << Y0 << endl;
                cerr << "Player " << i << " Now_X " << X1 << endl;
                cerr << "Player " << i << " Now_Y " << Y1 << endl << endl;

            }
            if (PX == -100 && PY == -100)
            {
                PX = X0;
                PY = Y0;
            }

        }
        pole[PY][PX] = 2;
        pole[Y1][X1] = 2;

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 30; j++) {
                cerr << pole[i][j] << " ";
            }
            cerr << endl;
        }


        // cout << "UP" << endl; // A single line with UP, DOWN, LEFT or RIGHT
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (PX <= 2)
        {
            if (PY <= 2)    // if |_ 1
            {
                cerr << "if |_ 1" << endl;
                cout << "RIGHT" << endl;
                PX += 1;
                cout << "UP" << endl;
                PY += 1;

                continue;
            }

            if (PY >= 3 && PY <= 17)   // if | 1
            {
                cerr << "if | 1" << endl;
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

            if (PY >= 18)   // if |‾ 1
            {
                cerr << "if | 1" << endl;
                cout << "RIGHT" << endl;
                PX += 1;
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

        }

        if (PX >= 28)
        {
            if (PY <= 2)    // if ‾| 2
            {
                cerr << "if ‾| 2" << endl;
                cout << "LEFT" << endl;
                PX -= 1;
                cout << "DOWN" << endl;
                PY -= 1;
                continue;
            }

            if (PY >= 3 && PY <= 17)   // if | 2
            {
                cerr << "if | 2" << endl;
                cout << "UP" << endl;
                PY += 1;
                continue;
            }

            if (PY >= 18)   // if _|  2
            {
                cerr << "if _|  2" << endl;
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
            if (PY >= 18)   // if _  3
            {
                cerr << "if _  3" << endl;
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
            if (PY <= 2)    // if ‾ 3
            {
                cerr << "if ‾ 3" << endl;
                if (PX <= 4) {
                    cout << "LEFT" << endl;
                    PX -= 1;
                }
                if (PX >= 26) {
                    cout << "RIGHT" << endl;
                    PX += 1;
                }
            }

            cerr << "default" << endl;     // pofig
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