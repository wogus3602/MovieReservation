#pragma once


// CDlgReservetion 대화 상자

class CDlgReservetion : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReservetion)

public:
	CDlgReservetion(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgReservetion();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESERVETION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void liston();
	BOOL SetAddData();  //영화예매에데한 메서드이다.
	BOOL SetUpdateData(); //영화관람수를 업데이트해준다
	CString strname;  //영화이름
	CString strPrice; //영화가격
	CString strTime;  //영화시간
	afx_msg void OnClickedButton4();  //리뷰사이트버튼
	//afx_msg void OnClickedButton5();
	//afx_msg void OnClickedButton6();
	//afx_msg void OnClickedButton7();
	CComboBox m_combo; //영화시간 콤보박스
	CStatic m_price; //영화가격 비교
	afx_msg void OnSelchangeCombo1(); //콤보박스선택 이벤트
	CStatic m_pic; //영화이미지
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();   //예매버튼이벤트
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);//리스트 선택 이벤트
	CListCtrl list;  //리스트컨트롤
	afx_msg void OnBnClickedButton8();//좌석버튼이벤트
};
