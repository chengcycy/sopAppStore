#pragma once

#include "../model/SDKTypes.h"
#include "../model/Packet.h"
#include "../model/Msg.h"
#include "IService.h"
#include "../extModel/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

#define VER_AV INTERFACE_VERSION(1,0)
static const VRVIID IID_IAVService = { 0x92d88e4f, 0x441c, 0x2226, 0x8a, 0xff, 0x31, 0x1a, 0xf7, 0x56, 0x43, 0x5 };


namespace service
{
	class IAvService : public IService{
	public:
		virtual ~IAvService(){}
		/*****************************************注册通知回调*******************************************/
		/**
		 *注册音视频事件回调
		 */
		virtual	 void regAvEventCb(std::function < void(model::AVEvent) > cb) = 0;

		/*****************************************请求接口*******************************************/

		/**
		 * 请求或挂断音视频
		 */
		virtual void sendAvRequestOrHungUp(AVRequest& req, std::function<void(ErrorInfo)> cb) = 0;
		/**
		 *接受或拒绝回话请求
		 */
		virtual void acceptOrReject(AVRejectOrAccept& req, std::function<void(ErrorInfo)> cb) = 0;
		/**
		  *打开或关闭音视频
		  */
		virtual void turnOnOrOff(int8 onOrOff, std::function<void(ErrorInfo)> cb) = 0;

			
	};


};