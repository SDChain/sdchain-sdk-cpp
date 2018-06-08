#include <WINSOCK2.H>  
//#include <stdio.h>  
#include <iostream>  
#include <string>  
#include "Account.h"
#include "conio.h"  //for getch
#include "MbedJSONValue.h"
#include "Payment.h"
#include "ServerInfo.h"
#include "Order.h"
#pragma comment(lib, "ws2_32.lib")  

using namespace std;  
int sd_account()
{
	string strWallet = "6h7oPUgcK38FjDftnKbkdFwXnPPP7CipTr";
	Account act;
	MbedJSONValue objJson;
	string strRet = act.getBalance(objJson,strWallet);
	if (strRet.empty())
	{
		return -1;
	}
	bool bSuccess = act.getRequestRet(objJson);
	if (bSuccess)
	{
		int iLedger = act.getLedger(objJson);
		bool bSuccess = act.getRequestRet(objJson);
		int iCurrenciesNum = act.getBalanceSize(objJson, "balances");
		for (int i = 0; i < iCurrenciesNum; i++)
		{
			string value = act.getBalanceArray(objJson, "balances", i, "value");
			string currency = act.getBalanceArray(objJson, "balances", i, "currency");
			string counterparty = act.getBalanceArray(objJson, "balances", i, "counterparty");
			cout << "第" << i << "条记录:" << endl << "value:" << value << endl << "currency:" << currency << endl
				<< "counterparty:" << counterparty << endl;
		}
	}
	return 0;
}

int sd_wallet()
{
	MbedJSONValue mJson;
	Account act;
	string strRet = act.getWallet(mJson);
	if (strRet.empty())
	{
		return -1;
	}
	bool bSuccess = act.getRequestRet(mJson);
	if (bSuccess)
	{
		string address1 = act.getKeyValue(mJson, "wallet", "address");
		string secret1 = act.getKeyValue(mJson, "wallet", "secret");
		cout << "address:" << address1 << endl << "secret:" << secret1 << endl;
	}
	return 0;
}

string sd_postpayment()//支付请求
{
	string strJson = "";
	Payment pay;
	MbedJSONValue mbJson;
	MbedJSONValue objJson;
	string secret = "sh7dqVn8mhg6BqGfAQyaYVUwK2zkR";
	string src_acc = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string dst_acc = "69Hu8QsnEZUP4f3AVYSW7rkpLVm6DAEq9y";
	string amount = "666";
	string MemoType = "memos";
	string MemoData = "Transaction from ARM mbed OS";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string strUrl = "/v1/accounts/payments/";
	pay.SetJsonBody(mbJson, secret, src_acc, dst_acc, amount, MemoType, MemoData);
	strJson = pay.PostPayment(mbJson, strUrl, strWallet,"");
	if (strJson.empty())
	{
		return "error";
	}
	string err = pay.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = pay.getRequestRet(objJson);
	if (bSuccess)
	{
		string hash = pay.getKeyValue(objJson, "hash");
		string status_url = pay.getKeyValue(objJson, "status_url");
		cout << "hash:" << hash << endl;
		cout << "status_url:" << status_url << endl;
		return hash;
	}
	return "error";
}

