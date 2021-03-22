#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Player {
public:
    int x;
    int y;
    int moveIndex;
};

// глобальные переменные ЗЛО! НО очень удобны для таких мелких программ =)
int pole[30 /*x*/][20 /*y*/] = {}; // [width][height]

//direction(направление)  движения
int direction[4 /*стороны*/][2 /*x,y*/] = { /*налево*/ { -1, 0 }, /*направо*/ { 1, 0 }, /*вниз*/ { 0, 1 }, /*вверх*/ { 0, -1 } };

int output_mas()        //just output mas
{
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 30; x++) {
            cerr << pole[x][y] << " ";
        }
        cerr << endl;
    }
}

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

// движемся!
string fist_strat(Player& player)
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

string move_index(Player& player,int index) {
    player.moveIndex = index;
    return toString(index);
}

bool prov = true;

// 2-я страта но я не знаю как ее вставить туда
string two_strat(Player& player)        //0-left / 1-right / 2-down / 3-up
{
    int rastvp, rastleft, rastright;
    //last_move не объявлена и вообще не знаю куда ее засунать
    if (last_move == "UP")
    {
        rastvp = player.y;
        rastleft = player.x;
        rastright = 30 - player.x;
        if rastleft >= rastright)
            return move_index(player, 0);
        else
            return move_index(player, 1);
    }

    if (last_move == "DOWN")
    {
        rastvp = 20 - player.y;
        rastleft = 30 - player.x;
        rastright = player.x;
        if rastleft >= rastright)
            return move_index(player, 0);
        else
            return move_index(player, 1);
    }

    if (last_move == "RIGHT")
    {
        rastvp = 30 - player.x;
        rastleft = player.y;
        rastright = 20 - player.y;
        if rastleft >= rastright)
            return move_index(player, 0);
        else
            return move_index(player, 1);
    }

    if (last_move == "LEFT")
    {
        rastvp = player.x;
        rastleft = 20 - player.y;
        rastright = player.y;
        if rastleft >= rastright)
            return move_index(player, 0);
        else
            return move_index(player, 1);
    }
    cerr << endl << "приплыли" << endl;
}


string lets_move(Player& player)     //1 strata
{
    if (prov == true)
    {
        if (player.y < 10 && isFree(player.x, player.y, 2))
            return move_index(player,2);
        if (player.y > 10 && isFree(player.x, player.y, 3))
            return move_index(player, 3);
        if (player.x < 15 && isFree(player.x, player.y, 1))
            return move_index(player, 1);
        if (player.x > 15 && isFree(player.x, player.y, 0))
            return move_index(player, 0);
        prov = false;
    }

    return fist_strat(player);
}
// cout << "UP" << endl; // A single line with UP, DOWN, LEFT or RIGHT

int main()
{
    // game loop
    int X0, Y0; // starting X,Y coordinate of lightcycle (or -1)
    int X1, Y1; // starting X,Y coordinate of lightcycle (can be the same as X0 if you play before this player)
    int PX = -100, PY = -100;
    int move = 0;

    // раз может быть от 2 до 4 - создадим массив на всех!
    Player players[4];

    while (1) {
        move++;
        int N; // total number of players (2 to 4).
        int P; // your player number (0 to 3).
        cin >> N >> P;
        cin.ignore();
        cerr << "STEP " << move << endl << endl;
        for (int i = 0; i < N; i++) {
            cin >> X0 >> Y0 >> X1 >> Y1;
            cin.ignore();

            //просваивание в начале координат
            if (move == 1)
            {
                pole[X0][Y0] = i + 1;

                players[i].x = X0;      //omega присваивани
                players[i].y = Y0;
            }
            // инициализируем i-го игрока.
            players[i].x = X1;
            players[i].y = Y1;
            // меняем 0 на доске, на id игрока.
            pole[X1][Y1] = i + 1;

            if (P == i) {
                cerr << " -----THIS MY----- " << P << endl << endl;
                // TODO может можно тут поумней как-то
                // сначала двигаем в случайном направлении
                if (move == 1) {
                    players[P].moveIndex = rand() % 4;
                }
            }
            else {
                cerr << " ---ENEMY--- " << endl << endl;
                // TODO перед присваиванием
                // players[i].x = X1;
                // players[i].y = Y1;
                // мы можем вычислить moveIndex на любом ходе, кроме первого, т.к. знаем предыдущие координаты
                // x  == players[i].x   y == players[i].y
            }

            cerr << "Player " << i << " Now_X " << players[i].x << endl;
            cerr << "Player " << i << " Now_Y " << players[i].y << endl;
        }

        // ВЫВОД поля
        output_mas();

        cout << lets_move(players[P]) << endl;
    }
}