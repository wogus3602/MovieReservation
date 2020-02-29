#pragma once


// CChatClient 대화 상자

class CChatClient : public CDialog
{
	DECLARE_DYNAMIC(CChatClient)

public:
	CChatClient(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChatClient();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COUNSELLING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam); //서버쪽에서 Send를 했을때 응답하는 함수
public:
	afx_msg void OnBnClickedCancel(); //채팅창을 나가기 눌렀을때 서버에 "EXIT" 를 보내주는 함수
	afx_msg void OnClickedButtonSend();//서버쪽에 내용을 전달하는 함수
	CString m_strSend; //EditControl에 적은 내용을 저장하는 변수
	CString m_count; //상담원 오른쪽하단에 대기자를 저장하는 변수
	CListCtrl m_wait; // 대기자 이름 나타나는곳
	CListBox m_list; //대기자 이름을 나타내려고 했으나 구현하지 못했다.
	CSocCom m_socCom;
	BOOL TF = FALSE; //TRUE이면 다음 차례 대기자에게 연결되었다고 메세지를 보내준다.

	virtual BOOL OnInitDialog();
};
