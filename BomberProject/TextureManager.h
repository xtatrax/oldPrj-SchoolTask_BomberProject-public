////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FTextureManager.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�e�N�X�`���[�̊Ǘ�
//					��
//	namespace wiz;
//		class TextureManager;
//		class TextureManager::Texture;
//
#pragma once
namespace wiz {

//**************************************************************************
// class TextureManager;
//
// �S����  : ���� �O
// �p�r    : �e�N�X�`���Ǘ��N���X
//         : ����f�[�^�̑��d�����y�у����[�X�R��̖����悤��
//         : �e�N�X�`���[���Ǘ��ł��܂�
//**************************************************************************
class TextureManager{
	class Texture;
	vector< Texture* > m_vecTextures;
public:
/////////////////// ////////////////////
//// �p�r       �FTextureManager()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	TextureManager();
/////////////////// ////////////////////
//// �p�r       �F~TextureManager()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�j��������
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual ~TextureManager();
/////////////////// ////////////////////
//// �p�r       �FRelease()
//// �J�e�S��   �F�֐�
//// �p�r       �F�S�e�N�X�`���[�̔j��
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void Release();
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
////            �F  	const wchar_t *filepath, const wchar_t *texturename )
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`���[�̓ǂݍ���
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	// �f�o�C�X
////            �F  const wchar_t *filepath			// �t�@�C���p�X
////            �F  const wchar_t *texturename		// �e�N�X�`���� ( �I�v�V���� )
//// �ߒl       �F�������ꂽ�e�N�X�`���܂��͓���f�[�^�̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	LPDIRECT3DTEXTURE9 addTexture(LPDIRECT3DDEVICE9 pD3DDevice,
		const wchar_t* filepath,const wchar_t* texturename = L"");
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
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
//// �ߒl       �F�������ꂽ�e�N�X�`���܂��͓���f�[�^�̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	LPDIRECT3DTEXTURE9 addTextureEx(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
		UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
		DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F  	DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename )
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`���[�̓ǂݍ���
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice	// �f�o�C�X
////            �F  const wchar_t *filepath			// �t�@�C���p�X
////            �F  DWORD Usage						// �����_�����O�^�[�Q�b�g�Ɏw�肷��Ƃ��Ƃ��Ɏw��(�ʏ�0)
////            �F  D3DFORMAT Format				// �F�̃t�H�[�}�b�g
////            �F  D3DCOLOR ColorKey				// �y������z�F�𓧉ߐF�Ƃ���y0�Ŗ����z
////            �F  const wchar_t *texturename		// �e�N�X�`����(�I�v�V����)
//// �ߒl       �F�������ꂽ�e�N�X�`���܂��͓���f�[�^�̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	LPDIRECT3DTEXTURE9 addTextureExLight(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
		DWORD Usage, D3DFORMAT Format, D3DCOLOR ColorKey,  const wchar_t* texturename = L"" );
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureSearchFromName(const wchar_t* filename)
//// �J�e�S��   �F�֐�
//// �p�r       �F�e�N�X�`��������ǂݍ��ݍς݂̃e�N�X�`���[������
//// ����       �F  const wchar_t* filename		// ��������t�@�C����
//// �ߒl       �F���������e�N�X�`���̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	LPDIRECT3DTEXTURE9 TextureSearchFromName(const wchar_t* filename) ;
/////////////////// ////////////////////
//// �p�r       �FLPDIRECT3DTEXTURE9 TextureSearchFromFilePath(const wchar_t* path)
//// �J�e�S��   �F�֐�
//// �p�r       �F�t�@�C���p�X����ǂݍ��ݍς݂̃e�N�X�`���[������
//// ����       �F  const wchar_t* path		// ��������t�@�C����
//// �ߒl       �F���������e�N�X�`���̃|�C���^��Ԃ� ( LPDIRECT3DTEXTURE9�^ )
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	LPDIRECT3DTEXTURE9 TextureSearchFromFilePath(const wchar_t* path) ;


};//�yEND�zTextureManager

//**************************************************************************
// class TextureManager::Texture;
//
// �S����  : ���� �O
// �p�r    : 
//**************************************************************************
class TextureManager::Texture{
	
	LPDIRECT3DTEXTURE9	m_pTexture     ;
	wstring				m_strTexName   ;
	wstring				m_strFilePath  ;

public:
/////////////////// ////////////////////
//// �p�r       �FTexture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
////            �F    const wchar_t* texturename = L"")
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		// ��������t�@�C����
////            �F  const wchar_t* filepath             // 
////            �F  const wchar_t* texturename = L""    // 
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,const wchar_t* texturename = L"");
/**************************************************************************
 Texture::Texture(
	LPDIRECT3DDEVICE9 i_pD3DDev,	//DirectX�f�o�C�X
	const wchar_t* filename	//�e�N�X�`���̃t�@�C����
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
TextureManager::Texture::Texture(LPDIRECT3DDEVICE9 pD3DDevice,const wchar_t* filepath,
    UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter,
    DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, const wchar_t* texturename = L"" );

/**************************************************************************
 ~Texture();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Texture();
/**************************************************************************
 const LPDIRECT3DTEXTURE9 getTexture() const
 �p�r: �A�N�Z�b�T
 �߂�l: �Ȃ�
***************************************************************************/
	const LPDIRECT3DTEXTURE9 getTexture() const{
		return m_pTexture;
	}
	bool	checkTextureName( wstring name ) const;
	bool	checkFilePath(    wstring path ) const;
};//�yEND�zTexture

}