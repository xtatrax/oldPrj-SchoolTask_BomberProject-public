/********************************************************************
Effect.cpp

class Object ��-class Effect ��`����-class ThreeDimensionsEffect		��`��
			  |						|		��class BlockBreakEffect	��`��
			  |						��class TwoDimensionsEffect			��`��
			  |								
			�@|- class XMeshEffect	��`��
			  |
			  �� class LineEffect	��`�� 

********************************************************************/


#include "StdAfx.h"
#include "Object.h"
#include "SeiyaEffect.h"
#include "TL-String.h"
//#include "UI.h"


namespace wiz{
/*****************************************************************************
struct VertexLineState	�錾��
�p�r : 3�������W��̒��_�`�揈�����s��
******************************************************************************/

/******************************************************************************
VertexLineState::VertexLineState()
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
******************************************************************************/
VertexLineState::VertexLineState()
{
}

/******************************************************************************
VertexLineState::VertexLineState(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X 
		const wchar_t* i_pFilename		//�t�@�C����
	)
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
******************************************************************************/
VertexLineState::VertexLineState(LPDIRECT3DDEVICE9 pD3DDevice , const wchar_t* i_pFilename )
:m_iDrawPrimitiveVertexNum( 0 ) , m_pVertexBuffer( 0 ) , m_pVertex( 0 ) ,
m_PrimitiveType( D3DPT_TRIANGLESTRIP ) , m_iVertexNum( 0 )
{
	m_pVertexBuffer	= NULL ;
	m_pVertex =NULL ;
	//if( i_pFilename )	m_pTexture = new Texture(pD3DDevice,i_pFilename);
	//else				m_pTexture = 0 ;

}
/******************************************************************************
VertexLineState::~VertexLineState()
�p�r : �f�X�g���N�^
�߂�l : �Ȃ�
******************************************************************************/
VertexLineState::~VertexLineState()
{
	SafeDelete( m_pTexture ) ;
	SafeRelease( m_pVertexBuffer );
}

/******************************************************************************
void VertexLineState::SetVertex(
	LPDIRECT3DDEVICE9	pD3DDevice ,	//�f�o�C�X
	VertexStyle			i_Style			//Object�̌`
);
�p�r : �����ɉ������`�����
�߂�l : �Ȃ�
******************************************************************************/
void VertexLineState::SetVertex( LPDIRECT3DDEVICE9 pD3DDevice , VertexStyle i_Style , D3DPRIMITIVETYPE i_PrimitiveType )
{
	
	D3DXVECTOR3 vHafeSize = D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) / 2 ;	//�����̑傫��

	int iVertexSize = 0 ;	//���_�̐�������

	//�e�X�^�C���̒��_��
	const int c_iTriangle	= 4 ;	//�O�p�`
	const int c_iSquare		= 5 ;	//�l�p�`
	const int c_iCircle		= 7 ;	//�~
	const int c_iCross		= 4 ;	//�\��
	const int c_iLine		= 2 ;	//��

	switch( i_Style ) {
		case VS_Triangle :
			iVertexSize					= c_iTriangle	 ;
			m_iDrawPrimitiveVertexNum	= c_iTriangle - 1;
			break ;
		case VS_Square :
			iVertexSize					= c_iSquare		;
			m_iDrawPrimitiveVertexNum	= c_iSquare - 1 ;
			break ;
		case VS_Circle :
			iVertexSize					= c_iCircle		;
			m_iDrawPrimitiveVertexNum	= c_iCircle	- 1 ;
			break ;
		//��̐����������Ɏg�p
		case VS_Cross :
		case VS_NameLine :
			iVertexSize					= c_iCross		;
			m_iDrawPrimitiveVertexNum	= c_iCross / 2	;
			break ;
		case VS_Line :
			iVertexSize					= c_iLine		;
			m_iDrawPrimitiveVertexNum	= c_iLine - 1	;
			break ;
	}

	float iRotSize = 360.0f / m_iDrawPrimitiveVertexNum ;	
	m_iVertexNum = iVertexSize ;

	//	: ���_�o�b�t�@�̐����i����ł���̈�̃T�C�Y�A�f�[�^�̈����A���_�f�[�^�̒��g�A���_�f�[�^���Ǘ����郁�����A�������ꂽ�o�b�t�@�������A�h���X���A���Ă���j�j
	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * iVertexSize , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	

	switch( i_Style ){

		case VS_Circle :
		case VS_Square :
		case VS_Triangle :
			for ( int i = 0 ; i < iVertexSize ; i++ )
				m_pVertex[ i ]	= Vertex( D3DXVECTOR3(  cosf( D3DXToRadian( iRotSize * i ) ) , sinf(D3DXToRadian( iRotSize * i ) ) , 0.0f )	, 0xFFFFFFFF, D3DXVECTOR2(0.5f,0.0f) );
			//�v���~�e�B�u������
			m_PrimitiveType = i_PrimitiveType ;
			break ;

		case VS_Cross :

			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.5f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( -0.5f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.0f , 0.5f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 0.0f , -0.5f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;

		case VS_NameLine :

			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;

		case VS_Line :
			m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 1.0f , 0.0f , 0.0f ) , 0xFFFFFFFF , D3DXVECTOR2(0.0f ,0.0f) );
			
			m_PrimitiveType = D3DPT_LINELIST ;
			break ;
	};

	m_pVertexBuffer->Unlock();
}

/******************************************************************************
void VertexrhwState::SetDownColor( 
	DWORD i_dwColor	//�Z�b�g�������F
) ;
�p�r : �F�̕ύX
�߂�l : �Ȃ�
******************************************************************************/
void VertexLineState::SetDownColor( DWORD i_dwColor )
{
	//�f�[�^��ύX
	for( int i = 0 ; i <m_iVertexNum  ; i++ )
		m_pVertex[ i ].m_dwColor -= i_dwColor ;

	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	
	
	for ( int i = 0 ; i < m_iVertexNum ; i++ )
		m_pVertex[ i ]	= Vertex( m_pVertex[i].m_vPos , m_pVertex[i].m_dwColor , m_pVertex[i].m_vTex);

	m_pVertexBuffer->Unlock();

}

