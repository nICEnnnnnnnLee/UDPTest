// UDPToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDPTool.h"
#include "UDPToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDPToolDlg dialog
//全局变量
udp_conn udp;
HANDLE hThread;
bool isTxHex=false;
bool isRxHex=false;
bool isToUpdateRx=false;
bool isListening=true;
bool isSendByPeriod=false;
CString recvMsg;
CString appendMsg;
//CUDPToolDlg *ui;
void udp_process(void* p) //线程函数  
{
	CUDPToolDlg *ui = (CUDPToolDlg*)(p);
	//myUI->m_Send_period=1000;
	//PostMessage(ui->m_hWnd,MYMSG,NULL,NULL);
    while(isListening){
		MsgData data=udp.recvMsg();
		if(data.msgLen<=0)
            continue;
		if(!isRxHex){
			recvMsg=data.msg;
			ui->m_Rx_Text+=(recvMsg);
			appendMsg=recvMsg;
			isToUpdateRx=true;
			//PostMessage(ui->m_hWnd,MYMSG,NULL,NULL);
		}else{
			char rmsg[1024];
			Hex2Str(data.msg,rmsg,data.msgLen);
			rmsg[data.msgLen*2]='\0';
			ui->m_Rx_Text+=rmsg;
			appendMsg=rmsg;
			isToUpdateRx=true;
			//PostMessage(ui->m_hWnd,MYMSG,NULL,NULL);
		}
	}
	udp.closeUDP();
}  

void udp_sendByPeriod(void* p) //线程函数  
{
	CUDPToolDlg *ui = (CUDPToolDlg*)(p);
    while(isSendByPeriod){
		PostMessage(ui->m_hWnd,SEND_BY_PERIOD,NULL,NULL);
		Sleep(ui->m_Send_period);
	}
} 

CUDPToolDlg::CUDPToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDPToolDlg)
	m_Dest_ip = _T("127.0.0.1");
	m_Dest_port=5004;
	m_Local_port=5005;
	m_Send_period=100;
	m_Rx_Text = _T("");
	m_Tx_Text = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDPToolDlg)
	DDX_Control(pDX, IDC_RX_TEXT, m_Edit_Rx);
	DDX_Control(pDX, IDC_STOP_UDP, m_Stop_udp);
	DDX_Control(pDX, IDC_START_UDP, m_Start_udp);
	DDX_Text(pDX, IDC_DEST_IP, m_Dest_ip);
	DDX_Text(pDX, IDC_DEST_PORT, m_Dest_port);
	DDX_Text(pDX, IDC_LOCAL_PORT, m_Local_port);
	DDX_Text(pDX, IDC_SEND_PERIOD, m_Send_period);
	DDX_Text(pDX, IDC_RX_TEXT, m_Rx_Text);
	DDX_Text(pDX, IDC_TX_TEXT, m_Tx_Text);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDPToolDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPToolDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STOP_UDP, OnStopUdp)
	ON_BN_CLICKED(IDC_START_UDP, OnStartUdp)
	ON_MESSAGE(MYMSG,OnMsgBack)
	ON_BN_CLICKED(IDC_IS_TX_HEX, OnIsTxHex)
	ON_BN_CLICKED(IDC_IS_RX_HEX, OnIsRxHex)
	ON_BN_CLICKED(IDC_CLEAR_TX, OnClearTx)
	ON_BN_CLICKED(IDC_CLEAR_RX, OnClearRx)
	ON_BN_CLICKED(IDC_SEND_BTN, OnSendBtn)
	ON_MESSAGE(SEND_BY_PERIOD,SendMsg)
	ON_BN_CLICKED(IDC_IS_AUTO_SEND, OnIsAutoSend)

	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPToolDlg message handlers

BOOL CUDPToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetWindowText(_T("UDP测试工具"));
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//ui=this;
	// TODO: Add extra initialization here
	//GetDlgItem(IDC_STOP_UDP)->
	//UpdateData(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDPToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDPToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDPToolDlg::OnStopUdp() 
{
	// TODO: Add your control notification handler code here
	isListening=false;
	Sleep(500);
	m_Stop_udp.EnableWindow(false);
	m_Start_udp.EnableWindow(true);
	GetDlgItem(IDC_DEST_IP)->EnableWindow(true);
	GetDlgItem(IDC_DEST_PORT)->EnableWindow(true);
	GetDlgItem(IDC_LOCAL_PORT)->EnableWindow(true);
	KillTimer(REFRESH_TIMER_ID);
	MessageBox("关闭UDP链接！");
}

