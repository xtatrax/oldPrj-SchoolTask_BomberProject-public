/**************************************************************************
 Prim.h

 �A�v���P�[�V�����N���X
 �^�C�}�[�A�R���g���[���A�e�N�X�`��
 �V���h�E�{�����[���@�錾

****************************************************************************/
#pragma once

#include "StdAfx.h"

namespace wiz{

///**************************************************************************
// class App;
// �p�r: �A�v���P�[�V�����N���X
//****************************************************************************/
//class App{
//	//Singleton�ŗ��p���鎩�����g�̃|�C���^
//	static App* m_pApp;
///**************************************************************************
// App(HINSTANCE hInstance,HWND hWnd);
// �p�r: �R���X�g���N�^
// �߂�l: �Ȃ�
// Singleton�ō쐬���邽�߃R���X�g���N�^�A�f�X�g���N�^��privat
//***************************************************************************/
//	App(HINSTANCE hInstance,HWND hWnd);
///**************************************************************************
// ~App();
// �p�r: �f�X�g���N�^
// �߂�l: �Ȃ�
// Singleton�ō쐬���邽�߃R���X�g���N�^�A�f�X�g���N�^��privat
//***************************************************************************/
//	~App(){}
//public:
//	template<typename T> friend inline void SafeDelete(T*& p);
///**************************************************************************
// static App* GetApp(
// HINSTANCE hInstance = 0,
// HWND hWnd = 0
// );
// �p�r: Singleton�̂��߂̃C���X�^���X�\�z�istatic�֐��j
// �߂�l: �\�z����App�̃C���X�^���X
//***************************************************************************/
//	static App* GetApp(HINSTANCE hInstance = 0,HWND hWnd = 0){
//		//����App�̃C���X�^���X�\�z�O�Ȃ�\�z
//		if(!m_pApp){
//			m_pApp = new App(hInstance,hWnd);
//		}
//		//App�̃C���X�^���X��Ԃ�
//		return m_pApp;
//	}
///**************************************************************************
// static void FreeApp();
// �p�r: Singleton�̂��߂̃C���X�^���X�j���istatic�֐��j
// �߂�l: �Ȃ�
//***************************************************************************/
//	static void FreeApp(){
//		//App�C���X�^���X���\�z����Ă�����delete
//		SafeDelete(m_pApp);
//	}
///**************************************************************************
//���J�ϐ�
//***************************************************************************/
//	//���W���[���̃C���X�^���X
//	HINSTANCE m_hInstance;
//	//���C���E�C���h�E�̃n���h��
//	HWND m_hWnd;
//	//���W���[�����t���p�X
//	wstring m_wstrModulePath;
//	//���W���[��������f�B���N�g��
//	wstring m_wstrDir;
//	//���f�B�A�f�B���N�g��
//	wstring m_wstrDataPath;
//};
//
/**************************************************************************
 class Timer;
 �p�r: �^�C�}�[(DXUT��CDXUTTimer������)
****************************************************************************/
class Timer{
protected:
/**************************************************************************
 LARGE_INTEGER   GetAdjustedCurrentTime();
 �p�r: ���݂̃p�t�H�[�}���X�J�E���^�𓾂�
 �߂�l: LARGE_INTEGER�B
 �������X�g�b�v���Ȃ�X�g�b�v�^�C����Ԃ�
//--------------------------------------------------------------------------------------
// If stopped, returns time when stopped otherwise returns current time
//--------------------------------------------------------------------------------------
***************************************************************************/
    LARGE_INTEGER   GetAdjustedCurrentTime();
    bool m_bUsingQPF;
    bool m_bTimerStopped;
    LONGLONG m_llQPFTicksPerSec;

