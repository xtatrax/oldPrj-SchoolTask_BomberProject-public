#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Score.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Score ��`��
***************************************************************************/
/**************************************************************************
 Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
Score::Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDigit,
				Rect*		Rect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0x00FFFFFF )
,m_vPos( vPos )
,m_vScale( vScale )
,m_iScore( 0 )
,m_iDigit( iDigit )
,m_bFirst( false )
,m_pCoil( NULL )
{
	m_Color.byteColor.a	= 0xFF;
	m_Color.byteColor.r	= 0xFF;
	m_Color.byteColor.g	= 0xFF;
	m_Color.byteColor.b	= 0xFF;
	
	for( int i = 0; i < MAX_DIGIT_DEAD; i++ )
		m_DigitArr[i]	= 0;
}

/**************************************************************************
 Score::~Score();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Score::~Score(){
	m_pCoil	= NULL;
}

/**************************************************************************
 Score::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	Score::Draw(DrawPacket& i_DrawPacket){
	for( int i = 0; i < m_iDigit ; i++ ){
		update_Matrix( i );
		if( !m_bFirst ){
			if( m_DigitArr[i] != 0 )
				m_bFirst	= true;
			else if( i == m_iDigit-1 )
				m_bFirst	= true;
		}
		if( m_bFirst )
			SpriteObject::Draw( i_DrawPacket );
	}
	m_bFirst	= false;
}

/**************************************************************************
 Score::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	Score::Update(UpdatePacket& i_UpdatePacket){

	int	iDigit	= 1000;
	for( int i = 0; i < m_iDigit; i++ ){
		int	a	= m_iScore / iDigit;
		if( a >= 10 ){
			a	= a%10;
		}
		m_DigitArr[i]	= a;
		iDigit	= iDigit / 10;
	}

	//m_DigitArr[0]	= 0;
	//m_DigitArr[1]	= 0;
	//m_DigitArr[2]	= 1;
	//m_DigitArr[3]	= 0;
}

/**************************************************************************
 Score::setMatrix(int i)
 �p�r: �}�g���b�N�X�̍X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	Score::update_Matrix(int i){
	m_pRect->left	= int( 51.2f*m_DigitArr[i] );
	m_pRect->right	= int( 51.2f*(m_DigitArr[i]+1) );

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos.x+(i*20.0f),m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mPos ;
}

/**************************************************************************
 DeadScore ��`��
***************************************************************************/
/**************************************************************************
 DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
DeadScore::DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, MAX_DIGIT_DEAD, Rect )
{
}

/**************************************************************************
 DeadScore::~DeadScore();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
DeadScore::~DeadScore(){
	Score::~Score();
}

/**************************************************************************
 DeadScore::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	DeadScore::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 DeadScore::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	DeadScore::Update(UpdatePacket& i_UpdatePacket){

	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	if(m_pCoil != NULL)
		m_iScore	= m_pCoil->getDeadCount();

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 ArrivalPos ��`��
***************************************************************************/
/**************************************************************************
 ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
ArrivalPos::ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, MAX_DIGIT_DEAD, Rect )
{
}

/**************************************************************************
 ArrivalPos::~ArrivalPos();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ArrivalPos::~ArrivalPos(){
	Score::~Score();
}

/**************************************************************************
 ArrivalPos::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	ArrivalPos::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 ArrivalPos::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	ArrivalPos::Update(UpdatePacket& i_UpdatePacket){

	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	if(m_pCoil != NULL){
		if( m_iScore < int(m_pCoil->getPos().y)-5 )
			m_iScore	= int(m_pCoil->getPos().y)-5;
	}
	if( m_iScore < 0 )
		m_iScore	= 0;

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 GoalPos ��`��
***************************************************************************/
/**************************************************************************
 GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
GoalPos::GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, MAX_DIGIT_DEAD, Rect )
,m_pGoalObject(NULL)
{
}

/**************************************************************************
 GoalPos::~GoalPos();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
GoalPos::~GoalPos(){
	Score::~Score();
	m_pGoalObject = NULL;
}

/**************************************************************************
 GoalPos::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	GoalPos::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 GoalPos::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	GoalPos::Update(UpdatePacket& i_UpdatePacket){

	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	if(m_pGoalObject == NULL){
		m_pGoalObject = (GoalObject*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CLEARAREA);
	}
	if(m_pGoalObject != NULL){
		//if( m_iScore < int(m_pCoil->getPos().y)-5 )
		//	m_iScore	= int(m_pCoil->getPos().y)-5;
		D3DXVECTOR3	s,p,r;
		//m_pGoalObject->GetBaseScalePosRot(s,p,r);
		m_pGoalObject->GetWorldPos(p);
		m_iScore = (int)(p.y);
	}
	if( m_iScore < 0 )
		m_iScore	= 0;

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 Factory_Score ��`��
****************************************************************************/
/**************************************************************************
 Factory_Score::Factory_Score(
	Factory_Score *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Score::Factory_Score(FactoryPacket *fpac){
	try{
		//DeadCount
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"dead_count1.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 760.0f, 13.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//NowPos
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MAX_RANGE1.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 760.0f, 80.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//Slash
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"slash2.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 870.0f, 105.0f, 0.0f ),					
					&Rect( 0, 0, 64, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//���S��
		fpac->m_pVec->push_back(
			new DeadScore( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base1.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 900.0f, 40.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 50.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);

		//���B�n�_
		fpac->m_pVec->push_back(
			new ArrivalPos( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 780.0f, 110.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//�S�[���n�_
		fpac->m_pVec->push_back(
			new GoalPos( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 900.0f, 110.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Score::~Factory_Score();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Score::~Factory_Score(){
    //�Ȃɂ����Ȃ�
}

}
}
