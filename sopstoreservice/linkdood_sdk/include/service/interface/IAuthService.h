#pragma once

#include "../model/LoginInfo.h"
#include "../model/Packet.h"
#include "../model/Account.h"
#include "IService.h"

#include <functional>
#include <memory>
#include <string>

#define VER_IAUTH INTERFACE_VERSION(1,0)
static const VRVIID IID_IAuthSrvice = { 0x3271f2c2, 0xb855, 0x4234, 0x9f, 0x8b, 0x4d, 0x86, 0xd0, 0x6c, 0x2b, 0xb7 };

namespace service 
{

class IAuthService : public IService
{
public:
		
	virtual ~IAuthService(){};

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听网络连接状态
	* @param[in] cb 传入-1断线重连，0重连成功
	*/
	virtual void regNetChangedCb(std::function< void(int) > cb) = 0;

	/**
	* \brief 设置监听数据库升级完成的回调
	* @param[in] cb 0代表开始 1代表升级完成 2升级失败
	*/
	virtual void regDbUpdatedCb(std::function< void(int) > cb) = 0;

	/**
	* \brief 重新登录时推送
	* @param[in] cb  _1 错误id,  _2用户ID
	*/
	virtual void regReLoginCb(std::function< void(int, int64) > cb) = 0;

	/**
	* \brief 版本升级推送
	* @param[in] cb 版本升级信息结构 见packet.h
	*/
	virtual void regUpgrageCb(std::function< void(UpgradeInfo&) > cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 快速注册
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[in] name 用户昵称
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086158********”
	* @param[in] passwd 密码
	* @param[in] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void quickRegister(const std::string &server, const std::string &name, const std::string &account, const std::string &passwd, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取注册验证码
	* @param[in] server 服务器
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086158********”
	* @param[in] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void getRegCode(const std::string& server, const std::string &account, std::function<void(ErrorInfo, int/*超时*/)> cb) = 0;

	/**
	* \brief 注册用户
	* @param[in] regCode 验证码
	* @param[in] user    传入用户名，建议使用真实姓名
	* @param[in] pwd	 传入注册密码
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void signup(const std::string& regCode, const std::string &user, const std::string &pwd, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取重置密码验证码
	* @param[in] server 服务器
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086158********”
	* @param[in] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void getResetPwCode(const std::string& server, const std::string &account, std::function<void(ErrorInfo, int/*超时*/)> cb) = 0;

	/**
	* \brief 重置密码
	* @param[in] regCode 验证码
	* @param[in] user    传入用户名，为空代表不改名
	* @param[in] pwd	 传入新密码
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void resetPasswd(const std::string& regCode, const std::string &user, const std::string &pwd, std::function<void(ErrorInfo)> cb) = 0;
		
	/**
	* \brief 获取密码复杂度
	* @param[in] cb 传入接收结果回调 _1错误信息
	*  _2密码规则: 
	*	高8位代表最小长度
	*	低8位，按照最低位开始，依次代表:(1代表必须，0 表示可选)
	*	1. 是否必须有数字
	*	2. 是否必须有小写字母
	*	3. 是否必须有大写字母
	*	4. 是否必须有英文字母
	*	5. 是否必须有字符(特殊字符)
	*	6. 是否允许注册(1允许，0不允许)
	*/
	virtual void getPasswordRule(std::function<void(ErrorInfo, int)> cb) = 0;

	//////////////////////////////////////////////////////////////////////////
	//	登录相关接口

	/**
	*  \brief 登录
	* @param[in] user 传入用户名 如果是手机账户格式为“0086158********”
	* @param[in] pwd 传入密码
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[in] cb 传入接收结果回调 _1错误信息  _2用户Id _3 帐号被锁定剩余时长,_4 返回1102错误时的验证码路径
	* @return	int64 返回当前执行的操作ID，用于取消该次执行
	*/
	virtual int64 login(const std::string& user, const std::string& pwd, const std::string& server,
						std::function<void(ErrorInfo, int64,int64, const std::string&)> cb) = 0;

	//离线转在线接口
	/**
	 * @param[in] server 传入服务器地址，域名或IP均可
	 * @param[in] cb 传入接收结果回调 _1错误信息  _2用户Id _3 帐号被锁定剩余时长,_4 返回1102错误时的验证码路径
	 * @return	int64 返回当前执行的操作ID，用于取消该次执行
	 */

