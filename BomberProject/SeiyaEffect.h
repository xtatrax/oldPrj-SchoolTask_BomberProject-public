/********************************************************************
Effect.h

class Object ��-class Effect �錾����-class ThreeDimensionsEffect		�錾��
			  |						|		��class BlockBreakEffect	�錾��
			  |						��class TwoDimensionsEffect			�錾��
			  |								
			�@|-class XMeshEffect	�錾��
			  |
			  ��class LineEffect	�錾��
********************************************************************/
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace seiyasource{
/**************************************************************************
inline D3DXMATRIX CreateMatrix(
	const D3DXVECTOR3& i_vPos	,	//�ʒu
	const D3DXVECTOR3& i_vSize	,	//�傫��
	const D3DXVECTOR3& i_vRot		//��]
	);
�p�r : �ʒu�A�傫���A��]����}�g���b�N�X���쐬����
�߂�l : �Ȃ�
**************************************************************************/
inline D3DXMATRIX CreateMatrix(const D3DXVECTOR3& i_vPos , const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot)
{
	D3DXMATRIX	mTrans , mScale , mRot ;
	D3DXMatrixTranslation( &mTrans , i_vPos.x , i_vPos.y , i_vPos.z );
	D3DXMatrixScaling( &mScale , i_vSize.x , i_vSize.y , i_vSize.z ) ;
	D3DXMatrixRotationYawPitchRoll( &mRot , D3DXToRadian( i_vRot.y ) ,D3DXToRadian( i_vRot.x ) , D3DXToRadian( i_vRot.z ) );

	return mScale * mRot * mTrans ;

}

//LineEffect�p�̌`���w�肷���
enum VertexStyle {
	VS_Triangle ,	//�O�p�`
	VS_Square	,	//�l�p�`
	VS_Circle	,	//��
	VS_Cross	,	//�\��
	VS_NameLine	,	//�l�[���`��p�̐�
	VS_Line			//����
};
/****************************************************************************
class DeviceRenderState �錾��
�p�r : �����_�[�X�e�[�g�̕ύX���g�p����N���X
***************************************************************************/

class DeviceRenderState{
	//�����_�[�X�e�[�g�ݒ�p�\����
	struct RENDERSTATE_PARAM 
	{
		D3DRENDERSTATETYPE	type ;
		DWORD				value ;
		/*********************************************************************
		RENDERSTATE_PARAM(
			const D3DRENDERSTATETYPE i_type,
			const DWORD i_value
			)
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		**********************************************************************/
		RENDERSTATE_PARAM(const D3DRENDERSTATETYPE i_type,const DWORD i_value)
			:type(i_type),value(i_value){}

	};
	
	//�ύX������RenderState�̒l������
	vector<RENDERSTATE_PARAM> m_RPVec ;

public:
/***********************************************************
void ChangeRenderState(
	const LPDIRECT3DDEVICE9 i_pDevice,	//�f�o�C�X
	);
�p�r : �����_�[�X�e�[�g�ύX
�߂�l : �Ȃ�
***********************************************************/
void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice)
{

	vector<RENDERSTATE_PARAM>::size_type RPsz = m_RPVec.size();
	for(vector<RENDERSTATE_PARAM>::size_type i = 0 ; i < RPsz ; i++){
		DWORD dwSaveState;

		i_pDevice->GetRenderState(m_RPVec[i].type,&dwSaveState);		//���݃X�e�[�^�X�����炤
		i_pDevice->SetRenderState(m_RPVec[i].type,m_RPVec[i].value);	//�w�肵���X�e�[�^�X�ɕύX����

		m_RPVec[i].value = dwSaveState ;								//�ύX�O�̃X�e�[�^�X������
	}
}


/***********************************************************************
void ChangeRS_PointSprite(
	const float					i_fSize  //�|�C���g�X�v���C�g�̃T�C�Y
) ;
�p�r: �|�C���g�X�v���C�g��`��ł���悤�Ƀ����_�[�X�e�[�g��ύX
�߂�l: �Ȃ�
************************************************************************/
void ChangeRS_PointSprite(const float i_fSize)
{
	// �|�C���g�X�v���C�g�̐ݒ�
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSPRITEENABLE	,TRUE				)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSCALEENABLE	,TRUE				)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_POINTSIZE			,*(DWORD*)&i_fSize	)	);

}

/***********************************************************************
void ChangeRS_ALPHABLENDENABLE_Black() ;
�p�r: ���Z�������ł���悤�Ƀ����_�[�X�e�[�g��ύX
�߂�l: �Ȃ�
************************************************************************/
void ChangeRS_ALPHABLENDENABLE_Black()
{
	//���Z�����ɐݒ�
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_ALPHABLENDENABLE		,TRUE					)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_SRCBLEND				,D3DBLEND_ONE			)	);
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_DESTBLEND				,D3DBLEND_ONE			)	);

	//�d�Ȃ��Ă��Ă�z�o�b�t�@�̕\��������
	m_RPVec.push_back(RENDERSTATE_PARAM( D3DRS_ZWRITEENABLE			, FALSE			) );	

}

/***********************************************************************
void ChangeRS_ALPHABLENDENABLE_Skeleton() ;
�p�r: �����ɂȂ�悤�Ƀ����_�[�X�e�[�g��ύX
�߂�l: �Ȃ�
************************************************************************/
void ChangeRS_ALPHABLENDENABLE_Skeleton()
{
	//����
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_ALPHABLENDENABLE		,TRUE					) );
	m_RPVec.push_back(RENDERSTATE_PARAM(D3DRS_DESTBLEND				, D3DBLEND_INVSRCALPHA	) );
	m_RPVec.push_back(RENDERSTATE_PARAM( D3DRS_ZWRITEENABLE			, FALSE					) );	

}

