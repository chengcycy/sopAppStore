/*
* json_api_for_pc.h
*
*  Created on: 2016年04月07日
*      Author: corning
*/

#ifndef JSON_JSONTRANSTOOL_H_
#define JSON_JSONTRANSTOOL_H_

#include <config.h>
#include <string>
#include "../model/Msg.h"
#ifdef   SERVICE_EXPORTS
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllexport )
#else
#define SERVICE_API 
#endif
#else
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllimport )
#else
#define SERVICE_API 
#endif
#endif

namespace service
{
	/**
	* \brief 解析消息json
	* @param[in] type  消息类型  
	* @see jsonToolExport.h
	* @param[in] strIn 消息json串
	* @param[out] pOut  解析结果
	* @see jsonToolExport.h
	*/
SERVICE_API bool logic_jsonTransToStruct(uint16 type, std::string & strIn, void * pOut);
/**
* \brief 构造消息json
* @param[in] type  消息类型
* @see jsonToolExport.h
* @param[out] pOut  解析结果
* @see jsonToolExport.h
* @param[in] strIn 消息json串
*/

SERVICE_API bool logic_structTransToJson(uint16 type, void * pIn, std::string & strOut);


SERVICE_API std::shared_ptr<model::MsgText> toMsgText(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgVoice> toMsgVoice(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgVedio> toMsgVedio(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgAudio> toMsgAudio(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgPosition> toMsgPosition(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgImg> toMsgImg(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgFile> toMsgFile(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgCard> toMsgCard(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgTip> toMsgTip(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgWeb> toMsgWeb(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgRevoke> toMsgRevoke(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgDynExpression> toMsgDynExpression(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgPicWithText> toMsgPicWithText(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgTask> toMsgTask(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgDynExpression2> toMsgDynExpression2(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgMasterplate> toMsgMasterplate(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgMiniVedio> toMsgMsgMiniVedio(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgNineBlock> toMsgNineBlock(model::Msg *baseMsg);

SERVICE_API std::shared_ptr<model::MsgConference> toMsgConference(model::Msg *baseMsg);


}

#endif /* JSON_JSONTRANSTOOL_H_ */
