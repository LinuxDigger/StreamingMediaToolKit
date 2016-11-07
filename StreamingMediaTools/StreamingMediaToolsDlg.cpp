
// StreamingMediaToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StreamingMediaTools.h"
#include "StreamingMediaToolsDlg.h"
#include "afxdialogex.h"
#include "pxCommonDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CStreamingMediaToolsDlg �Ի���
CStreamingMediaToolsDlg::CStreamingMediaToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStreamingMediaToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
}

void CStreamingMediaToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINTAB,   m_TabCtrl);
	DDX_Control(pDX, IDC_LIST_INFO, m_listboxLogInfo);
}

BEGIN_MESSAGE_MAP(CStreamingMediaToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TEST,          &CStreamingMediaToolsDlg::OnBnClickedButtonTest)
	ON_NOTIFY(NM_CLICK, IDC_MAINTAB,        &CStreamingMediaToolsDlg::OnNMClickTab1)
	ON_MESSAGE(WM_ADD_LOG_TO_LIST,          &CStreamingMediaToolsDlg::AddLog2List)
	ON_BN_CLICKED(IDC_CHECK_CLEAR_LOG_LIST, &CStreamingMediaToolsDlg::OnClearLogList)
END_MESSAGE_MAP()


// CStreamingMediaToolsDlg ��Ϣ��������

BOOL CStreamingMediaToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ȡ������ľ��
	CWnd *pWnd  = AfxGetMainWnd();
	pWnd->GetWindowText(g_strAppTitle);
	g_hAppWnd = ::FindWindow(NULL, g_strAppTitle);

	Init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStreamingMediaToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStreamingMediaToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStreamingMediaToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStreamingMediaToolsDlg::OnNMClickTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int index = m_TabCtrl.GetCurSel();

	switch(index)
	{
	case 0:
		m_pRTMPAnalyzerDlg->ShowWindow(SW_SHOW);
		m_pRTSPAnalyzerDlg->ShowWindow(SW_HIDE);

		break;

	case 1:
		m_pRTMPAnalyzerDlg->ShowWindow(SW_HIDE);
		m_pRTSPAnalyzerDlg->ShowWindow(SW_SHOW);

		break;

		/*default:
		m_pRTMPAnalyzerDlg->ShowWindow(SW_SHOW);
		m_pRTMPAnalyzerDlg->ShowWindow(SW_HIDE);

		break;*/
	}

	*pResult = 0;
}

void CStreamingMediaToolsDlg::Init()
{
	m_TabCtrl.InsertItem(0, _T("RTMP"));
	m_TabCtrl.InsertItem(1, _T("RTSP"));

	// ����RTMP ��������
	m_pRTMPAnalyzerDlg = new CPxRTMPAnalyzerDlg;
	int bret = m_pRTMPAnalyzerDlg->Create(IDD_PAGE_RTMP, GetDlgItem(IDC_MAINTAB));
	if (FALSE == bret)
	{
		AfxMessageBox(_T("����RTMP �����Ի���ʧ��"));

		return ;
	}

	// ����RTSP ��������
	m_pRTSPAnalyzerDlg = new CPxRTSPAnalyzerDlg;
	bret = m_pRTSPAnalyzerDlg->Create(IDD_PAGE_RTSP, GetDlgItem(IDC_MAINTAB));
	if (FALSE == bret)
	{
		AfxMessageBox(_T("����RTSP �����Ի���ʧ��"));

		return ;
	}

	CRect rtTabClient;
	m_TabCtrl.GetClientRect(&rtTabClient);
	rtTabClient.top += 30;
	rtTabClient.bottom -= 30;
	rtTabClient.left += 1;
	rtTabClient.right -= 2;

	m_pRTMPAnalyzerDlg->MoveWindow(&rtTabClient,FALSE);
	m_pRTSPAnalyzerDlg->MoveWindow(&rtTabClient,FALSE);

	// ��ʾĬ�Ͻ���
	m_pRTMPAnalyzerDlg->ShowWindow(SW_SHOW);
	m_pRTSPAnalyzerDlg->ShowWindow(SW_HIDE);

	::InitializeCriticalSection(&m_csListBox);   //��ʼ���ٽ���
}

void CStreamingMediaToolsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pRTSPAnalyzerDlg)
	{
		m_pRTSPAnalyzerDlg->DestroyWindow();
		delete m_pRTSPAnalyzerDlg;
		m_pRTSPAnalyzerDlg = NULL;
	}

	if (m_pRTMPAnalyzerDlg)
	{
		m_pRTMPAnalyzerDlg->DestroyWindow();
		delete m_pRTMPAnalyzerDlg;
		m_pRTMPAnalyzerDlg = NULL;
	}

	::DeleteCriticalSection(&m_csListBox);    //�ͷ����ٽ���
}

LRESULT CStreamingMediaToolsDlg::AddLog2List( WPARAM wParam, LPARAM lParam )
{
	::EnterCriticalSection(&m_csListBox); 

	char *pszMsg = (char *)lParam;

	CString strMsg;
	strMsg.Format("%s", pszMsg);
	if (strMsg == "")
	{
		::LeaveCriticalSection(&m_csListBox); 

		return -1;
	}

	CString strGmt = "[" + GetCurTime();
	strGmt += "] ";
	CString strLine = strGmt + strMsg;

	m_listboxLogInfo.AddString(strLine);

	int nCount = m_listboxLogInfo.GetCount();
	if (nCount > 0)
	{
		m_listboxLogInfo.SetCurSel(nCount - 1); 
	}

	g_logFile.WriteLogInfo(strMsg);

	::LeaveCriticalSection(&m_csListBox); 

	return 0;
}

// �����־�б�
void CStreamingMediaToolsDlg::OnClearLogList()
{
	//UpdateData();
	if (((CButton *)GetDlgItem(IDC_CHECK_CLEAR_LOG_LIST))->GetCheck() == BST_CHECKED)
	{
		m_listboxLogInfo.ResetContent();
	}
	//UpdateData(FALSE);
}


void CStreamingMediaToolsDlg::OnBnClickedButtonTest()
{
	// ����������־��listbox
	TestAddLog();
}

// test unit - TestAddLog
void CStreamingMediaToolsDlg::TestAddLog()
{
	g_strMsg = "#1 CStreamingMediaToolsDlg::TestAddLog() \
#2 CStreamingMediaToolsDlg::TestAddLog() \
#3 CStreamingMediaToolsDlg::TestAddLog() \
#4 CStreamingMediaToolsDlg::TestAddLog()";

	::PostMessage(g_hAppWnd, WM_ADD_LOG_TO_LIST, NULL, (LPARAM)g_strMsg.GetBuffer());
}

