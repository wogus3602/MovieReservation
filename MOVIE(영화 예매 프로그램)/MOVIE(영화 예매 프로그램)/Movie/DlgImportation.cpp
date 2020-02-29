// DlgImportation.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgImportation.h"
#include "afxdialogex.h"


// CDlgImportation 대화 상자

IMPLEMENT_DYNAMIC(CDlgImportation, CDialogEx)

CDlgImportation::CDlgImportation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMPORTATION, pParent)
	, m_strSearch(_T(""))
{

}

CDlgImportation::~CDlgImportation()
{
}

void CDlgImportation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_MemberList);
	DDX_Text(pDX, IDC_EDIT_MOVIENAME, m_strSearch);
}


BEGIN_MESSAGE_MAP(CDlgImportation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgImportation::OnClickedButton7)
END_MESSAGE_MAP()


// CDlgImportation 메시지 처리기
BOOL CDlgImportation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//ControlList에서의 컬럼쪽에 내용을 적는 부분
	m_MemberList.InsertColumn(0, _T("영화제목"), LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(1, _T("영화가격"), LVCFMT_LEFT, 70);
	m_MemberList.InsertColumn(2, _T("관객 수"), LVCFMT_LEFT, 70);
	m_MemberList.InsertColumn(3, _T("영화수입"), LVCFMT_LEFT, 70);

	CRecordset* recSet; //레코드셋을 받을 포인터
	CString strSQL; //쿼리문을 저장할 변수
	strSQL.Format(_T("SELECT * FROM [MOVIE]"));
	recSet = new CRecordset(&g_dbMember);
	TRY
	{
		CString strName;  //영화내용을 저장할 변수
		CString strValue; //영화가격을 저장할 변수
		CString strCount; //영화관객수를 저장할 변수
		int nIndex = 0;

		recSet->Open(CRecordset::forwardOnly, strSQL);

		while (!recSet->IsEOF())
		{
			recSet->GetFieldValue(_T("MOVIENAME"), strName);
			recSet->GetFieldValue(_T("MOVIEVALUE"), strValue);
			recSet->GetFieldValue(_T("MOVIECOUNT"), strCount);

			int import = _tstoi(strValue) * _tstoi(strCount);
			CString importation;
			importation.Format(_T("%d"), import);

			m_MemberList.InsertItem(nIndex, strName, 1);
			m_MemberList.SetItemText(nIndex, 1, strValue);
			m_MemberList.SetItemText(nIndex, 2, strCount);
			m_MemberList.SetItemText(nIndex, 3, importation);
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
	}
	END_CATCH

		delete recSet;

	return TRUE;
}


void CDlgImportation::OnClickedButton7()
{
	UpdateData(TRUE);

	CString strSQL;
	if (m_strSearch.IsEmpty())
	{
		AfxMessageBox(_T("검색어를 입력하세요."), MB_ICONINFORMATION);
		return;
	}

	strSQL.Format(_T("SELECT * FROM [MOVIE] WHERE [MOVIENAME] = '%s'"), m_strSearch);
	m_MemberList.DeleteAllItems();
	SetSearchResult(strSQL);
}

void CDlgImportation::SetSearchResult(const CString& strSQL)
{
	CRecordset* recSet;
	recSet = new CRecordset(&g_dbMember);
	TRY
	{
		CString strName;
		CString strValue;
		CString strCount;

		recSet->Open(CRecordset::forwardOnly, strSQL);

		if (recSet->GetRecordCount() == 0)
		{
			AfxMessageBox(_T("검색하신 데이터가 존재하지않습니다."), MB_ICONINFORMATION);
			recSet->Close();
			return;
		}

		recSet->GetFieldValue(_T("MOVIENAME"), strName);
		recSet->GetFieldValue(_T("MOVIEVALUE"), strValue);
		recSet->GetFieldValue(_T("MOVIECOUNT"), strCount);

		int import = _tstoi(strValue) * _tstoi(strCount);
		CString importation;
		importation.Format(_T("%d"), import);

		m_MemberList.InsertItem(0, strName, 1);
		m_MemberList.SetItemText(0, 1, strValue);
		m_MemberList.SetItemText(0, 2, strCount);
		m_MemberList.SetItemText(0, 3, importation);

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


