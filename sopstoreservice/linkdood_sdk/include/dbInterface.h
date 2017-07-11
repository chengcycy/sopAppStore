/*
 * dbInterface.h
 *
 *  Created on: 2017年4月11日
 *
 */

#ifndef LOGICMGR_DBMGR_DBUTILS_DBINTERFACE_H_
#define LOGICMGR_DBMGR_DBUTILS_DBINTERFACE_H_
#include "config.h"

namespace imsdk {
typedef enum _SQLITE_DATATYPE
{
	 SQLITE_DATATYPE_INTEGER	= 	1,
	 SQLITE_DATATYPE_FLOAT,
	 SQLITE_DATATYPE_TEXT	,
	 SQLITE_DATATYPE_BLOB,
	 SQLITE_DATATYPE_NULL
} SQLITE_DATATYPE;

class IDbDataSet{
public:
	virtual bool isNull() = 0 ;
	///读取一行数据
	virtual bool read(void) = 0 ;
	///使用完成滞后释放数据集,一定要调用
	virtual void release(void) = 0 ;
	///获取数据集列数
	virtual int  columnCount(void)= 0 ;
	///获取列名
	virtual bool getColumnName(int column, char* columnName)= 0 ;
	///获取列数据类型
	virtual SQLITE_DATATYPE getColumnType(int column) = 0 ;
	///获取字符串列值
	virtual void getColumnValue(int column, char* value ) = 0 ;
	///获取字符串列值
	virtual void getColumnValue(int column, std::string& value) = 0 ;
	///获取整形列值
	virtual void getColumnValue(int column, int32& value) = 0 ;
	///获取16位整形列值
	virtual void getColumnValue(int column, int16& value) = 0 ;
	///获取8位整形列值
	virtual void getColumnValue(int column, int8& value) = 0 ;
	///获取64位整形列值
	virtual void getColumnValue(int column, int64& value) = 0 ;
	///获取双精度列值
	virtual void getColumnValue(int column, double& value)= 0 ;
	///获取二进制列值
	virtual const unsigned char* getBlobValue(int column, int& len)= 0 ;

	///获取字符串列值
	virtual void getColumnValue(const char * pcolName, char* value ) = 0 ;
	///获取字符串列值
	virtual void getColumnValue(const char * pcolName, std::string& value) = 0 ;
	///获取整形列值
	virtual void getColumnValue(const char * pcolName, int32& value) = 0 ;
	///获取16位整形列值
	virtual void getColumnValue(const char * pcolName, int16& value) = 0 ;
	///获取8位整形列值
	virtual void getColumnValue(const char * pcolName, int8& value) = 0 ;
	///获取64位整形列值
	virtual void getColumnValue(const char * pcolName, int64& value) = 0 ;
	///获取双精度列值
	virtual void getColumnValue(const char * pcolName, double& value)= 0 ;
	virtual const unsigned char* getBlobValue(const char * pcolName, int& len)= 0 ;
	
};

/**
 * 预编译命令
 */
class IDbCommand {
public:
	///绑定字符串
	virtual bool bindParam(int index, const char* value) = 0;
	///绑定３２位整数
	virtual bool bindParam(int index, const int32 value)= 0;
	///绑定６４位整数
	virtual bool bindParam(int index, const int64 value)= 0;
	///绑定双精度
	virtual bool bindParam(int index, const double value)= 0;
	///绑定二进制数据
	virtual bool bindParam(int index, unsigned char* value, const int len)= 0;
	///执行
	virtual bool excute(void)= 0;
	///释放, 必须调用
	virtual void release() = 0 ;
};

class dbInterface
{
public:
	/**
	 * 打开路径
	 * path　　　数据库文件路径
	 * key    数据库密钥　ＮＵＬＬ　不加密
	 */
	virtual bool  openDb(const char* path, const char* key = 0) = 0 ;
	///数据库是否打开
	virtual bool  isOpen() = 0 ;
	///关闭数据库
	virtual void  close(void) = 0 ;
	///执行ＳＱＬ不返回数据集
	virtual bool  excuteNonQuery(const char* sql) = 0 ;
	///执行ＳＱＬ，通过pSet返回数据集
	virtual bool  excute(const char* sql,IDbDataSet ** pSet) = 0 ;
	///打开事务
	virtual bool  beginTransaction(void) = 0 ;
	///关闭事务
	virtual bool  commitTransaction(void) = 0 ;
	///回滚
	virtual bool  rollbackTransaction(void) = 0 ;
	///判断表是否存在 1存在，0不存在 -1失败
	virtual int   isExistTable(std::string & tblName) = 0 ;
	///预编译ＳＱＬ
	virtual bool  getSqlHanlder(const char * pSql,IDbCommand ** pCmd) =  0;
};

////导出函数
//创建数据库接口
IMSDK_EXPORT_API  dbInterface * createDbInterface();
///释放数据库
IMSDK_EXPORT_API  void cleanDBInterface(dbInterface * db);
}

#endif /* LOGICMGR_DBMGR_DBUTILS_DBINTERFACE_H_ */
