//////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_PlayRecorder.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_PlayRecorder.h"
//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberbehavior{

PlayRecorder::PlayRecorder(wiz::OBJID id)
:Behavior(id)
,m_pLButtonBuf(NULL)
,m_pMButtonBuf(NULL)
,m_pRButtonBuf(NULL)
,m_pCamera(NULL)
{

}
PlayRecorder::~PlayRecorder(){
	const char* sDataPath  = "PlayRec/RecordData01.bkr";
	PlayDataBIN SavePacket ;
	//////////
	//	: Folderパスの分離処理
	size_t	pathLength ;
	char* pFilePath ;
	for(  pathLength = strlen(sDataPath) ; pathLength >= 0 ; pathLength--  )
		if(  sDataPath[ pathLength ] == '/' || sDataPath[ pathLength ] == '\\'  )
			break ;
	pFilePath	= new char[ pathLength + 1 ] ;
	for(  size_t i = 0 ; i < pathLength ; i++  )
		pFilePath[ i ]	= sDataPath[ i ] ;
	pFilePath[ pathLength ]	= '\0' ;
	//	: Folderパスの分離処理
	//////////

	//////////
	//	: フォルダの存在確認と生成処理
	wstring wstr ;
	TLIB::widen(string(pFilePath),wstr);
	if(!PathIsDirectory(wstr.c_str())){
		if(!CreateDirectory(wstr.c_str(),NULL)){
			::MessageBoxA(NULL,"フォルダを確保出来ませんでしたー><、\nTLIB::BinarySave()","えらー",MB_OK);
		}
	}
	//	: フォルダの存在確認と生成処理
	//////////


	//////////
	//	: ファイルの作成と書き込み処理
	FILE* fp;
	if( fopen_s(&fp,sDataPath,"wb") != 0 ){
		return;	//	: あとでTLIB用例外作って置き換える
	}
	size_t	PacketSize = sizeof(PlayDataBIN),
			retSize = fwrite((void*)&SavePacket,PacketSize,1,fp);
	if( retSize == 0 ){
		fclose(fp);
		return ;	//	: あとでTLIB用例外作って置き換える
	}
	fclose(fp);
	//	: ファイルの作成と書き込み処理
	//////////

	SafeDeletePointerContainer(m_DataVec);

}
/////////////////// ////////////////////
//// 用途       ：virtual void PlayRecorder::Update( UpdatePacket& i_UpdatePacket )
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
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void PlayRecorder::Update( UpdatePacket& i_UpdatePacket ){

	if( !m_pCamera ) m_pCamera = (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA);

	if( Cursor2D::getLButtonState() ){
		if( !m_pLButtonBuf ){
			m_pLButtonBuf = new PlayData();
			m_pLButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pLButtonBuf->enumClickType = PlayData::CT_L ;
			m_pLButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pLButtonBuf ){

			m_pLButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pLButtonBuf );
			m_pLButtonBuf = NULL ;
		}
	}

	if( Cursor2D::getMButtonState() ){
		if( !m_pMButtonBuf ){
			m_pMButtonBuf = new PlayData();
			m_pMButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pMButtonBuf->enumClickType = PlayData::CT_M ;
			m_pMButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pMButtonBuf ){
			m_pMButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pMButtonBuf );
			m_pMButtonBuf = NULL ;
		}
	}

	if( Cursor2D::getRButtonState() ){
		if( !m_pRButtonBuf ){
			m_pRButtonBuf = new PlayData();
			m_pRButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pRButtonBuf->enumClickType = PlayData::CT_R ;
			m_pRButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pRButtonBuf ){
			m_pRButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pRButtonBuf );
			m_pRButtonBuf = NULL ;
		}
	}

	Debugger::DBGSTR::addStr(L"m_DataVec.size() = %d\n",m_DataVec.size());
}

RecorderFactory::RecorderFactory(FactoryPacket* fpac){
	fpac->AddObject(new PlayRecorder(OBJID_BEHAVIOR_PLAYSAVE));
}
}
}