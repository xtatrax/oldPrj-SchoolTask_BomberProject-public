////////////////////////////// //////////////////////////////
//	vWFNg	FBomberProject
//	t@C¼		FStage_Result.h
//	J­Â«		FMSVC++ 2008
//	ÅK^u		F4
//	SÒ			F²¡Á
//	àïÃÞ°ÀÆõl	FNAXe[W
//					¥
//	namespace wiz;
//		class ResultStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
namespace wiz{
/**************************/
/**************************************************************************
 class ResultStage : public Stage;
 pr: Q[Xe[WNX
****************************************************************************/
class ResultStage : public Stage{
	int	m_iTime;
public:	
/**************************************************************************
 ResultStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//foCX
	const Script::MLPHeader& Header,	//	: vC·éyÈÌwb_[f[^
	const Script::SCORELEVEL Level		//	: vC·éxíÊ
 );
 pr: RXgN^
 ßèl: Èµi¸sÍáOðthrowj
***************************************************************************/
	ResultStage(LPDIRECT3DDEVICE9 pD3DDevice, int iDeadCount, int iMaxPosY, Stage* pStage = NULL);
/**************************************************************************
ResultStage();
 pr: fXgN^
 ßèl: Èµ
***************************************************************************/
	virtual ~ResultStage();
	virtual void Update(UpdatePacket& i_UpdatePacket);
};
/**************************/

}
//end of namespace wiz.
