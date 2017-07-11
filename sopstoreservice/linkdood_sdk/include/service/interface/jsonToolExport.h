#pragma once
#include <config.h>
#include <string>
#include <vector>

namespace service
{

enum
{
    // 普通文本消息(2),弱提示消息(8),任务消息(17),撤回消息(18),动态表情消息(19),红包消息(88)

	json_txtMsg = 0x01,          ///< 文本消息结构体

	json_FileMsg,				 ///<文件消息

	json_ImageMsg,                   ///< 图片消息

	json_AudioMsg,                   ///< 音频消息

	json_TipMsg,                   ///< 弱提示

	json_TipMsgProper,              ///<弱提示消息属性

	json_CardMsg,                   ///< 名片消息

	json_DynamicExpressMsg,          ///<动态表情消息

	json_VedioMsg,                   ///< 视频消息

	json_DelayMsg,        ///< 延迟消息

	json_MsgProperties,      ///< json_MsgProperties

	json_Receipt,      ///<回执消息

	json_EnVChat,      ///<私信消息

	json_MediaMsgResult,                   ///< MediaMsgResult

	json_ExtendInfo,                  ///<ExtendInfo

	json_MsgDetailInfo,                  ///< MsgDetailInfo

    json_APPInfo,       ///<  json_APPInfo

	json_TinyRecContact,       ///< 最近联系人

	json_DeviceType,         ///<deviceType 消息属性

	json_PositionMsg,     ///<位置消息

	json_WebMsg,   ///<网络消息

	json_PicWithText, ///<图文消息

	json_CombineMsg, ///<组合消息

	json_NineBlockMsg, ///<九宫格消息

	json_MsgMasterplate, ///模版消息

	json_MiniVedio, ///小视频 pc只解析

	json_conference,///视频会议

	json_DynamicExpressMsg2, ///动态表情2

};

/**********************************************************************/

// 普通文本消息  2
// 弱提示消息    8
// 任务消息     17
// 撤回消息     18
// 动态表情消息 19
// 红包消息     88
/***************************************************************************/
///媒体消息基类
struct jst_MediaMsgBase{
	jst_MediaMsgBase() :isEncrypt(0), encryptUser(0), encKey(""){}
	int32			isEncrypt;			 ///<是否加密
	int64			encryptUser;		 ///<加密者ID
	std::string		encKey;				 ///<加密秘钥
};
struct st_failAttchment{
	std::string localPath;
	std::string fileName;
	int fileSize;
};
struct jst_fileAttches{
	std::vector<st_failAttchment> attch;
};
///文本消息
struct jst_TextMsg :public jst_MediaMsgBase
{
	std::string textMsg;  ///<消息体内容
	int8 conferType;
};

///web 消息
struct jst_WebMsg :public jst_MediaMsgBase{
	std::string title;	  ///<网页内容标题
	std::string url;	  ///<网页链接地址
	std::string img;	  ///<网页内容第一张图片
	std::string desc;	  ///<网页内容摘要
};
///	文件信息
struct jst_FileMsg :public jst_MediaMsgBase{
	jst_FileMsg() :fileSize(0), fileID(0), operateType(0), fileStates(0){}
	std::string fileName;      ///<文件名
	std::string mediaUrl;      ///<url
	std::string filePath;      ///<本地文件路径server不需要处理，ctrl和ui上用这个字段
	int64 fileSize;           ///<文件大小
	int64 fileID;			  ///<文件ID
	int32 operateType;		  ///<操作类型 文件直传使用  1.收到对方取消发送的消息 2.收到对方取消接收的消息
	int   fileStates;		  ///<界面展示用 1.文件存在， 2.文件不存在需要重新下载 3.接收文件 4.正在上传或下载 5.重新发送, 
};

///	图片信息
struct jst_ImageMsg :public jst_MediaMsgBase
{
	jst_ImageMsg() :width(0), height(0), buddyId(0){}
	std::string imageContents;///<描述
	int32 width;			 ///<宽度
	int32 height;			 ///<高度
	std::string fileName;     ///<文件名
	std::string bigPath;     ///<大图文件路径/url
	std::string thumbPath;   ///<缩略图路径/url
	std::string imagePath;       ///<原图本地路径
	std::string thumbimgPath;    ///<缩略图本地路径
	int64 buddyId;    ///<九宫格消息使用
};
///九宫格消息

struct jst_NineBlock{	
	std::vector<jst_ImageMsg> nine;
};
///	语音信息
struct jst_AudioMsg :public jst_MediaMsgBase
{
	jst_AudioMsg() :mediaTime(0), status(0){}
	int32 mediaTime;			 ///<时长
	std::string fileName;     ///<文件名
	std::string meidaUrl;       ///<路径
	int status;     ///<ui层用，标志是否需要显示小红点 0、不需要 1、需要 
	std::string localPath;
};

///位置消息
struct jst_PositionMsg :public jst_MediaMsgBase{
	jst_PositionMsg(){}
	std::string area;  ///<地名
	double latitude; ///<精度
	double longitude; ///<纬度
};
///弱提示消息
struct jst_TipMsg :public jst_MediaMsgBase{
	jst_TipMsg():tipType(0){}
	int32 tipType;		  ///<弱提示消息子类型
	std::string tipMsg;  ///<消息体内容
};
struct jst_miniVedio :public jst_MediaMsgBase{
	jst_miniVedio() :buddyId(0), brustFlag(0){}

