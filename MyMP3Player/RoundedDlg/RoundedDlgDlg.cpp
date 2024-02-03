// RoundedDlgDlg.cpp : implementation file
/*===========================================================================
====                                                                     ====
====    File name           :  RoundedDlgDlg.cpp                           ====
====    Creation date       :  7/10/2023                                 ====
====    Author(s)           :  Manoj J                               ====
====                                                                     ====
===========================================================================*/


#include "stdafx.h"
#include "RoundedDlg.h"
#include "RoundedDlgDlg.h"
#include <list>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRoundedDlgDlg dialog




CRoundedDlgDlg::CRoundedDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoundedDlgDlg::IDD, pParent)
{
	m_bmyflag = FALSE;
	m_bPlayStop = TRUE;
	Totaltime = 0;
	m_bPicChangeFlag = FALSE;
	m_nVolFlag = 2;
	m_bstopflag = TRUE;
	mp3fileflag = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoundedDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_stctext);


	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_btnplay);
	DDX_Control(pDX, IDC_BUTTON3, m_btnstop);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Control(pDX, IDC_STATIC_TEXT_TIME, m_stcDuration);
	DDX_Control(pDX, IDC_STATIC_PIC, m_stcPicCtrl);
	DDX_Control(pDX, IDC_STATIC_INCVOL, m_picIncVol);
	DDX_Control(pDX, IDC_STATIC_DECVOL, m_picDecVol);
}

BEGIN_MESSAGE_MAP(CRoundedDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST2, &CRoundedDlgDlg::OnLbnSelchangeList2)
	ON_LBN_DBLCLK(IDC_LIST2, &CRoundedDlgDlg::OnLbnDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON1, &CRoundedDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CRoundedDlgDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRoundedDlgDlg message handlers

BOOL CRoundedDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CDialog::DragAcceptFiles();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	m_bmpmute.LoadBitmap(IDB_BITMAP7);
	m_bmp60per.LoadBitmapA(IDB_BITMAP3);
	m_bmp30per.LoadBitmapA(IDB_BITMAP10);
	m_bmpfullper.LoadBitmapA(IDB_BITMAP11);

	m_Slider.EnableWindow(FALSE);
	//Dialog cut in Ellipse shape
	CRect rect;
	GetWindowRect(rect);
	CClientDC * m_clientDC;
	CRgn m_rgn;
	m_clientDC = new CClientDC(this);
	m_clientDC->BeginPath();
	m_clientDC->Ellipse(rect.left,rect.top,rect.Width(),rect.Height()); 
	m_clientDC->EndPath();
	m_rgn.CreateFromPath(m_clientDC);
	SetWindowRgn((HRGN) m_rgn,TRUE);

	CString Text("Manoj MP3 Player");
	m_stctext.SetWindowText(Text);

	CFont m_Font;
	m_Font.CreatePointFont(0, _T("Arial"));
	m_stctext.SetFont(&m_Font);
	m_list.AddString("Bhahubali.mp3");
	m_list.SetCurSel(0);

	m_bmpbuttonplay.LoadBitmap(IDB_BITMAP4);
	m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonplay.GetSafeHandle()));
	m_bmpbuttonstop.LoadBitmap(IDB_BITMAP5);
	m_btnstop.SetBitmap(HBITMAP(m_bmpbuttonstop.GetSafeHandle()));
	m_bmpbuttonpause.LoadBitmap(IDB_BITMAP6);
	MCIWndSetVolume(m_Song, 600);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRoundedDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRoundedDlgDlg::OnPaint()
{
	Invalidate(FALSE);
	CPaintDC dc(this); // device context for painting
	CBitmap m_Bmap;
  	CRect rect;
	HDC memdc;
	
	GetClientRect(&rect);
	
	m_Bmap.LoadBitmap(IDB_BITMAP1);
	memdc=::CreateCompatibleDC(dc.m_hDC);
	::SelectObject(memdc,m_Bmap);
	BitBlt(dc.m_hDC,0,0,rect.right,rect.bottom,memdc,0,0,SRCCOPY);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRoundedDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CRoundedDlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
		if(nCtlColor == CTLCOLOR_STATIC)
		{
			m_bBrush.CreateStockObject(HOLLOW_BRUSH);
		    pDC->SetBkMode(TRANSPARENT);
		    pDC->SetTextColor(RGB(255,255,255));// white
		    return (HBRUSH)m_bBrush;
		}
	 
		if(nCtlColor == CTLCOLOR_LISTBOX)
		{
			m_bBrush.CreateStockObject(HOLLOW_BRUSH);
            pDC->SetBkMode(TRANSPARENT);
		    pDC->SetTextColor(RGB(0,255,0));
		    return (HBRUSH)m_bBrush;
			
		}
       
		 
}

