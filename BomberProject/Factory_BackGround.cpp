////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_BackGround.cpp
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
#include "Factory_BackGround.h"

//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberobject{

BackGround::BackGround(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 vScalse,LPDIRECT3DTEXTURE9 pTextuer)
:Box( pD3DDevice, vScalse,
	 D3DXVECTOR3(vScalse.x/2,0.0f,0.3f), g_vZero,
	 getD3DCOLORVALUE(1.0f,1.0f,1.0f,1.0f),
	 getD3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f),
	 getD3DCOLORVALUE(1.0f,1.0f,1.0f,1.0f),
	 OBJID_3D_BACKGROUND,
	 false,
	 pTextuer
	 )
,m_pCamera(NULL)
,m_uiYNum(0){
	
}
/////////////////// ////////////////////
//// 用途       ：void update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void BackGround::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera ) m_pCamera = (Camera*) SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	if( !m_pCamera ){ Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"BackGround::Update(壁紙)がCameraを見つけられませんでした><\n"); return ;}
	float fEyePos = m_pCamera->getPosY();
	this->m_BasePos;
	if( fEyePos > this->m_BasePos.y + this->m_Size.y ){
		this->m_BasePos.y += this->m_Size.y ;
	}
	Debugger::DBGSTR::addStr(L"Y = %f\n",this->m_BasePos.y);
}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
void BackGround::Draw( DrawPacket& i_DrawPacket ){
	if( !m_pCamera ){ Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"BackGround::Draw(壁紙)がCameraを見つけられませんでした><\n"); return ;}

	D3DXVECTOR3 vWorkPos = this->m_BasePos;

	Box::CalcWorldMatrix();
	Box::Draw(i_DrawPacket);

	this->SetBasePos(D3DXVECTOR3(vWorkPos.x,vWorkPos.y + this->m_Size.y ,vWorkPos.z));
	Box::CalcWorldMatrix();
	Box::Draw(i_DrawPacket);

	this->SetBasePos(vWorkPos);
}
Factory_BG::Factory_BG(FactoryPacket *fpac){

	fpac->AddObject( new BackGround(fpac->pD3DDevice,D3DXVECTOR3(50.0f,90.0f,0.0f), fpac->AddTexture(L"BackStage.png")) );
}
}
}