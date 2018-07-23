
// XML_Operate_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XML_Operate_MFC.h"
#include "XML_Operate_MFCDlg.h"
#include "afxdialogex.h"
#include <afx.h>
#include <iostream>
#include <io.h>
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/*****************************ȫ�ֱ���************************************/

vector<string> g_strAllRightFilePath;

/*****************************ȫ�ֱ���************************************/



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
RESULT_TYPE_E LoadXmlFile(const char *szFilePath, TiXmlElement *pRoot)
{

	return RESULT_SUCCESS;
}

void dir(string path)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
	// \\* ����Ҫ�������е�����
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do
	{
		//�ж��ļ����������ļ��л����ļ�
		cout << fileInfo.name << (fileInfo.attrib&_A_SUBDIR ? "[folder]" : "[file]") << endl;
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return;
}

void getFiles(string path, vector<string>& files, vector<string> &ownname)
{
	/*files�洢�ļ���·��������(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	ownnameֻ�洢�ļ�������(eg.     data1.txt)*/

	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{  /*
			   if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
			   getFiles( p.assign(path).append("\\").append(fileinfo.name), files, ownname ); */
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				ownname.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void listFiles(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // ����Ŀ¼�еĵ�һ���ļ�
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}

	do
	{
		if (findData.attrib & _A_SUBDIR
			&& strcmp(findData.name, ".") == 0
			&& strcmp(findData.name, "..") == 0
			)    // �Ƿ�����Ŀ¼���Ҳ�Ϊ"."��".."
			cout << findData.name << "\t<dir>\n";
		else
			cout << findData.name << "\t" << findData.size << endl;
	} while (_findnext(handle, &findData) == 0);    // ����Ŀ¼�е���һ���ļ�

	cout << "Done!\n";
	_findclose(handle);    // �ر��������
}

void   visit(string path, string FileName)
{

	struct _finddata_t   filefind;
	string  curr = path + "\\*.*";

	int   done = 0, i, handle;
	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)
	{
		cerr << "can not match the folder path" << endl;
		exit(-1);
	}
	do {
		//�ж��Ƿ�����Ŀ¼
		if (_A_SUBDIR == filefind.attrib)
		{
			//���������Ҫ
			if ((strcmp(filefind.name, ".") != 0) && (strcmp(filefind.name, "..") != 0))
			{
				curr = path + "\\" + filefind.name;
				cout << "folder:			" << curr << endl;
				//				<span style = "color:#ff0000;">visit(curr, ++layer); < / span>
				string sTempPath = path + "\\" + filefind.name;
				visit(sTempPath, FileName);
			}


		}
		else
		{
			cout << path + "\\" + filefind.name << endl;
			if (0 == strcmp(filefind.name, FileName.data()))
			{
				cout << "******************find config.xml" << endl;
				string strTempFilePath = (path + "\\" + filefind.name);
				cout << strTempFilePath << endl;
				g_strAllRightFilePath.push_back(strTempFilePath);
			}
		}
	} while (_findnext(handle, &filefind) == 0);

	_findclose(handle);
}
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXML_Operate_MFCDlg �Ի���



CXML_Operate_MFCDlg::CXML_Operate_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XML_OPERATE_MFC_DIALOG, pParent)
	, m_FilePath(_T("E:\\ConfigFile"))
	, m_FileName(_T("config.xml"))
	, m_NodePath(_T("Node1;Node12;Node121;value1"))
	, m_NodeValueNow(_T("0"))
	, m_NodeValueNew(_T("0"))
	, m_OperationRecord(_T("������¼��\r\n-----------------------------------------------------------------------\r\n"))
	, m_NewNodeName(_T("Something"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXML_Operate_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_PATH, m_FilePath);
	DDV_MaxChars(pDX, m_FilePath, 1000);
	DDX_Text(pDX, IDC_FILE_NAME, m_FileName);
	DDX_Text(pDX, IDC_NODE_PATH, m_NodePath);
	DDX_Text(pDX, IDC_NODE_VALUE_NOW, m_NodeValueNow);
	DDX_Text(pDX, IDC_NODE_VALUE_NEW, m_NodeValueNew);
	DDX_Control(pDX, IDC_FILE_PATH, m_EditFilePath);
	DDX_Control(pDX, IDC_FILE_NAME, m_EditFileName);
	DDX_Control(pDX, IDC_NODE_PATH, m_EditNodePath);
	DDX_Control(pDX, IDC_NODE_VALUE_NOW, m_EditNodeValueNow);
	DDX_Control(pDX, IDC_NODE_VALUE_NEW, m_EditNodeValueNew);
	DDX_Control(pDX, IDC_OPERATION_RECORD, m_EditOperationRecord);
	DDX_Text(pDX, IDC_OPERATION_RECORD, m_OperationRecord);
	DDX_Control(pDX, IDC_NEW_NODE_NAME, m_EditNewNodeName);
	DDX_Text(pDX, IDC_NEW_NODE_NAME, m_NewNodeName);
}

