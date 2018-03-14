// imagetrievalDlg.cpp : implementation file

#include "stdafx.h"
#include "Retrieve.h"
#include "imagetrievalDlg.h"
#include "picture.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415926

CString* temp[100];//��������ͼ��·��
CString temp_1[100];//��ʱ��ż�������ͼ��·��
CString strfile;//������ͼ���·��
CString m_strPath;//������·��	
int tempi;//��ʱ�ļ�����ͼ�������
int counts;//������ͼ�������
double pix[1000][1000];//��ǰ����ͼ�������
double feature_shape[8];//������ͼ�����״����
double feature_shape_1[8]; //��ǰ����ͼ�����״����
double feature_color[3][12];//������ͼ�����ɫ����
double feature_color_1[3][12]; //��ǰ����ͼ�����ɫ����
bool open_pic;//���ô�����ͼ���־λ
bool dir;//���ü������־λ
bool color;//������ɫ�����Ƿ�ʹ�ù���־λ
bool shape;//��״�����Ƿ�ʹ�ù���־λ
picture image;//������ɫ����
picture image_color_temp;
picture image_color_1;
picture image_color_2;
picture image_color_3;
picture image_shape;
picture image_shape_temp;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagetrievalDlg dialog

CImagetrievalDlg::CImagetrievalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImagetrievalDlg::IDD, pParent)
	, ccmethod(_T(""))
	, ccper(_T(""))
	, ssper(_T(""))
{
	//{{AFX_DATA_INIT(CImagetrievalDlg)
	//��ʼ��ѡ��ķ���
	ccmethod=("��ɫֱ��ͼ");
	method=1;
	c_per=50;
	s_per=50;
	open_pic=false;
	dir=false;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImagetrievalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImagetrievalDlg)
	//}}AFX_DATA_MAP
	DDX_CBString(pDX, IDC_COMBO1, ccmethod);
	CString str1,str2,str3;
	str1=("��ɫֱ��ͼ");
	str2=("�ۼ�ֱ��ͼ");
	str3=("��ɫ��");
	if(ccmethod==str1)
		c_method=1;
	if(ccmethod==str2)
		c_method=2;
	if(ccmethod==str3)
		c_method=3;
	DDX_Text(pDX, IDC_EDIT2, ccper);
	c_per=atoi(CT2CA(ccper.GetBuffer(ccper.GetLength())));
	DDX_Text(pDX, IDC_EDIT3, ssper);
	s_per=atoi(CT2CA(ssper.GetBuffer(ssper.GetLength())));
}

BEGIN_MESSAGE_MAP(CImagetrievalDlg, CDialog)
	//{{AFX_MSG_MAP(CImagetrievalDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_PATH, OnPath)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_RADIO1, &CImagetrievalDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CImagetrievalDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CImagetrievalDlg::OnBnClickedRadio3)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT2, &CImagetrievalDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CImagetrievalDlg::OnEnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CImagetrievalDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagetrievalDlg message handlers

