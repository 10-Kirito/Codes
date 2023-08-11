//
// Created by DrMark on 10/4/2017.
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>
#include "GameObject.h"
/*
 Room1 Middle
 Room2 North    Blue
 Room3 East     Green
 Room4 South    Yellow
 Room5 West     Red
 */

const std::string r1name = "Room 1";            //middle
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north,south,east and west.";
const std::string r2name = "Blue Room";         //north
const std::string r2desc = "You are in blue room. You know because it's blue. That's about all though. There's a passage to the south.";
const std::string r3name = "Green Room";        //east
const std::string r3desc = "You are in green room. You know because it's green. That's about all though. There's a passage to the west.";
const std::string r4name = "Yellow Room";       //south
const std::string r4desc = "You are in yellow room. You know because it's yellow. That's about all though. There's a passage to the north.";
const std::string r5name = "Red Room";          //west
const std::string r5desc = "You are in red room. You know because it's red. That's about all though. There's a passage to the east.";

const std::string show_item = "The following is a list of the items you found in the room.";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";

const std::string object1 = "Small Health Pots";
const std::string object1_descri = "This can restore a drop of blood for you.";
const std::string object1_key = "SHP";

const std::string object2 = "Big Health Pots";
const std::string object2_descri = "This can restore five drop of blood for you.";
const std::string object2_key = "BHP";

const std::string object3 = "Shield";
const std::string object3_descri = "This will protect you from a wound.";
const std::string object3_key = "SHIELD";

const std::string object4 = "Shoes";
const std::string object4_descri = "This will increase your speed.";
const std::string object4_key = "SHOES";


const std::string object5 = "Lightsaber";
const std::string object5_descri = "This item will increases your damage by 2 points.";
const std::string object5_key = "LS";

GameObject object_1(object1,object1_descri,object1_key);
GameObject object_2(object2,object2_descri, object2_key);
GameObject object_3(object3,object3_descri, object3_key);
GameObject object_4(object4,object4_descri, object4_key);
GameObject object_5(object5,object5_descri, object5_key);



#endif //TEXTADV_STRINGS_H