BEGIN_MESSAGE_MAP(CXML_Operate_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET_NODE_VALUE, &CXML_Operate_MFCDlg::OnBnClickedGetNodeValue)
	ON_BN_CLICKED(IDC_CHANGE_NODE_VALUE, &CXML_Operate_MFCDlg::OnBnClickedChangeNodeValue)
	ON_BN_CLICKED(IDC_ADD_NODE, &CXML_Operate_MFCDlg::OnBnClickedAddNode)
	ON_BN_CLICKED(IDC_DEL_NODE, &CXML_Operate_MFCDlg::OnBnClickedDelNode)
END_MESSAGE_MAP()


// CXML_Operate_MFCDlg ��Ϣ�������

BOOL CXML_Operate_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXML_Operate_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXML_Operate_MFCDlg::OnPaint()
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
HCURSOR CXML_Operate_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXML_Operate_MFCDlg::OnBnClickedGetNodeValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(true);
	g_strAllRightFilePath.clear();
	TiXmlElement *pRoot = NULL;
	RESULT_TYPE_E enRet = (RESULT_TYPE_E)0;

	CString strFilePath;
	m_EditFilePath.GetWindowTextW(strFilePath);
	int len = strFilePath.GetLength();
	char *szFilePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFilePath, 0, len + 1);
	char szTempFilePath[0x100];
	::wsprintfA(szTempFilePath, "%ls", (LPCTSTR)strFilePath);
	szFilePath = szTempFilePath;

	CString strFileName;
	m_EditFileName.GetWindowTextW(strFileName);
	len = strFileName.GetLength();
	char *szFileName = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFileName, 0, len + 1);
	char szTempFileName[0x100];
	::wsprintfA(szTempFileName, "%ls", (LPCTSTR)strFileName);
	szFileName = szTempFileName;

	CString strNodePath;
	m_EditNodePath.GetWindowTextW(strNodePath);
	len = strNodePath.GetLength();
	char *szNodePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodePath, 0, len + 1);
	char szTempNodePath[0x100];
	::wsprintfA(szTempNodePath, "%ls", (LPCTSTR)strNodePath);
	szNodePath = szTempNodePath;

	visit(szFilePath, szFileName);
	TiXmlDocument *stXmlFile = new TiXmlDocument;
	for (int i = 0; i < g_strAllRightFilePath.size(); i++)
	{
		cout << g_strAllRightFilePath[i] << endl;
		const char *chTempFilePath = (g_strAllRightFilePath[i].data());
		if (!stXmlFile->LoadFile(chTempFilePath))
		{
			MessageBox(_T("Load File Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}
		pRoot = stXmlFile->FirstChildElement();
		if (NULL == pRoot)
		{
			MessageBox(_T("Find Root Element Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}

		char *szElementValue = (char *)malloc(sizeof(char) * MAX_NODE_VALUE_LENGTH);

		enRet = GetValueFromXmlFile(pRoot, szNodePath, szElementValue);
		if (RESULT_SUCCESS == enRet)
		{
//			CString cstrOutPutString = _T("hello\nworld347\n");
//			GetDlgItem(IDC_EDIT_OPERATION_RECORD)->SetWindowText(cstrOutPutString);
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Get <%S> From <%s> Success, Value is:[%s]\r\n", strNodePath, g_strAllRightFilePath[i].data(), szElementValue);
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}
		else
		{
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Get <%S> From <%s> Fail! Err Code is:%d\r\n", strNodePath, g_strAllRightFilePath[i].data(), enRet);
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}
		//	m_EditNodeValueNow.SetWindowTextW(LPCTSTR(szElementValue));
		//	string strElementValue = szElementValue;
		CString strElementValue(szElementValue);
		GetDlgItem(IDC_NODE_VALUE_NOW)->SetWindowText(strElementValue);
		GetDlgItem(IDC_NODE_VALUE_NOW)->UpdateWindow();
		if (NULL != szElementValue)
		{
			free(szElementValue);
			szElementValue = NULL;
		}
	}
	MessageBox(_T("Get Value From XML Files Finish!"), _T("Finish"), MB_OK);
	if (NULL != stXmlFile)
	{
		delete stXmlFile;
		stXmlFile = NULL;
	}
}

void CXML_Operate_MFCDlg::OnBnClickedChangeNodeValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	g_strAllRightFilePath.clear();
	TiXmlElement *pRoot = NULL;
	RESULT_TYPE_E enRet = (RESULT_TYPE_E)0;

	CString strFilePath;
	m_EditFilePath.GetWindowTextW(strFilePath);
	int len = strFilePath.GetLength();
	char *szFilePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFilePath, 0, len + 1);
	char szTempFilePath[0x100];
	::wsprintfA(szTempFilePath, "%ls", (LPCTSTR)strFilePath);
	szFilePath = szTempFilePath;

	CString strFileName;
	m_EditFileName.GetWindowTextW(strFileName);
	len = strFileName.GetLength();
	char *szFileName = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFileName, 0, len + 1);
	char szTempFileName[0x100];
	::wsprintfA(szTempFileName, "%ls", (LPCTSTR)strFileName);
	szFileName = szTempFileName;

	CString strNodePath;
	m_EditNodePath.GetWindowTextW(strNodePath);
	len = strNodePath.GetLength();
	char *szNodePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodePath, 0, len + 1);
	char szTempNodePath[0x100];
	::wsprintfA(szTempNodePath, "%ls", (LPCTSTR)strNodePath);
	szNodePath = szTempNodePath;

	CString strNodeValueNew;
	m_EditNodeValueNew.GetWindowTextW(strNodeValueNew);
	len = strNodeValueNew.GetLength();
	char *szNodeValueNew = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodeValueNew, 0, len + 1);
	char szTempNodeValueNew[0x100];
	::wsprintfA(szTempNodeValueNew, "%ls", (LPCTSTR)strNodeValueNew);
	szNodeValueNew = szTempNodeValueNew;

	visit(szFilePath, szFileName);
	
//	TiXmlDocument *stXmlFile = new TiXmlDocument[MAX_FILE_NUM];
	for (int i = 0; i < g_strAllRightFilePath.size(); i++)
	{
		
		const char *chTempFilePath = (g_strAllRightFilePath[i].data());
		TiXmlDocument *stXmlFile = new TiXmlDocument(chTempFilePath);
		do
		{
			if (!stXmlFile->LoadFile())
			{
				MessageBox(_T("Load File Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
				break;
			}
			pRoot = stXmlFile->FirstChildElement();
			if (NULL == pRoot)
			{
				MessageBox(_T("Find Root Element Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
				break;
			}
			enRet = SetValueToXmlFile(pRoot, szNodePath, szNodeValueNew);
			if (RESULT_SUCCESS != enRet)
			{
				char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
				sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Set <%S> To <%s> Fail! Err Code is:%d\r\n", strNodePath, g_strAllRightFilePath[i].data(), enRet);
				m_OperationRecord += chTempOperationRecord;
				GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
				m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				UpdateData(false);
				break;
			}
			else
			{
				char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
				sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Set <%S> To <%s> Success!\r\n", strNodePath, g_strAllRightFilePath[i].data());
				m_OperationRecord += chTempOperationRecord;
				GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
				m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
				UpdateData(false);
				break;
			}
			stXmlFile->SaveFile();
			if (NULL != stXmlFile)
			{
				delete stXmlFile;
				stXmlFile = NULL;
			}
		} while (0);
		
	}
//	delete[]stXmlFile;
	UpdateData(false);
	MessageBox(_T("Set Value To XML Files Finish!"), _T("Finish"), MB_OK);
}

void CXML_Operate_MFCDlg::OnBnClickedAddNode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	g_strAllRightFilePath.clear();
	TiXmlElement *pRoot = NULL;
	RESULT_TYPE_E enRet = (RESULT_TYPE_E)0;

	CString strFilePath;
	m_EditFilePath.GetWindowTextW(strFilePath);
	int len = strFilePath.GetLength();
	char *szFilePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFilePath, 0, len + 1);
	char szTempFilePath[0x100];
	::wsprintfA(szTempFilePath, "%ls", (LPCTSTR)strFilePath);
	szFilePath = szTempFilePath;

	CString strFileName;
	m_EditFileName.GetWindowTextW(strFileName);
	len = strFileName.GetLength();
	char *szFileName = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFileName, 0, len + 1);
	char szTempFileName[0x100];
	::wsprintfA(szTempFileName, "%ls", (LPCTSTR)strFileName);
	szFileName = szTempFileName;

	CString strNodePath;
	m_EditNodePath.GetWindowTextW(strNodePath);
	len = strNodePath.GetLength();
	char *szNodePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodePath, 0, len + 1);
	char szTempNodePath[0x100];
	::wsprintfA(szTempNodePath, "%ls", (LPCTSTR)strNodePath);
	szNodePath = szTempNodePath;

	CString strNodeValueNew;
	m_EditNodeValueNew.GetWindowTextW(strNodeValueNew);
	len = strNodeValueNew.GetLength();
	char *szNodeValueNew = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodeValueNew, 0, len + 1);
	char szTempNodeValueNew[0x100];
	::wsprintfA(szTempNodeValueNew, "%ls", (LPCTSTR)strNodeValueNew);
	szNodeValueNew = szTempNodeValueNew;

	CString strNewNodeName;
	m_EditNewNodeName.GetWindowTextW(strNewNodeName);
	len = strNewNodeName.GetLength();
	char *szNewNodeName = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNewNodeName, 0, len + 1);
	char szTempNewNodeName[0x100];
	::wsprintfA(szTempNewNodeName, "%ls", (LPCTSTR)strNewNodeName);
	szNewNodeName = szTempNewNodeName;

	visit(szFilePath, szFileName);
	for (int i = 0; i < g_strAllRightFilePath.size(); i++)
	{
		const char *chTempFilePath = (g_strAllRightFilePath[i].data());
		TiXmlDocument *stXmlFile = new TiXmlDocument(chTempFilePath);
		if (!stXmlFile->LoadFile())
		{
			MessageBox(_T("Load File Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}
		pRoot = stXmlFile->FirstChildElement();
		if (NULL == pRoot)
		{
			MessageBox(_T("Find Root Element Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}

		enRet = AddNodeToXml(pRoot, szNodePath, szNewNodeName, szNodeValueNew);
		if (RESULT_SUCCESS != enRet)
		{
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Add <%S> To <%s> Fail! Err Code is:%d\r\n", strNodePath, g_strAllRightFilePath[i].data(), enRet);
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}
		else
		{
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Add <%S> To <%s> Success!\r\n", strNodePath, g_strAllRightFilePath[i].data());
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}

		stXmlFile->SaveFile();
		if (NULL != stXmlFile)
		{
			delete stXmlFile;
			stXmlFile = NULL;
		}
	}
	UpdateData(false);
	MessageBox(_T("Add Node To XML Files Finish!"), _T("Finish"), MB_OK);
}


void CXML_Operate_MFCDlg::OnBnClickedDelNode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	g_strAllRightFilePath.clear();
	TiXmlElement *pRoot = NULL;
	RESULT_TYPE_E enRet = (RESULT_TYPE_E)0;

	CString strFilePath;
	m_EditFilePath.GetWindowTextW(strFilePath);
	int len = strFilePath.GetLength();
	char *szFilePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFilePath, 0, len + 1);
	char szTempFilePath[0x100];
	::wsprintfA(szTempFilePath, "%ls", (LPCTSTR)strFilePath);
	szFilePath = szTempFilePath;

	CString strFileName;
	m_EditFileName.GetWindowTextW(strFileName);
	len = strFileName.GetLength();
	char *szFileName = (char *)malloc(sizeof(char) * (len + 1));
	memset(szFileName, 0, len + 1);
	char szTempFileName[0x100];
	::wsprintfA(szTempFileName, "%ls", (LPCTSTR)strFileName);
	szFileName = szTempFileName;

	CString strNodePath;
	m_EditNodePath.GetWindowTextW(strNodePath);
	len = strNodePath.GetLength();
	char *szNodePath = (char *)malloc(sizeof(char) * (len + 1));
	memset(szNodePath, 0, len + 1);
	char szTempNodePath[0x100];
	::wsprintfA(szTempNodePath, "%ls", (LPCTSTR)strNodePath);
	szNodePath = szTempNodePath;

	visit(szFilePath, szFileName);
	for (int i = 0; i < g_strAllRightFilePath.size(); i++)
	{
		const char *chTempFilePath = (g_strAllRightFilePath[i].data());
		TiXmlDocument *stXmlFile = new TiXmlDocument(chTempFilePath);
		if (!stXmlFile->LoadFile())
		{
			MessageBox(_T("Load File Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}
		pRoot = stXmlFile->FirstChildElement();
		if (NULL == pRoot)
		{
			MessageBox(_T("Find Root Element Fail!"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		}

		enRet = DelNodeFromXml(pRoot, szNodePath);
		if (RESULT_SUCCESS != enRet)
		{
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Delete <%S> From <%s> Fail! Err Code is:%d\r\n", strNodePath, g_strAllRightFilePath[i].data(), enRet);
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}
		else
		{
			char *chTempOperationRecord = (char *)malloc(sizeof(char) * (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM));
			sprintf_s(chTempOperationRecord, (MAX_NODE_PATH_LENGTH + MAX_FILE_NUM), "Delete <%S> From <%s> Success!\r\n", strNodePath, g_strAllRightFilePath[i].data());
			m_OperationRecord += chTempOperationRecord;
			GetDlgItem(IDC_OPERATION_RECORD)->UpdateWindow();
			m_EditOperationRecord.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
			UpdateData(false);
		}

		stXmlFile->SaveFile();

		if (NULL != stXmlFile)
		{
			delete stXmlFile;
			stXmlFile = NULL;
		}
	}
	UpdateData(false);
	MessageBox(_T("Delete Node From XML Files Finish!"), _T("Finish"), MB_OK);
	
}

//���ݽڵ�·���ַ������ҵ���Ҫ�Ľڵ�
TiXmlElement *FindElementByStr(TiXmlElement *pRoot, const char *szNodePath)
{
	if (NULL == pRoot || NULL == szNodePath)
	{
		return NULL;
	}
	char str[MAX_NODE_PATH_LENGTH];/*���ָ���ԭ�ַ���*/
	cout << strlen(szNodePath) << endl;
	strncpy_s(str, strlen(szNodePath) + 1, szNodePath, strlen(szNodePath));
	char seg[] = ";"; /*�ָ�������Ϊ����comma���ָ�������Ϊ��ָ���ģ���ֺţ��ո��*/
	char charlist[MAX_NODE_DEEP][MAX_NODE_NAME_LENGTH] = { "" };/*ָ���ָ������ַ����洢��λ�ã����ﶨ���ά�ַ�������*/
	int i = 0;
	char *pTempContext;
	char *substr = strtok_s(str, seg, &pTempContext);/*�����ֳɵķָ��,substrΪ�ָ���������ַ���*/

	TiXmlElement *pNode[MAX_NODE_DEEP];
	pNode[0] = pRoot;

	while (substr != NULL) {
		strncpy_s(charlist[i], MAX_NODE_NAME_LENGTH, substr, MAX_NODE_NAME_LENGTH - 1);/*���·ָ���������ַ���substr������Ҫ�洢��charlsit��*/
		pNode[i + 1] = pNode[i]->FirstChildElement(charlist[i]);
		if (pNode[i + 1] == nullptr)
			return NULL;
		i++;
		printf("%s\n", substr);
		substr = strtok_s(NULL, seg, &pTempContext);/*�ڵ�һ�ε���ʱ��strtok()����������str�ַ�����
													����ĵ����򽫲���str���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣*/
	}
	TiXmlElement *pTempElement = (TiXmlElement *)malloc(sizeof(TiXmlElement));

	memcpy_s(pTempElement, sizeof(TiXmlElement), pNode[i], sizeof(TiXmlElement));
	//	pTempElement = pNode[i];
	return pTempElement;
}

RESULT_TYPE_E GetValueFromXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue)
{

	TiXmlElement *pElement = NULL;
	pElement = FindElementByStr(pRoot, szNodePath);
	if (NULL == pElement)
	{
		cout << "GetValueFromXmlFile, can not find " << szNodePath << endl;
		return RESULT_CANNOT_FIND_ELEMENT;
	}
	strncpy_s(szElementValue, MAX_NODE_VALUE_LENGTH, pElement->GetText(), MAX_NODE_VALUE_LENGTH);

	if (NULL != pElement)
	{
		free(pElement);
	}
	return RESULT_SUCCESS;

}

RESULT_TYPE_E SetValueToXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue)
{
	if (NULL == pRoot || NULL == szNodePath)
	{
		return RESULT_NULL_POINT;
	}
	char str[MAX_NODE_PATH_LENGTH];//���ָ���ԭ�ַ���
	cout << strlen(szNodePath) << endl;
	strncpy_s(str, strlen(szNodePath) + 1, szNodePath, strlen(szNodePath));
	char seg[] = ";"; //�ָ�������Ϊ����comma���ָ�������Ϊ��ָ���ģ���ֺţ��ո��
	char charlist[MAX_NODE_DEEP][MAX_NODE_NAME_LENGTH] = { "" };//ָ���ָ������ַ����洢��λ�ã����ﶨ���ά�ַ�������
	int i = 0;
	char *pTempContext;
	char *substr = strtok_s(str, seg, &pTempContext);//�����ֳɵķָ��,substrΪ�ָ���������ַ���

	TiXmlNode  *pNode[MAX_NODE_DEEP];
	pNode[0] = pRoot;

	while (substr != NULL) {
		strncpy_s(charlist[i], MAX_NODE_NAME_LENGTH, substr, MAX_NODE_NAME_LENGTH - 1);//���·ָ���������ַ���substr������Ҫ�洢��charlsit��
		pNode[i + 1] = pNode[i]->FirstChild(charlist[i]);
		if (pNode[i + 1] == nullptr)
			return RESULT_CANNOT_FIND_ELEMENT;
		i++;
		substr = strtok_s(NULL, seg, &pTempContext);//�ڵ�һ�ε���ʱ��strtok()����������str�ַ���������ĵ����򽫲���str���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣
	}
	cout << pNode[i - 1]->Value() << endl << pNode[i]->Value() << endl;
	TiXmlElement* RightElement = NULL;
	RightElement = pNode[i]->ToElement();
	pNode[i] = RightElement->FirstChild();
	TiXmlText  newText(szElementValue);
	RightElement->ReplaceChild(pNode[i], newText);
	return RESULT_SUCCESS;
}

RESULT_TYPE_E AddNodeToXml(TiXmlElement *pRoot, const char *szNodePath, const char *szNodeName, const char *szValue)
{
	TiXmlElement *pElement = NULL;
	pElement = FindElementByStr(pRoot, szNodePath);
	if (NULL == pElement)
	{
		cout << "GetValueFromXmlFile, can not find " << szNodePath << endl;
		return RESULT_CANNOT_FIND_ELEMENT;
	}
	// �����ӽڵ㣺pNewNode
	TiXmlElement *pNewNode = new TiXmlElement(szNodeName);
	if (NULL == pNewNode)
	{
		return RESULT_FAIL;
	}
	// ���ýڵ��ı���Ȼ�����ڵ�
	TiXmlText *pNewValue = new TiXmlText(szValue);
	pNewNode->LinkEndChild(pNewValue);
	
	pElement->LinkEndChild(pNewNode);
	
	if (NULL == pElement)
	{
		return RESULT_FAIL;
	}
	return RESULT_SUCCESS;
}

//ɾ���ڵ�
RESULT_TYPE_E DelNodeFromXml(TiXmlElement *pRoot, const char *szNodePath)
{
	if (NULL == pRoot || NULL == szNodePath)
	{
		return RESULT_NULL_POINT;
	}
	char str[MAX_NODE_PATH_LENGTH];//���ָ���ԭ�ַ���
	cout << strlen(szNodePath) << endl;
	strncpy_s(str, strlen(szNodePath) + 1, szNodePath, strlen(szNodePath));
	char seg[] = ";"; //�ָ�������Ϊ����comma���ָ�������Ϊ��ָ���ģ���ֺţ��ո��
	char charlist[MAX_NODE_DEEP][MAX_NODE_NAME_LENGTH] = { "" };//ָ���ָ������ַ����洢��λ�ã����ﶨ���ά�ַ�������
	int i = 0;
	char *pTempContext;
	char *substr = strtok_s(str, seg, &pTempContext);//�����ֳɵķָ��,substrΪ�ָ���������ַ���

	TiXmlElement *pNode[MAX_NODE_DEEP];
	pNode[0] = pRoot;

	while (substr != NULL) {
	strncpy_s(charlist[i], MAX_NODE_NAME_LENGTH, substr, MAX_NODE_NAME_LENGTH - 1);//���·ָ���������ַ���substr������Ҫ�洢��charlsit��
	pNode[i + 1] = pNode[i]->FirstChildElement(charlist[i]);
	if (pNode[i + 1] == nullptr)
	return RESULT_CANNOT_FIND_ELEMENT;
	i++;
	substr = strtok_s(NULL, seg, &pTempContext);//�ڵ�һ�ε���ʱ��strtok()����������str�ַ���������ĵ����򽫲���str���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣
	}
	cout << pNode[i - 1]->Value() << endl << pNode[i]->Value() << endl;
	if (pNode[i - 1]->RemoveChild(pNode[i])) return RESULT_SUCCESS;

	return RESULT_FAIL;
}
