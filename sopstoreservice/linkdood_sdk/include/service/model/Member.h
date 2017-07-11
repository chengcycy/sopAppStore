#pragma once
#include "User.h"
#include <string>

namespace model
{
///群成员
class Member : public User 
{
public:
	Member() :groupId(0), team(0), memberType(0), isApp(false)
	{}
	virtual void init(){}
	
	bool operator == (const Member& rhs) const
	{
		return (groupId == rhs.groupId) && (team == rhs.team) && (isApp == rhs.isApp) &&
			(memberType == rhs.memberType) && (remark == rhs.remark);
	}
public:
	Optional<int64> groupId;		///<群id
	Optional<int>  team;			///<分组
	Optional<int8> memberType;		///<成员类型：1.普通 2.管理员 3.超级管理员
	Optional<bool> isApp;			///<是否为机器人
	Optional<std::string> remark;   ///<群备注
};

}/*namespace model */