string sd_getpaymentinfo(string hash)
{
	Payment pay;
	MbedJSONValue objJson;
	string strJson = "";
	string strWallet = "69Hu8QsnEZUP4f3AVYSW7rkpLVm6DAEq9y";
	string strUrl = "/v1/accounts/payments/";
	//string strHash = "EF252979355F2666486F69E9C96D137265214DE65B14E1136ECCDCE84F09AD11";
	string strHash = hash;
	strJson = pay.GetPaymentInfo(strUrl, strWallet, strHash);
	if (strJson.empty())
	{
		return "error";
	}
	string err = pay.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = pay.getRequestRet(objJson);
	if (bSuccess)
	{
		string hash = pay.getKeyValue(objJson, "hash");
		string ledger = pay.getKeyValue(objJson, "ledger");
		string state = pay.getKeyValue(objJson, "state");
		string source_account = pay.getKeyValue(objJson, "source_account");
		string dst_account = pay.getKeyValue(objJson, "destination_account");
		string amount_cur = pay.getKeyValue(objJson, "amount", "currency");
		string value = pay.getKeyValue(objJson, "amount", "value");
		string amount_issuer = pay.getKeyValue(objJson, "amount", "issuer");
		string currency = pay.getKeyValue(objJson, "currency");
		string issuer = pay.getKeyValue(objJson, "issuer");
		string direction = pay.getKeyValue(objJson, "direction");
		string timestamp = pay.getKeyValue(objJson, "timestamp");
		string fee = pay.getKeyValue(objJson, "fee");
		cout << "hash:" << hash << " ledger:" << ledger << " state:" << state
			<< " source_account:" << source_account << " dst_account:" << dst_account
			<< " amount_cur:" << amount_cur << " value:" << value << " amount_issuer:" << amount_issuer
			<< " currency:" << currency << " issuer" << issuer << " direction" << direction
			<< " timestamp:" << timestamp << " fee" << fee;
		int iCurrenciesNum = pay.getBalanceSize(objJson, "memos");
		for (int i = 0; i < iCurrenciesNum; i++)
		{
			string memo_type = pay.getBalanceArray(objJson, "memos", i, "memo_type");
			string memo_data = pay.getBalanceArray(objJson, "memos", i, "memo_data");
			cout << i << ":" << memo_type << "--" << memo_data << endl;
		}

		return hash;
		
	}
	return "";
}

int sd_gettransactions(string tx_hash)
{
	Payment pay;
	MbedJSONValue objJson;
	string strJson = "";
	string strHash = "EF252979355F2666486F69E9C96D137265214DE65B14E1136ECCDCE84F09AD11";
	strHash = tx_hash;
	string strUrl = "/v1/transactions/";
	strJson = pay.GetPaymentInfo(strUrl,"", strHash);
	if (strJson.empty())
	{
		return -1;
	}
	string err = pay.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = pay.getRequestRet(objJson);
	if (bSuccess)
	{
		string TransactionType = pay.getKeyValue(objJson, "transaction", "TransactionType");
		int Flags = pay.getKeyValueInt(objJson, "transaction", "Flags");
		int Sequence = pay.getKeyValueInt(objJson, "transaction", "Sequence");
		int LastLedgerSequence = pay.getKeyValueInt(objJson, "transaction", "LastLedgerSequence");
		string Amount = pay.getKeyValue(objJson, "transaction", "Amount");
		string Fee = pay.getKeyValue(objJson, "transaction", "Fee");
		string SigningPubKey = pay.getKeyValue(objJson, "transaction", "SigningPubKey");
		string TxnSignature = pay.getKeyValue(objJson, "transaction", "TxnSignature");
		string Account = pay.getKeyValue(objJson, "transaction", "Account");
		string Destination = pay.getKeyValue(objJson, "transaction", "Destination");
		int iCurrenciesNum = pay.getBalanceSize(objJson,"transaction","Memos");
 		for (int i = 0; i < iCurrenciesNum; i++)
		{
			string MemoType = pay.getBalanceArray(objJson, "transaction", "Memos", "Memo", i,"MemoType");
 			string MemoData = pay.getBalanceArray(objJson, "transaction", "Memos", "Memo", i, "MemoData");
 			string parsed_memo_type = pay.getBalanceArray(objJson, "transaction", "Memos", "Memo", i, "parsed_memo_type");
 			cout << i << ":" << MemoType << "--" << MemoData << "--" << parsed_memo_type << endl;
 		}
		int date = pay.getKeyValueInt(objJson, "transaction", "date");
		string hash = pay.getKeyValue(objJson, "transaction", "hash");
		int inLedger = pay.getKeyValueInt(objJson, "transaction", "inLedger");
		int ledger_index = pay.getKeyValueInt(objJson, "transaction", "ledger_index");
		bool validated = pay.getKeyValueBool(objJson, "transaction", "validated");

	}
	return 0;
}

