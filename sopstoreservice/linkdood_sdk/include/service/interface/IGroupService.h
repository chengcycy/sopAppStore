#pragma once

#include "../model/Group.h"
#include"../model/Packet.h"
#include "../model/Member.h"
#include "IService.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#define VER_GROUP INTERFACE_VERSION(1,0)
static const VRVIID IID_IGroupService = { 0x6df7882f, 0x5ab3, 0x4326, 0x4d, 0xd2, 0xaf, 0x3f, 0xb2, 0xd1, 0xa2, 0x16 };

namespace service
{

class IGroupService : public IService
{
public:

	virtual ~IGroupService(){}

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听群头像更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void regGroupHeadImgUpdateCb(std::function < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 监听群成员头像更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void regMemberHeadImgUpdateCb(std::function < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 监听群背景更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void regGroupBackImgUpdateCb(std::function < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 设置监听群信息更新的回调
	* @param[in] _1 操作类型 1.添加 2.更新，31.解散 32.移除 33.退出 34.自动解散
	* @param[in] _2 群信息
	*/
	virtual void regGroupRefreshCb(std::function< void(int8, const Group&) > cb) = 0;

	/**
	* \brief 设置监听群主更新的回调
	* @param[in] _1 群主ID
	* @param[in] _2 群主名
	* @param[in] _3 群ID
	* @param[in] _4 群名
	*/
	virtual void regTransferGroupCb(std::function< void(int64, const std::string&, int64, const std::string&) > cb) = 0;
	
	/**
	* \brief 设置监听群成员信息更新的回调
	* @param[in] _1 群ID
	* @param[in] _2 群成员信息
	*/
	virtual void regGrpMemInfoRefreshCb(std::function< void(int64, const Member&) > cb) = 0;

	/**
	* \brief  设置群成员列表更新的回调
	* @param[in] _1 操作类型  1 添加， 32 移除， 33 退出
	* @param[in] _2 群ID
	* @param[in] _3 变更的群成员集合
	*/
	virtual void regGrpMemRefreshCb(std::function< void(int, int64, std::vector<std::shared_ptr<Member> >&) > cb) = 0;

	/**
	* \brief  设置获取群成员列表的回调
	* @param[in] _1 错误信息，不使用，只是为了和getMemberList回调函数一致
	* @param[in] _2 群成员列表
	*/
	virtual void regGetGrpMemListCb(std::function<void(ErrorInfo, std::vector<std::shared_ptr<Member> >&)> cb) = 0;
	
	/**
	* \brief  监听群列表刷新
	* @param[in] _1 群列表
	*/
	virtual void regGroupListCb(std::function< void(std::vector<std::shared_ptr<TinyGroup> >&) > cb) = 0;


	/*****************************************请求接口*******************************************/


	/**
	* \brief 创建群
	* @param[in] level 传入群等级
	* @param[in] name 传入群名称
	* @param[in] members   传入群成员
	* @param[in] cb  传入接收结果回调  _1错误信息  _2群ID
	*/
	virtual void createGroup(int level, const std::string &name, std::vector<int64> &members, std::function<void(ErrorInfo, int64)> cb) = 0;

	/**
	* \brief 加群
	* @param[in] groupid 传入群id
	* @param[in] verify_info 传入验证信息
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void addGroup(int64 groupid, const std::string &verify_info, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 解散群
	* @param[in] type 传入操作类型
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void removeGroup(int type, int64 groupid, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 转让群
	* @param[in] groupid 传入群id
	* @param[in] userid 传入新群主的id
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void transferGroup(int64 groupid, int64 userid, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取群设置
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调  _1错误信息 \n
	*    _2  验证类型: 1.不允许任何人添加, 2.需要验证信息, 3.允许任何人添加.\n
	*	 _3	 是否允许群成员邀请好友加入群: 1.允许 2.不允许.
	*/
	virtual void getGroupSet(int64 groupid, std::function<void(ErrorInfo, int8, int8)> cb) = 0;

	/**
	* \brief 设置群设置
	* @param[in] groupid 传入群id
	* @param[in] verify_type 传入验证类型
	* @param[in] is_allow 传入是否允许成员邀请用户
	* @param[in] cb  传入接收结果回调  _1错误信息 
	*/
	virtual void setGroupSet(int64 groupid, int8 verify_type, int8 is_allow, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取群信息 （同步接口）
	* @param[in] groupid 传入群id
	* @param[out] groupInfo 群信息
	*/
	virtual void getGroupInfo(int64 groupid, Group& groupInfo) = 0;

	/**
	* \brief 设置群信息
	* @param[in] groupId 设置的群ID
	* @param[in] group  可设置的群信息
	* @param[in] cb  传入接收结果回调  _1错误信息 
	*/
	virtual void setGroupInfo(int64 groupId, GroupUpdate &group, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取群列表 （同步接口）
	* @param[in] cb  传入接收结果回调  _1群信息集合;
	*/
	virtual void getGroupList(std::vector<std::shared_ptr<TinyGroup> > &groups) = 0;

	/**
	* \brief 邀请群成员
	* @param[in] groupid 传入群id
	* @param[in] members 传入成员名单
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void inviteMember(int64 groupid,std::vector<int64> &members,std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 移除群成员
	* @param[in] groupid 传入群id
	* @param[in] userid 传入需要移除的成员id
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void removeMember(int64 groupid, int64 userid, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置群成员信息
	* @param[in] member 传入成员信息
	* @param[in] cb  传入接收结果回调
	*/
	virtual void setMemberInfo(Member &member, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 判断用户是否在群里 (同步接口)
	* @param[in] groupid 传入群id
	* @param[in] userid 传入成员id
	* @return false代表不是群成员
	*/
	virtual bool isInGroup(int64 groupId, int64 userId) = 0;

	/**
	* \brief 获取群成员信息 (同步接口)
	* @param[in] groupid 传入群id
	* @param[in] userid 传入成员id
	* @param[out] member返回成员信息
	* @return false代表没有此信息
	*/
	virtual bool getMemberInfo(int64 groupid, int64 userid, Member &member) = 0;

	/**
	* \brief  获取群成员列表
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调   _1错误信息  _2群成员信息集合
	*/
	virtual void getMemberList(int64 groupid, std::function<void(ErrorInfo, std::vector<std::shared_ptr<Member> >&)> cb) = 0;

	/**
	* \brief 获取群文件列表
	* @param[in] groupid 传入群id
	* @param[in] beginid 传入起始id
	* @param[in] count 传入数量
	* @param[in] flag 传入偏移标志0为向上1为向下
	* @param[in] cb  传入接收结果回调   _1错误信息 _2文件信息集合
	*/
	virtual void getGroupFileList(int64 groupid, int64 beginid, int count, int8 flag, std::function<void(ErrorInfo, std::vector<Fileinfo>&)> cb) = 0;

	/**
	* \brief 删除群文件
	* @param[in] files 传入群文件id
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void deleteGroupFile(std::vector<int64> &files, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取个人群聊背景图片
	* @param[in] groupId 群ID
	* @param[in] cb  传入接收结果回调   _1错误信息   _2图片URL
	*/
	virtual void getPersonalGroupImg(int64 groupId, std::function<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	* \brief 设置个人群聊背景图片
	* @param[in] groupId 群ID
	* @param[in] imgUrl 图片URL
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void setPersonalGroupImg(int64 groupId, const std::string &imgUrl, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置群消息免打扰模式
	* @param[in] groupId 群ID
	* @param[in] mode 提醒模式 1：提示并接收消息；2：不提示，接收仅显示数目；3：屏蔽消息
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void setGroupMsgRemindType(int64 groupId, int8 mode , std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取群消息免打扰模式
	* @param[in] groupId 群ID
	* @param[in] cb  传入接收结果回调   _1错误信息 _2提醒模式
	*/
	virtual void getGroupMsgRemindType(int64 groupId, std::function<void(ErrorInfo, int8)> cb) = 0;

	/**
	* \brief 设置群消息内容模式和V标
	* @param[in] groupId 群ID
	* @param[in] vSign 群V标 0为非v标群，1为v标群 -1为不设置
	* @param[in] msgContentMode 群通知消息内容模式: 1、通知详情  2、通知源，隐藏内容  3、完全隐藏   -1为不设置
	* @param[in] cb  传入接收结果回调   _1错误信息 _2提醒模式
	*/
	virtual void setGroupExtraInfo(int64 groupId, int8 vSign, int8 msgContentMode, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 判断是否为群成员 同步接口
	* @param[in] groupId 群ID
	* @param[in] memberId 群成员id
	* @return true代表为此群成员，返回false不为群成员
	*/
	//virtual bool isGroupMember(int64 groupId, int64 memberId) = 0;
};

} /*namespace service*/