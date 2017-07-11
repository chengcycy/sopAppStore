#pragma once
#include "SDKTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <memory.h>
#include <string.h>
const int64  MSGMEMSIZE = 256;
namespace model 
{
///消息类型
enum MSG_TYPE
{
	MSG_TYPE_TEXT = 2,			///<文本消息
	MSG_TYPE_AUDIO,				///<语言消息
	MSG_TYPE_POSITION,			///<位置消息
	MSG_TYPE_IMG,				///<图片消息
	MSG_TYPE_FILE,				///<文件消息
	MSG_TYPE_CARD,				///<名片消息
	MSG_TYPE_TIP,				///<弱提示消息
	MSG_TYPE_WEB,				///<网页链接消息
	MSG_TYPE_PICTEXT = 12,		///<图文消息
	MSG_TYPE_COMBINE,           ///<组合消息
	MSG_TYPE_REVOKE = 18,		///<回执消息
	MSG_TYPE_DYNEXPRESSION,		///<动态表情消息
	MSG_TYPE_VOICE = 16,///<音頻消息
	MSG_TYPE_VIDEIO = 14,///<視頻消息
	MSG_TYPE_CONFER = 15,///<視頻会议消息
	MSG_TYPE_TASK = 17,///<任务消息
	MSG_TYPE_TEMPL = 26,    ///<模版消息
	MSG_TYPE_MINIVEDIO= 89,///<微视频消息
	MSG_TYPE_NINEBLOCK = 28,///<9图消息
	MSG_TYPE_DYNEXPRESSION2 = 27 ///<新动态表情
};

///消息状态
enum MSG_STATE
{
	MSG_TYPEX_UPLOAD_FAILED = 0x100,	///< 附加资源失败
	MSG_TYPEX_SEND_ERROR = 0x200,		///< 发送消息失败
	MSG_TYPEX_DOWNLOAD_FAILED = 0x400,  ///< 下载失败
	MSG_TYPEX_SENDING = 0x1000,			///< 正在发送消息
	MSG_TYPEX_UPLOADING = 0x2000,		///< 正在上传附件
};

struct FailAttchment{
	FailAttchment() :filesize(0){}
	int64 filesize;   ///<发送失败且非一步发送时 存储的是文件大小
	std::string filePath;///<发送失败且非一步发送时 存储的是文件本地路径
	std::string fileName;///<发送失败且非一步发送时 存储的是文件名
};
///消息基类
class Msg 
{
public:
	Msg() :msgType(0), msgId(0), targetId(0), fromId(0), toId(0),
		relatedUsers(0), noStore(0), time(0), localId(0), isPrivateMsg(0), timeZone(-1), isBurn(0), activeType(0), deal(false), msgRemindMode(0)
	{}
	virtual ~Msg() {}

	bool operator == (const Msg & rhs) const
	{
		if (isBurn != rhs.isBurn)
			return false;
		if (msgType != rhs.msgType)
			return false;
		if (msgId != rhs.msgId)
			return false;
		if (targetId != rhs.targetId)
			return false;
		if (fromId != rhs.fromId)
			return false;
		if (toId != rhs.toId)
			return false;
		if (relatedUsers != rhs.relatedUsers)
			return false;
		if (limitRange != rhs.limitRange)
			return false;
		if (body != rhs.body)
			return false;
		if (relatedMsgId != rhs.relatedMsgId)
			return false;
		if (sourceId != rhs.sourceId)
			return false;
		if (noStore != rhs.noStore)
			return false;
		if (msgProperties != rhs.msgProperties)
			return false;
		if (time != rhs.time)
			return false;
		if (localId != rhs.localId)
			return false;
		if (format != rhs.format)
			return false;
		if (isPrivateMsg != rhs.isPrivateMsg)
			return false;
		return true;
	}
	int8 activeType;
	int8  isBurn;            ///<0x01为阅后即焚 
	int8 deviceType;         ///<设备类型
	int msgType;			///<消息类型
	int8 noStore;			///<本地不存储消息  0为存储，1为不存储	
	int8 isPrivateMsg;		///<是否是私信   0不是 1是
	int64 msgId;			///<消息ID
	int64 targetId;			///<会话者ID（群或用户等）
	int64 localId;			///<本地ID
	int64 fromId;			///<发送者ID
	int64 toId;				///<接收者ID
	int64 relatedMsgId;		///<关联消息ID
	int64 lastMsgId;		///<上一条消息ID
	int64 time;				///<消息发送的时间
	int   timeZone;         ///<时区
	std::string sourceId;	///<会话来源ID 1_groupID表示传的群ID，2_orgID表示传的组织ID
	std::string body;		///<消息内容 
	std::string msgProperties;		///<消息属性
	std::string format;		///<格式
	std::vector<int64> relatedUsers;///<秘聊时相关的用户ID
	std::vector<int64> limitRange; ///<@人员列表
	std::string loginfoPath; ///发送消息，登录信息路径。仅发送时使用

