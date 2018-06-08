#include "Payment.h"
string Payment::PostPayment(MbedJSONValue& in, string sUrl, string sAddr, string otherInfo)
{
	string strRep = "";
	string strUrl = sUrl + sAddr + otherInfo;
	string strJson = in.serialize();
	client.http_post(strUrl, strJson, strRep);
	string content = client.get_content(strRep);
	return content;
}

bool Payment::SetJsonBody(MbedJSONValue& out, string secretIn, string src_accIn, string dst_accIn, string amt_In, string memtypeIn, string memdataIn)
{
	MbedJSONValue val;
	val["secret"] = secretIn;
	val["payment"]["source_account"] = src_accIn;
	val["payment"]["destination_account"] = dst_accIn;
	val["payment"]["amount"] = amt_In;
	val["payment"]["memos"][0]["MemoType"] = memtypeIn;
	val["payment"]["memos"][0]["MemoData"] = memdataIn;
	out = val;
	return true;
}

bool Payment::SetJsonBody(MbedJSONValue& out, string src_accIn, string dst_accIn, string direction, int start_ledger, int end_ledger, int per_page, int page)
{
	MbedJSONValue val;
	val["source_account"] = src_accIn;
	val["destination_account"] = dst_accIn;
	val["direction"] = direction;
	val["start_ledger"] = start_ledger;
	val["end_ledger"] = end_ledger;
	val["per_page"] = per_page;
	val["page"] = page;
	out = val;
	return true;
}

string Payment::GetPaymentInfo(string sUrl, string sAddr, string otherInfo)
{
	string strRep = "";
	if ( "" != sAddr)
	{
		sAddr.append("/");
	}
	string strUrl = sUrl + sAddr + otherInfo;
	client.http_get(strUrl, "", strRep);
	string content = client.get_content(strRep);
	return content;
}