BOOL CImagetrievalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ������ʾ
	CenterWindow();
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
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	CString str;
	str.Format("��ɫֱ��ͼ");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str);
	str.Format("�ۼ�ֱ��ͼ");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str);
	str.Format("��ɫ��");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str);
	ccper=("50");
	ssper=("50");
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImagetrievalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImagetrievalDlg::OnPaint() 
{
	//ȷ�����������Ƿ�����С����ͼ�껯���Ĵ���
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
		CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImagetrievalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*******************************************************************************************
���ô�����ͼ��
*******************************************************************************************/
void CImagetrievalDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileOpenDlg(TRUE);
	if (fileOpenDlg.DoModal () != IDOK)   return;	
	open_pic=true;//��־λ����Ϊtrue����ʾ������ͼ��������
	CWnd* pWnd = GetDlgItem(IDC_VIEW);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();		
	POSITION pos = fileOpenDlg.GetStartPosition();//����ѡ���˶���ļ�������õ���һ���ļ�λ��
	strfile = fileOpenDlg.GetNextPathName(pos);//�õ�������ͼ���·��
	ShowPic(strfile,IDC_VIEW);	//��ʾ������ͼ��
}
/************************************************************************************
��ʾ������ͼ��
pathfileΪ����ʾ���ļ�·����idcΪͼ����ʾ�ؼ���ID��
************************************************************************************/
void CImagetrievalDlg::ShowPic(CString pathfile, int idc)
{
	CBitmap hbmp;
	HBITMAP hbitmap;  	
	//��pStaticָ��Ҫ��ʾ�ĵط�	
	CStatic *pStaic;  
	pStaic=(CStatic*)GetDlgItem(idc);
	//װ����Դ 
	hbitmap=(HBITMAP)::LoadImage (/*::AfxGetInstanceHandle()*/NULL,pathfile, IMAGE_BITMAP,
		           0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ	
	BITMAP bm;  
	hbmp.GetBitmap(&bm); 	
	//������ʱ���ڴ�DC����
	CDC dcMem;	
	dcMem.CreateCompatibleDC(pStaic->GetDC());	
	CBitmap *poldBitmap=(CBitmap*)dcMem.SelectObject(hbmp);		
	CRect lRect;	
	pStaic->GetClientRect(&lRect);	
	lRect.NormalizeRect();
	//��ʾλͼ	
	pStaic->GetDC()->StretchBlt(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(),		
		&dcMem,0 ,0,bm.bmWidth,bm.bmHeight,SRCCOPY);	
	dcMem.SelectObject(&poldBitmap); 
    pStaic->ReleaseDC(&dcMem);
}
/*************************************************************************************
���ü�����·��
*************************************************************************************/
void CImagetrievalDlg::OnPath() 
{
	// TODO: Add your control notification handler code here
	//��ͨ�öԻ���BROWSEINFO�ṹ�а������û�ѡ��Ŀ¼����Ҫ��Ϣ
	BROWSEINFO browse;
	ZeroMemory(&browse,sizeof(browse));//fills a block of memory with zeros.
	browse.hwndOwner = NULL;
	browse.pszDisplayName = m_strPath.GetBuffer(MAX_PATH);
	browse.lpszTitle = "��ѡ��һ��ͼ��Ŀ¼";
	//SHBrowseForFolder��������һ��ITEMIDLIST�ṹ��ָ�룬�������û�ѡ���ļ��е���Ϣ
	LPITEMIDLIST lpItem = SHBrowseForFolder(&browse);
	if(lpItem == NULL) return ;
	m_strPath.ReleaseBuffer();
	//SHGetPathFromIDList����Ŀ��־���б�ת��Ϊ�ĵ�ϵͳ·��
	if(SHGetPathFromIDList(lpItem,m_strPath.GetBuffer(MAX_PATH)) == false) return;
	m_strPath.ReleaseBuffer();
	dir=true; //��־λ����Ϊtrue����ʾ������ͼ��������
	AfxMessageBox("��ѡ���Ŀ¼Ϊ:"+m_strPath,MB_ICONINFORMATION|MB_OK);	
	//ɨ������⣬�õ�ͼ��Ŀ¼���ļ���·��
	CString tempath;
	CString temps;
	tempath=m_strPath;
	tempath.TrimRight();tempath.TrimLeft(); //ȥ��ǰ�����
	CString strfilepath=tempath;
	tempi=0;
	counts=0;//����������
	//��������ͼ���������counts�У���·������temp[100]��
	StartDir(strfilepath);
    temps.Format("��Ŀ¼�¹���%d��ͼ��!",counts);
    AfxMessageBox(temps,MB_ICONINFORMATION|MB_OK);
}

/***********************************************************************************
ɨ��������е�ͼ�����
**********************************************************************************/
void CImagetrievalDlg::StartDir(const CString &strfile1)
{
	BOOL yesno; 
	CFileFind find;	
	char tempFileFind[200]; 
	sprintf_s(tempFileFind,"%s\\*.*",strfile1);	
	RunDir(strfile1);//�ڵ�ǰĿ¼�в���ͼ�񣬲�������Ŀ¼
	yesno = (BOOL)find.FindFile(tempFileFind); 
	//���ҵ�ǰĿ¼����Ŀ¼�е��ļ�
	while(yesno) 
	{ 
		yesno = find.FindNextFile(); 
		if (find.IsDots() != TRUE)//����ȱʡĿ¼
		{
			char foundFileName[200];
			strcpy_s(foundFileName,find.GetFileName().GetBuffer(200));			
			if((find.IsDirectory() == TRUE)) //�ж��Ƿ�ΪĿ¼
			{ 
				char tempDir[200];
				sprintf_s(tempDir,"%s\\%s",strfile1,foundFileName);//�����Ŀ¼·��
				StartDir(tempDir); 	// �ݹ���ã�������Ŀ¼��ͼ��
			} 			
		}
	}   
	find.Close(); 
	return; 
}
/***********************************************************************************
ɨ�赱ǰĿ¼�е�ͼ�����
**********************************************************************************/
void CImagetrievalDlg::RunDir(const CString &strfile2)
{
	BOOL yesno; 	
	CFileFind find; 
	char tempFileFind[200]; 
	sprintf_s(tempFileFind,"%s\\*.bmp",strfile2); 
	yesno = find.FindFile(tempFileFind); //�ڵ�ǰĿ¼�²���BMP�ļ�
	while(yesno) 
	{ 
		yesno = find.FindNextFile(); 
		char foundFileName[200];//��ʱ�洢���ҵ���ͼ����
		strcpy_s(foundFileName,find.GetFileName().GetBuffer(200));//��ȡͼ����
		if(!find.IsDots()) //����ȱʡĿ¼
		{ 
			char tempFileName[200];
			sprintf_s(tempFileName,"%s\\%s",strfile2,foundFileName);
            CString strfilepath1;
			strfilepath1.Format("%s",tempFileName);//��ȡͼ������·��
			counts++;			
			temp[tempi] = new CString(strfilepath1);//����ͼ������·��
			tempi++;			
		} 
	} 
	find.Close(); 
	return; 
}
/**************************************************************************
��ʼ����
**************************************************************************/
void CImagetrievalDlg::OnStart() 
{
	//����Ƿ������˴�����ͼ��ͼ�����·��
	if(open_pic==false)
	{
		AfxMessageBox("�������ô�����ͼ��");
		return;
	}
	if(dir==false)
	{
		AfxMessageBox("�����ü�����·��");
		return;
	}
	if(method==1)
	{
	switch(c_method)
	{
	case 1:
		general(strfile,1);//��ȡ������ͼ����ɫֱ��ͼ
		break;
	case 2:
		succession(strfile,1);//��ȡ������ͼ���ۼ�ֱ��ͼ
		break;
	case 3:
		centerM(strfile,1);//��ȡ������ͼ����ɫ��
		break;
	}
	Color_SeekImage();//������ɫ���������ƶȼ��㺯��
	}
	if(method==2)
	{
		torque(strfile,1);//��ȡ������ͼ��Ĳ����
		Shape_SeekImage();//������״���������ƶȼ��㺯��
		sort();
	}
	if(method==3)
	{
		torque(strfile,1);
		Shape_SeekImage();
		switch(c_method)
		{
		case 1:
		general(strfile,1);
		break;
		case 2:
		succession(strfile,1);
		break;
		case 3:
		centerM(strfile,1);		
		break;
		}
		Color_SeekImage();
	}
}
/***************************************************************************************
������״���������ƶȼ��㺯��
***************************************************************************************/
void CImagetrievalDlg::Shape_SeekImage()
{
	for(int count=0; count<counts; count++)
		temp_1[count] = *temp[count];
	if(image_shape_temp.strfile_old==strfile&&image_shape_temp.m_strPath_old==m_strPath)
			shape=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
	else
			shape=0;
	for(int pic=0; pic<counts; pic++)//���������������ͼ��
	{
		if(shape==0)
		{
		torque(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ�Ĳ����
		double dis=0;//��N��ͼ�������ͼ��ľ���
		double dis_temp=0;
		//��ʾ���ڼ����ĵ�N��ͼ�������ͼ��ľ���
    	for(int i=0;i<8;i++)
			dis+=fabs((feature_shape_1[i]-feature_shape[i])/fabs(feature_shape[i]));
		image_shape_temp.tp[pic]=temp_1[pic];//�����N��ͼ·��
		image_shape_temp.num[pic]=dis;//�����N��ͼ�������ͼ��ľ���
		}
		ShowPic(temp_1[pic],IDC_VIEW1);
	}
	if(shape==0)//��������Ϊ��һ�μ��㣬�򱣴����ƶȼ�����
		image_shape=image_shape_temp;
	else//���������Ѿ�����������ȡ���ƶȼ�����
		image_shape_temp=image_shape;
	//�������Ĵ�����ͼ�񼰼�����·������
	image_shape_temp.m_strPath_old=m_strPath;
	image_shape_temp.strfile_old=strfile;
}
/**************************************************************************************
������ɫ���������ƶȼ��㺯��
***************************************************************************************/
void CImagetrievalDlg::Color_SeekImage()
{
	for(int count=0; count<counts; count++)
		temp_1[count] = *temp[count];
	switch(c_method)
	{
	case 1:
		if(image_color_1.strfile_old==strfile&&image_color_1.m_strPath_old==m_strPath)
			color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
		else
			color=0;
		break;
	case 2:
		if(image_color_2.strfile_old==strfile&&image_color_2.m_strPath_old==m_strPath)
			color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
		else
			color=0;
		break;
	case 3:
		if(image_color_3.strfile_old==strfile&&image_color_3.m_strPath_old==m_strPath)
			color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷���������Ѿ��ô˷��������
		else
			color=0;
		break;
	}
	for(int pic=0; pic<counts; pic++)//���������������ͼ��
	{
		if(color==0)
		{
			switch(c_method)
			{
			case 1:
			general(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ����ɫֱ��ͼ
			break;
			case 2:
			succession(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ���ۼ�ֱ��ͼ
			break;
			case 3:
			centerM(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ����ɫ��
			break;
			}
			double dis=0;//��N��ͼ�������ͼ��ľ���
			double dis_temp=0;
			//�������ڼ����ĵ�N��ͼ�������ͼ��ľ���
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<12;j++)
					dis_temp+=(feature_color_1[i][j]-feature_color[i][j])*(feature_color_1[i][j]-feature_color[i][j]);
				dis+=sqrt((double)dis_temp);
				dis_temp=0;
			}
			image_color_temp.tp[pic]=temp_1[pic];//�����N��ͼ·��
			image_color_temp.num[pic]=dis;//�����N��ͼ�������ͼ��ľ���
		}
		ShowPic(temp_1[pic],IDC_VIEW1);
	}
	switch(c_method)
	{
	case 1:
		if(color==0)//��������Ϊ��һ�μ��㣬�򱣴����ƶȼ�����
		{
			image_color_1=image_color_temp;
			sort();			
		}
		else//���������Ѿ�����������ȡ���ƶȼ�����
		{
			image_color_temp=image_color_1;
			sort();
		}
		//�������Ĵ�����ͼ�񼰼�����·������
		image_color_1.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_1.strfile_old=image_color_temp.strfile_old=strfile;
		break;
	case 2:
		if(color==0)
		{
			image_color_2=image_color_temp;
			sort();
		}
		else
		{
			image_color_temp=image_color_2;
			sort();
		}
		image_color_2.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_2.strfile_old=image_color_temp.strfile_old=strfile;
		break;
	case 3:
		if(color==0)
		{
			image_color_3=image_color_temp;
			sort();
		}
		else
		{
			image_color_temp=image_color_3;
			sort();
		}
		image_color_3.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_3.strfile_old=image_color_temp.m_strPath_old=strfile;
		break;
	}
}
/***********************************************************************************
��ȡ����غ���
************************************************************************************/
void CImagetrievalDlg::torque(CString pathfile,int mode)
{	
    CBitmap hbmp;
	HBITMAP hbitmap; 
	int R,G,B;
	//װ����Դ
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		           0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//������ʱ���ڴ�DC����
	CDC dcMem;	
	dcMem.CreateCompatibleDC(GetDC());	
	dcMem.SelectObject(hbmp);
	int width=bm.bmWidth;
	int height=bm.bmHeight;
	COLORREF clr;
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			//�ú�������ָ�����������ص�RGB��ɫֵ
			clr=dcMem.GetPixel(x,y);
			R=GetRValue(clr);
			G=GetGValue(clr);
			B=GetBValue(clr);
			pix[x][y]=0.299*R+0.587*G+0.114*B;
		}
	}
	//�������ֵ
	int index_max;//�����ֵ
	double g_max;
	g_max=0;
	for(int index=0;index<256;index++)
	{
		double c0,c1,sum_0,sum_1;
		double w0,w1,u0,u1,g;
		c0=c1=sum_0=sum_1=w0=w1=u0=u1=g=0;
		for(int x=0;x<width;x++)
		{
			for(int y=0;y<height;y++)
			{
				if(pix[x][y]<index)
				{
				sum_0=sum_0+pix[x][y];//ͳ�Ʊ����Ҷ�ֵ
				c0++;                               //ͳ�Ʊ�������ֵ
				}
				else
				{
				sum_1=sum_1+pix[x][y];//ͳ��ǰ���Ҷ�ֵ
				c1++;                               //ͳ��ǰ������ֵ
				}
			}
		}
		w0=c0/(c0+c1);//����������ռ����
		w1=c1/(c0+c1);//ǰ��������ռ����
		if(c0==0)
			u0=0;
		else
			u0=sum_0/c0;//����ƽ���Ҷ�ֵ
		if(c1==0)
			u1=0;
		else
			u1=sum_1/c1;//ǰ��ƽ���Ҷ�ֵ
		g=w0*w1*(u0-u1)*(u0-u1);
		if(g>g_max)//���������ֵ
		{
			g_max=g;
			index_max=index;
		}
	}
	//����������ֵ������ֵ�ָ�
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			if(pix[x][y]<index_max)
				pix[x][y]=0;
			else
				pix[x][y]=1;
		}
	}

	//0+0�׾�
	double m00=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m00+=pix[x][y];
	//1+0�׾�
	double m10=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m10+=(x+1)*pix[x][y];
    //0+1�׾�
	double m01=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m01+=(y+1)*pix[x][y];
	//1+1�׾�
	double m11=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m11+=(y+1)*(x+1)*pix[x][y];
	//2+0�׾�
	double m20=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m20+=(x+1)*(x+1)*pix[x][y];
	//0+2�׾�
	double m02=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m02+=(y+1)*(y+1)*pix[x][y];
	//3+0�׾�
	double m30=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m30+=(x+1)*(x+1)*(x+1)*pix[x][y];
	//0+3�׾�
	double m03=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m03+=(y+1)*(y+1)*(y+1)*pix[x][y];
	//1+2�׾�
	double m12=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m12+=(x+1)*(y+1)*(y+1)*pix[x][y];
	//2+1�׾�
	double m21=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m21+=(x+1)*(x+1)*(y+1)*pix[x][y];

	//��ͼ�����������
	double xbar,ybar;
	xbar=(double)m10/m00;
	ybar=(double)m01/m00;

	//�����ľ�
	double eta11,eta20,eta02,eta30,eta03,eta21,eta12;
	eta11=(m11-ybar*m10)/(m00*m00);
	eta20=(m20-xbar*m10)/(m00*m00);
	eta02=(m02-ybar*m01)/(m00*m00);
	eta30=(m30-3*xbar*m20+2*xbar*xbar*m10)/(m00*m00*sqrt(m00));
	eta03=(m03-3*ybar*m02+2*ybar*ybar*m01)/(m00*m00*sqrt(m00));
	eta21=(m21-2*xbar*m11-ybar*m20+2*xbar*xbar*m01)/(m00*m00*sqrt(m00));
	eta12=(m12-2*ybar*m11-xbar*m02+2*ybar*ybar*m10)/(m00*m00*sqrt(m00));

    //HU�����
	double phi[8];
	phi[0]=eta20+eta02;
	phi[1]=(eta20-eta02)*(eta20-eta02)+(4*eta11*eta11);
	phi[2]=((eta30-3*eta12)*(eta30-3*eta12))+((3*eta21-eta03)*(3*eta21-eta03));
	phi[3]=((eta30+eta12)*(eta30+eta12))+((eta21+eta03)*(eta21+eta03));
	phi[4]=(eta30-3*eta12)*(eta30+eta12)*((eta30+eta12)*(eta30+eta12)-3*(eta21+eta03)*(eta21+eta03)+
		        (3*eta21-eta03)*(eta21+eta03)*(3*(eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03)));
	phi[5]=(eta20-eta02)*((eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03))+
		        4*eta11*(eta30+eta12)*(eta21+eta03);
	phi[6]=(3*eta21-eta03)*(eta30+eta12)*((eta30+eta12)*(eta30+eta12)-3*(eta21+eta03)*(eta21+eta03))+
		        (3*eta12-eta30)*(eta21+eta03)*(3*(eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03)); 
	//ͼ��������
	phi[7]=((eta20-eta02)*(eta20-eta02)+4*eta11*eta11)/((eta20+eta02)*(eta20+eta02));
