// DlgManagement.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgManagement.h"
#include "afxdialogex.h"


// CDlgManagement 대화 상자

IMPLEMENT_DYNAMIC(CDlgManagement, CDialogEx)

CDlgManagement::CDlgManagement(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MANAGEMENT, pParent)
	, m_strSearch(_T(""))
{

}

CDlgManagement::~CDlgManagement()
{
}

void CDlgManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_MemberList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strSearch);
}


BEGIN_MESSAGE_MAP(CDlgManagement, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgManagement::OnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &CDlgManagement::OnClickedButtonAll)
END_MESSAGE_MAP()


// CDlgManagement 메시지 처리기
void CDlgManagement::SetSearchResult(const CString& strSQL)
{
	CRecordset* recSet;
	recSet = new CRecordset(&g_dbMember);

	TRY
	{
		CString strID;	//회원ID
		CString strPassword;	//회원 password
		CString strMembername;//회원 이름
		CString strPhonenumber;//회원 전화번호
		CString strEmail;//회원 이메일
		int nIndex = 0;

		recSet->Open(CRecordset::forwardOnly, strSQL);

		if (recSet->GetRecordCount() == 0)
		{
			AfxMessageBox(_T("검색하신 데이터가 존재하지않습니다."), MB_ICONINFORMATION);
			recSet->Close();
			return;
		}

		while (!recSet->IsEOF())
		{
			recSet->GetFieldValue(_T("ID"), strID);
			recSet->GetFieldValue(_T("PASSWORD"), strPassword);
			recSet->GetFieldValue(_T("MEMBERNAME"), strMembername);
			recSet->GetFieldValue(_T("PHONENUMBER"), strPhonenumber);
			recSet->GetFieldValue(_T("EMAIL"), strEmail);

			m_MemberList.InsertItem(nIndex, strID, 1);
			m_MemberList.SetItemText(nIndex, 1, strPassword);
			m_MemberList.SetItemText(nIndex, 2, strMembername);
			m_MemberList.SetItemText(nIndex, 3, strPhonenumber);
			m_MemberList.SetItemText(nIndex, 4, strEmail);
			nIndex++;

			recSet->MoveNext();
		}

		recSet->Close();
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if (recSet->IsOpen())
			recSet->Close();
		delete recSet;
		return;
	}
	END_CATCH

		delete recSet;
}


void CDlgManagement::OnClickedButton8()
{
	UpdateData(TRUE);

	if (m_strSearch.IsEmpty())
	{
		AfxMessageBox(_T("검색어를 입력하세요."), MB_ICONINFORMATION);
		return;
	}
	CString strSQL;

	// 검색 조건에 맞는 검색 쿼리를 만든다.

	strSQL.Format(_T("SELECT * FROM [MEMBER] WHERE [MEMBERNAME] = '%s'"), m_strSearch);


	// 리스트뷰에 검색 데이터된 데이터를 보여준다.
	m_MemberList.DeleteAllItems();
	SetSearchResult(strSQL);
}


BOOL CDlgManagement::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_MemberList.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(1, _T("PW"), LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 50);
	m_MemberList.InsertColumn(3, _T("PH"), LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(4, _T("EMail"), LVCFMT_LEFT, 100);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgManagement::OnClickedButtonAll()
{
	CString strSQL;
	m_MemberList.DeleteAllItems(); // 우선 리스트에있는 회원정보를 삭제 후 다시 출력하기 위해 작성
	strSQL.Format(_T("SELECT * FROM [MEMBER]"), m_strSearch);//모든 회원정보를 검색할 쿼리문
	SetSearchResult(strSQL);
}
