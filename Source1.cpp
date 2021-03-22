#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Dir{ LEFT, RIGHT, DOWN, UP};
//direction(направление)  движения
int direction[4 /*стороны*/][2 /*x,y*/] = { /*налево*/ { -1, 0 }, /*направо*/ { 1, 0 }, /*вниз*/ { 0, 1 }, /*вверх*/ { 0, -1 } };

extern string toString(Dir dirIndex);
extern bool isFree(int x, int y, int dirIndex);

class Player {
public:
    int x;
    int y;
    Dir dirIndex;
    
    string dir_index(Dir dir)
    {
        dirIndex = dir;
        return toString(dir);
    }

    string dir_index(int index)
    {
        return dir_index(static_cast<Dir>(index));
    }

    bool isUp()
    {
        return UP == dirIndex;
    }
    bool isDown()
    {
        return DOWN == dirIndex;
    }
    bool isLeft()
    {
        return LEFT == dirIndex;
    }
    bool isRight()
    {
        return RIGHT == dirIndex;
    }

    string up()
    {
        return dir_index(UP);
    }
    string down()
    {
        return dir_index(DOWN);
    }
    string right()
    {
        return dir_index(RIGHT);
    }
    string left()
    {
        return dir_index(LEFT);
    }

    bool canUp(){
        return isFree(x, y, UP);
    }
    bool canDown(){
        return isFree(x, y, DOWN);
    }
    bool canLeft(){
        return isFree(x, y, LEFT);
    }
    bool canRight(){
        return isFree(x, y, RIGHT);
    }

};


// глобальные переменные ЗЛО! НО очень удобны для таких мелких программ =)
int pole[30 /*x*/][20 /*y*/] = {}; // [width][height]

// раз может быть от 2 до 4 - создадим массив на всех!
Player players[4];

const std::string null = "";    //trash)

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
string toString(Dir dirIndex)
{
    if (dirIndex == LEFT) {
        return "LEFT";
    }
    else if (dirIndex == RIGHT) {
        return "RIGHT";
    }
    else if (dirIndex == DOWN) {
        return "DOWN";
    }
    else if (dirIndex == UP) {
        return "UP";
    }
    cerr << "toString не должны попасть сюда " << endl;
    return "UP";
}

