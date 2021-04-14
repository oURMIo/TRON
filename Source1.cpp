#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
    int move;
    int id;    
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

	bool can(Dir dir){
        return isFree(x, y, dir);
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

extern string fist_strat_m(Player& player);

// раз может быть от 2 до 4 - создадим массив на всех!
Player players[4];
Player enemy;
Player our;

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
string toString(int i){
    return toString(static_cast<Dir>(i));
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
bool isFree(int x, int y, int dirIndex, bool deeper)
{
    // cerr << endl << " isF ";
    int newX = x + direction[dirIndex][0];
    int newY = y + direction[dirIndex][1];
    // cerr << " (" << newX << "," << newY << ") ";
    // TODO закоментить вывод.
    // где-то кроется дефект, потому оставил вывод
  //  cerr << x << "  " << y << "  " << dirIndex << " " << newX << "  " << newY << endl;
    // проверка на границы
    if (newX < 0 || newX > 29) {
        // cerr << " x ";
        return false;
    }
    if (newY < 0 || newY > 19) {
        // cerr << " y ";
        return false;
    }

    int mark = pole[newX][newY];
    // mark == 0 - пустой.
    // mark 1 до 4 - player.id == индекс в массиве players + 1
    if (mark  >= 1 && mark <= 4 && players[mark-1].x >-1){
        // cerr << " pole busy " << pole[newX][newY];
        return false;
    }
    if(!deeper){
        // cerr << endl;
        return true;
    }
    // cerr << "deeper " << endl;
    // если узкий коридор туда нельзя ходить.
    //enum Dir{ LEFT, RIGHT, DOWN, UP};
    if((dirIndex == 0 || dirIndex == 1) && !isFree(x, y-1, dirIndex,false) && !isFree(x, y+1,dirIndex, false)){
        return false;
    }

    if((dirIndex == 2 || dirIndex == 3) && !isFree(x-1, y,dirIndex, false) && !isFree(x+1, y, dirIndex,false)){
        return false;
    }

    return true;
}
bool isFree(int x, int y, int dirIndex){
    return isFree(x, y, dirIndex,false);
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

    while(!queue.empty() && score < 100){
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
             //   cerr << " ADD  ============= " << queue.size() << "======" << endl;
            }
        }
    }

    cerr << " cs (" << x << ", " << y <<")  " << " = " << score << " " << endl;
    return score;
}

int calc_score(int x, int y, int moveIndex){
    return calc_score(x + direction[moveIndex][0], y + direction[moveIndex][1]);
}

