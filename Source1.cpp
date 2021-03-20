#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Player {
public:
    int x;
    int y;
    int moveIndex;
};

// раз может быть от 2 до 4 - создадим массив на всех!
Player players[4];

int N; // total number of players (2 to 4).
int P; // your player number (0 to 3).

// глобальные переменные ЗЛО! НО очень удобны для таких мелких программ =)
int pole[30 /*x*/][20 /*y*/] = {}; // [width][height]

//direction(направление)  движения
int direction[4 /*стороны*/][2 /*x,y*/] = { /*налево*/ { -1, 0 }, /*направо*/ { 1, 0 }, /*вниз*/ { 0, 1 }, /*вверх*/ { 0, -1 } };

// из индекса в строчку вывода!
string toString(int moveIndex)
{
    if (moveIndex == 0) {
        return "LEFT";
    }
    else if (moveIndex == 1) {
        return "RIGHT";
    }
    else if (moveIndex == 2) {
        return "DOWN";
    }
    else if (moveIndex == 3) {
        return "UP";
    }
    cerr << "toString не должны попасть сюда " << endl;
    return "UP";
}

//свободна ли (free) точка, куда мы двинем
bool isFree(int x, int y, int moveIndex)
{
    int newX = x + direction[moveIndex][0];
    int newY = y + direction[moveIndex][1];
    // TODO закоментить вывод.
    // где-то кроется дефект, потому оставил вывод
    cerr << x << "  " << y << "  " << moveIndex << " " << newX << "  " << newY << endl;
    // проверка на границы
    if (newX < 0 || newX > 29) {
        return false;
    }
    if (newY < 0 || newY > 19) {
        return false;
    }

    // если занято уже кем-то
    if (pole[newX][newY] != 0) {
        return false;
    }
    return true;
}

struct Point {
    int x;
    int y;
};


int calc_score(int x, int y)
{
    int score = 0;
    int pole_temp[30 /*x*/][20 /*y*/] = {}; // [width][height]

    queue<Point> queue;
    Point t; t.x = x; t.y = y;
    queue.push(t);

    while(!queue.empty() && score < 50){
        Point p = queue.front();
        queue.pop();

        score++;

        for(int i = 0; i < 4; i++){
            int newX = p.x + direction[i][0];
            int newY = p.y + direction[i][1];

            if(isFree(p.x, p.y, i) && pole_temp[newX][newY] != 1)
            {
                Point newP; newP.x = newX; newP.y = newY;
                queue.push(newP);
                pole_temp[newX][newY] = 1;
                cerr << " ADD  ============= " << queue.size() << "======" << endl;
            }
        }
    }

    cerr << " FINISHED  ============= " << queue.size() << "====== score = " << score << " ==" << endl;
    return score;
}

int calc_score(int x, int y, int moveIndex){
    return calc_score(x + direction[moveIndex][0], y + direction[moveIndex][1]);
}

// движемся!
string lets_move(Player& player)
{
    int mi = -1;
    int score = -1;

    if (isFree(player.x, player.y, player.moveIndex)) {
        mi = player.moveIndex;
        score = calc_score(player.x, player.y, mi);
        cerr << " __ " << mi << " __ " << score << endl;
    }
    // выбираем пока тупо какое-то из тех направлений, какое можем =)
    for (int i = 0; i < 4; i++) {
        if (isFree(player.x, player.y, i)) {
            int score_cand = calc_score(player.x, player.y, i);
            if(score_cand > score){
                mi = i;
                score = score_cand;
                cerr << " changed __ " << mi << " __ " << score << endl;
            }
        }
    }

    if(mi > -1){
        player.moveIndex = mi;
        return toString(mi);
    }

    cerr << "lets_move не должны попасть сюда " << endl;
    player.moveIndex = 0;
    return toString(0);
}

string first(Player& player)
{
    // двигаем в прежнем направлении, если можем
    if (isFree(player.x, player.y, player.moveIndex)) {
        return toString(player.moveIndex);
    }

    //TODO придумать что-то поумней =)
    // выбираем пока тупо какое-то из тех направлений, какое можем =)
    for (int i = 0; i < 4; i++) {
        if (isFree(player.x, player.y, i)) {
            player.moveIndex = i;
            return toString(i);
        }
    }

    cerr << "lets_move не должны попасть сюда " << endl;
    player.moveIndex = 0;
    return toString(0);
}

// cout << "UP" << endl; // A single line with UP, DOWN, LEFT or RIGHT
// Write an action using cout. DON'T FORGET THE "<< endl"
// To debug: cerr << "Debug messages..." << endl;

int main()
{
    // game loop
    int X0; // starting X coordinate of lightcycle (or -1)
    int Y0; // starting Y coordinate of lightcycle (or -1)
    int X1; // starting X coordinate of lightcycle (can be the same as X0 if you play before this player)
    int Y1; // starting Y coordinate of lightcycle (can be the same as Y0 if you play before this player)

    int PX = -100;
    int PY = -100;
    int move = 0;


    while (1) {
        move++;
        cin >> N >> P;
        cin.ignore();
        cerr << "STEP " << move << endl
             << endl;
        //cerr << "Наш Player "<< P << endl;

        for (int i = 0; i < N; i++) {
            cin >> X0 >> Y0 >> X1 >> Y1;
            cin.ignore();

            // инициализируем i-го игрока.
            players[i].x = X1;
            players[i].y = Y1;
            // меняем 0 на доске, на id игрока.
            pole[X1][Y1] = i + 1;

            // ВЫВОД игрока (Убрать в функцию)
            if (P == i) {
                cerr << " -----THIS MY----- " << P << endl
                     << endl;
                // TODO может можно тут поумней как-то
                // сначала двигаем в случайном направлении
                if (move == 1) {
                    players[P].moveIndex = rand() % 4;
                }
            }
            else {
                cerr << " ---ENEMY--- " << endl
                     << endl;
                // TODO перед присваиванием
                // players[i].x = X1;
                // players[i].y = Y1;
                // мы можем вычислить moveIndex на любом ходе, кроме первого, т.к. знаем предыдущие координаты
                // x  == players[i].x   y == players[i].y
            }

            cerr << "Player " << i << " Now_X " << players[i].x << endl;
            cerr << "Player " << i << " Now_Y " << players[i].y << endl;
        }

        // ВЫВОД поля (Убрать в функцию)
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 30; x++) {
                cerr << pole[x][y] << " ";
            }
            cerr << endl;
        }

        string m = lets_move(players[P]);
        cout << m << endl;
    }
}