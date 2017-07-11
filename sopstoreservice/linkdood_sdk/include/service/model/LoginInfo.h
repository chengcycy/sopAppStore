#pragma once

#include "SDKTypes.h"
#include <string>
#include <vector>
namespace model
{

#define KEEPPASSWD 2
#define AUTOLOGIN 4
///登陆信息
class LoginInfo
{
public:
	LoginInfo() :status(0), isRemberPass(0), isAutoLogin(0), userId(0), last_login_time(0), userType(0)
	{}
	int32 status;
	int32 isRemberPass;					///<是否记住密码
	int32 isAutoLogin;					///<自动登录 
	int64 userId;						///<用户id
	int8 userType;						///<用户类型
	int64 last_login_time;				///<上次登陆时间
    std::string server;					///<服务器
    std::string name;					///<用户名
	std::string account;				///<账号
	std::string pwd;
    std::string user_icon;				///<头像
    std::string nation;					///<国家码
	std::string phone;					///<绑定的手机
	std::string email;					///<绑定的邮箱
};
///代理
struct NetProxy
{
	NetProxy() :type(0), port(0)
	{}

	int8     type;         ///<0-不使用，１-http1.1  2-http1.0  3-socket4  4-socket5
	uint16   port;         ///<端口
	std::string addr;      ///<地址
	std::string user;      ///<用户名
	std::string pw;        ///<密码
};

struct PreLogincfg {
	PreLogincfg() :userid(0){}
	std::string  area;     ///< 输入 服务器
	std::string  account; ///< 输入 账号
	int64 userid;         ///< 输出 用户ID 
	std::string  json;    ///< 输出 输出预登录结果
};
///日志级别
enum LogLevel
{
	sdklog_debug,
	sdklog_trace,
	sdklog_notice,
	sdklog_warn,
	sdklog_err,
	sdklog_all,
	sdklog_none
};

}// namespace service
