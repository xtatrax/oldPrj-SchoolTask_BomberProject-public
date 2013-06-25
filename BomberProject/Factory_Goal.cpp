////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Goal.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�S�[���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject ;
//		class Factory_Goal ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Goal.h"
#include "Factory_Wall.h"
#include "BassItems.h"

const D3DXVECTOR3	GOAL_CHAR_SIZE			= D3DXVECTOR3(1.0f,1.0f,0.0f);
const	float		GOAL_CHAR_RATE_Y		= (1.0f/GOAL_CHAR_SIZE.y);
const	float		GOAL_CHAR_RATE_X		= (1.0f/GOAL_CHAR_SIZE.x);
const	float		GOAL_CHAR_DOWNSPEED		= 20.0f;

namespace wiz{
namespace bomberobject{

/**************************************************************************
 FMemoryTex ��`��
****************************************************************************/
/**************************************************************************
 FMemoryTex::FMemoryTex(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F������
***************************************************************************/
FMemoryTex::FMemoryTex( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
	,m_pCamera( NULL )
	,m_pCoil( NULL )
	,m_bEnding( false )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_iPtn		= 1;

	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
		//�@���ƒ��_����uv�l�𓾂�
		BoxVecNomalUV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();

}

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void FMemoryTex::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,mItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		//�e�N�X�`��������ꍇ
		if(m_pTexture){
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
			//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
////            �F
////
void FMemoryTex::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera	)	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA	) ;
	if( !m_pCoil	)	m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;

