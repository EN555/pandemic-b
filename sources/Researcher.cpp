#include "Board.hpp"
#include "Researcher.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

Researcher::Researcher(Board& board, City city):Player(board, city){
}

Researcher& Researcher::discover_cure(Color color){
    const int number_of_need_cards = 5;
    if (board.is_have_cure_desease(color)) {   //if the cure already exist
        return  *this;
    }
    if(mine_cards.size() < number_of_need_cards){  //not enough cards
        throw invalid_argument("not enough cards!!");
    }

    std::set<City> remove_the_cards;
    int counter=0;
    for(City curr: mine_cards){
        if(board.city_to_color(curr) == color) {
            remove_the_cards.insert(curr);
            counter++;
            if (counter == number_of_need_cards) { break; }
        }
    }
    if(counter <number_of_need_cards ){
        throw invalid_argument("you havn't enough cards!!!!");
    }

    for(City curr : remove_the_cards){
        mine_cards.erase(curr);
    }

    board.add_cure_for_color(color); //add cure for this color
    return *this;

}