	std::string userName;///<用户名 组合消息用
	std::string userPic;///<用户头像 组合消息用

	bool deal;///<标记已处理

	int8 msgRemindMode;		//与0x0F 0.免打扰 1.提醒始终有声音  2.提醒始终无声音  3.提醒  4.不提醒，仅显示条目 5.根据免打扰时间段判断是否免打扰
							//与 0xF0, 1、通知详情  2、通知源，隐藏内容  3、完全隐藏
};

///文本消息
class MsgText : public Msg 
{
public:
	MsgText() :isReceipt(false), isDelay(false), isRbtMsg(false), delayTime(0), fontSize(0), bwdType(0)
	{ 
		msgType = MSG_TYPE_TEXT; 
	}
	MsgText(Msg& msg) :Msg(msg), isReceipt(false), isDelay(false), isRbtMsg(false), delayTime(0), fontSize(0), bwdType(0)
	{
		msgType = MSG_TYPE_TEXT;
	}

	~MsgText(){}

	bool operator == (const MsgText & rhs) const
	{
		return (isReceipt == rhs.isReceipt) && (isDelay == rhs.isDelay);
	}
	bool isRbtMsg;           ///<是否是机器人消息
	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	bool isReceipt;			///<是否阅后回执
	int fontSize;
	int8 bwdType;           ///<敏感词类型(发送不用传)
	std::vector<std::string> bwds;///<敏感词集合(发送不用传)
};

///音頻消息
class MsgVoice : public Msg
{
public:
	MsgVoice() :extendMsgType(0)
	{
		msgType = MSG_TYPE_VOICE;
		session.resize(MSGMEMSIZE);
	}
	MsgVoice(Msg& msg) :Msg(msg), extendMsgType(0)
	{
		msgType = MSG_TYPE_VOICE;
	}

	~MsgVoice(){}

	bool operator == (const MsgVoice & rhs) const
	{
		return (extendMsgType == rhs.extendMsgType) && (session == rhs.session);
	}
	int extendMsgType;
	std::string session;
};
///視頻消息
class MsgVedio : public Msg
{
public:
	MsgVedio()
	{
		msgType = MSG_TYPE_VIDEIO;
		channelID.resize(MSGMEMSIZE);
		isSipChat.resize(MSGMEMSIZE);
		videoType.resize(MSGMEMSIZE);
		videostatus.resize(MSGMEMSIZE);
		key.resize(MSGMEMSIZE);
		version.resize(MSGMEMSIZE);
	}
	MsgVedio(Msg& msg) :Msg(msg)
	{
		msgType = MSG_TYPE_VIDEIO;
	}

	~MsgVedio(){}

	
	std::string channelID;
	std::string isSipChat;//1,音频 4，视频 5，p2p  (只适用单点和p2p)
	std::string videoType;
	std::string videostatus;
	std::string key;
	std::string version;//没值的是 单点音视频 或者 p2p; 有值  "rtc@1.0.0"  ///rtc协议版本  "agora@1.0.0" ///声网协议版本
};
///位置消息
class MsgPosition : public Msg
{
public:
	MsgPosition() :isDelay(false), latitude(0), longitude(0), delayTime(0)
	{
		msgType = MSG_TYPE_POSITION;
		name.resize(MSGMEMSIZE);
	}
	MsgPosition(Msg& msg) :Msg(msg), isDelay(false), latitude(0), longitude(0), delayTime(0)
	{
		msgType = MSG_TYPE_POSITION;
	}
	~MsgPosition(){}

