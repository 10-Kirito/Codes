
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <algorithm>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r1 = new Room(&r1name, &r1desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r5 = new Room(&r5name, &r5desc);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    r1->addObject(object_1);
    r1->addObject(object_1);
    r2->addObject(object_1);
    r2->addObject(object_3);
    r3->addObject(object_4);
    r4->addObject(object_5);
    r4->addObject(object_1);
    r5->addObject(object_3);
    r5->addObject(object_2);


    r1->setNorth(r2);
    r2->setSouth(r1);
    r1->setEast(r3);
    r3->setWest(r1);
    r1->setSouth(r4);
    r4->setNorth(r1);
    r1->setWest(r5);
    r5->setEast(r1);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north, south, east and west */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a south exit */
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's an east exit */
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
            }
        }
        // if player types INVENTORY or inventory, it will display the objects of players
        if ((commandBuffer.compare(0,endOfVerb,"INVENTORY") == 0) || (commandBuffer.compare(0,endOfVerb,"inventory") == 0)) {
            commandOk = true;
            currentState->showObject();
            std :: cout << std :: endl;
        }

        // if player types get or GET, output information based on the name of the object entered by the player
        if ((commandBuffer.compare(0,endOfVerb,"get") == 0) || (commandBuffer.compare(0,endOfVerb,"GET") == 0)) {
            commandOk = true;
            int number = commandBuffer.find(' ');
            string second = commandBuffer.substr(number + 1);

            GameObject temp(second);
            bool flag = false;
            for (auto temp0 : currentState->getCurrentRoom()->getObjectList()) {
                if(temp0 == temp) {
                    temp = temp0;
                    flag = true;
                    break;
                }
            }
            if(!flag)
                // if the object is not in the room, output the following information
                std::cout << "Please input the right name of object!"<<std::endl;
            else {
                // determine if the items are already owned
                if(std::find(currentState->getObjectList().begin(),
                             currentState->getObjectList().end(),
                             temp) != currentState->getObjectList().end())
                    std::cout << "You already own the item."<<std::endl;
                else {
                    // if player don't have object, add the object into list
                    currentState->addObject(temp);
                    // delete the object from the list of the room
                    auto s = std::find(currentState->getCurrentRoom()->getObjectList().begin(),
                                       currentState->getCurrentRoom()->getObjectList().end(),
                                       temp);
                    currentState->getCurrentRoom()->getObjectList().erase(s);

                    std::cout << "Items have been picked up!" << std::endl;
                }
            }
        }

        // if player types drop or DROP, output information based on the name of the object entered by the player
        if ((commandBuffer.compare(0,endOfVerb,"drop") == 0) || (commandBuffer.compare(0,endOfVerb,"DROP") == 0)) {
            commandOk = true;
            int number = commandBuffer.find(' ');
            string second = commandBuffer.substr(number + 1);

            GameObject temp(second);
            bool flag = false;
            for (auto temp0 : currentState->getObjectList()) {
                if(temp0 == temp) {
                    temp = temp0;
                    flag = true;
                    break;
                }
            }
            if(!flag)
                // if the player doesn't own the object, output the following information
                std::cout << "You don't have the item!"<<std::endl;
            else {
                // if the player has the object, throw the object into room
                auto s = std::find(currentState->getObjectList().begin(),
                                   currentState->getObjectList().end(),
                                   temp);
                currentState->getObjectList().erase(s);
                currentState->getCurrentRoom()->addObject(temp);
                std::cout << "The object has since been discarded!"<<std::endl;
            }
        }

        // if player types findobject or FINDOBJECT , display all objects of rooms
        if ((commandBuffer.compare(0,endOfVerb,"FINDOBJECT") == 0) || (commandBuffer.compare(0,endOfVerb,"findobject") == 0)) {
            commandOk = true;
            currentState->getCurrentRoom()->showObject();
            std :: cout << std :: endl;
        }


        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0) || (commandBuffer.compare(0,endOfVerb,"QUIT") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}