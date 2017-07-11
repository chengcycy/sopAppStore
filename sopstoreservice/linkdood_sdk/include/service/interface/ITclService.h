#pragma once

#include "../model/LoginInfo.h"
#include "../extModel/packet.h"
#include "../model/Account.h"
#include "IService.h"

#include <functional>
#include <memory>
#include <string>

#define VER_ITCL INTERFACE_VERSION(1,0)
static const VRVIID IID_ITclService = { 0x92d87e83, 0x46ac, 0x4b66, 0x8a, 0xf5, 0x28, 0xaf, 0xe7, 0x45, 0xac, 0x14 };

namespace service{

	class ITclService :public IService{
	public:
		virtual ~ITclService(){}

		/*****************************************注册通知回调*******************************************/
		/**
		*注册远程连接事件回调
		*/
		virtual	 void regTclEventCb(std::function <void(model::tclEvent&)> cb) = 0;

		/*****************************************请求接口*******************************************/

		/**
		* 请求或邀请远程连接
		*/
		virtual void tclCallOrRequest(tclRequest&, std::function<void(ErrorInfo)> cb) = 0;
		/**
		*接受或拒绝音视频会议邀请
		*/
		virtual void tclAcceptOrReject(tclRejectOrAccept&, std::function<void(ErrorInfo)> cb) = 0;
		/*
		* 挂断或取消远程连接
		*/
		virtual void tclHungUpOrCancel(tclHungUp&, std::function<void(ErrorInfo)> cb) = 0;
		/*
		* 切换远程连接状态
		*/
		virtual void switchCtrl(tclSwitch&, std::function<void(ErrorInfo)> cb) = 0;

	};



}