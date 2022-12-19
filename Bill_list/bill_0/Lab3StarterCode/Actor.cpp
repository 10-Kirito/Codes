#include "Actor.h"

using namespace std;

Actor::Actor()
{}

Actor::Actor(std::string first,std::string last,int birth)
{
    firstName = first;
    lastName = last;
    birthYear = birth;
}

void Actor::setFirstName(std::string first)
{
    firstName = first;
}

void Actor::setLastName(std::string last)
{
    lastName = last;
}

void Actor::setBirthYear(int birth)
{
    birthYear = birth;
}

std::string Actor::getFirstName()
{
    return firstName;
}

std::string Actor::getLastName()
{
    return lastName;
}

int Actor::getBirthYear()
{
    return birthYear;
}

std::ostream & operator<<(std::ostream& out,Actor actor)
{
    out << actor.getFirstName()<<" "<<actor.getLastName() <<", "<<actor.getBirthYear();
    return out;
}

Actor& Actor::operator=(const Actor&actor)
{   
    if(&actor != this)
    {
        firstName = actor.firstName;
        lastName = actor.lastName;
        birthYear = actor.birthYear;
    }
    return *this;
}