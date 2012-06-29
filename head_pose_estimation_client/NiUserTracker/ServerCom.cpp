#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Common.h"
#include "Util.h"
#include "Config.h"
#include "ServerCom.h"

// �R���X�g���N�^
ServerCom::ServerCom(void)
{
	host[0] = NULL;
	port = -1;
	csock = NULL;
}

// �f�X�g���N�^
ServerCom::~ServerCom(void)
{
	EndServer();
}

int ServerCom::InitServer(char* host, short port)
{
	struct sockaddr_in dest;

	sprintf_s(ServerCom::host, sizeof(ServerCom::host), "%s", host);
	ServerCom::port = port;

#ifdef _MSC_VER
	//�\�P�b�g�ʐM�̏���
	WSADATA data;
	WSAStartup(MAKEWORD(2,0), &data);
#endif
	
	//�ڑ���i�T�[�o�j�̃A�h���X����ݒ�
	memset(&dest, 0, sizeof(dest));

	//�|�[�g�ԍ��̓T�[�o�v���O�����Ƌ���
	dest.sin_port = htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(host);

	printf("Connect to %s:%d\n", host, port);

	//�\�P�b�g�̐���
	csock = socket(AF_INET, SOCK_STREAM, 0);

	//�T�[�o�ւ̐ڑ�
	if( connect(csock, (struct sockaddr *) &dest, sizeof(dest)) ) {
		printf("%s:%d �ɐڑ��ł��܂���ł����B\n", host, port);
		csock = NULL;
		return -1;
	}

	return 0;
}

void ServerCom::EndServer(void)
{
	if(csock != NULL) {
#ifdef _MSC_VER
		closesocket(csock);
#else
		close(csock);
#endif
	}
}

// �X�P���g����񑗐M
int ServerCom::SendInfo(const char *time_stamp, const int valsize, const float *value)
{
	char *dp;
	int dsize;
	int timesize;
	int ret = -1;

	timesize = (int)strlen(time_stamp) + 1;
	dsize = valsize + timesize;
	if( (dp = (char *)malloc(dsize)) == NULL ) {
		perror("malloc Failed!!:");
		return ret;
	}

	// ���M�f�[�^�ݒ�
	memcpy(dp, value, valsize);
	// �Ō�Ƀ^�C���X�^���v�ݒ�
	memcpy((dp+valsize), time_stamp, timesize);

	// ���M
	if(SendData(dsize, (char *)dp) == 0) {
		ret = 0;
	}
	else {
		printf("SendData ERROR!!\n");
	}

	free(dp);

	return ret;
}

int ServerCom::SendData(const int datasize, const char *data)
{
	if (csock == NULL) {
		printf("�T�[�o���ڑ� [%s:%d] datasize:%d\n", host, port, datasize);
		return -1;
	}

	// ���M
	int ssize;
	if((ssize = send(csock, (char *)data, datasize, 0)) != datasize) {
		printf("���M�T�C�Y�ُ� sendSize:%d sentSize:%d\n", datasize, ssize);
		return -1;
	}

	return 0;
}