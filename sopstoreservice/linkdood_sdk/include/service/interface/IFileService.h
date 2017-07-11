#pragma once

#include "../model/SDKTypes.h"
#include "../model/Packet.h"
#include "IService.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <map>

#define VER_FILE INTERFACE_VERSION(1,0)
static const VRVIID IID_IFileService = { 0xc1388c4f, 0x9cb4, 0x4907, 0xa2, 0xee, 0x18, 0xab, 0x98, 0x72, 0x2a, 0x54 };

namespace service
{

class IFileService : public IService
{
public:
	virtual ~IFileService(){}

	/**
	* \brief 注册进度推送
	*@param cb _1 进度对应的文件的localId _2 进度标示 _3进度 _4文件当年传入大小/文件总大小
	*/
	virtual void regProcessCb(std::function<void(int64, int32, int32, const std::string&)> cb) = 0;
	/**
	* \brief 注册p2p用户状态改变推送
	*@param cb _1 用户Id _2 0x01 PC , 0x02 移动终端 _3 上线 0 ， 下线， 1
	*/
	virtual void regP2pUserStatusChgCb(std::function<void(int64, int8, int8)> cb) = 0;
	/**
	* \brief 注册p2p用户发送文件请求推送
	*@param cb _1 见Packet.h 中P2pSendFileReq注释
	*/
	virtual void regP2pSendFileReqCb(std::function<void(P2pSendFileReq&)> cb) = 0;
	/**
	* \brief 注册p2p用户文件传输操作推送
	*@param  cb _1 接收 0,  取消 1 _2 发送标识taskID
	*/
	virtual void regP2pFileTransOpCb(std::function<void(int8, int64)> cb) = 0;

	/**
	* \brief 上传头像
	* @param[in] path 传入头像本地路径
	* @param[in] cb  传入接收结果回调 _1错误信息  _2大图地址json _3缩略图地址json
	*/
	virtual void uploadAvatar(const std::string &path, std::function<void(ErrorInfo, const std::string&, const std::string&)> cb) = 0;