/******************************************************************************
void VertexLineState::setVertexPos(
	vector<D3DXVECTOR3*> i_vPosVec�ύX������Line�̃|�W�V����
);
�p�r : ���_�̈ʒu��ύX����
�߂�l : �Ȃ�
******************************************************************************/
void VertexLineState::setVertexPos( vector<D3DXVECTOR3*> i_vPosVec )
{
	try{
		int iLoadPosSize = i_vPosVec.size();
		int iVertexSize	 = m_iVertexNum ;

		if( iLoadPosSize != iVertexSize ){
			#ifdef _DEBUG
				throw BaseException(	L"�ݒ肵�����ʒu�̐����Ⴂ�܂�"	,
									L"VertexLineState::setVertexPos()");
			#else
				return ;
			#endif
		}else{
			for(int i = 0 ; i < iLoadPosSize ; i++ ){
				m_pVertex[ i ].m_vPos = *i_vPosVec[ i ] ;
			}
			m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	
			
			for ( int i = 0 ; i < m_iVertexNum ; i++ )
				m_pVertex[ i ]	= Vertex( m_pVertex[i].m_vPos , m_pVertex[i].m_dwColor , m_pVertex[i].m_vTex);

			m_pVertexBuffer->Unlock();
		}

	}catch(...){
		throw ;
	}
}


/******************************************************************************
void VertexLineState::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X
	const D3DXMATRIX& i_Matrix		//�`�悵�����v���[�g�̔z��
	)
�p�r : �����`�̃v���[�g��`��
�߂�l : �Ȃ�
******************************************************************************/
void VertexLineState::Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix )
{
	 pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	//if( m_pTexture ) pD3DDevice->SetTexture( 0 , m_pTexture->getTexture() );			//	: �e�N�X�`����ݒ�iNULL �̏ꍇ�̓e�N�X�`�������j

	 //���[���h�ϊ��s���ݒ�
	pD3DDevice->SetTransform( D3DTS_WORLD , &i_Matrix );								//�ϊ��ςݒ��_�̏ꍇ�͖��������

	//	: ���_�o�b�t�@��p���ă��f����`�悷��
	pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: �`��ΏۂƂȂ钸�_�o�b�t�@��ݒ�
	pD3DDevice->SetFVF( Vertex::getFVF() );											//	: ���_�f�[�^�̌`����ݒ�
	pD3DDevice->DrawPrimitive( m_PrimitiveType , 0, m_iDrawPrimitiveVertexNum );	//	: ���_�f�[�^�̕`��i�`��̎d���A�`��J�n�ʒu�A�v���~�e�B�u���j


	pD3DDevice->SetTexture( 0 , NULL );												//	: �e�N�X�`����ݒ�iNULL �̏ꍇ�̓e�N�X�`�������j
	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );

}


/*********************************************************************
class Effect : public Object	��`��
�p�r : ���o�p�G�t�F�N�g�̌��N���X
*********************************************************************/

/*********************************************************************
Effect::clear()
�p�r : �폜����
�߂�l: �Ȃ�
*********************************************************************/
void Effect::clear()
{
	SafeRelease(m_pTexture);
}

/*********************************************************************
Effect::Effect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
*********************************************************************/
Effect::Effect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
:m_fEffectSize(i_fSize)
{
	if( i_filename ){
		int Decolorisations[4] ;
		// 0 = �A���t�@�l , 1 = �� , 2 = �� , 3 = ��
		for(int i = 0 ; i < 4 ; i++){
			Decolorisations[i] = i_Decolorisation & 0x000000FF ;
			i_Decolorisation = i_Decolorisation >> 8 ;		//1�F���V�t�g
		}

		//D3DXCreateTextureFromFileEx(
		//	pD3DDevice,
		//	i_filename,			         // �t�@�C����
		//	0,
		//	0,
		//	0,
		//	0,
		//	D3DFMT_A1R5G5B5,                // �F�������\��
		//	D3DPOOL_MANAGED,
		//	D3DX_FILTER_LINEAR,
		//	D3DX_FILTER_LINEAR,
		//	D3DCOLOR_ARGB(Decolorisations[0], Decolorisations[1], Decolorisations[2], Decolorisations[3]),  // �w�肳�ꂽ�F�𓧉ߐF�Ƃ���
		//	NULL,
		//	NULL,
		//	&m_pTexture                   // �e�N�X�`����
		//);
	}else{
		m_pTexture = 0 ;
	}
}

/*********************************************************************
Effect::~Effect()
�p�r: �f�X�g���N�^
�߂�l: �Ȃ�
*********************************************************************/
Effect::~Effect()
{
	clear() ;
}

/*********************************************************************
class ThreeDimensionsEffect : public Effect	��`��
�p�r : 3�������W�̃G�t�F�N�g�`��N���X
*********************************************************************/

/*********************************************************************
ThreeDimensionsEffect::PointSpriteVertex::PointSpriteVertex(
		const D3DXVECTOR3&	i_vPos,		//�ʒu
		BYTE				i_byBlue,	//�F
		BYTE				i_byGreen,	//�ΐF
		BYTE				i_byRed,	//�ԐF
		BYTE				i_byAlpha	//�����x
		);
�p�r : �����t���R���X�g���N�^
�߂�l : �Ȃ�
*********************************************************************/
ThreeDimensionsEffect::PointSpriteVertex::PointSpriteVertex(  const D3DXVECTOR3& i_vPos,
	BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
	:m_vPos(i_vPos)
{
	m_Color.b = i_byBlue	;
	m_Color.g = i_byGreen	;
	m_Color.r = i_byRed		;
	m_Color.a = i_byAlpha	;
}

/*********************************************************************
void ThreeDimensionsEffect::PointSpriteVertex::setState(
	const D3DXVECTOR3&	i_vPos,		//�ʒu
	DWORD				i_dwColor	//�F
	) ;
�p�r : �X�e�[�^�X������
�߂�l : �Ȃ�
*********************************************************************/
void ThreeDimensionsEffect::PointSpriteVertex::setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor)
{
	m_vPos		= i_vPos ;
	m_dwColor	= i_dwColor ;
}

