/*
 * sopstorecmdExport.h
 *
 *  Created on: 2017年03月27日
 *      Author: corning
 */

#ifndef SOPSTORECMDEXPORT_H_
#define SOPSTORECMDEXPORT_H_

#include <string>
#include <vector>
#include <map>
#include <config.h>
#include <cmdExport.h>

using namespace imsdk;

/**
 * 消息枚举类型
 * sdk开发人员加入新的数据结构后，需要同时更新cmdMemger类里面的实现
 */
namespace imsdksopstore {

	/**
	 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
	 * ** [in] 标识输入参数
	 * ** [out] 标识返回参数
	 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
	 */
	enum {

	    /// [in] req_qAppStoreS 	[out] resp_qAppStoreS
        sopstore_logic_cmd_qAppStoreS = 14001,                          ///

        /// [in] req_qEnOS 	[out] resp_qEnOS
        sopstore_logic_cmd_qEnOS = 14002,                               ///

        /// [in] req_getUsersByParam 	[out] resp_getUsersByParam
        sopstore_logic_cmd_getUsersByParam = 14003,                     ///

        sopstore_logic_cmd_max,	                                        /// 最大的命令标识，标识命令个数，无特殊业务意义
	};

    /// =========================================================================================

    /// 结果
    struct Result {
        Result() :
            code(0),
            result(0) {}

        int32	    code;           ///< 是否处理成功
        std::string message;        ///< 失败原因
        int64       result;         ///< 处理的结果
    };

	/// 应用实体
    struct AppInfoBean {
        AppInfoBean() :
            id(0),
            classify(0),
            type(0),
            status(0),
            createUserID(0),
            createUnitID(0),
            sort(0) {}

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
        int64 createUnitID;         ///< 创建者所属单位ID
	};

    /// 应用分类实体
    struct AppClassifyBean {
        AppClassifyBean() :
            classifyID(0),
            createUserID(0),
            classifyStatus(0),
            classifyType(0),
            classifySort(0) {}

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
        /**
         * 分类类型
         * 1:内置分类-不可操作,服务应用服务启动初始化进数据库,分类优先排序
         * 2:其他分类-管理员创建的分类,可维护,排序在内置分类后
         */
        int32 classifyType;
    };

    /// 要闻热点实体
    struct HotNewsBean {
        HotNewsBean() :
            id(0),
            createUserID(0),
            newsSort(0) {}

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
        AppRelationBean() :
            id(0),
            userID(0),
            appID(0),
            classifyID(0),
            relationStatus(0),
            sort(0) {}

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
	
	/// 客户端统计接口
	struct AppStatisticsBean {
		std::string appType;		///< 应用类型: 1.门户应用类型 2.普通应用类型
		std::string appID;			///< 应用ID
		std::string userID;			///< 用户ID
		std::string orgID;			///< 组织机构ID
		std::string orgCode;		///< 组织机构CODE
		std::string unitID;			///< 组织机构CODE
	};
	
	/// 应用统计结果实体
	struct AppStatisticsResult {
		std::string msg;			///< 结果描述
		std::string code;			///< 结果码
	};
	
    /// 我的应用信息
    struct MyAppInfo {
        MyAppInfo() :
            code(0) {
                appInfoList.clear();
            }

        AppClassifyBean appClassify;            ///< 应用分类
        std::vector<AppInfoBean> appInfoList;   ///< 应用集合
        int64 code;                             ///< 响应码
        std::string msg;                        ///< 响应码描述语
    };

    /// 应用商店
    struct AppStore {
        AppStore() :
            pageSize(0),
            pageNum(0),
            totalCount(0),
            totalPage(0),
            code(0) {
                appInfoList.clear();
            }

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
        AppStoreQueryParam() :
            userId(0),
            appClassifyId(0),
            pageSize(0),
            searchType(0),
            pageNum(0) {}

