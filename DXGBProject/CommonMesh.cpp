/**************************************************************************
 CommonMesh.h

****************************************************************************/

#include "StdAfx.h"
#include "CommonMesh.h"
namespace wiz{

/**************************************************************************
 CommonMesh ��`��
***************************************************************************/
/**************************************************************************
 CommonMesh(
    D3DXVECTOR3 pos,                //�ʒu
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient          //�A���r�G���g�F
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
CommonMesh::CommonMesh(D3DXVECTOR3 pos,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
:Object(),
m_pMesh(0),     //�|�C���^�͂O������
m_pShadowMesh(0),
m_Pos(pos)
{
    try{
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
        // ���f���̐F��ݒ�
        m_Material.Diffuse = Diffuse;
        m_Material.Specular = Specular;
        m_Material.Ambient = Ambient;
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 CommonMesh::~CommonMesh();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
CommonMesh::~CommonMesh(){
    //��n��
	//�h���N���X�ł�Delete/Release�Y��΍�
    SafeRelease(m_pMesh);
    SafeRelease(m_pShadowMesh);
}
/**************************************************************************
 void CommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �R�������b�V����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void CommonMesh::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    //�����`�F�b�N
    if((!m_pMesh) || (!pD3DDevice)){
        throw DxException(L"�f�o�C�X�����b�V���������ł��B",
        L"CommonMesh::Draw()");
    }
    if(m_Material.Diffuse.a < 1.0f){
        //�����A�����x��1.0�����Ȃ�
        // �A���t�@�����̐ݒ�
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    }
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //�����A�X�y�L�����[���ݒ肵�Ă�����
        // �X�y�L�����[�L���̐ݒ�
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
    }
    // �}�e���A���������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetMaterial( &m_Material);
    //�`��
    m_pMesh->DrawSubset(0);
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //�����A�X�y�L�����[���ݒ肵�Ă�����
        // �X�y�L�����[�����ɖ߂�
        pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
    }
    if(m_Material.Diffuse.a < 1.0f){
        //�����A�����x��1.0�����Ȃ�
        // �A���t�@���������ɖ߂�
        pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    }
}
}