void CRoundedDlgDlg::OnDropFiles(HDROP hDropInfo)
{
	char sFile[500],Dest[300];
	int nFiles = 0;
	if(m_bmyflag == FALSE)
	m_list.DeleteString(0);
    m_bmyflag = TRUE;
	
	//MCIWndStop(m_Song);
	m_btnplay.EnableWindow(TRUE);
	nFiles = DragQueryFile(hDropInfo,//Identifier of the structure that contains the file names of the dropped files.
				  -1,//Index of the file to query
				  sFile,//The address of a buffer that receives the file name of a dropped file when the function returns. 
						 //This file name is a null-terminated string.
				  MAX_PATH//The size, in characters, of the lpszFile buffer.
					);
	for(int i = 0;i<nFiles;i++)
	{
		    DragQueryFile(hDropInfo,i,sFile,MAX_PATH);
			Mp3ORNot(sFile);
			if(mp3fileflag == TRUE)
			{
			mylist.push_back(sFile);
			GetOnlyFileName(sFile,Dest);
			//m_list.SetCurSel(m_list.AddString(Dest));
			m_list.AddString(Dest);
			Invalidate(FALSE);
			mp3fileflag = FALSE;
			}
	}
	 //m_Song = MCIWndCreate(this->GetSafeHwnd(), AfxGetInstanceHandle(), WS_CHILD,sFile);
	 //MCIWndPlay(m_Song);
	 //Totaltime = MCIWndGetLength(m_Song)/1000;
	 //m_Slider._SetRange32(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the progress bar
	 //m_Slider.SetRange(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the Slider ctrl
	 //m_Slider.EnableWindow(TRUE);
	 //SetTimer(100,1000,NULL);
	// m_stctext.SetWindowText(Dest);
	if(m_list.GetCount()== 0||m_list.GetCurSel() == -1)
	m_list.SetCurSel(0);

	CDialog::OnDropFiles(hDropInfo);
}
void CRoundedDlgDlg::GetOnlyFileName(char* PathName,char* Dest)
{
	int len = strlen(PathName);
	int j = 0;
//////***********************************************************
	//This code for get only the file name from sFile string
	for(int i = len-1;i>=0;i--,j++)
	{
		if(!(PathName[i] == '\\'))
			Dest[j] = PathName[i];
		else
			break;
	}

	Dest[j] = '\0';
	strrev(Dest);
}

void CRoundedDlgDlg::OnLbnSelchangeList2()
{
	/*char temp[200];
	int index = m_list.GetCurSel();
	m_list.GetText(index,temp);
	m_stctext.SetWindowText(temp);*/
	Invalidate(FALSE);
}

