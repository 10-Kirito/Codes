//
// Created by 华为 on 2022/11/5.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H
#include <string>

class GameObject{
    std::string _name;
    std::string _description;
    std::string _key;

public:
    GameObject() = default;
    GameObject(std::string key);
    GameObject(std::string name, std::string description, std::string key);
    const std::string * getName() const ;
    const std::string * getDescri() const ;

    bool operator ==(const GameObject & object) const;
    GameObject & operator=(const GameObject &object);
    friend std::ostream &operator <<(std::ostream &, const GameObject &);
};


#endif //TEXTADV_GAMEOBJECT_H
