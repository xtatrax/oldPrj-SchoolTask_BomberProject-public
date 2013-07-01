////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FTextureManager.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�e�N�X�`���[�̊Ǘ�
//					��
//	namespace wiz;
//		class TextureManager;
//		class TextureManager::Texture;
//
#include "StdAfx.h"
#include "TextureManager.h"
#include "TL-String.h"
namespace wiz {
/**************************************************************************
 TextureManager ��`��
/***************************************************************************/

/////////////////// ////////////////////
//// �p�r       �FTextureManager::TextureManager()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
TextureManager::TextureManager(){

};
/////////////////// ////////////////////
//// �p�r       �FTextureManager::~TextureManager()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�j��������
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
TextureManager::~TextureManager(){
	Release();
};
/////////////////// ////////////////////
//// �p�r       �FTextureManager::Release()
//// �J�e�S��   �F�֐�
//// �p�r       �F�S�e�N�X�`���[�̔j��
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
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
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureManager::addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
////            �F  	const wchar_t *filepath, const wchar_t *texturename )
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`���[�̓ǂݍ���
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	// �f�o�C�X
////            �F  const wchar_t *filepath			// �t�@�C���p�X
////            �F  const wchar_t *texturename		// �e�N�X�`���� ( �I�v�V���� )
//// �ߒl       �F�������ꂽ�e�N�X�`���̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// ���l       �F
////            �F
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
			// ���������s
			::MessageBox(NULL,L"�e�N�X�`�������������܂���\nTextureManager::addTexture()",L"�G���[",MB_OK);
			
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
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��TextureManager::addTexture()"
				);
	}
	catch(...){
		//�R���X�g���N�^��O����
		//��n��
		Release();
		//�ăX���[
		throw;
	}
};
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureManager::addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F  	UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
////            �F  	DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename )
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`���[�̓ǂݍ���
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	// �f�o�C�X
////            �F  const wchar_t *filepath			// �t�@�C���p�X
////            �F  UINT Width						// �摜�̕�(0�ŃI���W�i��)
////            �F  UINT Height						// �摜�̍���(0�ŃI���W�i��)
////            �F  UINT MipLevels					// �~�b�v���x��(�ʏ�0)
////            �F  DWORD Usage						// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
////            �F  D3DFORMAT Format				// �F�̃t�H�[�}�b�g
////            �F  D3DPOOL Pool					// �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
////            �F  DWORD Filter					// �t�B���^�[(������Ȃ��Ă�k)
////            �F  DWORD MipFilter					// �~�b�v�t�B���^�[(������Ȃ��Ă�k)
////            �F  D3DCOLOR ColorKey				// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
////            �F  D3DXIMAGE_INFO *pSrcInfo		// �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
////            �F  PALETTEENTRY *pPalette			// �p���b�g
////            �F  const wchar_t *texturename		// �e�N�X�`����(�I�v�V����)
//// �ߒl       �F����
//// ���l       �F
////            �F
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

			// ���������s
			::MessageBox(NULL,L"�e�N�X�`�������������܂���\nTextureManager::addTextureEx()",L"�G���[",MB_OK);
		}
		else
		{
			Texture* tx = new Texture(
					pD3DDevice ,
					filepath ,
					Width,				// �摜�̕�(0�ŃI���W�i��)
					Height,				// �摜�̍���(0�ŃI���W�i��)
					MipLevels,			// �~�b�v���x��(�ʏ�0)
					Usage,				// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
					Format,				// �F�̃t�H�[�}�b�g
					Pool,				// �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
					Filter,				// �t�B���^�[(������Ȃ��Ă�k)
					MipFilter,			// �~�b�v�t�B���^�[(������Ȃ��Ă�k)
					ColorKey,			// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
					pSrcInfo,			// �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
					pPalette,			// �p���b�g
					texturename);
			m_vecTextures.push_back( tx );
			return tx->getTexture();
		}

		return NULL;
	}
	catch(wiz::BaseException& e){
		Release();
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��TextureManager::addTextureEx()"
				);
	}
	catch(...){
		//�R���X�g���N�^��O����
		//��n��
		Release();
		//�ăX���[
		throw;
	}
};
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureManager::addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F  	DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename )
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`���[�̓ǂݍ���
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	// �f�o�C�X
////            �F  const wchar_t *filepath			// �t�@�C���p�X
////            �F  UINT Width						// �摜�̕�(0�ŃI���W�i��)
////            �F  UINT Height						// �摜�̍���(0�ŃI���W�i��)
////            �F  UINT MipLevels					// �~�b�v���x��(�ʏ�0)
////            �F  DWORD Usage						// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
////            �F  D3DFORMAT Format				// �F�̃t�H�[�}�b�g
////            �F  D3DPOOL Pool					// �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
////            �F  DWORD Filter					// �t�B���^�[(������Ȃ��Ă�k)
////            �F  DWORD MipFilter					// �~�b�v�t�B���^�[(������Ȃ��Ă�k)
////            �F  D3DCOLOR ColorKey				// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
////            �F  D3DXIMAGE_INFO *pSrcInfo		// �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
////            �F  PALETTEENTRY *pPalette			// �p���b�g
////            �F  const wchar_t *texturename		// �e�N�X�`����(�I�v�V����)
//// �ߒl       �F����
//// ���l       �F
////            �F
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
			// ���������s
			::MessageBox(NULL,L"�e�N�X�`�������������܂���\nTextureManager::addTextureExLight()",L"�G���[",MB_OK);
		}
		else
		{
			Texture* tx = new Texture(
					pD3DDevice ,
					filepath ,
					0,					// �摜�̕�(0�ŃI���W�i��)
					0,					// �摜�̍���(0�ŃI���W�i��)
					0,					// �~�b�v���x��(�ʏ�0)
					Usage,				// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
					Format,				// �F�̃t�H�[�}�b�g
					D3DPOOL_MANAGED,	// �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
					D3DX_FILTER_LINEAR,	// �t�B���^�[(������Ȃ��Ă�k)
					D3DX_FILTER_LINEAR,	// �~�b�v�t�B���^�[(������Ȃ��Ă�k)
					ColorKey,			// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
					NULL,				// �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
					NULL,				// �p���b�g
					texturename);
			m_vecTextures.push_back( tx );
			return tx->getTexture();
		}
		return NULL;
	}
	catch(wiz::BaseException& e){
		Release();
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��TextureManager::addTextureExLight()"
				);
	}
	catch(...){
		//�R���X�g���N�^��O����
		//��n��
		Release();
		//�ăX���[
		throw;
	}
};
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromName(const wchar_t* filename)
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`��������ǂݍ��ݍς݂̃e�N�X�`���[������
//// ����       �F  const wchar_t* filename		// ��������t�@�C����
//// �ߒl       �F���������e�N�X�`���̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// ���l       �F
////            �F
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
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureManager::TextureSearchFromFilePath(const wchar_t* path)
//// �J�e�S��   �F�֐�
//// �p�r       �F�t�@�C���p�X����ǂݍ��ݍς݂̃e�N�X�`���[������
//// ����       �F  const wchar_t* path		// ��������t�@�C����
//// �ߒl       �F���������e�N�X�`���̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// ���l       �F
////            �F
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
 TextureManager::Texture ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �FTextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F    const wchar_t* texturename = L"")
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FNormalLoad
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		// ��������t�@�C����
////            �F  const wchar_t* filepath             // 
////            �F  const wchar_t* texturename = L""    // 
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,const wchar_t* texturename )
:m_pTexture( 0 )
,m_strFilePath( filepath )
,m_strTexName( texturename )
{
	try{
		wstring sFileName ;
		//�e�N�X�`���̍쐬
		if( PathFileExists( filepath ) ){
			sFileName = filepath ;
		}else if( PathFileExists( wstring( g_sDefaultTexturePath + filepath ).c_str() ) ){
			sFileName = g_sDefaultTexturePath + filepath ;
		}else{
			wstring msgtxt = L"�e�N�X�`���t�@�C����������܂���ł����B\nTextureManager::Texture::Texture()\n";
			msgtxt += sFileName  ;
			msgtxt += L"  or  "  ;
			msgtxt += g_sDefaultTexturePath + filepath ;

            // ���������s
			::MessageBox(NULL,msgtxt.c_str(),L"�G���[",MB_OK);
		}
		if(FAILED(D3DXCreateTextureFromFile(pD3DDevice,sFileName.c_str(),&m_pTexture))){
			wstring msgtxt = L"�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B\nTextureManager::Texture::Texture()\n";
			msgtxt += sFileName  ;
			msgtxt += L"  or  "  ;
			msgtxt += g_sDefaultTexturePath + filepath ;
			::MessageBox(NULL,msgtxt.c_str(),L"�G���[",MB_OK);
		}
	}
	catch(wiz::BaseException& e){
        SafeRelease(m_pTexture);
        //�ăX���[
        throw BaseException(
				e.what_w(), 
                L"��TextureManager::Texture::Texture()"
                );
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pTexture);
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �p�r       �FTextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format,
////            �F    D3DPOOL Pool, DWORD Filter,DWORD MipFilter, D3DCOLOR ColorKey,
////            �F    D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FExLoad
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	 // �f�o�C�X
////            �F  const wchar_t *filepath			 // �t�@�C���p�X
////            �F  UINT Width						 // �摜�̕�(0�ŃI���W�i��)
////            �F  UINT Height						 // �摜�̍���(0�ŃI���W�i��)
////            �F  UINT MipLevels					 // �~�b�v���x��(�ʏ�0)
////            �F  DWORD Usage						 // �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
////            �F  D3DFORMAT Format				 // �F�̃t�H�[�}�b�g
////            �F  D3DPOOL Pool					 // �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
////            �F  DWORD Filter					 // �t�B���^�[(������Ȃ��Ă�k)
////            �F  DWORD MipFilter					 // �~�b�v�t�B���^�[(������Ȃ��Ă�k)
////            �F  D3DCOLOR ColorKey				 // �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
////            �F  D3DXIMAGE_INFO *pSrcInfo		 // �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
////            �F  PALETTEENTRY *pPalette			 // �p���b�g
////            �F  const wchar_t *texturename = L"" // �e�N�X�`����(�I�v�V����)
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
    DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename )
