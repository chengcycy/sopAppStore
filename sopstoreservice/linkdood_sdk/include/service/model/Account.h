#pragma once
#include <vector>
#include "User.h"

namespace model 
{
///账号信息
class Account : public User 
{
public:
	Account() :birthday(0)
	{}
	void init(){}
	
	bool operator == (const Account & rhs) const
	{
		return (birthday == rhs.birthday) && (nickId == rhs.nickId) &&
			(phone == rhs.phone) && (email == rhs.email) && (sign == rhs.sign) && (area == rhs.area) &&
			(phones == rhs.phones) && (emails == rhs.emails);
	}

public:
	Optional<int64> birthday;                 ///<生日
	Optional<std::string> nickId;			  ///<豆豆号
	Optional<std::string> phone;              ///<手机号
	Optional<std::string> email;              ///<邮箱号
	Optional<std::vector<std::string> > phones;   ///<手机号
	Optional<std::vector<std::string> > emails;   ///<邮箱号
	Optional<std::string> sign;               ///<签名
	Optional<std::string> area;              ///<地区
};

} /*namespace model */
