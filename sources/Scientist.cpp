


#include "Board.hpp"
#include "Scientist.hpp"

using namespace std;
using namespace pandemic;

Scientist::Scientist(Board& board, City city, int num):Player(board,city), n(num){
}

Scientist& Scientist::discover_cure(Color color){
    if(!board.is_have_have_research_station(current_location)){ //check if have research station
        throw invalid_argument("can't build in city without research station!!");
    }
    if (board.is_have_cure_desease(color)){ //check if already have cure
        return *this;
    }
    if(mine_cards.size() < n){  //not enough cards
        throw invalid_argument("not enough cards!!");
    }

    std::set<City> remove_the_cards;
    int counter=0;
    for(City curr: mine_cards){
        if(board.city_to_color(curr) == color) {
            remove_the_cards.insert(curr);
            counter++;
            if (counter == n) { break; }
        }
    }
    if(counter <n ){
        throw invalid_argument("you havn't enough cards!!!!");
    }

    for(City curr : remove_the_cards){
        mine_cards.erase(curr);
    }

    board.add_cure_for_color(color); //add cure for this color
    return *this;
}