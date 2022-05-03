//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************

#ifndef INC_DIALOGSAPREFS5_H
#define INC_DIALOGSAPREFS5_H

#include "resource.h"
#include "afxwin.h"

#include "libpq-fe.h"
#include "SAPrefsDialog.h"


// CDlgSAPrefs5 dialog

class CDlgSAPrefs5 : public CSAPrefsSubDlg
{
	DECLARE_DYNAMIC(CDlgSAPrefs5)

public:
	CDlgSAPrefs5(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSAPrefs5();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedDBtest();
	afx_msg void OnBnClickedDBcreate();
	afx_msg void OnBnClickedDBdelete();
	afx_msg void OnBnClickedDBoptimize();
	afx_msg void OnLbnSelectedPokerNetwork();
	afx_msg void OnEnUpdatedHHfolder();
	afx_msg void OnEnUpdatedTSfolder();
	afx_msg void OnBnClickedHHsearch();
	afx_msg void OnBnClickedTSsearch();
	afx_msg void OnBnClickedGetHandsManual();
	afx_msg void OnBnClickedGetHandsLive();

	enum { IDD = IDD_SAPREFS5 };

	DECLARE_MESSAGE_MAP()

public:
	__declspec(dllexport) CEdit* get_dbip() { return &m_ot_dbip; }

	CComboBox m_ot_version;
	CEdit m_ot_dbip, m_ot_dbport, m_ot_dbuser, m_ot_dbpass, m_ot_dbname,
			m_hh_folder, m_ts_folder;
	CListBox m_poker_networks;

private:

	PGconn*	_pgconn;
};


#endif //INC_DIALOGSAPREFS5_H