    LONGLONG m_llStopTime;
    LONGLONG m_llLastElapsedTime;
    LONGLONG m_llBaseTime;
public:
/**************************************************************************
 Timer();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    Timer();
/**************************************************************************
 ~Timer();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Timer(){}
/**************************************************************************
 void Reset();
 �p�r: �^�C�}�[�̃��Z�b�g
 �߂�l: �Ȃ�
 // resets the timer
***************************************************************************/
    void Reset();
/**************************************************************************
 void Start();  
 �p�r: �^�C�}�[�̃X�^�[�g
 �߂�l: �Ȃ�
// starts the timer
***************************************************************************/
    void Start();
/**************************************************************************
 void Stop();  
 �p�r: �^�C�}�[�̃X�g�b�v
 �߂�l: �Ȃ�
// stop (or pause) the timer
***************************************************************************/
    void Stop();  
/**************************************************************************
 void Advance();
 �p�r: �^�C�}�[��0.1�b�i�߂�
 �߂�l: �Ȃ�
// advance the timer by 0.1 seconds
***************************************************************************/
    void Advance(); 
/**************************************************************************
 double GetAbsoluteTime();
 �p�r: �V�X�e���^�C�}�[�i�p�t�H�[�}���X�J�E���^�����j�𓾂�
 �߂�l: �V�X�e���^�C�}�[�i�p�t�H�[�}���X�J�E���^�����j
// get the absolute system time
***************************************************************************/
    double GetAbsoluteTime(); 
/**************************************************************************
 double GetTime(); 
 �p�r: �J�����g�̌o�ߎ��Ԃ𓾂�
 �߂�l:�J�����g�̌o�ߎ���
// get the current time
***************************************************************************/
    double GetTime(); 
/**************************************************************************
 float GetElapsedTime(); 
 �p�r: �O��GetElapsedTime���Ă΂�Ă���̌o�ߎ��Ԃ𓾂�
 �߂�l: �o�ߎ���
// get the time that elapsed between GetElapsedTime() calls
***************************************************************************/
    float GetElapsedTime(); 
/**************************************************************************
 void GetTimeValues(
 double& rfTime,		//�J�����g����
 double& rfAbsoluteTime,	//��Ύ���
 float& rfElapsedTime		//�O��GetElapsedTime���Ă΂�Ă���̌o�ߎ���
 ); 
 �p�r: ���ׂẴf�[�^�𓾂�B
 ���O��GetElapsedTime���Ă΂�Ă���̌o�ߎ��Ԃ�����
 �߂�l: �Ȃ��i�w��̎Q�ƂɃZ�b�g�j
// get all time values at once
***************************************************************************/
    void GetTimeValues( double& rfTime, double& rfAbsoluteTime, float& rfElapsedTime ); 
/**************************************************************************
 bool IsStopped(); 
 �p�r: �^�C�}�[���~�܂��Ă邩�ǂ����𒲂ׂ�
 �߂�l: �^�C�}�[���~�܂��Ă��true
// returns true if timer stopped
***************************************************************************/
    bool IsStopped(); 
};



/**************************************************************************
 class ShadowVolume;
 �p�r: �V���h�E�{�����[���N���X
 ��DXUT�T���v�����x�[�X�ɍ쐬
****************************************************************************/
class ShadowVolume{
protected:
	/**************************************************************************
	 struct SHADOWVERT;
	 �p�r: �e��FVF�f�[�^
	 ��DXUT�����p
	****************************************************************************/
	struct SHADOWVERT
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		const static D3DVERTEXELEMENT9 Decl[3];
	};
	/**************************************************************************
	 struct CEdgeMapping;
	 �p�r: �G�b�W�}�b�s���O�N���X
	 ��DXUT�����p
	****************************************************************************/
	struct CEdgeMapping
	{
		int m_anOldEdge[2];  // vertex index of the original edge
		int m_aanNewEdge[2][2]; // vertex indexes of the new edge
		// First subscript = index of the new edge
		// Second subscript = index of the vertex for the edge
	public:
			CEdgeMapping()
			{
				FillMemory( m_anOldEdge, sizeof( m_anOldEdge ), -1 );
				FillMemory( m_aanNewEdge, sizeof( m_aanNewEdge ), -1 );
			}
	};
	const FLOAT ADJACENCY_EPSILON;
	LPD3DXMESH m_pShadowVolumeMesh;
	IDirect3DVertexDeclaration9*    m_pShadowDecl;
	/**************************************************************************
	 int FindEdgeInMappingTable()�֐�
	 �p�r: �G�b�W�}�b�s���O�֐�
	 ��DXUT�����p
	****************************************************************************/
	//--------------------------------------------------------------------------------------
	// Takes an array of CEdgeMapping objects, then returns an index for the edge in the
	// table if such entry exists, or returns an index at which a new entry for the edge
	// can be written.
	// nV1 and nV2 are the vertex indexes for the old edge.
	// nCount is the number of elements in the array.
	// The function returns -1 if an available entry cannot be found.  In reality,
	// this should never happens as we should have allocated enough memory.
	int FindEdgeInMappingTable( int nV1, int nV2, CEdgeMapping* pMapping, int nCount )
	{
		for( int i = 0; i < nCount; ++i )
		{
			// If both vertex indexes of the old edge in mapping entry are -1, then
			// we have searched every valid entry without finding a match.  Return
			// this index as a newly created entry.
			if( ( pMapping[i].m_anOldEdge[0] == -1 && pMapping[i].m_anOldEdge[1] == -1 ) ||

				// Or if we find a match, return the index.
				( pMapping[i].m_anOldEdge[1] == nV1 && pMapping[i].m_anOldEdge[0] == nV2 ) )
			{
				return i;
			}
		}

		return -1;  // We should never reach this line
	}
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//�f�o�C�X
 LPD3DXMESH pMesh			//���ƂȂ郁�b�V��
 );
 �p�r: �R���X�g���N�^�i�V���h�E�{�����[�����쐬����j
 �߂�l: �Ȃ�
***************************************************************************/
	ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh);
/**************************************************************************
 ~ShadowVolume();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~ShadowVolume();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect			//�G�t�F�N�g�ւ̃|�C���^
 );
 �p�r: �e�{�����[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect);
};

}
//end of namespace base

