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

/************************************************************************
Reply 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Reply(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：タイトルへ戻るの再確認
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
Reply::Reply(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,const bool mark,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos(		vPos	)
,m_bMark(		mark	)
,m_bPushRock(	false	)
,m_bWhichDraw(	false	)
,m_iTime(		0		)
,m_bPush(		false	)
,m_bSelect(		false	)
,m_pCoil(		NULL	)
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
};

Reply::~Reply(){
	m_pCoil		= NULL;
}
/////////////////// ////////////////////
//// 関数名     ：void Reply::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Reply::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void Reply::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Reply::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);
	if( Cursor2D::isHitSprite( this ) ){
		if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
			if( m_bPushRock ){
				if( m_bMark ){
					i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_RESULT;
					i_UpdatePacket.pCommand->m_Param1	= m_pCoil->getDeadCount();
					i_UpdatePacket.pCommand->m_Param2	= m_pCoil->getMaxPos();
				}
				else{
					m_bWhichDraw	= true;
				}
				if( !m_bPush ){
					i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
				}
				m_bPush		= true;
				m_bPushRock	= false;
			}
		}
		else	m_bPushRock	= true;
		m_Color	= 0xFFFFFFFF;
		if( !m_bSelect ){
			m_bSelect = true;
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
		}
	}
	else{
		//	: マウスが画像の範囲外にいるとき
		m_Color	= 0xA0FFFFFF;
		m_bSelect = false;
		if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
		else				m_bPushRock	= true;
	}
		if( m_bPush ){
		m_iTime++;
		if( m_iTime > 30 ){
			//選ばれた画面へとぶ
			i_UpdatePacket.pCommand->m_Command	= m_dNext;
			m_bPush = false ;
		}
	}

};

/************************************************************************
Dead 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Dead(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：死亡時に表示する文字
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
Dead::Dead(	const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,
			const LPDIRECT3DTEXTURE9 pDeadCountTex, const  LPDIRECT3DTEXTURE9 pCountCharTex,const int iDeadCount,
			const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
			const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_iTime(0)
,m_pDeadScore( NULL )
,m_pDeadCountChar( NULL )
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;
		int		iCount	= iDeadCount+1;

		D3DXVECTOR3	vScoreScale		= D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
		D3DXVECTOR3	vScorePos		= D3DXVECTOR3( wide+40.0f*vScoreScale.x, height-32.0f*vScoreScale.y+65.0f, 0.0f );
		D3DXVECTOR3	vCountCharScale	= D3DXVECTOR3( 0.6f, 2.0f, 0.0f );
		D3DXVECTOR3	vCountCharPos	= D3DXVECTOR3( wide-256-40, height, 0.0f );

		m_pDeadScore			= new Score( pD3DDevice, pDeadCountTex, vScoreScale, vScorePos, iCount, &Rect( 0, 0, 512, 64 ) );
		m_pDeadCountChar		= new SpriteObject( pD3DDevice, pCountCharTex, vCountCharScale, g_vZero, vCountCharPos, NULL, g_vZero,g_vZero );

	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
};

/************************************
デストラクタ
************************************/
Dead::~Dead(){
	SAFE_DELETE(m_pDeadScore);
	SAFE_DELETE(m_pDeadCountChar);
}
/////////////////// ////////////////////
//// 関数名     ：void Dead::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Dead::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw( i_DrawPacket );

	if( m_pDeadScore )		m_pDeadScore->Draw( i_DrawPacket );
	if( m_pDeadCountChar )	m_pDeadCountChar->Draw( i_DrawPacket );
};

/////////////////// ////////////////////
//// 関数名     ：void Dead::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Dead::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_iTime > 60 ){
		m_Color.byteColor.a	-= 5;
		if( m_Color.byteColor.a <= 5)
			m_Color.byteColor.a	= 0;

	}
	m_iTime++;

	if( m_pDeadScore ){
		m_pDeadScore->setAlpha( m_Color.byteColor.a );
		m_pDeadScore->Update( i_UpdatePacket );
	}
	if( m_pDeadCountChar ){
		m_pDeadCountChar->setAlpha( m_Color.byteColor.a );
	}
};

