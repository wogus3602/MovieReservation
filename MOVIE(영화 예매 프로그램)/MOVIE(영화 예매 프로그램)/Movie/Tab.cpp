// Tab.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "Tab.h"
#include "afxdialogex.h"

#include "DlgImportation.h"
#include "DlgManagement.h"
#include "DlgRegistration.h"

// CTab 대화 상자

IMPLEMENT_DYNAMIC(CTab, CDialogEx)

CTab::CTab(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CTab::~CTab()
{
}

void CTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTab 메시지 처리기


void CTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSelect = m_tab.GetCurSel();	// 탭의 번호를 저장받는다.

	switch (iSelect)		// 탭의 번호에 따라 다른 다이얼로그를 띄워준다.
	{
	case 0:					// 영화 등록 다이얼로그
		dlg->ShowWindow(SW_SHOW);
		dlg1->ShowWindow(SW_HIDE);
		dlg2->ShowWindow(SW_HIDE);
		break;
	case 1:					// 회원 관리 다이얼로그
		dlg->ShowWindow(SW_HIDE);
		dlg1->ShowWindow(SW_SHOW);
		dlg2->ShowWindow(SW_HIDE);
		break;
	case 2:					// 영화 수익  다이얼로그
		dlg->ShowWindow(SW_HIDE);
		dlg1->ShowWindow(SW_HIDE);
		dlg2->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;

}


BOOL CTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_tab.InsertItem(0, _T("영화등록"));	// 탭의 번호와 이름을 지정한다.
	m_tab.InsertItem(1, _T("회원관리"));
	m_tab.InsertItem(2, _T("영화수익"));

	m_tab.SetCurSel(0);						// 초기에 선택되어있는 탭 번호

	CRect rect;
	m_tab.GetWindowRect(&rect);

	dlg = new CDlgRegistration;						// 영화 등록 클래스를 생성하여
	dlg->Create(IDD_DIALOG_REGISTRATION, &m_tab);	// 탭에 넣는다.
	dlg->MoveWindow(0, 25, rect.Width(), rect.Height());	
	dlg->ShowWindow(SW_SHOW);						// 초기에 선택되어 있는 탭이므로 보여지게한다.

	dlg1 = new CDlgManagement;
	dlg1->Create(IDD_DIALOG_MANAGEMENT, &m_tab);
	dlg1->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg1->ShowWindow(SW_HIDE);

	dlg2 = new CDlgImportation;
	dlg2->Create(IDD_DIALOG_IMPORTATION, &m_tab);
	dlg2->MoveWindow(0, 25, rect.Width(), rect.Height());
	dlg2->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
			   // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
