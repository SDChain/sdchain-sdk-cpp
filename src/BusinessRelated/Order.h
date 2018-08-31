/***********************************************************************
* Module:  Order.h
* Author:  Administrator
* Modified: 2018年6月8日 11:08:02
* Purpose: Declaration of the class Order
* Comment: Order对象包含了订单请求的详细信息
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
	string submitOrder(MbedJSONValue& in, string sUrl, string sAddr); //提交订单
	string getOrderList(string sAddr); //查看订单列表
	string getOrderInfo(string sAddr, string hash); //查看订单详情
	string deleteOrder(string sAddr, string sequence); //取消订单
protected:
private:
private:
	Client client;
};
#endif