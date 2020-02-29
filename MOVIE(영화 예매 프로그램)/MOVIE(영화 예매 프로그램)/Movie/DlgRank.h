#pragma once


// CDlgRank 대화 상자

class CDlgRank : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRank)

public:
	CDlgRank(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgRank();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	void SetSearchResult();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_RankList;			 // 영화의 정보들을 담을 리스트컨트롤
	virtual BOOL OnInitDialog();	
	CStatic m_Disaplay;				 // 영화 포스터를 나타낼 컨트롤
	afx_msg void OnClickedButton5(); // 각 영화의 사진을 처리하는 함수
	CString m_strname;				 // 영화 이름에 관한 Edit 컨트롤
	afx_msg void OnStnClickedStaticMoviepicture();
};
