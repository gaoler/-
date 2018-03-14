// imagetrievalDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_IMAGETRIEVALDLG_H__DBC9776B_CE72_40E6_980C_002B809850AC__INCLUDED_)
#define AFX_IMAGETRIEVALDLG_H__DBC9776B_CE72_40E6_980C_002B809850AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImagetrievalDlg dialog

class CImagetrievalDlg : public CDialog
{
// Construction
public:
	CImagetrievalDlg(CWnd* pParent = NULL);	// standard constructor
	void torque(CString pathfile,int mode);
	void general(CString pathfile,int mode);
	void succession(CString pathfile,int mode);
	void centerM(CString pathfile,int mode);
	void RGBToHSV(int r,int g,int b,double *h,double *s,double *v);
	int mymin(int,int,int);
	int mymax(int,int,int);
	void sort();
// Dialog Data
	//{{AFX_DATA(CImagetrievalDlg)
	enum { IDD = IDD_IMAGETRIEVAL_DIALOG };

	int	method;//ͼ��������ȡģʽ
	int	c_method;//������ɫ����ģʽ�µķ���ѡ��
	CString ccmethod;//������ɫ����ģʽ�µķ���ѡ���������

	CString ccper;//��ɫ��ռ�ٷֱȵĹ�������
	int c_per;//��ɫ��ռ�ٷֱ�
	CString ssper;//��״��ռ�ٷֱȵĹ�������
	int s_per;//��״��ռ�ٷֱ�
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagetrievalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CImagetrievalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnPath();
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Shape_SeekImage();	
	void Color_SeekImage();
	void RunDir(const CString &strfile2);
	void StartDir(const CString &strfile1);
	void ShowPic(CString pathfile, int idc);
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnCbnSelchangeCombo1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGETRIEVALDLG_H__DBC9776B_CE72_40E6_980C_002B809850AC__INCLUDED_)
