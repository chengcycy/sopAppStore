#pragma once

#include "../model/SDKTypes.h"
#include <string>
#include <vector>
#include "../model/Optional.h"
#include <map>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN ///防止重复包含
#include <Windows.h>
#else
//
#endif

namespace model
{

// 任务属性
struct MsgProperties {
	MsgProperties() 
	{}

	std::string timeZone;       ///< 时区
	std::string timeTask;     ///< 任务时间
	std::string isFinish;       ///< 是否完成     0：未完成 1：完成
	std::string isTask;         ///< 任务标记     0：非任务 1：任务
	std::string isRead;         ///< 是否已读     0：未读   1：已读
};

// task
struct Task 
{
	Task() :fromeUserID(0), sendTime(0), msgID(0), top(0), targetID(0)
	{
	}

	int64 fromeUserID;                  ///< 自己发送的这个字段填0
	int64 sendTime;                     ///< 发送时间
	std::string body;                   ///< 消息体
	int64 msgID;                        ///< 任务ID
	MsgProperties msgProperties;
	std::string relatedUsers;           ///< 如果是针对群全体成员，就是群ID，如果针对部分人，就是人的ID数组
	std::vector<int64> vt_relatedUsers; ///< 返回的时候用
	int8 top;                           ///< 是否置顶   0：不置顶 1：置顶
	int64 targetID; 		            ///< 接受者，可以为群或者人
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///房间
struct room 
{
	room() :roomID(0), top(0)
	{}

	int roomID;                         ///< 房间ID
	std::string roomName;               ///< 房间名
	std::string roomMember;             ///< 房间成员
	std::vector<int64> vt_roomMember;   ///< 返回的时候用
	int8 top;                           ///< 是否置顶   0：不置顶 1：置顶
	std::string portraitURL;            ///< 头像
};
/////////////////////////////////////////////////////////////////////////

/// 企业信息
struct entpriseInfo
{
	entpriseInfo() :
	enterpriseID(0),
	sector(0),
	sectorDetail(0),
	type(0),
	provinceID(0),
	cityID(0),
	areaID(0),
	status(0),
	creationDate(0),
	updatedDate(0){}

	int64 enterpriseID;         ///< 企业ID enterpriseID.
	std::string fullName;       ///< 企业全称 fullName.
	std::string shortName;      ///< 企业简称 shortName.
	std::string keyWords;       ///< 企业关键字 keyWords.
	int64 sector;               ///< 企业所属行业 sector.
	int64 sectorDetail;         ///< 企业所属行业的具体哪一类 sectorDetail.
	int8 type;                  ///< 企业类型 type.
	int64 provinceID;           ///< 企业所属省份 provinceID.
	int64 cityID;               ///< 企业所属市 cityID.
	int64 areaID;               ///< 企业所属地区 areaID.
	std::string address;        ///< 企业地址 address.
	std::string postcode;       ///< 企业邮编 postcode.
	std::string phone;          ///< 企业电话 phone.
	std::string fax;            ///< 企业传真 fax.
	std::string email;          ///< 企业邮箱 email.
	std::string homepage;       ///< 企业主业 homepage.
	std::string introduction;   ///< 企业简介 introduction.
	std::string logUrl;         ///< 企业logURL地址 logUrl.
	int8 status;                ///< 企业状态：1:审核通过；2：未审核；3：审核未通过 status.
	int64 creationDate;         ///< 注册时间 creationDate.
	int64 updatedDate;          ///< 修改时间 updatedDate.
};


/// 组织信息
struct OrganizationInfo
{
	OrganizationInfo() :
	orgID(0),
	enterpriseID(0),
	leaf(0),
	parentOrgID(0),
	orderNum(0),
	branchID(0),
	departLevel(0),
	subOrgNum(0),
	subUserNum(0),
	isHidden(0),
	provinceID(0),
	cityID(0),
	areaID(0) {}
		
