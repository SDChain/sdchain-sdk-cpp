/***********************************************************************
 * Module:  Account.h
 * Author:  Administrator
 * Modified: 2018年6月8日 11:06:20
 * Purpose: Declaration of the class Account
 * Comment: 账户
 ***********************************************************************/

#if !defined(__Account_Account_h)
#define __Account_Account_h
#include <string>
#include <map>
#include "Client.h"
#include "MbedJSONValue.h"
using namespace std;

class Account
{
public:
	Account();
	~Account();

	std::string id;
	std::string alias;
	int quorum;

	//void setId(const string newId){this->id = newId;};
	//string getId(){return this->id;};

	//void setAlias(const string newAlias){this->alias = newAlias;};
	//string getAlias(){return this->alias;};

	//void setQuorum(int newQuorum){this->quorum = newQuorum;};
	//int getQuorum(){return this->quorum;};

	string getBalance(MbedJSONValue &in_out,string strWallet);
	string  newWallet(MbedJSONValue &in_out);

	//string createAccount();
	//string listAccounts();
	string getParseMbedJson(MbedJSONValue& out, const char * pos);//转换成Mbedjson格式
	bool getRequestRet(MbedJSONValue& in);//获取交易成功标志
	string getKeyValue(MbedJSONValue& in, string Key1, string Key2);//获取键值
	string getKeyValue(MbedJSONValue& in, string Key1);
	bool getKeyValueBool(MbedJSONValue& in, string Key1, string Key2);
	bool getKeyValueBool(MbedJSONValue& in, string Key1);
	int getKeyValueInt(MbedJSONValue& in, string Key1, string Key2);
	double getKeyValuedouble(MbedJSONValue& in, string Key1, string Key2);
	int getLedger(MbedJSONValue& in);//获取Ledger长度
	int getBalanceSize(MbedJSONValue& in,string Key1);//获取余额对象数组大小
	int getBalanceSize(MbedJSONValue& in, string Key1,string Key2);
	int getBalanceSizeEx(MbedJSONValue& in, string Key1, string Key2, int i);
	string getBalanceArray(MbedJSONValue& in, string Key1, int i, string Key2);//获取余额数据
	string getBalanceArray(MbedJSONValue& in, string Key1, string Key2, int i, string Key3);
	string getBalanceArray(MbedJSONValue& in, string Key1, string Key2, string Key3, int i, string Key4);
	string getBalanceArrayEx(MbedJSONValue& in, string Key1, string Key2, int i, string Key3);
	string getBalanceArray_five(MbedJSONValue& in, string Key1, int i, string Key2, int j, string Key3);
protected:
private:
	Client client;
	MbedJSONValue m_valTags;

};

#endif