#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Score.h"
#include "BassItems.h"
#include "Factory_Cursor.h"

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
				int			iScore,
				Rect*		Rect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0xFFFFFFFF, OBJID_UI_SCORE, false )
,m_vPos( vPos )
,m_vScale( vScale )
,m_iScore( iScore )
,m_bFirst( false )
,m_pCoil( NULL )
{
	for( int i = 0; i < MAX_DIGIT; i++ )
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
	for( int i = 0; i < MAX_DIGIT ; i++ ){
		update_Matrix( i );
		if( !m_bFirst ){
			if( m_DigitArr[i] != 0 )
				m_bFirst	= true;
			else if( i == MAX_DIGIT-1 )
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

	int	iDigit	= 10000;
	for( int i = 0; i < MAX_DIGIT; i++ ){
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
	D3DXMatrixTranslation(&mPos,m_vPos.x+(i*50.0f*m_vScale.x),m_vPos.y,m_vPos.z);
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
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
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

	if( !m_pCoil )	m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil )	m_iScore	= m_pCoil->getDeadCount();

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
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
,m_iMaxPosY( 0 )
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

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil ){
		//�R�C���̌��݈ʒu
		m_iScore	= int(m_pCoil->getPos().y)-5;
		//Max���B�_
		if( m_iMaxPosY < m_iScore )
			m_iMaxPosY	= m_iScore;

		m_pCoil->setMaxPos( m_iMaxPosY );
	}
	if( m_iScore < 0 )
		m_iScore	= 0;

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 ScratchPoint ��`��
***************************************************************************/
/**************************************************************************
 ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
ScratchPoint::ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
{
}

/**************************************************************************
 ScratchPoint::~ScratchPoint();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ScratchPoint::~ScratchPoint(){
	Score::~Score();
}

/**************************************************************************
 ScratchPoint::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	ScratchPoint::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 ScratchPoint::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	ScratchPoint::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil ){
		m_iScore	=	m_pCoil->getScratchTime();
	}
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
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
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

	if( !m_pCoil       )	m_pCoil			= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL			) ;
	if( !m_pGoalObject )	m_pGoalObject	= (GoalObject*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CLEARAREA	) ;

	if(m_pGoalObject != NULL){
		//if( m_iScore < int(m_pCoil->getPos().y)-5 )
		//	m_iScore	= int(m_pCoil->getPos().y)-5;
		D3DXVECTOR3	s,p,r;
		//m_pGoalObject->GetBaseScalePosRot(s,p,r);
		m_pGoalObject->GetWorldPos(p);
		m_iScore = (int)(p.y)-2;
	}
	if( m_iScore < 0 )
		m_iScore	= 0;

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 AnimationScore ��`��
***************************************************************************/
/**************************************************************************
 AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
AnimationScore::AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect	)
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
,m_iResultScore( iScore )
,m_iDrawScore( 0 )
,m_bNext( false )
,m_bClickRock( false )
{
}

/**************************************************************************
 AnimationScore::~AnimationScore();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
AnimationScore::~AnimationScore(){
	Score::~Score();
}

/**************************************************************************
 AnimationScore::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	AnimationScore::Draw(DrawPacket& i_DrawPacket){
	m_iScore	= m_iDrawScore;
	Score::Draw( i_DrawPacket );

}

/**************************************************************************
 AnimationScore::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	AnimationScore::Update(UpdatePacket& i_UpdatePacket){

	Score::Update( i_UpdatePacket );

	if( m_iResultScore > m_iDrawScore )
		++m_iDrawScore;
	else
		m_bNext	= true;

	if( Cursor2D::getLButtonState() ){
		if( m_bClickRock )
			m_iDrawScore	= m_iResultScore;
	}
	else	m_bClickRock	= true;
}

/**************************************************************************
 ResultScore ��`��
***************************************************************************/
/**************************************************************************
 ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 �p�r�@�F�R���X�g���N�^
 �߂�l�F�Ȃ�
 �S���ҁF������
***************************************************************************/
ResultScore::ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
				int			iScratchScore,
				Rect*		rect	)
:Score( pD3DDevice, NULL, vScale, vPos, 0, rect )
,m_pDeadTex( pDeadTex )
,m_pMaxPosTex( pMaxPosTex )
,m_iNowDraw( 0 )
,m_pSelect( NULL )
{
	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;

	int iDead		= iDeadScore;
	int iMaxPos		= iMaxPosScore;
	int iScratch	= iScratchScore;

	D3DXVECTOR3	vScoreSize	= vScale;
	Rect		rScoreRect	= Rect( 0, 0, 512, 64 );

	int TotalScore	= (iMaxPos+iScratch-iDead)*10;

	m_pMaxPos	= new AnimationScore( pD3DDevice, m_pMaxPosTex, vScoreSize,
						D3DXVECTOR3( wide+100.0f, height-120.0f, 0.0f ), iMaxPos, &rScoreRect);
	m_pScratch	= new AnimationScore( pD3DDevice, m_pMaxPosTex, vScoreSize,
						D3DXVECTOR3( wide+100.0f, height-50.0f, 0.0f ), iScratch, &rScoreRect);
	m_pDead		= new AnimationScore( pD3DDevice, m_pDeadTex, vScoreSize,
						D3DXVECTOR3( wide+100.0f, height+30.0f, 0.0f ), iDead, &rScoreRect);
	m_pTotal	= new AnimationScore( pD3DDevice, m_pDeadTex, vScoreSize,
						D3DXVECTOR3( wide+100.0f, height+100.0f, 0.0f ), TotalScore, &rScoreRect);

}

/**************************************************************************
 ResultScore::~ResultScore();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ResultScore::~ResultScore(){
	m_pSelect	= NULL;
	SafeDelete(m_pDead);
	SafeDelete(m_pScratch);
	SafeDelete(m_pMaxPos);
	SafeDelete(m_pTotal);
}

/**************************************************************************
 ResultScore::Draw(DrawPacket& i_DrawPacket);
 �p�r: �`��
 �߂�l: �Ȃ�
***************************************************************************/
void	ResultScore::Draw(DrawPacket& i_DrawPacket){
	m_pMaxPos->Draw( i_DrawPacket );
	m_pScratch->Draw( i_DrawPacket );
	m_pDead->Draw( i_DrawPacket );
	m_pTotal->Draw( i_DrawPacket );
}

/**************************************************************************
 ResultScore::Update(UpdatePacket& i_UpdatePacket)
 �p�r: �X�V
 �߂�l: �Ȃ�
***************************************************************************/
void	ResultScore::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pSelect )	m_pSelect	= (Title_Select*)SearchObjectFromTypeID(i_UpdatePacket.pVec, typeid(Title_Select) ) ;

	switch( m_iNowDraw ){
		case 0:
			m_pMaxPos->Update( i_UpdatePacket );
			if( m_pMaxPos->getNext() )
				++m_iNowDraw;
			break;
		case 1:
			m_pScratch->Update( i_UpdatePacket );
			if( m_pScratch->getNext() )
				++m_iNowDraw;
			break;
		case 2:
			m_pDead->Update( i_UpdatePacket );
			if( m_pDead->getNext() )
				++m_iNowDraw;
			break;
		case 3:
			m_pTotal->Update( i_UpdatePacket );
			if( m_pTotal->getNext() )
				++m_iNowDraw;
			break;
		default:
			if( m_pSelect )
				m_pSelect->setCanSelect(true);
			break;
	}
	
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
					D3DXVECTOR3( 750.0f, 520.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//ScratchPoint
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"ScratchPoint.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 10.0f, 500.0f, 0.0f ),					
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
					D3DXVECTOR3( 870.0f, 550.0f, 0.0f ),					
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
					D3DXVECTOR3( 780.0f, 550.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//�S�[���n�_
		fpac->m_pVec->push_back(
			new GoalPos( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 900.0f, 550.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//ScratchPoint
		fpac->m_pVec->push_back(
			new ScratchPoint( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 100.0f, 550.0f, 0.0f ),					
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
