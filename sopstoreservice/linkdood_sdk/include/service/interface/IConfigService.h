#pragma once

#include <string>
#include <vector>
#include "../model/Packet.h"
#include "../model/LoginInfo.h"
#include "IService.h"

#define VER_CONFIG INTERFACE_VERSION(1,0)
static const VRVIID IID_IConfigService = { 0x6f57b9fc, 0x7c48, 0x42e8, 0xb8, 0xab, 0xc6, 0x9b, 0x1f, 0x80, 0x50, 0x13 };

namespace service
{

class IConfigService : public IService
{
public:

	virtual ~IConfigService(){}

	/**
	* \brief <U>获取登陆信息
	* @return 登录信息
	*/
	virtual std::vector<LoginInfo> getLoginInfos() = 0;

	/**
	* \brief <U>设置登陆信息
	* @param[in] 设置的登录信息
	* @return   设置结果
	*/
	virtual bool setLoginInfo(const LoginInfo& info) = 0;
	
	/**
	* \brief <U>设置日志级别
	* @param[in]  lvl 日志级别
	* @return   设置结果
	*/
	virtual bool setLogLevel(LogLevel lvl) = 0;

	/**
	* \brief <U>互联功能配置 
	* @param[in]  flag  0.不使用互联  1.使用互联  默认使用互联
	* @return   设置结果
	*/
	virtual bool setInterConnect(int flag) = 0;

	
	/**
	* \brief <U>设置ＮＯＴＩＦＹ状态
	* @param[in]  flag  0.打开  1.关闭
	* @return   设置结果
	*/
	virtual bool setNotifyStatus(int flag) = 0;

	/**
	* \brief <G>设置证书,初始化客户端之前设置
	* @param[in]  path  证书路径
	* @return   设置结果
	*/
	virtual bool setCertificatePath(std::string &path) = 0;

	/**
	* \brief <G>获取网络代理
	* @return   返回网络代理信息
	*/
	virtual NetProxy getNetProxy() = 0;
	/**
	* \brief <G>设置网络代理
	* @param[in] param 需设置的网络代理信息
	* @return   设置结果
	*/
	virtual bool setNetProxy(NetProxy &param) = 0;

	/**
	* \brief <G>设置是否插电。客户端设置，在ＳＤＫ里面使用
	* @param[in] isPlug 是否插电
	* @return   设置结果
	*/
	virtual bool setPlugPower(bool isPlug) = 0;

	/**
	* \brief <G>设置网络状态。客户端设置，在ＳＤＫ里面使用
	* @param[in] state  0.断网，１.在线WIFI或者有线,2.在线２Ｇ，３.在线３Ｇ，４.在线４Ｇ
	* @return   设置结果
	*/
	virtual bool setNetStatus(int state) = 0;

	/**
	* \brief <G>获取sdk版本号
	* @return   sdk版本号
	*/
	virtual std::string getSdkVersion() = 0;

	/**
	* \brief <G>设置应用信息
	* @param[in] version 版本号
	* @param[in] deviceType 设备类型
	* @param[in] deviceInfo 设备信息
	* @return   设置结果
	*/
	virtual bool setAppVersion(const std::string &version, int deviceType, const std::string &deviceInfo, const std::string &netType = "", const std::string &mac = "", const std::string &mark = "") = 0;


	/**
	* \brief <G>设置客户端文字编码
	* @param[in] code  编码 0.uft-8   1.gbk  默认utf-8
	* @return   设置结果
	*/
	virtual bool setTextCoding(int code) = 0;

	/**
	* \brief <G>设置应用名称
	* @param[in] name 应用名 安卓为包名 IOS为应用ID
	* @return   设置结果
	*/
	virtual bool setAppName(const std::string &name) = 0;

	/**
	* \brief <G>设置语言环境
	* @param[in] language 语言
	* @return   设置结果
	*/
	virtual bool setLanguage(const std::string &language) = 0;

	/**
	* \brief <G>获取根路径
	* @return   根路径
	*/
	virtual std::string rootPath() = 0;
    
    /**
     * \brief <U>设置资源根路径，包括图片，文件，音频，视频路径都受影响
     * 比如设置为/home/sharp/ , 图片路径就会成为/home/sharp/{userid}/image
     * userid为当前登录的用户ID
     */
    virtual bool setRootPath(const std::string &rootPath) = 0;

	/**
	* \brief <G>获取头像路径
	* @return   头像路径
	*/
	virtual std::string headImgPath() = 0;

	/**
	* \brief <U>获取该用户聊天中图片信息的保存路径 
	* @return   图片信息的保存路径 
	*/
	virtual std::string userImgPath() = 0;

	/**
	* \brief <U>获取该用户聊天中音频信息的保存路径
	* @return   音频信息的保存路径
	*/
	virtual std::string userAudioPath() = 0;

	/**
	* \brief <U>获取该用户聊天中视频信息的保存路径
	* @return   视频信息的保存路径
	*/
	virtual std::string userVideoPath() = 0;

	/**
	* \brief <U>获取该用户聊天中cache
	* @return   用户聊天中cache
	*/
	virtual std::string userCachePath() = 0;

	/**
	* \brief <U>获取该用户聊天中文件信息的保存路径
	* @return   文件信息的保存路径
	*/
	virtual std::string userFilePath() = 0;

	/**
	* \brief <U>获取该用户表情中文件的保存路径
	* @return   文件信息的保存路径
	*/
	virtual std::string userEmotionPath() = 0;

	/**
	* \brief <G>设置消息解析方式
	* @param[in]  isParser  true 解析生成json, false由用户自己处理json
	*/
	virtual bool setMsgParserMode(bool isParser) = 0;

	/**
	* \brief <U>获取预登录附加数据
	* @return   附加数据json串
	*/
	virtual std::string getLoginExData(const std::string &serverName) = 0;

	/**
	* \brief <U>屏幕状态 安卓,IOS专用
	*/
	virtual bool setScreenStatus(bool isLight) = 0;

	/**
	* \brief <U>获取多服务器信息
	*/
	virtual bool getSubServerInfo(std::vector<SubServerInfo> &infos) = 0;

	/**
	* \brief <U>设置多服务器信息
	*/
	virtual bool setSubServerInfo(std::vector<SubServerInfo> &infos) = 0;

	/**
	* \brief <U>重新推送数据
	*/
	virtual bool reNotifyData() = 0;

	/**
	* \brief <U>设置漫游
	*/
	virtual bool setIsRoming(int32 isRoming) = 0;
	/**
	* \brief <U>获取漫游设置
	*/
	virtual bool getIsRoming() = 0;

	/**
	* \brief <G>  获取上一次预登录数据
	*/
	virtual PreLogincfg getLastPreLoginData() = 0;


private:
		
};

} /*namespace service*/