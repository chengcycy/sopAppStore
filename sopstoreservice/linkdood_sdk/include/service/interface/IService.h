#pragma once

#include "IMUnkown.h"

namespace model
{
}
using namespace model;

namespace service 
{

//此接口为所有service的父类。
class IService
{
public:
	virtual unsigned int version() const = 0;
};


//通过版本号获取Service对象并向下转型的方法
#define SERVICE_GET(type, client, IID, VERSION) std::dynamic_pointer_cast<type>(client->queryInterface(IID, VERSION))

typedef int ErrorInfo;
} /*namespace service*/