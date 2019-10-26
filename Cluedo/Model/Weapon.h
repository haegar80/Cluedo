#pragma once

#include "CluedoObject.h"

class Weapon : public CluedoObject
{
public:
    Weapon(std::string p_name);
    virtual ~Weapon() = default;

private:
    Weapon(const Weapon& copy) = default;
    Weapon& operator= (const Weapon& copy) = default;
    Weapon(Weapon&& other) = default;
    Weapon& operator= (Weapon&& other) = default;
};