	int64 orgID;                ///< 组织机构ID orgID.
	int64 enterpriseID;         ///< 企业ID enterpriseID.
	std::string orgName;        ///< 组织机构名称 orgName.
	std::string orgCode;        ///< 组织机构内码 orgCode.
	int8 leaf;                  ///< 是否叶节点 leaf.
	int64 parentOrgID;          ///< 父节点 parentOrgID.
	std::string remark;         ///< 备注 remark.
	int64 orderNum;             ///< 排序 orderNum.
	int64 branchID;             ///< 办公地ID branchID.
	std::string departID;       ///< 删除 departID.
	int8 departLevel;           ///< 组织级别 departLevel.
	int64 subOrgNum;            ///< 递归计算所有下级组织数 subOrgNum.
	int64 subUserNum;           ///< 递归计算所有下级成员数 subUserNum.
	int8 isHidden;              ///< 是否隐藏, 1对本部门公开 2对所有部门公开，3对部分部门公开 isHidden.
	int64 provinceID;           ///< 省份ID provinceID.
	std::string provinceName;   ///< 省份名称 provinceName.
	int64 cityID;               ///< 市ID cityID.
	std::string cityName;       ///< 市名称 cityName.
	int64 areaID;               ///< 县ID areaID.
	std::string areaName;       ///< 县名称 areaName.
	std::string orgNamePinyin;  ///< 拼音 orgNamePinyin.
};

/// 企业成员信息
struct EntpriseUserInfo
{
	EntpriseUserInfo() :
	userID(0),
	enterpriseID(0),
	orgID(0),
	roleID(0),
	status(0),
	orderNum(0),
	newOrgID(0){}

	int64 userID;               ///< 用户ID userID.
	int64 enterpriseID;         ///< 企业ID enterpriseID.
	int64 orgID;                ///< 组织机构ID orgID.
	int64 roleID;               ///< 角色ID roleID.
	std::string enName;         ///< 企业内用户名称 enName.
	std::string duty;           ///< 企业内用户职位 duty.
	std::string enMail;         ///< 企业内用户email enMail.
	std::string enMobile;       ///< 企业内用户手机号 enMobile.
	int8 status;                ///< 企业账号是否被停用 1：正常 2：停用 status.
	int64 orderNum;             ///< 人员排序 orderNum.
	int64 newOrgID;             ///< 用户修改组织机构使用，表示用户新组织机构，在修改时给用户增加组织机构时，使用newOgrID而不是orgID newOrgID.
	std::string orgName;        ///< 组织名 orgName.
	std::string extend;         ///< 扩展信息 extend.
	std::string accountName;    ///< 账号名称 accountName.
	std::string enNamePy;       ///< 拼音 enNamePy.
	int8  bizStatus;            ///< 业务状态 业务状态：1：初始状态，2：在高管群
  	std::string userHead;       ///< 头像
	std::string userHeadUrl;    ///<头像全路径
	std::string power ;         ///< 权限
};

/// 团队用户查询参数
struct EnterpriseUserQueryInfo
{
	EnterpriseUserQueryInfo() :
	entID(0),
	entOrgID(0),
	pageNo(0),
	pageSize(100),
	entUserID(0),
	bizStatus(0),
	status(0){}

	std::string username; 	    ///< 用户名称 username.
	int64 entID; 			    ///< 企业ID entID.
	int64 entOrgID; 		    ///< 组织架构ID entOrgID.
	int32 pageNo; 			    ///< 分页页码 pageNo.
	int32 pageSize; 		    ///< 分页每页大小 pageSize.
	int64 entUserID; 		    ///< 企业用户ID.
	int8 bizStatus;             ///< 业务状态，1：默认，2：在高管层.
	int8 status;                ///< 企业用户状态.
};

/// note
struct _BaseNoteinfo__isset
{
	_BaseNoteinfo__isset() :id(false), lastChgTime(false), sendUserId(false), targetId(false), type(false), 
			content(false), title(false), key(false), isReminder(false), rmdTime(false), isArchive(false)
	{}
	bool id;						    ///记事本唯一标识
	bool lastChgTime;					///最后修改时间,毫秒
	bool sendUserId;					///发送的人
	bool targetId;						///来源 人或者群		
	bool type;
	bool content;						///内容     最长4096个字符	
	bool title;							///标题     最长128字符
	bool key;							///关键字(标签),  检索用 最长128字符 ,可以为空
	bool isReminder;					///是否是提醒
	bool rmdTime;						///提醒时间
	bool isArchive;						///是否归档
};
///记事本
struct BaseNoteInfo
{
	BaseNoteInfo() :id(0), lastChgTime(0), sendUserId(0), targetId(0), type(0), isReminder(0), rmdTime(0), isArchive(0){}

