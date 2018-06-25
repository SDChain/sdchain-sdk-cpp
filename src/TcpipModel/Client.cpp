#include "Client.h"
#include <WINSOCK2.H>  
//#include "BlockChain.h"


Client::Client()
{
	//m_strIP = "180.113.225.222";
	//m_strIP = "hengwell.asuscomm.com";
	string strDomain = "hengwell.asuscomm.com";
	getipbydomain(strDomain);
	m_strIP = strDomain;
	//cout << "m_sIP is:" << m_strIP << endl;
	m_sPort = 26990;
	m_url = "/info";
	m_host = "rest-beta.sdchain.io";
	m_token = "962cd39d-6496-4b23-a2c5-85e445069a78";
}

Client::Client(string ip,short port)
{
	this->m_strIP = ip;
	this->m_sPort = port;

	m_url = "/info";
	m_host = "testbc.hwelltech.com";
	m_token = "962cd39d-6496-4b23-a2c5-85e445069a78";
}

Client::~Client()
{

}

bool Client::build_post_raw(const string & url,const string & content, string & post_raw)
{
	return build_post_raw(url,m_host,m_token,content,post_raw);
}

bool Client::build_post_raw(const string & url, const string & host, const string & token, const string & content, string & post_raw)
{
	bool ret = true;

	post_raw = "";
	post_raw.append("POST "+ url + " HTTP/1.1\r\n");
	post_raw.append("Host: " + host + "\r\n");
	post_raw.append("Connection: keep-alive\r\n");
	post_raw.append("accept: application/json\r\n");
	post_raw.append("content-type: application/json\r\n");
	string authorization = "Basic YmxvY2tnZW5lcmF0b3I6MTM3NzQzMDJlNTcyYmU4MWMxZmRmZjg2NGZiODA2Yjc2NjcxMzg5NzMwZjBjMDYwZDNlODExNTQ4OGRjNjQ2Mg==";
	//if(!token.empty())
	//	authorization = Base64Encode(token)
	post_raw.append("authorization: " + authorization + "\r\n");

	char pLen[16] = {0};
	sprintf_s(pLen, sizeof(pLen), "%d", content.length());
	string strLen = pLen;

	post_raw.append("Content-Length: " + strLen + "\r\n");
	post_raw.append("\r\n");
	post_raw.append(content);
	post_raw.append("\r\n\r\n");

	return ret;
}

bool Client::build_delete_raw(const string & url, const string & content, string & post_raw)
{
	return build_delete_raw(url, m_host, m_token, content, post_raw);
}

bool Client::build_delete_raw(const string & url, const string & host, const string & token, const string & content, string & post_raw)
{
	bool ret = true;

	post_raw = "";
	post_raw.append("DELETE " + url + " HTTP/1.1\r\n");
	post_raw.append("Host: " + host + "\r\n");
	post_raw.append("Connection: keep-alive\r\n");
	post_raw.append("accept: application/json\r\n");
	post_raw.append("content-type: application/json\r\n");
	string authorization = "Basic YmxvY2tnZW5lcmF0b3I6MTM3NzQzMDJlNTcyYmU4MWMxZmRmZjg2NGZiODA2Yjc2NjcxMzg5NzMwZjBjMDYwZDNlODExNTQ4OGRjNjQ2Mg==";
	//if(!token.empty())
	//	authorization = Base64Encode(token)
	post_raw.append("authorization: " + authorization + "\r\n");

	char pLen[16] = { 0 };
	sprintf_s(pLen, sizeof(pLen), "%d", content.length());
	string strLen = pLen;

	post_raw.append("Content-Length: " + strLen + "\r\n");
	post_raw.append("\r\n");
	post_raw.append(content);
	post_raw.append("\r\n\r\n");

	return ret;
}

string Client::get_content(const string & strRep)
{
	if (strRep.empty())
	{
		cout << "recved string is empty" << endl;
		return "";
	}
	string content = "";
	content = strRep.substr(strRep.find("\r\n\r\n") + sizeof("\r\n\r\n") - 1); //sizeof("\r\n\r\n") 5
	if (content.at(0) != '{' && content.at(0) != '[')
	{
		content = content.substr(content.find("\r\n") + sizeof("\r\n") - 1);
	}
	return content;
}

bool Client::unbuild_post_raw(const string & strRep, int & content_length, string & url,string & content)
{
	bool ret = true;
	
	content_length = get_content_length(strRep);
	content = strRep.substr(strRep.find("\r\n\r\n"));

	if (strRep.find("200 OK") < 0)
	{
		ret = false;
	}
	
	return ret;
}

