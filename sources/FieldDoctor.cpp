
#include "FieldDoctor.hpp"
#include<exception>

using namespace pandemic;
using namespace std;


FieldDoctor::FieldDoctor(Board& board, City city):Player(board,city){
}

FieldDoctor& FieldDoctor::treat(City city){
    if(city != current_location && !board.is_connected(current_location,city)){
        throw("you can't reach there!!");
    }
    if(board[city] == 0){
        throw invalid_argument("No what to decrease!!");
    }

    Color color = board.city_to_color(city);
    if(board.is_have_cure_desease(color)){
        board[city] = 0;
    }
    else {
        board[city] -= 1;
    }
    return *this;
}