BOOL CRoundedDlgDlg::PreTranslateMessage(MSG* pMsg)
{
	int index =m_list.GetCurSel();
	int last = m_list.GetCount();
    if(pMsg->message == WM_MOUSEWHEEL)
	{
		int moment = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		if(moment>0)
		
			if(index>0)
		{
			m_list.SetCurSel(index-1);
			char temp[200];
			int index = m_list.GetCurSel();
			m_list.GetText(index,temp);
			m_stctext.SetWindowText(temp);
			Invalidate(FALSE);
			
		}
		
		if(moment <0)
		if(index<last-1)
		{
			m_list.SetCurSel(index+1);
			char temp[200];
			int index = m_list.GetCurSel();
			m_list.GetText(index,temp);
			m_stctext.SetWindowText(temp);
			Invalidate(FALSE);
			
		}
		
	}
	
   if (pMsg->message == WM_MOUSEMOVE && (pMsg->wParam  )) 
    { 
		Invalidate(FALSE);
        CPoint p; 
        GetCursorPos(&p); 
        CRect r; 
        GetWindowRect(&r); 
        if (r.PtInRect(p)) 
        { 
            ReleaseCapture(); 
            SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
            SendMessage(WM_NCLBUTTONUP, HTCAPTION, 0);
            return 1;
        }
	}
   CWnd *pWnd;
   pWnd = GetDlgItem(IDC_LIST2);
   pWnd->GetWindowRect(rect);

   if((pMsg->message == WM_MBUTTONDOWN)||(pMsg->wParam == VK_DELETE) && (pMsg->pt.x>rect.left && pMsg->pt.x<rect.right && pMsg->pt.y>rect.top && pMsg->pt.y<rect.bottom))
   {
	   CString str;
	   int index = m_list.GetCurSel();
	   if(index>=0)
	   {
	   mylist.erase (mylist.begin()+index);
	   m_list.DeleteString(index);
	   m_list.SetCurSel(index);
	   index = m_list.GetCurSel();
	   if(index!=-1)
	   {
	   m_list.GetText(index,str);
	   m_stctext.SetWindowText(str);
	   }
	   else
	   {
		   m_list.SetCurSel(m_list.GetCount()-1);
		   if(m_list.GetCurSel()!=-1)
		   m_list.GetText(m_list.GetCurSel(),str);
	       m_stctext.SetWindowText(str);

	   }
	   Invalidate(FALSE);

	   }


   }
   
   pWnd = GetDlgItem(IDC_SLIDER1);
	pWnd->GetWindowRect(&rect);
	if(pMsg->message == WM_LBUTTONUP && pMsg->pt.x>rect.left&&pMsg->pt.x<rect.right&&pMsg->pt.y>rect.top&&pMsg->pt.y<rect.bottom)
		
	{
		if(m_Song!=NULL)
		{
		long pos = m_Slider.GetPos();
		m_Slider._SetPos(pos);
		MCIWndPlayFrom(m_Song,pos);//The MCIWndPlayFrom macro plays the content of an MCI device from the specified location to the end of the content
		}
	}

	pWnd = GetDlgItem(IDC_STATIC_PIC);
	pWnd->GetWindowRect(&rect);
	if(pMsg->message == WM_LBUTTONDOWN && pMsg->pt.x>rect.left&&pMsg->pt.x<rect.right&&pMsg->pt.y>rect.top&&pMsg->pt.y<rect.bottom)
		
	{
		if(m_bPicChangeFlag == FALSE)
		{
			m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			m_bPicChangeFlag = TRUE;
			
		}
		else if(m_bPicChangeFlag == TRUE)
		{
			m_stcPicCtrl.SetBitmap(m_bmp60per);
			m_bPicChangeFlag = FALSE;
			switch(m_nVolFlag)
		{
		case 0:m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			break;
			case 1:m_stcPicCtrl.SetBitmap(m_bmp30per);
				MCIWndSetVolume(m_Song, 300);
			break;
			case 2:m_stcPicCtrl.SetBitmap(m_bmp60per);
				MCIWndSetVolume(m_Song, 600);
			break;
			case 3:m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
			break;
			default:m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
				m_nVolFlag = 3;
			break;
		}
		}
	}

	pWnd = GetDlgItem(IDC_STATIC_INCVOL);
	pWnd->GetWindowRect(&rect);
	if(pMsg->message == WM_LBUTTONDOWN && pMsg->pt.x>rect.left&&pMsg->pt.x<rect.right&&pMsg->pt.y>rect.top&&pMsg->pt.y<rect.bottom)
	
	{
		m_nVolFlag++;
		switch(m_nVolFlag)
		{
		case 0:m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			break;
			case 1:m_stcPicCtrl.SetBitmap(m_bmp30per);
				MCIWndSetVolume(m_Song, 300);
			break;
			case 2:m_stcPicCtrl.SetBitmap(m_bmp60per);
				MCIWndSetVolume(m_Song, 600);
			break;
			case 3:m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
			break;
			default:m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
				m_nVolFlag = 3;
			break;
		}
	}

	pWnd = GetDlgItem(IDC_STATIC_DECVOL);
	pWnd->GetWindowRect(&rect);
	if(pMsg->message == WM_LBUTTONDOWN && pMsg->pt.x>rect.left&&pMsg->pt.x<rect.right&&pMsg->pt.y>rect.top&&pMsg->pt.y<rect.bottom)
		
	{
		m_nVolFlag--;
		switch(m_nVolFlag)
		{
		case 0:m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			break;
			case 1:m_stcPicCtrl.SetBitmap(m_bmp30per);
				MCIWndSetVolume(m_Song, 300);
			break;
			case 2:m_stcPicCtrl.SetBitmap(m_bmp60per);
				MCIWndSetVolume(m_Song, 600);
			break;
			case 3:m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
			break;
			default:m_stcPicCtrl.SetBitmap(m_bmpmute);
				MCIWndSetVolume(m_Song, 0);
				m_nVolFlag = 0;
			break;
		}

	}
	return 0;
}

