#pragma once
#include "SDKTypes.h"
#include<string>

namespace model
{
///系统消息类型
enum SysOperType
{
	eSysAgree,		///<同意
	eSysRefuse,	///<拒绝
	eSysIgnore,	///<忽略
	eSysRefuseForever,	///<拒绝并不允许再次请求
};
///系统消息
struct SysMsg
{
	SysMsg() :msgId(0), userId(0), groupId(0), time(0), msgType(0), isResponse(0), isRead(0), operType(0), subType(0){}
	int64 msgId;       ///<消息ID
	int64 userId;		///<用户ID
	int64 groupId;     ///<群ID 群相关消息有值
	int64 time;        ///<时间
	int   msgType;     ///<消息类型
	int   isResponse;  ///<是否回应
	int   isRead;      ///<是否已读
	int   operType;    ///<活动类型
	int   subType;     ///<子操作类型标示,  msgType=1时 1:添加好友,2:关注   msgType=3	时 1:邀请, 2:申请加入
	std::string userName;  ///<用户名称
	std::string groupName; ///<群名称 群相关消息有值
	std::string avatar;///<消息来源头像
	std::string info;  ///<消息内容
};

/**
* \brief #msgType=1	 * 1:　添加好友，２：关注
* #
*/
}