if(mode==1)
	for(int i=0;i<8;i++)
	{
		phi[i]=fabs(log(fabs(phi[i])));
		feature_shape[i]=phi[i];
	}
else
	for(int i=0;i<8;i++)
	{
		phi[i]=fabs(log(fabs(phi[i])));
		feature_shape_1[i]=phi[i];
	}
}
/***********************************************************************************
������ɫֱ��ͼ
pathfileΪͼ���·����modeΪģʽ״̬λ��Ϊ1ʱ����ʾ������Ǵ�����ͼ��
Ϊ2ʱ����ʾ������Ǽ������е�ͼ��
************************************************************************************/
void CImagetrievalDlg::general(CString pathfile,int mode)
{	
    CBitmap hbmp;
	HBITMAP hbitmap; 
	//װ����Դ
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		           0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//������ʱ���ڴ�DC����
	CDC dcMem;	
	dcMem.CreateCompatibleDC(GetDC());	
	dcMem.SelectObject(hbmp);
	int width=bm.bmWidth;
	int height=bm.bmHeight;
	int totalnum= height *width;
	//��ʼ��
	long m_graph[3][12];
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		{
		   m_graph[i][j]=0;
		   if(mode==1)
			   feature_color[i][j]=0.0;
		   else
			   feature_color_1[i][j]=0.0;
		}
	COLORREF color;
	double h=0,s=0,v=0;
	//������ɫֱ��ͼ
	for(long y=0;y<height;y++)
	{	
		for(long x=0;x<width;x++)
		{			
			color=dcMem.GetPixel(x,y);
			//��ɫ�ռ�ת��
			RGBToHSV(GetRValue(color),GetGValue(color),GetBValue(color),&h,&s,&v);
		    int result_h=(int)(6*h/PI);
			if( result_h ==12)
				m_graph[0][11]++;
			else
        	    m_graph[0][result_h]++;
            int result_s=(int)(s*12);
			if( result_s ==12)
				m_graph[1][11]++;
			else
			    m_graph[1][result_s]++;
            int result_v=(int)(v*12);
			if( result_v ==12)
				m_graph[2][11]++;
			else
			    m_graph[2][result_v]++;
		}
	}
	//������ɫֱ��ͼ
	if(mode==1)
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
	else
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color_1[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
}
/***********************************************************************************
�����ۼ�ֱ��ͼ
pathfileΪͼ���·����modeΪģʽ״̬λ��Ϊ1ʱ����ʾ������Ǵ�����ͼ��
Ϊ2ʱ����ʾ������Ǽ������е�ͼ��
************************************************************************************/
void CImagetrievalDlg::succession(CString pathfile,int mode)
{	
    CBitmap hbmp;
	HBITMAP hbitmap; 
	//װ����Դ
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		          0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//������ʱ���ڴ�DC����
	CDC dcMem;	
	dcMem.CreateCompatibleDC(GetDC());	
	dcMem.SelectObject(hbmp);
	int width=bm.bmWidth;
	int height=bm.bmHeight;
	int totalnum= height *width;

	long m_graph[3][12];
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		{
		   m_graph[i][j]=0;
		   if(mode==1)
			   feature_color[i][j]=0.0;
		   else
			   feature_color_1[i][j]=0.0;
		}
	COLORREF color;
	double h=0,s=0,v=0;

	for(long y=0;y<height;y++)
	{	
		for(long x=0;x<width;x++)
		{			
			color=dcMem.GetPixel(x,y);
			RGBToHSV(GetRValue(color),GetGValue(color),GetBValue(color),&h,&s,&v);
		    int result_h=(int)(6*h/PI);
			if( result_h ==12)
				m_graph[0][11]++;
			else
        	    m_graph[0][result_h]++;

            int result_s=(int)(s*12);
			if( result_s ==12)
				m_graph[1][11]++;
			else
			    m_graph[1][result_s]++;

            int result_v=(int)(v*12);
			if( result_v ==12)
				m_graph[2][11]++;
			else
			    m_graph[2][result_v]++;
		}
	}	
	long temp[3][12];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<12;j++)
		{
		   temp[i][j]=m_graph[i][j];
		}
	}
	for(int i=0;i<3;i++)
	{
       for(int j=0;j<12;j++)
	   {
	      for(int k=0;k<j;k++)
		  {
		     m_graph[i][j]+=temp[i][k];
		  }
	   }
	}
	if(mode==1)
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
	else
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color_1[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
}

