// Tab1.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "Tab1.h"
#include "afxdialogex.h"

#include "DlgReservetion.h"
#include "DlgRank.h"
#include "ChatClient.h"

// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab1);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTab1::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTab1::OnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CTab1::OnClickedButton2)
END_MESSAGE_MAP()


// CTab1 메시지 처리기


void CTab1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelect = m_tab1.GetCurSel();		// 탭의 번호를 저장받는다.

	switch (iSelect)						// 탭의 번호에 따라 다른 다이얼로그를 띄워준다.
	{
	case 0:									// 영화 예매 다이얼 로그
		dlg->ShowWindow(SW_SHOW);
		dlg1->ShowWindow(SW_HIDE);
		break;
	case 1:									// 인기 순위 다이얼 로그
		dlg->ShowWindow(SW_HIDE);
		dlg1->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}

BOOL CTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_tab1.InsertItem(0, _T("영화예매"));		// 탭의 번호와 이름을 지정한다.
	m_tab1.InsertItem(1, _T("인기순위"));

	m_tab1.SetCurSel(0);						// 초기에 선택되어있는 탭 번호

	CRect rect;
	m_tab1.GetWindowRect(&rect);

	dlg = new CDlgReservetion;						// 영화 예매 클래스를 생성하여
	dlg->Create(IDD_DIALOG_RESERVETION, &m_tab1);	// 탭에 넣는다.
	dlg->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg->ShowWindow(SW_SHOW);						// 초기에 선택되어 있는 탭이므로 보여지게한다.

	dlg1 = new CDlgRank;
	dlg1->Create(IDD_DIALOG_RANK, &m_tab1);
	dlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg1->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
	//			  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab1::OnClickedButton4()		// 영화 리뷰 웹 사이트를 띄워준다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShellExecute(this->m_hWnd, TEXT("open"), TEXT("IEXPLORE.EXE"), TEXT("https://movie.naver.com/movie/point/af/list.nhn"), NULL, SW_SHOW);
}

#include "ChatClient.h"
void CTab1::OnClickedButton2()		// 상담원과 채팅 연결을 해준다.
{

	CChatClient *dlgChat = new CChatClient;
	if (dlgChat->DoModal() == IDOK) {

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}