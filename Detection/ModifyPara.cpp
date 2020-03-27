// ModifyPara.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Detection.h"
#include "ModifyPara.h"
#include "afxdialogex.h"
#include<fstream>
using namespace std;

// CModifyPara �Ի���

IMPLEMENT_DYNAMIC(CModifyPara, CDialogEx)

CModifyPara::CModifyPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MODIFY_PARA, pParent)
	//3.28ҹ ɾ����һ��
	, m_sGrayThreshold(_T(""))
{

	//3.28����  
	m_sResolution = _T("5.378");
	m_sDelayTime = _T("0");
	m_sPulseEquivalent = _T("1000");
	m_sThreshold = _T("100");

	m_sSampleCountStrip = _T("2");

	//4.10�¼�
	m_sGrayThreshold = _T("36");
}

CModifyPara::~CModifyPara()
{
}

void CModifyPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION, m_sResolution);
	DDX_Text(pDX, IDC_EDIT_MODIFY_MOTION_PARA_DELAY, m_sDelayTime);
	DDX_Text(pDX, IDC_EDIT_MODIFY_MOTION_PARA_PULSE, m_sPulseEquivalent);
	DDX_Control(pDX, IDC_STATIC_TIP, m_cTip);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD, m_sThreshold);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP, m_sSampleCountStrip);
	DDX_Text(pDX, IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD, m_sGrayThreshold);
}


BEGIN_MESSAGE_MAP(CModifyPara, CDialogEx)
	ON_BN_CLICKED(ID_BTN_MODIFY_PARA_OK, &CModifyPara::OnBnClickedBtnModifyParaOk)
	ON_BN_CLICKED(IDD_BTN_MODIFY_PARA_CANCEAL, &CModifyPara::OnBnClickedBtnModifyParaCanceal)
	ON_BN_CLICKED(ID_BTN_MODIFY_PARA_APPLY, &CModifyPara::OnBnClickedBtnModifyParaApply)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



BOOL CModifyPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��


	// *******************����ȡ��ʼ��ϵͳ������***********************
	GetIniSystemPara();

	//4.1�޸�
	
	ofstream outfile("testFile1.txt", ios::app);

	int m_steps_mm = (int)_ttof(m_sPulseEquivalent);
	double m_delayTime = (int)_ttof(m_sDelayTime);
	double m_resolution = (double)_ttof(m_sResolution);
	int m_threshold = (double)_ttof(m_sThreshold);
	int sampleCountStrip = (int)_ttof(m_sSampleCountStrip);
	//4.10�¼�
	int graythreshold = (int)_ttof(m_sGrayThreshold);


	outfile << m_steps_mm << endl;
	outfile << m_delayTime << endl;
	outfile << m_resolution << endl;
	outfile << m_threshold << endl;
	outfile << sampleCountStrip << endl << endl;
	//4.10
	outfile << graythreshold << endl << endl;



	//CFont* pFont;
	//pFont = m_cTip.GetFont();//��ȡCFont����
	//LOGFONT lf;
	//pFont->GetLogFont(&lf);//��ȡLOGFONT�ṹ��
	//lf.lfHeight = 20;    //�޸������С
	//lf.lfItalic = FALSE;        //��б
	//lf.lfWeight = 560;   //�޸�����Ĵ�ϸ
	//
	//m_font.CreateFontIndirectW(&lf);//����һ���µ�����
	//m_cTip.SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



// CModifyPara ��Ϣ��������


