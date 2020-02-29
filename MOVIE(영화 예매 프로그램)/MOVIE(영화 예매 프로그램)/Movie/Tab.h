#pragma once
class CDlgRegistration;
class CDlgManagement;
class CDlgImportation;
// CTab 대화 상자

class CTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTab)

public:
	CTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CDlgRegistration *dlg;		// 영화 등록 클래스
	CDlgManagement *dlg1;		// 회원 관리 클래스
	CDlgImportation *dlg2;		// 영화 수익 클래스
	CTabCtrl m_tab;				// 위 3개의 탭의 다이얼로그를 담을 탭
};
