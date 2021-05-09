

#include "Dispatcher.hpp"
#include <exception>
using namespace pandemic;
using namespace std;

Dispatcher::Dispatcher(Board& board, City city):Player(board, city){
}


Dispatcher& Dispatcher::fly_direct(City city){
    if(!board.is_city_exist(city)){ //check if exist city with this name
        throw invalid_argument("the city isn't exist!!");
    }

    if(city == current_location){
        throw invalid_argument("can't fly to yourself!!");
    }
    //if he in research station
    if(board.is_have_have_research_station(current_location)){
        current_location = city;
        return *this;
    }

    //if haven't research station
    if(mine_cards.find(city) == mine_cards.end()){  //ypu don't hold in this city
        throw invalid_argument("you can't fly charter to this city!!");
    }

    mine_cards.erase(current_location);
    current_location = city;
    return  *this;
}