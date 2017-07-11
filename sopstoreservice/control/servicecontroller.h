#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H
#pragma once
#include "IMClient.h"
#include "IAuthService.h"
#include "IChatService.h"
#include "IContactService.h"
#include "IConfigService.h"
#include "IExtService.h"
#include "IFaceToFaceService.h"
#include "IGroupService.h"
#include "ISearchService.h"
#include "IUserService.h"
#include "ISysMsgService.h"
#include "IFileService.h"
#include "ISopStoreService.h"
#include "sopstorecmdExport.h"
extern std::shared_ptr<service::IMClient> g_client;
#define	SOPSERVICE	        SERVICE_GET(service::ISopStoreService,g_client,IID_ISopStoreService,VER_SOP);
#define	AUTHSERVICE	        SERVICE_GET(service::IAuthService,g_client,IID_IAuthSrvice,VER_IAUTH);
#define	CHATSERVICE	        SERVICE_GET(service::IChatService,g_client,IID_IChatService,VER_IChatService);
#define	CONTACTSERVICE	    SERVICE_GET(service::IContactService,g_client,IID_IContactService,VER_CONTACT);
#define	CONFIGSERVICE	    SERVICE_GET(service::IConfigService,g_client,IID_IConfigService,VER_CONFIG);
#define	USERSERVICE	        SERVICE_GET(service::IUserService,g_client,IID_IUserService,VER_USER);
#define	SEARCHSERVICE	    SERVICE_GET(service::ISearchService,g_client,IID_ISearchService,VER_SEARCH);
#define	GROUPSERVICE	    SERVICE_GET(service::IGroupService,g_client,IID_IGroupService,VER_GROUP);
#define	FILESERVICE	        SERVICE_GET(service::IFileService,g_client,IID_IFileService,VER_FILE);
#define	IEXTSERVICE	        SERVICE_GET(service::IExtService,g_client,IID_IExtService,VER_EXT);
#define	SYSMSGSERVICE	    SERVICE_GET(service::ISysMsgService,g_client,IID_ISysMsgService,VER_SYSMSG);

#endif // SERVICECONTROLLER_H