	Optional<int64> id;						 ///<记事本唯一标识
	Optional<int64> lastChgTime;		    ///<最后修改时间,毫秒
	Optional<int64> sendUserId;				///<发送的人
	Optional<int64> targetId;				///<来源 人或者群
		/**
		*  低4位 类型 1. 文本，2，图片，3，音频，4，视频，5，URL
		*  高4位 0. 本地， 1. 网络
		*/
	Optional<int8> type;
	/**
	根据文件类型
	1. 文本、URL 直接存储内容。
	2. 非文本类型，存储附件地址，网络地址和本地地址均可。
	*/
	Optional<std::string> content;		///<内容     最长4096个字符	
	Optional<std::string> title;		///<标题     最长128字符
	Optional<std::string> key;			///<关键字(标签),  检索用 最长128字符 ,可以为空
	Optional<int8> isReminder;			///<是否是提醒
	Optional<int64> rmdTime;			///<提醒时间
	Optional<int8> isArchive;			///<是否归档
};
struct searchNoteInfo{
	searchNoteInfo() :beginID(0), offset(0), offsetFlag(0), type(0), is_all(0), is_archive(0){}
	int64 beginID;      ///< 起始消息ID, offsetFlag = 0 beginID = 0时，代表从最大的消息Id进行查找
	int32 offset;       ///< 查询的数量(赋值为0代表查询全部)
	int8  offsetFlag;   ///< 偏移标志；0.消息Id由大到小偏移 1.消息Id由小到大偏移 offsetFlag.

	int8 type;          ///< 1:只需给is_all赋值; 2:只需给is_archive赋值; 3:只需给key赋值;
	/**
	* 下面3个字段每次只能给一个字段赋值，剩余2个字段不用赋值
	*/
	int8 is_all;        ///< 1:获取全部
	int8 is_archive;    ///< 1:获取未归档 2:获取已经归档
	std::string key;    ///< 根据关键词查找
};
struct AVEvent
{
	AVEvent() :userId(0), type(0), videoType(0), avType(0){}
	int64 userId;
	int8 avType; ///<1，语音  2，视频

	int8 type;//事件类型 1,视频请求 2,挂断消息 3,请求被拒 4,忙 5,超时 6,取消 7,连接 8,断开
	std::string channelId;///<房间号 唯一
	int8 videoType;///<视频回话类型 1:单人 2:多人
	std::string fileName;///<文件名
	int64 fileSize;//<文件大小
};

struct AVRequest {
	AVRequest() :targetId(0), type(2), hungUp(false), videoType(1){}
	int64 targetId;//目标Id

#ifdef _WIN32
	HWND local;
	HWND remote;
#else
	long local;
	long remote;
#endif

	std::string channelId;///<房间号 唯一
	int8 type; ///<1，语音  2，视频
	bool hungUp;///true 挂断
	int8 videoType;///<视频回话类型 1:单人 2:多人
};

struct AVRejectOrAccept {
	AVRejectOrAccept() : targetId(0), type(1), videoType(0),  local(0), remote(0){}
	int64 targetId;//目标Id

#ifdef _WIN32
	HWND local;
	HWND remote;
#else
	long local;
	long remote;
#endif