	bool operator == (const MsgPosition &rhs) const
	{
		return (name == rhs.name) && (isDelay == rhs.isDelay) &&
			(latitude == rhs.latitude) && (longitude == rhs.longitude);
	}
	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	std::string name;		///<地名
	double latitude;		///<纬度
	double longitude;		///<经度
};
///文件消息
class MsgFile : public Msg 
{
public:
	MsgFile() :isDelay(false), states(0), size(0), fileId(0), isOld(false), delayTime(0), isResume(false)
	{ 
		msgType = MSG_TYPE_FILE; 
		fileName.resize(MSGMEMSIZE);
		filePath.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
		url.resize(MSGMEMSIZE);
	}
	MsgFile(Msg& msg) :Msg(msg), isDelay(false), states(0), size(0), fileId(0), isOld(false), delayTime(0), isResume(false)
	{
		msgType = MSG_TYPE_FILE;
	}
	~MsgFile(){}

	bool operator == (const MsgFile& rhs) const
	{
		return (isDelay == rhs.isDelay) && (states == rhs.states) &&
			(size == rhs.size) && (fileId == rhs.fileId) && (fileName == rhs.fileName) &&
			(filePath == rhs.filePath) && (url == rhs.url) && (encryptKey == rhs.encryptKey);
	}

	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	int states;
	int64 size;				///<文件大小  
	int64 fileId;			///<文件ID
	std::string fileName;	///<文件名  
	std::string filePath;	///<文件本地路径  
	std::string encryptKey;///<加密KEY
	std::string url;		///<文件URL	 一步发送消息时不赋值

	bool isOld;      ///<是否是老的形式(非一步发送)
	bool isResume;   ///<是否断点上传(一步发消息时使用)
	
};


///图片消息
class MsgImg : public Msg 
{
public:
	MsgImg() :isDelay(false), width(0), height(0), isCmd(false), isOld(false), buddyId(0), delayTime(0)
	{ 
		msgType = MSG_TYPE_IMG; 
		thumbUrl.resize(MSGMEMSIZE);
		mainUrl.resize(MSGMEMSIZE);
		thumbPath.resize(MSGMEMSIZE);
		mainPath.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
		fileName.resize(MSGMEMSIZE);
		imageContents.resize(MSGMEMSIZE);
	}
	MsgImg(Msg& msg) :Msg(msg), isDelay(false), width(0), height(0), isCmd(false), isOld(false), buddyId(0), delayTime(0)
	{
		msgType = MSG_TYPE_IMG;
	}
	~MsgImg(){}

	bool operator == (const MsgImg& rhs) const
	{
		return (width == rhs.width) && (height == rhs.height) && (fileName == rhs.fileName) &&
			(thumbUrl == rhs.thumbUrl) && (mainUrl == rhs.mainUrl) && (encryptKey == rhs.encryptKey) &&
			(isDelay == rhs.isDelay);

	}
public:
	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	int width;				///<图像宽度
	int height;				///<图像高度
	std::string thumbUrl;	///<缩略图URL 一步发送消息时不赋值
	std::string mainUrl;	///<大图URL  一步发送消息时不赋值
	std::string thumbPath;	///<缩略图本地地址 一步发送消息时使用
	std::string mainPath;	///<大图本地地址 一步发送消息时使用
	std::string encryptKey;///<加密KEY
	std::string fileName;   ///<文件名  
	bool isCmd; ///<是否是指令消息
	std::string imageContents;///<图片描述

