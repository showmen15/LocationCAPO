#include "UdpClientLinux.h"

//http://www.binarytides.com/udp-socket-programming-in-winsock/

UdpClient::UdpClient(const char* sIP,unsigned short portNo)
{
	slen=sizeof(si_other);

	info("\nInitialising Winsock..."); //Initialise winsock

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
		err("Failed. Error Code : %d" + WSAGetLastError());

	info("Initialised.\n");

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) //create socket
		err("socket() failed with error code : %d" + WSAGetLastError());

	memset((char *) &si_other, 0, sizeof(si_other)); //setup address structure
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(portNo);
	si_other.sin_addr.S_un.S_addr = inet_addr(sIP);
}

UdpClient::~UdpClient()
{
	closesocket(s);
	WSACleanup();
}

char* UdpClient::Receive()
{
	memset(buf,'\0', BUF_SIZE);

	if (recvfrom(s, buf, BUF_SIZE, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		err("recvfrom() failed with error code : %d" + WSAGetLastError());

	return buf;
}

void UdpClient::Send(string dgram)
{ 
	if (sendto(s, dgram.c_str(), dgram.length(), 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		err("sendto() failed with error code : %d" + WSAGetLastError());
}

void UdpClient::err(const char *str)
{
	printf(str);
}


void UdpClient::info(const char *str)
{
	printf(str);
}