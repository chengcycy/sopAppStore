#pragma once

#include "../model/Packet.h"
#include "../model/SysMsg.h"
#include "IService.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

#define VER_SYSMSG INTERFACE_VERSION(1,0)
static const VRVIID IID_ISysMsgService = { 0x92d87e23, 0x464c, 0x4406, 0x8d, 0xfd, 0x28, 0x1f, 0xe7, 0x45, 0xac, 0xb };

namespace service
{

class ISysMsgService : public IService
{
public:

	virtual ~ISysMsgService(){}

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 设置监听系统消息的回调
	* @param[in] _1 系统消息结构
	*/
	virtual void regSysMsgCb(std::function<void(const SysMsg&)> cb) = 0;

	/**
	* \brief 设置监听离线最后一条系统消息的回调
	* @param[in] _1 系统消息结构，_2未读系统消息总数
	*/
	virtual void regLastSysMsgCb(std::function<void(const SysMsg&, int)> cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 响应加好友的请求
	* @param[in] userId 请求者的用户ID 
	* @param[in] msgId 请求消息的msgId
	* @param[in] operType 对此请求的操作
	* @param[in] remark 好友备注
	* @param[in] refuseReason 附带的拒绝信息
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void respToAddBuddy(int64 userId, int64 msgId, SysOperType operType, const std::string &remark, 
									const std::string &refuseReason, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 响应进群的请求
	* @param[in] groupId 要进入的群ID
	* @param[in] msgId 请求消息的msgId
	* @param[in] operType 对此请求的操作，如果是回应被邀请进群消息，只有同意和拒绝选项
	* @param[in] refuseReason 附带的拒绝信息
	*/
	virtual void respToEnterGroup(int64 groupId, int64 msgId, SysOperType operType, const std::string &refuseReason, 
										std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置消息已读
	* @param[in] type 传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置群验证请求消息已读|4 设置群验证响应消息已读                      
	* @param[in] msgs 传入消息id
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void setMessagRead(int type, std::vector<int64> &msgs, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取系统消息消息
	* @param[in] type  传入响应消息类型 0 全部 1 加好友请求 2 加好友响应 3 加群请求 4 加群
	* @param[in] count 传入数量
	* @param[in] time  查找的起始时间 
	* @param[in] flag   传入偏移标志 0 以传入的time起始，向下偏移，拉取小于time的消息 如果time = 0，代表从最新收到的系统消息开始拉取
	                                1 以传入的time起始，向上偏移，拉取大于time的消息. 
	* @param[in] cb  传入接收结果回调  _1错误信息  _2系统消息集合
	*/
	virtual void getMessages(int type,int count,int64 time,int flag, std::function<void(ErrorInfo,std::vector<SysMsg>&)>cb) = 0;	

	/**
	* \brief 删除全部系统消息
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void deleteAllMessage(std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 通过类型删除系统消息
	* @param[in] type  消息类型  传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置群验证请求消息已读|4 设置群验证响应消息已读 
	* @param[in] msgIds 消息ID集合
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void deleteMessageByType(int type, std::vector<int64> msgIds, std::function<void(ErrorInfo)> cb) = 0;
};

} /*namespace service*/