int sd_getpaymenthistory()
{
	Payment pay;
	MbedJSONValue objJson;
	MbedJSONValue mbJson;
	string strJson = "";
	string strUrl = "/v1/accounts/payments/";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string src_acc = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string dst_acc = "69Hu8QsnEZUP4f3AVYSW7rkpLVm6DAEq9y";
	string direction = "incoming";
	int start_ledger = 1;
	int end_ledger = 10000;
	int per_page = 10;
	int page = 1;
	pay.SetJsonBody(mbJson, src_acc, dst_acc, direction, start_ledger, end_ledger, per_page, page);
	strJson = pay.PostPayment(mbJson, strUrl, strWallet, "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = pay.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = pay.getRequestRet(objJson);
	if (bSuccess)
	{
		int iCurrenciesNum = pay.getBalanceSize(objJson,"payments");
		for (int i = 0; i < iCurrenciesNum; i++)
		{
			string hash = pay.getBalanceArray(objJson, "payments", i, "hash");
			string ledger = pay.getBalanceArray(objJson, "payments", i, "ledger");
			string source_account = pay.getBalanceArray(objJson, "payments", i, "source_account");
			string destination_account = pay.getBalanceArray(objJson, "payments", i, "destination_account");
			string currency = pay.getBalanceArrayEx(objJson, "payments", "amount", i,"currency");
			string value = pay.getBalanceArrayEx(objJson, "payments", "amount", i, "value");
			string issuer = pay.getBalanceArrayEx(objJson, "payments", "amount", i, "issuer");
			string direction = pay.getBalanceArray(objJson, "payments", i, "direction");
			string timestamp = pay.getBalanceArray(objJson, "payments", i, "timestamp");
			string fee = pay.getBalanceArray(objJson, "payments", i, "fee");
			int iCurrenciesNum = pay.getBalanceSizeEx(objJson, "payments", "Memos",i);
			for (int j = 0; j < iCurrenciesNum; j++)
			{
				string memo_type = pay.getBalanceArray_five(objJson, "payments", j,"memos", i, "memo_type");
				string memo_data = pay.getBalanceArray_five(objJson, "payments",j, "memos", i, "memo_data");
				cout << i << ":" << memo_type << "--" << memo_data << endl;
			}
		}
	}
	return 0;
}

int sd_getdefaultfee()
{
	ServerInfo serInfo;
	MbedJSONValue objJson;
	string strJson = "";
	string strUrl = "/v1/transaction-fee";
	strJson = serInfo.GetPaymentInfo(strUrl, "", "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = serInfo.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = serInfo.getRequestRet(objJson);
	if (bSuccess)
	{
		string fee = serInfo.getKeyValue(objJson, "fee");
		cout << "fee:" << fee << endl;
	}
	return 0;
}

int sd_getserverinfo()
{
	ServerInfo serInfo;
	MbedJSONValue objJson;
	string strJson = "";
	string strUrl = "/v1/server";
	strJson = serInfo.GetPaymentInfo(strUrl, "", "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = serInfo.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = serInfo.getRequestRet(objJson);
	if (bSuccess)
	{
		string complete_ledgers = serInfo.getKeyValue(objJson, "sdchaind_server_status", "complete_ledgers");
		string server_state = serInfo.getKeyValue(objJson, "sdchaind_server_status", "server_state");
		int reserve_base_sda = serInfo.getKeyValueInt(objJson, "sdchaind_server_status", "reserve_base_sda");
		cout << "complete_ledgers:" << complete_ledgers << "server_state:" << server_state << "reserve_base_sda:" << reserve_base_sda << endl;
	}
	return 0;
}

int sd_getserverconnected()
{
	ServerInfo serInfo;
	MbedJSONValue objJson;
	string strJson = "";
	string strUrl = "/v1/server/connected";
	strJson = serInfo.GetPaymentInfo(strUrl, "", "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = serInfo.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = serInfo.getRequestRet(objJson);
	if (bSuccess)
	{
		bool connected = serInfo.getKeyValueBool(objJson, "connected");
	}
	return 0;
}

int sd_queryorderlist()
{
	Order orderInfo;
	MbedJSONValue objJson;
	string strJson = "";
	string strUrl = "/v1/accounts/orders/";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	strJson = orderInfo.GetPaymentInfo(strUrl, strWallet, "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = orderInfo.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = orderInfo.getRequestRet(objJson);
	if (bSuccess)
	{
		int  ledger = objJson["ledger"].get<int>();
		bool validated = orderInfo.getKeyValueBool(objJson, "validated");
		int iCurrenciesNum = orderInfo.getBalanceSize(objJson, "orders");
		for (int i = 0; i < iCurrenciesNum; i++)
		{
			string type = orderInfo.getBalanceArray(objJson, "orders", i, "type");
			string currency_gets = orderInfo.getBalanceArray(objJson, "orders","taker_gets",i,"currency");
			string value_gets = orderInfo.getBalanceArray(objJson, "orders", "taker_gets", i, "value");
			string counterparty_gets = orderInfo.getBalanceArray(objJson, "orders", "taker_gets", i, "counterparty");
			string currency_pays = orderInfo.getBalanceArray(objJson, "orders", "taker_pays", i, "currency");
			string value_pays = orderInfo.getBalanceArray(objJson, "orders", "taker_pays", i, "value");
			string counterparty_pays = orderInfo.getBalanceArray(objJson, "orders", "taker_pays", i, "counterparty");
			cout << "type:" << type << "currency_gets:" << currency_gets << "value_gets:" << value_gets
				<< "counterparty_gets:" << counterparty_gets << "currency_pays:" << currency_pays
				<< "value_pays:" << value_pays << "counterparty_pays:" << counterparty_pays << endl;
		}
		cout << "ledger:" << ledger << "validated:" << validated << endl;
	}
	return 0;
}

int sd_commitorder()
{
	Order orderCommit;
	MbedJSONValue objJson;
	MbedJSONValue mbJson;
	string strJson = "";
	string strUrl = "/v1/accounts/orders/";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string secret = "sh7dqVn8mhg6BqGfAQyaYVUwK2zkR";
	orderCommit.SetJsonBody(mbJson, secret, "buy", "SDA", "", "4", "CNY", "6UPd52jHtu1d88nc3S3WeroACFQpKfybhU", "22");
	strJson = orderCommit.PostPayment(mbJson, strUrl, strWallet, "");
	if (strJson.empty())
	{
		return -1;
	}
	string err = orderCommit.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = orderCommit.getRequestRet(objJson);
	if (bSuccess)
	{
		string account = orderCommit.getKeyValue(objJson, "order", "account");
		string currency_g = orderCommit.getKeyValue(objJson, "taker_gets", "currency");
		string value_g = orderCommit.getKeyValue(objJson, "taker_gets", "value");
		string counterparty_g = orderCommit.getKeyValue(objJson, "taker_gets", "counterparty");
		string currency_p = orderCommit.getKeyValue(objJson, "taker_pays", "currency");
		string value_p = orderCommit.getKeyValue(objJson, "taker_pays", "value");
		string counterparty_p = orderCommit.getKeyValue(objJson, "taker_pays", "counterparty");
		string fee = orderCommit.getKeyValue(objJson, "order", "fee");
		string type = orderCommit.getKeyValue(objJson, "order", "type");
		int sequence = orderCommit.getKeyValueInt(objJson, "order","sequence");
		string hash = orderCommit.getKeyValue(objJson, "hash");
		int ledger = orderCommit.getLedger(objJson);
		string state = orderCommit.getKeyValue(objJson, "state");
	}
	return 0;
}

int sd_deleteorder()
{
	Order orderCommit;
	MbedJSONValue objJson;
	MbedJSONValue mbJson;
	MbedJSONValue val;
	string strJson = "";
	string strUrl = "/v1/accounts/orders/";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string strNum = "1234";
	val["secret"] = "sh7dqVn8mhg6BqGfAQyaYVUwK2zkR";
	strJson = orderCommit.PostOrder(val, strUrl, strWallet, strNum);
	if (strJson.empty())
	{
		return -1;
	}
	string err = orderCommit.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = orderCommit.getRequestRet(objJson);
	if (bSuccess)
	{
		string account = orderCommit.getKeyValue(objJson, "order", "account");
		string fee = orderCommit.getKeyValue(objJson, "order", "fee");
		string offer_sequence = orderCommit.getKeyValue(objJson, "order", "offer_sequence");
		string sequence = orderCommit.getKeyValue(objJson, "order", "sequence");
		string hash = orderCommit.getKeyValue(objJson, "hash");
		string ledger = orderCommit.getKeyValue(objJson, "ledger");
		string state = orderCommit.getKeyValue(objJson, "state");
		cout << "account:" << account << "fee:" << fee << "offer_sequence:" << offer_sequence
			<< "sequence:" << sequence << "hash:" << hash << "ledger:" << ledger << "state:" << state << endl;
	}
	return 0;
}

int sd_queryorderdetailed()
{
	cout << "call sd_queryorderdetailed begin" << endl;
	Order orderInfo;
	MbedJSONValue objJson;
	string strJson = "";
	string strUrl = " /v1/accounts/orders/";
	string strWallet = "6ByxwCh2Lqwwr3pk6mh4GBb4bsqFz2zAKY";
	string hash = "EF252979355F2666486F69E9C96D137265214DE65B14E1136ECCDCE84F09AD11";
	strJson = orderInfo.GetPaymentInfo(strUrl, strWallet,hash);
	if (strJson.empty())
	{
		cout << "call sd_queryorderdetailed exception quit" << endl;
		return -1;
	}
	string err = orderInfo.getParseMbedJson(objJson, strJson.c_str());
	bool bSuccess = orderInfo.getRequestRet(objJson);
	if (bSuccess)
	{
		string hash = orderInfo.getKeyValue(objJson, "hash");
		int ledger = objJson["ledger"].get<int>();
		int iBalanceNum = orderInfo.getBalanceSize(objJson, "balance_changes");
		for (int i = 0; i < iBalanceNum; i++)
		{
			string counterparty = orderInfo.getBalanceArray(objJson, "balance_changes", i, "counterparty");
		}
		int iOrderChangesNum = orderInfo.getBalanceSize(objJson, "order_changes");
		for (int j = 0; j < iOrderChangesNum; j++)
		{
			string currency_gets = orderInfo.getBalanceArray(objJson, "order_changes", "taker_gets", j, "currency");
		}

	}
	cout << "call sd_queryorderdetailed end" << endl;
	return 0;
}
int main()  
{  
	
	WORD sockVersion = MAKEWORD(2, 2);  
	WSADATA data;  
	if(WSAStartup(sockVersion, &data)!=0)  
	{  
		return 0;  
	}
//	sd_wallet();//OK
//	sd_account();//OK
//	string tx_hash = sd_postpayment();//OK
//	sd_getpaymentinfo(tx_hash);//OK	
// 	sd_gettransactions(tx_hash);//OK
// 	sd_getpaymenthistory();
// 	sd_getdefaultfee();//OK
// 	sd_getserverinfo();//OK
// 	sd_getserverconnected();//OK
 	sd_queryorderlist();//OK
// 	sd_commitorder();//OK
// 	sd_deleteorder();
// 	sd_queryorderdetailed();
	WSACleanup();  
	return 0;  
}  