	int64 buddyId;
	int8 brustFlag;
	std::string preImgPath;
	std::string vedioFileName;
	int64 vedioHight;
	int64 vedioLenth;
	int64 vedioWideth;
	int64 vedioSize;
	std::string preImglocalPath;
	std::string videoPath;
};
///名片消息
struct jst_CardMsg
{
	jst_CardMsg() {}
	std::string id;   ///<名片人id
};
///动态表情消息
struct jst_DynamicExpressMsg
{
	std::string path;  ///<发送动态表情填表情名  接收动态表情返回的路径
};

///视频消息
struct jst_VedioMsg
{
	std::string channelID;
	std::string isSipChat;
	std::string videoType;
	std::string videostatus;
	std::string key;
	std::string version;
};

struct jst_picTextBean{
	jst_picTextBean() :index(0){}
	int32 index;
	std::string picUrl; ///<图片url
	std::string title; ///<标题
	std::string url; ///<url
	std::string dsc; ///<描述
};
///图文消息
struct jst_picWithTextMsg{
	std::vector<jst_picTextBean> vtMsgs; ///<图文消息集合
};


struct jst_ReceiptSubMsg{
	jst_ReceiptSubMsg() :isReceipt(0){}
	int isReceipt;
};

struct jst_DelaySubMsg
{
	jst_DelaySubMsg() :isDelayMsg(0), delaySendTime(0){}
	int32 isDelayMsg;		 ///<0：非延时，1：延时
	int64 delaySendTime;     ///<延时发送时间  取未来发送时间毫秒数（大于当前时间）时间戳形式长整形
};
struct jst_DynamicExpressMsg2{
	jst_DynamicExpressMsg2() :DyType(-1){}
	std::string code;
	std::string emoji;
	std::string mdCode;
	std::string meaning;
	int8 DyType;
};

struct jst_EnVChatSubMsg{
	jst_EnVChatSubMsg() : isEnVChat(0){}
	//int32 timeZone;			 ///<时区值
	int32 isEnVChat;		 ///<是否是私信
	//int32 deviceType;		 ///<设备类型 1PC 2手机
};

struct  jst_MsgProperties
{
	jst_MsgProperties() :timeZone(0), revokeMsgID(0){}
	int32 timeZone;			 ///<时区值	
	int64 revokeMsgID;    ///<要撤销的消息id	
};

struct jst_SubMsgProperties{
	jst_SubMsgProperties() :deviceType(0), revokeMsgId(0), timeZone(-1), delayTime(0), operType(0), extendmsgtype(-1), isPrivateMsg(-1), textSize(0), isdeal(0), iscmd(false), bwdtype(0){};
	int64 revokeMsgId;///<撤销消息使用
	///弱提示使用
	int operType;
	std::string tipTime;
	std::string operUser;
	std::string userInfo;
	std::string fileInfo;
	///音視頻消息使用
	int32 extendmsgtype; 
	std::string session;

