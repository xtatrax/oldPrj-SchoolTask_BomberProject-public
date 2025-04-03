////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Continue.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：コンテニュー
//					▼
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_Continue.h"

//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberobject{
///************************************************************************
//ContinueButton 定義部
//************************************************************************/
ContinueButton::ContinueButton(
		const LPDIRECT3DDEVICE9		pD3DDevice			,
		const LPTATRATEXTURE		pTexture			,
		const D3DXVECTOR3			vScalse				,
		const D3DXVECTOR3			vPos				,
		const Rect*					pRect				,
		const float					fWaitTime			,
		const Command				Com					,
		const wiz::OBJID			id					
)
:ButtonSprite(pD3DDevice,pTexture,vScalse,g_vZero,vPos,pRect,g_vZero,g_vZero,0xFFFFFFFF,0x88888888,
		RCTEXT_SOUND_SE_SELECT	,RCTEXT_SOUND_SE_ENTER	, fWaitTime, Com, id)
,m_bIsOperating(false)

{
	
}
void ContinueButton::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_bIsOperating ) return ;
	ButtonSprite::Update(i_UpdatePacket);
	m_IssueCommand = i_UpdatePacket.PopCommand() ;
}
void ContinueButton::Draw(DrawPacket& i_DrawPacket){
	if( !m_bIsOperating ) return ;
	ButtonSprite::Draw(i_DrawPacket);
}
///************************************************************************
//ContinueBehavior 定義部
//************************************************************************/

ContinueBehavior::ContinueBehavior(
		FactoryPacket& i_BassPacket
)
:Behavior(  OBJID_BEHAVIOR_CONTINUE)
,m_pPTContinue( NULL )
,m_pPTReally( NULL )
,m_pCoil(NULL)
,m_pTime(NULL)
,m_fDeadMessageTimeAccumulator( 0 )
,m_fFadeOutTimeAccumulator( 0 )
,m_fMessageTime( 1.0f )
,m_fFadeOutTime( 1.0f )
,m_fDeadMessageAlpha(255.0f)
,m_NowBehaviorFaze(CONTINUEBEHAVIORPHASE_WAIT)
{
	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;
	LPDIRECT3DDEVICE9 pD3DDevice = i_BassPacket.GetDevice();
	m_pPTContinue	= i_BassPacket.AddTexture(L"CONTINUE4.png");
	m_pPTReally		= i_BassPacket.AddTexture(L"REALLY4.png");
	D3DXVECTOR3	vScale	= D3DXVECTOR3( 0.5f, 0.5f, 0.0f );
	D3DXVECTOR3	vPos	= D3DXVECTOR3( (wide-512.0f*vScale.x), (height-256.0f*vScale.y-100), 0.0f );
	//	: ページタイトル
	m_pPageTitle = new SpriteObject(
		pD3DDevice				,
		m_pPTContinue			,
		g_vOne					,
		g_vZero					,
		D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ),
		&Rect( 0, 0, 512, 64 )	,
		g_vZero					,
		g_vZero					
	);

	//	: デッドメッセージ
	m_pDeadMessage = new SpriteObject(
		pD3DDevice				,
		i_BassPacket.AddTexture(L"dead6.png")	,
		vScale					,
		g_vZero					,
		vPos					,
		NULL					,
		g_vZero					,
		g_vZero					
	);

	//	: YESボタン
	i_BassPacket.AddButton( m_pYesButton = new ContinueButton(
		pD3DDevice				,
		i_BassPacket.AddTexture(L"TEST.png")	,
		g_vOne					,
		D3DXVECTOR3(wide-128.0f,height-50.0f,0.0f),
		&Rect( 0,0,256,64 )		,
		0.0f					,
		GM_CONTINUEBUTTON_YES	,
		OBJID_UI_BUTTON_YES		
		)
	);
	//	: NOボタン
	i_BassPacket.AddButton( m_pNoButton = new ContinueButton(
		pD3DDevice				,
		i_BassPacket.AddTexture(L"TEST.png")	,
		g_vOne					,
		D3DXVECTOR3(wide-128.0f,height+100.0f,0.1f),
		&Rect( 256,0,512,64 )	,
		0.0f					,
		GM_CONTINUEBUTTON_NO	,
		OBJID_UI_BUTTON_NO		
		)
	);

	D3DXVECTOR3	vScoreScale		= D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
	D3DXVECTOR3	vScorePos		= D3DXVECTOR3( wide+40.0f*vScoreScale.x-100.0f, height-32.0f*vScoreScale.y+65.0f, 0.0f );
	D3DXVECTOR3	vCountCharScale	= D3DXVECTOR3( 0.6f, 2.0f, 0.0f );
	D3DXVECTOR3	vCountCharPos	= D3DXVECTOR3( wide-256-40, height, 0.0f );

	m_pDeadScore			= new Score(
			pD3DDevice		,
			i_BassPacket.AddTexture(L"Number_Base1.png")	,
			vScoreScale		,
			vScorePos		,
			0		,
			&Rect( 0, 0, 512, 64 )
	);

	m_pDeadCountChar		= new SpriteObject(
			pD3DDevice		,
			i_BassPacket.AddTexture(L"dead_count1.png")	,
			vCountCharScale	,
			g_vZero			,
			vCountCharPos	,
			NULL,
			g_vZero,
			g_vZero
			
	);
	//m_pContinueChar	= new SpriteObject( pD3DDevice, m_pContinueTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
	//							D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ), Rect( 0, 0, 512, 64 ), g_vZero, g_vZero );

	//m_pRethinking	= new SpriteObject( pD3DDevice, m_pRethinkingTex, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
	//								D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ),Rect( 0,0,512,64 ), g_vZero, g_vZero  );
	//m_pReply_Yes	= new Reply(  pD3DDevice, m_pAnswerTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
	//								D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),Rect( 0,0,256,64 ), g_vZero, g_vZero  );
	//m_pReply_No		= new Reply(  pD3DDevice, m_pAnswerTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
	//								D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),Rect( 256,0,512,64 ), g_vZero, g_vZero  );

}