	/**
	* \brief 上传文件  ///若断点上传,key必须一致
	* @param[in] targetId 人或群的id
	* @param[in] cb  传入接收结果回调 _1错误信息 _2目标Id _3服务器返回的json
	* @param[in] pro  进度回调 _1 extra_req  _2process 
	* @return 每个文件对应的唯一localID
	*/
	virtual int64 uploadFile(UploadFileProperty &fileProperty, std::function<void(ErrorInfo, int64, const std::string&)> cb,
						std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;

	/**
	* \brief 下载文件
	* @param[in] targetId 发送者的targetId
	* @param[in] fileMsgId 文件消息的msgID
	* @param[in] path 传入下载路径
	* @param[in] url 传入url
	* @param[in] cb  传入接收结果回调 _1错误信息  _2本地路径 _3发送者ID
	* @param[in] pro  进度回调
	* @return 每个文件对应的唯一localID
	*/
	virtual int64 downloadFile(DownloadFileProperty &fileProperty, std::function<void(ErrorInfo, const std::string&, int64)> cb, 
							std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;

	/**
	* \brief 下载外部文件
	* @param[in] localPath 文件本地保存路径 
	* @param[in] url  flag = 0时为远程路径完整的URL路径  flag = 1时为远程路径,从消息JSON中解析出来的路径
	* @param[in] cb  传入接收结果回调 _1错误信息 
	* @param[in] pro  进度回调
	* @return 每个文件对应的唯一localID
	*/
	virtual int64 downloadExternalFile(const std::string &localPath, const std::string &url, int8 flag, std::function<void(ErrorInfo)> cb,
								std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;

	/**
	* \brief 上传照片
	* @param[in] targetId 人或群的id
	* @param[in] thumbimg 传入缩略图
	* @param[in] srcimg 传入原图
	* @param[in] encryptkey 传入解密密码
	* @param[in] cb  传入接收结果回调 _1错误信息 _2目标ID， _3原图JSON， _4缩略图JSON
	*/
	virtual void uploadImage(int64 targetId, int64 localId, const std::string &thumbimg, const std::string &srcimg, const std::string &encryptkey,
							std::function<void(ErrorInfo, int64, const std::string&, const std::string&)> cb,
							std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;

	/**
	* \brief 下载图片
	* @param[in] targetId 人或群的id
	* @param[in] url 传入图片url
	* @param[in] cb  传入接收结果回调 _1错误信息  _2图片名  _3对方ID
	*/                                       
	virtual void downloadImage(int64 targetId, const std::string &url, std::function<void(ErrorInfo, const std::string&, int64)> cb,
								std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;

	/**
	* \brief 下载九宫格图片
	* @param[in] targetId 人或群的id
	* @param[in] url 传入所有图片url
	* @param[in] cb  传入接收结果回调 回调的次数和上传图片的次数一致  _1错误信息  _2对方ID _3图片名 _4图片索引 _5图片总数
	*/                                       
	virtual void downloadNineBoxImage(int64 targetId, std::vector<std::string> &url, std::function<void(ErrorInfo, int64, const std::string&, int8, int8)> cb,
								std::function<void(int32, int32, const std::string&)> pro = nullptr) = 0;
	/**
	* \brief 解密文件
	* @param[in] encryptkey 传入解密密码
	* @param[in] srcpath 传入原图路径
	* @param[in] destpath 传入解密后图片路径
	*/
	virtual bool decryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath) = 0;
	/**
	* \brief 加密文件
	* @param[in] encryptkey 传入加密密码
	* @param[in] srcpath 传入原图路径
	* @param[in] destpath 传入加密后图片路径
	*/
	virtual bool encryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath) = 0;

	/**
	* \brief 获取文件列表
	* @param[in] targetid 传入查询对象id
	* @param[in] fileid 传入起始文件id
	* @param[in] count 传入数量
	* @param[in] flag 传入偏移标志0为向上1为向下
	* @param[in] cb  传入接收结果回调 _1错误信息  _2文件信息集合
	*/
	virtual void getFileList(int64 targetid, int64 fileid, int count, int flag, std::function<void(ErrorInfo, std::vector<Fileinfo>&)> cb) = 0;

	/**
	* \brief 通过文件消息ID得到文件详细信息 同步接口
	* @param[in] fileMsgIds  文件消息ID集合
	* @param[in] files 返回文件信息
	*/
	virtual void getFilesInfo(std::vector<int64> &fileMsgIds, std::map<int64, Fileinfo> &files) = 0;

	/**
	* \brief 判断是否有文件在传输
	* @param[in] localId  文件的local, 0代表判断是否存在任意文件在上传状态
	*/
	virtual bool isTransmitting(int64 localId = 0) = 0;

	/**
	* \brief 判断个人或群中是否有文件传输
	* @param[in] targetId  个人或群Id
	*/
	virtual bool isTransmittingInTarget(int64 targetId) = 0;

	/**
	* \brief 取消文件上传或下载
	* @param[in] localId 文件的localId
	* @param[in] type  1.上传 2.下载 3.外部下载
	*/
	virtual void cancelTransfer(int64 localId, int type, std::function<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 取消个人或群中的所有文件传输
	* @param[in] targetId人或群Id
	* @param[in] cb  _1 错误码
	*/
	virtual bool cancelTargetTransfer(int64 targetId) = 0;

	/**
	* \brief 取消所有文件传输
	*/
	virtual void cancelAllTransfer(std::function<void(ErrorInfo)> cb) = 0;
	/**
	*\brief 获取局域网可以P2P通讯的用户
	*@param[in] p2pUsers 用来接收获取的p2p用户 
	*@return 返回值 见errorExport.h p2p项
	*/
	virtual int  getP2pUsers(std::vector<model::p2pUser>& p2pUsers) = 0;
	/**
	* \brief 取消正在进行的传输或拒绝尚未开始的p2p传输
	* @param[in] cb  传入接受结果回掉 _1 错误信息 _2见packet.h
	*/
	virtual void  p2pTransferCancle(int64  taskID) = 0;
	/**
	 *\brief 获取本地文件已经下载大小
	 *@Param[in] localPath 本地文件路径
	 */
	virtual bool getAlreadyDownload(std::string&, downloadFileInfo&) = 0;

	/**
	*\brief 检查URL是否有效
	*@Param[in] url 要检查的url，如果为相对路径，下层会自己拼接为完整路径
	*/
	virtual void checkUrlValid(const std::string &url, std::function<void(ErrorInfo)> cb) = 0;

	/**
	*\brief //通过url获取名字 生成一个以年月文件夹名的前缀目录如'201704/name' 
	*@Param[in] url 服务器相对路径
	*/
	virtual std::string getNameByUrl(const std::string &url) = 0;
};

	
} /*namespace service*/