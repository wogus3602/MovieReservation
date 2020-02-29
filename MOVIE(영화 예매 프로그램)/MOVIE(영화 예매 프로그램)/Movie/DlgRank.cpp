// DlgRank.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgRank.h"
#include "afxdialogex.h"


// CDlgRank 대화 상자

IMPLEMENT_DYNAMIC(CDlgRank, CDialogEx)

CDlgRank::CDlgRank(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
	, m_strname(_T(""))
{

}

CDlgRank::~CDlgRank()
{
}

void CDlgRank::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_RankList);
	DDX_Control(pDX, IDC_STATIC_MoviePicture, m_Disaplay);
	DDX_Text(pDX, IDC_EDIT1, m_strname);
}


BEGIN_MESSAGE_MAP(CDlgRank, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgRank::OnClickedButton5)
	ON_STN_CLICKED(IDC_STATIC_MoviePicture, &CDlgRank::OnStnClickedStaticMoviepicture)
END_MESSAGE_MAP()


// CDlgRank 메시지 처리기
void CDlgRank::SetSearchResult()
{
	CRecordset* recSet;
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM [MOVIE] ORDER BY MOVIECOUNT DESC"));	// 영화 관객 수를 내림차순으로 정렬하여 순위를 나타낸다.
	recSet = new CRecordset(&g_dbMember);

	TRY
	{
		CString strName;	// 영화 이름
		CString strValue;	// 영화 가격
		CString strTime;	// 상영 시간
		CString strCount;	// 관객 수
		int nIndex = 0;		// 튜플의 번호

		recSet->Open(CRecordset::forwardOnly, strSQL);

		if (recSet->GetRecordCount() == 0)
		{
			AfxMessageBox(_T("검색하신 데이터가 존재하지않습니다."), MB_ICONINFORMATION);
			recSet->Close();
			return;
		}

		while (!recSet->IsEOF())
		{
			recSet->GetFieldValue(_T("MOVIENAME"),   strName);	  // MOVIE 테이블의 MOVIENAME을 strName으로 받는다.
			recSet->GetFieldValue(_T("MOVIEVALUE"),  strValue);	  // 테이블의 MOVIEVALUE를 strValue로 받는다.
			recSet->GetFieldValue(_T("MOVIETIME"),   strTime);	  // 테이블의 MOVIETIME을 strTime으로 받는다.
			recSet->GetFieldValue(_T("MOVIECOUNT"),    strCount); // 테이블의 MOVIECOUNT를 strCount로 받는다.

			m_RankList.InsertItem(nIndex, strName, 1);			  // 해당 튜플의 정보들을 리스트에 띄운다.
			m_RankList.SetItemText(nIndex, 1, strValue);
			m_RankList.SetItemText(nIndex, 2, strTime);
			m_RankList.SetItemText(nIndex, 3, strCount);

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

BOOL CDlgRank::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_RankList.InsertColumn(0, _T("영화제목"), LVCFMT_LEFT, 100);		// 리스트 내용의 가장 윗 부분에 필드를 명시한다.
	m_RankList.InsertColumn(1, _T("영화가격"), LVCFMT_LEFT, 70);
	m_RankList.InsertColumn(2, _T("영화시간"), LVCFMT_LEFT, 120);
	m_RankList.InsertColumn(3, _T("영화예매수"), LVCFMT_LEFT, 100);
	SetSearchResult();
	return TRUE;
}


void CDlgRank::OnClickedButton5()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HBITMAP hbit;


	if (m_strname == "아쿠아맨")		// 검색되는 영화이름에 따라 이미지를 나타낸다.
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	else if (m_strname == "내안의그놈") {
		hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	}
	else if (m_strname == "말모이") {
		hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	}
	else {
		AfxMessageBox("검색 결과가 없습니다.");
		return;
	}
	m_Disaplay.SetBitmap(hbit);

}


void CDlgRank::OnStnClickedStaticMoviepicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
