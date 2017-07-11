#pragma once

#include "../model/SDKTypes.h"
#include "../model/Packet.h"
#include "../model/Msg.h"
#include "IService.h"
#include "../extModel/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

#define VER_EXT INTERFACE_VERSION(1,0)
static const VRVIID IID_IExtService = { 0x5dd084b3, 0x19f, 0x4109, 0x88, 0x92, 0x8f, 0xf9, 0x77, 0xa9, 0xac, 0xa2 };

namespace service
{

class IExtService : public IService
{
public:
	
	virtual ~IExtService(){}

	/*****************************************注册通知回调*******************************************/

	/**
	*\brief 注册企业成员更新完成回调，收到回到代表更新完成
	*/
	virtual void regEntUpdateFinishCb(std::function< void(int)> cb) = 0;

	/**
	* \brief 监听组织成员头像更新
	* @param[in] cb 传入结果回掉 _1 传入目标ID，人或者群; _2 传入头像
	*/
	virtual void regOrgMemHeadImgUpdateCb(std::function < void(int64, const std::string&) > cb) = 0;

	/*****************************************请求接口*******************************************/

	//Task
	/**
	* @brief 发送任务消息
	* @param[in] msg 任务消息
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 msgID; _3 sendTime;
	*/
	virtual void sendTaskMsg(Msg& msg, std::function<void(ErrorInfo,int64, int64)> cb) = 0;
	/**
	* @brief 置顶任务
	* @param[in] msgId 传入TaskId
	* @param[in] isTop 是否置顶  0：不置顶 1：置顶
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void topTask(int64 msgId,int8 isTop,std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 获取指派的任务
 	* @param[in] cb  传入接收结果回调 _1 错误号; _2 任务集;
	*/
	virtual void getApTask(std::function<void(ErrorInfo, std::vector<Task>&)> cb) = 0;
	/**
	* @brief 获取接收的任务
	* @param[in] cb  传入接收结果回调  _1 错误号; _2 任务集;
	*/
	virtual void getRecvTask(std::function<void(ErrorInfo, std::vector<Task>&)> cb) = 0;
	/**
	* @brief 获取历史任务
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 任务集;
	*/
	virtual void getHistoryTask(std::function<void(ErrorInfo, std::vector<Task>&)> cb) = 0;
	/**
	* @brief 获取任务上下文
	* @param[in] taskId  指定的TaskID
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 任务上下文;
	*/
	virtual void getBodyTask(int64 taskId, std::function<void(ErrorInfo, std::string&)> cb) = 0;
	/**
	* @brief 恢复任务
	* @param[in] taskId  需要恢复的TaskID
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void recoveryTask(int64 taskId, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 完成任务
	* @param[in] taskId  需要完成的任务 id
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void finishTask(int64 taskId, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 设置任务已读
	* @param[in] taskId  需设置已读的任务id
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void setReadTask(int64 taskId, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 获取任务回复消息
	* @param[in] type    1:根据msgID获取; 2:根据timeTask获取
	* @param[in] msgID    type = 1时赋值
	* @param[in] timeTask type = 2时赋值
 	* @param[in] count  要获取的的任务id
	* @param[in] begin  从第几条开始 如果从第一条开始就传0
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 回复消息;
	*/
	virtual void getRecvMsg(int8 type, int64 msgID, std::string timeTask, int count, int begin, std::function<void(ErrorInfo, std::vector<MsgPtr>&, std::vector<model::Task>&)> cb) = 0;

	
	//room
	/**
	* @brief 创建房间
	* @param[in] roomName 房间名
	* @param[in] ids  成员集合
	* @param[in] flag  是否置顶 0：不置顶 1：置顶
	* @param[in] url  头像url
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void createRoom(std::string& roomName, std::vector<int64>& ids, int8 flag, std::string& url, std::function<void(ErrorInfo,int32)> cb) = 0;
	/**
	* @brief 修改房间名称
	* @param[in] roomId  要修改的roomID
	* @param[in] newName   新名称
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void changRoomName (int roomId, std::string& newName, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief changRoomIcon
	* @param[in] roomId 要修改的roomID
	* @param[in] icoURL 头像的URL
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void changRoomIcon (int roomId, std::string& icoURL, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 删除房间
	* @param[in] roomID  房间ID
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void deleRoom(int roomID, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 获取房间信息
	* @param[in] roomID  房间ID
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 获取的房间信息;
	*/
	virtual void getRoom(int roomID, std::function<void(ErrorInfo, std::vector<room>&)> cb) = 0;
	/**
	* @brief 获取所有房间信息
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 获取的房间信息集合;
	*/
	virtual void getAllRoom( std::function<void(ErrorInfo, std::vector<room>&)> cb) = 0;
	/**
	* @brief 房间置顶
	* @param[in] roomId  房间ID
	* @param[in] isTop  是否置顶
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void topRoom(int roomId,int8 isTop,std::function<void(ErrorInfo)> cb) = 0;

	/**
	* @brief 房间增加人员
	* @param[in] roomId  房间ID
	* @param[in] vt  加入的成员
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/

	virtual void addRoomMember(int64 roomId, std::vector<int64> vt, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* @brief 房间删除人员
	* @param[in] roomId  房间ID
	* @param[in] vt  删除的成员
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void delRoomMember(int64 roomId, std::vector<int64> vt, std::function<void(ErrorInfo)> cb) = 0;


	//enterprise
	/**
	* @brief 获取企业列表
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 企业信息集合;
	*/
	//virtual void getEnterpriseListByUser(std::function<void(ErrorInfo, std::vector<entpriseInfo>&)> cb) = 0; //废弃
	/**
	* @brief getVisibleOrgUsers
	* @param[in] type 
	* 0:获取登陆时刻的组织机构，如果登陆后对后台组织机构进行了修改，本次登陆拉取不到，下次登陆才可以拉取到 \n
	* 1:获取当前时刻的组织机构 =1 比 =0 速度上慢了很多，建议使用 =0\n
	* @param[in] orgID  组织ID  传 0 表示获取根组织
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 组织集合; _3 企业用户信息;
	*/
	virtual void getVisibleOrgUsers(int8,int64, std::function<void(ErrorInfo, int8, int8, std::vector<OrganizationInfo>&, std::vector<EntpriseUserInfo>&)> cb) = 0;
	/**
	* @brief 根据条件查询企业用户列表
	* @param[in] EnterpriseUserQueryInfo  查询信息 见Packet.h
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 total 总数; _3 totalPage 总页数; _4 用户信息集合;
	*/
	virtual void queryEnterpriseUserlist(EnterpriseUserQueryInfo& enterpriseUserQueryInfo, std::function<void(ErrorInfo, int64, int64, std::map<std::string,std::vector<EntpriseUserInfo> >&)>  cb) = 0;
	/**
	* @brief 获取企业所有用户信息
	* @param[in] vt  需要获取的用户集合
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 返回企业用户信息;
	*/
	virtual void queryEntUserAll(std::vector<int64> vt, std::function<void(ErrorInfo, std::vector<EntpriseUserInfo>&)> cb) = 0;
	/**
	* @brief queryEntUser
	* @param[in] userId  用户id
	* @param [in] cb  传入接收结果回调 _1 错误号;_2 返回企业用户信息;
	*/
	virtual void queryEntUserOneById(int64 userId, std::function<void(ErrorInfo, std::vector<EntpriseUserInfo>&)> cb) = 0;
	/**
	* @brief queryEntUser
	* @param[in] userName  用户名
	* @param [in] cb  传入接收结果回调 _1 错误号;_2 返回企业用户信息;
	*/
	virtual void queryEntUserOneByName(std::string& userName, std::function<void(ErrorInfo, std::vector<EntpriseUserInfo>&)> cb) = 0;
	/**
	* @brief getOrgInfo
	* @param[in] orgId 组织Id
	* @param [in] cb  传入接收结果回调 _1 错误号;_2 组织信息;
	*/
	virtual void getOrgInfo(int64 orgId, std::function<void(ErrorInfo, OrganizationInfo&)> cb) = 0;
	virtual void getOrgInfos(std::vector<int64>& orgId, std::function<void(ErrorInfo,std::vector<OrganizationInfo>&)> cb) = 0;