	int32 timeZone; ///<时区

	int deviceType; ///<设备类型

	///task消息使用
	std::string timeTask;///<任务时间
	std::string isFinish;///<是否完成
	std::string isTask;///<任务标记
	std::string isRead;///<任务消息用
	///指令消息使用
	bool iscmd; ///<是否是指令消息

	std::string isDelay;			 ///<是否延迟消息
	int64 delayTime;				 ///<延迟时间
	std::string isReceipt;			 ///<是否阅后回执
	std::string isBurn;			 ///<是否阅后即焚
	int isPrivateMsg;		 ///<是否是私信   0不是 1是

	int textSize;///<字体大小 文本消息用
	int isdeal;

	int8 bwdtype;///文本消息用 敏感词类型
	std::vector<std::string> bwds;///文本消息用 敏感词列表

};


//上传媒体消息返回结构体
struct jst_MediaMsgResult
{
	jst_MediaMsgResult(int isthb, int isHead) :isthumb(isthb), isHeadJson(isHead), code(0), targetId(0), fileSize(0), fileid(0){}

	int         isthumb;///<入参 
	int         isHeadJson;///<入参

	int			code;
	int64		targetId;
	int64		fileSize;
	int64		fileid;
	std::string fileName;
	std::string url;
	std::string thumbUrl;
};

//扩展信息
struct jst_ExtendInfo{
	jst_ExtendInfo() :sex(0){}
	int32		sex;			///<性别
	std::string orgName;		///<组织名
	std::string phoneNum;		///<手机号
	std::string pOrgName;		///<父组织结点名称
	std::string postCode;		///<邮政编码
	std::string address;		///<地址
	std::string fax;			///<传真
	std::string duty;			///<职位
	std::string enmail;			///<电子邮件
	std::string enmobile;		///<手机号
	std::string enname;			///<在企业组织中的名称
};

//消息详细搜素具体消息的内容//只解析
struct jst_MsgDetailInfo
{//发送时间
	jst_MsgDetailInfo() :sendTime(0), sendUserId(0), msgId(0){}
	int64 sendTime;
	//发送者ID
	int64 sendUserId;
	//消息ID
	int64 msgId;
	//发送内容
	std::string context;
};

//企业应用信息//只解析
struct jst_AppInfo{
	jst_AppInfo() :openIDEncoded(0), appID(0), entID(0){}
	int8		openIDEncoded;  ///<openID是否编码，0:不编码，1:编码
	int64       appID;	  ///<应用ＩＤ
	int64       entID;	  ///<企业ＩＤ
	std::string appSign;  ///<应用标识
	std::string appName;  ///<应用名称
	std::string appEnName; ///<英文名
	std::string appIcon;  ///<应用图标
	std::string homeUrl;  ///<主页地址
	std::string entName;  ///<企业名称
	std::string appSecret;	 ///<应用密钥
	std::string appToken;	 ///<应用令牌
	std::string appMenus;   ///<应用菜单
	std::string subAccount; ///<应用子账号
	std::vector<std::string> configKey;	 ///<客户端配置key
	std::vector<std::string> configVal;	 ///<客户端配置value
};

struct jst_TinyRecContact{
	std::string lastMsg;
};

struct jst_MsgMasterplate {
	jst_MsgMasterplate() :createTime(0){}
	std::string  content;
	int64 createTime;
	std::string detailUrl;
	std::string title;
	std::string  toUsers;
	std::string status;
	std::string statColor;
	std::string titleColor;
	std::string typeM;
	std::string titleBGColor;
	std::string fields;
	std::string creator;
};

}