// движемся!
string enemy_strat(Player& player)   //
{
    int eX = enemy.x - direction[enemy.dirIndex][0];
    int eY = enemy.y - direction[enemy.dirIndex][1];

	int diffX = eX - player.x;
	int diffY = eY - player.y;

	Dir dir[3] = {};

	int i = 0;
	cerr << " s ";
	if(abs(diffX) >= abs(diffY) ){
	    cerr << " X ";
		if(diffX > 0){
		    cerr << " R ";
			dir[i] = RIGHT;
			i++;
		}else if(diffX <0){
		    cerr << " L ";
			dir[i] = LEFT;
			i++;
		}
		if(diffY > 0){
		    cerr << " D ";
			dir[i] = DOWN;
			i++;
		}else if(diffY < 0){
		    cerr << " U ";
			dir[i] =UP;
			i++;
		}else{
		    cerr << " SAME ";
		    cerr << " U ";
			dir[i] =UP;
			i++;
            cerr << " D ";
            dir[i] = DOWN;
            i++;
        }
	}else if(abs(diffY)>= abs(diffX)){
	    cerr << " Y ";
		if(diffY > 0){
		    cerr << " D ";
			dir[i] = DOWN;
			i++;
		}else if(diffY < 0){
		    cerr << " U ";
			dir[i] =UP;
			i++;
		}else {
		    cerr << " SAME ";
            dir[i] = player.dirIndex;
			i++;
        }
		if(diffX > 0){
		    cerr << " R ";
			dir[i] = RIGHT;
			i++;
		}else if(diffX <0){
		    cerr << " L ";
			dir[i] = LEFT;
			i++;
		}else{
		    cerr << " SAME ";
            dir[i] = player.dirIndex;
            i++;
        }

    }
    cerr << endl;

    int score = 0;
    int scores[4] = {};
    int mi = -1;
    int score_cand;
    for (int j = 0; j < 4; j++) {
        score_cand = calc_score(player.x, player.y, j);
        if (isFree(player.x, player.y, j)) {
           if (isFree(player.x, player.y, j, true)) {
                score_cand  = score_cand + 10;
                cerr << " es " << toString(j) << " sc " << score_cand;
            }else {
                cerr << " es1 " << toString(j) << " sc " << score_cand;
            }
            scores[j] = score_cand;
            cerr << " sc ["<< j << "]=" <<  scores[j] << endl;
            if(score_cand > score){
                mi = j;
                score = score_cand;
                cerr << " new " << toString(j) << " sc " << score << endl;
            }
        }
    }

    int score_max = score;

    Dir dir1 = static_cast<Dir>(mi);
    score = score_max;
	for(int j=0; j<i;j++){
	    cerr << "cand " << j << " " << dir[j];
	    cerr << " " << toString(dir[j]) << endl;
		if(player.can(dir[j])){
			score_cand = scores[dir[j]] + 10;
			cerr <<  toString(dir[j]) <<" sc " << score_cand;
			cerr << " sc ["<< dir[j] << "]=" <<  scores[dir[j]] << endl;
			if(score_cand > score){
			    dir1 = dir[j];
			    score = score_cand;
			    cerr <<  toString(dir[j]) <<" NEW sc " << score_cand << endl;
			}
		}else {
            cerr <<  toString(dir[j]) <<" failed" << endl;
		}
	}
	if(score > 0){
	    string s = player.dir_index(dir1);
	    cerr << "enemy_strat " << s <<  " score " << score << endl;
	    return s;
	}
	cerr << " enemy strat no idea ";
	return  null;
}
// движемся!
string fist_strat(Player& player)   //
{
    int mi = -1;
    int score = -1;

    if (isFree(player.x, player.y, player.dirIndex)) {
        mi = player.dirIndex;
        score = calc_score(player.x, player.y, mi);
        cerr << " __ " << mi << " __ " << score << endl;
    }
    // выбираем пока тупо какое-то из тех направлений, какое можем =)
    for (int i = 3; i >= 0; i--) {
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

string fist_strat_m(Player& player)   //
{
    cerr << " fsm ";
    int mi = -1;
    int score = -1;
    bool was = true;
    // выбираем пока тупо какое-то из тех направлений, какое можем =)
    for (int i = 0; i < 4; i++) {
        if (isFree(player.x, player.y, i)) {            
            int score_cand = calc_score(player.x, player.y, i);
            cerr << " " << toString(i) << " sc ";

            if(score_cand > score){
                was = false;
                mi = i;
                score = score_cand;
                cerr << " NEW " << toString(mi) << " ";
            }else if (score_cand == score){
                was = true;
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

// if(player.move <200) {
//string mo = fist_strat_m(player);
//if(player.move > 50){
//    return fist_strat(player);
//}
string mo = enemy_strat(player);
cerr << "enemy " << mo << endl;
if(mo == null){
    player.dirIndex = static_cast<Dir>(rand() % 4);
    mo =  fist_strat_m(player);
    cerr << " first strat_m mo " << mo << endl;
    if(mo == null){
        return fist_strat(player);
    }
}
return mo;
// }

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
                // 0 - пустой, i+1 - player.
                pole[X0][Y0] = i + 1;

                players[i].x = X0;      //omega присваивани
                players[i].y = Y0;
                players[i].id = i+1;
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
                    // вверх
                    players[i].up();
                }
                else if (players[i].y > Y1)
                {
                    // вниз
                    players[i].down();
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
                players[i].move = move;
                our = players[i];
            }
            else {
                cerr << " ---ENEMY--- " << endl << endl;
                enemy = players[i];
                enemy.move = move;
            }

            cerr << "Player " << i << " Now_X " << players[i].x << endl;
            cerr << "Player " << i << " Now_Y " << players[i].y << endl;
        }

        // ВЫВОД поля
        //output_mas();

        cout << lets_move(players[P]) << endl;
    }
}