/***********************************************************************
void SetDeviceRenderState(
		const D3DRENDERSTATETYPE i_type,
		const DWORD i_value
		);
�p�r : �����_�[�X�e�[�g�̕ύX���e��m_RSVec�ɓ����
�߂�l : �Ȃ�
***********************************************************************/
void SetDeviceRenderState(const D3DRENDERSTATETYPE i_type,const DWORD i_value)
{
	m_RPVec.push_back(RENDERSTATE_PARAM(i_type, i_value ) );
}


};

/*****************************************************************
static Vertex
�p�r:3D���_���_�f�[�^ 
******************************************************************/
struct Vertex
{
D3DXVECTOR3 m_vPos ;	//�Q�[����ʂł̈ʒu
DWORD		m_dwColor ;	//�F
D3DXVECTOR2 m_vTex ;	//�ǂݍ��݉摜�̈ʒu

public :

/***************************************************************
vertex()
�p�r�F�����t���R���X�g���N�^
�߂�l:�Ȃ�
****************************************************************/
Vertex()
:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_dwColor(0xFFFFFFFF),m_vTex(D3DXVECTOR2(0.0f,0.0f)){}

/***************************************************************
vertex( 
	D3DXVECTOR3 i_vPos ,	//�Q�[����ʂł̈ʒu
	DWORD		i_dwColor,  //�F
	D3DXVECTOR2 i_vTex		//�ǂݍ��݉摜�̈ʒu
)
�p�r�F�����t���R���X�g���N�^
�߂�l:�Ȃ�
****************************************************************/
Vertex(	D3DXVECTOR3 i_vPos, DWORD i_dwColor, D3DXVECTOR2 i_vTex )
	:m_vPos(i_vPos),m_dwColor(i_dwColor),m_vTex(i_vTex){}

/***************************************************************
~Vertex()
�p�r�F�f�X�g���N�^
�߂�l:�Ȃ�
****************************************************************/
~Vertex(){}

/**********************************************************************
static DWORD Vertex::getFVF()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: FVF
**********************************************************************/
static DWORD Vertex::getFVF()
{
	return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
}
/**********************************************************************
static DWORD Vertex::getSize()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: Vertex�̃f�[�^��
**********************************************************************/
static DWORD Vertex::getSize()
{
	return sizeof(Vertex) ;
}

};

/*****************************************************************************
struct VertexLineState	�錾��
�p�r :  3�������W��̒��_�`�揈�����s��
******************************************************************************/
struct VertexLineState
{
	D3DPRIMITIVETYPE		m_PrimitiveType				;	//�ǂ̕`������邩
	int						m_iDrawPrimitiveVertexNum	;	//DrawPrimitive�Ɏg�p���钸�_��
	Vertex*					m_pVertex					;	//���_�f�[�^�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer				;	//�o�b�t�@
	LPDIRECT3DTEXTURE9*		m_pTexture					;	//�e�N�X�`��
	int						m_iVertexNum				;	//���_��

	/******************************************************************************
	VertexLineState()
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	VertexLineState();

	/******************************************************************************
	VertexLineState::VertexLineState(
			LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X 
			const wchar_t* i_pFilename		//�t�@�C����
		)
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	VertexLineState(LPDIRECT3DDEVICE9 pD3DDevice , const wchar_t* i_pFilename );

	/******************************************************************************
	~VertexLineState()
	�p�r : �f�X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	~VertexLineState();

	/******************************************************************************
	void SetVertex(
		LPDIRECT3DDEVICE9	pD3DDevice ,	//�f�o�C�X
		VertexStyle			i_Style			//Object�̌`
		D3DPRIMITIVETYPE	i_PrimitiveType	//�`����@
	);
	�p�r : �����ɉ������`�����
	�߂�l : �Ȃ�
	******************************************************************************/
	void SetVertex( LPDIRECT3DDEVICE9 pD3DDevice , VertexStyle i_Style  , D3DPRIMITIVETYPE	i_PrimitiveType) ;

	/******************************************************************************
	void SetDownColor( 
		DWORD i_dwColor	//�Z�b�g�������F
	) ;
	�p�r : �F�̕ύX
	�߂�l : �Ȃ�
	******************************************************************************/
	void SetDownColor( DWORD i_dwColor ) ;

	/******************************************************************************
	void setVertexPos(
		vector<D3DXVECTOR3*> i_vPosVec	�ύX������Line�̃|�W�V����
	);
	�p�r : ���_�̈ʒu��ύX����
	�߂�l : �Ȃ�
	******************************************************************************/
	void setVertexPos( vector<D3DXVECTOR3*> i_vPosVec );

