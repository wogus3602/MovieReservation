// DlgSeatSelection.cpp: 구현 파일

#include "stdafx.h"
#include "Movie.h"
#include "DlgSeatSelection.h"
#include "afxdialogex.h"
#include "DlgReservetion.h" // 예매창에서 선택한 영화 이름 정보를 가져오기 위해 선언 해줍니다. ResName 사용

// CDlgSeatSelection 대화 상자

IMPLEMENT_DYNAMIC(CDlgSeatSelection, CDialogEx)

CDlgSeatSelection::CDlgSeatSelection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEATSELECTION, pParent)
{

}
CDlgSeatSelection::~CDlgSeatSelection()
{
}

void CDlgSeatSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgSeatSelection, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_RE, &CDlgSeatSelection::OnClickedButtonRe)
END_MESSAGE_MAP()


// CDlgSeatSelection 메시지 처리기
BOOL CDlgSeatSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CDlgReservetion *pDlg = (CDlgReservetion*)AfxGetMainWnd();

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	SelectData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgSeatSelection::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	DrawRec(); // 사각형 그리기
	DrawLine(); // 라인 그리기

	/*좌석 선택창에 들어갈 때 기존에 데이터베이스에 저장된 좌석 정보를 표시해 줍니다.*/
	/*m_Seat 값이 0이면 빈자리 1이면 자리가 있는 자리입니다.*/
	/*----------------------------------------왼쪽 좌석------------------------------------------------*/
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			/*선택한 좌석을 자리가 차있다고 알려주기 위해 빨간색으로 색칠해줌*/
			if (m_Seat[i][j] == 1)
			{
				DrawCheck(i, j);
			}
		}
	}
	/*----------------------------------------가운데 좌석------------------------------------------------*/
	for (int i = 0; i < 12; i++)
	{
		for (int j = 3; j < 14; j++)
		{
			/*선택한 좌석을 자리가 차있다고 알려주기 위해 빨간색으로 색칠해줌*/
			if (m_Seat[i][j] == 1)
			{
				DrawCheck(i, j);
			}
		}
	}
	/*----------------------------------------오른쪽 좌석------------------------------------------------*/
	for (int i = 0; i < 12; i++)
	{
		for (int j = 15; j < 17; j++)
		{
			/*선택한 좌석을 자리가 차있다고 알려주기 위해 빨간색으로 색칠해줌*/
			if (m_Seat[i][j] == 1)
			{
				DrawCheck(i, j);
			}
		}
	}
}


void CDlgSeatSelection::DrawRec()
{
	// 사각형을 그려줍니다.

	CClientDC dc(this);

	CBrush br;

	br.CreateSolidBrush(RGB(62, 62, 124)); // 색은 네이비

	CBrush *lbr = dc.SelectObject(&br);

	dc.Rectangle(10, 10, 10 + 40, 10 + 240); // 왼쪽 좌석의 사각형 네이비 상자

	dc.Rectangle(70, 10, 70 + (20 * 11), 10 + (20 * 12)); // 가운데 좌석의 네이비 상자

	dc.Rectangle(310, 10, 310 + (20 * 2), 10 + 240); // 오른쪽 좌석의 사각형 네이비 상자 : 10+(20*15) : 10은 윈도우 틀과 표의 거리, 20*15는 작은 네모의 갯수 만큼 띄워 줘야하니까 15개 만큼 띄어줌 

	dc.SelectObject(lbr);
}


void CDlgSeatSelection::DrawLine()
{
	// TODO: 여기에 구현 코드 추가.
	// 구분선을 그려줍니다.
	int i, j;
	CClientDC dc(this);

	CPen pen;

	pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));

	CPen *lodp = dc.SelectObject(&pen);
	/*----------------------------------------왼쪽 좌석------------------------------------------------*/
	/* 2 * 12, 왼쪽 Seat 한칸 20픽셀 크기 */
	for (int i = 0; i < 13; i++) //가로선 그리기
	{
		dc.MoveTo(10, 10 + i * 20); // 20은 네모 크기, 2랑 12는 가로 세로선 길이
		dc.LineTo(20 * 2 + 10, 10 + i * 20);
	}

	for (int i = 0; i < 3; i++) //세로선 그리기
	{
		dc.MoveTo(10 + i * 20, 10);
		dc.LineTo(10 + i * 20, 20 * 12 + 10);
	}
	/*---------------------------------------가운데 좌석-------------------------------------------------*/
	/* 11 * 12, 가운데 Seat 한칸 20픽셀 크기 */
	for (int i = 0; i < 13; i++) //가로선 그리기
	{
		dc.MoveTo(70, 10 + i * 20); // 20은 네모 크기, 2랑 12는 가로 세로선 길이
		dc.LineTo(20 * 11 + 70, 10 + i * 20);
	}
	for (int i = 0; i < 12; i++) //세로선 그리기
	{
		dc.MoveTo(70 + i * 20, 10);
		dc.LineTo(70 + i * 20, 20 * 12 + 10);
	}

	/*---------------------------------------오른쪽 좌석-------------------------------------------------*/
	/* 2 * 12, 오른쪽 Seat 한칸 20픽셀 크기 */
	for (int i = 0; i < 13; i++) //가로선 그리기
	{
		dc.MoveTo(310, 10 + i * 20); // 20은 네모 크기, 2랑 12는 가로 세로선 길이
		dc.LineTo(20 * 2 + 310, 10 + i * 20);
	}

	for (int i = 0; i < 3; i++) //세로선 그리기
	{
		dc.MoveTo(310 + i * 20, 10);
		dc.LineTo(310 + i * 20, 20 * 12 + 10);
	}
	/*---------------------------------------------------------------------------------------------------*/
	dc.SelectObject(pen);
}


