/***********************************************************************
 * Module:  Account.h
 * Author:  Administrator
 * Modified: 2018��6��8�� 11:06:20
 * Purpose: Declaration of the class Account
 * Comment: �˻�
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
	string getParseMbedJson(MbedJSONValue& out, const char * pos);//ת����Mbedjson��ʽ
	bool getRequestRet(MbedJSONValue& in);//��ȡ���׳ɹ���־
	string getKeyValue(MbedJSONValue& in, string Key1, string Key2);//��ȡ��ֵ
	string getKeyValue(MbedJSONValue& in, string Key1);
	bool getKeyValueBool(MbedJSONValue& in, string Key1, string Key2);
	bool getKeyValueBool(MbedJSONValue& in, string Key1);
	int getKeyValueInt(MbedJSONValue& in, string Key1, string Key2);
	double getKeyValuedouble(MbedJSONValue& in, string Key1, string Key2);
	int getLedger(MbedJSONValue& in);//��ȡLedger����
	int getBalanceSize(MbedJSONValue& in,string Key1);//��ȡ�����������С
	int getBalanceSize(MbedJSONValue& in, string Key1,string Key2);
	int getBalanceSizeEx(MbedJSONValue& in, string Key1, string Key2, int i);
	string getBalanceArray(MbedJSONValue& in, string Key1, int i, string Key2);//��ȡ�������
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