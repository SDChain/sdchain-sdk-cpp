#include "Account.h"


Account::Account()
{
//	cout << "Account Construction...begin" << endl;
	this->id = "";
	this->alias = "";
	//this->tags = "{}";
	this->quorum = 1;
//	cout << "Account Construction...end" << endl;
}


Account::~Account()
{

}



string Account::getBalance(MbedJSONValue &in_out,string strWallet)
{
	//https://rest-beta.sdchain.io/v1/accounts/balances/6faLUhmp9gNgS9jXS3rAWbg8hFfi9PbWH5
	string strRep = "";
	//string strWallet = "69Hu8QsnEZUP4f3AVYSW7rkpLVm6DAEq9y";
	string strUrl = "/v1/accounts/balances/" + strWallet;
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	if (content.empty())
	{
		return "";
	}
	string err = getParseMbedJson(in_out, content.c_str());
	return "success";
}

string Account::newWallet(MbedJSONValue &in_out)
{
	//https://rest-beta.sdchain.io/v1/accounts/balances/6faLUhmp9gNgS9jXS3rAWbg8hFfi9PbWH5
	string strRep = "";
	string strUrl = "/v1/wallet/new";
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	if (content.empty())
	{
		return "";
	}
	string err = getParseMbedJson(in_out, content.c_str());
	return "success";
}

string Account::getParseMbedJson(MbedJSONValue& out, const char * pos)
{
	string err = parse(out, pos);
	return err;
}

bool Account::getRequestRet(MbedJSONValue& in)
{
	bool bRet = in["success"].get <bool>();
	return bRet;
}

string Account::getKeyValue(MbedJSONValue& in, string Key1, string Key2)
{ 
	string sValue = in[Key1][Key2].get<string>();
	return sValue;
}

int Account::getKeyValueInt(MbedJSONValue& in, string Key1, string Key2)
{
	int sValue = in[Key1][Key2].get<int>();
	return sValue;
}

double Account::getKeyValuedouble(MbedJSONValue& in, string Key1, string Key2)
{
	double sValue = in[Key1][Key2].get<double>();
	return sValue;
}

string Account::getKeyValue(MbedJSONValue& in, string Key1)
{
	string sValue = in[Key1].get<string>();
	return sValue;
}

bool Account::getKeyValueBool(MbedJSONValue& in, string Key1,string Key2)
{
	bool bRet = in[Key1][Key2].get <bool>();
	return bRet;
}

bool Account::getKeyValueBool(MbedJSONValue& in, string Key1)
{
	bool bRet = in[Key1].get <bool>();
	return bRet;
}
int Account::getLedger(MbedJSONValue& in)
{
	int iLedger = in["ledger"].get<int>();
	return iLedger;
}

int Account::getBalanceSize(MbedJSONValue& in,string Key1)
{
	int iCurrenciesNum = in[Key1].size();
	return iCurrenciesNum;
}

int Account::getBalanceSize(MbedJSONValue& in, string Key1,string Key2)
{
	int iCurrenciesNum = in[Key1][Key2].size();
	return iCurrenciesNum;
}
int Account::getBalanceSizeEx(MbedJSONValue& in, string Key1, string Key2,int i)
{
	int iCurrenciesNum = in[Key1][i][Key2].size();
	return iCurrenciesNum;
}

string Account::getBalanceArray_five(MbedJSONValue& in, string Key1, int i, string Key2,int j,string Key3)
{
	string sValue = in[Key1][i][Key2][j][Key3].get<string>();
	return sValue;
}
string Account::getBalanceArray(MbedJSONValue& in, string Key1, int i, string Key2)
{
	string sValue = in[Key1][i][Key2].get<string>();
	return sValue;
}

string Account::getBalanceArrayEx(MbedJSONValue& in, string Key1, string Key2, int i, string Key3)
{
	string sValue = in[Key1][i][Key2][Key3].get<string>();
	return sValue;
}

string Account::getBalanceArray(MbedJSONValue& in, string Key1, string Key2,int i,string Key3)
{
	string sValue = in[Key1][Key2][i][Key3].get<string>();
	return sValue;
}

string Account::getBalanceArray(MbedJSONValue& in, string Key1,string Key2, string Key3,int i,string Key4)
{
	string sValue = in[Key1][Key2][i][Key3][Key4].get<string>();
	return sValue;
}