/*********************************************************************
ThreeDimensionsEffect::ThreeDimensionsEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
*********************************************************************/
ThreeDimensionsEffect::ThreeDimensionsEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:Effect(pD3DDevice,i_filename,i_Decolorisation,i_fSize)
{
}

/*********************************************************************
void ThreeDimensionsEffect::VerticesRender(
		LPDIRECT3DDEVICE9 pD3DDevice		,	//�f�o�C�X
		const PointSpriteVertex* pPSVertex	,	//�o�[�e�b�N�X�̔z��
		unsigned int VertexSize					//���ݕێ����Ă��钸�_�f�[�^�̐�
		);
�p�r : �`�揈��
�߂�l : �Ȃ�
*********************************************************************/
void ThreeDimensionsEffect::VerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteVertex* pPSVertex,unsigned int VertexSize)
{
	//�����ݒ�
	if(VertexSize <= 0 ) VertexSize = 0 ;
	else if(VertexSize > m_iVerticesMaxSize) VertexSize = m_iVerticesMaxSize ;
	////�`�揈��
	pD3DDevice->SetFVF( getSPFVF() );
	pD3DDevice->SetTexture(0,m_pTexture);
	pD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST,VertexSize,pPSVertex, getSPSize() ) ;

}

/***********************************************************
class RHWEffect : public Effect	��`��
�p�r : �X�N���[�����W�p�̃G�t�F�N�g��`��
***********************************************************/

/**********************************************************************
RHWEffect::RHWEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
RHWEffect::RHWEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:Effect(pD3DDevice,i_filename,i_Decolorisation,i_fSize){}

/*********************************************************************
void RHWEffect::RHWVerticesRender(
		LPDIRECT3DDEVICE9			pD3DDevice	,	//�f�o�C�X
		const PointSpriteRHWVertex* pPSRHWVertex,	//�o�[�e�b�N�X�̔z��
		unsigned int				VertexSize		//���ݕێ����Ă��钸�_�f�[�^�̐�
		);
�p�r : �`�揈��
�߂�l : �Ȃ�
*********************************************************************/
void RHWEffect::RHWVerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteRHWVertex* pPSRHWVertex,unsigned int VertexSize)
{
	//�����ݒ�
	if(VertexSize <= 0 ) VertexSize = 0 ;
	else if(VertexSize > m_iVerticesMaxSize) VertexSize = m_iVerticesMaxSize ;
	//�`�揈��
	pD3DDevice->SetFVF( getSPRHWFVF() );
	pD3DDevice->SetTexture(0,m_pTexture);
	pD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST,VertexSize,pPSRHWVertex, getSPRHWSize() ) ;

}

/***********************************************************
class ScaleEffect : public RHWEffect	��`��
�p�r : �X�N���[�����W�p�̃G�t�F�N�g��`��
***********************************************************/

/**********************************************************************
ScaleEffect::ScaleEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	const D3DXVECTOR3&	i_vPos			,	//�ʒu��ݒ�
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
ScaleEffect::ScaleEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,
						 const D3DXVECTOR3& i_vPos , float i_fSize)
	:RHWEffect(pD3DDevice,i_filename,0x00000000,i_fSize)
{
	m_pPSVertexrhw = new PointSpriteRHWVertex(i_vPos ,0xFFFFFFFF );
}

/***********************************************************************
ScaleEffect::~ScaleEffect()
�p�r: �f�X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
ScaleEffect::~ScaleEffect()
{
	SafeDelete( m_pPSVertexrhw );
}

/******************************************************************
virtualvoid ScaleEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	Command&				i_Com			//�R�}���h
) ;
�p�r : �V�[���̕ω�
�߂�l : �Ȃ�
******************************************************************/
void ScaleEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
 {
	 m_fEffectSize++ ;
 }

/*****************************************************************
 virtual void ScaleEffect::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command i_Com						//�R�}���h
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
*****************************************************************/
void ScaleEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{


	//�����_�[�X�e�[�g��ύX�����邽�߂̃N���X��錾
	DeviceRenderState drs = DeviceRenderState() ;

	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//���C�e�B���O���[�h��FALSE�ɐݒ�
	drs.ChangeRS_PointSprite(m_fEffectSize);			//�`����@���|�C���g�X�v���C�g�ɐݒ�
	drs.ChangeRS_ALPHABLENDENABLE_Black();				//���Z�����̐ݒ�
	drs.ChangeRenderState(pD3DDevice);					//��L�̐ݒ�Ƀ����_�[�X�e�[�g��ύX����

	RHWVerticesRender(pD3DDevice , m_pPSVertexrhw , 1 );

	drs.ChangeRenderState(pD3DDevice);					//��L�̐ݒ�Ƀ����_�[�X�e�[�g��ύX����

}



/***********************************************************
class ExtinguishEffect : public RHWEffect	��`��
�p�r : ���Ŏ��̃G�t�F�N�g
***********************************************************/

/***********************************************************
struct ExtinguishEffectState	��`��
�p�r : ���_�f�[�^��ύX���邽�߂̍\����
***********************************************************/

/*******************************************************
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState( 
	float				i_fSpeed,			//�X�s�[�h
	const D3DXVECTOR3&	i_vPos,				//�ʒu
	int 				i_iRadSpeed,		//��]�̑���
	int					i_iLifeTime,		//�\������
	int					i_iParticleSize,	//�p�[�e�B�N���̐�
	DWORD				i_dwColor,			//�F
	)
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
*******************************************************/
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos, int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,DWORD i_dwColor )
	:m_fSpeed(i_fSpeed), m_iLifeTime(i_iLifeTime),m_vCenter(i_vPos),m_fLangth(0),m_iRadSpeed(i_iRadSpeed),m_iRad(0)
{
	for(int i = 0 ; i < i_iParticleSize ; i++) m_Vertices.push_back( PointSpriteRHWVertex(i_vPos,i_dwColor) ) ;
}

