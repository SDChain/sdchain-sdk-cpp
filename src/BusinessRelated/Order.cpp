#include "Order.h"
bool Order::SetJsonBody(MbedJSONValue& out, string secretIn, string typeIn, string currencypayIn, string cntpartypayIn, string valuepayIn, string currencygetIn, string cntpartygetIn, string valuegetIn)
{
	MbedJSONValue val;
	val["secret"] = secretIn;
	val["order"]["type"] = typeIn;
	val["order"]["taker_pays"]["currency"] = currencypayIn;
	val["order"]["taker_pays"]["counterparty"] = cntpartypayIn;
	val["order"]["taker_pays"]["value"] = valuepayIn;
	val["order"]["taker_gets"]["currency"] = currencygetIn;
	val["order"]["taker_gets"]["counterparty"] = cntpartygetIn;
	val["order"]["taker_gets"]["value"] = valuegetIn;
	out = val;
	return true;
}

string Order::submitOrder(MbedJSONValue& in, string sUrl, string sAddr)
{
	string strRep = "";
	string strUrl = sUrl + sAddr;
	string strJson = in.serialize();
	client.http_post(strUrl, strJson, strRep);
	string content = client.get_content(strRep);
	return content;
}
	
string Order::getOrderList(string sAddr)
{
	string sUrl = "/v1/accounts/orders/";
	string strRep = "";
	if ( "" != sAddr)
	{
		sAddr.append("/");
	}
	string strUrl = sUrl + sAddr;
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}

string Order::getOrderInfo(string sAddr, string hash)
{
	string sUrl = "/v1/accounts/orders/";
	string strRep = "";
	if ( "" != sAddr)
	{
		sAddr.append("/");
	}
	string strUrl = sUrl + sAddr + hash;
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}

string Order::deleteOrder(string sAddr, string sequence)
{
	string sUrl = "/v1/accounts/orders/";
	string strRep = "";
	if ( "" != sAddr)
	{
		sAddr.append("/");
	}
	string strUrl = sUrl + sAddr + sequence;
	client.http_post_delete(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}