	int64 buddyId;    ///<九宫格消息使用
	bool isOld;      ///<是否是老的形式(非一步发送)
};

///动态表情
class MsgDynExpression : public Msg 
{
public:
	MsgDynExpression()
	{ 
		msgType = MSG_TYPE_DYNEXPRESSION; 
	}
	MsgDynExpression(Msg& msg) :Msg(msg)
	{
		msgType = MSG_TYPE_DYNEXPRESSION;
	}
	~MsgDynExpression(){}
};

class MsgCard : public Msg
{
public:
	MsgCard() :isDelay(false), delayTime(0)
	{
		msgType = MSG_TYPE_CARD;
		mediaUrl.resize(MSGMEMSIZE*2);
	}
	MsgCard(Msg& msg) :Msg(msg), isDelay(false), delayTime(0)
	{
		msgType = MSG_TYPE_CARD;
	}
	~MsgCard(){}

	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	std::string mediaUrl;	///<名片url
};
///tip消息
class MsgTip : public Msg 
{
public:
	MsgTip() :tipType(0), operType(0)
	{ 
		msgType = MSG_TYPE_TIP; 
		tipTime.resize(MSGMEMSIZE);
		operUser.resize(MSGMEMSIZE);
		userInfo.resize(MSGMEMSIZE);
		fileInfo.resize(MSGMEMSIZE);
	}
	MsgTip(Msg& msg) :Msg(msg),tipType(0), operType(0)
	{
		msgType = MSG_TYPE_TIP;
	}
	~MsgTip(){}
	bool operator == (const MsgTip& rhs) const 
	{
		return (tipType == rhs.tipType) && (operType == rhs.operType) && (tipTime == rhs.tipTime) &&
			(operUser == rhs.operUser) && (userInfo == rhs.userInfo);
	}

	int tipType; ///<tip 类型
	int operType;///<操作类型
	std::string tipTime;///<时间
	std::string operUser;///<操作userId
	std::string userInfo;///<用户信息
	std::string fileInfo;///<文件信息
};

///网页消息
class MsgWeb : public Msg
{
public:
	MsgWeb()
	{
		msgType = MSG_TYPE_WEB;
		title.resize(MSGMEMSIZE);
		url.resize(MSGMEMSIZE);
		img.resize(MSGMEMSIZE);
		desc.resize(MSGMEMSIZE*2);
	}
	MsgWeb(Msg& msg) :Msg(msg)
	{
		msgType = MSG_TYPE_WEB;
	}
	~MsgWeb(){}
	bool operator == (const MsgWeb& rhs) const
	{
		return (title == rhs.title) && (url == rhs.url) && (img == rhs.img) && (desc == rhs.desc);
	}

	std::string title;	 ///<网页内容标题
	std::string url;	 ///<网页链接地址
	std::string img;	 ///<网页内容第一张图片
	std::string desc;	 ///<网页内容摘要
};

///回执消息
class MsgRevoke : public Msg 
{
public:
	MsgRevoke() :revokeMsgId(0)
	{ 
		msgType = MSG_TYPE_REVOKE; 
	}
	MsgRevoke(Msg& msg) :Msg(msg),revokeMsgId(0)
	{
		msgType = MSG_TYPE_REVOKE;
	}
	~MsgRevoke(){}

	bool operator == (const MsgRevoke& rhs) const 
	{
		if (revokeMsgId != rhs.revokeMsgId)
			return false;

		return true;
	}
public:
	int64 revokeMsgId;///<id
};
///音频消息
class MsgAudio :public Msg{
public:
	MsgAudio() :mediaTime(0), status(0), isOld(false){
		msgType = MSG_TYPE_AUDIO;
		fileName.resize(MSGMEMSIZE);
		meidaUrl.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
		localPath.resize(MSGMEMSIZE);
	}
	MsgAudio(Msg& msg) :Msg(msg), mediaTime(0), status(0), isOld(false){
		msgType = MSG_TYPE_AUDIO;
	}
	bool operator == (const MsgAudio& rhs) const
	{
		return (mediaTime == rhs.mediaTime) && (fileName == rhs.fileName) && (meidaUrl == rhs.meidaUrl) && (status == rhs.status);
	}
	~MsgAudio(){};

	int32 mediaTime;			///<时长
	std::string fileName;    ///<文件名
	std::string meidaUrl;      ///<路径
	std::string encryptKey;///<加密KEY
	int status;    ///<ui层用，标志是否需要显示小红点 0、不需要 1、需要 
	std::string localPath;		//音频本地路径 

	bool isOld;      ///<是否是老的消息(非一步发送)
};


///图文消息
struct picTextBean{
	picTextBean() :index(0){}
	int32 index;
	std::string picUrl;///<图片url
	std::string title;///<标题
	std::string url;///<url
	std::string dsc;///<描述

	bool operator == (const picTextBean& rhs) const
	{
		return (index == rhs.index) && (picUrl == rhs.picUrl) && (title == rhs.title) && (url == rhs.url) && (dsc==rhs.dsc);
	}
};
///图文消息
class MsgPicWithText :public Msg{
public:
	MsgPicWithText(){
		msgType = MSG_TYPE_PICTEXT;
	}
	MsgPicWithText(Msg& msg) : Msg(msg){
		msgType = MSG_TYPE_PICTEXT;
	}

