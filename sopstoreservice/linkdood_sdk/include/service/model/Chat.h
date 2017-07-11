#pragma once

#include "User.h"

///聊天类型
enum ChatType
{
	BUDDY_CHAT = 1,        ///<好友聊天
	GROUP_CHAT = 2,        ///<群组聊天
	APP_CHAT = 3,		   ///<机器人
	SYSTEM_MSG = 4,        ///<系统消息
	STRANGER_CHAT = 5,     ///<陌生人聊天
	ENT_USER_CHAT = 6,     ///<企业成员聊天
	PHONE_CHAT             ///<我的设备
};

namespace model
{
///聊天信息	
class Chat : public User 
{
public:
	Chat() :msgType(0), chatType(0), operType(0), subType(0), unreadCount(0), lastMsgId(0), msgTime(0), msgRemindMode(0), lastAtMsgID(0), realUnReadCnt(0), sendUserId(0)
	{
	}
	void init(){}
	bool operator == (const Chat &rhs) const 
	{
		return (msgType == rhs.msgType) && (chatType == rhs.chatType) &&
			(operType == rhs.operType) && (subType == rhs.subType) && (unreadCount == rhs.unreadCount) &&
			(lastMsgId == rhs.lastMsgId) && (msgTime == rhs.msgTime) && (lastMsg == rhs.lastMsg) &&
			(whereFrom == rhs.whereFrom) && (lastAtMsgID == rhs.lastAtMsgID) && (msgProp == rhs.msgProp) && (realUnReadCnt == rhs.realUnReadCnt);
	}
public:
	int msgType;		  ///<消息类型;1：HTML, 2:TEXT, 3：AUDIO, 4：POSITION, 5：IMG, 6：FILE, 7：CARD,  8：TIP
	int chatType;	      ///<聊天类型
	int operType;         ///<活动类型
	int subType;          ///<子操作类型标示,置顶等其他操作
	int unreadCount;      ///<未读消息数量
	int32  realUnReadCnt; ///< 真正的未读消息数量 = unReadCnt+弱提示消息数量+其它端同步的设备消息数量，客户端每次拉取未读用这个字段，当realUnReadCnt为0时，表示所有消息在当前设备客户端都已经看过了
	///< 消息提醒模式 与0x0F 0.免打扰 1.提醒始终有声音  2.提醒始终无声音  3.提醒  4.不提醒，仅显示条目 5.根据免打扰时间段判断是否免打扰
	//< 与 0xF0, 1、通知详情  2、通知源，隐藏内容  3、完全隐藏
	int8 msgRemindMode;
	int64 lastMsgId;      ///<最后一条消息ID
	int64 lastAtMsgID;	  ///<最后一条@消息ID
	int64 msgTime;        ///<消息时间
	std::string whereFrom;///< 消息来源 在群的时候有用 
	std::string lastMsg;  ///<最后一条消息
	std::string msgProp;  ///<消息属性
	int64  sendUserId;    ///< 发送者Id
};

} /*namespace model */