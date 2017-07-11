#pragma once

#include "../model/SDKTypes.h"
#include "../model/User.h"
#include <memory>
#include <functional>
#include <string>
#include <vector>
#include "IService.h"

#define VER_FACETOFACE INTERFACE_VERSION(1,0)
static const VRVIID IID_IFaceToFaceService = { 0x5cad3868, 0x7bcc, 0x4ff2, 0x97, 0x7b, 0xdd, 0xbc, 0x27, 0x44, 0xd8, 0xdf };

namespace service
{

class IFaceToFaceService : public IService
{
public:

	virtual ~IFaceToFaceService() {}

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief  设置监听进入房间用户的信息
	* @param[in] cb  _1 房间ID; _2 加入房间的用户信息;
	*/
	virtual void regEnterBuddyRoomCb(std::function<void(const std::string&, User&)> cb) = 0;

	/**
	* \brief 设置监听进入房间用户的信息
	* @param[in] cb _1 房间ID;_2 加入房间的用户信息;
	*/
	virtual void regEnterGroupRoomCb(std::function<void(const std::string&, User&)> cb) = 0;

	/**
	* \brief 设置监听退出房间用户的信息
	* @param[in]  cb _1 房间ID;_2 退出的用户ID;_3 是否删除房间，1为删除，否则不删除
	*/
	virtual void regEixtBuddyRoomCb(std::function<void(const std::string&, int64, int8)> cb) = 0;

	/**
	* \brief 设置监听退出房间用户的信息
	* @param[in] cb _1 房间ID;_2 退出的用户ID;_3 是否删除房间，1为删除，否则不删除;
	*/
	virtual void regEixtGroupRoomCb(std::function<void(const std::string&, int64, int8)> cb) = 0;

	/**
	* \brief 完成近距离加好友的推送
	* @param[in] cb  _1 房间ID;_2 房间创建者Id;_3 是否被加好友  1是  2否
	*/
	virtual void regBuddyRoomCmpCb(std::function<void(const std::string&, int64, int8)> cb) = 0;

	/**
	*  \brief 完成近距离加好友或加群的推送
	* @param[in] cb _1 房间ID;_2 群Id;_3 是否被邀请进群 1是 2否
	*/
	virtual void regGroupRoomCmpCb(std::function<void(const std::string&, int64, int8)> cb) = 0;


	/*****************************************请求接口*******************************************/


	/**
	* \brief 创建近距离加好友房间
	* @param[in] userId 创建者ID
	* @param[in] logitude 经度
	* @param[in] latitude 维度
	* @param[in] cb 传入接收结果回调  _1错误信息  _2服务器返回的房间密码
	*/
	virtual void createBuddyRoom(int64 userId, double longitude, double latitude, std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 创建近距离加群房间
	* @param[in] userId 创建者ID
	* @param[in] logitude 经度
	* @param[in] latitude 维度
	* @param[in] cb 传入接收结果回调  _1错误信息  _2服务器返回的房间密码
	*/
	virtual void createGroupRoom(int64 userId, double longitude, double latitude, std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 进入近距离加好友房间
	* @param[in] userId 用户ID
	* @param[in] logitude 经度
	* @param[in] latitude 纬度
	* @param[in] passwd  房间密码
	* @param[in] cb 传入接收结果回调  _1错误信息 _2成员信息
	*/
	virtual void enterBuddyRoom(int64 userId, double longitude, double latitude, const std::string& passwd, std::function<void(ErrorInfo, std::vector<User>&)> cb) = 0;

	/**
	* \brief 进入近距离加群房间
	* @param[in] userId 用户ID
	* @param[in] logitude 经度
	* @param[in] latitude 纬度
	* @param[in] passwd  房间密码
	* @param[in] cb 传入接收结果回调  _1错误信息  _2成员信息
	*/
	virtual void enterGroupRoom(int64 userId, double longitude, double latitude, const std::string& passwd, std::function<void(ErrorInfo, std::vector<User>&)> cb) = 0;

	/**
	* \brief 退出近距离加好友房间
	* @param[in] userId 用户ID
	* @param[in] roomId 房间ID
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void exitBuddyRoom(int64 userId, const std::string &roomId, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 退出近距离加群房间
	* @param[in] userId 用户ID
	* @param[in] roomId 房间ID
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void eixtGroupRoom(int64 userId, const std::string &roomId, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 批量向好友房间的人发送好友请求(房间创建者操作)
	* @param[in] userId 用户ID
	* @param[in] roomId 房间ID
	* @param[in] verifyInfo 验证信息
	* @param[in] userList 发送的好友请求的用户ID集合，为房间中用户的子集
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addBuddysFromRoom(int64 userId, const std::string &roomId, const std::string &verifyInfo, std::vector<int64> &userList,
									std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 创建一个群，批量要求群房间的人进入 (房间创建者操作)
	* @param[in] userId 用户ID
	* @param[in] roomId 房间ID
	* @param[in] groupLevel 群等级 普通群为2
	* @param[in] groupName 群名  必须传
	* @param[in] userList 发送的好友请求的用户ID集合，为房间中用户的子集
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void createGroupFromRoom(int64 userId, const std::string &roomId, int8 groupLevel, const std::string &groupName, std::vector<int64> &userList,
									std::function<void(ErrorInfo)> cb) = 0;
	
};

} /*namespace service*/