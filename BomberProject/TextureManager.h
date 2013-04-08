////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：TextureManager.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：テクスチャーの管理
//					▼
//	namespace wiz;
//		class TextureManager;
//		class TextureManager::Texture;
//
#pragma once
namespace wiz {

//**************************************************************************
// class TextureManager;
//
// 担当者  : 鴫原 徹
// 用途    : テクスチャ管理クラス
//         : 同一データの多重生成及びリリース漏れの無いように
//         : テクスチャーを管理できます
//**************************************************************************
class TextureManager{
	class Texture;
	vector< Texture* > m_vecTextures;
public:
/////////////////// ////////////////////
//// 用途       ：TextureManager()
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	TextureManager();
/////////////////// ////////////////////
//// 用途       ：~TextureManager()
//// カテゴリ   ：デストラクタ
//// 用途       ：インスタンス破棄時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual ~TextureManager();
/////////////////// ////////////////////
//// 用途       ：Release()
//// カテゴリ   ：関数
//// 用途       ：全テクスチャーの破棄
//// 引数       ：無し
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	void Release();
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
////            ：  	const wchar_t *filepath, const wchar_t *texturename )
//// カテゴリ   ：関数
//// 用途       ：テクスチャーの読み込み
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice	// デバイス
////            ：  const wchar_t *filepath			// ファイルパス
////            ：  const wchar_t *texturename		// テクスチャ名 ( オプション )
//// 戻値       ：生成されたテクスチャまたは同一データのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	LPDIRECT3DTEXTURE9 addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
		const wchar_t* filepath,const wchar_t* texturename = L"");
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：  	UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
////            ：  	DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename )
//// カテゴリ   ：関数
//// 用途       ：テクスチャーの読み込み
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice	// デバイス
////            ：  const wchar_t *filepath			// ファイルパス
////            ：  UINT Width						// 画像の幅(0でオリジナル)
////            ：  UINT Height						// 画像の高さ(0でオリジナル)
////            ：  UINT MipLevels					// ミップレベル(通常0)
////            ：  DWORD Usage						// レンダリングターゲットに指定するときとかに指定(通常0)
////            ：  D3DFORMAT Format				// 色のフォーマット
////            ：  D3DPOOL Pool					// データの読み込み先(いじらなくておk)
////            ：  DWORD Filter					// フィルター(いじらなくておk)
////            ：  DWORD MipFilter					// ミップフィルター(いじらなくておk)
////            ：  D3DCOLOR ColorKey				// 【αあり】青色を透過色とする【0で無効】
////            ：  D3DXIMAGE_INFO *pSrcInfo		// 【D3DXIMAGE_INFO構造体】画像データの構造【ピクセルサイズとか】
////            ：  PALETTEENTRY *pPalette			// パレット
////            ：  const wchar_t *texturename		// テクスチャ名(オプション)
//// 戻値       ：生成されたテクスチャまたは同一データのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	LPDIRECT3DTEXTURE9 addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
		UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
		DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：  	DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename )
//// カテゴリ   ：関数
//// 用途       ：テクスチャーの読み込み
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice	// デバイス
////            ：  const wchar_t *filepath			// ファイルパス
////            ：  DWORD Usage						// レンダリングターゲットに指定するときとかに指定(通常0)
////            ：  D3DFORMAT Format				// 色のフォーマット
////            ：  D3DCOLOR ColorKey				// 【αあり】青色を透過色とする【0で無効】
////            ：  const wchar_t *texturename		// テクスチャ名(オプション)
//// 戻値       ：生成されたテクスチャまたは同一データのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	LPDIRECT3DTEXTURE9 addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
		DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename = L"" );
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureSearchFromName(const wchar_t* filename)
//// カテゴリ   ：関数
//// 用途       ：テクスチャ名から読み込み済みのテクスチャーを検索
//// 引数       ：  const wchar_t* filename		// 検索するファイル名
//// 戻値       ：発見したテクスチャのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	LPDIRECT3DTEXTURE9 TextureSearchFromName(const wchar_t* filename) ;
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureSearchFromFilePath(const wchar_t* path)
//// カテゴリ   ：関数
//// 用途       ：ファイルパスから読み込み済みのテクスチャーを検索
//// 引数       ：  const wchar_t* path		// 検索するファイル名
//// 戻値       ：発見したテクスチャのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	LPDIRECT3DTEXTURE9 TextureSearchFromFilePath(const wchar_t* path) ;


};//【END】TextureManager

//**************************************************************************
// class TextureManager::Texture;
//
// 担当者  : 鴫原 徹
// 用途    : 
//**************************************************************************
class TextureManager::Texture{
	
	LPDIRECT3DTEXTURE9	m_pTexture     ;
	wstring				m_strTexName   ;
	wstring				m_strFilePath  ;

public:
/////////////////// ////////////////////
//// 用途       ：Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：    const wchar_t* texturename = L"")
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		// 検索するファイル名
////            ：  const wchar_t* filepath             // 
////            ：  const wchar_t* texturename = L""    // 
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,const wchar_t* texturename = L"");
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 i_pD3DDev,	//DirectXデバイス
	const wchar_t* filename	//テクスチャのファイル名
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
    DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );

/**************************************************************************
 ~Texture();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Texture();
/**************************************************************************
 const LPDIRECT3DTEXTURE9 getTexture() const
 用途: アクセッサ
 戻り値: なし
***************************************************************************/
	const LPDIRECT3DTEXTURE9 getTexture() const{
		return m_pTexture;
	}
	bool	checkTextureName( wstring name ) const;
	bool	checkFilePath(    wstring path ) const;
};//【END】Texture

}