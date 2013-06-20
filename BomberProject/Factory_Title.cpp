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

namespace wiz{
	namespace bomberobject{

const	float	SCALE_RATE	=	1.4f;

/************************************************************************
ClickChar ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FClickChar(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F������
//// ���l       �F
////            �F
////
ClickChar::ClickChar(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const RECT*					pRect		,
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
	if( !m_pCursor ) m_pCursor = ( MouseCursor* )SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CURSOR       );

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
//// �֐���     �FTitle_Select(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  DWORD next                      // ���̉��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Title_Select::Title_Select(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,const DWORD next,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_dNext( next )
,m_iTime( 0 )
,m_bPush( false )
,m_bPushRock( false )

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

	if(Cursor2D::isHitSprite(this)){
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
			i_UpdatePacket.pCommand->m_Command	= m_dNext;
			m_bPush = false ;
		}
	}
};

/************************************************************************
MagnetField ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagnetField(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
MagnetField::MagnetField(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const D3DXVECTOR3&			vCenter		,
	const RECT*					pRect		
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, g_vZero, 0xFFFFFFFF , OBJID_UI_SPRITE, false)
//,m_pCoil( NULL )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vRot( vRot )
,m_fRotZ( NULL )
{
	try{
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
	setNowPos(1);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid MagnetField::Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �FDrawPacket& i_DrawPacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void MagnetField::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Fvoid MagnetField::Update( UpdatePacket& i_UpdatePacket)
//// �J�e�S��   �F�֐�
//// �p�r       �F�f�[�^�̍X�V
//// ����       �FUpdatePacket& i_UpdatePacket    //�������̃f�[�^
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void MagnetField::Update(UpdatePacket& i_UpdatePacket)
{
	//if( !m_pCoil ){
	//	m_pCoil	= ( Coil* )SearchObjectFromTypeID( i_UpdatePacket.pVec,typeid(Coil) ) ; 
	//}

	//static float s_fDir = 0.0f;
	//m_vPos += D3DXVECTOR3(cos(D3DXToRadian(s_fDir)),sin(D3DXToRadian(s_fDir)),0.0f) * 2.5f;
	//s_fDir += 1.25f;
	//if(s_fDir >= 360.0f)s_fDir = 0.0f;
	//m_fRotZ = s_fDir;

	//float fCoilRotZ = m_pCoil->getRotZ()-90.0f;
	//D3DXVECTOR3 vCartesian  = ConvertToCartesianCoordinates(50.0f, fCoilRotZ);
	//D3DXVECTOR3 vCoilPos	= m_pCoil->getPos();
	//m_vPos = vCoilPos + vCartesian;

	D3DXMATRIX mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(m_vRot.z));
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mRot * mPos ;
};

/************************************************************************
Coil ��`��
************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FCoil(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
//// �ߒl       �F�Ȃ�
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
Coil::Coil(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const D3DXVECTOR3&			vCenter		,
	const RECT*					pRect		
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, g_vZero, 0xFFFFFFFF , OBJID_UI_SPRITE, false)
,m_pMagnetField( NULL )
,m_vPos( vPos )
,m_vScale( vScale )
,m_vRot( vRot )
,m_fRotZ( NULL )
{
	try{
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
};

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
	if( !m_pMagnetField ){
		m_pMagnetField	= ( MagnetField* )SearchObjectFromTypeID( i_UpdatePacket.pVec,typeid(MagnetField) ) ; 
	}

	float	fTargetDir = TwoPoint2Degree( m_pMagnetField->getPos() , m_vPos );
	float	fReverse   = 0.0f;
	if(m_fRotZ > 180.0f){
		fReverse = m_fRotZ - 180.0f;
	}
	else{
		fReverse = m_fRotZ + 180.0f;
	}

	if(m_fRotZ < fTargetDir){
		if(fTargetDir - m_fRotZ <= 180.0f){
			m_fRotZ += 1.0f;
			m_fRotZ = float(int(m_fRotZ) % 360);						
		}
		else{
			m_fRotZ -= 1.0f;
			if(m_fRotZ < 0.0f){
				m_fRotZ += 360.0f;
			}
		}
	}
	else if(m_fRotZ > fTargetDir){
		if(m_fRotZ - fTargetDir <= 180.0f){
			m_fRotZ -= 1.0f;
			if(m_fRotZ < 0.0f){
				m_fRotZ += 360.0f;
			}
		}
		else{
			m_fRotZ += 1.0f;
			m_fRotZ = float(int(m_fRotZ) % 360);												
		}
	}

	D3DXVECTOR3 vMove = g_vZero;
	ArcMove( vMove , 1.0f,  m_fRotZ);
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
	if(m_fDistance <= 10.0f){
		iMGNowPosNum++;
		if(iMGNowPosNum > 3)iMGNowPosNum = 1;
		m_pMagnetField->setNowPos(iMGNowPosNum);
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
        fpac->m_pVec->push_back(
			new DirectionalLight(
				fpac->pD3DDevice,
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
        fpac->m_pVec->push_back(
			new Camera(
				fpac->pD3DDevice,
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
		//fpac->m_pVec->push_back( new TestBehavior2());
		//	:TitleName
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"BGP_TITLE03.tga" ),
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
		fpac->m_pVec->push_back(
			new SpriteObject(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"Title_Name005_02.tga" ),
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

		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"Title_Name005_01.tga" ),
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

		//START002_02
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Start002_02.tga" ),
					GM_CHANGE_CHILDSTAGE,
					//GM_OPENSTAGE_PLAY,
					//GM_OPENSTAGE_LOAD,
					D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
					g_vZero,
					D3DXVECTOR3( 630.0f, 280.0f, 0.0f ),
					Rect( 0, 0, 221, 31 ),
					g_vZero,
					g_vZero,
					0xFFFF8800
				)
		);

		//START002_01
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Start002_01.tga" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 630.0f, 280.0f, 0.0f ),
				Rect( 0, 0, 221, 31 ),
				g_vZero,
				g_vZero,
				0xFF00FFFF
				)
		);


		//EXIT002_02
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_Exit002_02.tga" ),
					GM_EXIT,
					D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
					g_vZero,
					D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
					Rect( 0, 0, 143, 31 ),
					g_vZero,
					g_vZero,
					0xFFFF8800
				)
		);

		//EXIT002_01
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Title_EXIT002_01.tga" ),
				D3DXVECTOR3(SCALE_RATE,SCALE_RATE,0.0f),
				g_vZero,
				D3DXVECTOR3( 660.0f, 420.0f, 0.0f ),
				Rect( 0, 0, 143, 31 ),
				g_vZero,
				g_vZero,
				0xFF00FFFF
				)
		);
		
		//���E
		fpac->m_pVec->push_back(
			new MagnetField(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetField.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				g_vZero,
				D3DXVECTOR3( 128.0f, 128.0f, 128.0f ),
				Rect( 0, 0, 256, 256 )
				)
		);

		//�R�C��
		fpac->m_pVec->push_back(
			new Coil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Coil.png" ),
				D3DXVECTOR3(0.2f,0.2f,0.0f),
				D3DXVECTOR3( 0.0f, 0.0f, 90.0f ),
				D3DXVECTOR3( 170.0f, 370.0f, 0.0f ),
				D3DXVECTOR3( 128.0f, 128.0f, 128.0f ),
				Rect( 0, 0, 256, 256 )
				)
		);


		//Click_Please
		fpac->m_pVec->push_back(
			new ClickChar(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Click_Please1.png"),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					g_vZero,
					Rect( 0, 0, 512, 64 ),
					D3DXVECTOR3( 40.0f, -70.0f, 0.0f )
			)
		);						
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 

		system::Sound* pSound = NULL;
		fpac->SetSound( pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_TITLE );

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
