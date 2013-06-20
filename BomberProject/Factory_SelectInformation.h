////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_SelectInformation.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：セレクト画面の説明ウインドウ
//					▼
//	namespace wiz;
//
#pragma once

//////////
//	: インクルード
//	: インクルード
//////////

namespace wiz{
namespace bomberobject{

class SelectInformation : public SpriteObject{
	LPDIRECT3DTEXTURE9	m_pTex			;
	LPDIRECT3DTEXTURE9	m_pNomalTex		;
	LPDIRECT3DTEXTURE9	m_pHardTex		;
	LPDIRECT3DTEXTURE9	m_pExtraTex		;
	int					m_iPtn			;
public:
	SelectInformation(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pNomalTex	,
		const LPDIRECT3DTEXTURE9	pHardTexture	,
		const LPDIRECT3DTEXTURE9	pExtraTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		,
		const wiz::OBJID			id			= OBJID_UI_SELECTINFORMATION
	);

	~SelectInformation();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPtn( int i ){
		m_iPtn	= i;
	}
	int		getPtn(){
		return	m_iPtn;
	}
};


//**************************************************************************//
// class Factory_SelectInformation ;
//
// 担当  : 鴫原 徹
// 用途  : チェックポイントでセーブを行う機能を作成します
//**************************************************************************//
class Factory_SelectInformation{
public:
	/////////////////// ////////////////////
	//// 関数名     ：Factory_SelectInformation(FactoryPacket* fpac)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：チェックポイントでセーブする機能を作成します
	//// 引数       ：  FactoryPacket* fpac
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	Factory_SelectInformation(FactoryPacket* fpac);
	~Factory_SelectInformation(){};
};

}
using namespace bomberobject ;
}