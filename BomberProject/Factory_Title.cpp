////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Title.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：タイトルファクトリー
//					▼
//	namespace wiz;
//		class Factory_Title ;
//
#include "StdAfx.h"
#include "BassMenuItems.h"
#include "Factory_Title.h"
#include "Factory_Scroll.h"
#include "Factory_Cursor.h"

namespace wiz{
	namespace bomberobject{

const	float	SCALE_RATE	=	1.4f;

/************************************************************************
ClickChar 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：ClickChar(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
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
		//再スロー
		throw;
	}
};

/////////////////// ////////////////////
//// 関数名     ：void ClickChar::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void ClickChar::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void ClickChar::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
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
Title_Select 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Title_Select(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
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
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Title_Select::Title_Select(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,const DWORD next,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color, bool bCanSelect)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_dNext( next )
,m_iTime( 0 )
,m_bPush( false )
,m_bPushRock( false )
,m_bCanSelect( bCanSelect )

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

/////////////////// ////////////////////
//// 関数名     ：void Title_Select::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Title_Select::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void Title_Select::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Title_Select::Update(UpdatePacket& i_UpdatePacket)
{
	//SaveData sd;
	//TLIB::BinaryLoad( RCTEXT_SAVEDATA_FILENAME,sd,RCTEXT_SAVEDATA_EXTENSION);

	if(Cursor2D::isHitSprite(this) && m_bCanSelect){
		//	: 画像の範囲内にマウスが入った

		if( Cursor2D::getLButtonState()/* || Cursor2D::getRButtonState()*/ ){
			//	: マウスの左ボタンが押された

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
		//	: マウスが画像の範囲外にいるとき
		m_Color	= 0xFF558855;
		m_bSelect = false ;
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

/**************************************************************************
 Factory_Title 定義部
****************************************************************************/
/**************************************************************************
 Factory_Title::Factory_Title(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Title::Factory_Title(FactoryPacket* fpac){
	try{
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
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Title::~Factory_Title();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Title::~Factory_Title(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
