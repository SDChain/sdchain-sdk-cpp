/***********************************************************************
 * Module:  Client.h
 * Author:  Administrator
 * Modified: 2018年6月8日 11:08:02
 * Purpose: Declaration of the class Client
 * Comment: Client对象包含对远程
 *    API执行HTTP请求所需的所有
 *    信息。 通常，应用程序将具有向
 *    链核心发出请求的客户端和向HSM
 *    服务器发出请求的单独客户端。
 ***********************************************************************/

#if !defined(__Account_Client_h)
#define __Account_Client_h

#include "define.h"
#include <stdio.h>  
#include <iostream>  
#include <string>  


using namespace std;

class Client
{
public:
	Client();
	Client(string ip, short port);
	~Client();

	void setIp(string newIp){ this->m_strIP = newIp;};
	string getIp(){return this->m_strIP;};
	void setPort(short newPort){this->m_sPort = newPort;};
	short getPort(){return this->m_sPort;};
	int http_post(const string &strIn,string &strOut);
	int http_post_delete(const string & url, const string & content, string & strOut);
	// POST
	bool build_post_raw(const string & url,const string & content, string & post_raw);
	bool build_post_raw(const string & url, const string & host, const string & token, const string & content, string & post_raw);
	int http_post(const string & url,const string & content,string & strOut);
	int http_post_raw(const string &strIn,string &strOut);

	// GET
	bool build_get_raw(const string & url, const string & content, string & get_raw);
	bool build_get_raw(const string & url, const string & host, const string & token, const string & content, string & get_raw);
	//DELETE
	bool build_delete_raw(const string & url, const string & content, string & post_raw);
	bool build_delete_raw(const string & url, const string & host, const string & token, const string & content, string & post_raw);
	int http_get(const string & url, const string & content, string & strOut);
	int http_get_raw(const string &strIn, string &strOut);

	int get_content_length(const string & strRaw);
	string get_content(const string & strRep);
	bool unbuild_post_raw(const string & strRep, int & content_length, string & url,string & content);
	bool getipbydomain(string& strDomain);
protected:
private:
   int urlIndex;
   //list<URL> urls;
   std::string accessToken;
   //socket httpClient;
   std::string json;
   std::string version;

   string m_strIP;
   short m_sPort;
   string m_url;
   string m_host;
   string m_token;


};

#endif