void CRoundedDlgDlg::OnLbnDblclkList2()
{
	MCIWndStop(m_Song);
	m_bstopflag = FALSE;
	if(m_bmyflag == FALSE)
	{
		char temp[300];
		GetCurrentDirectory(MAX_PATH,temp);
		strcat(temp,"\\Bhahubali.mp3");
	   // ShellExecute(NULL, "open",temp , NULL, NULL, SW_SHOWNORMAL);
		m_Song = MCIWndCreate(this->GetSafeHwnd(), AfxGetInstanceHandle(), WS_CHILD,temp);
		switch(m_nVolFlag)
		{
		case 0://m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			break;
			case 1://m_stcPicCtrl.SetBitmap(m_bmp30per);
				MCIWndSetVolume(m_Song, 300);
			break;
			case 2://m_stcPicCtrl.SetBitmap(m_bmp60per);
				MCIWndSetVolume(m_Song, 600);
			break;
			case 3://m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
			break;
		}
	    MCIWndPlay(m_Song);
		Totaltime = MCIWndGetLength(m_Song)/1000;
	 m_Slider._SetRange32(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the progress bar
	 m_Slider.SetRange(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the Slider ctrl
	 m_Slider.EnableWindow(TRUE);
	 SetTimer(100,1000,NULL);
		m_list.DeleteString(0);
		m_stctext.SetWindowText("");
		m_bmyflag ==TRUE;
		m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonpause.GetSafeHandle()));
		m_bPlayStop = FALSE;
		Invalidate(FALSE);
	}
	else
	{
	int index = m_list.GetCurSel();
	//ShellExecute(NULL, "open",mylist.at(index) , NULL, NULL, SW_SHOWNORMAL);
	 m_Song = MCIWndCreate(this->GetSafeHwnd(), AfxGetInstanceHandle(), WS_CHILD,mylist.at(index));
	 switch(m_nVolFlag)
		{
		case 0://m_stcPicCtrl.SetBitmap(m_bmpmute);
			MCIWndSetVolume(m_Song, 0);
			break;
			case 1://m_stcPicCtrl.SetBitmap(m_bmp30per);
				MCIWndSetVolume(m_Song, 300);
			break;
			case 2://m_stcPicCtrl.SetBitmap(m_bmp60per);
				MCIWndSetVolume(m_Song, 600);
			break;
			case 3://m_stcPicCtrl.SetBitmap(m_bmpfullper);
				MCIWndSetVolume(m_Song, 1000);
			break;
		}
	 MCIWndPlay(m_Song);
	 Totaltime = MCIWndGetLength(m_Song)/1000;
	 m_Slider._SetRange32(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the progress bar
	 m_Slider.SetRange(0,MCIWndGetLength(m_Song));//Sets the upper and lower limits of the Slider ctrl
	 m_Slider.EnableWindow(TRUE);
	 SetTimer(100,1000,NULL);
	 char temp[200];
	//int index = m_list.GetCurSel();
	m_list.GetText(index,temp);
	m_stctext.SetWindowText(temp);
	Invalidate(FALSE);
	m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonpause.GetSafeHandle()));
		m_bPlayStop = FALSE;
	}
}

