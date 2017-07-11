#pragma once

#include "../model/Packet.h"
#include "../model/Group.h"
#include "../model/Contact.h"
#include "IService.h"
#include <functional>
#include <memory>
#include <string>

#define VER_SEARCH INTERFACE_VERSION(1,0)
static const VRVIID IID_ISearchService = { 0xe14e0da, 0xff4b, 0x4644, 0xbc, 0x3b, 0xd4, 0x50, 0x45, 0x6a, 0xff, 0x7b };

namespace service 
{

class ISearchService : public IService
{
public:

	virtual ~ISearchService(){}

	/**
	* \brief 从网络进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromNet(const std::string &key, std::function<void(ErrorInfo,SearchResult&)> cb) = 0;

	/**
	* \brief 从本地数据库进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromLocal(const std::string &key, std::function<void(ErrorInfo, SearchResult&)> cb) = 0;

	/**
	* \brief 通过用户ID获取详细信息
	* @param[in] userid 传入用户ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户信息
	*/
	virtual void getUserInfo(int64 userid, std::function<void(ErrorInfo, User&)> cb) = 0;

	/**
	* \brief 通过用户ID获取详细信息
	* @param[in] userid 传入用户ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户信息
	*/
	virtual void getUserInfoEx(int64 userid, std::function<void(ErrorInfo, Contact&)> cb) = 0;

	/**
	* \brief 通过群ID获取详细信息
	* @param[in] groupId 传入群ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2群信息
	*/
	virtual void getGroupInfo(int64 groupId, std::function<void(ErrorInfo, Group&)> cb) = 0;

	/**
	* \brief 全局查找消息
	* @param[in] key	   传入查找关键字
	* @param[in] msgProperty  传入查找的附加属性
	* @param[in] cb     传入接收结果回调  _1错误信息  _2消息搜索结果集合
	*/
	virtual void searchMessage(const std::string &key, MsgSearchProperty &msgProperty,
		std::function<void(ErrorInfo, MsgSearchResult&)> cb) = 0;

	/**
	* \brief 查找相应targetID的详细消息
	* @param[in] key	   传入查找关键字
	* @param[in] msgDetailProperty  传入查找的附加属性
	* @param[in] cb     传入接收结果回调  _1错误信息  _2消息搜索结果集合
	*/
	virtual void searchDetailMessage(const std::string &key, MsgDetailSearchProperty &msgDetailProperty,
		std::function<void(ErrorInfo, MsgDetailSearchResult&)> cb) = 0;

};

} /*namespace service*/