
// XML_Operate_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>

using namespace std;

#define MAX_NODE_PATH_LENGTH	100
#define MAX_NODE_DEEP			10
#define MAX_NODE_NAME_LENGTH	50
#define MAX_NODE_VALUE_LENGTH	50
#define MAX_FILE_NUM			50

typedef	enum RESULT_TYPE
{
	RESULT_SUCCESS = 0,
	RESULT_FAIL = 1,
	RESULT_NULL_POINT,				//��β��Ϸ�
	RESULT_CANNOT_FIND_ELEMENT		//�Ҳ�����Ӧ�Ľڵ�
}RESULT_TYPE_E;

RESULT_TYPE_E LoadXmlFile(const char *szFilePath, TiXmlElement *pRoot);

//���ݽڵ�·���ַ������ҵ���Ҫ�Ľڵ�
TiXmlElement * FindElementByStr(TiXmlElement *pRoot, const char *szNodePath);

//����XML�ļ�
RESULT_TYPE_E LoadXmlFile(const char *szFilePath, TiXmlElement *pRoot);

//��ȡ�ڵ��ֵ
RESULT_TYPE_E GetValueFromXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue);

//�滻�ڵ��ֵ
RESULT_TYPE_E SetValueToXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue);

//���ӽڵ�
RESULT_TYPE_E AddNodeToXml(TiXmlElement *pRoot, const char *szNodePath, const char *szNodeName, const char *szValue);

//ɾ���ڵ�
RESULT_TYPE_E DelNodeFromXml(TiXmlElement *pRoot, const char *szNodePath);

//���ݽڵ�·���ַ������ҵ���Ҫ�Ľڵ�
TiXmlElement * FindElementByStr(TiXmlElement *pRoot, const char *szNodePath);

// CXML_Operate_MFCDlg �Ի���
class CXML_Operate_MFCDlg : public CDialogEx
{
// ����
public:
	CXML_Operate_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XML_OPERATE_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ����Ҫʲôע��
	CString m_FilePath;
	CString m_FileName;
	CString m_NodePath;
	CString m_NodeValueNow;
	CString m_NodeValueNew;
	afx_msg void OnBnClickedGetNodeValue();
	afx_msg void OnBnClickedChangeNodeValue();
	afx_msg void OnBnClickedAddNode();
	afx_msg void OnBnClickedDelNode();
	CEdit m_EditFilePath;
	CEdit m_EditFileName;
	CEdit m_EditNodePath;
	CEdit m_EditNodeValueNow;
	CEdit m_EditNodeValueNew;
	CEdit m_EditOperationRecord;
	CString m_OperationRecord;
	CEdit m_EditNewNodeName;
	CString m_NewNodeName;
};