	/******************************************************************************
	void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X
		const D3DXMATRIX& i_Matrix		//�`�悵�����v���[�g�̔z��
		)
	�p�r : �����`�̃v���[�g��`��
	�߂�l : �Ȃ�
	******************************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix ) ;

};

/*****************************************************************
static Vertex
�p�r:2D���_�̒��_�f�[�^ 
******************************************************************/
struct Vertexrhw{
D3DXVECTOR3 m_vPos ;	//�Q�[����ʂł̈ʒu
float		m_float		;
DWORD		m_dwColor ;	//�F
D3DXVECTOR2 m_vTex ;	//�ǂݍ��݉摜�̈ʒu

public :

/***************************************************************
VertexBackGround()
�p�r�F�R���X�g���N�^
�߂�l:�Ȃ�
****************************************************************/
Vertexrhw(){}

/***************************************************************
VertexBackGround( 
	D3DXVECTOR3 i_vPos ,	//�Q�[����ʂł̈ʒu
	DWORD		i_dwColor,  //�F
	D3DXVECTOR2 i_vTex		//�ǂݍ��݉摜�̈ʒu
)
�p�r�F�����t���R���X�g���N�^
�߂�l:�Ȃ�
****************************************************************/
Vertexrhw(	D3DXVECTOR3 i_vPos, DWORD i_dwColor, D3DXVECTOR2 i_vTex )
	:m_vPos(i_vPos),m_float(1.0f),m_dwColor(i_dwColor),m_vTex(i_vTex){}

/****************************************************************
~Vertexrhw()
�p�r : �f�X�g���N�^ 
�߂�l : �Ȃ�
****************************************************************/
~Vertexrhw()
{
}

/**********************************************************************
static DWORD getRHWFVF()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: FVF
**********************************************************************/
static DWORD getRHWFVF()
{
	return  D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
}
/**********************************************************************
static DWORD getRHWSize()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: Vertexrhw�̃f�[�^��
**********************************************************************/
static DWORD getRHWSize()
{
	return sizeof( Vertexrhw ) ;
}

};


/******************************************************************************
struct VertexRHWState	�錾��
�p�r : �����`�̃e�N�X�`����`��
******************************************************************************/
struct VertexrhwState
{
	static const int		MAXDEGREES	= 360			;	//�f�B�O���p�̍ő吔
	static const int		VERTEXNUM	= 4				;

	Vertexrhw*				m_pVertexrhw				;	//���_�f�[�^�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer				;	//�o�b�t�@
	D3DXVECTOR2				m_vTexSize					;	//Rect�g�p��1���̑傫��

	/******************************************************************************
	VertexState::VertexrhwState()
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	VertexrhwState();

	/******************************************************************************
	VertexState::VertexrhwState(
			LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X 
		)
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	VertexrhwState(LPDIRECT3DDEVICE9 pD3DDevice );

	/******************************************************************************
	~VertexrhwState()
	�p�r : �f�X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************************/
	~VertexrhwState();

	/******************************************************************************
	void VertexTransForm(
		const D3DXVECTOR3&	i_vPos  ,	//�ʒu
		const D3DXVECTOR3&	i_vSize ,	//�傫��
		int 				i_fRotZ		//��]
		);
	�p�r : �e�X�e�[�^�X����ʒu��ݒ肷��
	�߂�l : �Ȃ�
	******************************************************************************/
	void VertexTransForm(const D3DXVECTOR3& i_vPos , const D3DXVECTOR3& i_vSize , int i_iRotZ );

	/******************************************************************************
	void VertexRect(
		const D3DXVECTOR2&	i_vTexMaxSize ,	//�e�N�X�`���S�̂̑傫��
		const D3DXVECTOR2&	i_vSetTexSize ,	//�e�N�X�`���̕`�悵�����͈�(�傫��)
		int					i_iRectNum		//���N�g�̈ʒu
	);
	�p�r : ���̃e�N�X�`������`�悷��͈͂��w�肷��
	�߂�l : �Ȃ�
	******************************************************************************/
	void VertexRect(const D3DXVECTOR2& i_vTexMaxSize , const D3DXVECTOR2& i_vSetTexSize , int i_iRectNum );

	/******************************************************************************
	void SetColor( 
		DWORD i_dwColor	//�Z�b�g�������F
	) ;
	�p�r : �F�̕ύX
	�߂�l : �Ȃ�
	******************************************************************************/
	void SetColor( DWORD i_dwColor ) ;

	/*****************************************************************************
	void UpDate()
	�p�r : �f�[�^�̍X�V
	�߂�l : �Ȃ�
	*****************************************************************************/
	void UpDate() ; 

	/******************************************************************************
	void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice ,	//�f�o�C�X
		)
	�p�r : �����`�̃v���[�g��`��
	�߂�l : �Ȃ�
	******************************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice ) ;

};


/*********************************************************************
class Effect : public Object	�錾��
�p�r : ���o�p�G�t�F�N�g�̌��N���X
*********************************************************************/
class Effect //: public Object
{
protected:
	/*********************************************************************
	clear()
	�p�r : �폜����
	�߂�l: �Ȃ�
	*********************************************************************/
	void clear() ;

	float				m_fEffectSize				;	//�G�t�F�N�g�̑傫��
	LPDIRECT3DTEXTURE9	m_pTexture					;	// �e�N�X�`��
	static const int	m_iVerticesMaxSize = 3500	;	//��̃p�[�e�B�N���̍ő�`�搔

public:
/*********************************************************************
Effect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
*********************************************************************/
Effect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

/*********************************************************************
~Effect()
�p�r: �f�X�g���N�^
�߂�l: �Ȃ�
*********************************************************************/
~Effect();

};


/*********************************************************************
class ThreeDimensionsEffect : public Effect	�錾��
�p�r : 3�������W�p�G�t�F�N�g�̃N���X
*********************************************************************/
class ThreeDimensionsEffect : public Effect
{
protected:
	/*********************************************************************
	struct PointSpriteVertex
	�p�r : �p�[�e�B�N���̒��_�f�[�^
	*********************************************************************/
	struct PointSpriteVertex
	{
		D3DXVECTOR3 m_vPos ;		//���_�̈ʒu
		//�F�̋��p��
		union	{
			DWORD	m_dwColor ;
			struct {
				BYTE	b, g, r, a ;
			}m_Color ;
		};
		/*********************************************************************
		PointSpriteVertex();
		�p�r : �f�t�H���g�R���X�g���N�^
		�߂�l : �Ȃ�
		*********************************************************************/
		PointSpriteVertex()
			:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_dwColor(0xFFFFFFFF){}