void CRoundedDlgDlg::OnBnClickedButton1()
{
	if(m_bstopflag == TRUE)
	{
		if(m_list.GetCurSel()!= -1)
		{
			OnLbnDblclkList2();
		}
		else
		MessageBox("No song for play");
		//m_bstopflag = FALSE;
		m_bstopflag = FALSE;
		return;
	}
	if(m_bPlayStop == TRUE)
	{
		m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonpause.GetSafeHandle()));
		MCIWndResume(m_Song);
		m_bPlayStop = FALSE;
		
	}
	else if(m_bPlayStop == FALSE)
	{
		m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonplay.GetSafeHandle()));
		MCIWndPause(m_Song);
		m_bPlayStop = TRUE;
	}
}

void CRoundedDlgDlg::OnBnClickedButton3()
{
	MCIWndStop(m_Song);
	if(m_Song !=NULL)
	{
		MCIWndDestroy(m_Song);
		m_btnplay.SetBitmap(HBITMAP(m_bmpbuttonplay.GetSafeHandle()));
		m_bPlayStop = TRUE;
		m_bstopflag = TRUE;
	}
}

int CRoundedDlgDlg::Mp3ORNot(char * FileName)
{
	//CString File(FileName);
	//int len = File.GetLength();
	//strrev(FileName);
	int len = strlen(FileName);
	if(FileName[len - 1] == '3')
	{
		//MessageBox("Mp3 File");
		mp3fileflag = TRUE;
	}
	return 0;
}

void CRoundedDlgDlg::OnTimer(UINT_PTR nIDEvent)
{
	RuningTime = MCIWndGetPosition(m_Song)/1000;
	MCIWndSetTimeFormat(m_Song ,"ms");
	Totaltime = MCIWndGetLength(m_Song)/1000;
	sprintf(TimeDisp, "%02u:%02u:%02u/%02u:%02u:%02u",(RuningTime/3600)%60, (RuningTime/60)%60, (RuningTime%60),(Totaltime/3600)%60, (Totaltime/60)%60, (Totaltime%60));
	m_stcDuration.SetWindowText(TimeDisp);
	Invalidate(FALSE);
	m_Slider.SetPos(MCIWndGetPosition(m_Song));//Move the slider control according to song. MCIWndGetPosition macro retrieves the numerical value of 
	                                          //the current position within the content of the MCI device
	m_Slider._SetPos(MCIWndGetPosition(m_Song));
	if(Totaltime == RuningTime)
	{
		if(m_bstopflag == FALSE)
		{
		int index = m_list.GetCurSel();
		m_list.SetCurSel(index+1);
		Invalidate(FALSE);
		if(m_list.GetCount() != index+1)
		OnLbnDblclkList2();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CRoundedDlgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect picrect;
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_PIC);
	pWnd->GetWindowRect(picrect);
	if( point.x>picrect.left&&point.x<picrect.right&&point.y>picrect.top&&point.y<picrect.bottom)
		
	{
		MessageBox("Clicked");
	}
	CDialog::OnLButtonDown(nFlags, point);
}