	int8 type;//1,接受 2，拒绝
	std::string channelId;///<房间号 唯一
	int8 videoType;///<视频回话类型 1:单人 2:多人
	std::string path;               ///< P2P时代表另存为路径

};

struct channelEvent
{
	channelEvent() :userId(0), type(0), channelId(0), videoType(2){}
	int64 userId;
	int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消7,连接成功,8,连接断开,9,其他端已接受,10,P2P完成,11,收到accept 消息 现在需要调用createAnswer 12,收到responce 代表现在要调用setRemoteDescrption
	int64 channelId;          ///< 房间号 唯一
	int8 videoType;                  ///< 1，音频 2，视频，3,多人UI语音 4,多人UI视频
	std::string fileName;           ///< P2P时传输的文件名
	std::string sdp;                ///<收到accept时 讲sdp交给上层
	int8 version;            ///< 区分声网和rtc  ///< rtc = 0 声网 =1
	std::vector<int64> members;      ///<主叫方发过来的用户列表
};

struct channelRequest {
	channelRequest() : reject(false), videoType(2){}
	int64 targetId;//目标Ids
	int operType;                 ///< 0，普通呼叫 1，innercall,2,声网呼叫
	bool reject;  ///< true  代表用于拒绝申请加入会议
	int8 videoType;                 ///< 1，语音  2，视频 3,多人UI语音 4,多人UI视频
	std::string firstSdp;
};

struct joinChl{
	joinChl() :channelId(0){}
	int64 channelId; ///请求加入的房间号
	std::string  addition;///附加信息
};
struct setConfer{
	int64 m_vtMembers;///<需要操作的用户列表 （删除）
};
struct p2pServerInfo{
	std::string stunAddr;
	std::string stunPort;
	std::string turnAddr;
	std::string turnPort;
	std::string account;
	std::string password;
};
struct getConfer{
	std::string m_strTheme;///<会议议题
	p2pServerInfo info;///<打洞服务器信息
	std::vector<int64> m_vtMembers;///<成员
};
struct rejectOrAccept {

	rejectOrAccept() : targetId(0), type(0), channelId(0), videoType(2){}

	int64 targetId;                 ///< 目标Id
	int8 type;                      ///< 1,接受 2，拒绝,3,声网接受 4,声网拒绝
	int64 channelId;          ///< 房间号 唯一
	int8 videoType;                 ///< 视频类型 1:音频 2:视频
	//std::string path;               ///< P2P时代表另存为路径(不传为默认路径)
	 std::string  sdps;///<针对多点音视频，讲多个sdp useid对传下来
};

struct tclEvent {
    tclEvent() : userId(0), type(0), channelId(0), ctrlType(0) {}

    int64 userId;                   ///< 对方Id
    int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消 7,接受 8,响应 9,邀请 10,受邀,11,切换屏幕共享 12,切换控制 13,拒绝切换
    int64 channelId;                ///< 房间号 唯一（受控方UserId）
    int8 ctrlType;                  ///< 1-屏幕共享 2-远程操作
    std::vector<std::string> vecIPAddr;     // 受控方IP地址列表
};
struct tclRequest {
    tclRequest() : targetId(0), ctrlType(2), isControl(false){}

    int64 targetId;			    ///< 目标ID
    int8 ctrlType;			    ///< 远程控制类型 1-可视，2-可控
    bool isControl;			    ///< 是否控制方，true-请求、房间号为targetID，false-邀请、房间号为MyselfID
    std::vector<std::string> vecIPAddr;     ///< 受控方IP地址列表，邀请时有效
};
struct tclRejectOrAccept {
    tclRejectOrAccept() : targetId(0), type(0), channelId(0), ctrlType(2) {}

    int64 targetId;                 ///< 目标Id
    int8 type;                      ///< 1,接受 2，拒绝
    int64 channelId;                ///< 房间号 唯一
    int8 ctrlType;                  ///< 远程控制类型 1-可视，2-可控
    std::vector<std::string> vecIPAddr;     ///< 受控方IP地址列表，接受时有效
};
struct tclSwitch {
    tclSwitch() : targetId(0), ctrlType(0) {}
    int64 targetId;					///< 目标ID
    int8 ctrlType;					///< 远程控制类型 1-可视，2-可控
};
struct tclHungUp{
    tclHungUp() :targetId(0), isCancel(false){}

