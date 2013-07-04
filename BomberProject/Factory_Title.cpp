////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Title ;
//
#include "StdAfx.h"
#include "BassMenuItems.h"
#include "Factory_Title.h"
#include "Factory_Scroll.h"
#include "Factory_Cursor.h"
#include "Factory_Coil.h"
#include "Factory_CustomButtonA.h"

namespace wiz{
	namespace bomberobject{

const	float	SCALE_RATE	=	1.4f;


/************************************************************************
ClickChar ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FClickChar(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPTATRATEXTURE pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  Rect* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
ClickChar::ClickChar(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPTATRATEXTURE	pTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const Rect*					pRect		,
	const D3DXVECTOR3&			vOffsetPos
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, g_vZero, g_vZero, 0xFFFFFFFF , OBJID_UI_SPRITE, false)
,m_pCursor( NULL )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vOffsetPos( vOffsetPos )
{
	try{
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

ClickChar::~ClickChar(){
	m_pCursor = NULL;
}

/////////////////// ////////////////////
//// �֐���     �Fvoid ClickChar::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void ClickChar::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid ClickChar::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void ClickChar::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pCursor ) m_pCursor = ( MouseCursor* )i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR  );
	if( !m_pCursor ) return ;
	Point MousePos = Point(0,0) ;
	if( m_pCursor ) MousePos = m_pCursor->get2DPos();

	m_vPos	= D3DXVECTOR3( (float)MousePos.x + m_vOffsetPos.x, (float)MousePos.y + m_vOffsetPos.y, 0.0f);

	D3DXMATRIX mScale, mPos;
	//D3DXMatrixTranslation(&mPos,(float)MousePos.x,(float)MousePos.y,0.0f);
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mPos ;
};

/************************************************************************
Title_Select ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FTitle_Select(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,DWORD next,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPTATRATEXTURE pTexture     // �\��t�������e�N�X�`��
////            �F  DWORD next                      // ���̉��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  Rect* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Title_Select::Title_Select(const LPDIRECT3DDEVICE9 pD3DDevice,const LPTATRATEXTURE pTexture,const DWORD next,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const Rect *pRect,const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color, bool bCanSelect)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_dNext( next )
,m_iTime( 0 )
,m_bPush( false )
,m_bPushRock( false )
,m_bCanSelect( bCanSelect )

{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

Title_Select::~Title_Select(){
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Title_Select::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Title_Select::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Title_Select::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
void Title_Select::Update(UpdatePacket& i_UpdatePacket)
{
	//SaveData sd;
	//TLIB::BinaryLoad( RCTEXT_SAVEDATA_FILENAME,sd,RCTEXT_SAVEDATA_EXTENSION);

	if(Cursor2D::isHitSprite(this) && m_bCanSelect){
		//	: �摜�͈͓̔��Ƀ}�E�X��������

		if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
			//	: �}�E�X�̍��{�^���������ꂽ

			if( m_bPushRock ){
				if( !m_bPush ){
						i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
				}
				m_bPush		= true;
				m_bPushRock	= false;
			}
		}
		else m_bPushRock	= true;
		m_Color	= 0xFFFF8800;
		if( !m_bSelect ){
			m_bSelect = true;
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
		}
	}else{
		//	: �}�E�X���摜�͈̔͊O�ɂ���Ƃ�
		m_Color	= 0xFF558855;
		m_bSelect = false ;
		if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
		else				m_bPushRock	= true;
	}
	if( m_bPush ){
		m_iTime++;
		if( m_iTime > 30 ){
			//�I�΂ꂽ��ʂւƂ�
			i_UpdatePacket.PushCommand( m_dNext );
			m_bPush = false ;
		}
	}
};

/************************************************************************
MagnetFieldMini ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagnetFieldMini(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPTATRATEXTURE pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  Rect* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
MagnetFieldMini::MagnetFieldMini(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPTATRATEXTURE	pTextureN	,
	const LPTATRATEXTURE	pTextureS	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const D3DXVECTOR3&			vCenter		,
	const Rect*					pRect		
)
:SpriteObject( pD3DDevice, pTextureN, vScale, vRot, vPos, pRect, vCenter, g_vZero, 0xFFFFFFFF , OBJID_UI_TITLEMAGNETFIELD)
,m_pTextureN( pTextureN )
,m_pTextureS( pTextureS )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vRot( vRot )
,m_fRotZ( NULL )
,m_iNowPosNum( 1 )
,m_bMagnetPole( POLE_N )
{
	try{
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

MagnetFieldMini::~MagnetFieldMini(){	
}

/////////////////// ////////////////////
//// �֐���     �Fvoid MagnetFieldMini::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void MagnetFieldMini::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid MagnetFieldMini::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void MagnetFieldMini::Update(UpdatePacket& i_UpdatePacket)
{
	D3DXMATRIX mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(m_vRot.z));
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mRot * mPos ;

};

void MagnetFieldMini::setNowPos(int i_iNum){
	m_iNowPosNum = i_iNum;
	switch(m_iNowPosNum){
		case 1:
			m_vPos = MAGNET_FIELD_POS_1;
			break;
		case 2:
			m_vPos = MAGNET_FIELD_POS_2;
			break;
		case 3:
			m_vPos = MAGNET_FIELD_POS_3;
			break;
		default:
			break;
	}
	switch(m_bMagnetPole){
		case POLE_N:
			m_bMagnetPole = POLE_S;
			setTexture(m_pTextureS);
			break;
		case POLE_S:
			m_bMagnetPole = POLE_N;
			setTexture(m_pTextureN);
			break;
		default:
			break;
	}
};

/************************************************************************
Coil ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FCoil(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPTATRATEXTURE pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  Rect* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
Coil::Coil(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPTATRATEXTURE	pTextureN	,
	const LPTATRATEXTURE	pTextureS	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const D3DXVECTOR3&			vCenter		,
	const Rect*					pRect		
)
:SpriteObject( pD3DDevice, pTextureS, vScale, vRot, vPos, pRect, vCenter, g_vZero, 0xFFFFFFFF , OBJID_UI_SPRITE)
,m_pMagnetField( NULL )
,m_pTextureN( pTextureN )
,m_pTextureS( pTextureS )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vRot( vRot )
,m_fRotZ( 0.0f )
,m_bMagnetPole( POLE_S )
{
	try{
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

Coil::~Coil(){
	m_pMagnetField = NULL;
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Coil::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void Coil::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid Coil::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void Coil::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pMagnetField ) m_pMagnetField	= ( MagnetFieldMini* )i_UpdatePacket.SearchObjectFromID( OBJID_UI_TITLEMAGNETFIELD ) ; 
	if( !m_pMagnetField ) return ;

	float	fTargetDir = TwoPoint2Degree( m_pMagnetField->getPos() , m_vPos );
	float	fReverse   = 0.0f;
	float	fTurnAngle = 2.0f;
	if(m_fRotZ > 180.0f){
		fReverse = m_fRotZ - 180.0f;
	}
	else{
		fReverse = m_fRotZ + 180.0f;
	}

	if(m_fRotZ < fTargetDir){
		if(fTargetDir - m_fRotZ <= 180.0f){
			m_fRotZ += fTurnAngle;
			m_fRotZ = float(int(m_fRotZ) % 360);						
		}
		else{
			m_fRotZ -= fTurnAngle;
			if(m_fRotZ < 0.0f){
				m_fRotZ += 360.0f;
			}
		}
	}
	else if(m_fRotZ > fTargetDir){
		if(m_fRotZ - fTargetDir <= 180.0f){
			m_fRotZ -= fTurnAngle;
			if(m_fRotZ < 0.0f){
				m_fRotZ += 360.0f;
			}
		}
		else{
			m_fRotZ += fTurnAngle;
			m_fRotZ = float(int(m_fRotZ) % 360);												
		}
	}

	D3DXVECTOR3 vMove = g_vZero;
	ArcMove( vMove , 1.5f,  m_fRotZ);
	m_vPos += vMove;

	D3DXMATRIX mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(m_vRot.z + m_fRotZ));
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mRot * mPos ;

	//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
	D3DXVECTOR3	vTargetDir	= m_pMagnetField->getPos() - m_vPos;
	//	: �����ƑΏۂ܂ł̋��������߂�
	double dirX = vTargetDir.x * vTargetDir.x;
	double dirY = vTargetDir.y * vTargetDir.y;
	float m_fDistance = (float)sqrt(dirX + dirY);
	int iMGNowPosNum = m_pMagnetField->getNowPosNum();
	if(m_fDistance <= 5.0f){
		iMGNowPosNum++;
		if(iMGNowPosNum > 3)iMGNowPosNum = 1;
		m_pMagnetField->setNowPos(iMGNowPosNum);
		switch(m_bMagnetPole){
			case POLE_N:
				m_bMagnetPole = POLE_S;
				setTexture(m_pTextureS);
				break;
			case POLE_S:
				m_bMagnetPole = POLE_N;
				setTexture(m_pTextureN);
				break;
			default:
				break;
		}
	}

};

/**************************************************************************
 Factory_Title ��`��
****************************************************************************/
/**************************************************************************
 Factory_Title::Factory_Title(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Title::Factory_Title(FactoryPacket* fpac){
	try{
		//////////
		//	: ���C�g�̐ݒ�
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        fpac->AddObject(
			new DirectionalLight(
				fpac->GetDevice(),
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3( -0.0f, -1.0f, 0.0f)
			)
		);
		//	: ���C�g�̐ݒ�
		//////////

		//////////
		//	: �J�����̐ݒ�
		float ECXPos = 25.1f;
		float ECYPos = 10.666f;		
        fpac->AddObject(
			new Camera(
				fpac->GetDevice(),
				D3DXVECTOR3( ECXPos, ECYPos, -55.7f),
				D3DXVECTOR3( ECXPos, ECYPos,   0.0f),
				1 ,
				55.8f,
				30.0f
			)
		);

		//	: �J�����̐ݒ�
		//////////
		Factory_Scroll		Ffac( fpac );
		//fpac->AddObject( new TestBehavior2());

		fpac->AddObject(
			new SpriteObject(
				fpac->GetDevice(),
				fpac->AddTexture(L"BGP_TITLE01.png"),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				g_vZero,
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		) ;


		fpac->AddObject(
			new SpriteObject(
				fpac->GetDevice(),
				fpac->AddTexture( L"BGP_TITLE03.png" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0x25FFFFFF
				)
		);
//////////////////////////////////////////////////////////////////////////////////////
//		NAME																		//
//////////////////////////////////////////////////////////////////////////////////////
		fpac->AddObject(
			new SpriteObject(
					fpac->GetDevice(),
					fpac->AddTexture( L"Title_Name02.png" ),
					D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
					g_vZero,
					D3DXVECTOR3( 165.0f, 40.0f, 0.0f ),
					//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
					NULL,
					g_vZero,
					g_vZero,
					0xFF00FFFF		
					)
		);

		fpac->AddObject(
			new SpriteObject(
				fpac->GetDevice(),
				fpac->AddTexture( L"Title_Name01.png" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 165.0f, 40.0f, 0.0f ),
				//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFF8800
				)
		);
//////////////////////////////////////////////////////////////////////////////////////
//		START�{�^��																//
//////////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->GetDevice(),
				fpac->AddTexture(L"Title_Start02.png"),
				fpac->AddTexture(L"Title_Start01.png"),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 630.0f, 280.0f, 0.0f ),
				&Rect( 0, 0, 221, 31 ),
				&Rect( 0, 0, 221, 31 ),
				g_vZero,
				g_vZero,
				0xFFFF8800,
				0xFF558855,
				0xFF00FFFF,
				0xFF00FFFF,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_CHANGE_CHILDSTAGE, 3, 0 ),
				OBJID_UI_BUTTON_NORMAL
			)
		);
		//fpac->AddObject(
		//	new Title_Select(
		//			fpac->GetDevice(),
		//			pTex/*fpac->AddTexture( L"Title_Start02.png" )*/,
		//			GM_CHANGE_CHILDSTAGE,
		//			//GM_OPENSTAGE_PLAY,
		//			//GM_OPENSTAGE_LOAD,
		//			D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
		//			g_vZero,
		//			D3DXVECTOR3( 630.0f, 280.0f, 0.0f ),
		//			Rect( 0, 0, 221, 31 ),
		//			g_vZero,
		//			g_vZero,
		//			0xFFFF8800
		//		)
		//);
		//fpac->AddObject(
		//	new SpriteObject(
		//		fpac->GetDevice(),
		//		pTex/*fpac->AddTexture( L"Title_Start01.png" )*/,
		//		D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
		//		g_vZero,
		//		D3DXVECTOR3( 630.0f, 280.0f, 0.0f ),
		//		Rect( 0, 0, 221, 31 ),
		//		g_vZero,
		//		g_vZero,
		//		0xFF00FFFF
		//		)
		//);
//////////////////////////////////////////////////////////////////////////////////////
//		EXIT�{�^��																	//
//////////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->GetDevice(),
				fpac->AddTexture(L"Title_Exit02.png"),
				fpac->AddTexture(L"Title_Exit01.png"),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
				&Rect( 0, 0, 143, 31 ),
				&Rect( 0, 0, 143, 31 ),
				g_vZero,
				g_vZero,
				0xFFFF8800,
				0xFF558855,
				0xFF00FFFF,
				0xFF00FFFF,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_EXIT, 3, 0 ),
				OBJID_UI_BUTTON_NORMAL
			)
		);
		//fpac->AddObject(
		//	new Title_Select(
		//			fpac->GetDevice(),
		//			pTex/*fpac->AddTexture( L"Title_Exit02.png" )*/,
		//			GM_EXIT,
		//			D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
		//			g_vZero,
		//			D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
		//			Rect( 0, 0, 143, 31 ),
		//			g_vZero,
		//			g_vZero,
		//			0xFFFF8800
		//		)
		//);
		//fpac->AddObject(
		//	new SpriteObject(
		//		fpac->GetDevice(),
		//		pTex/*fpac->AddTexture( L"Title_EXIT01.png" )*/,
		//		D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
		//		g_vZero,
		//		D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
		//		Rect( 0, 0, 143, 31 ),
		//		g_vZero,
		//		g_vZero,
		//		0xFF00FFFF
		//		)
		//);
			
		//���E
		fpac->AddObject(
			new MagnetFieldMini(
				fpac->GetDevice(),
				fpac->AddTexture( L"MagnetField_N.png" ),
				fpac->AddTexture( L"MagnetField_S.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				MAGNET_FIELD_POS_1,
				D3DXVECTOR3( 128.0f, 128.0f, 128.0f ),
				&Rect( 0, 0, 256, 256 )
				)
		);
		//�R�C��
		fpac->AddObject(
			new Coil(
				fpac->GetDevice(),
				fpac->AddTexture( L"Coil_N.png" ),
				fpac->AddTexture( L"Coil_S.png" ),
				D3DXVECTOR3(0.35f,0.35f,0.0f),
				D3DXVECTOR3( 0.0f, 0.0f, 90.0f ),
				D3DXVECTOR3( 170.0f, 370.0f, 0.0f ),
				D3DXVECTOR3( 128.0f, 128.0f, 128.0f ),
				&Rect( 0, 0, 256, 256 )
				)
		);

		//Click_Please
		fpac->AddObject(
			new ClickChar(
					fpac->GetDevice(),
					fpac->AddTexture( L"Click_Please1.png"),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					g_vZero,
					&Rect( 0, 0, 512, 64 ),
					D3DXVECTOR3( 40.0f, -70.0f, 0.0f )
			)
		);						
		float	fLineLength	= 550.0f;
		float	fPointSize	= 1.0f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 

		system::Sound* pSound = NULL;
		fpac->SetSound( pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_TITLE );
//*/
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Title::~Factory_Title();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Title::~Factory_Title(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
