/*
 * IMUnkown.h
 *
 *  Created on: 2016年7月29日
 *      Author: sharp
 *  所有导出接口的基类
 */
#ifndef VRV_IMUNKOWN
#define VRV_IMUNKOWN

#include <memory>

///库的主要版本号
#define PSDK_VER    1  

#ifdef _WIN32
    #define  _CDECL_  __cdecl
#elif __linux__
    #define  _CDECL_  __attribute__((__cdecl__))
#elif __APPLE__
    #define  _CDECL_  __attribute__((__cdecl__))
#endif

///版本定义
#define INTERFACE_VERSION(cbMainVer,cbSubVer)								\
		(unsigned int)(														\
		(((unsigned char)(PSDK_VER))<<24)+								    \
		(((unsigned char)(cbMainVer))<<16)+								    \
		((unsigned char)(cbSubVer)<<8))

///获取库的主要版本号
inline unsigned char getProductVer(unsigned int nVersion)
{
	unsigned char * cbVersion=(unsigned char *)&nVersion;
	return cbVersion[3];
}

///获取主版本
inline unsigned char getMainVer(unsigned int nVersion)
{
	unsigned char * cbVersion = (unsigned char *)&nVersion;
	return cbVersion[2];
}

///获取子版本
inline unsigned char getSubVer(unsigned int nVersion)
{
	unsigned char * cbVersion=(unsigned char *)&nVersion;
	return cbVersion[1];
}

///接口版本对比
inline bool InterfaceVersionCheck(unsigned int nQueryVer, unsigned int nInterfaceVer)
{
	if (getMainVer(nQueryVer)!=getMainVer(nInterfaceVer)) return false;
	if (getSubVer(nQueryVer)>getSubVer(nInterfaceVer)) return false;
	return true;
}

///com 接口标识定义

struct VRVGUID 
{
    unsigned int   r1 ;   ///随机数
    unsigned short t1 ;   ///和时间相关
    unsigned short t2 ;   ///和时间相关
    unsigned char  cb[8]; ///MAC相关

	bool operator==(const VRVGUID &guid) const
	{
		if (r1 != guid.r1 || t1 != guid.t1 || t2 != guid.t2) return false;
		for (int i = 0; i < 8; ++i)
		{
			if (cb[i] != guid.cb[i])
				return false;
		}
		return true;
	}
};

typedef VRVGUID VRVIID;

#define VER_IMUNKNOW INTERFACE_VERSION(1,0)
static const VRVIID IID_IMUnknown = { 0x92d87e92, 0x46ab, 0x4465, 0x8d, 0xfd, 0x28, 0x1f, 0xe7, 0x45, 0xac, 0xb };

namespace service
{
	class IService;
}

///基础接口
class IMUnknown
{
	///接口查询
#ifdef _WIN32
	virtual std::shared_ptr<service::IService>  __stdcall queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __linux__
	virtual std::shared_ptr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __APPLE__
	virtual std::shared_ptr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#endif
};

#endif
