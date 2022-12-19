#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <iostream>
#include <cstring>
class Actor {
private:
	std::string firstName;
	std::string lastName;
	int birthYear;
public:
	Actor();
	Actor(std::string, std::string, int);
	//~Actor() = default;
	void setFirstName(std::string);
	std::string getFirstName();
	void setLastName(std::string);
	std::string getLastName();
	void setBirthYear(int);
	int getBirthYear();
	Actor& operator=(const Actor&actor);
	friend std::ostream & operator<<(std::ostream& out,Actor actor);
};

#endif /* ACTOR_H_ */