HBRUSH CModifyPara::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
	{
		pDC->SetTextColor(RGB(255, 0, 0));  // �����ı���ɫΪ��ɫ
		pDC->SetBkMode(OPAQUE);    // �����ı�����Ϊ͸��
		// pDC->SetBkColor(RGB(0, 0, 100));   // �����ı�����Ϊ��ɫ

	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CModifyPara::GetIniSystemPara()
{
	/*m_sResolution = _T("5.378");
	m_sDelayTime = _T("0");
	m_sPulseEquivalent = _T("1000");
	m_sThreshold = _T("100");*/

	// ���嵱��
	CString strPluse;
	::GetPrivateProfileString(_T("SaveInfo"), _T("���嵱��"), strPluse, strPluse.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_PULSE)->SetWindowText(strPluse);
	m_sPulseEquivalent = strPluse;

	// �ӳ�
	CString strDelayTime;
	::GetPrivateProfileString(_T("SaveInfo"), _T("�ӳ�"), strDelayTime, strDelayTime.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_DELAY)->SetWindowText(strDelayTime);
	m_sDelayTime = strDelayTime;

	// �ֱ���
	CString strResolution;
	::GetPrivateProfileString(_T("SaveInfo"), _T("�ֱ���"), strResolution, strResolution.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION)->SetWindowText(strResolution);
	m_sResolution = strResolution;

	// ��С������ֵ
	CString strThreshold;
	::GetPrivateProfileString(_T("SaveInfo"), _T("��С������ֵ"), strThreshold, strThreshold.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD)->SetWindowText(strThreshold);
	m_sThreshold = strThreshold;

	//3.26�޸�  3.28����
	// ÿ��ȡ��֡��
	CString strSampleCountStrip;  //3.28ҹ ������
	::GetPrivateProfileString(_T("SaveInfo"), _T("ÿ��ȡ��֡��"), strSampleCountStrip, strSampleCountStrip.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP)->SetWindowText(strSampleCountStrip);
	m_sSampleCountStrip = strSampleCountStrip;

	//4.10�¼�
	// �Ҷ���ֵ
	CString strGrayThreshold;
	::GetPrivateProfileString(_T("SaveInfo"), _T("�Ҷ���ֵ"), strGrayThreshold, strGrayThreshold.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\SystemPara.ini"));
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD)->SetWindowText(strGrayThreshold);
	m_sGrayThreshold = strGrayThreshold;
}

void CModifyPara::SaveSystemPara()
{
	// ���嵱��
	CString strPluse;
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_PULSE)->GetWindowText(strPluse);
	::WritePrivateProfileString(_T("SaveInfo"), _T("���嵱��"), strPluse, _T("..\\SystemPara.ini"));

	// �ӳ�
	CString strDelayTime;
	GetDlgItem(IDC_EDIT_MODIFY_MOTION_PARA_DELAY)->GetWindowText(strDelayTime);
	::WritePrivateProfileString(_T("SaveInfo"), _T("�ӳ�"), strDelayTime, _T("..\\SystemPara.ini"));

	// �ֱ���
	CString strResolution;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_RESOLUTION)->GetWindowText(strResolution);
	::WritePrivateProfileString(_T("SaveInfo"), _T("�ֱ���"), strResolution, _T("..\\SystemPara.ini"));

	// ��С������ֵ
	CString strThreshold;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_THRESHOLD)->GetWindowText(strThreshold);
	::WritePrivateProfileString(_T("SaveInfo"), _T("��С������ֵ"), strThreshold, _T("..\\SystemPara.ini"));

	//3.26�޸�  3.28����
	// ÿ��ȡ��֡�� 
	CString strSampleCountStrip;  	//3.28ҹ ������
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_SAMPLECOUNTSTRIP)->GetWindowText(strSampleCountStrip);
	::WritePrivateProfileString(_T("SaveInfo"), _T("ÿ��ȡ��֡��"), strSampleCountStrip, _T("..\\SystemPara.ini"));

	//4.10�¼�
	// �Ҷ���ֵ
	CString strGrayThreshold;
	GetDlgItem(IDC_EDIT_MODIFY_IMAGE_PARA_GRAYTHRESHOLD)->GetWindowText(strGrayThreshold);
	::WritePrivateProfileString(_T("SaveInfo"), _T("�Ҷ���ֵ"), strGrayThreshold, _T("..\\SystemPara.ini"));
}


void CModifyPara::OnBnClickedBtnModifyParaOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	UpdateData(TRUE);

	SaveSystemPara();

	EndDialog(-1);
}


void CModifyPara::OnBnClickedBtnModifyParaCanceal()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	EndDialog(-1);
}


void CModifyPara::OnBnClickedBtnModifyParaApply()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	UpdateData(TRUE);

	SaveSystemPara();
}


//void CModifyPara::OnOK()
//{
//	// TODO: �ڴ�����ר�ô����/����û���
//	// CDialogEx::OnOK();
//}