#include	"stdafx.h"
#include	"AnimationModelClass.h"

#if defined( CF_OVERLORDNEW_ENABLE )
	#define new new
#endif
/*-----------------------------------------------------:
	Animation model Class impliment .
 :-----------------------------------------------------*/
AnimationModel::AnimationModel(  LPDIRECT3DDEVICE9 lpD3DDevice , char *pFileName  )
{
	NumBoneMatricesMax	= 0;
	pBoneMatrices		= NULL;
	pFrameRoot			= NULL;
	pAnimController		= NULL;
	D3DXMatrixIdentity( &matWorld );

	releaseFlg	= true ;

	this->Load(  lpD3DDevice , pFileName  );
}

AnimationModel::~AnimationModel()
{
	Release(); // リリース忘れ防止
}

bool AnimationModel::Load( LPDIRECT3DDEVICE9 lpD3DDevice , char *pFileName )
{
	size_t	pathLength ;
	for(  pathLength = strlen(pFileName) ; pathLength >= 0 ; pathLength--  )
		if(  pFileName[ pathLength ] == '/' || pFileName[ pathLength ] == '\\'  )
			break ;
	pFilePath	= new char[ pathLength + 1 ] ;
	for(  size_t i = 0 ; i < pathLength ; i++  )
		pFilePath[ i ]	= pFileName[ i ] ;
	pFilePath[ pathLength ]	= '\0' ;
	
    CAllocateHierarchy Alloc( this );

    LPD3DXANIMATIONCONTROLLER pAnimControllerTmp;
    if( FAILED( D3DXLoadMeshHierarchyFromXA(
		pFileName, D3DXMESH_MANAGED, lpD3DDevice,	&Alloc, NULL, &pFrameRoot, &pAnimControllerTmp ) ) ) return false;

	// 利便性を考えて、トラック数をアニメーションセット数に増やす
	int TracksNum   = pAnimControllerTmp->GetMaxNumTracks();
	int AnimSetsNum = pAnimControllerTmp->GetMaxNumAnimationSets();
	if( TracksNum < AnimSetsNum ) TracksNum = AnimSetsNum;

	if( FAILED( pAnimControllerTmp->CloneAnimationController(
		pAnimControllerTmp->GetMaxNumAnimationOutputs(),
		pAnimControllerTmp->GetMaxNumAnimationSets(),
		TracksNum,
		pAnimControllerTmp->GetMaxNumEvents(),
		&pAnimController ) ) ) return false;

	SAFE_RELEASE( pAnimControllerTmp );

	if( AnimSetsNum > 1 ){
		// トラックに全てのアニメーションセットを読み込む
		for( int i = 1; i < AnimSetsNum; i++ ){
			LPD3DXANIMATIONSET pAnimSet = NULL;
			if( FAILED( pAnimController->GetAnimationSet( i, &pAnimSet ) ) ) return false;
			if( FAILED( pAnimController->SetTrackAnimationSet( i, pAnimSet ) ) ) return false;

			// 全てのトラックにデフォルトのD3DXTRACK_DESCを設定しておく
			D3DXTRACK_DESC Desc = { D3DXPRIORITY_LOW, 1, 1, 0.0 , FALSE };
			if( FAILED( pAnimController->SetTrackDesc( i, &Desc ) ) ) return false;
		}
	}

    if( FAILED( SetupBoneMatrixPointers( pFrameRoot ) ) ) return false;

	return true;
}

void AnimationModel::Release()
{
	if( pFrameRoot ){
		CAllocateHierarchy Alloc( this );
		D3DXFrameDestroy( pFrameRoot, &Alloc );
		pFrameRoot = NULL;
	}

	SAFE_DELETE_ARRAY( pBoneMatrices );
	SAFE_RELEASE( pAnimController );

	SAFE_DELETE_ARRAY( pFilePath );
}

