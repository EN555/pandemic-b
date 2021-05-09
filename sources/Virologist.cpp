#include "Virologist.hpp"
#include "Color.hpp"

using namespace pandemic;
using namespace std;


Virologist:: Virologist(Board& board, City city):Player(board,city){}


Virologist& Virologist::treat(City city) {

    if (board[city] == 0) {
        throw invalid_argument("The city is already clean!!");
    }

    Color color = board.city_to_color(city);

    //if you cure another city
    if (board.is_have_cure_desease(color)) {  //check if found cure to this color
        board[city] = 0;
        return *this;
    }
    if(current_location != city){
    if(mine_cards.find(city) != mine_cards.end()) {   //check if he have this card city
        mine_cards.erase(city);     //remove this card
        board[city] -= 1;
    }else{
        throw invalid_argument("you havn't the right card!!");
    }
    }
    else{
            board[city] -=1;
    }
    return *this;
}