ContinueBehavior::~ContinueBehavior(){
	m_pPageTitle->setTexture(NULL);
	//SafeRelease(m_pPTContinue);
	//SafeRelease(m_pPTReally);
	SafeDelete(m_pPageTitle);
	SafeDelete(m_pDeadMessage);
	SafeDelete(m_pDeadScore);
	SafeDelete(m_pDeadCountChar);
	//m_pYesButton->Kill();
	//m_pYesButton = NULL ;
	//m_pNoButton->Kill() ;
	//m_pNoButton = NULL  ;
	//SafeDelete(m_pYesButton);
	//SafeDelete(m_pNoButton);
	m_pCoil = NULL ;

}


/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void ContinueBehavior::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil )  m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL );
	if( !m_pTime )	m_pTime	= ( TimeScore*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME );
	if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_WAIT ) return;


	if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE ){
		//	: デッドメッセージ描画フェイズ
		m_pDeadScore->Update(i_UpdatePacket);
		if( ( m_fDeadMessageTimeAccumulator += (float)i_UpdatePacket.GetTime()->getElapsedTime()) > m_fMessageTime){
			//	: フェードアウトフェイズ
			if( (m_fDeadMessageAlpha -= ( ( 255.0f / m_fFadeOutTime ) * (float)i_UpdatePacket.GetTime()->getElapsedTime())) <= 0.0f){
				m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_CONTINUESELECTION;
				m_pYesButton->OperationStart();
				m_pNoButton->OperationStart();
			}
			if( m_fDeadMessageAlpha <= 0 ) m_fDeadMessageAlpha = 0;
			m_pDeadMessage->setAlpha((BYTE)m_fDeadMessageAlpha);
			m_pDeadScore->setAlpha((BYTE)m_fDeadMessageAlpha);
			m_pDeadCountChar->setAlpha((BYTE)m_fDeadMessageAlpha);
		}
		//m_pDeadMessage->Update();
	}else{
		Command cmd;
		m_pYesButton->getIssueCommand(cmd);
		m_pNoButton->getIssueCommand(cmd);
		if( cmd.m_Command == GM_CONTINUEBUTTON_YES ){
			if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_CONTINUESELECTION ){
				//	: コイルへ復帰命令
				m_pCoil->setReadyContinue(true);
				m_pYesButton->OperationEnd();
				m_pNoButton->OperationEnd();
				m_pTime->setTime();
				OperationStop();

			}else if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_CHECKSELECTION ){
				//	: リザルト画面へ遷移命令
				i_UpdatePacket.PushCommand( 
					Command(
						GM_OPENSTAGE_RESULT			,
						m_pCoil->getDeadCount()		,
						m_pCoil->getMaxPos()		,
						m_pCoil->getScratchTime()
					)
				);
			}
		}
		if( cmd.m_Command == GM_CONTINUEBUTTON_NO ){
			if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_CONTINUESELECTION ){
				//	: 確認が目へ
				m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_CHECKSELECTION ;
				m_pPageTitle->setTexture(m_pPTReally);
				m_pYesButton->setWaitTime(0.7f);
			}else if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_CHECKSELECTION ){
				//	: 復帰選択へ
				m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_CONTINUESELECTION ;
				m_pPageTitle->setTexture(m_pPTContinue);
				m_pYesButton->setWaitTime(0.0f);
			}
		}
	}

};
/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void ContinueBehavior::Draw( DrawPacket& i_DrawPacket ){
	if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_WAIT ) return;
	if( m_NowBehaviorFaze == CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE ){

		m_pDeadMessage->Draw(i_DrawPacket);
		m_pDeadScore->Draw(i_DrawPacket);
		m_pDeadCountChar->Draw(i_DrawPacket);
	}else{
		m_pPageTitle->Draw(i_DrawPacket);
		//m_pYesButton->Draw(i_DrawPacket);
		//m_pNoButton->Draw(i_DrawPacket);
	}
};

