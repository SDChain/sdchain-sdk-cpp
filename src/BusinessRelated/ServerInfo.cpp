#include "ServerInfo.h"

string ServerInfo::getTransactionFee()
{
	string sUrl = "/v1/server/";
	string strRep = "";

	string strUrl = sUrl + "transaction-fee";
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}

string ServerInfo::getInfo()
{
	string sUrl = "/v1/server/";
	string strRep = "";

	string strUrl = sUrl + "server";
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}

string ServerInfo::isConnected()
{
	string sUrl = "/v1/server/";
	string strRep = "";

	string strUrl = sUrl + "connected";
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}