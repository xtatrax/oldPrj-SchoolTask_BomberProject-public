////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：磁石属性
//					▼
//	namespace wiz;
//		class Factory_Magnetic ;
//
#include "StdAfx.h"
#include "Factory_Magnetic.h"

namespace wiz{
namespace bomberobject{


/**************************************************************************
 MagneticObject 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：MagneticObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：曳地 大洋
//// 備考       ：
////            ：
////
MagneticObject::MagneticObject()
:m_bMagnetPole( POLE_S )
,m_fMagneticum((float)MGPRM_MAGNETICUM)
{
	::ZeroMemory( &m_PoleMaterial, sizeof(D3DMATERIAL9) ) ;
}
/////////////////// ////////////////////
//// 用途       ：  ~MagneticObject()
//// カテゴリ   ：コンストラクタ
//// 用途       ：Player用のコンストラクタ
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////	
MagneticObject::~MagneticObject(){
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"MagneticObject::~MagneticObject()\n");
}


/**************************************************************************
 Factory_Magnetic 定義部
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	Factory_Magnetic *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Magnetic::~Factory_Magnetic();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Magnetic::~Factory_Magnetic(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
