// imagetrieval.h : main header file for the IMAGETRIEVAL application
//

#if !defined(AFX_IMAGETRIEVAL_H__DCC8137E_268D_43B9_9282_3E55CFEC3DB7__INCLUDED_)
#define AFX_IMAGETRIEVAL_H__DCC8137E_268D_43B9_9282_3E55CFEC3DB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImagetrievalApp:
// See imagetrieval.cpp for the implementation of this class
//

class CImagetrievalApp : public CWinApp
{
public:
	CImagetrievalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagetrievalApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImagetrievalApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGETRIEVAL_H__DCC8137E_268D_43B9_9282_3E55CFEC3DB7__INCLUDED_)
