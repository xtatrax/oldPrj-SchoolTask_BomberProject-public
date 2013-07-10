////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library_DirectX
//	�t�@�C����		�FDebugFunctions.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O�p�֐��Q
//					��
//	namespace wiz;
//		class DBGSTR ;
//		class DBGWRITINGLOGTEXT ;
//
#ifndef TLIBDEBUGGER_STRINGS
#define TLIBDEBUGGER_STRINGS
#include "StdAfx.h"
namespace Debugger{
//************************************************//
//class DBGWRITINGLOGTEXT
//
// �S����  : ���� �O
// �ړI    : ���O�t�@�C�����o�͂���֐��Q
//************************************************//
class DBGWRITINGLOGTEXT{
	static wstring DefaultLogFolder ;
	static wstring DefaultLogFileName; 
public:
	static void OutputSystemLog(LPCWSTR i_sOutPutString){
		OutputDebugStringW(i_sOutPutString);
	}
	/////////////////// ////////////////////
	//// �֐���     �Fstatic void Init()
	//// �J�e�S��   �F�C�j�V�����C�U
	//// �p�r       �F�t�@�C���̏�����
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�K�����̊֐���������̕ʂ̊֐����ŏ��Ɉ�񂾂��Ă�ł�������
	////            �F
	////�������������
	////======== �T���v�� ========
	//// void main(){
	////
	////     // ���{�֐�
	////     DBGWRITINGLOGTEXT::Init();   // �N���X�̏�����
	////
	////     while( boolean ){
	////
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	////
	////         if( foo ){
	////
	////             DBGWRITINGLOGTEXT::addStr( "�ǋL������������\n %s" , "�t���̃p�����[�^" );
	////
	////         }
	////     }
	//// }
	////
	static void Init(){
		if(PathFileExists(DefaultLogFileName.c_str())){
			_wremove( DefaultLogFileName.c_str() );
		}
	}