        std::string appName;                    ///< 应用名称
        int64       userId;                     ///< 应用类型
        int64       appClassifyId;              ///< id
        int64       pageSize;                   ///< 每页显示的条数
        int64       pageNum;                    ///< 当前页数
        int32       searchType;                 ///< 搜索类型(1:我的应用搜索, 2:应用商店搜索)
    };

    struct EnterpriseUserBean {
        EnterpriseUserBean() :
            userID(0),
            enterpriseID(0),
            orgID(0),
            roleID(0),
            status(0),
            orderNum(0),
            newOrgID(0),
            bizStatus(0) {}

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

    struct OrgUserAndChildNodes {
        OrgUserAndChildNodes() :
            code(0) {
                users.clear();
                obeans.clear();
            }

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
        OrgSearchResult() {
            uBeans.clear();
        }

        std::vector<EnterpriseUserBean> uBeans;
        std::string resultFlag;
    };

    struct YMD {
        YMD() :
            year(0),
            month(0),
            day(0) {}

        int16 year;                 // 0 不被使用
        int8 month;                 // 从1开始
        int8 day;                   // 从1开始
    };

    struct AccountType {
        AccountType() :
            type(0) {}

        int8 type;                  // 账号类型 1：电话, 3：邮箱, 4：userID, 5:身份证, 6：豆豆号, 7:自定义帐号(不做限制)
        std::string accounts;       // 账号
        std::string mark;           // 标识
    };

    struct UserBean {
        UserBean() :
            userID(0),
            userType(0),
            sex(0),
            qqNum(0),
            status(0),
            timeZone(0),
            lockDeadline(0),
            remainLockDuration(0),
            SDKID(0),
            regFlag(0),
            pwdStrength(0),
            roleID(0),
            bizStatus(0),
            uploadFlag(0),
            oldStatus(0) {
                phoneNums.clear();
                emails.clear();
                accounts.clear();
            }

        int64 userID;               /*用户ID*/
        std::string phoneNum;       /*可以删除 */
        std::string email;          /*可以删除 */
        int16 userType;             /*目前没有意义*/
        std::string name;           /*用户名 */
        std::string pwd;            /*用户密码 */
        int8 sex;                   /* 性别*/
        std::string area;           /*区域 */
        YMD birthday;               /*生日*/
        std::string school;         /*毕业学校*/
        int64 qqNum;                /*可以删除*/
        std::string maccode;        /*目前无意义*/
        int8 status;                /*用户状态 1：正常 2：停用 3: 注册邀请4: 影子用户，5:锁定，6:冻结*/
        std::string portraitURL;    /*头像地址*/
        std::string sign;           /*签名*/
        int8 timeZone;              /*时区*/
        std::vector<std::string> phoneNums; /*电话号码清单*/
        std::vector<std::string> emails;    /*邮箱清单 */
        std::string oriPortraitURL;         /*原始头像地址*/
        std::string idcard;                 /*可以删除*/
        std::string accountName;            /*账号名称*/
        std::string extend;                 /*扩展信息*/
        int64 lockDeadline;                 /*锁定截止时间，毫秒*/
        int64 remainLockDuration;           /*剩余锁定时长，毫秒*/
        int64 SDKID;                        /*SDKID*/
        std::string entExtend;              /*企业扩展信息*/
        std::vector<AccountType> accounts;  /*联系方式集合 */
        int8 regFlag;                       /*注册标识0为更新1为注册 */
        int8 pwdStrength;                   /*密码强度:1:弱,2:中,3:强*/
        std::string orgID;                  /*组织结构id,多个用逗号分隔*/
        int64 roleID;                       /*角色ID*/
        int8 bizStatus;                     /*业务状态，1：初始默认，2：在高管层*/
        int8 uploadFlag;                    /*上传标识, 1:未上传,2:已上传,3:已忽略*/
        int8 oldStatus;                     /*保存冻结之前用户状态status的值*/
    };

	/// =========================================================================================