	//msg
	/**
	* @brief 获取对应targetId中的所有消息数目
	* @param[in] targetId  targetId
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 消息数目;
	*/
	virtual void getMsgCountByTargetID(int64 targetId,std::function<void(ErrorInfo,int32)> cb) = 0;
	/**
	* @brief getMsgTopNGroup
	* @param[in] topN   获取聊天数量前topN的群组
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 targetID集合;_3 消息数目;
	*/
	virtual void getMsgTopNGroup(int topN, std::function<void(ErrorInfo, std::vector<int64>&, std::vector<int>&)> cb) = 0;
	/**
	* @brief getMsgTopNSession
	* @param[in] topN   获取聊天数目前topN的单聊
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 targetID集合;_3 消息数目;
	*/
	virtual void getMsgTopNSession(int topN, std::function<void(ErrorInfo, std::vector<int64>&, std::vector<int>&)> cb) = 0;
	/**
	* @brief 获取@自己最多的topN个群
	* @param[in] topN    获取前topN会话的群组
	* @param[in] cb  传入接收结果回调 _1 错误号;_2 targetID集合;_3 消息数目;
	*/
	virtual void getMsgTopNAtGroup(int topN, std::function<void(ErrorInfo, std::vector<int64>&, std::vector<int>&)> cb) = 0;


