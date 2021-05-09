#include "GeneSplicer.hpp"
#include "Color.hpp"
#include "City.hpp"

using namespace std;
using namespace pandemic;

const int number_of_cards = 5;

GeneSplicer::GeneSplicer(Board& board, City city):Player(board,city){
}

GeneSplicer& GeneSplicer::discover_cure(Color color){

    const int number_of_need_cards = 5;
    if(!board.is_have_have_research_station(current_location)){ //check if have research station
        throw invalid_argument("can't build in city without research station!!");
    }
    if (board.is_have_cure_desease(color)){ //check if already have cure
        return *this;
    }

    if(mine_cards.size() < number_of_need_cards){  //not enough cards
        throw invalid_argument("you havn't enough cards!!");
    }
    std::set<City> remove_the_cards;
    int counter=0;
    for(City curr: mine_cards){
        remove_the_cards.insert(curr);
        counter++;
    }
    if(counter < number_of_need_cards){
        throw invalid_argument("you havn't enough cards!!");
    }
    for(City curr : remove_the_cards){
        mine_cards.erase(curr);
    }
    board.add_cure_for_color(color); //add cure for this color

    return *this;
}
