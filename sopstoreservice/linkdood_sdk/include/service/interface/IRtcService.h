#pragma once

#include "../model/LoginInfo.h"
#include "../extModel/packet.h"
#include "../model/Account.h"
#include "IService.h"
#include "../model/Packet.h"

#include <functional>
#include <memory>
#include <string>

#define VER_IRTC INTERFACE_VERSION(1,0)
static const VRVIID IID_IRtcSrvice = { 0x92d87e83, 0x46ac, 0x4b66, 0x8a, 0xf5, 0x28, 0xaf, 0xe7, 0x45, 0xac, 0xf };

namespace service{

	class IRtcService :public IService{
	public:
		virtual ~IRtcService(){}

		/*****************************************注册通知回调*******************************************/
		/**
		*注册音视频事件回调
		*/
		virtual	 void regChannelEventCb(std::function <void(model::channelEvent&)> cb) = 0;

		/**
		*声网用 推送房间成员
		*/
		virtual	 void regRoomMemCb(std::function< void(std::shared_ptr<Msg>) > cb) = 0;

		/*****************************************请求接口*******************************************/

		/**
		* 邀请成员加入音视频会议
		*/
		virtual void createChannel(channelRequest&, std::function<void(ErrorInfo)> cb) = 0;
		/**
		*接受或拒绝音视频会议邀请
		*/
		virtual void acceptOrReject(rejectOrAccept&, std::function<void(ErrorInfo)> cb) = 0;
		/*
		* 关闭音视频会议
		*/
		virtual void leaveChannel(std::function<void(ErrorInfo)> cb) = 0;
		/*
		*请求加入音视频会议
		*/
		virtual void joinChannel(joinChl&, std::function<void(ErrorInfo)> cb) = 0;
		/*
		*设置会议信息
		*/
		virtual void setConferenceInfo(setConfer&, std::function<void(ErrorInfo)> cb) = 0;
		/*
		* 获取会议信息
		*/
		virtual void getConferenceInfo(std::function<void(ErrorInfo, getConfer&)> cb) = 0;
		/*
		* 音视频切换
		*/
		virtual void switchChannel(int type,std::function<void(ErrorInfo)> cb) = 0;
		/*
		* 获取打洞服务地址
		*/
		virtual void getStunServer(std::function<void(ErrorInfo, p2pServerInfo&)> cb) = 0;
		/*
		* AGORA声网相关服务接口
		* @param type ///1,认证 2.呼叫 3.接听 4.重新申请subKey,5.outChat,6,updataID
		* @param channnelID ///channelID
		* @param chatTime /// 通话时间 type = 5时 填
		* @param uuid ///声网id type = 6时 填
		* @rerurn  subkey vendorKey
		*/
		virtual void getAgoraFunc(int8 type, int64 channnelID, int64 chatTime, int64 uuid, std::function<void(ErrorInfo, int, std::string&, std::string&)> cb) = 0;

	};



}