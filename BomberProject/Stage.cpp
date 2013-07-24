////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�X�e�[�W
//					�F�X�e�[�W�̓V�[������Ă΂�܂�
//					��
//	namespace wiz;
//		class StageLoader ;
//		class Stage ;
//		class MenuStage : public Stage ;
//
#include "StdAfx.h"
#include "Stage.h"
#include "BassItems.h"
#include "TL-String.h"
#include "Factory_Wall.h"
#include "Factory_Item.h"
#include "Factory_Magnetic.h"
#include "Object.h"



namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 Stage ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �Fvoid Stage::Clear()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Stage::Clear(){
	//SafeDelete(m_pChildStage);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"Stage::Clear  >  %X �폜�J�n\n",this);
    
    //  : �e�X�e�[�W���폜(���ƂŎq�X�e�[�W�ɏC������)
	SafeDelete(m_pParStage);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDelete(m_pParStage) ����\n");
    

	//  : ���ō��ꂽ���̂������Ă��������Ȃ̂łʂ��!
	m_pSound = NULL ;
    //  : �����p�̃T�E���h���폜
	SafeDelete(m_pMySound);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDelete(m_pMySound)  ����\n");


	//	: �{�^���̎��̂�m_Vec�̒��ɂ��邽��Clear�̂�
	m_ButtonVec.clear();
	////Debugger::DBGWRITINGLOGTEXT::addStr(L"m_ButtonVec.clear(); ����\n");
    
	//  : �X�e�[�W�ɔz�u���ꂽ�I�u�W�F�N�g�����ׂč폜
	SafeDeletePointerContainer(m_Vec);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(m_Vec);  ����\n");
	//SefeDeletePointerVector(m_Vec);


	//m_TexMgr.Release();
	////Debugger::DBGWRITINGLOGTEXT::addStr(L"m_TexMgr.Release(); ����\n",this);
}