///************************************************************************
//Reply 定義部
//************************************************************************/
///////////////////// ////////////////////
////// 関数名     ：Reply(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,DWORD next,
//////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
//////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
////// カテゴリ   ：コンストラクタ
////// 用途       ：タイトルへ戻るの再確認
////// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
//////            ：  LPTATRATEXTURE pTexture     // 貼り付けたいテクスチャ
//////            ：  DWORD next                      // 次の画面
//////            ：  D3DXVECTOR3 &vScale             // 大きさ
//////            ：  D3DXVECTOR3 &vRot               // 三軸回転
//////            ：  D3DXVECTOR3 &vPos               // 設置座標
//////            ：  Rect* pRect                     // 描画したい範囲(NULLで全体を描画)
//////            ：  D3DXVECTOR3& vCenter            // 中心
//////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
//////            ：  Color color = 0xFFFFFFFF        // 色
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//Reply::Reply(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPTATRATEXTURE pTexture,const bool mark,
//		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
//		const Rect *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
//:SpriteObject(	pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
//,m_vPos(		vPos	)
//,m_bMark(		mark	)
//,m_bPushRock(	false	)
//,m_bWhichDraw(	false	)
//,m_iTime(		0		)
//,m_bPush(		false	)
//,m_bSelect(		false	)
//,m_pCoil(		NULL	)
//{
//	try{
//		//	: 初期マトリックスを計算
//		D3DXMATRIX mScale,mRot,mPos;
//		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
//		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
//		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
//		m_mMatrix = mScale * mRot * mPos ;
//
//	}
//	catch(...){
//		SafeRelease(m_pSprite);
//		//再スロー
//		throw;
//	}
//};
//
//Reply::~Reply(){
//	m_pCoil		= NULL;
//}
///////////////////// ////////////////////
////// 関数名     ：void Reply::Draw( DrawPacket& i_DrawPacket)
////// カテゴリ   ：関数
////// 用途       ：スプライトを描画
////// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Reply::Draw(DrawPacket& i_DrawPacket)
//{
//	//	: 描画は親クラスに任せる
//	SpriteObject::Draw(i_DrawPacket);
//};
//
///////////////////// ////////////////////
////// 関数名     ：void Reply::Update( UpdatePacket& i_UpdatePacket)
////// カテゴリ   ：関数
////// 用途       ：データの更新
////// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Reply::Update(UpdatePacket& i_UpdatePacket)
//{
//	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);
//	if( Cursor2D::isHitSprite( this ) ){
//		if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
//			if( m_bPushRock ){
//				if( m_bMark ){
//					i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_RESULT;
//					i_UpdatePacket.pCommand->m_Param1	= m_pCoil->getDeadCount();
//					i_UpdatePacket.pCommand->m_Param2	= m_pCoil->getMaxPos();
//					i_UpdatePacket.pCommand->m_Param3	= m_pCoil->getScratchTime();
//				}
//				else{
//					m_bWhichDraw	= true;
//				}
//				if( !m_bPush ){
//					i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
//				}
//				m_bPush		= true;
//				m_bPushRock	= false;
//			}
//		}
//		else	m_bPushRock	= true;
//		m_Color	= 0xFFFFFFFF;
//		if( !m_bSelect ){
//			m_bSelect = true;
//			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
//		}
//	}
//	else{
//		//	: マウスが画像の範囲外にいるとき
//		m_Color	= 0xA0FFFFFF;
//		m_bSelect = false;
//		if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
//		else				m_bPushRock	= true;
//	}
//	if( m_bPush ){
//		m_iTime++;
//		if( m_iTime > 30 ){
//			//選ばれた画面へとぶ
//			i_UpdatePacket.pCommand->m_Command	= m_dNext;
//			m_bPush = false ;
//		}
//	}
//
//};
//
///************************************************************************
//Continue 定義部
//************************************************************************/
///////////////////// ////////////////////
////// 関数名     ：Continue(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,DWORD next,
//////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
//////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
////// カテゴリ   ：コンストラクタ
////// 用途       ：コンテニューするか確認
////// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
//////            ：  LPTATRATEXTURE pTexture     // 貼り付けたいテクスチャ
//////            ：  DWORD next                      // 次の画面
//////            ：  D3DXVECTOR3 &vScale             // 大きさ
//////            ：  D3DXVECTOR3 &vRot               // 三軸回転
//////            ：  D3DXVECTOR3 &vPos               // 設置座標
//////            ：  Rect* pRect                     // 描画したい範囲(NULLで全体を描画)
//////            ：  D3DXVECTOR3& vCenter            // 中心
//////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
//////            ：  Color color = 0xFFFFFFFF        // 色
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//Continue::Continue(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPTATRATEXTURE pTexture_Answer,
//		const LPTATRATEXTURE pTexture_Rethinking, const LPTATRATEXTURE pTexture_Continue,
//		const bool mark,const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vPos,
//		const Rect *pRect,const wiz::OBJID id, const  Color color)
//:SpriteObject( pD3DDevice, pTexture_Answer, vScale, g_vZero, vPos, pRect, g_vZero, g_vZero, color, id )
//,m_vPos( vPos )
//,m_bMark( mark )
//,m_pCoil( NULL )
//,m_pReply_Yes( NULL )
//,m_pReply_No( NULL )
//,m_pRethinking( NULL )
//,m_pContinueChar( NULL )
//,m_pTime( NULL )
//,m_bPushRock( false )
//,m_bWhichDraw( true )
//,m_pRethinkingTex(pTexture_Rethinking)
//,m_pAnswerTex(pTexture_Answer)
//,m_pContinueTex( pTexture_Continue )
//,m_iTime( 0 )
//,m_bPush( false )
//,m_bSelect( false )
//,m_bDrawing( false )
//{
//	try{
//		//	: 初期マトリックスを計算
//		D3DXMATRIX mScale,mPos;
//		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
//		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
//		m_mMatrix = mScale * mPos ;
//
//		float	wide	= BASE_CLIENT_WIDTH/2;
//		float	height	= BASE_CLIENT_HEIGHT/2;
//
//		//Continueロゴの作成
//		m_pContinueChar	= new SpriteObject( pD3DDevice, m_pContinueTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
//									D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ), Rect( 0, 0, 512, 64 ), g_vZero, g_vZero );
//
//		m_pRethinking	= new SpriteObject( pD3DDevice, m_pRethinkingTex, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
//										D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ),Rect( 0,0,512,64 ), g_vZero, g_vZero  );
//		m_pReply_Yes	= new Reply(  pD3DDevice, m_pAnswerTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
//										D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),Rect( 0,0,256,64 ), g_vZero, g_vZero  );
//		m_pReply_No		= new Reply(  pD3DDevice, m_pAnswerTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
//										D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),Rect( 256,0,512,64 ), g_vZero, g_vZero  );
//
//	}
//	catch(...){
//		SafeRelease(m_pSprite);
//		//再スロー
//		throw;
//	}
//};
//
///**********************************************
//デストラクタ
//**********************************************/
//Continue::~Continue(){
//	SafeDelete( m_pReply_Yes );
//	SafeDelete( m_pReply_No );
//	SafeDelete( m_pRethinking );
//	SafeDelete( m_pContinueChar );
//
//	m_pTime	= NULL ;
//	m_pCoil	= NULL ;
//
//}
//
///////////////////// ////////////////////
////// 関数名     ：void Continue::Draw( DrawPacket& i_DrawPacket)
////// カテゴリ   ：関数
////// 用途       ：スプライトを描画
////// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Continue::Draw(DrawPacket& i_DrawPacket)
//{
//	if( m_bDrawing ){
//		if( m_bWhichDraw ){
//			if( m_pContinueChar != NULL )
//				m_pContinueChar->Draw(i_DrawPacket);
//			//	: 描画は親クラスに任せる
//			SpriteObject::Draw(i_DrawPacket);
//		}else{
//			if( m_pRethinking != NULL )
//				m_pRethinking->Draw(i_DrawPacket);
//			if( m_pReply_Yes != NULL )
//				m_pReply_Yes->Draw(i_DrawPacket);
//			if( m_pReply_No != NULL )
//				m_pReply_No->Draw(i_DrawPacket);
//		}
//	}
//};
//
///////////////////// ////////////////////
////// 関数名     ：void Continue::Update( UpdatePacket& i_UpdatePacket)
////// カテゴリ   ：関数
////// 用途       ：データの更新
////// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Continue::Update(UpdatePacket& i_UpdatePacket)
//{
//	if( !m_pCoil )	m_pCoil	=	( PlayerCoil* ) i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL );
//
//	if( m_pCoil && m_pCoil->getState() != COIL_STATE_DEAD ){
//		m_bDrawing	= false;
//	}
//
//	if( m_bDrawing ){
//		if( m_bWhichDraw ){
//			if( !m_pTime )	m_pTime	= ( TimeScore* ) i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME );
//			if( Cursor2D::isHitSprite( this ) ){
//				if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
//					if( m_bPushRock ){
//						if( m_bMark ){
//							if( m_pTime )		m_pTime->setTime();
//							m_pCoil->setReadyContinue(true);
//						}
//						else{
//							if( m_pReply_No != NULL){
//								m_pReply_No->setWhichDraw( false );
//							}
//							m_bWhichDraw	= false;
//						}
//						//	: マウスの左ボタンが押された
//						
//						if( !m_bPush ){
//							i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
//						}
//						m_bPush		= true;
//						m_bPushRock	= false;
//					}
//				}
//				else	m_bPushRock	= true;
//				m_Color	= 0xFFFFFFFF;
//				if( !m_bSelect ){
//					m_bSelect = true;
//					i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
//				}
//			}
//			else{
//				//	: マウスが画像の範囲外にいるとき
//				m_Color	= 0xA0FFFFFF;
//				m_bSelect = false;
//				if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
//				else				m_bPushRock	= true;
//			}
//		}
//		else{
//			if( m_pRethinking != NULL )
//				m_pRethinking->Update( i_UpdatePacket );
//			if( m_pReply_Yes != NULL )
//				m_pReply_Yes->Update( i_UpdatePacket );
//			if( m_pReply_No != NULL ){
//				m_pReply_No->Update( i_UpdatePacket );
//				m_bWhichDraw	= m_pReply_No->getWhichDraw();
//			}
//		}
//		if( m_bPush ){
//			m_iTime++;
//			if( m_iTime > 30 ){
//				//選ばれた画面へとぶ
//				i_UpdatePacket.pCommand->m_Command	= m_dNext;
//				m_bPush = false ;
//			}
//		}
//	}
//};
//
///************************************************************************
//Dead 定義部
//************************************************************************/
///////////////////// ////////////////////
////// 関数名     ：Dead(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
//////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
//////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
////// カテゴリ   ：コンストラクタ
////// 用途       ：死亡時に表示する文字
////// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
//////            ：  LPTATRATEXTURE pTexture     // 貼り付けたいテクスチャ
//////            ：  DWORD next                      // 次の画面
//////            ：  D3DXVECTOR3 &vScale             // 大きさ
//////            ：  D3DXVECTOR3 &vRot               // 三軸回転
//////            ：  D3DXVECTOR3 &vPos               // 設置座標
//////            ：  Rect* pRect                     // 描画したい範囲(NULLで全体を描画)
//////            ：  D3DXVECTOR3& vCenter            // 中心
//////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
//////            ：  Color color = 0xFFFFFFFF        // 色
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//Dead::Dead(	const LPDIRECT3DDEVICE9 pD3DDevice,const  LPTATRATEXTURE pTexture,
//			const LPTATRATEXTURE pDeadCountTex, const  LPTATRATEXTURE pCountCharTex,const int iDeadCount,
//			const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vPos,
//			const Rect *pRect,const  Color color,const wiz::OBJID id)
//:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, pRect, g_vZero, g_vZero, color, id )
//,m_fTime(0)
//,m_pDeadScore( NULL )
//,m_pDeadCountChar( NULL )
//,m_bDrawing( false )
//,m_iDeadCount( 0 )
//,m_pSelect_Yes( NULL )
//,m_pSelect_No( NULL )
//{
//	try{
//		//	: 初期マトリックスを計算
//		D3DXMATRIX mScale,mPos;
//		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
//		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
//		m_mMatrix = mScale * mPos ;
//
//		float	wide	= BASE_CLIENT_WIDTH/2;
//		float	height	= BASE_CLIENT_HEIGHT/2;
//		int		iCount	= iDeadCount+1;
//
//		D3DXVECTOR3	vScoreScale		= D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
//		D3DXVECTOR3	vScorePos		= D3DXVECTOR3( wide+40.0f*vScoreScale.x-100.0f, height-32.0f*vScoreScale.y+65.0f, 0.0f );
//		D3DXVECTOR3	vCountCharScale	= D3DXVECTOR3( 0.6f, 2.0f, 0.0f );
//		D3DXVECTOR3	vCountCharPos	= D3DXVECTOR3( wide-256-40, height, 0.0f );
//
//		m_pDeadScore			= new Score( pD3DDevice, pDeadCountTex, vScoreScale, vScorePos, iDeadCount, &Rect( 0, 0, 512, 64 ) );
//		m_pDeadCountChar		= new SpriteObject( pD3DDevice, pCountCharTex, vCountCharScale, g_vZero, vCountCharPos, &Rect( 0, 192, 512, 256 ), g_vZero,g_vZero );
//
//	}
//	catch(...){
//		SafeRelease(m_pSprite);
//		//再スロー
//		throw;
//	}
//};
//
///************************************
//デストラクタ
//************************************/
//Dead::~Dead(){
//	SafeDelete(m_pDeadScore);
//	SafeDelete(m_pDeadCountChar);
//	m_pSelect_Yes	= NULL;
//	m_pSelect_No	= NULL;
//
//}
///////////////////// ////////////////////
////// 関数名     ：void Dead::Draw( DrawPacket& i_DrawPacket)
////// カテゴリ   ：関数
////// 用途       ：スプライトを描画
////// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Dead::Draw(DrawPacket& i_DrawPacket)
//{
//	if( m_bDrawing ){
//		//	: 描画は親クラスに任せる
//		SpriteObject::Draw( i_DrawPacket );
//
//		if( m_pDeadScore )		m_pDeadScore->Draw( i_DrawPacket );
//		if( m_pDeadCountChar )	m_pDeadCountChar->Draw( i_DrawPacket );
//	}
//};
//
///////////////////// ////////////////////
////// 関数名     ：void Dead::Update( UpdatePacket& i_UpdatePacket)
////// カテゴリ   ：関数
////// 用途       ：データの更新
////// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
////// 戻値       ：なし
////// 担当者     ：佐藤涼
////// 備考       ：
//////            ：
//////
//void Dead::Update(UpdatePacket& i_UpdatePacket)
//{
//	if( !m_pSelect_Yes )	m_pSelect_Yes	=	( Continue* ) i_UpdatePacket.SearchObjectFromID( OBJID_UI_ANS_YES );
//	if( !m_pSelect_No )		m_pSelect_No	=	( Continue* ) i_UpdatePacket.SearchObjectFromID( OBJID_UI_ANS_NO );
//
//	if( m_bDrawing ){
//		m_fTime	+= (float)i_UpdatePacket.GetTime()->getElapsedTime();
//		if( m_fTime >= 1.5f ){
//			m_Color.byteColor.a	-= 5;
//			if( m_Color.byteColor.a <= 5){
//				m_Color.byteColor.a	= 0;
//				m_fTime				= 0;
//				m_bDrawing			= false;
//				if( m_pSelect_Yes )	m_pSelect_Yes->setDrawing( true );
//				if( m_pSelect_No )	m_pSelect_No->setDrawing( true );
//			}
//
//		}
//
//		if( m_pDeadScore ){
//			m_pDeadScore->setScore( m_iDeadCount );
//			m_pDeadScore->setAlpha( m_Color.byteColor.a );
//			m_pDeadScore->Update( i_UpdatePacket );
//		}
//		if( m_pDeadCountChar ){
//			m_pDeadCountChar->setAlpha( m_Color.byteColor.a );
//		}
//	}
//	else	m_Color.byteColor.a	= 255;
//};

