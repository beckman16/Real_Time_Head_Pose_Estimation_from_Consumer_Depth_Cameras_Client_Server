#ifndef COMMON_H_
#define COMMON_H_

// �R���t�B�O�t�@�C����
#define CONFIG_FILE		"Config.txt"
#ifdef _MSC_VER
	#define DIR_DIV			"\\"
#else
	#define DIR_DIV			"/"
#endif

// ���i���֘A
#define SKEL_NUM			20		// ���i���
#define SRV_SEND_HDR_NUM	5		// �w�b�_�t�����
#define SRV_SEND_INFO_NUM	(SRV_SEND_HDR_NUM+(SKEL_NUM*3))	// �S�̐�

#define TIME_STR_LEN		24		//	����������(YYYY/MM/DD hh:mm:ss.fff)

#define REALTIME_FPS_CHECK_ENABLE

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------
#define CHECK_RC(rc, what)											\
	if (rc != XN_STATUS_OK)											\
	{																\
		printf("%s failed: %s\n", what, xnGetStatusString(rc));		\
		return rc;													\
	}

#define CHECK_RC_ERR(rc, what, errors)			\
{												\
	if (rc == XN_STATUS_NO_NODE_PRESENT)		\
	{											\
		XnChar strError[1024];					\
		errors.ToString(strError, 1024);		\
		printf("%s\n", strError);				\
	}											\
	CHECK_RC(rc, what)							\
}

#endif