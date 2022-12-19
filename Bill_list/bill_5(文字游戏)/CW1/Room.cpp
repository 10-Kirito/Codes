//
// Created by DrMark on 10/2/2017.
//
#include <iostream>
#include "Room.h"
#include "wordwrap.h"
/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    std::cout << "The following is a list of the items you found in the room."<< std::endl;
    for(auto temp : object_list)
    {
        //wrapOut(temp.getName());
        //wrapEndPara();
        //wrapOut(temp.getDescri());
        //wrapEndPara();
        std::cout << temp <<std::endl;
    }
    std::cout << "You can types \"drop\" or \"get\" to get or discard objects."<<std::endl;

}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

Room* Room::getSouth() const {
    return this->south;
}

Room* Room::getEast() const {
    return this->east;
}

Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}

void Room::setSouth(Room* _south) {
    this->south = _south;
}

void Room::setEast(Room* _east) {
    this->east = _east;
}

void Room::setWest(Room* _west) {
    this->west = _west;
}

//@Kirito
void Room::addObject(const GameObject &object){
    object_list.push_back(object);
}

std::vector<GameObject>& Room::getObjectList() {
    return object_list;
}

void Room::showObject() const {
    int a = 0;
    std::cout << "You find these objects in the room:" <<std::endl;
    for(auto test : object_list)
        std::cout << ++a << ". " << test << std::endl;
}
