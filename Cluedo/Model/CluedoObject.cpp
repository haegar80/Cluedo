#include "CluedoObject.h"

int CluedoObject::maxNumber{ 0 };

CluedoObject::CluedoObject(CluedoObjectType p_cluedoObjectType, const std::string& p_name) : m_cluedoObjectType(p_cluedoObjectType), m_name(p_name)
{
}
