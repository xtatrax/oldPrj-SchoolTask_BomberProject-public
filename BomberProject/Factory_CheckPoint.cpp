////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�� ���V
//	�ҏW			�F���� ��
//	�����ް��Ɣ��l	�F�`�F�b�N�|�C���g
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class CheckEffect         : public PrimitiveBox	;
//			class CheckPoint          : public Cylinder		;
//			class Factory_CheckPoint  ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_CheckPoint.h"
//	: ��{�̃C���N���[�h
//////////

//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////



const float CHECK_POINT_RADIUS = 0.25f ;
const D3DXVECTOR3 CHECK_POINT_CHAR_SIZE = D3DXVECTOR3(1.0f,1.0f,0.0f);
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.5f, 1.0f, 0.5f, 0.5f } ;
D3DCOLORVALUE CHECKPOINTCOLOR_CHAR = { 1.0f, 1.0f, 1.0f, 1.0f } ;

const	float	CHECKPOINT_CHAR_DOWNSPEED	= 20.0f;
const	float	CHECKPOINT_CHAR_RATE_Y		= (1.0f/CHECK_POINT_CHAR_SIZE.y);
const	float	CHECKPOINT_CHAR_RATE_X		= (1.0f/CHECK_POINT_CHAR_SIZE.x);

namespace wiz{
namespace bomberobject{
/****************************************************************************
RestartPoint ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
RestartPoint::RestartPoint(
	const LPDIRECT3DDEVICE9	pD3DDevice	,
	const LPTATRATEXTURE	pPointTex
)
:Box( pD3DDevice, g_vOne, D3DXVECTOR3( -10.0f, 0.0f, 0.0f ), g_vZero, CHECKPOINTCOLOR, CHECKPOINTCOLOR, CHECKPOINTCOLOR, OBJID_SYS_RESTARTPOINT, false, pPointTex)
,m_fSize(0.0f)
{
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void RestartPoint::Update(UpdatePacket &i_UpdatePacket){
	if( m_fSize < EFFECT_SIZE ){
		m_fSize += 0.1f;
	}else{
		m_fSize = EFFECT_SIZE ;
	}
	m_BaseScale = g_vOne * m_fSize ;
	m_BaseScale.z = 0;
	CalcWorldMatrix();
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O �{�����V(�ҏW)
//// ���l       �F
////            �F
////
void RestartPoint::Draw( DrawPacket& i_DrawPacket ){
	if(m_pTexture){
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.GetDevice()->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.GetDevice()->SetTexture(0,m_pTexture->getTexture());
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}
		
};

/****************************************************************************
CheckPoint ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
CheckPoint::CheckPoint(
		LPDIRECT3DDEVICE9	pD3DDevice				,
		float				fLength					,
		LPTATRATEXTURE		pLineTex				,
		LPTATRATEXTURE		pCheckPointStringTex	,
		LPTATRATEXTURE		pLastStingTex			,
		wiz::OBJID			id
)
:Box( pD3DDevice, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero, g_vZero, CHECKPOINTCOLOR, CHECKPOINTCOLOR, CHECKPOINTCOLOR, id, false, pLineTex )
//,m_Effect(pD3DDevice, g_vZero, fLength, pTexture)
//,m_PintMark(pD3DDevice, pTexture2, CHECK_POINT_CHAR_SIZE, g_vZero, g_vZero,&Rect( 0, 0, 512, 64 ), D3DXVECTOR3( 256.0f, 32.0f, 0.0f ), D3DXVECTOR3( 0.0f, -87.0f, 0.0f ))
,m_enumNowState( BEHAVIORSTATE_WAIT )
,m_fBassLength( fLength )
,m_fReductionScale(4.0f)
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_pRestartPoint( NULL )
,m_ActiveItem( NULL )
,m_pTime( NULL )
//,m_Color( CHECKPOINTCOLOR )
//,m_Thicken( 1.0f )
//,m_Length( fLength )
//,m_pTextureLast( pTexture3 )
//,m_bPlayerPass( false )
//,m_bFirstRead( true )
{
	Box::m_BaseScale.x	= fLength ;
	Box::m_BasePos.x	= 25 ;
	//add(D3DXVECTOR3(25.0f,10.0f,0.0f));
	Debugger::DBGWRITINGLOGTEXT::addStr(L"CheckPoint::CheckPoint OK\n");
}
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
CheckPoint::~CheckPoint(){
	m_pCoil		= NULL ;
	m_pCamera	= NULL ;
	m_pTime		= NULL ;
	SafeDeletePointerContainer( m_ItemContainer ) ;
	m_ItemContainer.clear();
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pTime         )	m_pTime			= (   TimeScore*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME			) ;
	if( !m_pCoil         )	m_pCoil			= (  PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL			) ;
	if( !m_pCamera       )	m_pCamera		= (      Camera*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA		) ;
	if( !m_pRestartPoint )	m_pRestartPoint	= (RestartPoint*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_RESTARTPOINT	) ;


	//�S�Ẵ`�F�b�N�|�C���g��ʂ��Ă��Ȃ����������
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		//	: �����ҋ@��Ԃ������� �v���C���[���ʉ߂������m�F����
		switch( m_enumNowState ){
			case BEHAVIORSTATE_WAIT :
				//	: �R�C���̒ʉ߂�ҋ@
				PlayerPass(i_UpdatePacket);
				break ;
			case BEHAVIORSTATE_REDUCTION :
				//	: �k���G�t�F�N�g
				Reduction(i_UpdatePacket);
				break;
		}
	}
	
};
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�v���C���[�ʉߎ��̓���
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
void	CheckPoint::PlayerPass(UpdatePacket &i_UpdatePacket){

	float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
	float fCoilPosY = m_pCoil->getPos().y;

	if(fPosY <= fCoilPosY){
		m_enumNowState = BEHAVIORSTATE_REDUCTION ;
		m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		//m_ActiveItem++;
		m_pCoil->setRecordTime();
		m_pTime->setTime();

		i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
	}
}
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�v���C���[�ʉߎ��̓���
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
CheckPoint::WORKSTATE CheckPoint::Reduction(UpdatePacket &i_UpdatePacket){
	m_BaseScale.x -= m_fReductionScale ;
	if( m_BaseScale.x >= 0.0f ){
		return WORKSTATE_UNFINSHED ;
	}
	else{
		m_pRestartPoint->ChangePoint(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		m_ActiveItem++;
		if( m_ActiveItem >= m_ItemContainer.size()){
			m_enumNowState = BEHAVIORSTATE_LAST ;
		}else{
			m_BaseScale.x = m_fBassLength ;
			m_BasePos.y = m_ItemContainer[ m_ActiveItem ]->fPosY ;
			m_enumNowState = BEHAVIORSTATE_WAIT;
		}
		return WORKSTATE_COMPLETION ;
	}
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O �{�����V(�ҏW)
//// ���l       �F
////            �F
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){
		//	: �J����������
		//	: �`��Ώۂ�����
		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			Box::m_BasePos.y = m_ItemContainer[ m_ActiveItem ]->fPosY;
			Box::CalcWorldMatrix();
			//	: ��ʂ̒��ɂ���

			DrawLine(i_DrawPacket);
		}
	}
		
};

void CheckPoint::DrawLine( DrawPacket& i_DrawPacket ){
	if(m_pTexture){
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.GetDevice()->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.GetDevice()->SetTexture(0,m_pTexture->getTexture());
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}

}



/**************************************************************************
 Factory_CheckPoint ��`��
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{
			//fpac->AddObject( new RestartPoint( fpac->GetDevice(), fpac->AddTexture(L"particle.png") ) );
			//D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			//D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			//D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			//
			//CheckPoint* pcp ;
			//fpac->AddObject(
			//	pcp = new CheckPoint( fpac->GetDevice(), 100.0f, fpac->AddTexture( L"particle.png" ),)
			//);
			//pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			//pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

		}
		
		catch(...){
			//��throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace bomberobject.
}//end of namespace wiz.