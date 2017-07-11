#pragma once

#include <memory>
#include <string>
#include "IService.h"

#ifdef   SERVICE_EXPORTS
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllexport )
#else
#define SERVICE_API 
#endif
#else
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllimport )
#else
#define SERVICE_API 
#endif
#endif

#define VER_IMCLIENT INTERFACE_VERSION(1,0)
static const VRVIID IID_IMClient = {};

namespace model
{
struct AppInfo;
}

namespace service 
{

class IAuthService;
class IUserService;
class IContactService;
class ISearchService;
class IFileService;
class IGroupService;
class IChatService;
class ISysMsgService;
class IExtService;
class IConfigService;
class IFaceToFaceService;
class IRtcService;

class SERVICE_API IMClient
{
public:
	IMClient() {};
	virtual ~IMClient() {};
	//IMClient(const IMClient&) = delete;
	//IMClient& operator = (const IMClient&) = delete;

	/**
	* \brief 初始化客户端
	* @param[in] dataPath 数据存储路径
	* @param[in] certPath 证书路径
	* @param[in] appName 应用名
	* @return clientId
	*/
	virtual int init(const std::string &dataPath, const std::string& certPath, AppInfo &info) = 0;

	/**
	* \brief 反初始化客户端
	*/
	virtual void uninit() = 0;

	/**
	* \brief 清除所有通知回调
	*/
	virtual void clearAllNotifyCb() = 0;


#ifdef _WIN32
	virtual std::shared_ptr<service::IService>  _stdcall queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __linux__
	virtual std::shared_ptr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __APPLE__
	virtual std::shared_ptr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#endif

#ifdef SDK_FOR_ANDROID

	//提供给安卓的非版本控制的service的方法
	virtual bool getReponse() = 0;		//安卓获取回调的方式，需要循环调用

	virtual std::shared_ptr<IAuthService> authService() = 0;
	virtual std::shared_ptr<IUserService> userService() = 0;
	virtual std::shared_ptr<IContactService> contactService() = 0;
	virtual std::shared_ptr<ISearchService> searchService() = 0;
	virtual std::shared_ptr<IFileService> fileService() = 0;
	virtual std::shared_ptr<IGroupService> groupService() = 0;
	virtual std::shared_ptr<IChatService> chatService() = 0;
	virtual std::shared_ptr<ISysMsgService> sysMsgService() = 0;
	virtual std::shared_ptr<IExtService> extService() = 0;
	virtual std::shared_ptr<IConfigService> configService() = 0;
	virtual std::shared_ptr<IFaceToFaceService> faceToFaceService() = 0;
	virtual std::shared_ptr<IRtcService> rtcService() = 0;
#endif

};

SERVICE_API std::shared_ptr<IMClient> getClient();


} /*namespace service */

