
// XML_Operate_MFCDlg.h : 头文件
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
	RESULT_NULL_POINT,				//入参不合法
	RESULT_CANNOT_FIND_ELEMENT		//找不到对应的节点
}RESULT_TYPE_E;

RESULT_TYPE_E LoadXmlFile(const char *szFilePath, TiXmlElement *pRoot);

//根据节点路径字符串，找到需要的节点
TiXmlElement * FindElementByStr(TiXmlElement *pRoot, const char *szNodePath);

//加载XML文件
RESULT_TYPE_E LoadXmlFile(const char *szFilePath, TiXmlElement *pRoot);

//获取节点的值
RESULT_TYPE_E GetValueFromXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue);

//替换节点的值
RESULT_TYPE_E SetValueToXmlFile(TiXmlElement *pRoot, const char *szNodePath, char *szElementValue);

//增加节点
RESULT_TYPE_E AddNodeToXml(TiXmlElement *pRoot, const char *szNodePath, const char *szNodeName, const char *szValue);

//删除节点
RESULT_TYPE_E DelNodeFromXml(TiXmlElement *pRoot, const char *szNodePath);

//根据节点路径字符串，找到需要的节点
TiXmlElement * FindElementByStr(TiXmlElement *pRoot, const char *szNodePath);

// CXML_Operate_MFCDlg 对话框
class CXML_Operate_MFCDlg : public CDialogEx
{
// 构造
public:
	CXML_Operate_MFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XML_OPERATE_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 不需要什么注释
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