HRESULT AnimationModel::GenerateSkinnedMesh( LPDIRECT3DDEVICE9 lpD3DDevice , CD3DXMesh *pCD3DXMesh )
{
	HRESULT hr = S_OK;

	if( !pCD3DXMesh->pSkinInfo ) return hr;
	SAFE_RELEASE( pCD3DXMesh->MeshData.pMesh );
	SAFE_RELEASE( pCD3DXMesh->pBoneCombinationBuf );

	hr = pCD3DXMesh->pOrigMesh->CloneMeshFVF(
			D3DXMESH_MANAGED, pCD3DXMesh->pOrigMesh->GetFVF(),
			lpD3DDevice, &pCD3DXMesh->MeshData.pMesh );
	if( FAILED( hr ) ) goto e_Exit;

	hr = pCD3DXMesh->MeshData.pMesh->GetAttributeTable( NULL, &pCD3DXMesh->NumAttributeGroups );
	if( FAILED( hr ) ) goto e_Exit;

	delete[] pCD3DXMesh->pAttributeTable;
	pCD3DXMesh->pAttributeTable = new D3DXATTRIBUTERANGE[pCD3DXMesh->NumAttributeGroups];
	if( !pCD3DXMesh->pAttributeTable ){
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}

	hr = pCD3DXMesh->MeshData.pMesh->GetAttributeTable( pCD3DXMesh->pAttributeTable, NULL );
	if( FAILED( hr ) ) goto e_Exit;

	// 他のメッシュによってボーン行列用のメモリが確保しきれていない場合は確保
	if( NumBoneMatricesMax < pCD3DXMesh->pSkinInfo->GetNumBones() ){
		NumBoneMatricesMax = pCD3DXMesh->pSkinInfo->GetNumBones();

		delete []pBoneMatrices;
		pBoneMatrices = new D3DXMATRIXA16[NumBoneMatricesMax];
		if( !pBoneMatrices ){
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}
    }

e_Exit:
    return hr;
}

void AnimationModel::DrawMeshContainer( LPDIRECT3DDEVICE9 lpD3DDevice , LPD3DXMESHCONTAINER pD3DXMeshContainer, LPD3DXFRAME pD3DXFrame )
{
	CD3DXMesh *pCD3DXMesh = (CD3DXMesh*)pD3DXMeshContainer;

	if( pCD3DXMesh->pSkinInfo ){ // スキンメッシュの場合
		DWORD NumBones = pCD3DXMesh->pSkinInfo->GetNumBones();
		{
			for( DWORD i = 0; i < NumBones; i++ ){
				D3DXMatrixMultiply(
					&pBoneMatrices[i],
					&pCD3DXMesh->pBoneOffsetMatrices[i], 
					pCD3DXMesh->ppBoneMatrixPtrs[i]
				);
			}
		}

		// ワールド行列をクリア
		D3DXMATRIX Identity;
		D3DXMatrixIdentity( &Identity );
		lpD3DDevice->SetTransform( D3DTS_WORLD, &Identity );

		// 頂点バッファをロック
		PBYTE pVerticesSrc;
		PBYTE pVerticesDest;
		pCD3DXMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc );
		pCD3DXMesh->MeshData.pMesh->LockVertexBuffer( 0, (LPVOID*)&pVerticesDest );

		// スキンメッシュ作成
		pCD3DXMesh->pSkinInfo->UpdateSkinnedMesh( pBoneMatrices, NULL, pVerticesSrc, pVerticesDest );

		// 頂点バッファのロックを解除
		pCD3DXMesh->pOrigMesh->UnlockVertexBuffer();
		pCD3DXMesh->MeshData.pMesh->UnlockVertexBuffer();

		// スキンメッシュ描画
		for( UINT i = 0; i < pCD3DXMesh->NumAttributeGroups; i++ ){
			lpD3DDevice->SetMaterial( &( pCD3DXMesh->pMaterials[pCD3DXMesh->pAttributeTable[i].AttribId].MatD3D ) );
			lpD3DDevice->SetTexture( 0, pCD3DXMesh->ppTextures[pCD3DXMesh->pAttributeTable[i].AttribId] );
			pCD3DXMesh->MeshData.pMesh->DrawSubset( pCD3DXMesh->pAttributeTable[i].AttribId );
		}
	}
	else{ // 通常のメッシュの場合
		lpD3DDevice->SetTransform( D3DTS_WORLD, &( (CD3DXFrame *)pD3DXFrame )->CombinedTransformationMatrix );

		// メッシュ描画
		for ( DWORD i = 0; i < pCD3DXMesh->NumMaterials; i++ ){
			lpD3DDevice->SetMaterial( &pCD3DXMesh->pMaterials[i].MatD3D );
			lpD3DDevice->SetTexture( 0, pCD3DXMesh->ppTextures[i] );
			pCD3DXMesh->MeshData.pMesh->DrawSubset( i );
		}
	}

}

