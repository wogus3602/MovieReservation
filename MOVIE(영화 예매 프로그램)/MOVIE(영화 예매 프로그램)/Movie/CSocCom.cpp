#include "stdafx.h"
#include "CSocCom.h"

CSocCom::CSocCom()
{
}


CSocCom::~CSocCom()
{
}


void CSocCom::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, UM_RECEIVE, 0, 0);

	CSocket::OnReceive(nErrorCode);
}


void CSocCom::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}
