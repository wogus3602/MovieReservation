#pragma once
class CSocCom : public CSocket
{
	HWND m_hWnd;
public:
	CSocCom();
	~CSocCom();
	virtual void OnReceive(int nErrorCode);
	void Init(HWND hWnd);
};

