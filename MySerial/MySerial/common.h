#ifndef __COMMM__EVENT___
#define __COMMM__EVENT___
#include <winuser.h>
#include <vector>

#include "MyString.h"

#define TC_TEST_INIT		0
#define TC_TEST_STOP		1
#define TC_TEST_START		2
#define TC_TEST_RUN			3
#define TC_TEST_PAUSE		4

#define TEST_DELAY	200


#define PRODUCT_SOUNDBAR	L"SOUNDBAR"
#define PRODUCT_DCOMPO		L"DCOMPO"

#define KEYS_FUNCION		L"Function"
#define KEYS_KEY			L"Key"
#define KEYS_MSG			L"Msg"
#define KEYS_OTHERS			L"Others"


#define WM_CK_TIMEOUT			WM_USER + 100
#define	WM_CK_NO_NEED			WM_USER + 101
#define	WM_CK_NEED				WM_USER + 102
#define	WM_CK_FILE_ERR			WM_USER + 103
#define	WM_CK_ERR				WM_USER + 104
#define	WM_CK_OK				WM_USER + 105
#define	WM_MIAN_DLG_RESOTRE		WM_USER + 106

//com
#define WM_COMM_READ			(WM_USER +107)

// makeTestSuit
#define WM_TC_DONE				(WM_USER +108)


//power off
#define WM_SET_SHUTDOWN			(WM_USER +109)

//get new func
#define WM_DEV_NOTICE_FUNC		(WM_USER +110)

//
#define TIMER_DEV_APD				1101
#define TIMER_CHK_CONFIG_FIME		1201
// 
#define STR_UPDATE_PATH			L"http://109.104.1.171/upload/ssat/"
#define	STR_CONFIG_FILE_PATH	L"http://109.104.1.171/upload/ssat/ssat_config.xlsx"

#define STR_CMD_TX_DEV_CONNECT			L"1F 10 A5 00 01 B4"
#define STR_CMD_RX_DEV_CONNECT			L"1F 1C A5 00 01 01 B9"
#define STR_CMD_RX_DEV_ISPOWEROFF		L"1F 1C A5 00 02 01 BA"
#define STR_CMD_TX_DEV_DISCONNECT		L"1F 10 A5 00 00 B5"

#define STR_CMD_RX_DEV_SHUTDOWN			L"1F 1C A5 00 02 01 BA"
#define STR_CMD_TX_RECORD_KEY_ON		L"1F 10 A5 00 03 B6"
#define STR_CMD_TX_RECORD_KEY_OFF		L"1F 10 A5 00 04 B1"
#endif