/////////////////// ////////////////////
//// �p�r       �FStage::Stage(Stage* Par)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F��������
//// ����       �FStage*		Par		//	: �e�X�e�[�W�ւ̃|�C���^
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Stage::Stage(Stage* Par)
:m_pParStage(Par),m_pChildStage(0),m_IsDialog(true)
,m_bUpdate( true )
,m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false)
,m_pMySound( NULL ),m_pSound( NULL )
,m_fActiveTime( 0 )
,m_dwFirstClock( 0 )
#if defined(ON_DEBUGGINGPROCESS)
,m_bSlow(false)
#endif
/////////////////// ////////////////////
{
	m_pParStage && (m_pParStage->m_pChildStage = this) ;
}
/**************************************************************************
virtual Stage::~Stage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Stage::~Stage(){
	Clear();
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void ButtonUpdateUpdate( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�{�^�����X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Stage::ButtonUpdate(UpdatePacket& i_UpdatePacket)
{
	CONTROLER_STATE	ControllerState1P = i_UpdatePacket.m_pCntlState[0];
    if(!m_SelectLock){

		DWORD dwSM = 0;
		if((dwSM = Button::getMouseSelectIndex()) != ULONG_MAX)
			m_SelectIndex = dwSM;

		//	: ���̃{�^����
		if(ControllerState1P.Gamepad.wPressedButtons.XConState.DOWN 
			|| ControllerState1P.Gamepad.sThumbLY < 0)
		{
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: �O�̃{�^����
		if(ControllerState1P.Gamepad.wPressedButtons.XConState.UP
			|| ControllerState1P.Gamepad.sThumbLY > 0)
		{
			if(m_SelectIndex == 0){
				m_SelectIndex = (m_ButtonVec.size() - 1);
			}
			else{
				m_SelectIndex--;
			}
			m_SelectLock = true;
		}


		//�I����Ԃ̐ݒ�
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//�I�������肳�ꂽ
		if(		ControllerState1P.Gamepad.wPressedButtons.XConState.A
			&&	!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setPressed();
			m_SelectLock = true;
		}


		Debugger::DBGSTR::addStr(L"Button::getMouseSelectIndex() %d\n",dwSM);
		if(	Cursor2D::clickLButtonWithLock() ){
			Debugger::DBGSTR::addStr(L"�N���b�N\n");
			if(	dwSM != ULONG_MAX ){
				if(	!m_ButtonVec.empty() )
				{
					if( m_SelectIndex >= m_ButtonVec.size() ){
						OutputDebugString( L"Stage::ButtonUpdate�Ŗ�����INDEX���Q�Ƃ���܂����B\n" );
						return ;
					}

					m_ButtonVec[m_SelectIndex]->setPressed();
					m_SelectLock = true;
				}
			}
		}
	}
	if( !(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		&&
		ControllerState1P.Gamepad.sThumbLY == 0
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		&& 
		!m_IsAnimetion
		){
		m_SelectLock = false;
	}

}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Stage::Update(UpdatePacket& i_UpdatePacket)
{

	if( m_dwFirstClock == 0 ) m_dwFirstClock = Tempus::getClock() ;

	m_fActiveTime = Tempus::TwoDwTime2ElapsedTime(m_dwFirstClock,Tempus::getClock()) ;

	i_UpdatePacket.GetTime()->setStageActiveTime(m_fActiveTime);
	//	: ������Sound���o�^����Ă��邩���m�F
	//if( !m_pSound )	m_pSound = (Sound*)SearchObjectFromID( &this->m_Vec,OBJID_SYS_SOUND );
	if( !m_pSound ){
		//	: �g����T�E���h�̓o�^���Ȃ�
		if( m_pMySound ){
			//	: �����̃T�E���h�������Ă���
			m_pSound = m_pMySound ;
			//	: �����̃T�E���h��o�^
		}else{
			//	: �����̃T�E���h���Ȃ�
			if( m_pParStage && m_pParStage->m_pSound ){
				//	: �e���T�E���h�������Ă���
				m_pSound = m_pParStage->m_pSound ;
			}
		}
	}

	i_UpdatePacket.SetStage( this );

#if defined(ON_DEBUGGINGPROCESS)
	float fElapsedTime = (float)i_UpdatePacket.GetTime()->getElapsedTime();
	if(GetAsyncKeyState( MYVK_DEBUG_STOP_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime ;
		if(m_bUpdate){
			if(s_fTime > 0.05f){
				m_bUpdate = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bUpdate = true ;
				s_fTime   = 0 ;
			}
		}
	}
	static float fSlowAccumulator = 0;
	if(GetAsyncKeyState( MYVK_DEBUG_SLOW_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime;
		if(m_bSlow){
			if(s_fTime > 0.05f){
				m_bSlow = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bSlow = true ;
				s_fTime   = 0 ;
			}
		}
	}
	if( m_bSlow && (fSlowAccumulator += fElapsedTime) < 1.0f ){
		return;
	}
	fSlowAccumulator = 0 ;
#endif

	if(m_bUpdate){
		ButtonUpdate(i_UpdatePacket);
		//clock_t sc = TLIB::Tempus::getClock();
		//�z�u�I�u�W�F�N�g�̕`��
		vector<Object*>::iterator it = m_Vec.begin();
		while( it != m_Vec.end() ){
			if(!(*it)->getDead()){
				(*it)->AccessBegin();
				(*it)->Update(i_UpdatePacket) ;
				(*it)->AccessEnd();
			} else {
				//EraseButton( it );
				SAFE_DELETE( (*it) )	;
				it = m_Vec.erase( it )	;
				continue;
			}
			it++;
		}
		//clock_t nc = TLIB::Tempus::getClock();
		//Debugger::DBGSTR::addStr( L" Update���� : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));
	}
}
/**************************************************************************
 void AddButton(
 Button* pButton	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
 �߂�l: �Ȃ�
***************************************************************************/
void Stage::EraseButton(vector<Object*>::iterator ObjIt){
	if( (*ObjIt)->getButtonP() ){
		Button		*pTargetButton	= (*ObjIt)->getButtonP(),
					*pNowButton		= NULL;

		DWORD dwIndex = 0;
		vector<Button*>::iterator	it  = m_ButtonVec.begin(),
									end = m_ButtonVec.end();

		//	: �T�[�`���[�v
		while( it != end ){
			pNowButton = (*it);
			if( pTargetButton == pNowButton ){
				it = m_ButtonVec.erase( it );
				//	: �ԍ��l�߃��[�v
				while( it != end ){
					(*it)->setIndex(dwIndex);
					dwIndex++;
					it++;
				}
				break;
			}
			dwIndex++;
			it++;
		}
	}
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Render(RenderPacket& i_RenderPacket);
//// �J�e�S��   �F�֐�
//// �p�r       �F�^�[�Q�b�g�����_�����O
//// ����       �F  RenderPacket& i_RenderPacket        // �����_�[�����ɗ����f�[�^�̏W����
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
////            �F
////
void Stage::Render(RenderPacket& i_RenderPacket){

	i_RenderPacket.SetStage( this );

	//clock_t sc = TLIB::Tempus::getClock();
	//�z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::iterator it = m_Vec.begin();
	while( it != m_Vec.end() ){
		if(!(*it)->getDead()){
			(*it)->AccessBegin();
			(*it)->TargetRender(i_RenderPacket);
			(*it)->AccessEnd();
		}
		it++;
	}
	//clock_t nc = TLIB::Tempus::getClock();
	//Debugger::DBGSTR::addStr( L" Render���� : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));

}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Stage::Draw(DrawPacket& i_DrawPacket)
{
	try{

		i_DrawPacket.SetStage( this );

		//clock_t sc = TLIB::Tempus::getClock();
		//�z�u�I�u�W�F�N�g�̕`��
		vector<Object*>::size_type sz = m_Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			m_Vec[i]->AccessBegin();
			m_Vec[i]->Draw(i_DrawPacket);
			m_Vec[i]->AccessEnd();
		}
		CommandTranslator(i_DrawPacket);
		//clock_t nc = TLIB::Tempus::getClock();
		//Debugger::DBGSTR::addStr( L"   Draw���� : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));
	}
	catch(exception& e){
        throw e;
	}
    catch(...){
        throw;
    }
}
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
void Stage::TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget){

}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
void Stage::DefaultRender(){

}
/////////////////// ////////////////////
//// �֐���     �Fvoid CommandTranslator(DrawPacket& i_DrawPacket);
//// �J�e�S��   �F�֐�
//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
//// ����       �F  DrawPacket& i_DrawPacket                       // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.GetTime()  // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Stage::CommandTranslator(DrawPacket& i_DrawPacket){
	switch(i_DrawPacket.PopCommand().m_Command){
		case GM_CHANGE_CHILDSTAGE:
		{
			if( m_pChildStage )
				m_pChildStage->m_IsDialog = false ;
			break ;
		}
		case GM_CHANGE_PARENTSTAGE:
		{
			m_IsDialog = true ;
			break ;
		}
	}
};
void Stage::AddButton(wiz::Object* pButton){
	Button* pb = pButton->getButtonP();
	pb->setIndex(m_ButtonVec.size());
	m_ButtonVec.push_back( pb );
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





/**************************************************************************
 MenuStage ��`��
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par){
	m_pChildStage = 0;
	try{
        // ���C�e�B���O���[�h
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //���C�g�̃C���X�^���X������
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        m_Vec.push_back(
			new DirectionalLight(
				pD3DDevice,
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3(0.4f, -1.0f, 0.4f)
			)
		);
        //�J�����̃C���X�^���X������
        m_Vec.push_back(
			new Camera(
				pD3DDevice,
				D3DXVECTOR3( 0.0f, 2.0f, -30.0f),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				1.0f,
				100.0f,
				60.0f
			)
		);

	}
	catch(...){
		//�e�N���X��Clear()���Ă�
		Clear();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MenuStage::~MenuStage(){
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MenuStage::Update(UpdatePacket& i_UpdatePacket)
{
	Stage::Update(i_UpdatePacket);
}


/**************************************************************************
 void MenuStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MenuStage::Draw(DrawPacket& i_DrawPacket){
	Stage::Draw(i_DrawPacket);
}

}
//end of namespace wiz.
