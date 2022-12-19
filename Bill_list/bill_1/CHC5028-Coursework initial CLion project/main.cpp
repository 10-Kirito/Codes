
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

#define WALK_ROOM(DIRECTION)    commandOk = true; Room *Room = nullptr; switch(DIRECTION){case NORTH:Room = currentState->getCurrentRoom()->getNorth();break;case SOUTH:Room = currentState->getCurrentRoom()->getSouth();break;case WEST:Room = currentState->getCurrentRoom()->getWest();break;case EAST:Room = currentState->getCurrentRoom()->getEast();break;}if (Room == nullptr){/* there isn't */wrapOut(&badExit);/* Output the "can't go there" message */wrapEndPara();}else{/* There is */currentState->goTo(Room);}

#define TRIGGER_COMMAND(DIRECTION)  trigger(commandBuffer, DIRECTION)
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
    auto *r2 = new Room(&r2name, &r2desc);
    auto *r1 = new Room(&r1name, &r1desc);
    //<<< @Kirito
    auto *r3 = new Room(&r3name, &r3desc);
    auto *r4 = new Room(&r4name, &r4desc);
    auto *r5 = new Room(&r5name, &r5desc);
    auto *r6 = new Room(&r6name, &r6desc);
    auto *r7 = new Room(&r7name, &r7desc);
    //@>>>
    Room::addRoom(r1);
    Room::addRoom(r2);
    //<<< @Kirito
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    Room::addRoom(r6);
    Room::addRoom(r7);
    //@>>>
    r1->setNorth(r2);
    //<<< @Kirito
    r1->setEast(r3);
    r2->setSouth(r1);
    r2->setEast(r4);
    r3->setNorth(r4);
    r3->setSouth(r6);
    r3->setEast(r7);
    r3->setWest(r1);
    r4->setWest(r2);
    r4->setEast(r5);
    r4->setSouth(r3);
    r5->setWest(r4);
    r5->setSouth(r7);
    r6->setNorth(r3);
    r7->setNorth(r5);
    r7->setWest(r3);
    /**
     * The topology diagram is below:
     *Blue Room —— Yellow Room —— Green Room
     *   |             |               |
     *Room 1    —— Red Room   —— While Room
     *                 |
     *            Purple Room
     */
    //@>>>
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
    bool gameOver = false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        auto trigger = [&](const string &input, size_t direction) -> bool {
            switch (direction) {
                case NORTH:
                    return (commandBuffer.compare(0, endOfVerb, "north") == 0) ||
                           (commandBuffer.compare(0, endOfVerb, "n") == 0);
                case SOUTH:
                    return (commandBuffer.compare(0, endOfVerb, "south") == 0) ||
                           (commandBuffer.compare(0, endOfVerb, "s") == 0);
                case WEST:
                    return (commandBuffer.compare(0, endOfVerb, "west") == 0) ||
                           (commandBuffer.compare(0, endOfVerb, "w") == 0);
                case EAST:
                    return (commandBuffer.compare(0, endOfVerb, "east") == 0) ||
                           (commandBuffer.compare(0, endOfVerb, "e") == 0);
            }
        };

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)) {
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
            //<<< @Kirito
        else if (TRIGGER_COMMAND(SOUTH)) {
            WALK_ROOM(SOUTH)
        } else if (TRIGGER_COMMAND(EAST)) {
            WALK_ROOM(EAST)
        } else if (TRIGGER_COMMAND(WEST)) {
            WALK_ROOM(WEST)
        }
        //@>>>
        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
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