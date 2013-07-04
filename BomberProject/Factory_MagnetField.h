////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_MagnetField.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�g�n ��m
//	����			�F�{�� ���V
//	�����ް��Ɣ��l	�F���E�͈͂̉���Object
//					��
//	namespace wiz;
//		class Factory_MagnetField ;
//
#pragma once
#include "Factory_Magnetic.h"

namespace wiz{
namespace bomberobject{

extern class MagneticGage_N;
extern class MagneticGage_S;


class MagnetFieldCircle{
	struct Vertex
	{
		D3DXVECTOR3 vPos ;
		DWORD dwColor ;

		Vertex(): vPos( 0.0f, 0.0f, 0.0f ), dwColor( 0xFFFFFFFF ){ }
		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor ): vPos( i_vPos ), dwColor( i_dwColor ){	}
		static size_t getSize()	{	return sizeof( Vertex );	}
		static DWORD getFVF(){return D3DFVF_XYZ | D3DFVF_DIFFUSE ;}
	};
	static DWORD						m_dwMyInstance	;
	static LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer	;	//�o�b�t�@
	static DWORD						m_dwVertexQty	;
	D3DXMATRIX					m_mMatrix		;
	DWORD						m_dwColor_N		;
	DWORD						m_dwColor_S		;

public:
	MagnetFieldCircle(LPDIRECT3DDEVICE9 pD3DDevice );
	~MagnetFieldCircle();
	void Draw(DrawPacket& i_DrawPacket);
	void setMatrix(D3DXMATRIX& i_mMatrix){
		m_mMatrix = i_mMatrix;
	}
	void setPole(POLE pl){
		Vertex* m_pVertex;
		m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	


		if( pl == POLE_S ){
			m_pVertex[ 0 ].dwColor = m_dwColor_S;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = m_dwColor_S;
			}
		}else{
			m_pVertex[ 0 ].dwColor = m_dwColor_N;
			for ( DWORD i = 1 ; i <= m_dwVertexQty  ; i++ ){
				m_pVertex[ i ].dwColor = m_dwColor_N;
			}
		
		}
		m_pVertexBuffer->Unlock();
	}

	void	setColor( POLE pl, DWORD i_dwColor){
		if( pl == POLE_S ){
			m_dwColor_S	= i_dwColor;
		}else{		
			m_dwColor_N	= i_dwColor;
		}
	}

	void	ResetColor(){
		m_dwColor_S	= 0x3F0000FF;
		m_dwColor_N	= 0x3FFF0000;
	}
};

//3D�ϊ��p
//**************************************************************************//
// class MagnetField : public PrimitiveCylinder ;
//
// �S����  : �g�n ��m
// �ҏW    : ���� �O(�啝����)
//         : �{�� ���V
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
extern class PlayerCoil ;
class MagnetField : public Object, public MagneticObject{

//////////
//	: �v���e�N�g
protected:
	Camera*				m_pCamera			;
	PlayerCoil*			m_pCoil				;
	MagneticGage_N*		m_pPole_N			;
	MagneticGage_S*		m_pPole_S			;
	MagnetFieldCircle	m_MagneticField		;
	D3DXVECTOR3			m_vPos				;
	float				m_fEffectSizeRate	;
	bool				m_bPtn				;
	int					m_iFlashingInterval	;

protected:


//////////
//	: ���J
public:
	/////////////////// ////////////////////
	//// �p�r       �FMagnetField(
	///										LPDIRECT3DDEVICE9 pD3DDevice,
	///										LPDIRECT3DTEXTURE9 pTexture,
	///										wiz::OBJID id = OBJID_3D_MAGNET
	///										) ;
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////	
	MagnetField(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wiz::OBJID id 
		) ;



	/////////////////// ////////////////////
	//// �p�r       �F  ~MagnetField()
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FPlayer�p�̃R���X�g���N�^
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////	
	~MagnetField();

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			 �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////             �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////             �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////             �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////              �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////              �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////              �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	void Update( UpdatePacket& i_UpdatePacket );


	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���S���W���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getPos() const {
		return m_vPos			;	
	}	;

	void HitTest();

	/////////////////// ////////////////////
	//// �֐���     �Fmultimap<float, Magnet3DItem*> getMapTarget() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �Fm_ItemMap_Target���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �Fm_ItemMap_Target
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	//multimap<float, Magnet3DItem*> getMapTarget() const{
	//	return m_ItemMap_Target;
	//}
	void	Flashing( UpdatePacket& i_UpdatePacket, POLE i_Pole );
	void	Reset(){
		m_MagneticField.ResetColor();
	}
};

class StaticMagnetField : public MagnetField {
protected:
	struct Magnet3DItem{
		//	: ���W
		D3DXVECTOR3		m_vPos ;
		POLE			m_bMagnetPole ;
		float			m_fMapKey	;
		bool			m_bHidden	;
		virtual ~Magnet3DItem(){}
	};


	//map<�I�u�W�F�N�g�̃|�W�V����, Magnet3DItem>
	typedef multimap<float, Magnet3DItem*>	ALLCONTAINER		;
	typedef list<Magnet3DItem*>				TARGETCONTAINER		;
	ALLCONTAINER		m_ItemMap_All		;
	TARGETCONTAINER		m_ItemMap_Target	;


public:
	StaticMagnetField(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wiz::OBJID id 
	);
	~StaticMagnetField();
	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////              �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////              �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////              �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			 �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////             �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////             �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////             �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void Draw( DrawPacket& i_DrawPacket );
	/////////////////// ////////////////////
	//// �p�r       �Fvoid AddMagnetic( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�}�O�l�b�g�̒ǉ�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////		    �F  D3DXVECTOR3 &vScale				//�g��k��
	////		    �F  D3DXVECTOR3 &vRot				//��]�p
	////		    �F  D3DXVECTOR3 &vPos				//�ʒu
	////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void AddMagnetic(
		D3DXVECTOR3 &vPos,
		POLE		vPole,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
	) ;
	
	/////////////////// ////////////////////
	//// �p�r       �Fbool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�����𔻒�
	//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
	////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
	//// �ߒl       �Ftrue , false
	//// �S����     �F�{�����V
	//// ���l       �F
	//bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const;
	
	void setDrawTarget();

	void HitTest();
};

/**************************************************************************
 class Factory_MagnetField;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_MagnetField{
public:
/**************************************************************************
 Factory_MagnetField(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	//Factory_MagnetField(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_MagnetField( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~Factory_MagnetField() ;
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