void AnimationModel::DrawFrame( LPDIRECT3DDEVICE9 lpD3DDevice , LPD3DXFRAME pD3DXFrame )
{
	LPD3DXMESHCONTAINER pD3DXMeshContainer;

	pD3DXMeshContainer = pD3DXFrame->pMeshContainer;
	while( pD3DXMeshContainer ){
		DrawMeshContainer( lpD3DDevice , pD3DXMeshContainer, pD3DXFrame );
		pD3DXMeshContainer = pD3DXMeshContainer->pNextMeshContainer;
	}

	if( pD3DXFrame->pFrameSibling ) DrawFrame( lpD3DDevice , pD3DXFrame->pFrameSibling );
	if( pD3DXFrame->pFrameFirstChild ) DrawFrame( lpD3DDevice , pD3DXFrame->pFrameFirstChild );
}

void AnimationModel::draw(  LPDIRECT3DDEVICE9 lpD3DDevice , float Time  )
{
	Update(  lpD3DDevice , Time  );
	DrawFrame( lpD3DDevice , pFrameRoot );
}

bool AnimationModel::SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer )
{
	CD3DXMesh *pCD3DXMesh = (CD3DXMesh*)pD3DXMeshContainer;

	// スキンメッシュのときはボーン行列をセット
	if( pCD3DXMesh->pSkinInfo ){
		DWORD NumBones = pCD3DXMesh->pSkinInfo->GetNumBones();

		pCD3DXMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[NumBones];
		if( !pCD3DXMesh->ppBoneMatrixPtrs ) return false;

		for( DWORD i = 0; i < NumBones; i++ ){
			CD3DXFrame *pCD3DXFrame = (CD3DXFrame*)D3DXFrameFind(
				pFrameRoot, pCD3DXMesh->pSkinInfo->GetBoneName( i ) );
			if( !pCD3DXFrame ) return false;

			pCD3DXMesh->ppBoneMatrixPtrs[i] = &pCD3DXFrame->CombinedTransformationMatrix;
		}
	}

	return true;
}


bool AnimationModel::SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame )
{
	if( pD3DXFrame->pMeshContainer ){
		if( FAILED( SetupBoneMatrixPointersOnMesh( pD3DXFrame->pMeshContainer ) ) ) return false;
	}

	if( pD3DXFrame->pFrameSibling ){
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameSibling ) ) ) return false;
	}

	if( pD3DXFrame->pFrameFirstChild ){
		if( FAILED( SetupBoneMatrixPointers( pD3DXFrame->pFrameFirstChild ) ) ) return false;
	}

	return true;
}

void AnimationModel::UpdateFrameMatrices( LPD3DXFRAME pD3DXMesh, LPD3DXMATRIX pParentMatrix )
{
	CD3DXFrame *pCD3DXFrame = (CD3DXFrame*)pD3DXMesh;

	if( pParentMatrix ){
		D3DXMatrixMultiply(
			&pCD3DXFrame->CombinedTransformationMatrix, &pCD3DXFrame->TransformationMatrix, pParentMatrix );
	}
	else pCD3DXFrame->CombinedTransformationMatrix = pCD3DXFrame->TransformationMatrix;

	if( pCD3DXFrame->pFrameSibling ) UpdateFrameMatrices( pCD3DXFrame->pFrameSibling, pParentMatrix );

	if( pCD3DXFrame->pFrameFirstChild ) UpdateFrameMatrices( pCD3DXFrame->pFrameFirstChild, &pCD3DXFrame->CombinedTransformationMatrix );
}