void CUDPToolDlg::OnStartUdp() 
{
	//port
	char pp[16];
	GetDlgItemText(IDC_LOCAL_PORT,pp,16);
	int port=atoi(pp);

	if(udp.bindUDP(port)){
		isListening=true;
		hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)udp_process,(void *)(this),0,NULL);
		CloseHandle(hThread);
		//GetDlgItem(IDC_STOP_UDP)->EnableWindow(true);
		m_Stop_udp.EnableWindow(true);//与上句注释等同
		m_Start_udp.EnableWindow(false);
		GetDlgItem(IDC_DEST_IP)->EnableWindow(false);
		GetDlgItem(IDC_DEST_PORT)->EnableWindow(false);
		GetDlgItem(IDC_LOCAL_PORT)->EnableWindow(false);
		SetTimer(REFRESH_TIMER_ID,100,0);
	}else{
		udp.closeUDP();
		MessageBox("创建UDP连接失败！",NULL,MB_OK);		
	}
	
}
void CUDPToolDlg::OnMsgBack()
{
	SetDlgItemText(IDC_RX_TEXT,m_Rx_Text);
}

void CUDPToolDlg::OnIsTxHex() 
{
	if(isTxHex){
		isTxHex=false;
	}else{
		isTxHex=true;
	}	
}

void CUDPToolDlg::OnIsRxHex() 
{
	if(isRxHex){
		isRxHex=false;
	}else{
		isRxHex=true;
	}	
}

void CUDPToolDlg::OnClearTx() 
{
	m_Rx_Text="";
	SetDlgItemText(IDC_TX_TEXT,"");	
}

void CUDPToolDlg::OnClearRx() 
{
	m_Rx_Text="";
	SetDlgItemText(IDC_RX_TEXT,"");	
}

void CUDPToolDlg::OnSendBtn() 
{
	//ip
	char text[128];
	GetDlgItemText(IDC_DEST_IP,text,128);
	char* ip=(LPSTR)(LPCTSTR)text;
	//port
	char pp[16];
	GetDlgItemText(IDC_DEST_PORT,pp,16);
	int port=atoi(pp);
	
	//msg
	char buf[1024];
	GetDlgItemText(IDC_TX_TEXT,buf,1024);
	if(isTxHex){
        const int len=(strlen(buf)+1)/2;
        unsigned char tmsg[1024];
        HexStrToByte(buf,tmsg,strlen(buf));
        udp.sendMsg(ip,port,(char*)tmsg,len);
    }else{
        udp.sendMsg(ip,port,buf,strlen(buf));
    }
}
void CUDPToolDlg::SendMsg() 
{
	//period
	char tt[16];
	GetDlgItemText(IDC_SEND_PERIOD,tt,16);
	int period=atoi(tt);
	this->m_Send_period=period;
	//ip
	char text[128];
	GetDlgItemText(IDC_DEST_IP,text,128);
	char* ip=(LPSTR)(LPCTSTR)text;
	//port
	char pp[16];
	GetDlgItemText(IDC_DEST_PORT,pp,16);
	int port=atoi(pp);
	
	//msg
	char buf[1024];
	GetDlgItemText(IDC_TX_TEXT,buf,1024);
	if(isTxHex){
        const int len=(strlen(buf)+1)/2;
        unsigned char tmsg[1024];
        HexStrToByte(buf,tmsg,strlen(buf));
        udp.sendMsg(ip,port,(char*)tmsg,len);
    }else{
        udp.sendMsg(ip,port,buf,strlen(buf));
    }
}

void CUDPToolDlg::OnIsAutoSend() 
{
	if(isSendByPeriod){
		isSendByPeriod=false;
		KillTimer(TIMERID);
		GetDlgItem(IDC_SEND_PERIOD)->EnableWindow(true);
		GetDlgItem(IDC_SEND_BTN)->EnableWindow(true);
	}else{
		isSendByPeriod=true;
		//hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)udp_sendByPeriod,(void *)(this),0,NULL);
		//CloseHandle(hThread);
		//period
		char tt[16];
		GetDlgItemText(IDC_SEND_PERIOD,tt,16);
		int period=atoi(tt);
		this->m_Send_period=period;
		SetTimer(TIMERID,period,0);

		GetDlgItem(IDC_SEND_PERIOD)->EnableWindow(false);
		GetDlgItem(IDC_SEND_BTN)->EnableWindow(false);
	}
}
void CUDPToolDlg::OnTimer(UINT_PTR nIDEvent){
	if(nIDEvent==TIMERID)
		SendMsg();
	else if(nIDEvent==REFRESH_TIMER_ID){
		if(isToUpdateRx){
			int nLength = m_Edit_Rx.SendMessage(WM_GETTEXTLENGTH);
			m_Edit_Rx.SetSel(nLength, nLength);
			m_Edit_Rx.ReplaceSel(appendMsg);
			if(nLength>1024*4){
				m_Edit_Rx.SetSel(0, appendMsg.GetLength());
				m_Edit_Rx.ReplaceSel("");
			}
			//SetDlgItemText(IDC_RX_TEXT,m_Rx_Text);
			m_Edit_Rx.LineScroll(m_Edit_Rx.GetLineCount());
			isToUpdateRx=false;
		}else{

		}
		
		//CEdit* m_edit=(CEdit*)GetDlgItem(IDC_RX_TEXT);
		//m_edit->LineScroll(m_edit->GetLineCount());
		//	
	}
}
