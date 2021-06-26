#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    int x, y;
};


int player;
const int SIZE = 8;
std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;
int get_score(Point p);

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}

void write_valid_spot(std::ofstream& fout) {
    int n_valid_spots = next_valid_spots.size();
    srand(time(NULL));
    int best = -100;
    Point p, good;
    for(int i=0; i<n_valid_spots; i++){
        p = next_valid_spots[i];
        int score = get_score(p);
        if (score > best){
            good = p;
            score = best;
        }
    }
    cout<<"my step("<<good.x<<", "<<good.y<<endl;
    fout << good.x << " " << good.y << std::endl;
    fout.flush();
}

int get_score(Point p){
    std::array<std::array<int, SIZE>, SIZE> score;
    score = {
         90, -60,  20,  10,  10,  20, -60,  90,
        -60, -80,   3,   2,   2,   3, -80, -60,
         20,   3,   5,   4,   4,   5,   3,  20,
         10,   2,   4,   1,   1,   4,   2,  10,
         10,   2,   4,   1,   1,   4,   2,  10,
         20,   3,   5,   4,   4,   5,   3,  10,
        -60, -80,   3,   3,   3,   3, -80, -60,
         90, -60,  10,  10,  10,  10, -60,  90
    };
    if(board[0][0]==player) score[0][1] = score[1][0] = 10, score[1][1] = 5;
    if(board[0][7]==player) score[0][6] = score[1][7] = 10, score[1][6] = 5;
    if(board[7][0]==player) score[6][0] = score[7][1] = 10, score[6][1] = 5;
    if(board[7][7]==player) score[7][6] = score[6][7] = 10, score[6][6] = 5;
    return score[p.x][p.y];
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