/*******************************************************
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState( 
	float				i_fSpeed,			//�X�s�[�h
	const D3DXVECTOR3&	i_vPos,				//�ʒu
	int 				i_iRadSpeed,		//��]�̑���
	int					i_iLifeTime,		//�\������
	int					i_iParticleSize,	//�p�[�e�B�N���̐�
	BYTE				i_byBlue,			//�F
	BYTE				i_byGreen,			//�ΐF
	BYTE				i_byRed,			//�ԐF
	BYTE				i_byAlpha			//�����x
	)
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
*******************************************************/
ExtinguishEffect::ExtinguishEffectState::ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos,int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
	:m_fSpeed(i_fSpeed), m_iLifeTime(i_iLifeTime),m_vCenter(i_vPos),m_fLangth(0),m_iRadSpeed(i_iRadSpeed),m_iRad(0)
{
	for(int i = 0 ; i < i_iParticleSize ; i++) m_Vertices.push_back( PointSpriteRHWVertex(i_vPos,i_byBlue,i_byGreen,i_byRed,i_byAlpha) ) ;
}

/*****************************************************************
bool ExtinguishEffect::ExtinguishEffectState::Move(
	const float* i_fRadSinArray,	//Sin�̔z�������
	const float* i_fRadCosArray		//Cos�̔z�������
)
�p�r : Particle�̓������s���폜�����̏ꍇ��true��Ԃ�
�߂�l : �Ȃ�
*****************************************************************/
bool ExtinguishEffect::ExtinguishEffectState::Move(const float* i_fRadSinArray,const float* i_fRadCosArray)
{
	//��Ɨp�ϐ�
	int iRad = m_iRad ;

	//���[�v�p���_�f�[�^
	list<PointSpriteRHWVertex>::iterator it  = m_Vertices.begin() ;
	list<PointSpriteRHWVertex>::iterator end = m_Vertices.end()   ;

	//���_�f�[�^�̃��[�v
	for(; it != end ; it++){
		//�p�x��360�x�𒴂��Ȃ��悤�ɏ���
		iRad %= MAXDEGREES ;

		//�����F�ɕύX���邽�߂̕ϐ�
		BYTE DownColor = 0x00000000 ;
		if(m_iLifeTime >= 1 )DownColor = ( ( m_iLifeTime - 1 ) * (*it).m_Color.a ) / m_iLifeTime ;

		D3DXVECTOR3	 g_vDir = D3DXVECTOR3(i_fRadCosArray[iRad],i_fRadSinArray[iRad],0.0f);

		//���_�̈ړ������𐳋K��
		D3DXVec3Normalize(&g_vDir,&g_vDir);

		//�ʒu�̐ݒ�
		(*it).m_vPos	= m_vCenter + g_vDir * m_fLangth ;
		iRad += MAXDEGREES / m_Vertices.size() ;

		//�F��ύX
		(*it).m_Color.r = DownColor ;
		(*it).m_Color.g = DownColor ;
		(*it).m_Color.b = DownColor ;
		(*it).m_Color.a = DownColor ;
	}
	//�����\�����Ԃ��O�ɂȂ�����
	if( m_iLifeTime < 0 )	return true ;
	else					m_iLifeTime-- ;

	m_fLangth += m_fSpeed;
	m_iRad += m_iRadSpeed ;
	return false ;
}

/**********************************************************************
ExtinguishEffect::ExtinguishEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
ExtinguishEffect::ExtinguishEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
	:RHWEffect(pD3DDevice,i_filename,i_Decolorisation,i_fSize),m_iVerticesSize( 0 )
{
	for(int i = 0 ; i < MAXDEGREES ; i++){
		m_fRadCosArray[i] = cosf(D3DXToRadian(i));
		m_fRadSinArray[i] = sinf(D3DXToRadian(i));
	}

	ZeroMemory( m_DrawVertices , sizeof(m_DrawVertices) ) ;

}

/***********************************************************************
void ExtinguishEffect::AddExtinguishEffect(
				const D3DXVECTOR3,	i_vPos,					//�ʒu
				float				i_fSpeed,				//�X�s�[�h
				int 				i_iRotSpeed,			//��]�̑���
				int					i_iParticleSize,		//�p�[�e�B�N���̐�
				int					i_iLifeTime,			//�\������
				BYTE				i_bBlue		= 0xFF,		//�F
				BYTE				i_bGreen	= 0xFF,		//�ΐF
				BYTE				i_bRed		= 0xFF,		//�ԐF
				BYTE				i_bAlpha	= 0xFF		//�����F
			);
�p�r: �Q�[�W�̒i�K���オ�������ɔ�������G�t�F�N�g�I�u�W�F�N�g�̍쐬
�߂�l: �Ȃ�
************************************************************************/
void ExtinguishEffect::AddExtinguishEffect(const D3DXVECTOR3 i_vPos,float i_fSpeed,int i_iRotSpeed , int i_iLifeTime ,int i_iParticleSize, BYTE i_bBlue,BYTE i_bGreen, BYTE i_bRed,BYTE i_bAlpha)
{
	ExtinguishEffectState* State  = new ExtinguishEffectState( i_fSpeed,i_vPos,i_iRotSpeed,i_iLifeTime,i_iParticleSize,i_bBlue,i_bGreen,i_bRed,i_bAlpha) ;
	m_Statelist.push_back(State);

}

