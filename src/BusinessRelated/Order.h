/***********************************************************************
* Module:  Order.h
* Author:  Administrator
* Modified: 2018��6��8�� 11:08:02
* Purpose: Declaration of the class Order
* Comment: Order��������˶����������ϸ��Ϣ
***********************************************************************/
#if !defined(__Order_h)
#define __Order_h
#include <string>
#include "MbedJSONValue.h"
#include "Payment.h"
#include "Client.h"
using namespace std;
class Order :public Payment
{
public:
	bool SetJsonBody(MbedJSONValue& out, string secretIn, string typeIn, string currencypayIn, string cntpartypayIn, string valuepayIn, string currencygetIn, string cntpartygetIn, string valuegetIn);
	string PostOrder(MbedJSONValue& in, string sUrl, string sAddr, string sequence);
protected:
private:
private:
	Client client;
};
#endif