    /*
    type 类型
    1.查询我的应用列表
    参数：无
    返回：code 0,成功
    appInfos

    2.查询应用商店列表---根据应用发布范围(用户所属组织的在发布范围内的)
    参数：appStoreQueryParam
    返回：code 0,成功
    appStores

    3.模糊查询
    参数：appStoreQueryParam
    模糊查询我的应用列表时appName，userId为必传参数
    模糊查询应用商店列表时appName为必传参数
    模糊查询应用列表无分页
    返回：code 0,成功
    appBeans
    4.应用分类列表
    参数：无
    返回：code 0,成功
    classifyBeans
    5.要闻热点列表
    参数：无
    返回：code 0,成功
    hotNewsBeans
    6.添加我的应用
    参数：appRelation
    返回：code 0,成功
    ret
    7.删除我的应用
    参数：appID
    返回：code 0,成功
    ret
    */
    struct req_qAppStoreS : public _sdkcmd_base {
        req_qAppStoreS() :
            value64(0),
            type(0) {}

        int8 type;
        AppStoreQueryParam appStoreQueryParam;
        AppRelationBean appRelation;
        int64 value64;
		AppStatisticsBean appStatic;
		CMD_SIZE();
	};

    struct resp_qAppStoreS : public _sdkrespcmd_base {
        resp_qAppStoreS() :
            code(0) {
                appInfos.clear();
                appBeans.clear();
                classifyBeans.clear();
                hotNewsBeans.clear();
            }

        int32 code;
        std::string what;
        std::vector<MyAppInfo> appInfos;
        AppStore appStore;
        std::vector<AppInfoBean> appBeans;
        std::vector<AppClassifyBean> classifyBeans;
        std::vector<HotNewsBean> hotNewsBeans;
        Result ret;
		AppStatisticsResult StatisResult;
		CMD_SIZE();
        COPY_OTHER(resp_qAppStoreS);
	};

    /*
    type 类型

    3.CASIC定制接口，客户端在组织架构下输入用户名称进行搜索,可以选择指定组织
    参数：map<string, string> params
    1: unitID	用户所在单位ID
    2: name		搜索的名称
    3: pageSize	每页记录数
    4: pageNum	当前页数
    返回：code 0,成功
    entUsers

    4.CASIC定制接口，根据单位id获取部门信息
    参数：value64    enterpriseID 企业ID
    value64_2  orgID 组织机构ID
    返回：
    */
    struct req_qEnOS : public _sdkcmd_base {
        req_qEnOS() :
            type(0),
            value64(0),
            value64_2(0),
            value64_3(0) {
                list_i64.clear();
                params.clear();
            }

        int8 type;
        int64 value64;
        int64 value64_2;
        int64 value64_3;
        std::string valuestr;
        std::vector<int64> list_i64;
        std::map<std::string, std::string> params;
        CMD_SIZE();
    };

    struct resp_qEnOS : public _sdkrespcmd_base {
        resp_qEnOS() :
            code(0) {
                orgSearchUsers.clear();
                entUsers.clear();
            }

        int32 code;
        std::string what;
        OrgUserAndChildNodes nodes;
        std::vector<OrgSearchUserRet> orgSearchUsers;
        OrgSearchResult searchRet;
        std::vector<EnterpriseUserBean> entUsers;
        std::vector<OrganizationBean> depts;
        CMD_SIZE();
        COPY_OTHER(resp_qEnOS);
    };

    struct req_getUsersByParam : public _sdkcmd_base {
        req_getUsersByParam() {
            userParam.clear();
        }

        std::map<std::string, std::string> userParam;
        CMD_SIZE();
    };

    struct resp_getUsersByParam : public _sdkrespcmd_base {
        resp_getUsersByParam() :
            code(0) {
                bean.clear();
            }

        int32 code;
        std::string what;
        std::vector<UserBean> bean;
        CMD_SIZE();
        COPY_OTHER(resp_getUsersByParam);
    };
}

#endif