void CDlgSeatSelection::DrawCheck(int iRow, int iCol)
{
	/*자리가 차있다고 알려주기 위한 메서드 (자리가 있으면 한칸을 빨강색으로 칠해 준다.)*/

	m_Seat[iRow][iCol] = 1;
	CString str;

	CClientDC dc(this);

	// 원래 있던 숫자(0)을 지웁니다.
	CBrush br;
	CPen pen;

	pen.CreatePen(PS_SOLID, 1, RGB(124, 0, 0)); // 빨강색
	CPen *lodp = dc.SelectObject(&pen);

	br.CreateSolidBrush(RGB(124, 0, 0)); // 빨강색
	CBrush *lbr = dc.SelectObject(&br);
	dc.Rectangle(12 + iCol * 20, 12 + iRow * 20, 12 + iCol * 20 + 15, 12 + iRow * 20 + 15);

	dc.SelectObject(lbr);
	dc.SelectObject(lodp);
}

void CDlgSeatSelection::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// TODO: Add your message handler code here and/or call default
	/*좌석창을 벗어나서 클릭을 하면 클릭이 않되게 합니다.*/
	if (point.x > 50 && point.x < 70 || point.y > 250) 
		return;
	if (point.x < 10 || point.y < 10)
		return;
	if (point.x > 290 && point.x < 310 || point.y > 250)
		return;
	if (point.x > 350 || point.y > 250)
		return;
	/*-----------------------------------------------------------------------------------------------*/
	int iRow = -1, iCol = -1;
	PosToIndex(point, iRow, iCol); // 선택한 좌석 좌표값을 가져옵니다.

	if (m_Seat[iRow][iCol] == 0 && chooseSeat == 0)
	{
		/*하나의 빈 좌석을 클릭시에만 빨강색으로 좌석을 표시해 줍니다.*/
		chooseSeat++; // 좌석을 하나 클릭하면 더이상 클릭못하게 해줍니다.
		DrawCheck(iRow, iCol); // 빨강색으로 좌석을 표시해줍니다.
		/*마우스로 잘못된 좌석 행열 정보를 가져오는걸 방지하기 위해 값을 미리 옮겨 줍니다.*/
		savex = iRow;
		savey = iCol;
		UpdateData(FALSE);
		// 선택한 숫자를 전송한다.
	}
	else if (iRow == savex && iCol == savey && chooseSeat != 0)
	{
		/*선택한 좌석을 한번더 누르면 취소 되고 다른 좌석으로 변경할 수 있게 해줌.*/
		chooseSeat = 0; // 다른 좌석으로 고를 수 있게 해줍니다.
		m_Seat[iRow][iCol] = 0;
		CString str;

		CClientDC dc(this);

		// 원래 있던 숫자(0)을 지웁니다.
		CBrush br;
		CPen pen;

		pen.CreatePen(PS_SOLID, 1, RGB(62, 62, 124)); // 네이비 색
		CPen *lodp = dc.SelectObject(&pen);

		br.CreateSolidBrush(RGB(62, 62, 124)); // 네이비 색
		CBrush *lbr = dc.SelectObject(&br);
		dc.Rectangle(12 + iCol * 20, 12 + iRow * 20, 12 + iCol * 20 + 15, 12 + iRow * 20 + 15);

		dc.SelectObject(lbr);
		dc.SelectObject(lodp);
	}

	CDialog::OnLButtonDown(nFlags, point);
}


HCURSOR CDlgSeatSelection::OnQueryDragIcon()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnQueryDragIcon();
}