	//Note
	/**
	* @brief 添加记事本
	* @param[in] noteInfo  记事本信息 见Packet.h
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void addNote(BaseNoteInfo& noteInfo, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 获取记事本
	* @param[in] beginID  起始消息ID offsetFlag = 0 msgBeginID = 0时，代表从最大的消息Id进行查找
	* @param[in] offset  查询的数量
	* @param[in] offsetFlag  偏移标志；0.消息Id由大到小偏移 1.消息Id由小到大偏移 offsetFlag.
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 记事本集合
	*/
	virtual void getNote(int64 beginID, int32 offset, int8 offsetFlag, std::function<void(ErrorInfo, std::vector<BaseNoteInfo>&)> cb) = 0;
	/**
	* @brief 删除记事本
	* @param[in] noteId  需删除noteID集合
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void delNote(std::vector<int64>& noteId,std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 修改记事本
	* @description: 修改记事本
	* @param[in] baseInfo  新的note信息
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void editNote(BaseNoteInfo& baseInfo, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 归档记事本
	* @param[in] noteId  要归档的note id
    *  低4位：表示是否归档 0. 不归档，1. 归档
    *  高4位：表示是否置顶 0. 不置顶，1. 置顶
	* @param[in] isArchive
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void archiveNote(int64 noteId,int8 isArchive ,std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 置顶记事本
	* @param[in] noteId  要置顶的note id
	* @param[in] isTop  是否置顶
	* @param[in] cb  传入接收结果回调 _1 错误号;
	*/
	virtual void topNote(int64 noteId, int8 isTop, std::function<void(ErrorInfo)> cb) = 0;
	/**
	* @brief 搜索记事本
	* @param[in] info  搜索的信息 见Packet.h
	* @param[in] cb  传入接收结果回调 _1 错误号; _2 搜索的记事本集合
	************************************************************************/
	virtual void searchNote(searchNoteInfo& info, std::function<void(ErrorInfo, std::vector<BaseNoteInfo>&)> cb) = 0;
};

} /*namespace service*/