int Client::get_content_length(const string & strRaw)
{
	int len = -1; // 表示没找到
/*/
	string strRaw = "\
HTTP/1.1 200 OK\r\n\
Blockchain-Id: 13804cbf90e019cc0bcc7243828298492f5d0d87423f776181069eb9af9b2071\r\n\
Chain-Request-Id: f90965648d6aeb6075e3\r\n\
Content-Length: 145\r\n\
X-Frame-Options: DENY\r\n\
\r\n\r\n\
{\"alias\":\"t_key_1\",\"xpub\":\"1c926b1e7a88496e5bd7e29736f9ca85c5386bb995c95412b1084ddc1ab5f80e49e7aea51f08b36b3773baa6277c5902f2034d36315b32bf96a3082c048225d5\"}\
\n";
*/
	string str = "";
	int pos = strRaw.find("Content-Length:") + sizeof("Content-Length:");
	str = strRaw.substr(pos);
	pos = str.find("\r\n");
	str = str.substr(0,pos);
	len = atoi(str.c_str());

	return len;
}

int Client::http_post(const string & url,const string & content,string & strOut)
{
	string post_raw = "";
	build_post_raw(url,content,post_raw);
	return http_post_raw(post_raw,strOut);
}

int Client::http_post_delete(const string & url, const string & content, string & strOut)
{
	string post_raw = "";
	build_delete_raw(url, content, post_raw);
	return http_post_raw(post_raw, strOut);
}

int Client::http_post_raw(const string &strIn,string &strOut)
{
	string strReq;
	string strRep;
	strReq = strIn;

	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
	if(sClient == INVALID_SOCKET)  
	{  
		printf("invalid socket!");  
		return 0;  
	}  
#ifdef WIN32
	//windows下是这样设置超时时间
	int recvTimeout = 3 * 1000;   //30s
	int sendTimeout = 3 * 1000;  //30s
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout ,sizeof(int));
	setsockopt(sClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&sendTimeout ,sizeof(int));
#else
	//在linux下设置超时是这样设置的
	struct timeval timeout = {3,0};    
	setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
	setsockopt(sClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(struct timeval));
#endif

	sockaddr_in serAddr;  
	serAddr.sin_family = AF_INET;  
	serAddr.sin_port = htons(m_sPort);  
	serAddr.sin_addr.S_un.S_addr = inet_addr(m_strIP.c_str());  
	if(connect(sClient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)  
	{  
		//连接失败   
		printf("connect error !");  
		closesocket(sClient);  
		return SOCKET_ERROR;  
	}  

	int ret = 0;
	int left = strReq.length();
	unsigned int pos = 0;
	ret = send(sClient, strReq.c_str(), strReq.length(), 0);  
	if (ret < 0)
	{
		//get last error
		//get errno
		return SOCKET_ERROR;
	}

	while (ret < left )
	{
		pos = pos + ret;
		ret = send(sClient, strReq.c_str() + pos, strReq.length() - pos, 0);  
		if (ret < 0)
		{
			return SOCKET_ERROR;
		}
	}

#ifdef DEBUG_LOG
	cout<< ">>>>>>>>>>HTTP Request (Length = "<< strReq.length() << "):\n" << strReq << endl;
#endif


	char recData[BUFSIZE+1] = {0};  

	ret = 0;
	ret = recv(sClient, recData, BUFSIZE, 0);  
	strRep.append(recData);

	// 第一次收数据可能没有收完全，所以一直收到没有数据为止，这里会堵塞
	while (ret > 0)
	{
		memset(recData,0,BUFSIZE);
		ret = recv(sClient, recData, BUFSIZE, 0); 

		if (ret > 0)
		{
			strRep.append(recData);
		}
	}

	strOut = strRep;

#ifdef DEBUG_LOG
	cout<< ">>>>>>>>>>HTTP Response (Length = "<< strRep.length() << "):\n" << strRep << endl;
#endif

	closesocket(sClient); 
	return 0;
}


bool Client::build_get_raw(const string & url, const string & content, string & get_raw)
{
	return build_get_raw(url, m_host, m_token, content, get_raw);
}

bool Client::build_get_raw(const string & url, const string & host, const string & token, const string & content, string & get_raw)
{
	bool ret = true;

	get_raw = "";
	get_raw.append("GET " + url + " HTTP/1.1\r\n");
	get_raw.append("Host: " + host + "\r\n");
	get_raw.append("cache-control: no-cache\r\n");
	get_raw.append("Connection: keep-alive\r\n");
	get_raw.append("accept: application/json\r\n");
	get_raw.append("content-type: application/json\r\n");
	//string token = "c4fa2402-fd65-4ba5-8f9e-4fbb6479612b";
	get_raw.append("Mbed-Token: " + token + "\r\n");
	get_raw.append("\r\n\r\n");

	return ret;
}

int Client::http_get(const string & url, const string & content, string & strOut)
{
	string get_raw = "";
	build_get_raw(url, content, get_raw);
	return http_post_raw(get_raw, strOut);
}

int Client::http_get_raw(const string &strIn, string &strOut)
{
	return http_post_raw(strIn, strOut);
}

bool Client::getipbydomain(string& strDomain)
{
	string strIp;
	struct hostent *host = gethostbyname(strDomain.c_str());
	for (int i = 0; host->h_addr_list[i]; i++){
		strDomain = (string)inet_ntoa(*(struct in_addr*)host->h_addr_list[i]);
		break;
	}
//	cout << "Domain to IP:" << strDomain << endl;
	return true;

}