		/*********************************************************************
		PointSpriteVertex(
				const D3DXVECTOR3& i_vPos,	//�ʒu
				DWORD i_dwColor				//�F
				);
		�p�r : �����t���R���X�g���N�^
		�߂�l : �Ȃ�
		*********************************************************************/
		PointSpriteVertex(  const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			:m_vPos(i_vPos),m_dwColor(i_dwColor){}

		/*********************************************************************
		PointSpriteVertex(
				const D3DXVECTOR3&	i_vPos,		//�ʒu
				BYTE				i_byBlue,	//�F
				BYTE				i_byGreen,	//�ΐF
				BYTE				i_byRed,	//�ԐF
				BYTE				i_byAlpha	//�����x
				);
		�p�r : �����t���R���X�g���N�^
		�߂�l : �Ȃ�
		*********************************************************************/
		PointSpriteVertex(  const D3DXVECTOR3& i_vPos,
			BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha) ;

		/*********************************************************************
		void setState(
			const D3DXVECTOR3& i_vPos,
			DWORD i_dwColor
			) ;
		�p�r : �X�e�[�^�X������
		�߂�l : �Ȃ�
		*********************************************************************/
		void setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor) ;
	};

public:
	/**********************************************************************
	ThreeDimensionsEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename			//�摜�̃t�@�C����
		DWORD				i_Decolorisation,	//���������F
		float				i_fSize				//�G�t�F�N�g�̑傫��
		)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	*********************************************************************/
	ThreeDimensionsEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize);

	/*********************************************************************
	~ThreeDimensionsEffect()
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	*********************************************************************/
	~ThreeDimensionsEffect(){}

	/*********************************************************************
	void AddThreeDimensionsEffectt(
					const D3DXVECTOR3&	i_vSize,			//�傫��
					const D3DXVECTOR3&	i_vPos,				//�ʒu
					const D3DXVECTOR3&	i_vDir,				//�ړ�����
					float				i_fSpeed			//����
					BYTE				i_byBlue	= 0xFF,	//�F
					BYTE				i_byGreen	= 0xFF,	//�ΐF
					BYTE				i_byRed		= 0xFF,	//�ԐF
					BYTE				i_byAlpha	= 0xFF	//�����x
					);
	�p�r: �e�G�t�F�N�g�I�u�W�F�N�g�̍쐬
	�߂�l: �Ȃ�
	************************************************************************/
	void AddThreeDimensionsEffect(const D3DXVECTOR3& i_vSize,const D3DXVECTOR3& i_vPos,const D3DXVECTOR3& i_vDir, float i_fSpeed,
				   BYTE i_byBlue = 0xFF, BYTE i_byGreen = 0xFF, BYTE i_byRed = 0xFF, BYTE i_byAlpha = 0xFF);


	/*********************************************************************
	void VerticesRender(
			LPDIRECT3DDEVICE9 pD3DDevice				//�f�o�C�X
			const PointSpriteRHWVertex* pPSRHWVertex	//�o�[�e�b�N�X�̔z��
			);
	�p�r : �`�揈��
	�߂�l : �Ȃ�
	*********************************************************************/
	void VerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteVertex* pPSVertex,unsigned int VertexSize) ;

	/*********************************************************************
	static DWORD getSPSize()
	�p�r:�A�N�Z�b�T(�Q�b�^�[)
	�߂�l: 3�����p�p�[�e�B�N����Vertex�̃f�[�^��
	*********************************************************************/
	DWORD getSPSize()
	{
		return sizeof(PointSpriteVertex);
	}
	/*********************************************************************
	static DWORD getSPFVF()
	�p�r:�A�N�Z�b�T(�Q�b�^�[)
	�߂�l: 3�����p�p�[�e�B�N����FVF
	*********************************************************************/
	DWORD	getSPFVF()
	{
		return D3DFVF_XYZ | D3DFVF_DIFFUSE ;	
	}

};


/***********************************************************
class BreakEffect : public ThreeDimensionsEffect
�p�r : �j�󎞂̃G�t�F�N�g
***********************************************************/
class BreakEffect : public ThreeDimensionsEffect
{

	PointSpriteVertex	m_DrawVertices[m_iVerticesMaxSize]	;	//�`��p���_�̔z��
	int					m_iDrawVerticesNumber				;	//���v�̒��_�f�[�^�����J�E���g����ϐ�

	/***********************************************************
	struct EffectState
	�p�r : ���_�f�[�^��ύX���邽�߂̍\����
	***********************************************************/
	struct EffectState
	{
		int						m_iLifeTime	;	//��юU���Ă��鎞��

		//�G�t�F�N�g��̃p�����[�^
		struct EffectParam{
			D3DXVECTOR3				m_vDir		;	//����
			float					m_fSpeed	;	//�X�s�[�h

		/*******************************************************
		EffectParam(
			const D3DXVECTOR3&	i_vDir ,		//����
			const D3DXVECTOR3&	i_fSpeed,		//�X�s�[�h
			)
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		*******************************************************/
		EffectParam(const D3DXVECTOR3& i_vDir , float i_fSpeed)
			:m_vDir(i_vDir),m_fSpeed(i_fSpeed){}
		};

		list<EffectParam>		m_EffectParams	;	//���_�f�[�^�̃p�����[�^
		list<PointSpriteVertex>	m_Vertices		;	//���_�f�[�^

		/*******************************************************
		EffectState(
			int					i_iVertexSize,		//���_�f�[�^�̐�
			float				i_vPos,				//�ʒu
			)
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		*******************************************************/
		EffectState(int i_iVertexSize, const D3DXVECTOR3& i_vPos);