/******************************************************************
virtualvoid ExtinguishEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	Command&				i_Com			//�R�}���h
) ;
�p�r : �V�[���̕ω�
�߂�l : �Ȃ�
******************************************************************/
void ExtinguishEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	try{

		list<ExtinguishEffectState*>::iterator		StateIt = m_Statelist.begin() ;		//�`��V�X�e���̃X�e�[�^�X
		list<ExtinguishEffectState*>::iterator		endIt	= m_Statelist.end() ;		//���[�v�̏I���

		//�`�惋�[�v
		while(StateIt != endIt){

			//��̃p�[�e�B�N���𓮂����A�폜����ꍇ�ɐ^���Ԃ��Ă���
			bool DeleteFlg = (*StateIt)->Move(m_fRadSinArray,m_fRadCosArray) ;		

			//�폜����
			if(DeleteFlg){

				StateIt = m_Statelist.erase(StateIt);
				continue ;
			
			}
			
			//���_�f�[�^�̕ϐ�
			list<PointSpriteRHWVertex>::iterator it  = (*StateIt)->m_Vertices.begin() ;	
			list<PointSpriteRHWVertex>::iterator end = (*StateIt)->m_Vertices.end()   ;	

			//�p�[�e�B�N����`�悷�邽�߂̒��_�f�[�^��ݒ肷��
			for(  ; it != end ;  it++){

				//�`�悷�钸�_���̍��v���ő�l�𒴂��ĂȂ��ꍇ
				if(m_iVerticesSize < m_iVerticesMaxSize ){
					//���_��`��p�z��ɐݒ肷��
					m_DrawVertices[m_iVerticesSize] = (*it) ;
					m_iVerticesSize++ ;

				//�������ꍇ
				}else{
					//�f�o�b�N�p
					throw BaseException(L"Particle�̏���𒴂��܂���",
						L"ExtinguishEffect::Draw()");
					//Release�p
					//break ;

				}

			}

			StateIt++ ;	//���̃p�[�e�B�N���ɐi�߂�
		}

	}
	catch(...){
		throw ;
	}
}

/*****************************************************************
 virtual void ExtinguishEffect::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command i_Com						//�R�}���h
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
*****************************************************************/
void ExtinguishEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{
	try{
		//�����_�[�X�e�[�g��ύX�����邽�߂̃N���X��錾
		DeviceRenderState drs = DeviceRenderState() ;

		drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//���C�e�B���O���[�h��FALSE�ɐݒ�
		drs.ChangeRS_PointSprite(m_fEffectSize);			//�`����@���|�C���g�X�v���C�g�ɐݒ�
		drs.ChangeRS_ALPHABLENDENABLE_Black();				//���Z�����̐ݒ�

		drs.ChangeRenderState(pD3DDevice);					//��L�̐ݒ�Ƀ����_�[�X�e�[�g��ύX����

		//�p�[�e�B�N���̕`��
		RHWVerticesRender(pD3DDevice,m_DrawVertices,m_iVerticesSize);

		//�����_�[�X�e�[�g�̕ύX
		drs.ChangeRenderState(pD3DDevice);

		//���_�����[���ɖ߂�
		m_iVerticesSize = 0 ;

	}
	catch(...){
		throw ;
	}
}






/***********************************************************
class BreakEffect : public ThreeDimensionsEffect
�p�r : �j�󂳂ꂽ�Ƃ��̃G�t�F�N�g
***********************************************************/

/*******************************************************
BreakEffect::EffectState::EffectState(
	int					i_iVertexSize,		//���_�f�[�^�̐�
	float				i_vPos,				//�ʒu
	)
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
*******************************************************/
BreakEffect::EffectState::EffectState(int i_iVertexSize, const D3DXVECTOR3& i_vPos)
:m_iLifeTime(0)
{
	const int c_iDirType = 4 ;

	D3DXVECTOR3 DirVec[c_iDirType] = {
		D3DXVECTOR3(1.0f,1.0f,0.0f),
		D3DXVECTOR3(-1.0f,1.0f ,0.0f),
		D3DXVECTOR3(1.0f,-1.0f,0.0f),
		D3DXVECTOR3(-1.0f,-1.0f ,0.0f)
	};

	for(int i = 0 ; i < i_iVertexSize ; i++){

		float fSpeed =  ( rand() % 3 ) * 0.1f  + 0.03f ; 
		float DirX = ( rand() % 10 ) * 0.05f + 0.1f;
		float DirY = ( rand() % 10 ) * 0.05f + 0.1f;
		
		D3DXVECTOR3 Dir = D3DXVECTOR3( DirX , DirY , 0.0f ) ;
		Dir.x *= DirVec[ i % c_iDirType ].x ;
		Dir.y *= DirVec[ i % c_iDirType ].y ; 

		m_Vertices.push_back(PointSpriteVertex(i_vPos,0xFF,0xFF,0xFF,0xFF));
		m_EffectParams.push_back( EffectParam(Dir,fSpeed) );
	}
}


/*****************************************************************
bool BreakEffect::EffectState::Move(
		Command				i_Com			//�R�}���h
)
�p�r : Particle�̓������s���폜�����̏ꍇ��true��Ԃ�
�߂�l : �Ȃ�
*****************************************************************/
bool BreakEffect::EffectState::Move( Command& i_Com )
{

	//��юU���Ă��鎞��
	const int c_iDeadTime = 50 ;

	//���_�f�[�^�̃C�e���[�^�̐錾
	list<PointSpriteVertex>::iterator VertexIt	= m_Vertices.begin();
	list<PointSpriteVertex>::iterator end		= m_Vertices.end()  ;

	//�ړ��p�����[�^�̃C�e���[�^�̐錾
	list<EffectParam>::iterator ParamIt = m_EffectParams.begin() ;

	//���_�f�[�^���ړ�����郋�[�v
	while(VertexIt != end){

		 (*ParamIt).m_fSpeed -=  (*ParamIt).m_fSpeed / c_iDeadTime ;

		(*VertexIt).m_vPos +=  (*ParamIt).m_vDir *  (*ParamIt).m_fSpeed ;		//�ړ�����
		(*VertexIt).m_Color.r += 10 ;											//�F�̕ύX

		//�e�f�[�^�����ɐi�߂�
		ParamIt++	;
		VertexIt++	;
	}

	m_iLifeTime++ ;

	//�폜�������ꍇ��true��Ԃ�
	if(m_iLifeTime < c_iDeadTime )	return false ;
	else							return true  ;
}

