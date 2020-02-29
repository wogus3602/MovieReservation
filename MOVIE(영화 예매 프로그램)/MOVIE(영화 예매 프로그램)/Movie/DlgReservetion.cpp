// DlgReservetion.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "DlgReservetion.h"
#include "afxdialogex.h"
#include "DlgSeatSelection.h"

// CDlgReservetion 대화 상자

IMPLEMENT_DYNAMIC(CDlgReservetion, CDialogEx)

CDlgReservetion::CDlgReservetion(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RESERVETION, pParent)
{

}

CDlgReservetion::~CDlgReservetion()
{
}

void CDlgReservetion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_PRICE, m_price);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_LIST2, list);

	//리스트컨트롤, 픽쳐박스, 콤보박스 , 텍스트를 변수로만듬

}


BEGIN_MESSAGE_MAP(CDlgReservetion, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON4, &CDlgReservetion::OnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CDlgReservetion::OnClickedButton5)
	//ON_BN_CLICKED(IDC_BUTTON6, &CDlgReservetion::OnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON7, &CDlgReservetion::OnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgReservetion::OnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CDlgReservetion::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CDlgReservetion::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgReservetion::OnBnClickedButton8)
END_MESSAGE_MAP()//각각의 버튼 이벤트를 주었다.





void CDlgReservetion::OnClickedButton4() //리뷰를 보이게 사이트 연결
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShellExecute(this->m_hWnd, TEXT("open"), TEXT("IEXPLORE.EXE"), TEXT("https://movie.naver.com/movie/point/af/list.nhn"), NULL, SW_SHOW);
}

//
//void CDlgReservetion::OnClickedButton5()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	HBITMAP hbit;
//
//	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
//	m_pic.SetBitmap(hbit);
//	m_combo.ResetContent();
//	 
//	CRecordset rs(&g_dbMember);
//	TRY
//	{
//		rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]"));
//	while (!rs.IsEOF())
//	{
//		rs.GetFieldValue(_T("MOVIENAME"), strname);
//		if (strname == "아쿠아맨")
//		{
//			rs.GetFieldValue(_T("MOVIETIME"), strTime);
//			m_combo.AddString(strTime);
//		}
//		rs.MoveNext();
//
//	}
//	rs.Close();
//	m_combo.SetCurSel(0);
//	}
//		CATCH(CException, e)
//	{
//		TCHAR szCause[255];
//		e->GetErrorMessage(szCause, 255);
//		if (rs.IsOpen())
//			rs.Close();
//		return;
//	}
//	END_CATCH
//
//}
//
//
//void CDlgReservetion::OnClickedButton6()
//{
//	//HBITMAP hbit;
//
//	//hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
//
//	//m_pic.SetBitmap(hbit);
//
//	m_combo.ResetContent();
//	CRecordset rs(&g_dbMember);
//	TRY
//	{
//		rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]"));
//	while (!rs.IsEOF())
//	{
//		rs.GetFieldValue(_T("MOVIENAME"), strname);
//		if (strname == "내안의그놈")
//		{
//			rs.GetFieldValue(_T("MOVIETIME"), strTime);
//			m_combo.AddString(strTime);
//		}
//		rs.MoveNext();
//
//	}
//	rs.Close();
//	m_combo.SetCurSel(0);
//	}
//		CATCH(CException, e)
//	{
//		TCHAR szCause[255];
//		e->GetErrorMessage(szCause, 255);
//		if (rs.IsOpen())
//			rs.Close();
//		return;
//	}
//	END_CATCH
//
//}
//
//
//void CDlgReservetion::OnClickedButton7()
//{
//	//HBITMAP hbit;
//
//	//hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
//
//	//m_pic.SetBitmap(hbit);
//
//	m_combo.ResetContent();
//	CRecordset rs(&g_dbMember);
//	TRY
//	{
//	rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]"));
//
//
//	while (!rs.IsEOF())
//	{
//		rs.GetFieldValue(_T("MOVIENAME"), strname);
//		if (strname == "말모이")
//		{
//			rs.GetFieldValue(_T("MOVIETIME"), strTime);
//			m_combo.AddString(strTime);
//		}
//		rs.MoveNext();
//
//	}
//	rs.Close();
//	m_combo.SetCurSel(0);
//	}
//		CATCH(CException, e)
//	{
//		TCHAR szCause[255];
//		e->GetErrorMessage(szCause, 255);
//		if (rs.IsOpen())
//			rs.Close();
//		return;
//	}
//	END_CATCH
//
//}

CString sIndexValue; //

void CDlgReservetion::OnSelchangeCombo1()//영화시간 콤보박스 이벤트
{
	CString strcom;
	CString strnamecom;
	int select = m_combo.GetCurSel();
	m_combo.GetLBText(select, strcom);
	m_price.SetWindowTextA("0원");  //처음 아무런 선택이 없을시 초기값
	CRecordset rs(&g_dbMember);
	TRY
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]")); //DB에서 영화테이블 불러옴

	while (!rs.IsEOF())
	{
		rs.GetFieldValue(_T("MOVIENAME"), strnamecom);   //영화이름
		rs.GetFieldValue(_T("MOVIETIME"), strTime);      //영화시간
		if (sIndexValue == strnamecom && strcom == strTime)   
		{
			rs.GetFieldValue(_T("MOVIEVALUE"), strPrice);  //영화가격

			m_price.SetWindowTextA(strPrice + "원");  // 영화가격 삽입
		}
		rs.MoveNext();

	}
	rs.Close();
	//m_combo.SetCurSel(0);
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		if (rs.IsOpen())
			rs.Close();
		return;
	}
	END_CATCH

		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CDlgReservetion::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	liston();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

