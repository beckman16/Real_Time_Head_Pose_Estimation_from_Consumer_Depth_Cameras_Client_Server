
#ifndef SERVER_COM_H_
#define SERVER_COM_H_

#include <string>

#ifdef _MSC_VER
	#include <winsock2.h>
#else
	#include <sys/unistd.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif

#include "Util.h"

class ServerCom
{
public:
	// �R���X�g���N�^
	ServerCom(void);
	// �f�X�g���N�^
	~ServerCom(void);
	// �����ݒ�
	int InitServer(char* host,short port);
	// �f�[�^���M
	int SendInfo(const char *time_stamp, const int valsize, const float *value);
	// �f�[�^���M
	int SendData(const int datasize, const char *data);

private:
	// �T�[�o���
	char	host[16];
	short	port;
	SOCKET	csock;

	Util	util;

	// �T�[�o�ڑ�
	int  InitServer(void);
	void EndServer(void);
};

#endif