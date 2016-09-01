// UDPTool.h : main header file for the UDPTOOL application
//
#include "udp.h"
#include "iostream.h"
#if !defined(AFX_UDPTOOL_H__EDA6380D_020B_4497_B3A5_2F66BE66C1B7__INCLUDED_)
#define AFX_UDPTOOL_H__EDA6380D_020B_4497_B3A5_2F66BE66C1B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDPToolApp:
// See UDPTool.cpp for the implementation of this class
//

class CUDPToolApp : public CWinApp
{
public:
	CUDPToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDPToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPTOOL_H__EDA6380D_020B_4497_B3A5_2F66BE66C1B7__INCLUDED_)
