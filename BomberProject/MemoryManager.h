////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���������Ǘ�����q�����̏W�܂�
//					��
//	namespace TLIB ;
//		class TMemoryManager ;		//	: �������̊Ǘ��N���X
//		inline void* operator new( size_t iSize,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine)	;		//	:    new ���Z�q�̃I�[�o�[���C�h�֐� �������𐶐����� �\�[�X�t�@�C���E�֐��E�s�ԍ��𓯎��Ɋl������
//		inline void  operator delete(  void* pv,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine)	;		//	: delete ���Z�q�̃I�[�o�[���C�h�֐�
//		template<typename T> inline void SafeDelete(T*& p)		;	//	: ���S�Ƀ|�C���^���폜����
//		template<typename T> inline void SafeDeleteArr(T*& p)	;	//	: ���S�ɔz����폜����
//		
//

#ifndef TLIB_MEMORYMANAGER
#define TLIB_MEMORYMANAGER

#include "DebugFunctions.h"

//namespace TLIB{
class TMemoryManager{
public:
	//	: new ���ꂽ�f�[�^�̏��\��
	struct itemInfo{
		void*		pPointer;
		size_t		iSize	;
		std::string	sFile	;
		std::string	sFunc	;
		UINT		iLine	;

		//	: �R���X�g���N�^
		itemInfo(void* i_pPointer,size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine)
			:pPointer(i_pPointer),iSize(i_iSize),sFile(i_sFile), sFunc(i_sFunc), iLine(i_iLine)
		{}
		//	: �����p�I�[�o�[���C�h?
		bool operator () ( const void* other ) const {
			return this->pPointer == other ;
		}
		//	: �����p�I�[�o�[���C�h?
		bool operator == ( const void* other ) const {
			return this->pPointer == other ;
		}
	};

	//	: new���ꂽ��񃊃X�g
	static std::list<itemInfo> m_ItemInfo ;

	//	: �ǉ�
	static void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine){
		void* pPointer = malloc(i_iSize);
		m_ItemInfo.push_back(itemInfo( pPointer, i_iSize , i_sFile,  i_sFunc, i_iLine));
		return pPointer ; 
	}

	//	: �폜
	static void remove( void* i_pPointer ){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			if( it->pPointer == i_pPointer ){
				free(it->pPointer);		
				it->pPointer = NULL;
				it = m_ItemInfo.erase( it );
				return;
			}
		}
	}
	
	//	: �O���t�B�J��������!
	//	: ��������Ԃ̕`��
	static void Draw(){
		std::list<itemInfo>::iterator it  = m_ItemInfo.begin();
		std::list<itemInfo>::iterator end = m_ItemInfo.end();
		if( GetAsyncKeyState( MYVK_DEBUG_OUTPUT_MEMORY ) ){
			time_t timer;
			struct tm local;

			/* ���ݎ������擾 */
			timer = time(NULL);

			localtime_s(&local, &timer); /* �n�����ɕϊ� */

			/* �n���� �ϊ���\�� */
			printf("�n����: ");
			printf("%4d/", local.tm_year + 1900);
			printf("%2d/", local.tm_mon + 1);
			printf("%2d ", local.tm_mday);
			printf("%2d:", local.tm_hour);
			printf("%2d:", local.tm_min);
			printf("%2d", local.tm_sec);
			printf(" %d\n", local.tm_isdst);


			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"�߂���.txt" , L"���[�J������ %4d/%2d/%2d %2d:%2d:%2d %d \n",
				local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
				local.tm_min, local.tm_sec, local.tm_isdst );
			DWORD i = 0 ;
			for(  ; it != end ; it++ ){
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , " %d \n"               , i                 );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�|�C���^   : 0x%X \n" , it->pPointer      );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�T�C�Y     : %d \n"   , it->iSize         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�t�@�C���� : %s \n"   , it->sFile.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�֐�       : %s \n"   , it->sFunc.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�s         : %d \n"   , it->iLine         );
				i ++ ;
			}
		}	
	}

	//////////
	//	: ���댯
	//	: �ʏ�͗��p���Ȃ�
	//	: ���܂܂Ŋm�ۂ��Ă��������������ׂĔj������
	static void Clear(){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			free((*it).pPointer);
		}
		m_ItemInfo.clear();
	}
	~TMemoryManager(){
		Clear();
	}

};
//std::list<TMemoryManager::itemInfo> TMemoryManager::m_ItemInfo ;

