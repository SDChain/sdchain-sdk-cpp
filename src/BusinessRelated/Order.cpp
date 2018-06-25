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

string Order::PostOrder(MbedJSONValue& in, string sUrl, string sAddr, string sequence)
{
	string strRep = "";
	string strUrl = sUrl + sAddr + sequence;
	string strJson = in.serialize();
	client.http_post_delete(strUrl, strJson, strRep);
	string content = client.get_content(strRep);
	return content;
}