void AnimationModel::UpdateTexture( LPD3DXFRAME pD3DXFrame, LPDIRECT3DTEXTURE9 newTexture )
{
	CD3DXMesh*	mesh	= (CD3DXMesh*)(pD3DXFrame->pMeshContainer);

	if(  mesh  )	{
		for(  int i = 0 ; i < sizeof(mesh->ppTextures)/sizeof(LPDIRECT3DTEXTURE9) ; i++  )
		{
			if(  releaseFlg  )	{
				releaseFlg	= false ;
				SAFE_RELEASE(  mesh->ppTextures[ i ]  );
			}
			mesh->ppTextures[ i ]	= newTexture ;
		}
	}

	if( pD3DXFrame->pFrameSibling )		UpdateTexture(  pD3DXFrame->pFrameSibling , newTexture  );
	if( pD3DXFrame->pFrameFirstChild )	UpdateTexture(  pD3DXFrame->pFrameFirstChild , newTexture  );
}

void	AnimationModel::searchMeshByName(  char* name , LPD3DXFRAME pD3DXFrame  )
{
	if(  pD3DXFrame->pMeshContainer  )	{
		if(  !strcmp(pD3DXFrame->pMeshContainer->Name,name)  )
			MessageBox(0,0,0,0);
	}

	if( pD3DXFrame->pFrameSibling )		searchMeshByName(  name , pD3DXFrame->pFrameSibling  );
	if( pD3DXFrame->pFrameFirstChild )	searchMeshByName(  name , pD3DXFrame->pFrameFirstChild  );
}

D3DXMATRIX*	AnimationModel::getFrameMatrixByName(  char* name , LPD3DXFRAME pD3DXFrame  )
{
	static D3DXMATRIX	*mat = NULL ;
	if(  pD3DXFrame  )	{
		if(  pD3DXFrame->Name  )
			if(  !strcmp(pD3DXFrame->Name,name)  )
				mat	= (D3DXMATRIX*)&((CD3DXFrame*)(pD3DXFrame))->CombinedTransformationMatrix ;

		if( pD3DXFrame->pFrameSibling )		getFrameMatrixByName(  name , pD3DXFrame->pFrameSibling  );
		if( pD3DXFrame->pFrameFirstChild )	getFrameMatrixByName(  name , pD3DXFrame->pFrameFirstChild  );
	}

	return	mat ;
}

void	AnimationModel::changeColor(  DWORD color , LPD3DXFRAME pD3DXFrame  )
{
	struct	Vertex
	{
		D3DXVECTOR3	pos ;
		D3DXVECTOR3	nml ;
		D3DCOLOR	clr ;
		D3DXVECTOR2	tex ;
	};

	CD3DXMesh*	mesh	= (CD3DXMesh*)(pD3DXFrame->pMeshContainer);

	if(  mesh  )
	{
		Vertex	*vtx ;
		void	*v ;
		mesh->pOrigMesh->LockVertexBuffer(  0 , (void**)&v  );
		vtx	= (Vertex*)v ;
		for(  DWORD i = 0 ; i < mesh->pOrigMesh->GetNumVertices() ; i++  )
		{
			vtx[ i ].clr	= color ;
		}
		mesh->pOrigMesh->UnlockVertexBuffer();
	}

	if( pD3DXFrame->pFrameSibling )		changeColor(  color , pD3DXFrame->pFrameSibling  );
	if( pD3DXFrame->pFrameFirstChild )	changeColor(  color , pD3DXFrame->pFrameFirstChild  );
}

void AnimationModel::Update( LPDIRECT3DDEVICE9 lpD3DDevice , float Time )
{
	if( pAnimController ) pAnimController->AdvanceTime( Time , NULL );
	lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );

	UpdateFrameMatrices( pFrameRoot, &matWorld );
}

// 以下ユーティリティ関数群
D3DXMATRIX& AnimationModel::GetMatrix()
{
	return matWorld;
}

void AnimationModel::setTrack(  DWORD Track  )
{
	for(  int i = 0 ; i < getNumTracks() ; i++  )
	{
		this->SetTrackEnable(  i , FALSE  );
	}
	this->SetTrackEnable(  Track%pAnimController->GetNumAnimationSets() , TRUE  );
}

int	AnimationModel::getNumTracks(  void  )
{
	return	pAnimController->GetNumAnimationSets();
}

bool AnimationModel::SetTrackEnable( DWORD Track, BOOL Enable )
{
	if( FAILED( pAnimController->SetTrackEnable( Track, Enable ) ) ){
		return false;
	}

	return true;
}

