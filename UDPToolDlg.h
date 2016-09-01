// UDPToolDlg.h : header file
//

#if !defined(AFX_UDPTOOLDLG_H__56DD6E81_19AD_48E9_A34B_EF6D42C19BDD__INCLUDED_)
#define AFX_UDPTOOLDLG_H__56DD6E81_19AD_48E9_A34B_EF6D42C19BDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MYMSG WM_USER +200
#define SEND_BY_PERIOD WM_USER +201
#include "funcs.h"
#include "afxmt.h"

#define TIMERID 8
#define REFRESH_TIMER_ID 9
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUDPToolDlg dialog

class CUDPToolDlg : public CDialog
{
// Construction
public:
	CUDPToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUDPToolDlg)
	enum { IDD = IDD_UDPTOOL_DIALOG };
	CEdit	m_Edit_Rx;
	CButton	m_Stop_udp;
	CButton	m_Start_udp;
	CString	m_Dest_ip;
	int		m_Dest_port;
	int		m_Local_port;
	int		m_Send_period;
	CString	m_Rx_Text;
	CString	m_Tx_Text;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUDPToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStopUdp();
	afx_msg void OnStartUdp();
	afx_msg void OnMsgBack();
	afx_msg void OnIsTxHex();
	afx_msg void OnIsRxHex();
	afx_msg void OnClearTx();
	afx_msg void OnClearRx();
	afx_msg void OnSendBtn();
	afx_msg void SendMsg();
	afx_msg void OnIsAutoSend();

	afx_msg void OnTimer(UINT_PTR nIDEvent); //回调函数,这里的函数名OnTimer不能换成其他名字.固定的
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPTOOLDLG_H__56DD6E81_19AD_48E9_A34B_EF6D42C19BDD__INCLUDED_)