		/*****************************************************************
		bool Move(
			Command				i_Com			//�R�}���h
		)
		�p�r : Particle�̓������s���폜�����̏ꍇ��true��Ԃ�
		�߂�l : �Ȃ�
		*****************************************************************/
		bool Move( Command& i_Com ) ; 
	};

	list<EffectState*>			m_Statelist ;	// �X�e�[�^�X�ύX�p�̔z��

public:
	/**********************************************************************
	BreakEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename,			//�摜�̃t�@�C����
		DWORD				i_Decolorisation,	//���������F
		float				i_fSize				//�G�t�F�N�g�̑傫��
		)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	BreakEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~BreakEffect()
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	~BreakEffect(){}

	/***********************************************************************
	void AddBreakEffect(
					const D3DXVECTOR3& i_vPos,	//�ʒu
					);
	�p�r: �u���b�N�j�󎞂̃G�t�F�N�g�I�u�W�F�N�g�̍쐬
	�߂�l: �Ȃ�
	************************************************************************/
	void AddBreakEffect(const D3DXVECTOR3& i_vPos);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
		const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
		vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
		Command&				i_Com			//�R�}���h
	) ;
	�p�r : �V�[���̕ω�
	�߂�l : �Ȃ�
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
		const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
		Command i_Com						//�R�}���h
	 );
	 �p�r: �I�u�W�F�N�g��`��
	 �߂�l: �Ȃ��B
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );
};

/***********************************************************
class BossHitDownEffect : public ThreeDimensionsEffect
�p�r : �{�X���_���[�W���󂯂�Ƃ��̃G�t�F�N�g
***********************************************************/
class BossHitDownEffect : public ThreeDimensionsEffect
{
	/***********************************************************
	struct BossHitDownEffectState
	�p�r : ���_�f�[�^��ύX���邽�߂̍\����
	***********************************************************/
	struct BossHitDownEffectState
	{
		int					m_iLife			; //�\������
		float				m_fSize			; //�傫��
		PointSpriteVertex	m_Vertex		; //���_�f�[�^

		/*******************************************************
		BossHitDownEffectState(
			const D3DXVECTOR3&	i_vPos,		//�ʒu
			float				i_fSize,	//�傫��
			int					i_iLife,	//�\������
			DWORD				i_dwColor	//�F
			)
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		*******************************************************/
		BossHitDownEffectState( const D3DXVECTOR3& i_vPos,float i_fSize , int i_iLife, DWORD i_dwColor);

		/*****************************************************************
		bool Move()
		�p�r : Particle�̓������s���폜�����̏ꍇ��true��Ԃ�
		�߂�l : �Ȃ�
		*****************************************************************/
		bool Move() ;
	};

	list<BossHitDownEffectState*>			m_Statelist ;	// �X�e�[�^�X�ύX�p�̔z��

public:
	/**********************************************************************
	BossHitDownEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename,			//�摜�̃t�@�C����
		DWORD				i_Decolorisation,	//���������F
		float				i_fSize				//�G�t�F�N�g�̑傫��
		)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	BossHitDownEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~BossHitDownEffect()
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	~BossHitDownEffect(){}

	/***********************************************************************
	void BossHitDownEffect::AddBossHitDownEffect(
					const D3DXVECTOR3&	i_vPos,			//�ʒu
					int					i_iLifeTime,	//�`�掞��
					DWORD				i_dxColor,		//�F
					Command&			i_Com			//�R�}���h
					);
	�p�r: �u���b�N�j�󎞂̃G�t�F�N�g�I�u�W�F�N�g�̍쐬
	�߂�l: �Ȃ�
	************************************************************************/
	void AddBossHitDownEffect(const D3DXVECTOR3& i_vPos,int i_iLifeTime,DWORD i_dxColor ,Command& i_Com ) ;

};

/***********************************************************
class RHWEffect : public Effect
�p�r : 2�����p�G�t�F�N�g
***********************************************************/
class RHWEffect : public Effect
{
protected:
	struct PointSpriteRHWVertex
	{
		D3DXVECTOR3 m_vPos ;
		float		m_fRhw	;
		union	{
			DWORD	m_dwColor ;
			struct {
				BYTE	b, g, r, a ;
			}m_Color ;
		};
		/***************************************************************
		PointSpriteRHWVertex();
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		***************************************************************/
		PointSpriteRHWVertex()
			:m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f)),m_fRhw(1.0f),m_dwColor(0xFFFFFFFF){}

		/***************************************************************
		PointSpriteRHWVertex(
				const D3DXVECTOR3& i_vPos,	//�ʒu
				DWORD i_dwColor				//�F
				);
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		***************************************************************/
		PointSpriteRHWVertex(  const D3DXVECTOR3& i_vPos, DWORD i_dwColor )
			:m_vPos(i_vPos),m_fRhw(1.0f),m_dwColor(i_dwColor){}

		/***************************************************************
		PointSpriteRHWVertex(
				const D3DXVECTOR3&	i_vPos,		//�ʒu
				BYTE				i_byBlue,	//�F
				BYTE				i_byGreen,	//�ΐF
				BYTE				i_byRed,	//�ԐF
				BYTE				i_byAlpha	//�����x
				);
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		***************************************************************/
		PointSpriteRHWVertex(  const D3DXVECTOR3& i_vPos,
			BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha)
			:m_vPos(i_vPos),m_fRhw(1.0f)
		{
			m_Color.b = i_byBlue	;
			m_Color.g = i_byGreen	;
			m_Color.r = i_byRed		;
			m_Color.a = i_byAlpha	;
		}

		/**************************************************************
		void setState(
			const D3DXVECTOR3& i_vPos,
			DWORD i_dwColor
			) ;
		�p�r : �X�e�[�^�X������
		�߂�l : �Ȃ�
		**************************************************************/
		void setState(const D3DXVECTOR3& i_vPos, DWORD i_dwColor) ;
	};