bool AnimationModel::setTrackSpeed( DWORD Track, FLOAT Speed )
{
	if( FAILED( pAnimController->SetTrackSpeed( Track, Speed ) ) ){
		return false;
	}

	return true;
}

bool AnimationModel::SetTrackWeight( DWORD Track, FLOAT Weight )
{
	if( FAILED( pAnimController->SetTrackWeight( Track, Weight ) ) ){
		return false;
	}

	return true;
}

DOUBLE	AnimationModel::GetTime(  VOID  )
{
	return(  pAnimController->GetTime()  );
}

void	AnimationModel::SetTransform(  D3DXMATRIX *Matrix  )
{
	memcpy(  this->matWorld , *Matrix , sizeof(D3DXMATRIX)  );
}

void	AnimationModel::SetTrackPosition(  UINT Track , DOUBLE Position  )
{
	this->pAnimController->SetTrackPosition(  Track , Position  );
}

//	: ※2013/01/11 追加 鴫原
LPD3DXMESH AnimationModel::GetMesh(){

	//CD3DXMesh *pCD3DXMesh = (CD3DXMesh*)pFrameFirstChild->pMeshContainer;
	return MeshSearch(this->pFrameRoot);
}
//	: ※2013/01/24 追加 鴫原
LPD3DXMESH AnimationModel::MeshSearch(LPD3DXFRAME pD3DXFrame){
	LPD3DXMESHCONTAINER pD3DXMeshContainer;

	pD3DXMeshContainer = pD3DXFrame->pMeshContainer;
	if( pD3DXMeshContainer ){
		CD3DXMesh *pCD3DXMesh = (CD3DXMesh*)pD3DXMeshContainer;
		return pCD3DXMesh->pOrigMesh;
	}

	if( pD3DXFrame->pFrameSibling ) MeshSearch( pD3DXFrame->pFrameSibling );
	if( pD3DXFrame->pFrameFirstChild ) MeshSearch( pD3DXFrame->pFrameFirstChild );
	return NULL;
}


/*	: Mesh	*/

AnimationModel::CD3DXMesh::CD3DXMesh()
{
	// D3DXMESHCONTAINER 由来の変数を初期化
	Name = NULL;
	ZeroMemory( &MeshData, sizeof( D3DXMESHDATA ) );
	pMaterials = NULL;
	pEffects = NULL;
	NumMaterials = 0;
	pAdjacency = NULL;
	pSkinInfo = NULL;

	// メンバ変数の初期化
	ppTextures = NULL;
	pOrigMesh = NULL;
	pAttributeTable = NULL;
	NumAttributeGroups = 0; 
	pBoneCombinationBuf = NULL;
	ppBoneMatrixPtrs = NULL;
	pBoneOffsetMatrices = NULL;
}

AnimationModel::CD3DXMesh::~CD3DXMesh()
{
	SAFE_DELETE_ARRAY( Name );
	SAFE_RELEASE( MeshData.pMesh );
	SAFE_DELETE_ARRAY( pMaterials );
	SAFE_DELETE( pEffects ); // SAFE_DELETE_ARRAYかも???
	SAFE_DELETE_ARRAY( pAdjacency );
	SAFE_RELEASE( pSkinInfo );

	if( ppTextures ){
		for( UINT i = 0; i < NumMaterials; i++ ){
			SAFE_RELEASE( ppTextures[i] );
		}
	}
	SAFE_DELETE_ARRAY( ppTextures );
	SAFE_RELEASE( pOrigMesh );
	SAFE_DELETE_ARRAY( pAttributeTable );
	SAFE_RELEASE( pBoneCombinationBuf );
	SAFE_DELETE_ARRAY( ppBoneMatrixPtrs );
	SAFE_DELETE_ARRAY( pBoneOffsetMatrices );
}

void AnimationModel::CD3DXMesh::SetName( LPCSTR Name )
{
	if( Name ){
		UINT Length;
		Length = lstrlenA( Name ) + 1;
		SAFE_DELETE_ARRAY( this->Name );
		this->Name = new char[Length];
		memcpy( this->Name, Name, Length );
	}
}