    int64 targetId;					///< 目标ID
    bool isCancel;                  ///< 是否取消通话 true-cancel, false-hungUp
};

///////////////////////////////////////////////sopStorePlugin/////////////////////////

/// 结果
struct Result {
	int32	    code;           ///< 是否处理成功
	std::string message;        ///< 失败原因
	int64       result;         ///< 处理的结果
};

/// 应用实体
struct AppInfoBean {
	int64       id;             ///< 应用主键
	std::string name;           ///< 应用名称
	std::string	icon;           ///< 应用图标(图片路径)
	int32	    classify;       ///< 应用分类(分类ID)
	int32       type;           ///< 软件应用类型(1:原生APK,2:H5)
	std::string homeUrl;        ///< h5首页访问地址
	std::string version;        ///< 版本号
	std::string packageName;    ///< 包名
	std::string downloadUrl;    ///< 下载地址
	std::string activityName;   ///< 安卓调取本地应用名称
	std::string orgIds;         ///< 发布范围(多个orgID以’，’拼接)
	int32       status;         ///< 状态(1:启用,2:停用，3：删除)
	std::string key;            ///< app_key
	std::string secret;         ///< app_secret
	int64       createUserID;   ///< 创建者userID
	std::string createTime;     ///< 创建时间
	std::string updateTime;     ///< 更新时间-新建分类时初始值与创建时间一致
	int32	    sort;           ///< 排序字段-未设置排序值时默认为1
	std::string column1;        ///< 预留字段1
	std::string column2;        ///< 预留字段2
	std::string column3;        ///< 预留字段3
	int64 createUnitID;
};

/// 应用分类实体
struct AppClassifyBean {
	int32       classifyID;     ///< 分类主键
	std::string classifyName;   ///< 分类名称
	int64       createUserID;   ///< 创建者userID
	int32       classifyStatus; ///< 分类状态 1：正常 2：已删除
	std::string createTime;     ///< 创建时间
	std::string updateTime;     ///< 更新时间-新建分类时初始值与创建时间一致
	int32       classifySort;   ///< 排序字段-未设置排序值时默认为1
	std::string classifyColumn1;///< 预留字段1
	std::string classifyColumn2;///< 预留字段2
	std::string classifyColumn3;///< 预留字段3
	int32 classifyType;
};

/// 要闻热点实体
struct HotNewsBean {
	int32       id;             ///< 要闻主键
	std::string newsTitle;      ///< 要闻标题
	std::string newsCover;      ///< 封面图片路径
	std::string newsContent;    ///< 正文内容
	int64       createUserID;   ///< 创建者Id
	std::string createTime;     ///< 创建时间
	std::string updateTime;     ///< 更新时间
	int32       newsSort;       ///< 排序字段
	std::string newsColumn1;    ///< 预留字段1
	std::string newsColumn2;    ///< 预留字段2
	std::string newsColumn3;    ///< 预留字段3
};

/// 用户与应用关系
struct AppRelationBean {
	int32       id;             ///< 关系id
	int64       userID;         ///< 用户id
	int64       appID;          ///< 应用id
	int32       classifyID;     ///< 应用类型id
	int32       relationStatus; ///< 关系状态 1：正常 2：已删除
	std::string createTime;     ///< 创建时间
	std::string updateTime;     ///< 更新时间
	int32       sort;           ///< 排序字段
	std::string relationColumn1;///< 预留字段1
	std::string relationColumn2;///< 预留字段2
	std::string relationColumn3;///< 预留字段3
};

/// 我的应用信息
struct MyAppInfo {
	AppClassifyBean appClassify;            ///< 应用分类
	std::vector<AppInfoBean> appInfoList;   ///< 应用集合
	int64 code;                             ///< 响应码
	std::string msg;                        ///< 响应码描述语
};

/// 应用商店
struct AppStore {
	std::vector<AppInfoBean> appInfoList;   ///< 应用集合
	int64       pageSize;                   ///< 每页显示的条数
	int64       pageNum;                    ///< 当前页数
	int64       totalCount;                 ///< 总条数
	int64       totalPage;                  ///< 总页数
	int64       code;                       ///< 响应码
	std::string msg;                        ///< 响应码描述语
};

/// 应用商店查询参数
struct AppStoreQueryParam {
	std::string appName;                    ///< 应用名称
	int64       userId;                     ///< 应用类型
	int64       appClassifyId;              ///< id
	int64       pageSize;                   ///< 每页显示的条数
	int64       pageNum;                    ///< 当前页数
	int32       searchType;
};

/// =========================================================================================
struct YMD {
	int32 year;                 // 0 不被使用
	int8 month;                 // 从1开始
	int8 day;                   // 从1开始
};
struct reqAppStore {
	int8 type;
	AppStoreQueryParam appStoreQueryParam;
	AppRelationBean appRelation;
	int64 value64;
};
/**
* 应用统计结果实体
* zhaorujia
*/
struct AppStatisticsResult{
	/* 结果描述 */
	std::string msg;
	/* 结果码 */
	std::string code;
};
struct respAppStore{
	int32 code;
	std::string what;
	std::vector<MyAppInfo> appInfos;
	AppStore appStore;
	std::vector<AppInfoBean> appBeans;
	std::vector<AppClassifyBean> classifyBeans;
	std::vector<HotNewsBean> hotNewsBeans;
	Result ret;
	AppStatisticsResult statResult;
};

struct EnterpriseUserBean {
	int64 userID;                           /// 用户ID
	int64 enterpriseID;                     /// 企业ID
	int64 orgID;                            /// 组织机构ID
	int64 roleID;                           /// 角色ID
	std::string Enname;                     /// 企业内用户名称
	std::string duty;                       /// 企业内用户职位
	std::string Enmail;                     /// 企业内用户email
	std::string Enmobile;                   /// 企业内用户手机号
	int8 status;                            /// 企业账号是否被停用 1：正常 2：停用
	int64 orderNum;                         /// 人员排序
	int64 newOrgID;
	std::string orgName;                    /// 组织名
	std::string extend;                     /// 扩展信息
	std::string accountName;                /// 账号名称
	int8 bizStatus;                         /// 业务状态：1：初始状态，2：在高管群
	std::string userHead;                   /// 头像
	std::string userExtend;
};

struct OrganizationBean {
	OrganizationBean() :
		orgID(0),
		enterpriseID(0),
		leaf(0),
		parentOrgID(0),
		orderNum(0),
		branchID(0),
		departLevel(0),
		subOrgNum(0),
		subUserNum(0),
		isHidden(0),
		provinceID(0),
		cityID(0),
		areaID(0) {}

