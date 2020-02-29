#pragma once


// CDlgManagement 대화 상자

class CDlgManagement : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgManagement)

public:
	CDlgManagement(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgManagement();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MANAGEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	void SetSearchResult(const CString& strSQL);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_MemberList;	//회원정보를 출력하는 ControlList
	afx_msg void OnClickedButton8(); //검색버튼을 눌렀을때 회원정보를 출력한다.
	CString m_strSearch;	//검색할 회원이름을 저장할 변수
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonAll();//전체보기버튼을 눌렀을때 모든 회원정보를 출력한다.
};
