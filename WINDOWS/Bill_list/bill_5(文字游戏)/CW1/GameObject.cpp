//
// Created by 华为 on 2022/11/5.
//


#include <iostream>
#include "GameObject.h"

GameObject::GameObject(std::string name, std::string description, std::string key) :
    _name(name),_description(description), _key(key) {};


std::ostream & operator << (std::ostream & out,const GameObject & object) {
    out << object._name <<"("<< object._key <<")"<< " : " << object._description;
    return out;
}

const std::string *GameObject::getDescri() const {
    return &_description;
}

const std::string *GameObject::getName() const{
    return &_name;
}

GameObject::GameObject(std::string key) : _key(key) {}

bool GameObject::operator==(const GameObject &object) const {
    return this->_key == object._key;
}

GameObject &GameObject::operator=(const GameObject &object) {
    _key = object._key;
    _description = object._description;
    _name = object._name;
    return *this;
}