:m_pTexture(0)
,m_strFilePath(filepath)
,m_strTexName(texturename)
{
	try{
		 
		//�e�N�X�`���̍쐬
		if(FAILED(D3DXCreateTextureFromFileEx(
				pD3DDevice,			// �f�o�C�X
				filepath,			// �t�@�C����
				Width,				// �摜�̕�(0�ŃI���W�i��)
				Height,				// �摜�̍���(0�ŃI���W�i��)
				MipLevels,			// �~�b�v���x��(�ʏ�0)
				Usage,				// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
				Format,				// �F�̃t�H�[�}�b�g
				Pool,				// �f�[�^�̓ǂݍ��ݐ�(������Ȃ��Ă�k)
				Filter,				// �t�B���^�[(������Ȃ��Ă�k)
				MipFilter,			// �~�b�v�t�B���^�[(������Ȃ��Ă�k)
				ColorKey,			// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
				pSrcInfo,			// �yD3DXIMAGE_INFO�\���́z�摜�f�[�^�̍\���y�s�N�Z���T�C�Y�Ƃ��z
				pPalette,			// �p���b�g
				&m_pTexture			// �e�N�X�`����
			))){
            // ���������s
			::MessageBox(NULL,L"�e�N�X�`���ǂݍ��݂Ɏ��s���܂����B\nTextureManager::Texture::Texture()",L"�G���[",MB_OK);
		}
	}
	catch(wiz::BaseException& e){
        SafeRelease(m_pTexture);
        //�ăX���[
        throw BaseException(
				e.what_w(), 
                L"��TextureManager::Texture::Texture()   (EX"
                );
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pTexture);
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �p�r       �FTextureManager::Texture::~Texture()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�j��������
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
TextureManager::Texture::~Texture(){
	if( this && m_pTexture){
		Debugger::DBGWRITINGLOGTEXT::addStr( L"TextureManager::Texture::~Texture(0x%X)  >>>  m_strFilePath( 0x%X ) = %s\n", this,m_pTexture , m_strFilePath.c_str() );
	    //��n��
		int ret = SafeRelease(m_pTexture);
		Debugger::DBGWRITINGLOGTEXT::addStr( L"TextureManager::Texture::~Texture(0x%X)  >>>  %d \n", this,ret );
	}else{
		Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"TextureManager::Texture::~Texture �� this ���ʂ�ۂ�!�Ă܂��");
	}
}

bool TextureManager::Texture::checkTextureName( wstring name ) const{
	return  (m_strTexName != L"" ) && (m_strTexName == name);
}

bool TextureManager::Texture::checkFilePath( wstring filepath ) const{
	return ( _wcsicmp(m_strFilePath.c_str(),filepath.c_str()) == 0 );
}
}