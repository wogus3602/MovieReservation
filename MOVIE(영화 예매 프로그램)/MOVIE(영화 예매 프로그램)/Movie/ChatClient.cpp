// ChatClient.cpp: 구현 파일
//

#include "stdafx.h"
#include "Movie.h"
#include "ChatClient.h"
#include "afxdialogex.h"


// CChatClient 대화 상자

IMPLEMENT_DYNAMIC(CChatClient, CDialog)

CChatClient::CChatClient(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_COUNSELLING, pParent)
	, m_strSend(_T(""))
	, m_count(_T(""))
{

}

CChatClient::~CChatClient()
{
}

void CChatClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	//  DDX_Control(pDX, IDCANCEL, Close);
	DDX_Control(pDX, IDC_LIST2, m_wait);
	//  DDX_Control(pDX, IDC_STATIC_COUNT, m_count);
	DDX_Text(pDX, IDC_STATIC_COUNT, m_count);
}


BEGIN_MESSAGE_MAP(CChatClient, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatClient::OnClickedButtonSend)
	ON_MESSAGE(UM_RECEIVE, &CChatClient::OnReceive)
	ON_BN_CLICKED(IDCANCEL, &CChatClient::OnBnClickedCancel)
END_MESSAGE_MAP()

// CChatClient 메시지 처리기

#include "MovieDlg.h"
BOOL CChatClient::OnInitDialog()
{
	CMovieDlg Cmd;
	CDialog::OnInitDialog();
	AfxSocketInit();
	UpdateData(TRUE);
	m_socCom.Create();
	int t = m_socCom.Connect("localhost", 5000);
	if (t == 0) { //연결이 안되면 메세지를 보내준다.
		AfxMessageBox("상담자가 없습니다.");
		return FALSE;
	}
	m_socCom.Init(this->m_hWnd);

	m_wait.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100);
	m_wait.InsertItem(1, Cmd.m_loginuser, 1);
	m_wait.InsertItem(1, Cmd.m_loginuser, 2);
	m_count = "0"; //대기자 초기값을 0으로 설정해준다.
	return TRUE;
}

afx_msg LRESULT CChatClient::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);
	m_socCom.Receive(pTmp, 256);
	strTmp.Format("%s", pTmp);

	if (atoi(strTmp) > 0) { // 서버쪽에서 메세지를 보낼때 대기하고있는 사람수를 보내는데 만약 대기자가 있으면 조건문 실행
		int i = m_list.GetCount();
		m_list.InsertString(i, "대기자 입니다. 잠시만 기다려주세요.");
	}
	//이 조건은 만약 서버쪽에서 메세지를 보낼때 대기자가 0 이면 이 조건을 실행한다.
	else if (atoi(strTmp) == 0 && !TF) { //처음에는 항상 FALSE 이니 이 조건문을 넘는다.
		int i = m_list.GetCount();
		m_list.InsertString(i, "상담원이 연결되었습니다.");
		TF = TRUE;	// TRUE로 변할시항상 채팅이 가능하게 해준다.
		return TRUE;
	}
	if (TF) {
		int i = m_list.GetCount();
		m_list.InsertString(i, strTmp);
	}
	UpdateData(FALSE);
	return TRUE;
}


void CChatClient::OnBnClickedCancel()
{
	m_socCom.Send("EXIT", 256); //나가기 버튼을 눌렀을때 EXIT 보낸다.
	CDialog::OnCancel();
}


void CChatClient::OnClickedButtonSend()
{
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);
	strcpy(pTmp, m_strSend);
	m_socCom.Send(pTmp, 256);
	strTmp.Format(_T("%s"), pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
}