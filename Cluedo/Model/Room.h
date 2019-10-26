#pragma once

#include "CluedoObject.h"

class Room : public CluedoObject
{
public:
    Room(std::string p_name);
    virtual ~Room() = default;

private:
    Room(const Room& copy) = default;
    Room& operator= (const Room& copy) = default;
    Room(Room&& other) = default;
    Room& operator= (Room&& other) = default;
};