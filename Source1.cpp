#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

enum Dir{ LEFT, RIGHT, DOWN, UP};
//direction(направление)  движения
int direction[4 /*стороны*/][2 /*x,y*/] = { /*налево*/ { -1, 0 }, /*направо*/ { 1, 0 }, /*вниз*/ { 0, 1 }, /*вверх*/ { 0, -1 } };

const std::string null = "";    //trash)

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

    string up()
    {
        return canUp() ? dir_index(UP) : null;
    }
    string down()
    {
        return canDown() ? dir_index(DOWN) : null;
    }
    string right()
    {
        return canRight() ? dir_index(RIGHT) : null;
    }
    string left()
    {
        return canLeft() ? dir_index(LEFT) : null;
    }

};


// раз может быть от 2 до 4 - создадим массив на всех!
Player players[4];

int N; // total number of players (2 to 4).
int P; // your player number (0 to 3).

// глобальные переменные ЗЛО! НО очень удобны для таких мелких программ =)
int pole[30 /*x*/][20 /*y*/] = {}; // [width][height]

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
string fist_strat(Player& player)   //
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
        return player.dir_index(mi);
    }

    cerr << "lets_move не должны попасть сюда " << endl;
    return player.dir_index(0);
}

string first(Player& player)
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
    cerr << "           НАЧАЛАСЬ ФИГНЯ          " << endl;
    int rastvp, rastleft, rastright, s_left,s_right;
    if (player.isUp())
    {
        rastvp = player.y;
        rastleft = player.x;
        rastright = 30 - player.x;
        s_left = rastvp * rastleft;     //rast
        s_right = rastvp * rastright;
        if (rastleft >= rastright)
            return player.left();
        else
            return player.right();
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
            return player.up();
        else
            return player.right();
    }

    if (player.isLeft())
    {
        rastvp = player.x;
        rastleft = 20 - player.y;
        rastright = player.y;
        if (rastleft >= rastright)
            return player.up();
        else
            return player.down();
    }

    cerr << endl << "приплыли" << endl;
    return null;
}


bool prov = true;
bool prov2 = true;
bool first_on_center = false;

string to_mid(Player& player)   // к центру движ
{
    if (player.y < 10 && player.canDown())
        return player.down();
    if (player.y > 10 && player.canUp())
        return player.up();
    if (player.x < 15 && player.canRight())
        return player.right();
    if (player.x > 15 && player.canLeft())
        return player.left();
    cerr << endl << endl << "/////       НА ЦЕНТРЕ, ПОЙДЁМ ДАЛЕЕ        /////" << endl << endl;
    prov=false;
    return null;
}