public:
/**********************************************************************
RHWEffect(
	LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
	const wchar_t*		i_filename,			//�摜�̃t�@�C����
	DWORD				i_Decolorisation,	//���������F
	float				i_fSize				//�G�t�F�N�g�̑傫��
	)
�p�r: �R���X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
RHWEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize);

/***********************************************************************
~RHWEffect()
�p�r: �f�X�g���N�^
�߂�l: �Ȃ�
***********************************************************************/
~RHWEffect(){}

/*********************************************************************
void RHWVerticesRender(
		LPDIRECT3DDEVICE9 pD3DDevice				//�f�o�C�X
		const PointSpriteRHWVertex* pPSRHWVertex	//�o�[�e�b�N�X�̔z��
		);
�p�r : �`�揈��
�߂�l : �Ȃ�
*********************************************************************/
void RHWVerticesRender(LPDIRECT3DDEVICE9 pD3DDevice,const PointSpriteRHWVertex* pPSRHWVertex,unsigned int VertexSize) ;


/**********************************************************************
static DWORD getSPRHWSize()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: �X�v���C�g�|�C���gRHW�pVertex�̃f�[�^��
**********************************************************************/
	DWORD getSPRHWSize()
	{
		return sizeof(PointSpriteRHWVertex);
	}
/**********************************************************************
static DWORD getSPRHWFVF()
�p�r:�A�N�Z�b�T(�Q�b�^�[)
�߂�l: �X�v���C�g�|�C���gRHW�pFVF
**********************************************************************/
	DWORD	getSPRHWFVF()
	{
		return D3DFVF_XYZRHW | D3DFVF_DIFFUSE ;	//�K�v�Ȓ��_���͍��W�ƐF�̃f�[�^���������Ă���
	}
};

/***********************************************************
class ScaleEffect : public RHWEffect
�p�r : �傫���̕ϓ�����G�t�F�N�g
***********************************************************/
class ScaleEffect : public RHWEffect
{
protected:

	PointSpriteRHWVertex* m_pPSVertexrhw ;

public:
	/**********************************************************************
	RHWEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename,			//�摜�̃t�@�C����
		const D3DXVECTOR3&	i_vPos			,	//�ʒu��ݒ�
		float				i_fSize				//�G�t�F�N�g�̑傫��
		)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	ScaleEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,
		const D3DXVECTOR3& i_vPos ,float i_fSize);

	/***********************************************************************
	~ScaleEffect()
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	~ScaleEffect() ;

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
		const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
		vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
		Command&				i_Com			//�R�}���h
	) ;
	�p�r : �V�[���̕ω�
	�߂�l : �Ȃ�
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
		const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
		Command i_Com						//�R�}���h
	 );
	 �p�r: �I�u�W�F�N�g��`��
	 �߂�l: �Ȃ��B
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

};

/***********************************************************
class ExtinguishEffect : public RHWEffect	�錾��
�p�r : ���Ŏ��̃G�t�F�N�g
***********************************************************/
class ExtinguishEffect : public RHWEffect
{
	
public:

	static const int	MAXDEGREES = 360 ;	//�f�B�O���p�̍ő吔

protected:
	float					m_fRadSinArray[MAXDEGREES] ;
	float					m_fRadCosArray[MAXDEGREES] ;

	PointSpriteRHWVertex	m_DrawVertices[m_iVerticesMaxSize]	;		//�`��p�z��
	int						m_iVerticesSize						;		//�`�撸�_�̐�

	/***********************************************************
	struct ExtinguishEffectState	�錾��
	�p�r : ���_�f�[�^��ύX���邽�߂̍\����
	***********************************************************/
	struct ExtinguishEffectState
	{
		float						m_fLangth	;	//���S����̋���
		D3DXVECTOR3					m_vCenter	;	//��юU��p�[�e�B�N���̒��S
		int  						m_iRad		;	//�p�x
		int 						m_iRadSpeed ;	//��]���鑬��
		float						m_fSpeed	;	//�X�s�[�h
		int							m_iLifeTime	;	//��юU���Ă��鎞��
		list<PointSpriteRHWVertex>	m_Vertices  ;	//���_�f�[�^

		/*******************************************************
		ExtinguishEffectState( 
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
		ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos, int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,DWORD i_dwColor );

		/*******************************************************
		ExtinguishEffectState( 
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
		ExtinguishEffectState(float i_fSpeed,const D3DXVECTOR3& i_vPos,int i_iRadSpeed , int i_iLifeTime ,int i_iParticleSize,BYTE i_byBlue, BYTE i_byGreen, BYTE i_byRed, BYTE i_byAlpha);

		/*****************************************************************
		bool Move(
			const float* i_fRadSinArray,	//Sin�̔z�������
			const float* i_fRadCosArray		//Cos�̔z�������
		)
		�p�r : Particle�̓������s���폜�����̏ꍇ��true��Ԃ�
		�߂�l : �Ȃ�
		*****************************************************************/
		bool Move(const float* i_fRadSinArray,const float* i_fRadCosArray) ; 
	};

	list<ExtinguishEffectState*>			m_Statelist ;	// �X�e�[�^�X�ύX�p�̔z��

public:
	/**********************************************************************
	ExtinguishEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename,			//�摜�̃t�@�C����
		DWORD				i_Decolorisation	//���������F
		float				i_fSize				//�G�t�F�N�g�̑傫��
		)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	ExtinguishEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,DWORD i_Decolorisation,float i_fSize) ;

	/***********************************************************************
	~ExtinguishEffect()
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***********************************************************************/
	~ExtinguishEffect(){}

