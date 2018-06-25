/***********************************************************************
* Module:  Payment.h
* Author:  Administrator
* Modified: 2018年6月8日 11:08:02
* Purpose: Declaration of the class Payment
* Comment: Payment对象包含了支付请求、获取支付详细信息
***********************************************************************/
#if !defined(__Account_Payment_h)
#define __Account_Payment_h
#include "Client.h"
#include <string>
#include "MbedJSONValue.h"
#include "Account.h"
using namespace std;
class Payment:public Account
{
public:
	string PostPayment(MbedJSONValue& in,string sUrl,string sAddr,string otherInfo);//支付请求
	bool SetJsonBody(MbedJSONValue& out, string src_accIn, string dst_accIn, string direction, int start_ledger, int end_ledger, int per_page, int page);
	bool SetJsonBody(MbedJSONValue& out,string secretIn,string src_accIn,string dst_accIn,string amt_In,string memtypeIn,string memdataIn);//组json包
	string GetPaymentInfo(string sUrl, string sAddr, string otherInfo);//获得支付信息
protected:
private:
	Client client;
};

#endif