void CDlgSeatSelection::PosToIndex(CPoint pnt, int &iRow, int &iCol)
{
	//포지션을 이용해 마우스로 선택한 좌표 인덱스를 구합니다.
	int i, j;
	int flagX = 0, flagY = 0;
	/*---------------------------------------왼쪽 좌석-------------------------------------------------*/
	if (flagX == 0)
	{
		for (i = 0; i < 12; i++) //행 결정(Row)
		{
			if ((pnt.y > 10 + i * 20) &&
				pnt.y <= (10 + (i + 1) * 20)
				) {
				flagX++;
				break;
			}
		}
	}
	if (flagY == 0)
	{
		for (j = 0; j < 2; j++) //열 결정(Col)
		{
			if ((pnt.x > 10 + j * 20) &&
				pnt.x <= (10 + (j + 1) * 20)
				) {
				flagY++;
				break;
			}
		}
	}

	/*---------------------------------------가운데 좌석-------------------------------------------------*/
	if (flagX == 0)
	{
		for (i = 0; i < 12; i++) //행 결정(Row)
		{
			if ((pnt.y > 10 + i * 20) &&
				pnt.y <= (10 + (i + 1) * 20)
				) {
				flagX++;
				break;
			}
		}
	}
	if (flagY == 0)
	{
		for (j = 3; j < 14; j++) //열 결정(Col)
		{
			if ((pnt.x > 10 + j * 20) &&
				pnt.x <= (10 + (j + 1) * 20)
				) {
				flagY++;
				break;
			}
		}
	}
	/*---------------------------------------오른쪽 좌석-------------------------------------------------*/
	if (flagX == 0)
	{
		for (i = 0; i < 12; i++) //행 결정(Row)
		{
			if ((pnt.y > 10 + i * 20) &&
				pnt.y <= (10 + (i + 1) * 20)
				) {
				flagX++;
				break;
			}
		}
	}
	if (flagY == 0)
	{
		for (j = 15; j < 17; j++) //열 결정(Col)
		{
			if ((pnt.x > 10 + j * 20) &&
				pnt.x <= (10 + (j + 1) * 20)
				) {
				flagY++;
				break;
			}
		}
	}
	iRow = i;
	iCol = j;
}

BOOL CDlgSeatSelection::SetAddData()
{
	/*선택된 좌석을 저장하기 위한 메서드 좌석 선택창을 누르면 누른 좌석을 데이터 베이스에 저장*/
	CString strSQL; // SQL문을 넣기 위한 변수 선언

	TRY
	{
		/*SEAT라는 테이블에 영화이름과 행열 정보를 넣습니다.*/
		strSQL.Format(_T("INSERT INTO [SEAT] VALUES('%s', %d, %d)"), ResName, savex, savey);
		g_dbMember.ExecuteSQL(strSQL);
		return TRUE;
	}
	CATCH(CException, e) // 예외 처리
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		return TRUE;
	}
	END_CATCH
}


void CDlgSeatSelection::OnClickedButtonRe()
{
	/*좌석을 선택하고 선택 버튼을 누를시에 생기는 이벤트*/
	if (chooseSeat == 1) {
		SetAddData(); // 데이터 베이스에 영화이름에 따른 좌석 위치를 저장 시킵니다.
		AfxMessageBox("좌석선택이 완료되었습니다.");
		CDialogEx::OnOK();
	}
	else {
		AfxMessageBox("좌석선택을 안했습니다.");
	}
}


void CDlgSeatSelection::SelectData()
{
	/*영화 이름에 따른 선택된 좌석을 표시해두기 위한 메서드*/
	/*좌석 선택창을 누르면 자리가 있는 좌석을 표시*/
	CRecordset rs(&g_dbMember);
	CString strname; // 데이터베이스에 있는 영화 이름
	CString x; // 데이터베이스에 있는 좌석 ROW
	CString y; // 데이터베이스에 있는 좌석 COLUMN
	TRY
	{
		rs.Open(CRecordset::dynaset, _T("SELECT * FROM [SEAT]"));
	while (!rs.IsEOF()) // 데이터베이스에 있는 모든 정보를 확인하기 위함입니다.
	{
		/*영화이름에 따른 선택된 좌석 위치를 데이터베이스에서 가져옴*/
		rs.GetFieldValue(_T("SEATMOVIENAME"), strname);
		if (strname == ResName)
		{
			rs.GetFieldValue(_T("SEATROW"), x); // 데이터베이스에서 행 정보를 가져옴
			rs.GetFieldValue(_T("SEATCOLUMN"), y); // 데이터베이스에서 열 정보를 가져옴
			DrawCheck(atoi(x), atoi(y)); // 데이터베이스에 있는 행열 위치를 통해 m_Seat 행열의 값정보를 1로 바꾸기 위해서 실행 해줍니다.
		}
		rs.MoveNext(); // 데이터베이스에 있는 정보를 다음칸으로 넘김

	}
	rs.Close(); // 레코드셋 닫음
	}
	CATCH(CException, e) // 예외 처리
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		if (rs.IsOpen())
			rs.Close();
		return;
	}
	END_CATCH

}
