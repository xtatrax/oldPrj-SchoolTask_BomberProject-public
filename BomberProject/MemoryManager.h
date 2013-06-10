////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
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
#if defined( CF_MEMORYMANAGER_ENABLE )

//namespace TLIB{
//**************************************************************************//
// class TMemoryManager ;
// �S��  : ���� �O
// �p�r  : �������Ǘ��V�X�e��
// ���l  : �v���W�F�N�g���Ŋm�ۂ��ꂽ���������Ǘ����܂�
//**************************************************************************//
class TMemoryManager{
public:
	//**************************************************************************//
	// struct itemInfo ;
	// �S��  : ���� �O
	// �p�r  : new ���ꂽ�f�[�^�̏��\��
	// ���l  : new���L������
	//**************************************************************************//
	struct itemInfo{
		void*		pPointer;
		size_t		iSize	;
		std::string	sFile	;
		std::string	sFunc	;
		const type_info&  sType	;
		UINT		iLine	;
		DWORD		iGenerateTime ;

		/////////////////// ////////////////////
		//// �֐���     �FitemInfo( void* i_pPointer, size_t i_iSize, std::string i_sFile,
		////            �F    std::string i_sFunc, UINT i_iLine, DWORD i_iGTime )
		//// �J�e�S��   �F�R���X�g���N�^
		//// �p�r       �F�C���X�^���X�̐���
		//// ����       �F  void*          i_pPointer
		////            �F  size_t         i_iSize
		////            �F  std::string    i_sFile
		////            �F  std::string    i_sFunc
		////            �F  UINT           i_iLine
		////            �F  DWORD          i_iGTime
		//// �ߒl       �F�Ȃ�
		//// �S��       �F���� �O
		//// ���l       �F
		////            �F
		////
		itemInfo(
			void* i_pPointer,
			size_t i_iSize,
			std::string i_sFile,
			std::string i_sFunc,
			UINT i_iLine,
			DWORD i_iGTime
		)
		:pPointer(i_pPointer)
		,iSize(i_iSize)
		,sFile(i_sFile)
		,sFunc(i_sFunc)
		,iLine(i_iLine)
		,iGenerateTime(i_iGTime)
		,sType(typeid( i_pPointer ))
		{
		}
		/////////////////// ////////////////////
		//// �֐���     �Fbool operator () ( const void* other ) const 
		//// �J�e�S��   �F�I�y���[�^
		//// �p�r       �F()�̋@�\�̃I�[�o�[���[�h
		//// ����       �F  const void* other
		//// �ߒl       �F�Ȃ�
		//// �S��       �F���� �O
		//// ���l       �F����悭�킩���ĂȂ�������^(�E �~ �E)�_
		////            �F
		////
		bool operator () ( const void* other ) const {
			return this->pPointer == other ;
		}
		/////////////////// ////////////////////
		//// �֐���     �Fbool operator == ( const void* other ) const 
		//// �J�e�S��   �F�I�y���[�^
		//// �p�r       �F==�̋@�\�̃I�[�o�[���[�h
		//// ����       �F  const void* other
		//// �ߒl       �F�Ȃ�
		//// �S��       �F���� �O
		//// ���l       �F����悭�킩���ĂȂ�������^(�E �~ �E)�_
		////            �F
		////
		bool operator == ( const void* other ) const {
			return this->pPointer == other ;
		}
	};
private:
	//	: �m�ۂ����������S�̂̃T�C�Y(Byte?)
	static DWORD m_dwAreaSize ;
	//	: new���ꂽ��񃊃X�g
	static std::list<itemInfo> m_ItemInfo ;
public:
	/////////////////// ////////////////////
	//// �֐���     �Fstatic void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine)
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�������̐����ƃ��X�g�ւ̒ǉ�
	//// ����       �F  size_t          i_iSize     //  : �m�ۂ��郁�����̃T�C�Y
	////            �F  std::string     i_sFile     //  : ���������̏����ꂽ�t�@�C���̖��O
	////            �F  std::string     i_sFunc     //  : ���������̏����ꂽ�֐��̖��O
	////            �F  UINT            i_iLine     //  : ���������̏�����Ă���s�ԍ�
	//// �ߒl       �F�m�ۂ����������ւ̃|�C���^
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	static void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine){
		void* pPointer = malloc(i_iSize);
		m_dwAreaSize += i_iSize ;
		m_ItemInfo.push_back(itemInfo( pPointer, i_iSize , i_sFile,  i_sFunc, i_iLine, timeGetTime() ));
		return pPointer ; 
	}

	/////////////////// ////////////////////
	//// �֐���     �Fstatic void remove( void* i_pPointer )
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�������̊J���ƃ��X�g����̍폜
	//// ����       �F  void* i_pPointer    //  : �폜�Ώۂ̃|�C���^
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	static void remove( void* i_pPointer ){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			if( it->pPointer == i_pPointer ){
				m_dwAreaSize -= it->iSize ;
				free(it->pPointer);
				it->pPointer = NULL;
				it = m_ItemInfo.erase( it );
				return;
			}
		}
	}
	
	/////////////////// ////////////////////
	//// �֐���     �Fstatic void Draw()
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�������̏�Ԃ����A���^�C���ɕ`��( �Ƃ��ł����炢���ȁ`�c )
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F���o�[�W�����ł̓f�o�b�O���ȊO�ɈӖ����Ȃ��܂���
	////            �F
	////
	static void Draw(){
<<<<<<< HEAD
		#if defined( CF_MEMORYOUTPUTPROCESS_ENABLE )
=======
>>>>>>> workspace
		Debugger::DBGSTR::addStr( L" Memory\n�� Area Size = %d Byte\n�� Instance  = %d Q'ty\n", m_dwAreaSize, m_ItemInfo.size() );
		if( GetAsyncKeyState( MYVK_DEBUG_OUTPUT_MEMORY ) ){
			std::list<itemInfo>::iterator it  = m_ItemInfo.begin();
			std::list<itemInfo>::iterator end = m_ItemInfo.end();
			time_t timer;
			struct tm local;

			/* ���ݎ������擾 */
			timer = time(NULL);

			localtime_s(&local, &timer); /* �n�����ɕϊ� */

			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"�߂���.txt" , L"���[�J������ %4d/%2d/%2d %2d:%2d:%2d %d \n",
				local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
				local.tm_min, local.tm_sec, local.tm_isdst );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"�߂���.txt" , L"���C���X�^���X�� : %d\n"		, m_ItemInfo.size()  );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"�߂���.txt" , L"�m�ۗ̈�e��     : %d Byte\n"	, m_dwAreaSize       );
			
			DWORD i = 0 ;
			for(  ; it != end ; it++ ){
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "////////////\n"                           );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�f�[�^ %d \n"         , i                 );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�|�C���^   : 0x%X \n" , it->pPointer      );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�T�C�Y     : %d \n"   , it->iSize         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�t�@�C���� : %s \n"   , it->sFile.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�֐�       : %s \n"   , it->sFunc.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "�s         : %d \n"   , it->iLine         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "�߂���.txt" , "����       : %d \n\n" , it->iGenerateTime );
				i ++ ;
			}
		}
		#endif
	}

	/////////////////// ////////////////////
	//// �֐���     �Fstatic void Clear()
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F���܂܂Ŋm�ۂ��Ă��������������ׂĔj������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F���댯
	////            �F�ʏ�͂��̊֐����Ăяo���Ȃ��ł�������
	////            �F�m���Ƀo�O��܂�
	////            �F�v���O�����I�����̍Ō�̍Ō�ł݂̂��̊֐����Ăяo���Ă�������
	////
	static void Clear(){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			free((*it).pPointer);
			(*it).pPointer = NULL ;
		}
		m_ItemInfo.clear();
	}
	/////////////////// ////////////////////
	//// �֐���     �F~TMemoryManager()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�N���X��j��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////
	~TMemoryManager(){
		Clear();
	}

};

//void* operator new(size_t iSize,LPCTSTR sFile, LPCTSTR sFunc, UINT iLine){
//	return NULL;//TMemoryManager::add(iSize,sFile,sFunc,iLine);
//};
////////
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

	//	: ����new�u������
	#if defined( CF_OVERLORDNEW_ENABLE )
		#define new new(__FILE__, __FUNCTION__, __LINE__)
	#endif

	#define NEW new(__FILE__, __FUNCTION__, __LINE__)

#else /* CF_MEMORYMANAGER_ENABLE */
	#define NEW new
#endif

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
	try{
		T::iterator	it  = c.begin()	;
		while(it != c.end()){
			SafeDelete( *it );
			//*it = NULL ;
			it++;
		}
		c.clear();
	}catch(...){
		throw ;
	}
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