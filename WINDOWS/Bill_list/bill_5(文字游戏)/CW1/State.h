//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H

#include <vector>
#include <iostream>
#include "Room.h"
#include "GameObject.h"

class State {
    Room *currentRoom;
    std::vector<GameObject> object_game;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
    std::vector<GameObject>& getObjectList();

    void addObject(GameObject &object);

    void showObject() const;
};


#endif //TEXTADV_STATE_H