	m_ItemMap_Target.clear();
	multimap<float,mItem*>::iterator it = m_ItemMap_Memory.begin();
	while(it != m_ItemMap_Memory.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,mItem*>::value_type(it->second->vPos.y,it->second));
		}
		++it;
	}


	multimap<float,mItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		if( m_pCoil->getState() == COIL_STATE_CLEAR ){
			OrientGoal( i_UpdatePacket );
		}

		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->vScale.x,it2->second->vScale.y,it2->second->vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->vPos.x,it2->second->vPos.y,it2->second->vPos.z);
		//�~�b�N�X�s��
		it2->second->mMatrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = it2->second->mMaterial;

		++it2;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddDesc( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FDesc�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void FMemoryTex::AddMemory(const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
			const D3DCOLORVALUE& Diffuse,const D3DCOLORVALUE& Specular,const D3DCOLORVALUE& Ambient)
{
	mItem* pItem = new mItem;
	pItem->vScale = vScale;
	pItem->vPos	= vPos;
    ::ZeroMemory(&pItem->mMaterial,sizeof(D3DMATERIAL9));
	pItem->mMaterial.Diffuse = Diffuse;
	pItem->mMaterial.Specular = Specular;
	pItem->mMaterial.Ambient = Ambient;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Memory.insert(multimap<float,mItem*>::value_type(pItem->vPos.y,pItem));

	m_vPos		= vPos;
	m_vScale	= vScale;
}

/****************************************************
�֐����@�Fvoid	OrientGoal(UpdatePacket& i_UpdatePacket)
�J�e�S���F�֐�
�p�r�@�@�F�N���A��v���[���[�𓮂���
�����@�@�F�Ȃ�
�߂�l�@�F�Ȃ�
�S���ҁ@�F������
���l�@�@�F
****************************************************/
void FMemoryTex::OrientGoal(UpdatePacket& i_UpdatePacket){
	//�R�C���̌��݂̏��𓾂�
	D3DXVECTOR3	move		= m_pCoil->getPos();	//�ʒu
	D3DXVECTOR3	scale		= m_pCoil->getScale();	//�傫��
	float		dir			= m_pCoil->getDir();	//�i�s����

	const float	rate		= 0.1f;			//�ړ����鑬��
	const float	ScaleRate	= rate*rate;	//�傫���̕ω���
	const float DirRate		= rate*60;		//�p�x�̕ω���
	const float	OrientPos	= m_vPos.x + (m_vScale.x / 2 - 4) -7.3f ;	//�������ׂ��ʒu

	int			dirPtn		= 1;		//�����ׂ��p�x������
	const float	TopDir		= 90.0f;	//������������̂̊p�x
	const float	RightDir	= 0.0f;		//�E�����������̂̊p�x
	const float	LeftDir		= 180.0f;	//�������������̂̊p�x

	static float LeastScale	= 0.3f;	//�ł��k���������̑傫��

	//****************************
	//�傫���̕ύX
	if( scale.x > LeastScale ){
		scale.x	-= ScaleRate;
		scale.y	-= ScaleRate;
		scale.z	-= ScaleRate;
	}
	else{
		scale.x	= LeastScale;
		scale.y	= LeastScale;
		scale.z	= LeastScale;

		if( scale.x == 0 )	m_bEnding	= true;
	}
	//****************************
	//�ʒu�̕ύX
	switch( m_iPtn ){
		case 1:	if( m_vPos.y-1.0f >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 2;
				break;
		case 2:	if( OrientPos > move.x ){
					move.x	+= rate;
					dirPtn	= 2;	//�E
					if( OrientPos < move.x )
						move.x	= OrientPos;
				}
				else if( OrientPos < move.x ){
					move.x	-= rate;
					dirPtn	= 3;	//��
					if( OrientPos > move.x )
						move.x	= OrientPos;
				}
				else	m_iPtn	= 3;
				break;
		case 3:	if( m_vPos.y + 1.4 >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 4;
				dirPtn	= 1;
				break;
		case 4:	if( m_vPos.x <= move.x ){
					move.x	-= rate;
					dirPtn	 = 3;
				}
				else{
					m_iPtn		= 5;
					LeastScale	= 0;
				}
				break;
		default:
				break;
	}
	//****************************
	//�p�x�̕ύX
	switch( dirPtn ){
		case 1:	//��
			if( dir > TopDir )
				dir	-= DirRate;
			else if( dir < TopDir )
				dir	+= DirRate;
			break;

		case 2:	//�E
			if( dir > RightDir )
				dir	-= DirRate;
			else if( dir < RightDir )
				dir	+= DirRate;
			break;

		case 3:	//��
			if( dir > LeftDir )
				dir	-= DirRate;
			else if( dir < LeftDir )
				dir	+= DirRate;
			break;
	}
	//**************************************************

	if( !m_bEnding ){
		m_pCoil->setPos(move);
		m_pCoil->setScale(scale);
		m_pCoil->setDir(dir);
	}
	else{ 
		static float s_fTimeCount = 0.0f;
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeCount >= 0.5f){
			i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_CLEAR;
			i_UpdatePacket.pCommand->m_Param1	= m_pCoil->getDeadCount();
			i_UpdatePacket.pCommand->m_Param2	= m_pCoil->getMaxPos();
			i_UpdatePacket.pCommand->m_Param3	= m_pCoil->getScratchTime();
			s_fTimeCount = 0.0f;
			LeastScale	 = 0.3f;
		}
	}
}

/**************************************************************************
 GoalObject ��`��
****************************************************************************/
/***************************************************************************
�֐����@�@�FGoalObject(
                   FactoryPacket* fpac,
                   LPDIRECT3DTEXTURE9 pTexture,
                   wiz::OBJID id
              )
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac           //�f�o�C�X�Ȃ�
�@�@�@�@�@�FLPDIRECT3DTEXTURE9 pTexture   //�e�N�X�`���\
�@�@�@�@�@�Fwiz::OBJID id                 //ID
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
****************************************************************************/
GoalObject::GoalObject( LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 vPos , LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DTEXTURE9 pGoakCharTex,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_bPlaySound( true )
,m_pGoalCharTex( pGoakCharTex )
,m_fInitPosY( 0 )
{
	try{
		D3DXVECTOR3		vScale = D3DXVECTOR3( 100.0f, 1.0f, 0.0f) ;
		SetBasePos(		vPos	);
		SetBaseScale(	vScale	);

		m_Obb = OBB( vScale, g_vZero, vPos );
		this->CalcWorldMatrix();
        // D3DMATERIAL9�\���̂�0�ŃN���A
		m_Material.Diffuse	= COLOR2D3DCOLORVALUE(0xFFFFFF00);
		m_Material.Specular	= COLOR2D3DCOLORVALUE(0xFFFFFF00);
		m_Material.Ambient	= COLOR2D3DCOLORVALUE(0xFFFFFF00);

		m_pGoalChar	= 	new SpriteObject( pD3DDevice, m_pGoalCharTex, GOAL_CHAR_SIZE, g_vZero, g_vZero,
									Rect( 0, 0, 256, 64 ), D3DXVECTOR3( 128.0f, 32.0f, 0.0f ), D3DXVECTOR3( 100.0f, -87.0f, 0.0f ));

	}
	catch(...){
		//�ăX���[
		throw;
	}
}
GoalObject::~GoalObject(){
	
	m_pCoil		= NULL ;
	m_pGoalChar	= NULL;
	m_pCamera	= NULL;
	//SafeDeletePointerMap( m_ItemMap_All ) ;


}
/**************************************************************
�֐����@�@�Fvoid GoalObject::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket   //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void	GoalObject::Draw(DrawPacket &i_DrawPacket){
	PrimitiveBox::Draw( i_DrawPacket );
	m_pGoalChar->Draw( i_DrawPacket );
}

/*******************************************************************
�֐����@�@�Fvoid GoalObject::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
�֐���     �Fvoid	 GoalObject::Update(UpdatePacket& i_UpdatePacket)
�p�r       �F�f�[�^�X�V
********************************************************************/
void	GoalObject::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pCoil  ) m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}


	//�Փ˔���
	if( m_pCoil && m_pCoil->HitTestWall( m_Obb ) ){
		m_pCoil->setState( COIL_STATE_CLEAR );
		m_pCoil->setSuperMode(COIL_STATE_SUPER_CHARGE);
		if( m_bPlaySound ){
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_GOAL );
			m_bPlaySound	= false;
		}
	}

	//*****************************************************************************************************
	//�S�[���̕���
	float	fTexPosY	= 0.0f;
	if( m_pCamera )
		fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;

	D3DXVECTOR3	p;
	GetWorldPos(p);
	float	m_fGoalPosX = p.x;
	float	m_fGoalPosY = p.y;

	float	wide	= BASE_CLIENT_WIDTH / 50 * m_fGoalPosX * GOAL_CHAR_RATE_X;
	float	height	= ( (m_fGoalPosY - fTexPosY)
								* GOAL_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * GOAL_CHAR_RATE_Y;

	D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,GOAL_CHAR_SIZE.x,GOAL_CHAR_SIZE.y,GOAL_CHAR_SIZE.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
	D3DXMatrixTranslation(&mPos, wide,height,0.0f);
	mTexMatrix	= mPos*mScale*mRot;
	m_pGoalChar->setMatrix( mTexMatrix );

}


/**************************************************************************
 Factory_Goal ��`��
****************************************************************************/
/**************************************************************************
 Factory_Goal::Factory_Goal(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Goal::Factory_Goal(FactoryPacket* fpac){
	try{
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Goal::~Factory_Goal();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Goal::~Factory_Goal(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