	/////////////////// ////////////////////
	//// �֐���     �F static void Init(wstring FileName)
	//// �J�e�S��   �F �C�j�V�����C�U
	//// �p�r       �F �o�͐�t�@�C���̕ύX�Ə�����
	//// ����       �F    wstring FileName    // ���O�t�@�C���̖��O���w��
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F �K�����̊֐���������̕ʂ̊֐����ŏ��Ɉ�񂾂��Ă�ł�������
	////            �F
	////�������������
	////======== �T���v�� ========
	//// void main( void ){
	////
	////     // ���{�֐�
	////     DBGWRITINGLOGTEXT::Init( L"�ۑ�����t�@�C����" );   // �N���X�̏�����
	////
	////     while( boolean ){
	////
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	////
	////         if( foo ){
	////
	////             DBGWRITINGLOGTEXT::addStr( "�ǋL������������\n %s" , "�t���̃p�����[�^" );
	////
	////         }
	////     }
	//// }
	////
	static void Init(wstring FileName){
		DefaultLogFileName = FileName;
		if(PathFileExists(DefaultLogFileName.c_str())){
			_wremove( DefaultLogFileName.c_str() );
		}
	}
	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(const wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �t�@�C���֕������ǋL ( ���C�h�� )
	//// ����       �F    wchar_t* addStr      //  : ����
	////            �F    ���                  //  : 
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F
	////            �F
	////�������������
	////======== �T���v�� ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // �N���X�̏�����
	////
	////     while( boolean ){
	////
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	////
	////         if( foo ){
	////
	////             // ���{�֐�
	////             DBGWRITINGLOGTEXT::addStr( L"�ǋL������������\n %s" , L"�t���̃p�����[�^" );  // �f�[�^�̒ǋL
	////
	////         }
	////     }
	//// }
	////
	static void addStr(const wchar_t* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
				int d;
				d = 0;
			}
		}
		wchar_t strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �t�@�C���֕������ǉ�
	//// ����       �F �Ȃ�
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F
	////            �F
	////
	//static void addStr(wchar_t* addStr){
	//	FILE* fp ;
	//	_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
	//	if(fp){
	//		fwprintf_s(fp,L"%s",addStr);
	//		fclose(fp);
	//	}
	//}

/* ���Comment�\������ */

	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(const addStr* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �t�@�C���֕������ǋL ( �}���`�o�C�g�� )
	//// ����       �F    wchar_t* addStr      //  : ����
	////            �F    ���                  //  : 
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F
	////            �F
	////�������������
	////======== �T���v�� ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // �N���X�̏�����
	////
	////     while( boolean ){
	////
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	////
	////         if( foo ){
	////
	////             // ���{�֐�
	////             DBGWRITINGLOGTEXT::addStr( "�ǋL������������\n %s" , "�t���̃p�����[�^" );  // �f�[�^�̒ǋL
	////
	////         }
	////     }
	//// }
	////
	static void addStr(const char* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
				int d;
				d = 0;
			}
		}
		char strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vsprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(wstring FileName,wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �t�@�C�����w�肵�ĕ������ǉ�
	//// ����       �F    wstring     FileName    //  : �o�͐�̃t�@�C����
	////            �F    wchar_t*    addStr      //  : ����
	////            �F    ...                     //  : 
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F�����L�P��!!
	////            �F���g�p���ĕ��u�����HDD�p���N�̋��ꂠ��!
	////�������������
	////======== �T���v�� ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // �N���X�̏�����
	////
	////     if( foo ){
	////
	////          // ���{�֐�
	////          DBGWRITINGLOGTEXT::addStr( "�ǋL������������\n %s" , "�t���̃p�����[�^" );  // �f�[�^�̒ǋL
	////      }
	//// }
	////
	static void addStrToFile(const wstring FileName,const wchar_t* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
			}
		}
		wchar_t strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		wstring path = DefaultLogFolder + FileName;
		_wfopen_s(&fp,path.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(wstring FileName,wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �t�@�C�����w�肵�ĕ������ǉ�
	//// ����       �F    wstring     FileName    //  : �o�͐�̃t�@�C����
	////            �F    wchar_t*    addStr      //  : ����
	////            �F    ...                     //  : 
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F�����L�P��!!
	////            �F���g�p���ĕ��u�����HDD�p���N�̋��ꂠ��!
	////�������������
	////======== �T���v�� ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // �N���X�̏�����
	////
	////     while( boolean ){
	////
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	//// �`�`�`�`�`�`�`�`�`�`�`�`
	////
	////         if( foo ){
	////
	////             // ���{�֐�
	////             DBGWRITINGLOGTEXT::addStr( "�ǋL������������\n %s" , "�t���̃p�����[�^" );  // �f�[�^�̒ǋL
	////
	////         }
	////     }
	//// }
	////
	static void addStrToFile(const string FileName,const char* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		//	: 
		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
			}
		}
		//	: �����K��
		char strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vsprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);

		//	: �t�@�C���I�[�v��
		FILE* fp ;
		string defaultPath ;
		TLIB::narrow( DefaultLogFolder , defaultPath);
		string path = defaultPath + FileName;
		fopen_s(&fp,path.c_str(),"a");

		if(fp){
			fprintf_s(fp,"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
};
#if defined( DIRECT3D_VERSION )
//************************************************//
//class DBGSTR
//
// �S����  : ���� �O
// �ړI    :  �f�o�b�O�p���������ʏ�ɕ`��
//         : �f�t�@�C����`
//         : �EDEBUG
//         : �E_DEBUG
//	       : �EON_DEBUGGINGPROCESS
//	       : �̓��A��ȏオ��`����Ă���ꍇ�̂ݗL��
//	       : ��L����`����Ă��Ȃ��ꍇ���ׂẴ����o��
//	       : ���͋�֐�������
//*************************************************//
class DBGSTR{
public:
	#if defined( DIRECT3D_VERSION )
	static bool				m_bDrawFlag;
	static wstring			str;
	static LPD3DXFONT		m_lpDebagFont;        // �t�H���g�I�u�W�F�N
	#endif
	/////////////////// ////////////////////
	//// �֐���     �F static void addStr(wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �`�敶����̒ǉ�
	//// ����       �F    wchar_t* addStr,    // �`�敶�� �t�H�[�}�b�g
	////            �F    ...,                // �ϒ�����
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F �����ɒǉ�
	////            �F
	////
	static void addStr(const wchar_t* addStr,...){
		#if defined( DIRECT3D_VERSION ) && defined(CF_DRAW_DEBUGSTRING)
		if(5120 > str.size()  ){
			wchar_t strBuf[1024];
			va_list	argp;
			va_start(argp, addStr);
			vswprintf_s( strBuf , 1024 , addStr, argp);
			va_end(argp);
			str += strBuf;
		}
		#endif
	}
	/////////////////// ////////////////////
	//// �֐���     �F static void addStrTop(wchar_t* addStr,...)
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F �`�敶����̒ǉ�
	//// ����       �F    wchar_t* addStr,    // �`�敶�� �t�H�[�}�b�g
	////            �F    ...,                // �ϒ�����
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F �擪�ɒǉ�
	////            �F
	////
	static void addStrTop(const wchar_t* addStr,...){
		#if defined( DIRECT3D_VERSION ) && defined(CF_DRAW_DEBUGSTRING)
		if(5120 > str.size()  ){
			wchar_t strBuf[1024];
			va_list	argp;
			va_start(argp, addStr);
			vswprintf_s( strBuf , 1024 , addStr, argp);
			va_end(argp);
			str = strBuf + str;
		}
		#endif
	}

	/////////////////// ////////////////////
	//// �֐���     �F static void Init(LPDIRECT3DDEVICE9 i_pD3DDevice)
	//// �J�e�S��   �F �C�j�V�����C�U
	//// �p�r       �F ������
	//// ����       �F    LPDIRECT3DDEVICE9 i_pD3DDevice,    // �f�o�C�X
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F�t�H���g�Ȃǂ��\�z
	////            �F�K���ŏ��Ɉ�x�����Ă�ł�������
	////
#if defined( DIRECT3D_VERSION )
	static void Init(LPDIRECT3DDEVICE9	i_pD3DDevice){
		#if defined(CF_DRAW_DEBUGSTRING)
		try{
			if (FAILED(D3DXCreateFont(i_pD3DDevice,				/* �f�o�C�X */
							10,									/* �����̍��� */
							0,									/* ������ */
							FW_NORMAL,							/* �t�H���g�̑��� */
							1,									/* MIPMAP�̃��x�� */
							FALSE,								/* �C�^���b�N���H */
							DEFAULT_CHARSET,					/* �����Z�b�g */
							OUT_DEFAULT_PRECIS,					/* �o�͐��x */
							DEFAULT_QUALITY,					/* �o�͕i�� */
							DEFAULT_PITCH | FF_SWISS,			/* �t�H���g�s�b�`�ƃt�@�~�� */
							L"�l�r �S�V�b�N",					/* �t�H���g�� */
							&m_lpDebagFont))) {					/* Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X */
				char		strBuf[2048]={0};
				sprintf_s(strBuf,sizeof(strBuf), "�f�o�b�O�p�t�H���g�̐����Ɏ��s\n �ꏊ : \"%s(%d) Func:%s\" \n�����܂����H",__FILE__,__LINE__,__FUNCTION__);
				wchar_t		outBuf[4096]={0};
				setlocale( LC_CTYPE, "jpn" );
				size_t nNameSize = 0;
				mbstowcs_s(&nNameSize,outBuf,strlen(strBuf),strBuf,_TRUNCATE);
				if(MessageBox(NULL,outBuf,L"�f�o�b�O�֐��G���[ �ꏊ:tagDBGSTR::Init",MB_YESNO) == IDNO){
					throw 1;
				}
			}
		}
		catch(...){
			throw;
		}
		#endif
	}
#endif
	/////////////////// ////////////////////
	//// �֐���     �F static void Draw()
	//// �J�e�S��   �F �����o�֐�
	//// �p�r       �F ������̕`��
	//// ����       �F �Ȃ�
	//// �ߒl       �F �Ȃ�
	//// �S����     �F ���� �O
	//// ���l       �F
	////            �F
	////
	static void Draw(){
		#if defined(CF_DRAW_DEBUGSTRING)
			if(GetAsyncKeyState( MYVK_DEBUG_OUTPUT_DBGSTR )){
				addStrTop(L"============================================================================================================\n");
				addStrTop(L"=====                                      �f�o�b�O������o��                                          =====\n");
				addStrTop(L"============================================================================================================\n");
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( wstring(L"DebugStr.LOG"), str.c_str() );
			}
			if(m_bDrawFlag){
				m_lpDebagFont->DrawText(NULL,str.c_str(), -1, NULL
					, 0 , D3DCOLOR_ARGB(255, 255, 255, 0));
				str   = L"\n\n[ENTER]RESTART : [ALT+ENTER]CSVRELOAD : [CONTROL]INVISIBLE MODE : [F6]SOUND SWITCH : [F7]OBB DRAW : [F8]MEMORY OUTPUT : [F9]DBGSTR OUTPUT : [F11]1FPS MODE : [F12] UPDATE STOP\n";
				str  += L"\n�f�o�b�O\n";
				//str += L"                                                                                                     �R���g���[���[���L�[�{�[�h / A = X / B = C / X = S / Y = D /  \n";
			}
		#endif
	}
};
#endif
}
#endif