/***********************************************************************************
������ɫ��
pathfileΪͼ���·����modeΪģʽ״̬λ��Ϊ1ʱ����ʾ������Ǵ�����ͼ��
Ϊ2ʱ����ʾ������Ǽ������е�ͼ��
************************************************************************************/
void CImagetrievalDlg::centerM(CString pathfile,int mode)
{	
    CBitmap hbmp;
	HBITMAP hbitmap; 
	//װ����Դ
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		          0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//������ʱ���ڴ�DC����
	CDC dcMem;	
	dcMem.CreateCompatibleDC(GetDC());	
	dcMem.SelectObject(hbmp);
	int width=bm.bmWidth;
	int height=bm.bmHeight;
	int totalnum= height *width;

	long m_graph[3][12];
	float m_graphf[3][12];;
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		{
		   m_graph[i][j]=0;
		   m_graphf[i][j]=0.0;
		   if(mode==1)
			   feature_color[i][j]=0.0;
		   else
			   feature_color_1[i][j]=0.0;
		}
	COLORREF color;
	double h=0,s=0,v=0;

	for(long y=0;y<height;y++)
	{	
		for(long x=0;x<width;x++)
		{			
			color=dcMem.GetPixel(x,y);
			RGBToHSV(GetRValue(color),GetGValue(color),GetBValue(color),&h,&s,&v);
		    int result_h=(int)(6*h/PI);
			if( result_h ==12)
				m_graph[0][11]++;
			else
        	    m_graph[0][result_h]++;

            int result_s=(int)(s*12);
			if( result_s ==12)
				m_graph[1][11]++;
			else
			    m_graph[1][result_s]++;

            int result_v=(int)(v*12);
			if( result_v ==12)
				m_graph[2][11]++;
			else
			    m_graph[2][result_v]++;
		}
	}	
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		   m_graphf[i][j]=((float)m_graph[i][j])/((float)totalnum);
	float m1[3],m2[3],m3[3];
	for(int i=0;i<3;i++)
	{
		m1[i] = 0.0;
		m2[i] = 0.0;
		m3[i] = 0.0;
	}
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		m1[i] +=m_graphf[i][j]/12;
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		{
			m2[i] +=((m_graphf[i][j] - m1[i]) * (m_graphf[i][j] - m1[i]))/12;
			m3[i] +=((m_graphf[i][j] - m1[i]) * (m_graphf[i][j] - m1[i])
				* (m_graphf[i][j] - m1[i]))/12;
		}
	float zz=1/3;
    for(int i=0;i<3;i++)
	{
		m2[i] = sqrtf(m2[i]);
		m3[i] = (float)pow( m3[i], zz );
	}
	if(mode==1)
	{
	feature_color[0][0]=m1[0]; feature_color[0][1]=m2[0]; feature_color[0][2]=m3[0];
	feature_color[1][0]=m1[1]; feature_color[1][1]=m2[1]; feature_color[1][2]=m3[1];
	feature_color[2][0]=m1[2]; feature_color[2][1]=m2[2]; feature_color[2][2]=m3[2];
	}
	else
	{
	feature_color_1[0][0]=m1[0]; feature_color_1[0][1]=m2[0]; feature_color_1[0][2]=m3[0];
	feature_color_1[1][0]=m1[1]; feature_color_1[1][1]=m2[1]; feature_color_1[1][2]=m3[1];
	feature_color_1[2][0]=m1[2]; feature_color_1[2][1]=m2[2]; feature_color_1[2][2]=m3[2];
	}
}
/*******************************************************************************
RGB�ռ���HSV�ռ��ת��
*********************************************************************************/
void CImagetrievalDlg::RGBToHSV(int r,int g,int b,double *h,double *s,double *v)
{
	*h=acos((r-g+r-b)/(2.0*sqrtf((float)(r-g)*(r-g)+(float)(r-b)*(g-b))));
	if(b>g)
		*h=2*PI-*h;
    *s=(mymax(r,g,b)-mymin(r,g,b))/(float)mymax(r,g,b);
	*v=mymax(r,g,b)/255.0;
}