/*	: AllocateHieararchy	*/

AnimationModel::CAllocateHierarchy::CAllocateHierarchy( AnimationModel *pAnimationModel )
{
	this->pAnimationModel = pAnimationModel;
}

HRESULT AnimationModel::CAllocateHierarchy::CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame )
{
	*ppNewFrame = NULL;

	CD3DXFrame *pFrame = new CD3DXFrame;
	if( !pFrame ) return E_OUTOFMEMORY;

	pFrame->SetName( Name );
	*ppNewFrame = pFrame;

	return S_OK;
}

HRESULT AnimationModel::CAllocateHierarchy::CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData,
                            const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, 
                            const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
                            LPD3DXMESHCONTAINER *ppNewMeshContainer ) 
{
	HRESULT hr = S_OK;

	*ppNewMeshContainer = NULL;

	// patch meshes を扱う事はできない
	if( pMeshData->Type != D3DXMESHTYPE_MESH ) return E_FAIL;

	LPD3DXMESH pMesh = pMeshData->pMesh;

	// FVF で記述されたメッシュ以外は読めません
	if( pMesh->GetFVF() == 0 ) return E_FAIL;
	UINT NumFaces = pMesh->GetNumFaces();

	// メッシュ作成
	CD3DXMesh *pCD3DXMesh = new CD3DXMesh();
	if( !pCD3DXMesh ) return E_OUTOFMEMORY;

	pCD3DXMesh->SetName( Name );
	pCD3DXMesh->MeshData.Type = D3DXMESHTYPE_MESH;

	LPDIRECT3DDEVICE9 pD3DDevice = NULL;
	if( FAILED( pMesh->GetDevice( &pD3DDevice ) ) ){
		hr = E_FAIL;
		goto e_Exit;
	}

	// Xファイルに法線が無かったら計算で求める
	if( !( pMesh->GetFVF() & D3DFVF_NORMAL ) ){

		// FVFに法線を追加した新しいメッシュにする
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
                                  pMesh->GetFVF() | D3DFVF_NORMAL, 
                                  pD3DDevice, &pCD3DXMesh->MeshData.pMesh );
        if( FAILED( hr ) ) goto e_Exit;

		// 引数で渡されたメッシュへのポインタに新しいメッシュへのポインタをセット
		// pMeshへの参照はこの時点で存在しないので、ここではreleaseをかけない
		pMesh = pCD3DXMesh->MeshData.pMesh;

		D3DXComputeNormals( pMesh, NULL );
	}
	else{
		// リファレンスを増やすだけ
		pCD3DXMesh->MeshData.pMesh = pMesh;
		pMesh->AddRef();
	}

	// マテリアル用のメモリを確保
	pCD3DXMesh->NumMaterials = max( 1, NumMaterials );
	pCD3DXMesh->pMaterials = new D3DXMATERIAL[pCD3DXMesh->NumMaterials];
	pCD3DXMesh->ppTextures = new LPDIRECT3DTEXTURE9[pCD3DXMesh->NumMaterials];
	pCD3DXMesh->pAdjacency = new DWORD[NumFaces * 3];
	if( !pCD3DXMesh->pAdjacency || !pCD3DXMesh->pMaterials ){
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}

	memcpy( pCD3DXMesh->pAdjacency, pAdjacency, sizeof( DWORD ) * NumFaces * 3 );
	memset( pCD3DXMesh->ppTextures, 0, sizeof( LPDIRECT3DTEXTURE9 ) * pCD3DXMesh->NumMaterials );

	// マテリアルのコピー
	if( NumMaterials > 0 ){
		memcpy( pCD3DXMesh->pMaterials, pMaterials, sizeof( D3DXMATERIAL ) * NumMaterials );

		for( UINT i = 0; i < NumMaterials; i++ ){
			if( pCD3DXMesh->pMaterials[i].pTextureFilename ){
				//////////
				//	: 2013年2月7日 追加/変更 鴫原 徹
				//	: 
				std::string sTexDir ;
				TLIB::narrow(g_sDefaultTexturePath,sTexDir);
				size_t	pathSize	= strlen(sTexDir.c_str()) + strlen(pCD3DXMesh->pMaterials[i].pTextureFilename) + 1 ;
				char	*pTexPathName	= new char[ pathSize ] ;
				sprintf_s(  pTexPathName , pathSize , "%s%s" , sTexDir.c_str() , pCD3DXMesh->pMaterials[i].pTextureFilename  ); /*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
				//	:
				//	:
				//////////
				if( FAILED( D3DXCreateTextureFromFileA(
								pD3DDevice, pTexPathName,
								&pCD3DXMesh->ppTextures[i] ) ) ) pCD3DXMesh->ppTextures[i] = NULL;

				// 安全のためにNULLクリア
				SAFE_DELETE_ARRAY( pTexPathName );
				pCD3DXMesh->pMaterials[i].pTextureFilename = NULL;
			}
		}
	}
	else{ // マテリアルが無いときは適当にセット
		pCD3DXMesh->pMaterials[0].pTextureFilename = NULL;
		memset( &pCD3DXMesh->pMaterials[0].MatD3D, 0, sizeof( D3DMATERIAL9 ) );
		pCD3DXMesh->pMaterials[0].MatD3D.Diffuse.r = 1.0f;
		pCD3DXMesh->pMaterials[0].MatD3D.Diffuse.g = 1.0f;
		pCD3DXMesh->pMaterials[0].MatD3D.Diffuse.b = 1.0f;
		pCD3DXMesh->pMaterials[0].MatD3D.Specular = pCD3DXMesh->pMaterials[0].MatD3D.Diffuse;
	}

	if( pSkinInfo ){ // ワンスキン形式のXファイル
		// pSkinInfo と pMesh をセット
		pCD3DXMesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pCD3DXMesh->pOrigMesh = pMesh;
		pMesh->AddRef();

		// Bone Offset Matrices 保存用のメモリを確保
		UINT NumBones = pSkinInfo->GetNumBones();
		pCD3DXMesh->pBoneOffsetMatrices = new D3DXMATRIX[NumBones];
		if( !pCD3DXMesh->pBoneOffsetMatrices ){
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// Bone Offset Matrices 読み込み
		for( UINT i = 0; i < NumBones; i++ ){
			pCD3DXMesh->pBoneOffsetMatrices[i] = *( pCD3DXMesh->pSkinInfo->GetBoneOffsetMatrix( i ) );
		}

		// スキンメッシュ作成
		hr = pAnimationModel->GenerateSkinnedMesh( pD3DDevice , pCD3DXMesh );
        if( FAILED( hr ) ) goto e_Exit;
	}

	*ppNewMeshContainer = pCD3DXMesh;
	pCD3DXMesh = NULL;

e_Exit:
	SAFE_RELEASE( pD3DDevice );
	if( pCD3DXMesh ) DestroyMeshContainer( pCD3DXMesh );

	return hr;
}

HRESULT AnimationModel::CAllocateHierarchy::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	CD3DXFrame *pCD3DXFrame = (CD3DXFrame*)pFrameToFree;
	SAFE_DELETE( pCD3DXFrame );

	return S_OK; 
}

HRESULT AnimationModel::CAllocateHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER pCD3DXMeshBase )
{
	CD3DXMesh *pCD3DXMesh = (CD3DXMesh*)pCD3DXMeshBase;
	SAFE_DELETE( pCD3DXMesh );

	return S_OK;
}

/*	: Frame	*/

AnimationModel::CD3DXFrame::CD3DXFrame()
{
	// D3DXFRAME 由来の変数を初期化
	Name = NULL;
	D3DXMatrixIdentity( &TransformationMatrix );
	pMeshContainer = NULL;
	pFrameSibling = NULL;
	pFrameFirstChild = NULL;

	// メンバ変数初期化
	D3DXMatrixIdentity( &CombinedTransformationMatrix );
}

AnimationModel::CD3DXFrame::~CD3DXFrame()
{
	SAFE_DELETE_ARRAY( Name );
}

void AnimationModel::CD3DXFrame::SetName( LPCSTR Name )
{
	if( Name ){
		UINT Length;
		Length = (UINT)strlen( Name ) + 1;
		SAFE_DELETE_ARRAY( this->Name );
		this->Name = new char[Length];
		memcpy( this->Name, Name, Length );
	}
}
