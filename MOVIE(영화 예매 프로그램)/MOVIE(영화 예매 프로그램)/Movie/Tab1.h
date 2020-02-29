#pragma once
class CDlgReservetion;
class CDlgRank;
class CChatClient;

// CTab1 대화 상자

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CDlgReservetion *dlg;		// 영화 예매 클래스
	CDlgRank *dlg1;				// 인기 순위 클래스
	CTabCtrl m_tab1;			// 위 2개의 탭의 다이얼로그를 담을 탭
	afx_msg void OnClickedButton4();	// 영화 리뷰 웹 사이트로 넘어갈 수 있게 해주는 버튼의 함수
	afx_msg void OnClickedButton2();	// 상담원과 채팅을 할 수 있는 창을 띄워주는 함수
};
