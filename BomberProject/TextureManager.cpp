////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：TextureManager.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：テクスチャーの管理
//					▼
//	namespace wiz;
//		class TextureManager;
//		class TextureManager::Texture;
//
#include "StdAfx.h"
#include "TextureManager.h"
#include "TL-String.h"
namespace wiz {
/**************************************************************************
 TextureManager 定義部
/***************************************************************************/

/////////////////// ////////////////////
//// 用途       ：TextureManager::TextureManager()
//// カテゴリ   ：コンストラクタ
//// 用途       ：インスタンス生成時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
TextureManager::TextureManager(){

};
/////////////////// ////////////////////
//// 用途       ：TextureManager::~TextureManager()
//// カテゴリ   ：デストラクタ
//// 用途       ：インスタンス破棄時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
TextureManager::~TextureManager(){
	Release();
};
/////////////////// ////////////////////
//// 用途       ：TextureManager::Release()
//// カテゴリ   ：関数
//// 用途       ：全テクスチャーの破棄
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
void TextureManager::Release(){
	//vector< Texture* >::iterator	it  = m_vecTextures.begin()	;
	//while(it != m_vecTextures.end()){
	//	SafeDelete( *it );
	//	
	//	//*it = NULL ;
	//	it = m_vecTextures.erase(it);
	//}
	SafeDeletePointerContainer( m_vecTextures );
	m_vecTextures.clear();
};
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureManager::addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
////            ：  	const wchar_t *filepath, const wchar_t *texturename )
//// カテゴリ   ：関数
//// 用途       ：テクスチャーの読み込み
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice	// デバイス
////            ：  const wchar_t *filepath			// ファイルパス
////            ：  const wchar_t *texturename		// テクスチャ名 ( オプション )
//// 戻値       ：生成されたテクスチャのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 備考       ：
////            ：
////
LPDIRECT3DTEXTURE9 TextureManager::addTexture(
		LPDIRECT3DDEVICE9	pD3DDevice	,
		const wchar_t*		filepath	,
		const wchar_t*		texturename 
){
	try{
		LPDIRECT3DTEXTURE9 tex ;
		if( (tex = TextureSearchFromFilePath(filepath)) != NULL)
			return tex;
		else
		if( texturename && TextureSearchFromName(texturename) ){
			// 初期化失敗
			::MessageBox(NULL,L"テクスチャ名が競合しました\nTextureManager::addTexture()",L"エラー",MB_OK);
			
		}
		else
		{
			Texture* tx = new Texture(pD3DDevice , filepath , texturename);
			m_vecTextures.push_back( tx );
			return tx->getTexture();
		}

		return NULL;
	}
	catch(wiz::BaseException& e){
		Release();
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑TextureManager::addTexture()"
				);
	}
	catch(...){
		//コンストラクタ例外発生
		//後始末
		Release();
		//再スロー
		throw;
	}
};
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureManager::addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
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
//// 戻値       ：無し
//// 備考       ：
////            ：
////
LPDIRECT3DTEXTURE9 TextureManager::addTextureEx(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	const wchar_t*		filepath	,
    UINT				Width		,
	UINT				Height		,
	UINT				MipLevels	,
	DWORD				Usage		,
	D3DFORMAT			Format		,
	D3DPOOL				Pool		,
	DWORD				Filter		,
    DWORD				MipFilter	,
	D3DCOLOR			ColorKey	,
	D3DXIMAGE_INFO*		pSrcInfo	,
	PALETTEENTRY*		pPalette	,
	const wchar_t*		texturename
){
	try{
		LPDIRECT3DTEXTURE9 tex ;
		if( (tex = TextureSearchFromFilePath(filepath)) != NULL)
			return tex;
		else
		if( texturename && TextureSearchFromName(texturename) ){

			// 初期化失敗
			::MessageBox(NULL,L"テクスチャ名が競合しました\nTextureManager::addTextureEx()",L"エラー",MB_OK);
		}
		else
		{
			Texture* tx = new Texture(
					pD3DDevice ,
					filepath ,
					Width,				// 画像の幅(0でオリジナル)
					Height,				// 画像の高さ(0でオリジナル)
					MipLevels,			// ミップレベル(通常0)
					Usage,				// レンダリングターゲットに指定するときとかに指定(通常0)
					Format,				// 色のフォーマット
					Pool,				// データの読み込み先(いじらなくておk)
					Filter,				// フィルター(いじらなくておk)
					MipFilter,			// ミップフィルター(いじらなくておk)
					ColorKey,			// 【αあり】青色を透過色とする【0で無効】
					pSrcInfo,			// 【D3DXIMAGE_INFO構造体】画像データの構造【ピクセルサイズとか】
					pPalette,			// パレット
					texturename);
			m_vecTextures.push_back( tx );
			return tx->getTexture();
		}

		return NULL;
	}
	catch(wiz::BaseException& e){
		Release();
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑TextureManager::addTextureEx()"
				);
	}
	catch(...){
		//コンストラクタ例外発生
		//後始末
		Release();
		//再スロー
		throw;
	}
};
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureManager::addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：  	DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename )
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
//// 戻値       ：無し
//// 備考       ：
////            ：
////
LPDIRECT3DTEXTURE9 TextureManager::addTextureExLight(
	LPDIRECT3DDEVICE9	pD3DDevice		,
	const wchar_t*		filepath		,
    DWORD				Usage			,
	D3DFORMAT			Format			,
	D3DCOLOR			ColorKey		,
	const wchar_t*		texturename
){
	try{
		LPDIRECT3DTEXTURE9 tex ;
		if( (tex = TextureSearchFromFilePath(filepath)) != NULL)
			return tex;
		else
		if( texturename && TextureSearchFromName(texturename) ){
			// 初期化失敗
			::MessageBox(NULL,L"テクスチャ名が競合しました\nTextureManager::addTextureExLight()",L"エラー",MB_OK);
		}
		else
		{
			Texture* tx = new Texture(
					pD3DDevice ,
					filepath ,
					0,					// 画像の幅(0でオリジナル)
					0,					// 画像の高さ(0でオリジナル)
					0,					// ミップレベル(通常0)
					Usage,				// レンダリングターゲットに指定するときとかに指定(通常0)
					Format,				// 色のフォーマット
					D3DPOOL_MANAGED,	// データの読み込み先(いじらなくておk)
					D3DX_FILTER_LINEAR,	// フィルター(いじらなくておk)
					D3DX_FILTER_LINEAR,	// ミップフィルター(いじらなくておk)
					ColorKey,			// 【αあり】青色を透過色とする【0で無効】
					NULL,				// 【D3DXIMAGE_INFO構造体】画像データの構造【ピクセルサイズとか】
					NULL,				// パレット
					texturename);
			m_vecTextures.push_back( tx );
			return tx->getTexture();
		}
		return NULL;
	}
	catch(wiz::BaseException& e){
		Release();
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑TextureManager::addTextureExLight()"
				);
	}
	catch(...){
		//コンストラクタ例外発生
		//後始末
		Release();
		//再スロー
		throw;
	}
};
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromName(const wchar_t* filename)
//// カテゴリ   ：関数
//// 用途       ：テクスチャ名から読み込み済みのテクスチャーを検索
//// 引数       ：  const wchar_t* filename		// 検索するファイル名
//// 戻値       ：発見したテクスチャのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 備考       ：
////            ：
////
LPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromName(const wchar_t* filename) {
	vector< Texture* >::iterator it;
	for(it = m_vecTextures.begin();it != m_vecTextures.end();it++){
		if((*it)->checkTextureName(filename))
			return (*it)->getTexture();
	}
	return NULL;
}
/////////////////// ////////////////////
//// 用途       ：LPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromFilePath(const wchar_t* path)
//// カテゴリ   ：関数
//// 用途       ：ファイルパスから読み込み済みのテクスチャーを検索
//// 引数       ：  const wchar_t* path		// 検索するファイル名
//// 戻値       ：発見したテクスチャのポインタを返す ( LPDIRECT3DTEXTURE9型 )
//// 備考       ：
////            ：
////
LPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromFilePath(const wchar_t* path){
	vector< Texture* >::iterator it;
	for(it = m_vecTextures.begin();it != m_vecTextures.end();it++){
		if((*it)->checkFilePath(path))
			return (*it)->getTexture();
	}
	return NULL;
}

