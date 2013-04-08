#ifndef	__AnimationModelClass__
#define	__AnimationModelClass__
/*-----------------------------------------------------:
	Animation model Class .
 :-----------------------------------------------------*/
class AnimationModel
{
	class	CD3DXMesh ;
	class	CAllocateHierarchy ;
	class	CD3DXFrame ;

public:
	AnimationModel(  LPDIRECT3DDEVICE9 lpD3DDevice , char *pFileName  );
	~AnimationModel();

	void Release();
	bool Load( LPDIRECT3DDEVICE9 lpD3DDevice , char *pFileName );
	HRESULT GenerateSkinnedMesh( LPDIRECT3DDEVICE9 lpD3DDevice , CD3DXMesh *pCD3DXMesh );
	void draw(  LPDIRECT3DDEVICE9 lpD3DDevice , float Time  );
	void Update( LPDIRECT3DDEVICE9 lpD3DDevice , float Time );

	D3DXMATRIX& GetMatrix();
	void	setTrack(  DWORD Track  );
	int		getNumTracks(  void  );
	void	resetTime(){  pAnimController->ResetTime();  }
	bool SetTrackEnable( DWORD Track, BOOL Enable );
	bool setTrackSpeed( DWORD Track, FLOAT Speed );
	bool SetTrackWeight( DWORD Track, FLOAT Weight );

	DOUBLE	GetTime(  VOID  );
	void	SetTransform(  D3DXMATRIX *Matrix  );
	void	SetTrackPosition(  UINT Track , DOUBLE Position  );

	//	: 階層構造のルートフレームを取得する
	LPD3DXFRAME	getFrameRoot(  void  ){  return(  pFrameRoot  );  }

	//	: 動的にテクスチャを切り替える
	void AnimationModel::UpdateTexture( LPD3DXFRAME pD3DXFrame, LPDIRECT3DTEXTURE9 newTexture );

	//	: 現在のアニメーションモデルからアニメーションの階層構造を取得する
	void	CreateClone(  LPD3DXANIMATIONCONTROLLER *newAnmController  )
	{
		pAnimController->CloneAnimationController(  pAnimController->GetMaxNumAnimationOutputs() , pAnimController->GetMaxNumAnimationSets() , pAnimController->GetMaxNumTracks() , pAnimController->GetMaxNumEvents() ,  newAnmController  );
	}

	//	: アニメーション構造を基に描画を行う（引数に渡されたアニメーション構造はTimeで更新される）
	void draw(  LPDIRECT3DDEVICE9 lpD3DDevice , LPD3DXANIMATIONCONTROLLER glbAnmController , float Time  )
	{
		if( glbAnmController ) glbAnmController->AdvanceTime( Time , NULL );
		lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );

		UpdateFrameMatrices( pFrameRoot, &matWorld );
		DrawFrame( lpD3DDevice , pFrameRoot );
	}

	//	: 階層構造から指定の名前が付けられたフレームの行列を取得する
	D3DXMATRIX*	getFrameMatrixByName(  char* name , LPD3DXFRAME pD3DXFrame  );

	//	: 階層構造から指定の名前がつけられたメッシュを取得する
	void		searchMeshByName(  char* name , LPD3DXFRAME pD3DXFrame  );

	void	changeColor(  DWORD color , LPD3DXFRAME pD3DXFrame  );


	//	: ※2013/01/11 追加 鴫原
	LPD3DXMESH GetMesh();
	//	: ※2013/01/24 追加 鴫原
	LPD3DXMESH MeshSearch(LPD3DXFRAME pD3DXFrame);

private:
	void DrawMeshContainer( LPDIRECT3DDEVICE9 lpD3DDevice , LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pD3DXFrame );
	void DrawFrame( LPDIRECT3DDEVICE9 lpD3DDevice , LPD3DXFRAME pD3DXFrame );
	bool SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pD3DXMeshContainer );
	bool SetupBoneMatrixPointers( LPD3DXFRAME pD3DXFrame );
	void UpdateFrameMatrices( LPD3DXFRAME pD3DXFrame, LPD3DXMATRIX pParentMatrix );

private:
    UINT						NumBoneMatricesMax;
    D3DXMATRIXA16*				pBoneMatrices;
    LPD3DXFRAME					pFrameRoot;
    LPD3DXANIMATIONCONTROLLER	pAnimController;
	D3DXMATRIX					matWorld;

	char	*pFilePath ;
	bool	releaseFlg ;
};


class AnimationModel::CD3DXMesh: public D3DXMESHCONTAINER
{
public:
	CD3DXMesh();
	~CD3DXMesh();
	void SetName( LPCSTR Name );

public:
    LPDIRECT3DTEXTURE9*  ppTextures;       // array of textures, entries are NULL if no texture specified    
                                
    // SkinMesh info             
    LPD3DXMESH           pOrigMesh;
    LPD3DXATTRIBUTERANGE pAttributeTable;
    DWORD                NumAttributeGroups; 
    LPD3DXBUFFER         pBoneCombinationBuf;
    D3DXMATRIX**         ppBoneMatrixPtrs;
    D3DXMATRIX*          pBoneOffsetMatrices;
};


class AnimationModel::CAllocateHierarchy: public ID3DXAllocateHierarchy
{
public:
	STDMETHOD( CreateFrame )( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame );
	STDMETHOD( CreateMeshContainer )( THIS_ LPCSTR Name, const D3DXMESHDATA *pMeshData,
					const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, 
					const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
					LPD3DXMESHCONTAINER *ppNewMeshContainer );
	STDMETHOD( DestroyFrame )( THIS_ LPD3DXFRAME pFrameToFree );
	STDMETHOD( DestroyMeshContainer )( THIS_ LPD3DXMESHCONTAINER pMeshContainerBase );
	CAllocateHierarchy( AnimationModel *pAnimationModel );

private:
	AnimationModel* pAnimationModel;
};


class AnimationModel::CD3DXFrame: public D3DXFRAME
{
public:
	CD3DXFrame();
	~CD3DXFrame();
	void SetName( LPCSTR Name );

public:
	D3DXMATRIXA16 CombinedTransformationMatrix;
};


#endif