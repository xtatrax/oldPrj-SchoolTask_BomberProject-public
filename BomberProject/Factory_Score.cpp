#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Score.h"
#include "BassItems.h"
#include "Factory_Cursor.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Score 定義部
***************************************************************************/
/**************************************************************************
 Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
Score::Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect,
				wiz::OBJID	id		)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0xFFFFFFFF, id, true )
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
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Score::~Score(){
	m_pCoil	= NULL;
}

/**************************************************************************
 Score::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
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
 用途: 更新
 戻り値: なし
***************************************************************************/
void	Score::Update(UpdatePacket& i_UpdatePacket){

	int	iDigit	= 100000;
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
 用途: マトリックスの更新
 戻り値: なし
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
 DeadScore 定義部
***************************************************************************/
/**************************************************************************
 DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
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
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
DeadScore::~DeadScore(){
	Score::~Score();
}

/**************************************************************************
 DeadScore::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	DeadScore::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 DeadScore::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	DeadScore::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pCoil )	m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil )	m_iScore	= m_pCoil->getDeadCount();

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 ArrivalPos 定義部
***************************************************************************/
/**************************************************************************
 ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
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
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ArrivalPos::~ArrivalPos(){
	Score::~Score();
}

/**************************************************************************
 ArrivalPos::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	ArrivalPos::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 ArrivalPos::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	ArrivalPos::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil ){
		//コイルの現在位置
		m_iScore	= int(m_pCoil->getPos().y)-5;
		//Max到達点
		if( m_iMaxPosY < m_iScore )
			m_iMaxPosY	= m_iScore;

		m_pCoil->setMaxPos( m_iMaxPosY );
	}
	if( m_iScore < 0 )
		m_iScore	= 0;

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 ScratchPoint 定義部
***************************************************************************/
/**************************************************************************
 ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
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
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ScratchPoint::~ScratchPoint(){
	Score::~Score();
}

/**************************************************************************
 ScratchPoint::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	ScratchPoint::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 ScratchPoint::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	ScratchPoint::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil ){
		m_iScore	=	m_pCoil->getScratchTime();
	}
	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 GoalPos 定義部
***************************************************************************/
/**************************************************************************
 GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
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
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
GoalPos::~GoalPos(){
	Score::~Score();
	m_pGoalObject = NULL;
}

/**************************************************************************
 GoalPos::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	GoalPos::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 GoalPos::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
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
 TimeScore 定義部
***************************************************************************/
/**************************************************************************
 TimeScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
TimeScore::TimeScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iTime,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect, OBJID_UI_TIME )
,m_iTime( iTime )
,m_fElapsedTime( 0 )
{
}

/**************************************************************************
 TimeScore::~TimeScore();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
TimeScore::~TimeScore(){
	Score::~Score();
}

/**************************************************************************
 TimeScore::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	TimeScore::Draw(DrawPacket& i_DrawPacket){
	Score::Draw( i_DrawPacket );
}

/**************************************************************************
 TimeScore::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	TimeScore::Update(UpdatePacket& i_UpdatePacket){

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	if( m_pCoil ){
		if( m_iTime == 0 ){
			m_pCoil->setState( COIL_STATE_DEAD );
		}
		else if( m_pCoil->getState() == COIL_STATE_MOVE || m_pCoil->getState() == COIL_STATE_STICK ){
			m_fElapsedTime	+= i_UpdatePacket.pTime->getElapsedTime();
			if( m_fElapsedTime >= 1.0f ){
				--m_iTime;
				m_fElapsedTime	= 0;
			}
		}
	}

	m_iScore	= m_iTime;
	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 AnimationScore 定義部
***************************************************************************/
/**************************************************************************
 AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
AnimationScore::AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				int			iDight,
				Rect*		Rect	)
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect )
,m_iResultScore( iScore )
,m_iDrawScore( 0 )
,m_bNext( false )
,m_bClickRock( false )
,m_fTransRate( float( iScore )/float(iDight) )
,m_iDight( iDight+1 )
,m_fTime( 0.0f )
{
}

/**************************************************************************
 AnimationScore::~AnimationScore();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
AnimationScore::~AnimationScore(){
	Score::~Score();
}

/**************************************************************************
 AnimationScore::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	AnimationScore::Draw(DrawPacket& i_DrawPacket){
	m_iScore	= m_iDrawScore;
	Score::Draw( i_DrawPacket );

}

/**************************************************************************
 AnimationScore::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	AnimationScore::Update(UpdatePacket& i_UpdatePacket){

	Score::Update( i_UpdatePacket );

	int	i	= 0;

	switch( m_iDight ){
		case	1:
			i	= 1;
			break;
		case	2:
			i	= 2;
			break;
		case	3:
			i	= 3;
			break;
		case	4:
		case	5:
			i	= 4;
			break;
		default:
			break;
	}

	if( m_iResultScore != 0 ){
		m_fTime	+= i_UpdatePacket.pTime->getElapsedTime();
		if( m_fTime >= 1.0f/(m_fTransRate) ){
			if( m_iResultScore > m_iDrawScore )
				m_iDrawScore	+= i;
			else{
				m_bNext	= true;
			}

			if( m_iResultScore < m_iDrawScore ){
				m_iDrawScore	= m_iResultScore;
			}

			m_fTime	= 0;
		}
		if( Cursor2D::getLButtonState() ){
			if( m_bClickRock )
				m_iDrawScore	= m_iResultScore;
		}
		else	m_bClickRock	= true;
	}
	else	m_bNext	= true;
}

/**************************************************************************
 ResultScore 定義部
***************************************************************************/
/**************************************************************************
 ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ResultScore::ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				LPDIRECT3DTEXTURE9	pRate10Tex,
				LPDIRECT3DTEXTURE9	pRate30Tex,
				LPDIRECT3DTEXTURE9	pRate1Tex,
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
,m_pRate10Tex( pRate10Tex )
,m_pRate30Tex( pRate30Tex )
,m_pRate1Tex( pRate1Tex )
{
	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;

	//int iMaxPos		= 482;
	//int iScratch	= 81;
	//int iDead		= 3;
	int iMaxPos		= iMaxPosScore;
	int iScratch	= iScratchScore;
	int iDead		= iDeadScore;

	D3DXVECTOR3	vScoreSize	= vScale;
	Rect		rScoreRect	= Rect( 0, 0, 512, 64 );

	int TotalScore	= (iMaxPos*10)+iScratch-(iDead*30);
	Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"MaxPos     = %d\n",iMaxPosScore);
	Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"Scratch    = %d\n",iScratchScore);
	Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"DeadCount  = %d\n",iDeadScore);
	Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"TotalScore = %d\n",TotalScore);

	int iDightMaxPos	= 0;
	int iDightScratch	= 0;
	int iDightDead		= 0;
	int iDightTotal		= 0;

	//*******************************************
	// MaxPosの桁数の取得
	int	i	= 10000, dight	= 5;
	while(1){
		iDightMaxPos	= iMaxPos / i;
		if( iDightMaxPos >= 1 ){
			iDightMaxPos	= dight;
			break;
		}
		iDightMaxPos	= 1;
		i	/= 10;
		dight--;
		if( i == 1 )	break;
	}

	//*******************************************
	// スクラッチの桁数の取得
	i	= 10000, dight	= 5;
	while(1){
		iDightScratch	= iScratch / i;
		if( iDightScratch >= 1 ){
			iDightScratch	= dight;
			break;
		}
		iDightScratch	= 1;
		i	/= 10;
		dight--;
		if( i == 1 )	break;
	}

	//*******************************************
	// 死亡回数の桁数の取得
	i	= 10000, dight	= 5;
	while(1){
		iDightDead	= iDead / i;
		if( iDightDead >= 1 ){
			iDightDead	= dight;
			break;
		}
		iDightDead	= 1;
		i	/= 10;
		dight--;
		if( i == 1 )	break;
	}

	//*******************************************
	// トータルスコアの桁数の取得
	i	= 10000, dight	= 5;
	while(1){
		iDightTotal	= TotalScore / i;
		if( iDightTotal >= 1 ){
			iDightTotal	= dight;
			break;
		}
		iDightTotal	= 1;
		i	/= 10;
		dight--;
		if( i == 1 )	break;
	}
	//*******************************************


	m_pMaxPos	= new AnimationScore( pD3DDevice, m_pMaxPosTex, vScoreSize,
						D3DXVECTOR3( wide, height-115.0f, 0.0f ), iMaxPos, iDightMaxPos, &rScoreRect);
	m_pScratch	= new AnimationScore( pD3DDevice, m_pMaxPosTex, vScoreSize,
						D3DXVECTOR3( wide, height-35.0f, 0.0f ), iScratch, iDightScratch, &rScoreRect);
	m_pDead		= new AnimationScore( pD3DDevice, m_pDeadTex, vScoreSize,
						D3DXVECTOR3( wide, height+45.0f, 0.0f ), iDead, iDightDead, &rScoreRect);
	m_pTotal	= new AnimationScore( pD3DDevice, m_pMaxPosTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
						D3DXVECTOR3( wide+50, height+120.0f, 0.0f ), TotalScore, iDightTotal, &rScoreRect);
	m_pRate_10	= new SpriteObject( pD3DDevice, m_pRate10Tex, vScoreSize, g_vZero, 
									D3DXVECTOR3( wide+250.0f, height-115.0f, 0.0f ), Rect( 0, 0, 256, 64 ),g_vZero, g_vZero );
	m_pRate_1	= new SpriteObject( pD3DDevice, m_pRate1Tex, vScoreSize, g_vZero, 
									D3DXVECTOR3( wide+250.0f, height-35.0f, 0.0f ), Rect( 0, 0, 256, 64 ),g_vZero, g_vZero );
	m_pRate_30	= new SpriteObject( pD3DDevice, m_pRate30Tex, vScoreSize, g_vZero, 
									D3DXVECTOR3( wide+250.0f, height+45.0f, 0.0f ), Rect( 0, 0, 256, 64 ),g_vZero, g_vZero );

}



/**************************************************************************
 ResultScore::~ResultScore();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ResultScore::~ResultScore(){
	m_pSelect	= NULL;
	SafeDelete(m_pDead);
	SafeDelete(m_pScratch);
	SafeDelete(m_pMaxPos);
	SafeDelete(m_pTotal);
	SafeDelete(m_pRate_10);
	SafeDelete(m_pRate_1);
	SafeDelete(m_pRate_30);
}

/**************************************************************************
 ResultScore::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	ResultScore::Draw(DrawPacket& i_DrawPacket){
	m_pMaxPos->Draw( i_DrawPacket );
	m_pScratch->Draw( i_DrawPacket );
	m_pDead->Draw( i_DrawPacket );
	m_pTotal->Draw( i_DrawPacket );
	m_pRate_10->Draw( i_DrawPacket );
	m_pRate_1->Draw( i_DrawPacket );
	m_pRate_30->Draw( i_DrawPacket );
}

/**************************************************************************
 ResultScore::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
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
 Factory_Score 定義部
****************************************************************************/
/**************************************************************************
 Factory_Score::Factory_Score(
	Factory_Score *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Score::Factory_Score(FactoryPacket *fpac){
	try{
		//Time
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TIME2.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 50.0f, 10.0f, 0.0f ),			
					&Rect( 0, 0, 256, 64 ),
					g_vZero,
					g_vZero
			)
		);

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
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"NOW_RANGE1.png" ),
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
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"SCRATCH_TIME2.png" ),
					D3DXVECTOR3( 0.5f, 0.65f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 10.0f, 516.0f, 0.0f ),					
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

		//死亡回数
		fpac->m_pVec->push_back(
			new DeadScore( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base1.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 850.0f, 40.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 50.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);

		//到達地点
		fpac->m_pVec->push_back(
			new ArrivalPos( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 730.0f, 550.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//ゴール地点
		fpac->m_pVec->push_back(
			new GoalPos( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 850.0f, 550.0f, 0.0f ),					
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
		//Time
		fpac->m_pVec->push_back(
			new TimeScore( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Number_Base1.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 30.0f, 50.0f, 0.0f ),
					LIMIT_TIME,
					&Rect( 0, 0, 512, 64 )
			)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Score::~Factory_Score();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Score::~Factory_Score(){
    //なにもしない
}

}
}
