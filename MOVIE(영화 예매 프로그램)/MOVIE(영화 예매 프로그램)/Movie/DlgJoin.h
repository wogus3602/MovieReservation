#pragma once


// CDlgJoin 대화 상자

class CDlgJoin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgJoin)

public:
	CDlgJoin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgJoin();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_JOIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL SetAddData();
	CString m_strID;	//회원 아이디를 저장하는 변수
	CString m_strPassword;	//회원 비밀번호를 저장하는 변수
	CString m_strName;	//회원 이름을 저장하는 변수
	CString m_strPhonenumber;	//회원 번호를 저장하는 변수
	CString m_strEmail;	//회원 이메일아이디를 저장하는 변수
	CString m_strEmail1 = "naver.com"; //도메인을 저장하는 변수
	virtual void OnOK();	//회원가입 버튼을 눌렀을때 데이터를 데이터베이스에 저장하는 버튼
	CString m_strPassword2;//회원 비밀번호확인   비밀번호 변수랑 비교해 잘 적었는지 확인하는 변수

	CComboBox m_emailform; //이메일 도메인을 나타내는 콤보상자
	void SetComboItem();	//콤보상자내 정보를 저장하는 함수
	virtual BOOL OnInitDialog();//SetComboItem() 과 m_edemail를 숨기는 함수
	afx_msg void OnSelchangeComboEmail(); // 콤보상자를 변경했을때 m_emailform에 도메인을 저장하는 함수
	CEdit m_edemail;//콤보상자에서 직접입력을 선택했을때 도메인을 입력하는칸
};
