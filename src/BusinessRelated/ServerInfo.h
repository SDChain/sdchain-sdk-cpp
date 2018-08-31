/***********************************************************************
* Module:  ServerInfo.h
* Author:  Administrator
* Modified: 2018年6月8日 11:08:02
* Purpose: Declaration of the class ServerInfo
* Comment: ServerInfo对象包含了获取服务器连接状态、服务器信息
***********************************************************************/
#if !defined(__ServerInfo_h)
#define __ServerInfo_h
#include <string>
#include "MbedJSONValue.h"
#include "Payment.h"
using namespace std;
class ServerInfo :public Payment
{
public:
	string getTransactionFee(); //获取默认费率
	string getInfo(); //获取服务器信息
	string isConnected(); //查看服务器连接
protected:
private:
private:
	Client client;
};
#endif