	/***********************************************************************
	void AddExtinguishEffect(
					const D3DXVECTOR3,	i_vPos,					//�ʒu
					float				i_fSpeed,				//�X�s�[�h
					int 				i_iRotSpeed,			//��]�̑���
					int					i_iLifeTime,			//�\������
					int					i_iParticleSize			//�p�[�e�B�N���̐�
					BYTE				i_bBlue		= 0xFF,		//�F
					BYTE				i_bGreen	= 0xFF,		//�ΐF
					BYTE				i_bRed		= 0xFF,		//�ԐF
					BYTE				i_bAlpha	= 0xFF		//�����F
				);
	�p�r: �Q�[�W�̒i�K���オ�������ɔ�������G�t�F�N�g�I�u�W�F�N�g�̍쐬
	�߂�l: �Ȃ�
	************************************************************************/
	void AddExtinguishEffect(const D3DXVECTOR3 i_vPos,float i_fSpeed,int i_iRotSpeed , int i_iLifeTime,
					   int i_iParticleSize, BYTE i_bBlue = 0xFF,BYTE i_bGreen = 0xFF, BYTE i_bRed = 0xFF,BYTE i_bAlpha = 0xFF);

	/*********************************************************************
	bool Move(
		list<EffectState*>::iterator	it,				//���݂̃C�e���[�^�[
		const D3DXVECTOR3&				i_vHammerPos	//�n���}�[�̈ʒu
		);
	�p�r : �G�t�F�N�g�̓���
	�߂�l :	�^�������ꍇ�A���݂̃C�e���[�^�[���폜,
				�U�������ꍇ�A���̃C�e���[�^�[��
	*********************************************************************/
	bool Move(list<ExtinguishEffectState*>::iterator it,const D3DXVECTOR3& i_vHammerPos);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
		const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
		vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
		Command&				i_Com			//�R�}���h
	) ;
	�p�r : �V�[���̕ω�
	�߂�l : �Ȃ�
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
		const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
		Command i_Com						//�R�}���h
	 );
	 �p�r: �I�u�W�F�N�g��`��
	 �߂�l: �Ȃ��B
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

};

/*******************************************************************
class LineEffect : public Object	�錾��
�p�r :	���̃G�t�F�N�g�̕`��
*******************************************************************/
class LineEffect //: public Object
{

	/***************************************************************
	struct LineEffectGroup	�錾��
	�p�r : ���G�t�F�N�g���Ǘ�����\����
	***************************************************************/
	struct LineEffectGroup{

		float				m_fRotZSpeed;		//	��]���x
		float				m_fScale	;		//	�g��k���̒l
		int					m_iLifeTime ;		//	�o�����Ă��鎞��

		/***************************************************************
		struct LineEffectState	�錾��
		�p�r : ���G�t�F�N�g���Ǘ�����X�e�[�^�X
		***************************************************************/
		struct LineEffectState 
		{
			VertexLineState*	m_VLState	;
			D3DXVECTOR3			m_vPos		;
			D3DXVECTOR3			m_vRot		;
			D3DXVECTOR3			m_vSize		;
			D3DXMATRIX			m_Matrix	;

			/***********************************************************
			LineEffectState(
				LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
				const D3DXVECTOR3&	i_vPos		,	//�ʒu
				const D3DXVECTOR3&	i_vSize		,	//�傫��
				const D3DXVECTOR3&	i_vRot		,	//��]�x
				VertexStyle			i_VertexStyle,	//���̌` 
			);
			�p�r : �R���X�g���N�^
			�߂�l : �Ȃ�
			***********************************************************/
			LineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
				const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ) ;

		};

		vector<LineEffectState*>	m_StateVec ;

		/**************************************************************
		LineEffectGroup(
			float				i_fRotZSpeed,	//	��]���x
			float				i_fScaling		//	�g��k���̒l
			int					i_iLifeTime		//�o�����Ă��鎞��
		);
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		**************************************************************/
		LineEffectGroup( float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime ) ;

		/**************************************************************
		void Move( 
			Command& i_Com		//�R�}���h
		);
		�p�r : ����
		�߂�l : �Ȃ�
		**************************************************************/
		void Move( Command& i_Com ) ;

		/*************************************************************
		void Draw( 
			LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
		)
		�p�r : 
		�߂�l : 
		*************************************************************/
		void Draw( LPDIRECT3DDEVICE9 pD3DDevice );

	};
	
	vector<LineEffectGroup*>	m_StateVec ;

public :

	/******************************************************************
	LineEffect() ;
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************/
	LineEffect()	;

	/******************************************************************
	~LineEffect();
	�p�r : �f�X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************/
	~LineEffect();

