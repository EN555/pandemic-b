#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include "City.hpp"
#include <exception>
#include <iostream>

using namespace pandemic;
using namespace std;

Player::Player(Board& board, City city): board(board),current_location(city){}

Player& Player::take_card(City city) {
    if (!board.is_city_exist(city)) {  //so he can't take this card
        throw invalid_argument("the city isn't in the map!!");
    }
    mine_cards.insert(city);    //can take more than one the same card
    return *this;
}

Player& Player::drive(City city){
    if(city ==current_location){
        throw invalid_argument("can't drive to yourself!!");
    }
    if (!board.is_city_exist(city)) {  //check the map
        throw invalid_argument("the city isn't in the map!!");
    }
    if(!board.is_connected(current_location, city)){
        throw invalid_argument("you can't drive to this city!!");
    }

    current_location = city;
    return *this;
}

Player& Player::fly_direct(City city){
    if(city ==current_location){
        throw invalid_argument("can't drive to yourself!!");
    }
    if (!board.is_city_exist(city)) {  //so he can take this card
        throw invalid_argument("the city isn't in the map!!");
    }
    if(mine_cards.find(city) != mine_cards.end()){  // find the card
        mine_cards.erase(city); //remove the card
        current_location = city;
        return *this;
    }
    else{
        throw invalid_argument("you can't fly direct to this city!!");
    }
    return *this;
}
Player& Player::fly_charter(City city){
    if(city ==current_location){
        throw invalid_argument("can't drive to yourself!!");
    }
    if (!board.is_city_exist(city)) {  //so he can take this card
        throw invalid_argument("the city isn't in the map!!");
    }
    if(mine_cards.find(current_location) != mine_cards.end()){  //the card exist in his mine cards
        mine_cards.erase(current_location);
        current_location = city;
        return *this;
    }
    else{
        throw invalid_argument("you can't fly charter to this city!!");
    }
    return *this;
}
Player& Player::fly_shuttle(City city){
    if(city ==current_location){
        throw invalid_argument("can't drive to yourself!!");
    }
    if (!board.is_city_exist(city)) {  //so he can take this card
        throw invalid_argument("the city isn't in the map!!");
    }
    if(!board.is_have_have_research_station(city) || !board.is_have_have_research_station(current_location)){
            throw invalid_argument("you can't fly shuttle to this city!!");
    }
    current_location = city;
    return *this;
}
Player& Player::build(){
    if(board.is_have_have_research_station(current_location)){  //already exist research station on current location
        return *this;
    }
    if(mine_cards.find(current_location) == mine_cards.end()) {   //holds at this card
        throw invalid_argument("you havn't the card!!");
    }
    board.add_research_station(current_location);   //add research station
    mine_cards.erase(current_location);     //erase the card
    return *this;
}

Player& Player::discover_cure(Color color) {
    const int number_of_need_cards = 5;
    int number_color = 0;

    if(!board.is_have_have_research_station(current_location)){ //check if have research station
        throw invalid_argument("you havn't research station in this place!!");
    }

    if(board.is_have_cure_desease(color)){  //already care at this desease
        return *this;
    }
    std::set<City> remove_the_cards;
    for(City curr:mine_cards){
        if (board.city_to_color(curr) == color) {   //from the same color as the desease
            number_color++;
            remove_the_cards.insert(curr);
        }
    }
    if(number_color < number_of_need_cards){
        throw invalid_argument("you havn't enough cards!!");
    }
    for(City curr: remove_the_cards){
      mine_cards.erase(curr);
    }
    board.add_cure_for_color(color);
    return *this;
}

Player& Player::treat(City city) {
    if (!board.is_city_exist(city)) {  //the city exist in the map
        throw invalid_argument("the city isn't in the map!!");
    }
    if(city != current_location){
        throw("you can't care at this city!!");
    }
    if(board[city] == 0){
        throw invalid_argument("The city is already clean!!");
    }
    Color color = board.city_to_color(city);
    if(board.is_have_cure_desease(color)) {  //check if found cure to this color

        board[city] = 0;
    }
    else{
        board[city] -=1;
    }
        return *this;
}

void Player::remove_cards(){
    mine_cards.clear();
}
