/***********************************************************************
* Module:  ServerInfo.h
* Author:  Administrator
* Modified: 2018��6��8�� 11:08:02
* Purpose: Declaration of the class ServerInfo
* Comment: ServerInfo��������˻�ȡ����������״̬����������Ϣ
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
	string getTransactionFee(); //��ȡĬ�Ϸ���
	string getInfo(); //��ȡ��������Ϣ
	string isConnected(); //�鿴����������
protected:
private:
private:
	Client client;
};
#endif