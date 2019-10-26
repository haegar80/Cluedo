#pragma once

#include "CluedoObject.h"

class Murder : public CluedoObject
{
public:
    Murder(std::string p_name);
    virtual ~Murder() = default;

private:
    Murder(const Murder& copy) = default;
    Murder& operator= (const Murder& copy) = default;
    Murder(Murder&& other) = default;
    Murder& operator= (Murder&& other) = default;
};