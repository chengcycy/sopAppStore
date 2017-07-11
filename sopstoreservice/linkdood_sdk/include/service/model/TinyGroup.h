#pragma once
#include "Optional.h"
#include "SDKTypes.h"
#include <string>
namespace model
{
///群组信息
class TinyGroup
{
public:
	TinyGroup() :level(0), createrId(0), cantExit(true), isVSign(false), isTop(false), isHidden(false), groupId(0)
	{}
	virtual ~TinyGroup(){}
	virtual void init(){}

	bool operator == (const TinyGroup& rhs) const
	{
		return (level == rhs.level) && (cantExit == rhs.cantExit) && (createrId == rhs.createrId) &&
			(groupId == rhs.groupId) && (groupName == rhs.groupName) && (avatar == rhs.avatar) &&
			(pinyin == rhs.pinyin) && (server == rhs.server) && (avatarUrl == rhs.avatarUrl);
	}
public:
	Optional<int> level;				///<群等级（1,2,3,4)1是临时群，2是普通群
	Optional<bool> cantExit;			///<是否允许退群
	Optional<bool> isVSign;				///<是否为v标群
	Optional<bool> isTop;				///<是否置顶
	Optional<bool> isHidden;			///<是否是隐藏群
	Optional<int64> createrId;			///<创建者ID
	Optional<int64> groupId;			///<群ID
	Optional<std::string> groupName;	///<群名
	Optional<std::string> avatar;		///<群头像
	Optional<std::string> avatarUrl;	///<群头像url
	Optional<std::string> pinyin;		///<名称拼音
	Optional<std::string> server;		///<服务器
};

} /*namespace service*/
