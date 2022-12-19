//
// Created by DrMark on 10/2/2017.
//

#include "State.h"
/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

void State::addObject(GameObject &object) {
    object_game.push_back(object);

}

std::vector<GameObject>& State::getObjectList() {
    return object_game;
}

void State::showObject() const{
    if(object_game.empty()) {
        std::cout << "You haven't picked up anything yet." << std::endl;
        return;
    }
    int i = 0;
    std::cout<<"Your item are listed below."<<std::endl;
    for(auto test : object_game)
        std::cout <<++i << ". " << test << std::endl;
}
