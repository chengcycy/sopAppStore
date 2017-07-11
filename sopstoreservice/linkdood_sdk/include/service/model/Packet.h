#pragma once
#include "User.h"
#include "Msg.h"
#include "TinyGroup.h"
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace model
{ 
class Msg;
struct AppInfo
{
	AppInfo() :deviceType(1)
	{}	
	std::string appVersion;		//应用版本号，如"1.5.0"  *必须设置
	int deviceType;				//设备类型 1：PC；2：手机；3：pad；4：网页  *必须设置
	std::string deviceInfo;		//设备信息 如"pc-windows"  *必须设置
	std::string appName;		//应用信息 需与应用名保持一致 *必须设置
	std::string netType;		//网络信息 如"wifi"  可选
	std::string mac;			//mac地址  windows,mac,linux平台会自动获取，其它平台需手动设置
	std::string mark;			//应用标示 可选
};

///用户设置
struct UserSetting
{
	UserSetting() :isonline(0), issearchbybean(0), issearchbyphone(0), issearchbymail(0),
					isshareupdate(0), isnewmsgtip(0), ismultiservmsgtip(0), ismultiservfrdtip(0), 
					ismultiservpersontip(0)
	{
	}

	int8 isonline;				///<否显示在线信息 0显示 1不显示 默认0
	int8 issearchbybean;		///<豆豆号查找  0允许 1不允许 默认0
	int8 issearchbyphone;		///<手机号查找  0显示 1不显示 默认0
	int8 issearchbymail;		///<邮箱号查找 0显示 1不显示 默认0
	int8 isshareupdate;			///<分享更新   0提示更新 1不提示更新 默认0
	int8 isnewmsgtip;			///<新消息通知是否提醒0提醒 1不提醒 默认0
	int8 ismultiservmsgtip;		///<多服务新消息通知是否提醒0不始终提示 1始终提示 默认0
	int8 ismultiservfrdtip;		///<多服务设置V标好友始终提醒 0不始终提示 1始终提示 默认
	int8 ismultiservpersontip;	///<多服务设置设置@相关人始终提醒0不始终提示 1始终提示 默认0
};

///本地配置条目
struct LocalSetting
{
	LocalSetting(){}
	LocalSetting(const std::string &k, const std::string &v) :key(k), val(v)
	{}
	std::string key; ///<标识
	std::string val; ///<值
};

///个人配置项
struct PersonalData
{
	PersonalData(){}
	PersonalData(int16 t, int16 v) :type(t), val(v)
	{}
	int16 type; ///<标识
	int16 val; ///<值
};
///好友验证方式返回
struct ContactVerifyType
{
	ContactVerifyType() :userid(0), type(0)
	{}
	int64 userid;
	int8  type;   ///<验证类型1需要验证信息:2:不允许任何人添加,3:允许任何人添加
};
///在线状态
struct  OnlineState
{
	OnlineState() :userID(0), connectID(0), deviceType(0), flag(0)
	{}
	int64 userID;   ///<用户ID
	int64 connectID;
	int8 deviceType;  ///<在线设备类型  1：PC；2：手机；3：pad；4：网页
	int8 flag;        ///<在线状态 -1：离线，1:在线；2 : 隐身, 3 : 忙碌, 4 : 离开, 5 : 请勿打扰, 6 : 想聊天
};

///消息查询
struct  MsgSearchProperty 
{
	MsgSearchProperty() :msgtype(2), count(0), targetid(0), start_time(0), end_time(0)
	{}
	int msgtype; ///<消息类型 当前只支持2文本
	int count;   ///<消息数量
	/**
	* 　targetId为用户Id或群Id，与count字段共同决定搜索的方式，有以下几种组合：
	*   targetId !=0, count = 1:搜索指定的targetId的聊天记录数目。
	* 　targetId = 0,count > 1: 从最小的targetId开始向上搜索记录，共搜索到count个匹配的targetId为止。
	*   targetId !=0, count >1: 从指定的targetId开始向上搜索记录，共搜索到count个匹配的targetId为止。
	*   count = 0为匹配全部消息，最多匹配10000条
	*/
	int64 targetid;
	int64 start_time;///<开始时间
	int64 end_time;  ///<结束时间  起始和结束时间全部为0代表搜索全部时间段
};
///查询结构体
struct SimpleSearchInfo
{
	SimpleSearchInfo() :flag(0){}
	int8  flag;			///<0x01男，0x02女, 0x08为群，0x10, 0 非男非女为保密
	std::string name;	///<目标名称
	std::string avatar;	///<目标头像
	std::string avatarUrl;
};
///消息查询结果
struct  MsgSearchResult
{
	MsgSearchResult() :nextTargetId(0)
	{}
	struct info
	{
		info() :count(0), targetId(0){}
		int64 targetId;			///<搜索到对象的targetId
		int count;			    ///<消息数量
		SimpleSearchInfo simpleInfo; 
	};

	std::vector<info> infos;  ///<搜索到的消息信息集合
	int64 nextTargetId;	    ///<后续查找的targetId，0代表已搜索全部消息
	
};

struct MsgDetailSearchProperty
{
	MsgDetailSearchProperty() :msgtype(2), messageId(0), targetid(0), count(0), start_time(0), end_time(0)
	{}
	int msgtype;	///<消息类型 当前只支持2文本
	int64 targetid; ///<目标Id
	int messageId;  ///<起始msgId，0为从最早的消息就行搜索
	int count;		///<一次匹配到最大的消息数量,0为匹配全部消息,最多匹配100000条
	int64 start_time;///<开始时间
	int64 end_time;  ///<结束时间  起始和结束时间全部为0代表搜索全部时间段
};

struct  MsgDetailSearchResult
{
	MsgDetailSearchResult() :nextMsgId(0){}
	int64 nextMsgId;  ///<后续查找的消息ID，0代表已搜索全部消息
	std::map<int64, SimpleSearchInfo> senderInfos; ///<存放此次搜索结果中的所有发送者信息,key为senderUserId
	std::vector<std::shared_ptr<Msg> > msgs; ///<保存所有消息内容信息
};

struct UploadFileProperty
{
	UploadFileProperty() :isP2p(0), isJS(0), localid(0), targetid(0), type(0), isResume(false){}
	int64 targetid;			///<对方的targetId(人或群)
	int64 localid;			///<标示文件的唯一localId 通过time()生成
	int16 type;				///<附件类型
	std::string localPath;	///<上传文件的本地路径
	std::string msg;		///<用于存储自定义信息
	std::string encryptKey; ///<秘钥  ///断点上传的key必须一致
	int8  isP2p;            ///<是否点对点 0 否， 1 是.
	int8   isJS;             ///< 是否JS上传图片,0 否， 1 是
	bool  isResume;         ///<是否断点上传 
};

struct DownloadFileProperty
{
	DownloadFileProperty() :bisP2P(false), bIsResume(true), localId(0), fromUserId(0){}
	int64 msgid;				///<文件的消息ID
	int64 targetId;				///<个人文件为发送者用户ID，群文件为群ID
	int64 localId;				///<标示文件的唯一localId
	int64 fromUserId;			///<发送者ID，个人文件时和targetId相同	
	std::string fileName;		//文件名
	std::string localPath;		///<本地保存地址
	std::string url;			///<服务器地址
	std::string encryptKey;      ///<加密KEY
	bool        bisP2P;	 ///< 是否接收局域网直传文件.
	bool        bIsResume;///<是否断点续传下载
};

struct Fileinfo
{
	Fileinfo() :fileid(0), userid(0), targetid(0), size(0), time(0)
	{}
	int64 fileid;                 ///<文件ID
	int64 userid;                 ///<发送者ID
	int64 targetid;               ///<目标ID,可以是群,也可以是用户
	int64 size;                   ///<文件大小
	int64 time;                   ///<上传时间
	std::string path;             ///<本地路径
	std::string name;             ///<文件名
	std::string url;              ///<文件url
	std::string encrypt_key;      ///<加密KEY
};

struct OfflineMsg
{
	OfflineMsg() :offline_type(0), count(0)
	{}
	int offline_type;  ///<1未读消息 2设备已读消息
	int count;      ///<数量
	std::shared_ptr<model::Msg> msg;
};

///版本升级信息
struct UpgradeInfo
{
	std::string hasCode;	///< 升级包的HAXI值
	int8 gradeType;			///< 升级类型 0建议升级,1强制升级 gradeType.
	std::string version;    ///< 服务器版本号 version.
	std::string updateAddr; ///< 升级的地址
	std::string desc;		///< 升级描述信息
};


/// 企业信息(搜索中使用)

struct EntInfo
{
	EntInfo() :
	enterpriseID(0){}

	int64 enterpriseID;         ///< 企业ID enterpriseID.
	std::string fullName;       ///< 企业全称 fullName.
	std::string shortName;      ///< 企业简称 shortName.
	std::string keyWords;       ///< 企业关键字 keyWords.
	std::string phone;          ///< 企业电话 phone.
};


struct OrGroupinfo
{
	OrGroupinfo() :
	groupid(0),
	orderid(0){}

	int64    groupid;
	int32    orderid;
	std::string groupname;
	std::string orgname;
};


/**
* \struct st_orgUserinfo
* \brief  组织用户信息（搜索中使用）
*/
struct OrgUserinfo
{
	OrgUserinfo() :
	userid(0){}

	int64   userid; 	                        ///< 用户ID      userid.
	std::string name;                           ///< 用户名称 	 name.
	//std::vector<std::string>  phonenumbers;     ///< 电话号码清单 phonenumbers.
	//std::vector<std::string>  emails;           ///< 电子邮件清单 emails.
	std::string orgname;                        ///< orgname 组织名称.
	std::string userHead;                        ///< 头像.
};


/**
* \struct st_entAppinfo
* \brief 应用信息
*/
struct  EntAppinfo
{
	std::string appSign;///< 应用标识
	std::string appName;///< 应用名称
	std::string appIcon;///< 应用图标
	std::string appIconUrl; ///服务器应用图标全路径
	int64 appID;        ///< 应用ID
	std::string appHomeUrl;///< 应用主页
	int64 entID;           ///< entID
	std::string entName;   ///< 应用名称
	std::map<std::string, std::string>  configItems; ///< 客户端配置
	std::string appSecret; ///< 应用密钥
	std::string appToken;  ///< 应用TOKEN
	std::string appMenus;  ///< 应用菜单
	int8	openIDEncoded; ///< openID是否编码，0:不编码，1:编码
	std::string subAccount;///< 应用子账号
	///子类型  1 H5应用，2 移动应用
	int8 appSubType;
	///推荐 1 是 ，2 否
	int8 recommend;
	/// 默认安装 1 是 ，2 否
	int8 defaultInstall;
	///扩展字段 json 格式，mainUrl H5首页，adminUrl 后台管理地址，myUrl 个人中心地址
	std::string extend;
	///设备类型 1(iPhone_E), 2(iPad_E), 3(iPhone), 4(iPad), 5(androidPhone), 6(androidPad)
	std::string deviceTypes;
	///消息历史地址
	std::string messageHistoryUrl;
	///是否启用自定义菜单   1 启用  0停用
	std::string menuOpen;
	///是否启用自定义菜单响应事件  1启用 0停用
	std::string replyMenuOpen;
	///智能开关 2
	int8 appType;
	///公众号状态
	int8 status;
	///1:订阅号2：企业号
	int8 subOrAppType;
	///应用功能介绍
	std::string appFunctintroduce;
	///公众号介绍
	std::string appDescription;
};

struct SearchResult
{
	std::vector<model::User> users;
	std::vector<model::TinyGroup> groups;

	std::vector<EntInfo> vtent;     	            ///< 企业列表 vtent.
	std::vector<OrGroupinfo> vtOrgroup;     	    ///< 企业组织列表 vtOrgroup.
	std::map<std::string, std::vector<OrgUserinfo> > mporgUser;///< 组织用户列表 vtorgUser
	std::vector<EntAppinfo> vtEntApp;       	    ///< 企业应用列表 vtEntApp

};

struct QueryMarketApplication{

	QueryMarketApplication() :pageNum(0), pageSize(0), deviceType(0), userID(0){}

	int32 pageNum;                 ///<页码
	int32 pageSize;                ///<页长
	int32 deviceType;              ///<类型 2（IOS），3（Android）
	int64 userID;                 ///<用户ID，预留类型，暂时不用输入
	std::string appName;  ///<应用名称 模糊查询用


};
///应用市场信息
struct SmallMarketAppInfo
{
	SmallMarketAppInfo() :appID(0), entID(0), ownerId(0), status(0), appType(0), defaultInstall(0), showInMy(0){}
	int64 appID;                   ///<应用ID
	int64 entID;                   ///<企业ID
	int64 ownerId;                 ///<所有者id
	int8 status;                   ///<状态 1启用，2停用，3删除
	int8 appType;                  ///<类型：1(H5应用), 2(IOS应用), 3(Android应用), 4(内部应用), 5(快捷应用)
	int8 defaultInstall;            ///<默认安装 1 是 ，2 否
	int8 showInMy;                 ///<个人安全中心是否展示 1 是 ，2 否
	std::string appSign;            ///<应用标识
	std::string appName;            ///<应用名称
	std::string appIcon;            ///<应用图标		
	std::string appFunctintroduce;   ///<应用功能介绍
	std::string version;            ///<版本号	
	std::string mainUrl;            ///<H5首页
	std::string adminUrl;           ///<后台管理地址
	std::string myUrl;              ///<个人中心地址
	std::string packageName;         ///<包名
	std::string downloadUrl;         ///<下载地址
	std::string urlScheme;           ///<urlScheme
	std::string quickUrl;            ///<快捷应用地址
	std::string extend;              ///<扩展字段
	std::string activityName;         ///<activity
};
///应用市场分页查询
struct SmallMarketAppPage{
	SmallMarketAppPage() : pageNum(0), pageSize(0), count(0), totalPage(0)
	{
		appInfoList.clear();
	}
	int32 pageNum;                               ///<页码
	int32 pageSize;                              ///<页长
	int32 count;                                 ///<总数
	int32 totalPage;                             ///<总页数
	std::vector<SmallMarketAppInfo> appInfoList;  ///<应用列表
};

struct EnterpriseDictionary
{
	int32 id;                ///<组织ID
	int32 parentId;          ///<父组织ID
	std::string dicValue;    ///<字段的名字
	std::string dickey;      ///<字段的键值
	std::string extend;      ///<拓展字段，内部json结构
};

///通讯录
class  PhoneBookContact
{
public:
	PhoneBookContact() :source(0)
	{}

public:
	std::string contactNum;   ///<联系人号码
	std::string name;         ///<联系人姓名
	int8 source;              ///<数据来源 1：手机通讯录； 2：qq好友；
};

///本地通讯录
class  localPhoneBook
{
public:
	localPhoneBook() :userId(0), flag(0)
	{}

public:
	std::string phone;   ///<联系人号码
	int64 userId;         ///<联系人ID
	int8 flag;            ///<标示
	std::string phoneName; ///<手机通讯录里的名称
	std::string userName; ///< 用户名称
	std::string userHead; ///< 用户头像
};

///上传通讯录后的推荐者
class RecommendContact
{
public:
	RecommendContact() :isBuddy(0){}
	PhoneBookContact pbContact;	//上传的联系人
	User contact;				//联系人信息
	User recommend;				//推荐者信息
	int8 isBuddy;               ///< 是否是好友标识，1表示是好友关系，2表示不是好友关系, 3表示等待验证
};

struct transferLocalData{
	transferLocalData() :version("0.0.1"), year(0), mon(0), day(0){};
	std::string filePath;///<要导入或导出文件的存放路径 

	std::string version;///<当前0.0.1
	/**导出时选择从那天开始 */
	int year;
	int mon;
	int day;
	int8 type;///<0:导出;1:导入;2:南京数据迁移
};

///p2p传文件请求
struct P2pSendFileReq
{
	P2pSendFileReq() :fileType(0), fileSize(0), fileSign(0), sendUserID(0){}
	int8        fileType; ///1:文件, 2:目录
	std::string fileName; ///文件名称
	int64       fileSize; ///文件大小
	/**
	* 发送文件的标识,响应的时候需要回传回去
	*/
	int64       fileSign; ///发送标识
	int64       sendUserID;///发送者ID
};

///p2p对象
struct p2pUser
{
	p2pUser() :userid(0), flag(0){}
	int64 userid; ///<用户ID
	int8  flag; ///<PC 0x01，移动 0x02
};

struct downloadFileInfo {
	downloadFileInfo() {
		fileType = 1;
		size = 0;
		finished = 0;
	}

	int8   fileType; /* 1:文件, 2:文件夹 */
	int64  size;    /* 当前文件大小, http上传时是总分片数 */
	int64  finished; /* 完成量, http上传时是已上传的分片数 */
	std::string   remotePath; /* 远端路径 */
	std::string   localPath;  /* 本地路径 */
};
//子账号信息
struct SubServerInfo 
{
	SubServerInfo() :userId(0), type(0){}
	std::string  addr;		///< 服务器地址
	int64        userId;	///< 用户ＩＤ
	std::string  name;		///< 登录账号名称
	std::string  avatar;	///< 头像
	std::string  account;	///< 账号
	std::string remark;		///< 备注
	int8         type;		///< 账号类型
};
 struct upMsgCt {
	upMsgCt() :type(0){}
	int8 type;
	std::string PackName;///<包名
	std::string UserName;///<用户名
	std::string MsgNum;///<消息数
	std::string devtype;///<设备类型
};

 ///敏感词
 struct BadWord
 {
	 BadWord() : badWordType(0){}
	 int8 badWordType;     ///< 0不过滤 1使用*号 2禁止发送
	 std::vector<std::string> badWordList;   ///< 敏感词列表
 };
 struct reqEntAppInfo{
	 reqEntAppInfo() :pageNum(0), pageSize(0), status(0), userID(0), entID(0){}
	 int32 pageNum;          ///< 页码
	 int32 pageSize;         ///< 每页大小
	 int8 status;            ///< 状态
	 int64 userID;           ///< 登录用户id
	 Optional<int64> entID;   ///< 企业ID，本身获取不到entID,入参为0即可
 };

 struct oauthReq{
	 std::string appID;            ///< 应用ID
	 std::string userID;           ///< 用户ID
	 std::string accountType;      ///< 账户类型
	 Optional< std::string> account; ///< 账户
	 Optional< std::string> password;///< 密码
 };


} /*namespace service*/