	bool operator == (const MsgPicWithText& rhs) const
	{
		return (vtPtBean == rhs.vtPtBean);
	}
	~MsgPicWithText(){}

	std::vector<picTextBean> vtPtBean;///<消息集合
};


class MsgDynExpression2 :public Msg{
public:
	MsgDynExpression2() :DyType(0), textSize(0){
		msgType = MSG_TYPE_DYNEXPRESSION2;
		code.resize(MSGMEMSIZE);
		emoji.resize(MSGMEMSIZE);
		mdCode.resize(MSGMEMSIZE);
		meaning.resize(MSGMEMSIZE);
	}
	std::string code;
	std::string emoji;
	std::string mdCode;
	std::string meaning;
	int8 DyType;
	int textSize;

};
class MsgTask :public Msg{
public:
	MsgTask(){
		msgType = MSG_TYPE_TASK;
		timeTask.resize(MSGMEMSIZE);
		isFinish.resize(MSGMEMSIZE);
		isTask.resize(MSGMEMSIZE);
		isRead.resize(MSGMEMSIZE);
		fontSize = 0;
	}
	~MsgTask(){}
	std::string timeTask;
	std::string isFinish;
	std::string isTask;
	std::string isRead;
	int fontSize;

};

struct st_Masterplate{
	std::string content;
	std::string num;
	std::string proposer;
	std::string approver;
};
class MsgMasterplate :public Msg{
public:
	MsgMasterplate() :createTime(0){
		msgType = MSG_TYPE_TEMPL;
		content.resize(MSGMEMSIZE);
		detailUrl.resize(MSGMEMSIZE);
		title.resize(MSGMEMSIZE);
		toUsers.resize(MSGMEMSIZE);
		status.resize(MSGMEMSIZE);
		statColor.resize(MSGMEMSIZE);
		titleColor.resize(MSGMEMSIZE);
		type.resize(MSGMEMSIZE);
		titleBGColor.resize(MSGMEMSIZE);
		fields.resize(MSGMEMSIZE*2);
		creator.resize(MSGMEMSIZE);
	}
	std::string  content;
	int64 createTime;
	std::string detailUrl;
	std::string title;
	std::string  toUsers;
	std::string status;
	std::string statColor;
	std::string titleColor;
	std::string type;
	std::string titleBGColor;
	std::string fields;
	std::string creator;

};
class MsgMiniVedio :public Msg{
public:
	MsgMiniVedio() :buddyId(0), brustFlag(0), vedioHight(0), vedioLenth(0), vedioWideth(0),vedioSize(0){
		msgType = MSG_TYPE_MINIVEDIO;
		preImgPath.resize(MSGMEMSIZE);
		vedioFileName.resize(MSGMEMSIZE);
		localPreImgPath.resize(MSGMEMSIZE);
		localVedioPath.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
	}
	int64 buddyId;					///< 接收人ID
	int8 brustFlag;					///< 是否阅后即焚
	std::string preImgPath;			///< 预览图片服务器地址  一步发送消息时不赋值
	std::string vedioFileName;		///< 视频服务器地址	 一步发送消息时不赋值
	std::string localPreImgPath;	///< 本地预览图片路径 一步发送消息时使用
	std::string localVedioPath;		///< 本地视频路径	一步发送消息时使用
	int64 vedioHight;				///< 视频分辨率高
	int64 vedioLenth;				///< 视频长, （毫秒）
	int64 vedioWideth;				///< 视频分比率宽
	int64 vedioSize;				///< 视频大小（Byte）
	std::string encryptKey;///<加密KEY

};

struct ImgMsgInner{

	ImgMsgInner() :toId(0), fromId(0), msgType(MSG_TYPE_IMG), msgId(0), time(0), height(0), width(0), buddyId(0), isDelay(0), delayTime(0), isCmd(false){}
	int64 toId;
	int64 fromId;
	std::string userName;
	std::string userPic;
	int64   msgType;
	int64   msgId;
	int64   time;