/**********************************************************************
BreakEffect::BreakEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
BreakEffect::BreakEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize)
:ThreeDimensionsEffect(pD3DDevice,i_filename,i_Decolorisation,i_fSize),m_iDrawVerticesNumber( 0 )
{
	for(int i = 0 ; i < m_iVerticesMaxSize ; i++ )
		m_DrawVertices[i] = PointSpriteVertex(D3DXVECTOR3(0.0f,0.0f,0.0f),0xFFFFFFFF) ;
}

/***********************************************************************
void BreakEffect::AddBreakEffect(
				const D3DXVECTOR3& i_vPos,	//�ʒu
				);
�p�r: �u���b�N�j�󎞂̃G�t�F�N�g�I�u�W�F�N�g�̍쐬
�߂�l: �Ȃ�
************************************************************************/
void BreakEffect::AddBreakEffect(const D3DXVECTOR3& i_vPos)
{
	const int c_VertexSize = 5 ;

	EffectState*		State  = new EffectState( c_VertexSize , i_vPos ) ;
	m_Statelist.push_back(State);

}

/******************************************************************
virtual void BreakEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	Command&				i_Com			//�R�}���h
) ;
�p�r : �V�[���̕ω�
�߂�l : �Ȃ�
******************************************************************/
void BreakEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{


	//�`��piterator�̐錾
	list<EffectState*>::iterator		StateIt  = m_Statelist.begin() ;
	//���[�v�p�C�e���[�^�̐錾
	list<EffectState*>::iterator		endIt = m_Statelist.end() ;

	for(int i = 0 ; StateIt != endIt ; i++ ){

		//�ړ�����
		bool DeleteFlg = (*StateIt)->Move( i_Com );

		//�폜����
		if(DeleteFlg){

			StateIt  = m_Statelist.erase(StateIt) ;

		}else{

			//�z��ɓ���钸�_�f�[�^
			list<PointSpriteVertex>::iterator it  = (*StateIt)->m_Vertices.begin() ;
			list<PointSpriteVertex>::iterator end = (*StateIt)->m_Vertices.end() ;

			//�z��ɕ`�悳���o�[�e�b�N�X�̃f�[�^������
			for( ; it != end ; it++ ){
				m_DrawVertices[m_iDrawVerticesNumber] = (*it) ;
				m_iDrawVerticesNumber++ ;
			}

			//�C�e���[�^�����ɐi�߂�
			StateIt++  ;
		}

	}

}

/*****************************************************************
 virtual void BreakEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	Command					i_Com			//�R�}���h
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
*****************************************************************/
void BreakEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{

	//�����_�[�X�e�[�g��ύX�����邽�߂̃N���X��錾
	DeviceRenderState drs = DeviceRenderState() ;
	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//���C�e�B���O���[�h��FALSE
	drs.ChangeRS_PointSprite(m_fEffectSize);
	drs.ChangeRS_ALPHABLENDENABLE_Black();
	drs.ChangeRenderState(pD3DDevice);

	//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX Matrix ;
	D3DXMatrixIdentity(&Matrix);		
	pD3DDevice->SetTransform(D3DTS_WORLD,&Matrix);

	//�p�[�e�B�N���̕`��
	VerticesRender(pD3DDevice,m_DrawVertices,m_iDrawVerticesNumber);

	//�����_�[�X�e�[�g�̕ύX
	drs.ChangeRenderState(pD3DDevice);

	//���_�����[���ɖ߂�
	m_iDrawVerticesNumber = 0 ;
	//���_�f�[�^�̔z������Z�b�g����
	ZeroMemory( m_DrawVertices , sizeof( m_DrawVertices ));

}


/*******************************************************************
class LineEffect : public Object ��`��
�p�r :	���G�t�F�N�g�̕`��
*******************************************************************/

/*******************************************************************
class LineEffect::LineEffectGroup::LineEffectState  ��`��
�p�r : ���G�t�F�N�g���Ǘ�����X�e�[�^�X
*******************************************************************/
/***********************************************************
LineEffect::LineEffectGroup::LineEffectState::LineEffectState(
	LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
	const D3DXVECTOR3&	i_vPos		,	//�ʒu
	const D3DXVECTOR3&	i_vSize		,	//�傫��
	const D3DXVECTOR3&	i_vRot			//��]�x
	VertexStyle			i_VertexStyle	//���̌`
);
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
***********************************************************/
LineEffect::LineEffectGroup::LineEffectState::LineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
	const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle )
:m_vPos( i_vPos ),m_vSize( i_vSize ),m_vRot( i_vRot )
{

	m_VLState = new VertexLineState(pD3DDevice , 0 );
	m_VLState->SetVertex(pD3DDevice , i_VertexStyle , D3DPT_LINESTRIP );

}

/***************************************************************
struct LineEffect::LineEffectGroup	��`��
�p�r : ���G�t�F�N�g���Ǘ�����\����
***************************************************************/
/**************************************************************
LineEffect::LineEffectGroup::LineEffectGroup(
	float				i_fRotZSpeed,	//	��]���x
	float				i_fScaling		//	�g��k���̒l
	int					i_iLifeTime		//�o�����Ă��鎞��
);
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
**************************************************************/
LineEffect::LineEffectGroup::LineEffectGroup( float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime )
:m_fRotZSpeed( i_fRotZSpeed ) , m_fScale( i_fScaling ),m_iLifeTime( i_iLifeTime )
{
}

/**************************************************************
void LineEffect::LineEffectGroup::Move( 
	Command& i_Com		//�R�}���h
);
�p�r : ����
�߂�l : �Ȃ�
**************************************************************/
void LineEffect::LineEffectGroup::Move( Command& i_Com )
{
	float fRotZSpeed	= m_fRotZSpeed	 ;		//	��]���x
	DWORD dwDownColor	= 0x00000D2B	 ;		//	�F�̕ψ�
	vector<LineEffectState*>::size_type i	= 0 ;
	vector<LineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->m_vRot.z	+= fRotZSpeed	;
		m_StateVec[ i ]->m_vSize.x	+= m_fScale		;
		m_StateVec[ i ]->m_vSize.y	+= m_fScale		;
		m_StateVec[ i ]->m_Matrix = CreateMatrix( m_StateVec[i]->m_vPos , m_StateVec[i]->m_vSize , m_StateVec[i]->m_vRot );

		m_StateVec[ i ]->m_VLState->SetDownColor( dwDownColor );
		fRotZSpeed *= -1 ;	//��]�����𔽓]������
	}

	m_iLifeTime-- ;
	
}