/************************************************************************
Continue 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Continue(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：コンテニューするか確認
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
Continue::Continue(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture_Answer,
		const LPDIRECT3DTEXTURE9 pTexture_Rethinking, const LPDIRECT3DTEXTURE9 pTexture_Continue,
		const bool mark,const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture_Answer, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_bMark( mark )
,m_pCoil( NULL )
,m_pReply_Yes( NULL )
,m_pReply_No( NULL )
,m_pRethinking( NULL )
,m_pContinueChar( NULL )
,m_bPushRock( false )
,m_bWhichDraw( true )
,m_pRethinkingTex(pTexture_Rethinking)
,m_pAnswerTex(pTexture_Answer)
,m_pContinueTex( pTexture_Continue )
,m_iTime( 0 )
,m_bPush( false )
,m_bSelect( false )
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		//Continueロゴの作成
		m_pContinueChar	= new SpriteObject( pD3DDevice, m_pContinueTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
									D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ), Rect( 0, 0, 512, 64 ), g_vZero, g_vZero );

		m_pRethinking	= new SpriteObject( pD3DDevice, m_pRethinkingTex, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-256.0f,height-200.0f,0.0f ),Rect( 0,0,512,64 ), g_vZero, g_vZero  );
		m_pReply_Yes	= new Reply(  pD3DDevice, m_pAnswerTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),Rect( 0,0,256,64 ), g_vZero, g_vZero  );
		m_pReply_No		= new Reply(  pD3DDevice, m_pAnswerTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f), g_vZero,
										D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),Rect( 256,0,512,64 ), g_vZero, g_vZero  );

	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
};

/**********************************************
デストラクタ
**********************************************/
Continue::~Continue(){
	SAFE_DELETE( m_pReply_Yes );
	SAFE_DELETE( m_pReply_No );
	SAFE_DELETE( m_pRethinking );
	SAFE_DELETE( m_pContinueChar );
}

/////////////////// ////////////////////
//// 関数名     ：void Continue::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Continue::Draw(DrawPacket& i_DrawPacket)
{
	if( m_bWhichDraw ){
		if( m_pContinueChar != NULL )
			m_pContinueChar->Draw(i_DrawPacket);
		//	: 描画は親クラスに任せる
		SpriteObject::Draw(i_DrawPacket);
	}else{
		if( m_pRethinking != NULL )
			m_pRethinking->Draw(i_DrawPacket);
		if( m_pReply_Yes != NULL )
			m_pReply_Yes->Draw(i_DrawPacket);
		if( m_pReply_No != NULL )
			m_pReply_No->Draw(i_DrawPacket);
	}
};

/////////////////// ////////////////////
//// 関数名     ：void Continue::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Continue::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_bWhichDraw ){
		if( !m_pCoil ) m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);
		if( Cursor2D::isHitSprite( this ) ){
			if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
				if( m_bPushRock ){
					if( m_bMark )
						m_pCoil->setReadyContinue(true);
					else{
						if( m_pReply_No != NULL){
							m_pReply_No->setWhichDraw( false );
						}
						m_bWhichDraw	= false;
					}
					//	: マウスの左ボタンが押された
					
					if( !m_bPush ){
						i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_ENTER );
					}
					m_bPush		= true;
					m_bPushRock	= false;
				}
			}
			else	m_bPushRock	= true;
			m_Color	= 0xFFFFFFFF;
			if( !m_bSelect ){
				m_bSelect = true;
				i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SELECT );
			}
		}
		else{
			//	: マウスが画像の範囲外にいるとき
			m_Color	= 0xA0FFFFFF;
			m_bSelect = false;
			if( Cursor2D::getLButtonState() )	m_bPushRock	= false;
			else				m_bPushRock	= true;
		}
	}
	else{
		if( m_pRethinking != NULL )
			m_pRethinking->Update( i_UpdatePacket );
		if( m_pReply_Yes != NULL )
			m_pReply_Yes->Update( i_UpdatePacket );
		if( m_pReply_No != NULL ){
			m_pReply_No->Update( i_UpdatePacket );
			m_bWhichDraw	= m_pReply_No->getWhichDraw();
		}
	}
	if( m_bPush ){
		m_iTime++;
		if( m_iTime > 30 ){
			//選ばれた画面へとぶ
			i_UpdatePacket.pCommand->m_Command	= m_dNext;
			m_bPush = false ;
		}
	}
};

}
}