string covering(Player& player)        // накрытин
{
    cerr << endl <<"   2.0 СТРАТА НАКРЫТИЕ    " << endl;
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
            cerr << "       враг справо     " << endl;
            if (diffY < 0)    //враг сверху
            {
                cerr << "       враг сверху     " << endl;
                if (enemy.isLeft() || enemy.isUp())
                {
                    cerr << " enemy moves to the left or up" << "  | we up" << endl;
                    if (player.canUp())
                        return player.up();
                    if (first_on_center)
                    {
                        if (player.canRight())
                        {
                            return player.right();
                        }
                    }
                    //return fist_strat(player);
                }
                if (enemy.isRight() || enemy.isDown()){
                    cerr << " enemy moves to the right or down" << "  | we right" << endl;
                    if(player.canRight())
                        return player.right();
                    if (first_on_center)
                    {
                        if (player.canUp())
                        {
                            return player.up();
                        }
                    }
                }
            }
            else    // враг снизу
            {
                cerr << "       враг справо     " << endl;
                if (enemy.isLeft()  || enemy.isDown())
                {
                    cerr << " enemy moves to the left or down" << "  | we down" << endl;
                    if(player.canDown())
                        return player.down();
                    if (first_on_center)
                    {
                        if (player.canLeft())
                        {
                            return player.left();
                        }
                    }
                    //return fist_strat(player);
                }
                if (enemy.isRight() || enemy.isUp())
                {
                    cerr << " enemy moves to the right or up" << "  | we right" << endl;
                    if(player.canRight())
                        return player.right();
                    if (first_on_center)
                    {
                        if (player.canUp())
                        {
                            return player.up();
                        }
                    }
                    //return fist_strat(player);
                }
            }
        }
        else    //враг слево
        {
            cerr << "       враг слево      " << endl;
            if (diffY < 0)    //враг сверху
            {
                cerr << "       враг сверху     " << endl;
                if (enemy.isRight() || enemy.isUp())
                {
                    cerr << " enemy moves to the right or up" << "  | we up" << endl;
                    if (player.canUp())
                        return player.up();
                    if (first_on_center)
                    {
                        if (player.canLeft())
                        {
                            return player.left();
                        }
                    }
                }
                if (enemy.isLeft() || enemy.isDown())
                {
                    cerr << " enemy moves to the left or down" << "  | we right" << endl;
                    if (player.canRight())
                        return player.right();
                    if (first_on_center)
                    {
                        if (player.canDown())
                        {
                            return player.down();
                        }
                    }
                    //return fist_strat(player);
                }
            }
            else    // враг снизу
            {
                cerr << "       враг снизу     " << endl;
                if (enemy.isLeft() || enemy.isUp())
                {
                    cerr << " enemy moves to the left or up" << "  | we left" << endl;
                    if (player.canLeft())
                        return player.left();
                    if (first_on_center)
                    {
                        if (player.canUp())
                        {
                            return player.up();
                        }
                    }
                    //return fist_strat(player);
                }
                if (enemy.isRight() || enemy.isDown())
                {
                    cerr << " enemy moves to the right or dowт" << "  | we down" << endl;
                    if (player.canDown())
                        return player.down();
                    if (first_on_center)
                    {
                        if (player.canRight())
                        {
                            return player.right();
                        }
                    }
                    //return fist_strat(player);
                }
            }
        }

        cerr << "////////////////////////////////////////////////" << endl;
        cerr << "/////       НАКРЫТИЕ ВСЁ covering off      /////" << endl;
        cerr << "////////////////////////////////////////////////" << endl;
        prov2 = false;
        return null;
}


/*
    2   █   1
    █████████
    3   █   4

*/
// int cheak_chetver(int x, int y)
// {
//     if ( x >= 15 )      //справо
//     {
//         if ( y >= 10 )      //снизу
//             return 4;
//         else        //сверху
//             return 1;
//     }
//     else        //слево
//     {
//         if ( y >= 10 )      //снизу
//             return 3;
//         else        //сверху
//             return 2;
//     }
//     cerr << "/////     АХТУНГ ЧЕТВЕРТЬ   /////" << endl;
//     return 0;
// }

// string covering2(Player& player)
// {
//     Player* enemyP;     //enemy
//     Player &enemy = *enemyP;
//     if (cheak_chetver(enemy.x, enemy.y)
//     {
//         return;
//     }

// }

string lets_move(Player& player)     //     обродотчик движения
{
//    first_on_center = false;
//    if (prov)       // выглядит фигово но работает
//    {
//        if(to_mid(player)!=null)
//            return to_mid(player);
//        else
//            first_on_center = true;
//    }
//
//    if (prov2)      // накрытие)
//    {
//        if(covering(player) != null)
//            return covering(player);
//    }
//
//
//    string result = two_strat(player);
//    if (result == null)
//    {
//        cerr << "return fist strat" << endl;
//        return fist_strat(player);
//    }
//    else
//    {
//        cerr << "2 strat" << endl;
//        return result;
//    }
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

      /* initialize random seed: */
      srand (time(NULL));

    while (1) {
        move++;
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
        //output_mas();

        cout << lets_move(players[P]) << endl;
    }
}