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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
Score::Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
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
,m_bTotal( false )
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
		if( m_bFirst || m_bTotal )
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

	int	iDigit	= MAX_DIGHT_SCORE/10;
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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
DeadScore::DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
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

	if( !m_pCoil )	m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

	if( m_pCoil )	m_iScore	= m_pCoil->getDeadCount();

	Score::Update( i_UpdatePacket );
}

/**************************************************************************
 ArrivalPos 定義部
***************************************************************************/
/**************************************************************************
 ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ArrivalPos::ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
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

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ScratchPoint::ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
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

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
GoalPos::GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
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

	if( !m_pCoil       )	m_pCoil			= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL			) ;
	if( !m_pGoalObject )	m_pGoalObject	= (GoalObject*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CLEARAREA	) ;

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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
TimeScore::TimeScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iTime,
				Rect*		Rect)
:Score( pD3DDevice, pTexture, vScale, vPos, 0, Rect, OBJID_UI_TIME )
,m_iTime( iTime )
,m_fElapsedTime( 0 )
,m_bIsCoilKillConcrete( false )

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

	if( !m_pCoil ) m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

	if( m_pCoil ){
		if( m_iTime == 0 ){
			if( !m_bIsCoilKillConcrete ){
				m_bIsCoilKillConcrete = true ;
				m_pCoil->setState( COIL_STATE_DEAD );
			}
		}
		else if( m_pCoil->getState() == COIL_STATE_MOVE || m_pCoil->getState() == COIL_STATE_STICK ){
			m_fElapsedTime	+= (float)i_UpdatePacket.GetTime()->getElapsedTime();
			if( m_fElapsedTime >= 1.0f ){
				--m_iTime;
				m_fElapsedTime	= 0;
			}
			m_bIsCoilKillConcrete = false ;
		}else{
			m_bIsCoilKillConcrete = false ;
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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
AnimationScore::AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				int			iDight,
				bool		bTotal,
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
	m_bTotal	= bTotal;
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
			i	= 1;
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
		m_fTime	+= (float)i_UpdatePacket.GetTime()->getElapsedTime();
		if( m_fTime >= 1.0f/(m_fTransRate) ){
			if( m_iResultScore > m_iDrawScore ){
				m_iDrawScore	+= i;
				if( m_iResultScore != m_iDrawScore )
					i_UpdatePacket.SearchWaveAndPlay(RCTEXT_SOUND_SE_COUNT_UP);
				else{
					if( m_iResultScore != 0 )
						i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
				}
			}else{
				m_bNext	= true;
			}

			if( m_iResultScore < m_iDrawScore ){
				m_iDrawScore	= m_iResultScore;
			}

			m_fTime	= 0;
		}
		if( Cursor2D::getLButtonState() ){
			if( m_bClickRock ){
				m_iDrawScore	= m_iResultScore;
				if( m_iResultScore != 0 )
					i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
			}
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
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ResultScore::ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pDeadTex,
				LPTATRATEXTURE	pMaxPosTex,
				LPTATRATEXTURE	pRate10Tex,
				LPTATRATEXTURE	pRate30Tex,
				LPTATRATEXTURE	pRate1Tex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
				int			iScratchScore,
				Rect*		rect	)
:Score( pD3DDevice, NULL, vScale, vPos, 0, rect )
,m_iNowDraw( 0 )
,m_pDeadTex( pDeadTex )
,m_pMaxPosTex( pMaxPosTex )
,m_pRate10Tex( pRate10Tex )
,m_pRate30Tex( pRate30Tex )
,m_pRate1Tex( pRate1Tex )
,m_pRank( NULL )
,m_ResultRank( Rank_C )
{
	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;

	//int iMaxPos		= 482;
	//int iScratch	= 81;
	//int iDead		= 3;
	int iMaxPos		= iMaxPosScore;
	int iScratch	= iScratchScore;
	int iDead		= iDeadScore;
	D3DXVECTOR3 vRateSize( 0.5f, 0.5f, 0.0f ) ;
	D3DXVECTOR3	vScoreSize	= vScale;
	Rect		rScoreRect	= Rect( 0, 0, 512, 64 );

	int TotalScore	= (iMaxPos*10)+iScratch-(iDead*30);
	if( TotalScore >= MAX_DIGHT_SCORE )
		TotalScore	= MAX_DIGHT_SCORE-1;
	//Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"MaxPos     = %d\n",iMaxPosScore);
	//Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"Scratch    = %d\n",iScratchScore);
	//Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"DeadCount  = %d\n",iDeadScore);
	//Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"TotalScore = %d\n",TotalScore);

	//点数に応じたランクの設定************************************
	if( TotalScore >= 10000 )		m_ResultRank	= Rank_S;
	else if( TotalScore >= 5000 )	m_ResultRank	= Rank_A;
	else if( TotalScore >= 2500 )	m_ResultRank	= Rank_B;
	else							m_ResultRank	= Rank_C;
	//***************************************************************

	int iDightMaxPos	= 0;
	int iDightScratch	= 0;
	int iDightDead		= 0;
	int iDightTotal		= 0;

	//*******************************************
	// MaxPosの桁数の取得
	int	i	= MAX_DIGHT_SCORE/10, dight	= MAX_DIGIT;
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
	i	= MAX_DIGHT_SCORE/10, dight	= MAX_DIGIT;
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
	i	= MAX_DIGHT_SCORE/10, dight	= MAX_DIGIT;
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
	i	= MAX_DIGHT_SCORE/10, dight	= MAX_DIGIT;
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

	m_pMaxPos	= new AnimationScore(
		pD3DDevice,
		pMaxPosTex,
		vScoreSize,
		D3DXVECTOR3( wide+90.0f, height-140.0f, 0.0f ),
		iMaxPos,
		iDightMaxPos,
		false,
		&rScoreRect
	);
	m_pScratch	= new AnimationScore(
		pD3DDevice,
		pMaxPosTex,
		vScoreSize,
		D3DXVECTOR3( wide+90.0f, height-70.0f, 0.0f ),
		iScratch,
		iDightScratch,
		false,
		&rScoreRect);
	m_pDead		= new AnimationScore(
		pD3DDevice,
		pDeadTex, 
		vScoreSize,
		D3DXVECTOR3( wide+90.0f, height+5.0f, 0.0f ),
		iDead,
		iDightDead,
		false,
		&rScoreRect);
	m_pTotal	= new AnimationScore(
		pD3DDevice,
		pMaxPosTex,
		D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
		D3DXVECTOR3( 500.0f, height+160.0f, 0.0f ),
		TotalScore,
		iDightTotal,
		true,
		&rScoreRect);
	m_pRate_10	= new SpriteObject(
		pD3DDevice,
		pRate10Tex,
		vRateSize,
		g_vZero, 
		D3DXVECTOR3( wide+340.0f, height-140.0f+15.0f, 0.0f ),
		&Rect( 0, 0, 256, 64 ),
		g_vZero,
		g_vZero );
	m_pRate_1	= new SpriteObject(
		pD3DDevice,
		pRate1Tex,
		vRateSize,
		g_vZero, 
		D3DXVECTOR3( wide+340.0f, height-70.0f+15.0f, 0.0f ),
		&Rect( 0, 0, 256, 64 ),
		g_vZero,
		g_vZero );
	m_pRate_30	= new SpriteObject(
		pD3DDevice,
		pRate30Tex,
		vRateSize,
		g_vZero, 
		D3DXVECTOR3( wide+340.0f, height+20.0f, 0.0f ),
		&Rect( 0, 0, 256, 64 ),
		g_vZero,
		g_vZero );


}



/**************************************************************************
 ResultScore::~ResultScore();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ResultScore::~ResultScore(){
	m_pRank		= NULL;
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

	if( !m_pRank )		m_pRank		= (Rank*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_RANK ) ;

	switch( m_iNowDraw ){
		case 0:
			//i_UpdatePacket.SearchWaveAndPlay(RCTEXT_SOUND_SE_COUNT_UP);
			m_pMaxPos->Update( i_UpdatePacket );
			if( m_pMaxPos->getNext() ){
				++m_iNowDraw;
				//i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
			}
			break;
		case 1:
			///i_UpdatePacket.SearchWaveAndPlay(RCTEXT_SOUND_SE_COUNT_UP);
			m_pScratch->Update( i_UpdatePacket );
			if( m_pScratch->getNext() ){
				++m_iNowDraw;
				//i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
			}
			break;
		case 2:
			//i_UpdatePacket.SearchWaveAndPlay(RCTEXT_SOUND_SE_COUNT_UP);
			m_pDead->Update( i_UpdatePacket );
			if( m_pDead->getNext() ){
				++m_iNowDraw;
				//i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
			}
			break;
		case 3:
			//i_UpdatePacket.SearchWaveAndPlay(RCTEXT_SOUND_SE_COUNT_UP);
			m_pTotal->Update( i_UpdatePacket );
			if( m_pTotal->getNext() ){
				++m_iNowDraw;
				//i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_COUNT_FINISH );
			}
			break;
		default:
			if( m_pRank )
				m_pRank->setDrawing( true, m_ResultRank );
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
		fpac->AddObject(
			new SpriteObject( fpac->GetDevice(),
					fpac->AddTexture( L"GAGE6.png" ),
					D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 10.0f, 10.0f, 0.0f ),		
					&Rect( 129, 96, 256, 127 ),
					g_vZero,
					g_vZero
			)
		);

		//DeadCount
		fpac->AddObject(
			new SpriteObject( fpac->GetDevice(),
					fpac->AddTexture( L"TEST.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 760.0f, 13.0f, 0.0f ),					
					&Rect( 0, 192, 512, 256 ),
					g_vZero,
					g_vZero
			)
		);

		//NowPos
		fpac->AddObject(
			new SpriteObject( fpac->GetDevice(),
					fpac->AddTexture( L"NOW_RANGE1.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 750.0f, 520.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//ScratchPoint
		fpac->AddObject(
			new SpriteObject( fpac->GetDevice(),
					fpac->AddTexture( L"SCRATCH_TIME2.png" ),
					D3DXVECTOR3( 0.5f, 0.65f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 15.0f, 516.0f, 0.0f ),				
					&Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero
			)
		);

		//Slash
		fpac->AddObject(
			new SpriteObject( fpac->GetDevice(),
					fpac->AddTexture( L"GAGE7.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 870.0f, 550.0f, 0.0f ),					
					&Rect( 64, 192, 128, 256 ),
					g_vZero,
					g_vZero
			)
		);

		//死亡回数
		fpac->AddObject(
			new DeadScore( fpac->GetDevice(),
					fpac->AddTexture( L"Number_Base1.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 850.0f, 40.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 50.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);

		//到達地点
		fpac->AddObject(
			new ArrivalPos( fpac->GetDevice(),
					fpac->AddTexture( L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 730.0f, 550.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//ゴール地点
		fpac->AddObject(
			new GoalPos( fpac->GetDevice(),
					fpac->AddTexture( L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 850.0f, 550.0f, 0.0f ),					
					//D3DXVECTOR3( 880.0f, 90.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//ScratchPoint
		fpac->AddObject(
			new ScratchPoint( fpac->GetDevice(),
					fpac->AddTexture( L"Number_Base2.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 100.0f, 550.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
		//Time
		fpac->AddObject(
			new TimeScore( fpac->GetDevice(),
					fpac->AddTexture( L"Number_Base1.png" ),
					D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
					D3DXVECTOR3( 10.0f, 50.0f, 0.0f ),
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