/**************************************************************************
 Factory_Continue 定義部
****************************************************************************/
/**************************************************************************
 Factory_Continue::Factory_Continue(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Continue::Factory_Continue(FactoryPacket* fpac)
{
	try{
		fpac->AddObject( new ContinueBehavior(*fpac) );
		//float	wide	= BASE_CLIENT_WIDTH/2;
		//float	height	= BASE_CLIENT_HEIGHT/2;

		//D3DXVECTOR3	vScale	= D3DXVECTOR3( 0.5f, 0.5f, 0.0f );
		//D3DXVECTOR3	vPos	= D3DXVECTOR3( (wide-512.0f*vScale.x), (height-256.0f*vScale.y-100), 0.0f );
		//LPTATRATEXTURE pTex;
		//LPTATRATEXTURE pTex2;
		//LPTATRATEXTURE pTex3;
		//0(fpac->GetDevice(),L"dead6.png",&pTex);
		//0(fpac->GetDevice(),L"Number_Base1.png",&pTex2);
		//0(fpac->GetDevice(),L"TEST.png",&pTex3);
		//fpac->AddObject(
		//	new Dead( fpac->GetDevice(),
		//				pTex/*fpac->AddTexture( L"dead6.png" )*/,
		//				pTex2/*fpac->AddTexture( L"Number_Base1.png" )*/,
		//				pTex3/*fpac->AddTexture( L"TEST.png" )*/,
		//				0,
		//				vScale,
		//				vPos,
		//				NULL
		//	)
		//);
		//0(fpac->GetDevice(),L"TEST.png",&pTex);
		////***************************************************
		////YES
		//fpac->AddObject(
		//	new Continue(
		//			fpac->GetDevice(),
		//			pTex/*fpac->AddTexture( L"TEST.png" )*/,
		//			NULL,
		//			NULL,
		//			true,
		//			D3DXVECTOR3(1.0f,1.0f,0.0f),
		//			D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),
		//			Rect( 0,0,256,64 ),
		//			OBJID_UI_ANS_YES
		//	)
		//);
		////**********************************::
		////NO
		//0(fpac->GetDevice(),L"TEST.png",&pTex);
		//0(fpac->GetDevice(),L"REALLY4.png",&pTex2);
		//0(fpac->GetDevice(),L"CONTINUE4.png",&pTex3);
		//fpac->AddObject(
		//	new Continue(
		//			fpac->GetDevice(),
		//			pTex/*fpac->AddTexture( L"TEST.png" )*/,
		//			pTex2/*fpac->AddTexture( L"REALLY4.png" )*/,
		//			pTex3/*fpac->AddTexture( L"CONTINUE4.png" )*/,
		//			false,
		//			D3DXVECTOR3(1.0f,1.0f,0.0f),
		//			D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),
		//			Rect( 256,0,512,64 ),
		//			OBJID_UI_ANS_NO
		//	)
		//);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Continue::~Factory_Continue();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Continue::~Factory_Continue(){
    //なにもしない
}

}
}