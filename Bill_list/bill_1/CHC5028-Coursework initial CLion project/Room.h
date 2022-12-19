//
// Created by DrMark on 10/2/2017.
//


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>

using std::string;

enum direction
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
    DIRECTION_COUNT
};

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;
    //<< @Kirito
    //add other rooms around this room
    Room* south;
    Room* west;
    Room* east;
    //@>>>
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);


    Room* getNorth() const;
    void setNorth(Room* _north);
    //<<< @Kirito
    Room* getSouth() const;
    Room* getWest() const;
    Room* getEast() const;

    void setSouth(Room* _south);
    void setWest(Room* _west);
    void setEast(Room* _east);
    //@>>>

};

#endif //TEXTADV_ROOM_H