	virtual int64 offLineToLogin(const std::string& server,std::function<void(ErrorInfo, int64, int64, const std::string&)> cb) = 0;
	//登录

	/**
	* \brief 自动登录（不用填密码）
	* @param[in] userid 传入用户ID
	* @param[in] server 传入服务器地址，域名或IP均可
	* @param[in] cb 传入接收结果回调 _1错误信息  _2用户Id,_3 帐号被锁定剩余时长
	* @return	int64 返回当前执行的操作ID，用于取消该次执行
	*/
	virtual int64 autoLogin(int64 userid, const std::string &server, std::function<void(ErrorInfo, int64, int64, const std::string&)> cb) = 0;

	/**
	* \brief 离线登录
	* @param[in] userId 用户id如果为零，获取最近一次登录成功的用户id
	* @param[in] pwd 密码
	* @param[in] cb 传入接收结果回调 _1错误信息 
	*/
	virtual void offlineLogin(int64 userId, const std::string& pwd, std::function<void(ErrorInfo)> cb) = 0;
		
	/**
	* \brief 登出
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void logout(std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 取消登录
	* @param[in] operateid 传入对应登录操作的ID
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void abortLogin(int64 operateid, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 验证登录验证码或者获取下一张验证码
	* @param[[in] account 传入登录账号
	* @param[[in] code	 传入验证码内容 code为空则获取下一张验证码
	* @param[[in] cb 传入接收结果回调 _1错误信息  _2下一张验证图片
	*/
	virtual void verifyImgCode(const std::string& account, const std::string& code, 
							std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 获取安全中心URL
	* @param[in] server 传入企业服务器
	* @param[in] cb 传入接收结果回调 _1错误信息  _2 url
	*/
	virtual void getSecUrl(const std::string &server, std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 修改密码
	* @param[in] oldPw 传入旧密码
	* @param[in] newPw 传入新密码
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void changePassword(const std::string &oldPw, const std::string &newPw, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取CLIENTKEY
	* @param[in] cb 传入接收结果回调  _1错误信息  _2clientkey
	*/
	virtual void getClientKey(std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 获取绑定手机验证码
	* @param[in] phone 手机号
	* @param[in] language 语言
	* @param[in] cb 传入接收结果回调  _1错误信息  _2超时重发时间  _3注册ID
	*/
	virtual void getBindPhoneCode(const std::string &phone, const std::string &language, std::function<void(ErrorInfo, int32, int64)> cb) = 0;

	/**
	* \brief 通过获取的验证码绑定手机
	* @param[in] phone 手机号
	* @param[in] code 验证码
	* @param[in] registryID 获取验证码时返回的ID
	* @param[in] cb 传入接收结果回调  _1错误信息 0成功 100参数不正确 120账号不存在 381未指定接受者  382未指定接收者类型 
	*    383验证码已过期 384验证码不正确  385发送间隔时间太短 386发送失败  387：未发送过验证码  510帐号已被使用
	*/
	virtual void bindPhone(const std::string &phone, const std::string &code, int64 registryID,  std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 绑定邮箱
	* @param[in] mail  邮箱号
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void bindMail(const std::string &mail, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取登录的票据(同步接口)
	*/
	virtual std::string getLoginTicket() = 0;

	/**
	* \brief 获取数据库秘钥(同步接口)
	*/
	virtual std::string getPrivateKey() = 0;

	/**
	* \brief 获取登录信息。用户传入(同步接口)
	*/
	/**
	* \brief 获取登录信息。(同步接口)
	* @param[out] data  用户传入的内存地址，获取成功后，把信息拷贝到此内存中
	* @param[in] len 用户传入内存地址的长度
	* @param[return] 返回0代表获取失败，否则，返回获取数据的实际长度
	*/
	virtual int getLoginInfo(uint8_t *data, int len) = 0;
	/**
	*\brief 获取Oauth 授权码
	*/
	virtual void getLoginAuthCode(oauthReq&, std::function<void(ErrorInfo, const std::string&)> cb) = 0;

};

} /*namespace service*/