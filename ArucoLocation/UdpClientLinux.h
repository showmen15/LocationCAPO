#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include <stdio.h>
#include <string>
#include <winsock2.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUF_SIZE 1000
//#define TIMEOUT_S      2     /* Seconds between retransmits */
//#define TIMEOUT_MSS    100000     /* Seconds between retransmits */

class UdpClient
{
public:
	UdpClient(const char* sIP,unsigned short port);
	~ UdpClient();

	char* Receive();
	void Send(string dgram);


private:
	struct sockaddr_in si_other;
	int s;
	int slen;
	char buf[BUF_SIZE];
	char message[BUF_SIZE];
	WSADATA wsa;

	void err(const char *str);
	void info(const char *str);

};
#endif /* UDPCLIENT_H_ */

