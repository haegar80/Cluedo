#pragma once

#include <QImage>
#include <string>

class CluedoObject
{
public:
    enum CluedoObjectType
    {
        Undefined = 0,
        Murder = 1,
        Weapon = 1,
        Room = 2,
    };

    CluedoObject(CluedoObjectType p_cluedoObjectType, std::string p_name);
    virtual ~CluedoObject() = default;

    std::string getName()
    {
        return m_name;
    }

private:
    CluedoObjectType m_cluedoObjectTye{ Undefined };
    std::string m_name{ "" };
    QImage m_image{};

    CluedoObject(const CluedoObject& copy) = default;
    CluedoObject& operator= (const CluedoObject& copy) = default;
    CluedoObject(CluedoObject&& other) = default;
    CluedoObject& operator= (CluedoObject&& other) = default;
};