int CImagetrievalDlg::mymax(int a,int b,int c)//Ѱ�����
{
	int m;
	if(a>b)
		m=a;
	else
		m=b;
	if(m<c)
		m=c;
	return m;
}

int CImagetrievalDlg::mymin(int a,int b,int c)//Ѱ����С
{
	int m;
	if(a<b)
		m=a;
	else 
		m=b;
	if(m>c)
		m=c;
	return m;
}

/*******************************************************************************
���������ʾ
*********************************************************************************/
void CImagetrievalDlg::sort()
{
	int  picnum=1009;//ͼ����ʾ�ؼ���ID��
	if(method==1)
	{
		CString tp;//ͼ��·��
		double  num;//ͼ���������ͼ��ľ���
		//ͼ�����ƶ�����
		for(int i=0;i<counts;i++)
		{
			for(int j=i+1;j<counts;j++)
			{
				if(image_color_temp.num[i]>image_color_temp.num[j])
				{
					tp=image_color_temp.tp[i];
					num=image_color_temp.num[i];
					image_color_temp.tp[i]=image_color_temp.tp[j];
					image_color_temp.num[i]=image_color_temp.num[j];
					image_color_temp.tp[j]=tp;
					image_color_temp.num[j]=num;
				}}}
		//��ʾǰʮ�����ƶ���ߵ�ͼ��
		for(int i=0;i<10&&picnum<=1018;i++)
		{
			ShowPic(image_color_temp.tp[i],picnum);
			picnum++;
		}
	}
	if(method==2)
	{
		CString tp;//ͼ��·��
		double  num;//ͼ���������ͼ��ľ���
		//ͼ�����ƶ�����
		for(int i=0;i<counts;i++)
		{
			for(int j=i+1;j<counts;j++)
			{
				if(image_shape_temp.num[i]>image_shape_temp.num[j])
				{
					tp=image_shape_temp.tp[i];
					num=image_shape_temp.num[i];
					image_shape_temp.tp[i]=image_shape_temp.tp[j];
					image_shape_temp.num[i]=image_shape_temp.num[j];
					image_shape_temp.tp[j]=tp;
					image_shape_temp.num[j]=num;
				}}}
		//��ʾǰʮ�����ƶ���ߵ�ͼ��
		for(int i=0;i<10&&picnum<=1018;i++)
		{
			ShowPic(image_shape_temp.tp[i],picnum);
			picnum++;
		}
	}
	if(method==3)
	{
		CString tp;//ͼ��·��
		double  num;//ͼ���������ͼ��ľ���
		//ͼ�����ƶ�����
		for(int i=0;i<counts;i++)//�ۺ��������ƶ�
		{
			image.num[i]=(c_per*image_color_temp.num[i]+s_per*image_shape_temp.num[i])/100;
			image.tp[i]=image_color_temp.tp[i];
		}
		for(int i=0;i<counts;i++)
		{
			for(int j=i+1;j<counts;j++)
			{
				if(image.num[i]>image.num[j])
				{
					tp=image.tp[i];
					num=image.num[i];
					image.tp[i]=image.tp[j];
					image.num[i]=image.num[j];
					image.tp[j]=tp;
					image.num[j]=num;
				}}}
		//��ʾǰʮ�����ƶ���ߵ�ͼ��
		for(int i=0;i<10&&picnum<=1018;i++)
		{
			ShowPic(image.tp[i],picnum);
			picnum++;
		}
	}
}
void CImagetrievalDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	method=1;
}

void CImagetrievalDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	method=2;
}

void CImagetrievalDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	method=3;
}
void CImagetrievalDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	s_per=100-c_per;
	ssper.Format("%d",s_per);
	UpdateData(FALSE);
}

void CImagetrievalDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	c_per=100-s_per;
	ccper.Format("%d",c_per);
	UpdateData(FALSE);
}
void CImagetrievalDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
}
