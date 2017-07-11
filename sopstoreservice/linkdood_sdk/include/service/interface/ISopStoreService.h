#pragma once
#include "../model/SDKTypes.h"
#include "IService.h"
#include "../extModel/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

#define VER_SOP INTERFACE_VERSION(1,0)
static const VRVIID IID_ISopStoreService = { 0x92dc7e43, 0x4a6c, 0x4426, 0xad, 0x5d, 0x28, 0x1f, 0xe7, 0x65, 0xbc, 0x1 };

namespace service
{
	class ISopStoreService : public IService
	{
	public:

		virtual ~ISopStoreService(){}
		virtual void queryAppStore(int8 type, model::AppStoreQueryParam appStoreQueryParam, model::AppRelationBean appRelation, int64 value64, model::AppStatisticsBean& stic, std::function<void(ErrorInfo, model::respAppStore)> cb) = 0;
		virtual void queryEnOS(model::reqEnOS &req, std::function<void(ErrorInfo, model::respEnOS &resp)> cb) = 0;
		virtual void getUsersByParam(std::map<std::string, std::string> &userParam, std::function<void(ErrorInfo, int32 code, std::string &what, std::vector<model::UserBean> &bean)> cb) = 0;

	};
}