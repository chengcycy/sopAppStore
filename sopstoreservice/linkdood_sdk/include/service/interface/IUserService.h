#pragma once

#include <functional>
#include <memory>
#include <string>
#include "../model/Account.h"
#include "../model/Packet.h"
#include "../model/Emoticon.h"
#include "IService.h"

#define VER_USER INTERFACE_VERSION(1,0)
static const VRVIID IID_IUserService = { 0x92d87e13, 0x463c, 0x4406, 0x8d, 0xfd, 0x28, 0x1f, 0xe7, 0x45, 0xac, 0xb };

namespace service 
{

class IUserService : public IService
{
public:
		
	virtual ~IUserService(){};

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听自己头像更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void regUserHeadImgUpdateCb(std::function < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 设置监听用户信息更新的回调，服务器推送
	* @param[in] _1 用户信息
	*/
	virtual void regOperateUserCb(std::function< void(Account&) > cb) = 0;

	/**
	* \brief 监听用户信息修改，登录更新后会主动推送
	* @param[in] _1 用户信息
	*/
	virtual void regGetMyselfCb(std::function< void(Account&) > cb) = 0;
	

	/*****************************************请求接口*******************************************/


	/**
	* \brief 获取账户信息，同步接口
	* @param[in] info 用户信息
	*/
	virtual void getAccountInfo(Account& info) = 0;


	/**
	* \brief 更新用户信息
	* @param[in] user 传入用户信息
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void updateAccountInfo(Account& user, std::function<void(ErrorInfo)> cb) = 0;

	
	/**
	* \brief 设置账号设置项
	* @param[in] flag 传入设置项属性
	* @param[in] type 传入设置项类型
	* @param[in] cb 传入接收结果回调 _1 错误信息
	*
	*  type = 1: 设置是否显示在线信息 flag: 0显示 1不显示 默认0\n
	*  type = 3: 设置豆豆号查找 flag: 0允许 1不允许 默认0\n
	*  type = 4: 设置手机号查找 flag: 0允许 1不允许 默认0\n
	*  type = 5: 设置邮箱号查找 flag: 0允许 1不允许 默认0\n
	*  type = 6: 设置分享更新   flag: 0提示更新 1不提示更新 默认0\n
	*  type = 7: 新消息通知是否提醒 flag: 0提醒 1不提醒 默认0\n
	*  type = 12: 多服务新消息通知是否提醒 flag: 0不始终提示 1始终提示 默认0\n
	*  type = 13: 多服务设置V标好友始终提醒 flag: 0不始终提示 1始终提示 默认0\n
	*  type = 14: 多服务设置设置@相关人始终提醒 flag: 0不始终提示 1始终提示 默认0
	*/
	virtual void setSetting(int8 flag, int type, std::function<void(ErrorInfo)> cb) = 0;


	/**
	* \brief 获取账号设置项
	* @param[in] type 传入获取的设置项类型
	* type为1，则返回值为value_i64第一位 如果type=0,返回所有字段，每个字段所占的位于type相对应\n
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户设置
	*/
	virtual void getSetting(int type, std::function<void(ErrorInfo, UserSetting&)> cb) = 0;


	/**
	* \brief 通过密码获取隐藏对象(好友或群)
	* @param[in] passwd 之前设置过的密码
	* @param[in] cb 传入接收结果回调  _1错误信息  _2返回对象ID合集  _3 true代表存在此密码，false代表不存在
	*/
	virtual void getHiddenTarget(const std::string &passwd, std::function<void(ErrorInfo, std::vector<int64>&, bool)> cb) = 0;

	/**
	* \brief 设置隐藏对象(好友或群)
	* @param[in] passwd 设置的密码
	* @param[in] hiddenIDs 设置的隐藏好友集合
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setHiddenTarget(const std::string &passwd, std::vector<int64>& hiddenIDs, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 删除隐藏对象(好友或群)
	* @param[in] passwd 密码
	* @param[in] hiddenIDs 要删除的ID集合
	* @param[in] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void delHiddenTarget(const std::string &passwd, std::vector<int64>& hiddenIDs, std::function<void(ErrorInfo)> cb) = 0;


	/**
	* \brief 更改隐藏密码
	* @param[in] oldPwd 旧密码
	* @param[in] newPwd 新密码
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void changeHiddenPasswd(const std::string &oldPwd, const std::string &newPwd, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取全局勿扰模式
	* @param[in] cb 传入接收结果回调  _1错误信息 _2起始时间  _3结束时间  _4是否打开
	*/
	virtual void getGlobalNoDisturbMode(std::function<void(ErrorInfo, int32, int32, bool)> cb) = 0;

	/**
	* \brief 设置全局勿扰模式
	* @param[in] startTime  起始时间
	* @param[in] endTime 结束时间
	* @param[in] isOpen 是否打开
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setGolbalNoDisturbMode(int32 startTime, int32 endTime, bool isOpen, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户ID  _3设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰
	*/
	virtual void getUserNoDisturbMode(int64 targetId, std::function<void(ErrorInfo, int64, int8)> cb) = 0;

	/**
	* \brief 设置针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[in] value 设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰, 默认1
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUserNoDisturbMode(int64 targetId, int8 value, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取针对目标消息的通知模式
	* @param[in] targetId  用户ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户ID _3设置的值:  1.通知详情 2.通知源，隐藏内容 3.完全隐藏 
	*/
	virtual void getMsgNotifyMode(int64 targetId, std::function<void(ErrorInfo, int64, int8)> cb) = 0;

	/**
	* \brief 设置针对目标消息的通知模式
	* @param[in] targetId  用户ID
	* @param[in] value 设置的值:  1.通知详情 2.通知源，隐藏内容 3.完全隐藏  默认开启模式1
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setMsgNotifyMode(int64 targetId, int8 value, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取服务器时间
	* @param[in] cb 传入接收结果回调  _1错误信息   _2服务器时间，单位毫秒
	*/
	virtual void getServerTime(std::function<void(ErrorInfo, int64)> cb) = 0;

	/**
	* \brief 增加本地配置，以键值对方式保存
	* @param[in] items  配置信息集合
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addLocalSetting(std::vector<LocalSetting> &items, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 增加本地配置，以键值对方式保存(同步接口)
	* @param[in] items  配置信息集合
	*/
	virtual bool addLocalSettingSync(std::vector<LocalSetting> &items) = 0;

	/**
	* \brief 获取本地配置
	* @param[in] keys 获取的配置信息的键集合
	* @param[in] cb 传入接收结果回调  _1错误信息  _2获取的配置信息集合
	*/
	virtual void getLocalSetting(std::vector<std::string> &keys, std::function<void(ErrorInfo, std::vector<LocalSetting>&)> cb) = 0;
	/**
	* \brief 获取本地配置(同步接口)
	* @param[in] keys 获取的配置信息的键集合
	* @param[in] result 返回的配置信息
	*/
	virtual bool getLocalSettingSync(std::vector<std::string> &keys, std::vector<LocalSetting> &result) = 0;

	/**
	* \brief 更新本地配置
	* @param[in] newItems 插入的新的配置信息集合
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void updateLocalSetting(std::vector<LocalSetting> &newItems, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 更新本地配置(同步接口)
	* @param[in] newItems 插入的新的配置信息集合
	*/
	virtual bool updateLocalSettingSync(std::vector<LocalSetting> &newItems) = 0;

	/**
	* \brief 删除本地配置
	* @param[in] keys 删除的配置信息集合
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void deleteLocalSetting(std::vector<std::string> &keys, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 删除本地配置(同步接口)
	* @param[in] keys 删除的配置信息集合
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual bool deleteLocalSettingSync(std::vector<std::string> &keys) = 0;


	/**
	* \brief 设置个人设置项\n
	*		type: 1 (生日)，２（电话），３（邮件）\n
	* 　　　　　　value:  1：所有人可见 2：仅好友可见 3：仅自己可见，默认1\n
	*		type: 4 (好友验证方式)\n
	* 　　　　　　value:   1：需要验证信息,2:不允许任何人添加,3:允许任何人添加，默认1\n
	*		type: 5 V标\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 6 @相关人提醒模式\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 7 全局通知消息内容展现模式\n
	 *         value: 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2\n
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setPersonalData(std::vector<PersonalData> items, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取个人设置项
	* @param[in] cb 传入接收结果回调  _1错误信息  _2返回的值
	*/
	virtual void getPersonalData(std::vector<int16> &types, std::function<void(ErrorInfo, std::vector<PersonalData>&)> cb) = 0;

	/**
	* \brief 通过应用ID获取应用信息
	* @param[in] appId 应用程序ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2返回的值
	*/
	virtual void getAppInfo(int64 appId, std::function<void(ErrorInfo, EntAppinfo&)> cb) = 0;
	/**
	* \brief 查询应用市场应用信息
	* @param[in] qData 传入的查询信息
	* @param[in] cb 传入接收结果回调  _1错误信息  _2返回的应用信息
	*/
	virtual void queryMarketApplication(QueryMarketApplication& qData, std::function<void(ErrorInfo, SmallMarketAppPage&)> cb) = 0;
	/**
	* \brief 删除添加应用
	* @param[in] type 传入的查询类型
	* @param[in] appID 操作的appID
	* @param[in] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void addOrDeleteApplication(int8 type, int64 appID, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取已安装的应用
	* @param[in] deviceType 安卓orIOS
	* @param[in] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void getInstalledApplication(int32 deviceType, std::function<void(ErrorInfo, std::vector<SmallMarketAppInfo>&)> cb) = 0;
	/**
	* \brief 单个查询表情包
	* @param[in] label表情包标签
	* @param[in] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void QueryEmoticonPackageByLabel(std::string label, std::function<void(ErrorInfo, std::vector<EmoticonPackage>&)> cb) = 0;
	/**
	* \brief 单个表情查询、根据表情包标识查询表情，查询所有用户自定义表情
	* @param[in] type  1, 单个查询表情 md5Code表示单个表情的md5, 6,根据表情包标识查询所有表情 md5Code表示表情包的md5, 7,查询用户所有自定义表情 这里md5Code不传值
	* @param[in] md5   md5值
	* @param[in] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void queryEmoticon(int8 type, std::string md5, std::function<void(ErrorInfo, std::vector<Emoticon>&)> cb) = 0;
	/**
	* \brief 单个查询表情包
	* @param[in] md5   md5值
	* @param[in] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void singleQueryEmoticonPackage(std::string md5, std::function<void(ErrorInfo, EmoticonPackage&)> cb) = 0;
	/**
	* \brief 分页查询表情包
	* @param[in] pageNum   页码
	* @param[in] pageSize   页长
	* @param[in] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void pageQueryEmoticon(int32 pageNum, int32 pageSize, std::function<void(ErrorInfo, PageQueryEmoticon&)> cb) = 0;
	/**
	* \brief 增删自定义表情
	* @param[in] type   类型  4 增加， 5删除.
	* @param[in] emot   表情
	* @param[in] cb 传入接收结果回调  _1错误信息 _2resultCode _3resultMsg _4successList _5failedList
	*/
	virtual void addOrDeleteCustomEmoticon(int8 type, Emoticon &emot, std::function<void(ErrorInfo, int32, const std::string&, std::vector<EmoticonResult>&, std::vector<EmoticonResult>&)> cb) = 0;
	/**
	*\brief 查选单个表情包内的单个表情
	*@param[in] packageCode 表情包md5 
	*@param[in] emotCode  表情md5
	*/
	virtual void queryEmotionInPackage(std::string packageCode, std::string emotCode, std::function<void(ErrorInfo, singleEmoticonResult&)>) = 0;
	/**
	* \brief 本地数据导入导出
	* @param[in] req   见结构体定义处说明
	* @param[in] cb 传入接收结果回调  _1错误信息 _2resultCode _3resultMsg _4successList _5failedList
	*/
	virtual void transLocalData(transferLocalData &req, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 设置用户自定义声音
	* @param[in] userId   用户ID id为0代表设置用户自己
	* @param[in] voiceName   声音名字
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUserDefineVoice(int64 userId, const std::string &voiceName, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 获取用户自定义声音
	* @param[in] userId   用户ID id为0代表获取用户自己
	* @param[in] cb 传入接收结果回调  _1错误信息 _2
	*/
	virtual void getUserDefineVoice(int64 userId, std::function<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 通过账号名获取用户ID
	* @param[in] accounts   用户accountName集合
	* @param[in] cb 传入接收结果回调  _1错误信息 _2用户ID集合，key为account value为用户ID
	*/
	virtual void getIdByAccount(std::vector<std::string> &accounts, std::function<void(ErrorInfo, std::map<std::string, int64>&)> cb) = 0;
	/**
	* \brief 设置在线状态
	* @param[in] flag  1:在线,2:隐身,3:忙碌,4:离开,5:请勿打扰
	* @param[in] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void setOnlineState(int8 flag, std::function<void(ErrorInfo)> cb) = 0;

	/**************IOS专用接口 begin***************/

	/**
	* \brief IOS设置Token
	* @param[in] appleId  需要设置的appleId
	* @param[in] token  需要设置的token
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setToken(const std::string &appleId, const std::string &token, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief ios设置是否推送
	* @param[in] isPush 是否推送
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setPushSwitch(bool isPush, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief  ios设置客户端消息未读数量
	* @param[in] count 未读数量
	* @param[in] appleId  应用id，不同的应用所对应的证书是不一样的.
	* @param[in] token  ios token
	* @param[in] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUnReadCount(int count, const std::string &appleId, const std::string &token, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief  获取用户应用安装天数
	* @param[in] cb 传入接收结果回调  _1错误信息 _2使用天数
	*/
	virtual void getInstallDays(std::function<void(ErrorInfo, int32)> cb) = 0;
	
	/**
	*\brief 根据用户id分页获取企业号
	*@param[in] cb 
	*/
	virtual void getEntAppInfo(reqEntAppInfo& req,std::function<void(ErrorInfo, int64, int64, std::vector<model::EntAppinfo>&)> cb) = 0;

	/**************IOS专用接口 end***************/

	/**************安卓专用接口 begin***************/
	virtual void wakeUp(std::function<void(ErrorInfo)> cb) = 0;
	/**************安卓专用接口 end***************/

};

} /*namespace service*/
