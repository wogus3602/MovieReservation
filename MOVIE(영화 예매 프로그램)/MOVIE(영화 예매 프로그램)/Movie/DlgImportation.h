#pragma once


// CDlgImportation 대화 상자

class CDlgImportation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImportation)

public:
	CDlgImportation(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImportation();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORTATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void OnClickedButton7(); //검색버튼을 눌렀을때 실행하는 함수
	void SetSearchResult(const CString& strSQL); //원하는 결과를 검색해 ControlList에 출력
	CListCtrl m_MemberList; //데이터베이스정보를 출력하는 리스트
	virtual BOOL OnInitDialog();//
	CString m_strSearch; //EditControl에 작성한 내용을 저장하는 변수
};
