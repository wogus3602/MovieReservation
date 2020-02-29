// DlgRegistration.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgRegistration.h"
#include "afxdialogex.h"


// CDlgRegistration 대화 상자

IMPLEMENT_DYNAMIC(CDlgRegistration, CDialogEx)

CDlgRegistration::CDlgRegistration(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REGISTRATION, pParent)
	, m_strMovieName(_T(""))
	, m_strMovieTime(_T(""))
	, m_strMovieValue(_T(""))
{

}

CDlgRegistration::~CDlgRegistration()
{
}

void CDlgRegistration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOVIENAME, m_strMovieName);
	DDX_Text(pDX, IDC_EDIT_MOVIETIME, m_strMovieTime);
	DDX_Text(pDX, IDC_EDIT_MOVIEVALUE, m_strMovieValue);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CDlgRegistration, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgRegistration::OnClickedButton7)
END_MESSAGE_MAP()


/*데이터 베이스에 정보를 저장하는 함수*/
void CDlgRegistration::SetAddData()
{
	UpdateData(TRUE);

	TRY
	{
		CString strSQL;

	/*쿼리문을 strSQL에 저장후 데이터베이스에 보낸다.*/
		strSQL.Format(_T("INSERT INTO [MOVIE] VALUES('%s', '%s', '%s', 0, 0,0)"),  m_strMovieName, m_strMovieValue, m_strMovieTime);

		g_dbMember.ExecuteSQL(strSQL);
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		return;
	}
	END_CATCH
}


/*등록버튼을 누르면 edit컨트롤에 적혀있는 정보가 데이터베이스에
저장이 되고 리스트컨트롤에있는 정보를 재 갱신한다.*/
void CDlgRegistration::OnClickedButton7()
{
	SetAddData();  //데이터베이스에 데이터를 저장하는 함수
	m_list1.DeleteAllItems(); //리스트에 있는 정보를 지운다.
	SetSearchResult(); //데이터베이스에 저장되어있는 정보를 리스트에 출력해준다.

}

/*초기작업 함수이다.*/
BOOL CDlgRegistration::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	/*리스트컨트롤창에서 컬럼부분에 삽입한다.*/
	m_list1.InsertColumn(0, _T("영화제목"), LVCFMT_LEFT, 100);
	m_list1.InsertColumn(1, _T("영화가격"), LVCFMT_LEFT, 70);
	m_list1.InsertColumn(2, _T("영화시간"), LVCFMT_LEFT, 120);
	m_list1.InsertColumn(3, _T("영화예매수"), LVCFMT_LEFT, 100);
	SetSearchResult();
	return TRUE;
}


void CDlgRegistration::SetSearchResult()
{
	CRecordset* recSet;
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM [MOVIE]"));
	recSet = new CRecordset(&g_dbMember);

	TRY
	{
		CString strName;
		CString strValue;
		CString strTime;
		CString strCount;
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
			recSet->GetFieldValue(_T("MOVIENAME"),   strName);
			recSet->GetFieldValue(_T("MOVIEVALUE"),  strValue);
			recSet->GetFieldValue(_T("MOVIETIME"),   strTime);
			recSet->GetFieldValue(_T("MOVIECOUNT"),    strCount);

			m_list1.InsertItem(nIndex, strName, 1);
			m_list1.SetItemText(nIndex, 1, strValue);
			m_list1.SetItemText(nIndex, 2, strTime);
			m_list1.SetItemText(nIndex, 3, strCount);

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