/*************************************************************
void LineEffect::LineEffectGroup::Draw( 
	LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
)
�p�r : 
�߂�l : 
*************************************************************/
void LineEffect::LineEffectGroup::Draw( LPDIRECT3DDEVICE9 pD3DDevice )
{
	vector<LineEffectState*>::size_type i	= 0 ;
	vector<LineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->m_VLState->Draw(pD3DDevice , m_StateVec[ i ]->m_Matrix ) ;
	}

}


/******************************************************************
LineEffect::LineEffect() ;
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
******************************************************************/
LineEffect::LineEffect( )
{
}

/******************************************************************
LineEffect::~LineEffect();
�p�r : �f�X�g���N�^
�߂�l : �Ȃ�
******************************************************************/
LineEffect::~LineEffect()
{
}

/******************************************************************
void LineEffect::AddLineEffect(
	LPDIRECT3DDEVICE9 pD3DDevice	,	//�f�o�C�X
	const D3DXVECTOR3&	i_vPos		,	//�ʒu
	const D3DXVECTOR3&	i_vSize		,	//�傫��
	const D3DXVECTOR3&	i_vRot		,	//��]�x
	VertexStyle			i_VertexStyle	//���̌`
	float				i_fRotZSpeed,	//	��]���x
	float				i_fScaling	,	//	�g��k���̒l
	int					i_iLifeTime	,	//�o�����Ă��鎞��
	int					i_iLineNumber	//���̖{��
);
�p�r : ���C���G�t�F�N�g�̒ǉ�
�߂�l : �Ȃ�
******************************************************************/
void LineEffect::AddLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize ,
							   const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ,float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime , int i_iLineNumber)
{

	D3DXVECTOR3 vRot			= i_vRot	;					//��]�p�̍�Ɨ̈�
	float		fRotZ			= 15.0f	/ i_iLineNumber;	//�G�t�F�N�g���ɂ��炷��]�x��
	const float	fSize			= 0.25f		;					//�������̑傫�������炷�p�̕ϐ�

	LineEffectGroup* LEG = new LineEffectGroup( i_fRotZSpeed , i_fScaling , i_iLifeTime);

	//�G�t�F�N�g�̐������[�v
	for(int i = 0 ; i < i_iLineNumber ; i++ ){

		D3DXVECTOR3 wvSize = i_vSize + D3DXVECTOR3( (i * fSize) / ((i_iLineNumber - i) * fSize ) , (i * fSize) / ((i_iLineNumber - i) * fSize) , 0.0f )  ; 

		LEG->m_StateVec.push_back(new LineEffectGroup::LineEffectState(
										pD3DDevice , i_vPos , wvSize , vRot ,
										i_VertexStyle ) );
		vRot.z += fRotZ ;
	}

	m_StateVec.push_back( LEG );
}

/******************************************************************
virtual void LineEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	Command&				i_Com			//�R�}���h
) ;
�p�r : �V�[���̕ω�
�߂�l : �Ȃ�
******************************************************************/
void LineEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	vector<LineEffectGroup*>::size_type i	= 0 ;
	vector<LineEffectGroup*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->Move(i_Com) ;
	}

}

/*****************************************************************
 virtual void LineEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	Command					i_Com			//�R�}���h
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
*****************************************************************/
void LineEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{
	vector<LineEffectGroup*>::iterator it ;
	vector<LineEffectGroup*>::iterator end	= m_StateVec.end() ;

	for( it = m_StateVec.begin() ; it != end ; ){

		//�`�揈��
		(*(it))->Draw(pD3DDevice);

		if((*(it))->m_iLifeTime > 0 ){
	
			it++ ;

		//�������C�t�^�C�����Ȃ��Ȃ�����폜����
		}else{

			it	= m_StateVec.erase( it );
			end = m_StateVec.end() ;
		}

	}

}

/***************************************************************************
D3DXVECTOR3 LineEffect::getPos(
	int i_iVecNum	//�z����ł̓Y����
) ;
�p�r : �ʒu��Ԃ�
�߂�l : �w�肳�ꂽ�Y������Object�̈ʒu��Ԃ�
***************************************************************************/
D3DXVECTOR3 LineEffect::getPos( int i_iVecNum )
{
	int iMaxSize = m_StateVec.size() ;
	if( i_iVecNum > iMaxSize ) i_iVecNum %= iMaxSize ;

	return m_StateVec[ i_iVecNum ]->m_StateVec[ 0 ]->m_vPos ;
}

/**************************************************************************
const int LineEffect::getObjectVecSize() const ;
�p�r : �I�u�W�F�N�g�̐���c������
�߂�l : ���̃N���X�ŊǗ����Ă���Object�̐�
**************************************************************************/
const int LineEffect::getObjectVecSize() const
{
	return m_StateVec.size() ;
}

/*******************************************************************
class NameLineEffect : public Object ��`��
�p�r :	���O�̐��G�t�F�N�g�̕`��
*******************************************************************/

/*******************************************************************
class NameLineEffect::NameLineEffectState  ��`��
�p�r : ���G�t�F�N�g���Ǘ�����X�e�[�^�X
*******************************************************************/
/***********************************************************
NameLineEffect::NameLineEffectGroup::NameLineEffectState::NameLineEffectState(
	LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
	const D3DXVECTOR3&	i_vPos		,	//�ʒu
	const D3DXVECTOR3&	i_vSize		,	//�傫��
	const D3DXVECTOR3&	i_vRot			//��]�x
	VertexStyle			i_VertexStyle	//���̌`
);
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
***********************************************************/
NameLineEffect::NameLineEffectState::NameLineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
	const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle )
