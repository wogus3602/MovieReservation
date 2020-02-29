#pragma once


// CDlgSeatSelection 대화 상자

class CDlgSeatSelection : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSeatSelection)

public:
	CDlgSeatSelection(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgSeatSelection();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEATSELECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
public:
	CString ResName; // 영화 이름을 예매창에서 넘겨받기 위해 선언
	void OnPaint();
	void DrawRec(); //네이비 사각형을 그려줍니다.
	void DrawLine(); // 네이비 사각형에 구분선을 그려줍니다.
	void DrawCheck(int iRow, int iCol); // 좌석마다 자리가 있는 좌석을 표시 해줍니다, 데이터 베이스에 있는 좌석 정보를 넘겨 받아서 그 좌석에 있는 m_Seat의 값을 1로 바꾸어 줍니다.

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	void PosToIndex(CPoint pnt, int &iRow, int &iCol);
	int m_Seat[13][16] = { 0 }; // 좌석 빈자리의 값은 0으로 만들고 2중 for문을 통해 m_Seat의 값이 1인 값만 빨간색 자리가 차있다는걸 표시하기 위해서 0으로 초기화 하였습니다.

	/*데이터베이스에 저장된 행열 정보를 사용하기 위해 선언*/
	int savex;
	int savey;

	int chooseSeat = 0; // 한자리 선택하면 더이상 자리를 못고르게 합니다.
	int width = 20; //좌석 한칸은 20pixel
	virtual BOOL OnInitDialog();
	BOOL SetAddData(); // 좌석 선택한 행열 정보와 영화 이름을 저장 해줍니다.
	CString DBMovieName;
	int SeatNum = 0;
	afx_msg void OnClickedButtonRe(); // 좌석 선택버튼을 누르게 해줍니다.
	void SelectData(); // 선택 했었던 좌석 정보를 DrawCheck에 넘겨주어 m_Seat 값을 1로 만들게 해줍니다. 그리고 DrawCheck을 통해 좌석을 빨강색으로 칠해주기 위함입니다.
};