//void* operator new(size_t iSize,LPCTSTR sFile, LPCTSTR sFunc, UINT iLine){
//	return NULL;//TMemoryManager::add(iSize,sFile,sFunc,iLine);
//};
//////////
//	: operator new �̃I�[�o�[���C�h
//inline void* operator new(size_t iSize,LPCSTR  sFile =  "" , LPCSTR  sFunc = "" , UINT iLine = 0)
inline void* operator new(size_t iSize,LPCSTR  sFile  , LPCSTR  sFunc  , UINT iLine )
{
	return TMemoryManager::add(iSize,sFile,sFunc,iLine);
};

inline void operator delete(void* pv,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine){
	return TMemoryManager::remove(pv);
};

inline void operator delete(void* pv){
	return TMemoryManager::remove(pv);
};

#define new new(__FILE__, __FUNCTION__, __LINE__)


//////////
// DXUT�݊��}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{	if (p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{	if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{	if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_VECTOR
#define SAFE_DELETE_VECTOR(v)	{	for( DWORD i = 0 , L = v.size() ; L > i ; i++)	\
										SAFE_DELETE(v[i]) ;							\
									v.clear();										}
#endif    
//
//////////


/////////////////// ////////////////////
//// �֐���     �Ftemplate<typename T> inline void SafeDelete(T*& p)
//// �J�e�S��   �F�e���v���[�g�֐�
//// �p�r       �F���S�Ƀ|�C���^��delete����
//// ����       �F  T*& p               // T�^�̃|�C���^�̎Q��
//// �ߒl       �F�Ȃ�
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
template<typename T>
inline void SafeDelete(T*& p){
    if(p){
        delete p;
    }
    p = 0;
}

/////////////////// ////////////////////
//// �֐���     �Ftemplate<typename T> inline void SafeDeleteArr(T*& p)
//// �J�e�S��   �F�e���v���[�g�֐�
//// �p�r       �F���S�ɔz���delete����
//// ����       �F  T*& p               // T�^�̃|�C���^�̎Q��
//// �ߒl       �F�Ȃ�
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
template<typename T>
inline void SafeDeleteArr(T*& p){
    if(p){
        delete [] p;
    }
    p = 0;
}

/////////////////// ////////////////////
//// �֐���     �Ftemplate<typename T> inline void SafeDeletePointerMap(T& c)
//// �J�e�S��   �F�e���v���[�g�֐�
//// �p�r       �F�|�C���^�[���i�[����std�R���e�i�����S��delete����
//// ����       �F  T*& c               // T�^��std�R���e�i�̎Q��
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F==�L���Ȍ^==
////            �Fstd::map
////            �Fstd::multimap
////
template<typename T>
inline void SafeDeletePointerMap(T& c){
	T::iterator	it  = c.begin()	;
	while(it != c.end()){
		delete it->second ;
		it->second = NULL ;
		it++;
	}
	c.clear();
}
/////////////////// ////////////////////
//// �֐���     �Ftemplate<typename T> inline void SafeDeletePointerContainer(T& c)
//// �J�e�S��   �F�e���v���[�g�֐�
//// �p�r       �F�|�C���^�[���i�[����std�R���e�i�����S��delete����
//// ����       �F  T*& c               // T�^��std�R���e�i�̎Q��
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F==�ȉ��̌^�ȊO�̃R���e�i�ɗL���ł�==
////            �Fstd::map
////            �Fstd::multimap
////
template<typename T>
inline void SafeDeletePointerContainer(T& c){
	T::iterator	it  = c.begin()	;
	while(it != c.end()){
		delete *it ;
		*it = NULL ;
		it++;
	}
	c.clear();
}

/////////////////// ////////////////////
//// �֐���     �Ftemplate<typename T> inline void SafeRelease(T*& p)
//// �J�e�S��   �F�e���v���[�g�֐�
//// �p�r       �F���S�ɃC���^�[�t�F�C�X��release����
//// ����       �F  T*& p               // T�^�̃C���^�[�t�F�C�X�̃|�C���^�̎Q��
//// �ߒl       �F�Ȃ�
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
template<typename T>
inline void SafeRelease(T*& p){
    if(p){
        p->Release();
    }
    p = 0;
}

//};
#endif