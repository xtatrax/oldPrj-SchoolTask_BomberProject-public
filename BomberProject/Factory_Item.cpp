////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Item ;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Item.h"
//#include "Factory_Player.h"

namespace wiz{
namespace bomberobject{




/**************************************************************************
 Item ��`��
****************************************************************************/
/***************************************************************************
�֐����@�@�@�FItem( FactoryPacket* fpac,
                      LPDIRECT3DTEXTURE9 pTexture,
                      wiz::OBJID id )
�J�e�S���@�@�F�R���X�g���N�^
�p�r�@�@�@�@�F
�����@�@�@�@�FFactoryPacket* fpac           // : �f�o�C�X�Ȃ�
�@�@�@�@�@�@�FLPDIRECT3DTEXTURE9 pTexture   // : �e�N�X�`���\
�@�@�@�@�@�@�Fwiz::OBJID id                 // : ID
�߂�l�@�@�@�F
�S���ҁ@�@�@�F������
���l�@�@�@�@�F
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						pTexture
	)
	,m_pPlayerCoil(NULL)
	,m_pSuperGage(NULL)
	,m_pSound(NULL)
	,m_pCamera(NULL)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/////////////////// ////////////////////
//// �֐���     �F~Item();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Item::~Item(){
	SafeDeletePointerMap( m_ItemMap_All );	
}

/**************************************************************
�֐����@�@�Fvoid Item::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket          // �`��p�̂������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}


void Item::setDrawTarget(){

	//////////
	//	�`��Ώۂ̒ǉ�
	//
	ALLCONTAINER::iterator	AIMit  = m_ItemMap_All.lower_bound( m_pCamera->getPosY()  -20 ),
							AIMend = m_ItemMap_All.upper_bound( m_pCamera->getPosY()  +20 );
	while( AIMit != AIMend ){
		if( AIMit->second->m_bHidden == true ){
			AIMit->second->m_bHidden = false ;
			m_ItemMap_Target.push_back( AIMit->second );
		}
		AIMit++ ;
	}
	//
	//
	//////////
}

/*******************************************************************
�֐����@�@�Fvoid Item::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  // �X�V�p�f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
�ҏW      �F���� �O
���l�@�@�@�F
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{
	DWORD dwSTime = TLIB::Tempus::TimeGetTime();

	vector<Object*>	Vec	= *(i_UpdatePacket.pVec);

	if( !m_pPlayerCoil )	m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromID(&Vec,OBJID_3D_COIL);
	if( !m_pSuperGage )		m_pSuperGage	= (SuperGage*)SearchObjectFromID(&Vec,OBJID_UI_SUPERGAUGE);
	if( !m_pSound )			m_pSound		= (Sound*)SearchObjectFromID(&Vec,OBJID_SYS_SOUND);
	if( !m_pCamera )		m_pCamera		= (Camera*)SearchObjectFromID(&Vec, OBJID_SYS_CAMERA);

	//�R�C���̈ʒu�擾
	D3DXVECTOR3	cPos	= m_pPlayerCoil->getPos();

	setDrawTarget();

	Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_Target.size());

	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();

	while(it != m_ItemMap_Target.end()){

		if( (m_pPlayerCoil->getState() == COIL_STATE_MOVE		//	: �R�C�����ړ���
			|| m_pPlayerCoil->getState() == COIL_STATE_STICK )	//	: ��������	�A�C�e�����z����
			&& !m_pPlayerCoil->getSuperMode())					//	: �Ȃ�����	�X�[�p�[���[�h����Ȃ�������
		{
			//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
			D3DXVECTOR3	vTargetDir	= cPos - ((*it)->m_Pos) ;

			//	: �����ƑΏۂ܂ł̋��������߂�
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			(*it)->m_fDistance	 = (float)sqrt(dirX + dirY);

			//������5�ȓ��Ȃ����Ă���
			if( (*it)->m_fDistance < SuctionArea ){
				(*it)->m_Pos	+= vTargetDir/**SpeedRate*/ * m_pPlayerCoil->getSpeed();