//свободна ли (free) точка, куда мы двинем
bool isFree(int x, int y, int dirIndex)
{
    int newX = x + direction[dirIndex][0];
    int newY = y + direction[dirIndex][1];
    // TODO закоментить вывод.
    // где-то кроется дефект, потому оставил вывод
    cerr << x << "  " << y << "  " << dirIndex << " " << newX << "  " << newY << endl;
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
string fist_strat(Player& player)   //
{
    // двигаем в прежнем направлении, если можем
    if (isFree(player.x, player.y, player.dirIndex)) {
        return toString(player.dirIndex);
    }

    //TODO придумать что-то поумней =)
    // выбираем пока тупо какое-то из тех направлений, какое можем =)
    for (int i = 0; i < 4; i++) {
        if (isFree(player.x, player.y, i)) {
            return player.dir_index(i);
        }
    }

    cerr << "lets_move не должны попасть сюда " << endl;
    return player.left();
}

// 2-я страта но я не знаю как ее вставить туда
string two_strat(Player& player)        //0-left / 1-right / 2-down / 3-up
{
    return null;
    int rastvp, rastleft, rastright, s_left,s_right;
    if (player.isUp())
    {
        rastvp = player.y;
        rastleft = player.x;
        rastright = 30 - player.x;
        s_left = rastvp * rastleft;
        s_right = rastvp * rastright;
        if (rastleft >= rastright)
            return player.left();
        else
            return player.down();
    }

    if (player.isDown())
    {
        rastvp = 20 - player.y;
        rastleft = 30 - player.x;
        rastright = player.x;
        if (rastleft >= rastright)
            return player.left();
        else
            return player.right();
    }

    if (player.isRight())
    {
        rastvp = 30 - player.x;
        rastleft = player.y;
        rastright = 20 - player.y;
        if (rastleft >= rastright)
            return player.left();
        else
            return player.right();
    }

    if (player.isLeft())
    {
        rastvp = player.x;
        rastleft = 20 - player.y;
        rastright = player.y;
        if (rastleft >= rastright)
            return player.left();
        else
            return player.right();
    }

    cerr << endl << "приплыли" << endl;
    return null;
}


bool prov = true;
bool prov2 = true;

string lets_move(Player& player)     //1 strata
{
    if (prov)
    {
        if (player.y < 10 && player.canDown())
            return player.down();
        if (player.y > 10 && player.canUp())
            return player.up();
        if (player.x < 15 && player.canRight())
            return player.right();
        if (player.x > 15 && player.canLeft())
            return player.left();
        cerr << "НА ЦЕНТРЕ, ПОЙДЁМ ДАЛЕЕ" << endl;
        prov = false;
    }


    if (prov2) {
        Player* enemyPointer;     //enemy
        for (int i = 0; i < 4; i++) {
            if (players[i].x != player.x || players[i].y != player.y) {
                enemyPointer = &players[i];
                cerr << "враг найден : на поле закрашен как  " << i + 1 << endl;
                break;
            }
        }
        Player &enemy = *enemyPointer;
        int diffX = enemy.x - player.x;
        int diffY = enemy.y - player.y;
        // враг справа
        if (diffX > 0)
        {
            cerr << "PROVERKA1" << endl;
            if (diffY < 0)    //враг сверху
            {
                if (enemy.isLeft() || enemy.isUp())
                {
                    cerr << " enemy moves to the left or up" << "  | we up" << endl;
                    player.up();
                    return fist_strat(player);
                }
                if (enemy.isRight() || enemy.isDown()){
                    cerr << " enemy moves to the right or down" << "  | we right" << endl;
                    if(player.canRight())
                        return player.right();
                    else if(player.canUp())
                        return player.up();
                }
            }
            else    // враг снизу
            {
                if (enemy.isLeft()  || enemy.isDown())
                {
                    cerr << " enemy moves to the left or down" << "  | we down" << endl;
                    if(player.canDown())
                        return player.down();
                }
                if (enemy.isRight() || enemy.isUp())
                {
                    cerr << " enemy moves to the right or up" << "  | we right" << endl;
                    if(player.canRight())
                        return player.right();
                }
            }
        }
        else
        {
        }
        cerr << "НАКРЫТИЕ ВСЁ covering off" <<  diffX << " " << diffY << endl;
        prov2 = false;
    }

    //return fist_strat(player);
    //return two_strat(player);
    string result = two_strat(player);
    if (result == null)
    {
        cerr << "LOOLLOOL" << endl;
        return fist_strat(player);
    }
    else
    {
        cerr << "222222222LOOLLOOL" << endl;
        return result;
    }
}
// cout << "UP" << endl; // A single line with UP, DOWN, LEFT or RIGHT

int main()
{
    // game loop
    int X0, Y0; // starting X,Y coordinate of lightcycle (or -1)
    int X1, Y1; // starting X,Y coordinate of lightcycle (can be the same as X0 if you play before this player)
    int PX = -100, PY = -100;
    int move = 0;
      /* initialize random seed: */
      srand (time(NULL));

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
            else
            {
                // пошёл влево
                if (players[i].x > X1)
                {
                    players[i].left();
                }
                else if (players[i].x < X1)
                {
                    // пошёл вправо
                    players[i].right();
                }
                else if (players[i].y < Y1)
                {
                    // вниз
                    players[i].down();
                }
                else if (players[i].y > Y1)
                {
                    // вверх
                    players[i].up();
                }
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
                    players[P].dirIndex = static_cast<Dir>(rand() % 4);
                }
            }
            else {
                cerr << " ---ENEMY--- " << endl << endl;
            }

            cerr << "Player " << i << " Now_X " << players[i].x << endl;
            cerr << "Player " << i << " Now_Y " << players[i].y << endl;
        }

        // ВЫВОД поля
        output_mas();

        cout << lets_move(players[P]) << endl;
    }
}