:m_vPos( i_vPos ),m_vSize( i_vSize )
{

	m_pVLState = new VertexLineState(pD3DDevice , 0 );
	m_pVLState->SetVertex(pD3DDevice , i_VertexStyle , D3DPT_LINESTRIP );

	m_pPointSprite = new PointSpriteVertex( g_vZero , 0xFFFFFFFF) ;
}

/************************************************************
NameLineEffect::NameLineEffectState::~NameLineEffectState();
�p�r : �f�X�g���N�^
�߂�l : �Ȃ�
************************************************************/
NameLineEffect::NameLineEffectState::~NameLineEffectState()
{
	SafeDelete( m_pVLState );
	SafeDelete( m_pPointSprite );
}

/**************************************************************
void NameLineEffect::NameLineEffectState::Move( 
	Command& i_Com		//�R�}���h
);
�p�r : ����
�߂�l : �Ȃ�
**************************************************************/
void NameLineEffect::NameLineEffectState::Move( Command& i_Com )
{
	m_Matrix = CreateMatrix( m_vPos , m_vSize , g_vZero ) ;
	D3DXVECTOR3 vOffsetPos = m_vSize ;
	vOffsetPos.x *=  0.9f	;
	vOffsetPos.y += vOffsetPos.y * 0.5f ;
	m_pPointSprite->m_vPos = m_vPos + vOffsetPos ;
}

/******************************************************************
NameLineEffect::NameLineEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename			//�摜�̃t�@�C����
	float				i_fSize				//�G�t�F�N�g�̑傫��
) ;
�p�r : �R���X�g���N�^
�߂�l : �Ȃ�
******************************************************************/
NameLineEffect::NameLineEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,float i_fSize)
:ThreeDimensionsEffect( pD3DDevice , i_filename , 0x00000000 , i_fSize ),m_iDrawVerticesNumber(0)
{
	ZeroMemory(m_DrawVertices , sizeof(m_DrawVertices) )	;
				

}

/******************************************************************
NameLineEffect::~NameLineEffect();
�p�r : �f�X�g���N�^
�߂�l : �Ȃ�
******************************************************************/
NameLineEffect::~NameLineEffect()
{
}

/******************************************************************
void NameLineEffect::AddNameLineEffect(
	LPDIRECT3DDEVICE9 pD3DDevice	,	//�f�o�C�X
	const D3DXVECTOR3&	i_vPos		,	//�ʒu
	const D3DXVECTOR3&	i_vSize		,	//�傫��
);
�p�r : ���C���G�t�F�N�g�̒ǉ�
�߂�l : �Ȃ�
******************************************************************/
void NameLineEffect::AddNameLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize )
{
	m_StateVec.push_back(new NameLineEffectState(pD3DDevice , i_vPos , i_vSize ,g_vZero ,VS_NameLine ) );
}

/******************************************************************
virtual void NameLineEffect::Transform(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	Command&				i_Com			//�R�}���h
) ;
�p�r : �V�[���̕ω�
�߂�l : �Ȃ�
******************************************************************/
void NameLineEffect::Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com)
{
	vector<NameLineEffectState*>::size_type i	= 0 ;
	vector<NameLineEffectState*>::size_type end	= m_StateVec.size() ;

	for( i = 0 ; i < end ; i++){
		m_StateVec[ i ]->Move(i_Com) ;
		m_DrawVertices[m_iDrawVerticesNumber] = *( m_StateVec[ i ]->m_pPointSprite ) ;
		m_iDrawVerticesNumber++ ;
	}

}

/*****************************************************************
 virtual void NameLineEffect::Draw(
	LPDIRECT3DDEVICE9		pD3DDevice	,	//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
	Command					i_Com			//�R�}���h
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
*****************************************************************/
void NameLineEffect::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
							const CONTROLER_STATE* pCntlState,Command& i_Com )
{

	vector<NameLineEffectState*>::iterator it ;
	vector<NameLineEffectState*>::iterator end	= m_StateVec.end() ;


	//���̕`��
	for( it = m_StateVec.begin() ; it != end ; ){

		//�`�揈��
		(*(it))->m_pVLState->Draw(pD3DDevice,(*it)->m_Matrix);
		//if((*(it))->m_iLifeTime > 0 ){
	
		//	it++ ;

		////�������C�t�^�C�����Ȃ��Ȃ�����폜����
		//}else{

		//	it	= m_StateVec.erase( it );
		//	end = m_StateVec.end() ;
		//}
		it++ ;

	}
	D3DXMATRIX mMatrix ;
	D3DXMatrixIdentity( &mMatrix );
	pD3DDevice->SetTransform( D3DTS_WORLD , &mMatrix );

	//���O�̕`��
	//�����_�[�X�e�[�g��ύX�����邽�߂̃N���X��錾
	DeviceRenderState drs = DeviceRenderState() ;
	drs.SetDeviceRenderState(D3DRS_LIGHTING, FALSE );	//���C�e�B���O���[�h��FALSE
	drs.ChangeRS_PointSprite(m_fEffectSize);
	drs.ChangeRS_ALPHABLENDENABLE_Black();
	drs.ChangeRenderState(pD3DDevice);
	//�p�[�e�B�N���̕`��
	VerticesRender(pD3DDevice,m_DrawVertices,m_iDrawVerticesNumber);
	//�����_�[�X�e�[�g�̕ύX
	drs.ChangeRenderState(pD3DDevice);

	//���_�����[���ɖ߂�
	m_iDrawVerticesNumber = 0 ;
	//���_�f�[�^�̔z������Z�b�g����
	ZeroMemory( m_DrawVertices , sizeof( m_DrawVertices ));


}

/****************************************************************
void NameLineEffect::setPos( 
	const vector<D3DXVECTOR3*>& i_vPosVec //�w�肵�����|�W�V�����̔z��
);
�p�r : �n���ꂽ�|�W�V�����̐������ʒu���Z�b�g����
�߂�l : �Ȃ�
****************************************************************/
void NameLineEffect::setPos( const D3DXVECTOR3& i_vPosVec )
{

	!m_StateVec.empty() && ( m_StateVec[0]->m_vPos  = i_vPosVec ) ;
}

}