/**************************************************************************
 TextureManager::Texture 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：    const wchar_t* texturename = L"")
//// カテゴリ   ：コンストラクタ
//// 用途       ：NormalLoad
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		// 検索するファイル名
////            ：  const wchar_t* filepath             // 
////            ：  const wchar_t* texturename = L""    // 
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,const wchar_t* texturename )
:m_pTexture( 0 )
,m_strFilePath( filepath )
,m_strTexName( texturename )
{
	try{
		wstring sFileName ;
		//テクスチャの作成
		if( PathFileExists( filepath ) ){
			sFileName = filepath ;
		}else if( PathFileExists( wstring( g_sDefaultTexturePath + filepath ).c_str() ) ){
			sFileName = g_sDefaultTexturePath + filepath ;
		}else{
			wstring msgtxt = L"テクスチャファイルが見つかりませんでした。\nTextureManager::Texture::Texture()\n";
			msgtxt += sFileName  ;
			msgtxt += L"  or  "  ;
			msgtxt += g_sDefaultTexturePath + filepath ;

            // 初期化失敗
			::MessageBox(NULL,msgtxt.c_str(),L"エラー",MB_OK);
		}
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,sFileName.c_str(),&m_pTexture))){
			wstring msgtxt = L"テクスチャ読み込みに失敗しました。\nTextureManager::Texture::Texture()\n";
			msgtxt += sFileName  ;
			msgtxt += L"  or  "  ;
			msgtxt += g_sDefaultTexturePath + filepath ;
			::MessageBox(NULL,msgtxt.c_str(),L"エラー",MB_OK);
		}
	}
	catch(wiz::BaseException& e){
        SafeRelease(m_pTexture);
        //再スロー
        throw BaseException(
				e.what_w(), 
                L"↑TextureManager::Texture::Texture()"
                );
	}
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pTexture);
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 用途       ：TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            ：    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format,
////            ：    D3DPOOL Pool, DWORD Filter,DWORD MipFilter, D3DCOLOR ColorKey,
////            ：    D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );
//// カテゴリ   ：コンストラクタ
//// 用途       ：ExLoad
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice	 // デバイス
////            ：  const wchar_t *filepath			 // ファイルパス
////            ：  UINT Width						 // 画像の幅(0でオリジナル)
////            ：  UINT Height						 // 画像の高さ(0でオリジナル)
////            ：  UINT MipLevels					 // ミップレベル(通常0)
////            ：  DWORD Usage						 // レンダリングターゲットに指定するときとかに指定(通常0)
////            ：  D3DFORMAT Format				 // 色のフォーマット
////            ：  D3DPOOL Pool					 // データの読み込み先(いじらなくておk)
////            ：  DWORD Filter					 // フィルター(いじらなくておk)
////            ：  DWORD MipFilter					 // ミップフィルター(いじらなくておk)
////            ：  D3DCOLOR ColorKey				 // 【αあり】青色を透過色とする【0で無効】
////            ：  D3DXIMAGE_INFO *pSrcInfo		 // 【D3DXIMAGE_INFO構造体】画像データの構造【ピクセルサイズとか】
////            ：  PALETTEENTRY *pPalette			 // パレット
////            ：  const wchar_t *texturename = L"" // テクスチャ名(オプション)
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
    DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename )
:m_pTexture(0)
,m_strFilePath(filepath)
,m_strTexName(texturename)
{
	try{
		 
		//テクスチャの作成
		if(FAILED(D3DXCreateTextureFromFileEx(
				pD3DDevice,			// デバイス
				filepath,			// ファイル名
				Width,				// 画像の幅(0でオリジナル)
				Height,				// 画像の高さ(0でオリジナル)
				MipLevels,			// ミップレベル(通常0)
				Usage,				// レンダリングターゲットに指定するときとかに指定(通常0)
				Format,				// 色のフォーマット
				Pool,				// データの読み込み先(いじらなくておk)
				Filter,				// フィルター(いじらなくておk)
				MipFilter,			// ミップフィルター(いじらなくておk)
				ColorKey,			// 【αあり】青色を透過色とする【0で無効】
				pSrcInfo,			// 【D3DXIMAGE_INFO構造体】画像データの構造【ピクセルサイズとか】
				pPalette,			// パレット
				&m_pTexture			// テクスチャ名
			))){
            // 初期化失敗
			::MessageBox(NULL,L"テクスチャ読み込みに失敗しました。\nTextureManager::Texture::Texture()",L"エラー",MB_OK);
		}
	}
	catch(wiz::BaseException& e){
        SafeRelease(m_pTexture);
        //再スロー
        throw BaseException(
				e.what_w(), 
                L"↑TextureManager::Texture::Texture()   (EX"
                );
	}
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pTexture);
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 用途       ：TextureManager::Texture::~Texture()
//// カテゴリ   ：デストラクタ
//// 用途       ：インスタンス破棄時処理
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
TextureManager::Texture::~Texture(){
	if( this && m_pTexture){
		Debugger::DBGWRITINGLOGTEXT::addStr( L"TextureManager::Texture::~Texture(0x%X)  >>>  m_strFilePath( 0x%X ) = %s\n", this,m_pTexture , m_strFilePath.c_str() );
	    //後始末
		int ret = SafeRelease(m_pTexture);
		Debugger::DBGWRITINGLOGTEXT::addStr( L"TextureManager::Texture::~Texture(0x%X)  >>>  %d \n", this,ret );
	}else{
		Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"TextureManager::Texture::~Texture で this がぬるぽっ!てます｡");
	}
}

bool TextureManager::Texture::checkTextureName( wstring name ) const{
	return  (m_strTexName != L"" ) && (m_strTexName == name);
}

bool TextureManager::Texture::checkFilePath( wstring filepath ) const{
	return ( _wcsicmp(m_strFilePath.c_str(),filepath.c_str()) == 0 );
}
}