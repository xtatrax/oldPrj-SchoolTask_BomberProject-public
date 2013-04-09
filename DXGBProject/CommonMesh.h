/**************************************************************************
 CommonMesh.h

****************************************************************************/

#include "Object.h"


namespace wiz{

/**************************************************************************
 class CommonMesh : public Object;
 用途: コモンメッシュクラス
****************************************************************************/
class CommonMesh : public Object{
protected:
    //メッシュ
    LPD3DXMESH m_pMesh;
	//影のメッシュ
    LPD3DXMESH m_pShadowMesh;
    //マテリアル
    D3DMATERIAL9 m_Material;
    //現在のオブジェクトの位置(中心)
    D3DXVECTOR3 m_Pos;
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
  CommonMesh(D3DXVECTOR3 pos,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 virtual ~CommonMesh();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~CommonMesh();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: メッシュを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
public:
/**************************************************************************
 D3DXVECTOR3 getPos() const;
 用途: 現在のポジションを得る
 戻り値: 現在のポジション
***************************************************************************/
	D3DXVECTOR3 getPos() const{
		return m_Pos;
	}

/**************************************************************************
 void setPos(D3DXVECTOR3& pos);
 用途:ポジションを設定
 戻り値: なし
***************************************************************************/
	void setPos(D3DXVECTOR3& pos){
		m_Pos = pos;
	}

};

}