	int64 orgID;                ///< 组织机构ID orgID.
	int64 enterpriseID;         ///< 企业ID enterpriseID.
	std::string orgName;        ///< 组织机构名称 orgName.
	std::string orgCode;        ///< 组织机构内码 orgCode.
	int8 leaf;                  ///< 是否叶节点 leaf.
	int64 parentOrgID;          ///< 父节点 parentOrgID.
	std::string remark;         ///< 备注 remark.
	int64 orderNum;             ///< 排序 orderNum.
	int64 branchID;             ///< 办公地ID branchID.
	std::string departID;       ///< 删除 departID.
	int8 departLevel;           ///< 组织级别 departLevel.
	int64 subOrgNum;            ///< 递归计算所有下级组织数 subOrgNum.
	int64 subUserNum;           ///< 递归计算所有下级成员数 subUserNum.
	int8 isHidden;              ///< 是否隐藏, 1对本部门公开 2对所有部门公开，3对部分部门公开 isHidden.
	int64 provinceID;           ///< 省份ID provinceID.
	std::string provinceName;   ///< 省份名称 provinceName.
	int64 cityID;               ///< 市ID cityID.
	std::string cityName;       ///< 市名称 cityName.
	int64 areaID;               ///< 县ID areaID.
	std::string areaName;       ///< 县名称 areaName.
	std::string orgNamePinyin;  ///< 拼音 orgNamePinyin.
	std::string extend;         ///< 拓展字段
	int32 resCode;              ///< 导入组织机构时,返回的错误码
	int32 exlRow;
};
struct AccountType{
	int8 type;                  // 账号类型 1：电话, 3：邮箱, 4：userID, 5:身份证, 6：豆豆号, 7:自定义帐号(不做限制)
	std::string accounts;       // 账号
	std::string mark;           // 标识
};
struct UserBean {
	int64 userID;               ///<用户ID
	std::string phoneNum;       //<可以删除
	std::string email;          ///<可以删除
	int16 userType;             ///<目前没有意义
	std::string name;           ///<用户名
	std::string pwd;            ///<用户密码
	int8 sex;                   ///<性别
	std::string area;           ///<区域
	YMD birthday;               ///<生日
	std::string school;         ///<毕业学校
	int64 qqNum;                ///<可以删除
	std::string maccode;        ///<目前无意义
	int8 status;                ///<用户状态 1：正常 2：停用 3: 注册邀请4: 影子用户，5:锁定，6:冻结
	std::string portraitURL;    ///<头像地址
	std::string sign;           ///<签名
	int8 timeZone;              ///<时区
	std::vector<std::string> phoneNums; ///<电话号码清单
	std::vector<std::string> emails;    ///<邮箱清单
	std::string oriPortraitURL;        ///<原始头像地址
	std::string idcard;                 ///<可以删除
	std::string accountName;            ///<账号名称
	std::string extend;                 ///<扩展信息
	int64 lockDeadline;                 ///<锁定截止时间，毫秒
	int64 remainLockDuration;           ///<剩余锁定时长，毫秒
	int64 SDKID;                        ///<SDKID
	std::string entExtend;              ///<企业扩展信息
	std::vector<AccountType> accounts;  ///<联系方式集合
	int8 regFlag;                       ///<注册标识0为更新1为注册
	int8 pwdStrength;                   ///<密码强度:1:弱,2:中,3:强
	std::string orgID;                  ///<组织结构id,多个用逗号分隔
	int64 roleID;                       ///<角色ID
	int8 bizStatus;                     ///<业务状态，1：初始默认，2：在高管层
	int8 uploadFlag;                    ///<上传标识, 1:未上传,2:已上传,3:已忽略
	int8 oldStatus;                     ///<保存冻结之前用户状态status的值
};
struct OrgUserAndChildNodes {
	int32 code;
	std::string what;
	std::vector<EnterpriseUserBean> users;
	std::vector<OrganizationBean> obeans;
	std::string oPower;
};

struct OrgSearchUserRet {
	EnterpriseUserBean ub;
	std::string power;
};

struct OrgSearchResult {
	std::vector<EnterpriseUserBean> uBeans;
	std::string resultFlag;
};

struct reqEnOS{
	int8 type;
	int64 value64;
	int64 value64_2;
	int64 value64_3;
	std::string valuestr;
	std::vector<int64> list_i64;
	std::map<std::string, std::string> params;
};

struct respEnOS{
	int32 code;
	std::string what;
	OrgUserAndChildNodes nodes;
	std::vector<OrgSearchUserRet> orgSearchUsers;
	OrgSearchResult searchRet;
	std::vector<EnterpriseUserBean> entUsers;
	std::vector<OrganizationBean> depts;
};

///客户端统计接口
struct AppStatisticsBean{
	/* 应用类型：
	* 1：门户应用类型 2.普通应用类型
	*/
	std::string appType;
	/* 应用ID */
	std::string appID;
	/* 用户ID */
	std::string userID;
	/* 组织机构ID*/
	std::string orgID;
	/* 组织机构CODE */
	std::string orgCode;
	/* 组织机构CODE */
	std::string unitID;
};

}