#include"MovieDlg.h"
BOOL CDlgReservetion::SetAddData()  //영화예매이벤트
{
	CMovieDlg mm;

	UpdateData(TRUE);

	TRY
	{
		CString strSQL;  
		strSQL.Format(_T("INSERT INTO [RES] VALUES('%s', '%s', '%s')"), sIndexValue, mm.DBid, strTime);  

		g_dbMember.ExecuteSQL(strSQL);   //DB에 영화이름,사용자이름,시간때 저장.
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

BOOL CDlgReservetion::SetUpdateData()  //영화 예매시 현재 영화의 구입수를 업데이트해줌
{
	CString sName, sTime, sCount;
	int cnt;
	CRecordset rs(&g_dbMember);
	CString strSQL;
	TRY
	{
	   rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]"));


	while (!rs.IsEOF())
	{
		  rs.GetFieldValue(_T("MOVIECOUNT"), sCount);
		  rs.GetFieldValue(_T("MOVIENAME"), sName);
		   rs.GetFieldValue(_T("MOVIETIME"), sTime);
		  if (sIndexValue == sName && strTime == sTime)
		  {
				cnt = _ttoi(sCount);
				cnt++;
				strSQL.Format(_T("UPDATE [MOVIE] SET [MOVIECOUNT] ='%d' WHERE [MOVIENAME]='%s'AND [MOVIETIME]='%s'"),cnt, sName, sTime);  //영화시간과 이름으로 영화카운트증가 업데이트
				g_dbMember.ExecuteSQL(strSQL);
				return TRUE;
		  }
		  //영화 이름과 시간때를 비교조건으로 하여 영화관람수 카운트증가
		  rs.MoveNext();

	}
	rs.Close();

	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		if (rs.IsOpen())
			rs.Close();
		return TRUE;
	}
	END_CATCH
}
void CDlgReservetion::OnBnClickedOk()//예매버튼 누를시 위 업데이트 메서드 호출, 그리고 예매완료메세지창 나옴
{
	SetUpdateData();
		if (!SetAddData()) {

		}
		else {

		}
	AfxMessageBox("예매가 완료되었습니다.");
}


void CDlgReservetion::liston() //DB영화 테이블에 저장된 영화이름을 리스트컨트롤로 뿌려준다.
{
	int index = 0;
	CRecordset rs(&g_dbMember);

	TRY
	{
		rs.Open(CRecordset::dynaset, _T("SELECT DISTINCT [MOVIENAME] FROM [MOVIE]"));

	while (!rs.IsEOF())
	{
		rs.GetFieldValue(_T("MOVIENAME"), strname);
		list.InsertItem(index, strname);  //리스트컨트롤 값추가
		//list.SetItemText(index, 1,strname);
		index++;
		rs.MoveNext();

	}
	rs.Close();
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		if (rs.IsOpen())
			rs.Close();
		return;
	}
	END_CATCH
}

void CDlgReservetion::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)  //리스트 컨트로에 마우스이벤트를주어 클릭시 영화사진을 픽쳐박스에 보여주며 각 영화의 시간값들을 콤보박스에 준다.
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int idx = pNMListView->iItem; 
	m_price.SetWindowTextA("0원"); //가격 초기화

	sIndexValue = list.GetItemText(idx, 0);
	m_combo.ResetContent();   //콤보박스 초기화

	CRecordset rs(&g_dbMember);
	TRY
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM [MOVIE]"));


	while (!rs.IsEOF())
	{
		rs.GetFieldValue(_T("MOVIENAME"), strname);
		if (sIndexValue == strname && sIndexValue == "내안의그놈")
		{
			HBITMAP hbit;

			hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); //이미지 비트를 저장

			m_pic.SetBitmap(hbit);  //이미지를 보여준다

			rs.GetFieldValue(_T("MOVIETIME"), strTime);
			m_combo.AddString(strTime);  //해당 콤보박스에 시간 저장.
		}
		else if (sIndexValue == strname && sIndexValue == "아쿠아맨")
		{
			HBITMAP hbit;

			hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1)); //아쿠아맨 이미지

			m_pic.SetBitmap(hbit);  //이미지출력

			rs.GetFieldValue(_T("MOVIETIME"), strTime);
			m_combo.AddString(strTime);  //아쿠아맨 시간 저장
		}
		else if (sIndexValue == strname && sIndexValue == "말모이")
		{
			HBITMAP hbit;

			hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); //말모이이미지

			m_pic.SetBitmap(hbit); //이미지출력

			rs.GetFieldValue(_T("MOVIETIME"), strTime);
			m_combo.AddString(strTime); //말모이 시간 저장
		}
		rs.MoveNext();  //데이터베이스 다음행.

	}
	rs.Close();
	//m_combo.SetCurSel(0);
	}
		CATCH(CException, e)
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		if (rs.IsOpen())
			rs.Close();
		return;
	}
	END_CATCH
		*pResult = 0;
}


void CDlgReservetion::OnBnClickedButton8() // 좌석 선택 버튼 누를시에 좌석선택 대화상자 나오게 함
{
	/*좌석 선택창 나오게 함*/
	CDlgSeatSelection *dlgSeat = new CDlgSeatSelection;
	dlgSeat->ResName = sIndexValue; // 영화 예매창에서 선택한 영화 이름을 좌석창에 넘겨주기 위해 좌석창의 header에 선언된 ResName에 예매창에서 선택한 영화이름을 넘겨줌
	if (dlgSeat->DoModal() == IDOK) {

	}
}