	/******************************************************************
	void AddLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
		const D3DXVECTOR3&	i_vPos		,	//�ʒu
		const D3DXVECTOR3&	i_vSize		,	//�傫��
		const D3DXVECTOR3&	i_vRot			//��]�x
		VertexStyle			i_VertexStyle	//���̌` 
		float				i_fRotZSpeed,	//	��]���x
		float				i_fScaling		//	�g��k���̒l
		int					i_iLifeTime		//�o�����Ă��鎞��
		int					i_iLineNumber	//���̖{��
	);
	�p�r : ���C���G�t�F�N�g�̒ǉ�
	�߂�l : �Ȃ�
	******************************************************************/
	void AddLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize , 
		const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ,float i_fRotZSpeed ,float i_fScaling , int i_iLifeTime , int i_iLineNumber);

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
		const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
		vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
		Command&				i_Com			//�R�}���h
	) ;
	�p�r : �V�[���̕ω�
	�߂�l : �Ȃ�
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
		const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
		Command i_Com						//�R�}���h
	 );
	 �p�r: �I�u�W�F�N�g��`��
	 �߂�l: �Ȃ��B
	*****************************************************************/
		virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

//------------------------------�A�N�Z�b�T-------------------------------------------

	/***************************************************************************
	D3DXVECTOR3 StarFragment::getPos(
		int i_iVecNum	//�z����ł̓Y����
	) ;
	�p�r : �ʒu��Ԃ�
	�߂�l : �w�肳�ꂽ�Y������Object�̈ʒu��Ԃ�
	***************************************************************************/
	D3DXVECTOR3 getPos( int i_iVecNum ) ;

	/**************************************************************************
	const int getObjectVecSize() const ;
	�p�r : �I�u�W�F�N�g�̐���c������
	�߂�l : ���̃N���X�ŊǗ����Ă���Object�̐�
	**************************************************************************/
	const int getObjectVecSize() const ;

	
};


/*******************************************************************
class NameLineEffect : public Object	�錾��
�p�r :	���O�̐��̃G�t�F�N�g�̕`��
*******************************************************************/
class NameLineEffect : public ThreeDimensionsEffect
{
	PointSpriteVertex	m_DrawVertices[m_iVerticesMaxSize]	;	//�`��p���_�̔z��
	int					m_iDrawVerticesNumber				;	//���v�̒��_�f�[�^�����J�E���g����ϐ�

	/***************************************************************
	struct NameLineEffectState	�錾��
	�p�r : ���G�t�F�N�g���Ǘ�����X�e�[�^�X
	***************************************************************/
	struct NameLineEffectState 
	{
		PointSpriteVertex*	m_pPointSprite;
		VertexLineState*	m_pVLState	;
		D3DXVECTOR3			m_vPos		;
		D3DXVECTOR3			m_vSize		;
		D3DXMATRIX			m_Matrix	;

		/***********************************************************
		NameLineEffectState(
			LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
			const D3DXVECTOR3&	i_vPos		,	//�ʒu
			const D3DXVECTOR3&	i_vSize		,	//�傫��
			const D3DXVECTOR3&	i_vRot		,	//��]�x
			VertexStyle			i_VertexStyle,	//���̌` 
		);
		�p�r : �R���X�g���N�^
		�߂�l : �Ȃ�
		***********************************************************/
		NameLineEffectState(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,
			const D3DXVECTOR3& i_vSize , const D3DXVECTOR3& i_vRot , VertexStyle i_VertexStyle ) ;

		/************************************************************
		~NameLineEffectState();
		�p�r : �f�X�g���N�^
		�߂�l : �Ȃ�
		************************************************************/
		~NameLineEffectState();

		/**************************************************************
		void Move( 
			Command& i_Com		//�R�}���h
		);
		�p�r : ����
		�߂�l : �Ȃ�
		**************************************************************/
		void Move( Command& i_Com ) ;

	};

	vector<NameLineEffectState*>	m_StateVec ;

public :

	/******************************************************************
	NameLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice,			//�f�o�C�X
		const wchar_t*		i_filename			//�摜�̃t�@�C����
		float				i_fSize				//�G�t�F�N�g�̑傫��
	) ;
	�p�r : �R���X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************/
	NameLineEffect(LPDIRECT3DDEVICE9 pD3DDevice, const wchar_t* i_filename,float i_fSize)	;

	/******************************************************************
	~NameLineEffect();
	�p�r : �f�X�g���N�^
	�߂�l : �Ȃ�
	******************************************************************/
	~NameLineEffect();

	/******************************************************************
	void AddNameLineEffect(
		LPDIRECT3DDEVICE9	pD3DDevice	,	//�f�o�C�X
		const D3DXVECTOR3&	i_vPos		,	//�ʒu
		const D3DXVECTOR3&	i_vSize		,	//�傫��
	);
	�p�r : ���C���G�t�F�N�g�̒ǉ�
	�߂�l : �Ȃ�
	******************************************************************/
	void AddNameLineEffect( LPDIRECT3DDEVICE9 pD3DDevice , const D3DXVECTOR3& i_vPos ,const D3DXVECTOR3& i_vSize );

	/******************************************************************
	virtualvoid Transform(
		LPDIRECT3DDEVICE9		pD3DDevice	,	//�f�o�C�X
		const CONTROLER_STATE*	pCntlState	,	//�R���g���[���̃X�e�[�^�X
		vector<Object*>&		i_Vec		,	//�I�u�W�F�N�g�̔z��
		Command&				i_Com			//�R�}���h
	) ;
	�p�r : �V�[���̕ω�
	�߂�l : �Ȃ�
	******************************************************************/
	 virtual void Transform( LPDIRECT3DDEVICE9 pD3DDevice , const CONTROLER_STATE* pCntlState ,vector<Object*> i_ObjectVec ,Command& i_Com) ;

	/*****************************************************************
	 virtual void Draw(
		LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		vector<Object*>& i_Vec,				//�I�u�W�F�N�g�̔z��
		const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
		Command i_Com						//�R�}���h
	 );
	 �p�r: �I�u�W�F�N�g��`��
	 �߂�l: �Ȃ��B
	*****************************************************************/
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& i_Vec,
								const CONTROLER_STATE* pCntlState,Command& i_Com );

//-------------------------------�A�N�Z�b�T------------------------------------------

	/****************************************************************
	void setPos( 
		const vector<D3DXVECTOR3*>& i_vPosVec //�w�肵�����|�W�V�����̔z��
	);
	�p�r : �n���ꂽ�|�W�V�����̐������ʒu���Z�b�g����
	�߂�l : �Ȃ�
	****************************************************************/
	void setPos( const D3DXVECTOR3& i_vPosVec ); 
};
}
using namespace seiyasource;
}