				//�v���C���[�ƌ���Ȃ��߂��Ȃ�����A����
				if( (*it)->m_fDistance < VanishArea ){
					m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_ITEMS );
					//m_ItemMap_All.value_comp();
					ALLCONTAINER::size_type		count	= m_ItemMap_All.count((*it)->m_fMapKey) , 
												i		;
					ALLCONTAINER::iterator		ait		= m_ItemMap_All.find((*it)->m_fMapKey);
					//�G�l���M�[��
					m_pSuperGage->Recovery(-RECOVERY_POINT);
					(*it)->m_bHidden = true ;
					// SafeDelete( (*it) );
					for( i = 0 ; i < count ; i++ ){
						if( ait->second == (*it) ){
							SafeDelete(ait->second);
							m_ItemMap_All.erase(ait);
							break ;
						}
						ait++ ;
					}
					it = m_ItemMap_Target.erase( it );
					continue;
				}
			}
			//�Q�[�W���ő�ɂȂ�����R�C���𖳓G��Ԃ�
			if(m_pSuperGage->getRate() >= 1.0f){
				m_pPlayerCoil->setSuperMode(true);	
			}
		}
		if( (*it)->m_fMapKey > m_pCamera->getPosY() +20 ||
			(*it)->m_fMapKey < m_pCamera->getPosY() -20 ){
				(*it)->m_bHidden = true ;
				it = m_ItemMap_Target.erase(it);
				continue;
		}
		//�ړ��p
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			(*it)->m_Pos.x,(*it)->m_Pos.y,(*it)->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			(*it)->m_Size.x,(*it)->m_Size.y,(*it)->m_Size.z);

		//�}�e�B���A���ݒ�
		m_Material = (*it)->m_Material;
		(*it)->m_mMatrix	= mScale * mMove;

		it++;
	}
	if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && m_pPlayerCoil->getSuperMode()){
		static float s_fTimeTotal = 0.0f;
		s_fTimeTotal += (float)SUPER_GAGE_MAX / (float)COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeTotal >= 1.0f){
			m_pSuperGage->Consume( -(1.0f / COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime()) );
			s_fTimeTotal -= (int)s_fTimeTotal;
		}
	}
	DWORD dwETime = TLIB::Tempus::TimeGetTime();
	Debugger::DBGSTR::addStr( L"Item::Update : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));

}

/***********************************************
�֐����@�Fvoid Item::addItem(
                      D3DXVECTOR3 pos,
                      D3DXVECTOR3 size,
                      D3DCOLORVALUE Diffuse,
                      D3DCOLORVALUE Specular, 
                      D3DCOLORVALUE Ambient)
�J�e�S���F�֐�
�p�r�@�@�F�A�C�e���̒ǉ�
�����@�@�FD3DXVECTOR3 pos          //�`��ʒu
�@�@�@�@�FD3DXVECTOR3 size         //�傫��
�@�@�@�@�FD3DCOLORVALUE Diffuse    //
�@�@�@�@�FD3DCOLORVALUE Specular   //
�@�@�@�@�FD3DCOLORVALUE Ambient    //
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_fMapKey = pos.y ;
		bItem->m_bHidden = true ;
		bItem->m_Size = size;
		bItem->m_fDistance = 6.0f;
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemMap_All.insert(multimap<float,BallItem*>::value_type(bItem->m_Pos.y,bItem));
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
 Factory_Item ��`��
****************************************************************************/
/**************************************************************************
�֐����@�@�FFactory_Item::Factory_Item( FactoryPacket* fpac );
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac     // �������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);

		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 300; j++){
				it->addItem(D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.05f))+1.5f,
										(float(j)*2.75f+float(rand()%100*0.05f))+1.5f,0.0f),
							D3DXVECTOR3(0.5f,0.5f,0.5f),
							BallDiffuse,
							BallSpecular,
							BallAmbient);
			}
		}
		fpac->m_pVec->push_back(it);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 �֐����@�@�FFactory_Item::~Factory_Item();
 �J�e�S���@�F�f�X�g���N�^
 �p�r�@�@�@�F
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������
 ���l�@�@�@�F
***************************************************************************/
Factory_Item::~Factory_Item(){
    //�Ȃɂ����Ȃ�
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
