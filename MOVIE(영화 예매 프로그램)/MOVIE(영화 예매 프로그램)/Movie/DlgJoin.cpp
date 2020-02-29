// DlgJoin.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgJoin.h"
#include "afxdialogex.h"


// CDlgJoin 대화 상자

IMPLEMENT_DYNAMIC(CDlgJoin, CDialogEx)

CDlgJoin::CDlgJoin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_JOIN, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
	, m_strName(_T(""))
	, m_strPhonenumber(_T(""))
	, m_strEmail(_T(""))
	, m_strPassword2(_T(""))
{

}

CDlgJoin::~CDlgJoin()
{
}

void CDlgJoin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strID);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
	DDX_Text(pDX, IDC_EDIT4, m_strName);
	DDX_Text(pDX, IDC_EDIT5, m_strPhonenumber);
	DDX_Text(pDX, IDC_EDIT6, m_strEmail);
	//  DDX_Control(pDX, IDC_EDIT3, m_strPassword2);
	DDX_Text(pDX, IDC_EDIT3, m_strPassword2);
	//  DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_COMBO_EMAIL, m_emailform);
	DDX_Control(pDX, IDC_EDIT_EMAIL, m_edemail);
}


BEGIN_MESSAGE_MAP(CDlgJoin, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_EMAIL, &CDlgJoin::OnSelchangeComboEmail)
END_MESSAGE_MAP()


// CDlgJoin 메시지 처리기


BOOL CDlgJoin::SetAddData()
{
	UpdateData(TRUE);

	TRY
	{
		CString strSQL;
		m_strEmail1 = m_strEmail + "@" + m_strEmail1; // "이메일아이디 @ 도메인" 을 나타낸다

		strSQL.Format(_T("INSERT INTO [MEMBER] VALUES('%s', '%s', '%s', '%s', '%s')"),  m_strID, m_strPassword, m_strName, m_strPhonenumber,m_strEmail1);

		//만약 비밀번호가 다를시 메세지를 띄우고 return을 해준다.
		if (m_strPassword != m_strPassword2)
		{
			AfxMessageBox(_T("비밀번호확인을 정확히 입력해주세요."));
			return FALSE;
		}

		//strSQL에 저장한 쿼리를 데이터베이스에 보내준다.
		g_dbMember.ExecuteSQL(strSQL);
		return TRUE;
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		return TRUE;
	}
	END_CATCH
}


void CDlgJoin::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (!SetAddData()) {

	}
	else
		CDialogEx::OnOK();
}



void CDlgJoin::SetComboItem()
{
	//콤보상자에 도메인을 입력
	m_emailform.AddString(_T("naver.com"));
	m_emailform.AddString(_T("duam.net"));
	m_emailform.AddString(_T("hanmail.net"));
	m_emailform.AddString(_T("nate.com"));
	m_emailform.AddString(_T("gmail.com"));
	m_emailform.AddString(_T("hotmail.com"));
	m_emailform.AddString(_T("직접 입력"));


	m_emailform.SetCurSel(0);
	// TODO: 여기에 구현 코드 추가.
}


BOOL CDlgJoin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetComboItem();	//콤보상자에 도메인 정보 입력
	m_edemail.ShowWindow(FALSE); //처음에는 직접입력칸을 숨겨준다.
	return TRUE;
}


void CDlgJoin::OnSelchangeComboEmail()
{
	CString mm; //콤보상자에서 선택된 내용을 저장하는 변수


	int index = m_emailform.GetCurSel();  //콤보상자내에서 몇번째 선택했는지 index에 저장해준다.
	m_emailform.GetLBText(index, m_strEmail1); //콤보상자에서 index번째 내용을 m_strEmail1에 저장
											// SetAddData() 함수에서 쓰기위해 저장을 해준다.	


	m_emailform.GetLBText(index, mm); //콤보상자에서 index번째 내용을 mm에 저장
									//밑 if문에서 사용하기 위해 저장을 해준다.

	if (mm == "직접 입력") { // TRUE면 EditControl창을 띄우고 콤보상자를 오른쪽으로 배치해준다.
		m_edemail.ShowWindow(TRUE);
		m_emailform.SetWindowPos(NULL, 520, 278, 0, 0, SWP_NOSIZE);
	}
	else {	//아니면 다시 원위치로 바꿔준다.
		m_emailform.SetWindowPos(NULL, 332, 278, 0, 0, SWP_NOSIZE);
		m_edemail.ShowWindow(FALSE);
	}
}
