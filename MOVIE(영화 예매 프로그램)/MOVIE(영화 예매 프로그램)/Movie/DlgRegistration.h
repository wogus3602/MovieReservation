#pragma once


// CDlgRegistration 대화 상자

class CDlgRegistration : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRegistration)

public:
	CDlgRegistration(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgRegistration();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetAddData(); //쿼리문을 통해 데이터베이스에 정보를 넘겨주는 함수
	CString	m_strSearch;
	CString m_strMovieName;	//EditControl에 저장된 영화제목을 저장할 변수
	CString m_strMovieTime; //영화시간을 저장할 변수
	CString m_strMovieValue; // 영화가격을 저장할 변수
	afx_msg void OnClickedButton7(); //등록버튼을 눌렀을때 데이터베이스에 EditControl 적힌 내용을 저장
	CListCtrl m_list1; // 데이터베이스에서 가져온 정보를 출력하는 리스트
	virtual BOOL OnInitDialog();
	void SetSearchResult(); //쿼리문을 통해 데이터베이스에 정보를 검새해주는 함수
};
