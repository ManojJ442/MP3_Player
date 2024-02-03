// RoundedDlgDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <vector>
#include "Ownshape.h"
#include "vfw.h"
#include "ProsliderCtrl.h"
class CRoundedDlgDlg : public CDialog
{
// Construction
public:
	CRoundedDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ROUNDEDDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stctext;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_bBrush;
	CRect rect;
	CSize sz;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void GetOnlyFileName(char* PathName,char* Dest);
	CListBox m_list;
	afx_msg void OnLbnSelchangeList2();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLbnDblclkList2();
	std::vector<CString> mylist;
	bool m_bmyflag;
	CBitmap m_bmpbuttonplay, m_bmpbuttonstop, m_bmpbuttonpause;
	COwnShape m_btnplay;
	COwnShape m_btnstop;
	afx_msg void OnBnClickedButton1();
	bool m_bPlayStop;
	HWND m_Song;
	afx_msg void OnBnClickedButton3();
	CProSliderCtrl m_Slider;
	int Mp3ORNot(char * FileName);
	int Totaltime, RuningTime;
	char TimeDisp[50];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_stcDuration;
	CStatic m_stcPicCtrl;
	bool m_bPicChangeFlag;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CBitmap m_bmp60per, m_bmpmute, m_bmp30per, m_bmpfullper;
	CStatic m_picIncVol;
	CStatic m_picDecVol;
	int m_nVolFlag;
	bool m_bstopflag,mp3fileflag;
};
