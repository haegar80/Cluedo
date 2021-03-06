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
        Weapon = 2,
        Room = 3,
    };

    static int maxNumber;

    CluedoObject(CluedoObjectType p_cluedoObjectType, const std::string& p_name);
    virtual ~CluedoObject() = default;

    CluedoObjectType getCluedoObjectType()
    {
        return m_cluedoObjectType;
    }

    std::string getName()
    {
        return m_name;
    }

    int getNumber() {
        return m_number;
    }

    void setNumber(int p_number) {
        m_number = p_number;
    }

private:
    CluedoObjectType m_cluedoObjectType{ Undefined };
    std::string m_name{ "" };
    int m_number{ 0 };
    QImage m_image{};

    CluedoObject(const CluedoObject& copy) = default;
    CluedoObject& operator= (const CluedoObject& copy) = default;
    CluedoObject(CluedoObject&& other) = default;
    CluedoObject& operator= (CluedoObject&& other) = default;
};