/**************************************************************************
 CommonMesh.h

****************************************************************************/

#include "StdAfx.h"
#include "CommonMesh.h"
namespace wiz{

/**************************************************************************
 CommonMesh 定義部
***************************************************************************/
/**************************************************************************
 CommonMesh(
    D3DXVECTOR3 pos,                //位置
    D3DCOLORVALUE& Diffuse,         //ディフューズ色
    D3DCOLORVALUE& Specular,            //スペキュラ色
    D3DCOLORVALUE& Ambient          //アンビエント色
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
CommonMesh::CommonMesh(D3DXVECTOR3 pos,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
:Object(),
m_pMesh(0),     //ポインタは０初期化
m_pShadowMesh(0),
m_Pos(pos)
{
    try{
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
        // モデルの色を設定
        m_Material.Diffuse = Diffuse;
        m_Material.Specular = Specular;
        m_Material.Ambient = Ambient;
    }
    catch(...){
        //コンストラクタ例外発生
        //再スロー
        throw;
    }
}
/**************************************************************************
 CommonMesh::~CommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
CommonMesh::~CommonMesh(){
    //後始末
	//派生クラスでのDelete/Release忘れ対策
    SafeRelease(m_pMesh);
    SafeRelease(m_pShadowMesh);
}
/**************************************************************************
 void CommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: コモンメッシュを描画
 戻り値: なし。
***************************************************************************/
void CommonMesh::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    //無効チェック
    if((!m_pMesh) || (!pD3DDevice)){
        throw DxException(L"デバイスかメッシュが無効です。",
        L"CommonMesh::Draw()");
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成の設定
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    }
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラー有効の設定
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
    }
    // マテリアルをレンダリングパイプラインに設定
    pD3DDevice->SetMaterial( &m_Material);
    //描画
    m_pMesh->DrawSubset(0);
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //もし、スペキュラーが設定していたら
        // スペキュラーを元に戻す
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
    }
    if(m_Material.Diffuse.a < 1.0f){
        //もし、透明度が1.0未満なら
        // アルファ合成を元に戻す
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    }
}
}