	std::string encryptKey;
	std::string fileName;
	int height;
	int width;
	std::string mainUrl;
	std::string thumbUrl;
	std::string body;
	int64 buddyId;
	std::string mainPath;
	std::string thumbPath;

	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	bool isCmd; ///<是否是指令消息
	std::string imageContents;///<图片描述
};

 
struct TextMsgInner{
	TextMsgInner() :toId(0), fromId(0), msgType(MSG_TYPE_TEXT), msgId(0), time(0), isRbtMsg(false), isDelay(false), delayTime(0), isReceipt(false){}
	int64 toId;
	int64 fromId;
	std::string userName;
	std::string userPic;
	int64   msgType;
	int64   msgId;
	int64   time;

	bool isRbtMsg;           ///<是否是机器人消息
	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	bool isReceipt;			///<是否阅后回执
	std::string  body;      ///<消息体
};

struct AudioMsgInner{
	AudioMsgInner() :toId(0), fromId(0), msgType(MSG_TYPE_AUDIO), msgId(0), time(0), mediaTime(0), status(0){}
	int64 toId;
	int64 fromId;
	std::string userName;
	std::string userPic;
	int64   msgType;
	int64   msgId;
	int64   time;

	int32 mediaTime;			///<时长
	std::string fileName;    ///<文件名
	std::string meidaUrl;      ///<路径
	std::string encryptKey;///<加密KEY
	int status;    ///<ui层用，标志是否需要显示小红点 0、不需要 1、需要 
	std::string localPath;		//音频本地路径 
};

struct PositionMsgInner{
	PositionMsgInner() :toId(0), fromId(0), msgType(MSG_TYPE_POSITION), msgId(0), time(0), isDelay(false), delayTime(0), latitude(0), longitude(0){}
	int64 toId;
	int64 fromId;
	std::string userName;
	std::string userPic;
	int64   msgType;
	int64   msgId;
	int64   time;

	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	std::string name;		///<地名
	double latitude;		///<纬度
	double longitude;		///<经度
};
class MsgConference:public Msg{

public:
	MsgConference() :conferType(0){
		msgType = MSG_TYPE_CONFER;
	}
	std::string comment;
	int8 conferType;
};
#ifdef SDK_FOR_ANDROID
class MsgNineBlock :public Msg{
public:
	MsgNineBlock() {
		msgType = MSG_TYPE_NINEBLOCK;
	}
	std::vector<ImgMsgInner> nine;
};
class MsgCombine :public Msg{
public:
	MsgCombine(){
		msgType = MSG_TYPE_COMBINE;
	}
	~MsgCombine(){}
	std::vector<MsgText> mVt_TextMsg;
	std::vector<MsgImg> mVt_ImgMsg;
	std::vector<MsgWeb> mVt_WebMsg;
	std::vector<MsgAudio> mVt_AudMsg;
	std::vector<MsgPosition> mVt_PosMsg;
	std::vector<MsgFile> mVt_FileMsg;
	std::vector<MsgCard> mVt_CardMsg;
	std::vector<MsgTip> mVt_TipMsg;
	std::vector<MsgPicWithText> mVt_PicTextMsg;
	std::vector<MsgDynExpression> mVt_Dy1Msg;
	std::vector<MsgVoice> mVt_VoiceMsg;
	std::vector<MsgTask> mVt_TaskMsg;
	std::vector<MsgMasterplate> mVt_TemlMsg;
	std::vector<MsgMiniVedio> mVt_MiniVedioMsg;
	std::vector<MsgNineBlock> mVt_NineMsg;
	std::vector<MsgDynExpression2> mVt_Dy2Msg;
};

#else
class MsgCombine :public Msg{
public:
	MsgCombine(){
		msgType = MSG_TYPE_COMBINE;
	}
	~MsgCombine(){}
	std::vector<std::shared_ptr<Msg> > mVt_msg;	
};
class MsgNineBlock :public Msg{
public:
	MsgNineBlock() {
		msgType = MSG_TYPE_NINEBLOCK;
	}
	std::vector<MsgImg> nine;
};
#endif

typedef std::shared_ptr<Msg> MsgPtr;

template<typename T>
T& msgCast(Msg& val){ return dynamic_cast<T&>(val); }

template <typename T>
std::shared_ptr<T> msgPointCast(MsgPtr val){ return std::dynamic_pointer_cast<T>(val); }
	
} /*namespace model*/