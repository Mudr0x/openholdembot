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

// DialogSAPrefs5.cpp : implementation file
//

#include "stdafx.h"

#include "COpenTrackerThread.h"

#include "DialogSAPrefs5.h"
#include "MainFrm.h"
#include "..\DLLs\WindowFunctions_DLL\window_functions.h"
#include "..\OpenTracker DLL\opentracker_query_definitions.h"
#include "..\OpenTracker DLL\CDatabase.h"
#include "..\OpenTracker DLL\CImporter.h"
#include "SAPrefsSubDlg.h"
using namespace std;


// CDlgSAPrefs5 dialog

IMPLEMENT_DYNAMIC(CDlgSAPrefs5, CSAPrefsSubDlg)

CDlgSAPrefs5::CDlgSAPrefs5(CWnd* pParent /*=NULL*/)
		: CSAPrefsSubDlg(CDlgSAPrefs5::IDD, pParent)
{
}

CDlgSAPrefs5::~CDlgSAPrefs5()
{
}

void CDlgSAPrefs5::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OT_DBIP, m_ot_dbip);
	DDX_Control(pDX, IDC_OT_DBPORT, m_ot_dbport);
	DDX_Control(pDX, IDC_OT_DBUSER, m_ot_dbuser);
	DDX_Control(pDX, IDC_OT_DBPASS, m_ot_dbpass);
	DDX_Control(pDX, IDC_OT_DBNAME, m_ot_dbname);
	DDX_Control(pDX, IDC_POKER_NETWORKS, m_poker_networks);
	DDX_Control(pDX, IDC_HH_FOLDER, m_hh_folder);
	DDX_Control(pDX, IDC_TS_FOLDER, m_ts_folder);
}

BEGIN_MESSAGE_MAP(CDlgSAPrefs5, CSAPrefsSubDlg)
	ON_BN_CLICKED(IDC_OT_DBTEST, &CDlgSAPrefs5::OnBnClickedDBtest)
	ON_BN_CLICKED(IDC_OT_DBCREATE, &CDlgSAPrefs5::OnBnClickedDBcreate)
	ON_BN_CLICKED(IDC_OT_DBDELETE, &CDlgSAPrefs5::OnBnClickedDBdelete)
	ON_BN_CLICKED(IDC_OT_DBOPTIMIZE, &CDlgSAPrefs5::OnBnClickedDBoptimize)
	ON_LBN_SELCHANGE(IDC_POKER_NETWORKS, &CDlgSAPrefs5::OnLbnSelectedPokerNetwork)
	ON_EN_UPDATE(IDC_HH_FOLDER, &CDlgSAPrefs5::OnEnUpdatedHHfolder)
	ON_EN_UPDATE(IDC_TS_FOLDER, &CDlgSAPrefs5::OnEnUpdatedTSfolder)
	ON_BN_CLICKED(IDC_HH_SEARCH, &CDlgSAPrefs5::OnBnClickedHHsearch)
	ON_BN_CLICKED(IDC_TS_SEARCH, &CDlgSAPrefs5::OnBnClickedTSsearch)
	ON_BN_CLICKED(IDC_GETHANDS_MANUAL, &CDlgSAPrefs5::OnBnClickedGetHandsManual)
	ON_BN_CLICKED(IDC_GETHANDS_LIVE, &CDlgSAPrefs5::OnBnClickedGetHandsLive)
END_MESSAGE_MAP()


CDatabase OT_DB;
CImporter OT_IMP;

CString poker_networks[] =	{ "", "", "", "", "", "", "", "", "" };
CString hh_folders[] =		{ "", "", "", "", "", "", "", "", "" };
CString ts_folders[] =		{ "", "", "", "", "", "", "", "", "" };


// CDlgSAPrefs5 message handlers
BOOL CDlgSAPrefs5::OnInitDialog()
{
	CString Separator = _T(",");
	CString Token = "null";
	int i = 0, Position = 0;

	CSAPrefsSubDlg::OnInitDialog();

	OT_IMP.StartThread();

	m_ot_dbip.SetWindowText(Preferences()->ot_ip_addr());
	m_ot_dbport.SetWindowText(Preferences()->ot_port());
	m_ot_dbuser.SetWindowText(Preferences()->ot_user());
	m_ot_dbpass.SetWindowText(Preferences()->ot_pass());
	m_ot_dbname.SetWindowText(Preferences()->ot_dbname());
	CString poknets =	Preferences()->ot_poknets();
	CString hhfolders = Preferences()->ot_hhfolders();
	CString tsfolders = Preferences()->ot_tsfolders();
	while (!Token.IsEmpty())
	{
		// Get next token.
		Token = poknets.Tokenize(Separator, Position);
		if (!Token.IsEmpty()) {
			m_poker_networks.AddString(Token);
			poker_networks[i] = Token;
			++i;
		}
	}
	i = 0, Position = 0;
	Token = "null";
	while (!Token.IsEmpty())
	{
		// Get next token.
		Token = hhfolders.Tokenize(Separator, Position);
		if (!Token.IsEmpty()) {
			hh_folders[i] = Token;
			++i;
		}
	}
	i = 0, Position = 0;
	Token = "null";
	while (!Token.IsEmpty())
	{
		// Get next token.
		Token = tsfolders.Tokenize(Separator, Position);
		if (!Token.IsEmpty()) {
			ts_folders[i] = Token;
			++i;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSAPrefs5::OnOK()
{
	CString			text = "";

	m_ot_dbip.GetWindowText(text);
	Preferences()->SetValue(k_prefs_ot_ip_addr, text);

	m_ot_dbport.GetWindowText(text);
	Preferences()->SetValue(k_prefs_ot_port, text);

	m_ot_dbuser.GetWindowText(text);
	Preferences()->SetValue(k_prefs_ot_user, text);

	m_ot_dbpass.GetWindowText(text);
	Preferences()->SetValue(k_prefs_ot_pass, text);

	m_ot_dbname.GetWindowText(text);
	Preferences()->SetValue(k_prefs_ot_dbname, text);

	text = "";
	for (int i = 0; i < (int)size(hh_folders); i++) {
		if (hh_folders[i] == "") hh_folders[i] = "#";
		text.Append(hh_folders[i] + ",");
	}
	Preferences()->SetValue(k_prefs_ot_hhfolders, text);

	text = "";
	for (int i = 0; i < (int)size(ts_folders); i++) {
		if (ts_folders[i] == "") ts_folders[i] = "#";
		text.Append(ts_folders[i] + ",");
	}
	Preferences()->SetValue(k_prefs_ot_tsfolders, text);

	CSAPrefsSubDlg::OnOK();
}

void CDlgSAPrefs5::OnBnClickedDBtest() {
	CString			conn_str = "", ip_addr = "", port = "", user = "", pass = "", dbname = "", e = "";

	m_ot_dbip.GetWindowText(ip_addr);
	m_ot_dbport.GetWindowText(port);
	m_ot_dbuser.GetWindowText(user);
	m_ot_dbpass.GetWindowText(pass);
	m_ot_dbname.GetWindowText(dbname);

	if (dbname.IsEmpty()) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Test DB: PostgreSQL DB Name not set ! Default : It will be set to '%s'\n", user);
		MessageBox_Interactive("PostgreSQL DB Name not set !\nBy Default : the same as the Username",
					   "Warning", MB_OK);
	}

	conn_str = p_opentracker_thread->CreateConnectionString(ip_addr,
		port, user, pass, dbname);

	// Set busy cursor
	PMainframe()->set_wait_cursor(true);
	PMainframe()->BeginWaitCursor();

	// Test the connection parameters
	_pgconn = PQconnectdb(conn_str.GetString());

	// Unset busy cursor
	PMainframe()->EndWaitCursor();
	PMainframe()->set_wait_cursor(false);

	if (PQstatus(_pgconn) == CONNECTION_OK) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Test DB: PostgreSQL DB opened successfully <%s/%s/%s>\n", ip_addr, port, dbname);
		if (PQisthreadsafe()) {
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Test DB: PostgreSQL library is thread safe.\n\n");
			MessageBox_Interactive("PostgreSQL DB opened successfully", "Success", MB_OK);
		} else {
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Test DB: PostgreSQL library is *NOT* thread safe!  This is a problem!\n\n");
			MessageBox_Interactive("PostgreSQL DB opened successfully, but\nPostgreSQL library is *NOT* thread safe!\nThis is a problem!",
					   "Success (partial)", MB_OK);
		}
		PQfinish(_pgconn);
	} else {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Test DB: ERROR opening PostgreSQL DB: %s\n\n", PQerrorMessage(_pgconn));
		e = "ERROR opening PostgreSQL DB:\n";
		e += PQerrorMessage(_pgconn);
		e += "\nConn string:";
		e += conn_str;

		MessageBox_Interactive(e.GetString(), "ERROR", MB_OK);

		PQfinish(_pgconn);
	}
}

void CDlgSAPrefs5::OnBnClickedDBcreate() {
	CString			conn_str = "", ip_addr = "", port = "", user = "", pass = "", dbname = "", e = "";

	m_ot_dbip.GetWindowText(ip_addr);
	m_ot_dbport.GetWindowText(port);
	m_ot_dbuser.GetWindowText(user);
	m_ot_dbpass.GetWindowText(pass);
	m_ot_dbname.GetWindowText(dbname);

	// Work around for OpenTracker Dll version
	// On standalone version it would not be necessary
	OT_DB.SetDBconnectEntries(ip_addr, port, user, pass, dbname);

	if (dbname.IsEmpty()) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Create DB: PostgreSQL DB Name not set! DB creation cancelled.\n\n");
		MessageBox_Interactive("PostgreSQL DB Name not set !\nCreate Database isn't possible until you provide a DB Name",
			"Warning", MB_OK);
	}
	else if (OT_DB.PQconnect()) {
		if (OT_DB.IsDBexists(dbname)) {
			CString warnMsg;
			warnMsg.Format("Database %s already exists.\nDo you want to override it?",
				dbname);
			if (MessageBox_Interactive(warnMsg, "Warning", MB_YESNO) == IDYES) {
				write_log(Preferences()->debug_opentracker(), "[OpenTracker] Create DB: PostgreSQL %s DB already exists! User choose to override it.\n\n", dbname);
				OT_DB.CreateOpenTrackerDB(dbname, user);
			}
			else
				write_log(Preferences()->debug_opentracker(), "[OpenTracker] Create DB: PostgreSQL %s DB already exists! User choose to cancel DB creation.\n\n", dbname);
		}
		else {
			write_log(Preferences()->debug_opentracker(), "[OpenTracker] Create DB: PostgreSQL %s DB doesn't exist. This new DB is going to be created.\n\n", dbname);
			OT_DB.CreateOpenTrackerDB(dbname, user);
		}

		//PQfinish(_pgconn);
	}
}

void CDlgSAPrefs5::OnBnClickedDBdelete() {
	CString			conn_str = "", ip_addr = "", port = "", user = "", pass = "", dbname = "", e = "";

	m_ot_dbip.GetWindowText(ip_addr);
	m_ot_dbport.GetWindowText(port);
	m_ot_dbuser.GetWindowText(user);
	m_ot_dbpass.GetWindowText(pass);
	m_ot_dbname.GetWindowText(dbname);

	// Work around for OpenTracker Dll version
	// On standalone version it would not be necessary
	OT_DB.SetDBconnectEntries(ip_addr, port, user, pass, dbname);

	if (dbname.IsEmpty()) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Delete DB: PostgreSQL DB Name not set! DB deletion cancelled.\n\n");
		MessageBox_Interactive("PostgreSQL DB Name not set!\nDelete Database isn't possible until you provide a DB Name.",
			"Warning", MB_OK);
	}
	else if (OT_DB.PQconnect()) {
		if (!OT_DB.IsDBexists(dbname)) {
			write_log(Preferences()->debug_opentracker(),
				"[OpenTracker] Delete DB: Database %s doesn't exist!\nDelete it isn't possible.\n\n", dbname);
			CString warnMsg;
			warnMsg.Format("Database %s doesn't exist!\nDelete it isn't possible.",
				dbname);
			MessageBox_Interactive(warnMsg, "Error", MB_OK);
		} else {
			CString warnMsg;
			warnMsg.Format("Do you really want to delete %s database?\nAll datas will be lost!",
				dbname);
			if (MessageBox_Interactive(warnMsg, "Warning", MB_YESNO) == IDYES) {
				CString query = OT_DLL_GetDBQuery("delete_db", dbname, user);
				if (OT_DB.QueryPostGreSQL(dbname, query)) {
					write_log(Preferences()->debug_opentracker(),
						"[OpenTracker] Delete DB: Query success for %s DB deletion.\nOpenTracker DB deleted successfully.\n\n", dbname);
					MessageBox_Interactive("OpenTracker DB deleted successfully.", "Success", MB_OK);
				}
			}
			else
				write_log(Preferences()->debug_opentracker(), "[OpenTracker] Delete DB: User choose to cancel DB deletion.\n\n", dbname);
		}

		//PQfinish(_pgconn);
	}
}

void CDlgSAPrefs5::OnBnClickedDBoptimize() {
}

void CDlgSAPrefs5::OnLbnSelectedPokerNetwork() {
	m_hh_folder.SetWindowText(hh_folders[m_poker_networks.GetCurSel()]);
	m_ts_folder.SetWindowText(ts_folders[m_poker_networks.GetCurSel()]);
}

void CDlgSAPrefs5::OnEnUpdatedHHfolder() {
	CString hh_folder = "";
	m_hh_folder.GetWindowText(hh_folder);
	hh_folders[m_poker_networks.GetCurSel()] = hh_folder;
}

void CDlgSAPrefs5::OnEnUpdatedTSfolder() {
	CString ts_folder = "";
	m_ts_folder.GetWindowText(ts_folder);
	ts_folders[m_poker_networks.GetCurSel()] = ts_folder;
}

void CDlgSAPrefs5::OnBnClickedHHsearch() {
}

void CDlgSAPrefs5::OnBnClickedTSsearch() {
}

void CDlgSAPrefs5::OnBnClickedGetHandsManual() {
	CString			conn_str = "", ip_addr = "", port = "", user = "", pass = "", dbname = "", hh_folder = "", ts_folder = "", e = "";

	m_ot_dbip.GetWindowText(ip_addr);
	m_ot_dbport.GetWindowText(port);
	m_ot_dbuser.GetWindowText(user);
	m_ot_dbpass.GetWindowText(pass);
	m_ot_dbname.GetWindowText(dbname);
	m_hh_folder.GetWindowText(hh_folder);
	m_ts_folder.GetWindowText(ts_folder);

	// Work around for OpenTracker Dll version
	// On standalone version it would not be necessary
	OT_DB.SetDBconnectEntries(ip_addr, port, user, pass, dbname);


	if (dbname.IsEmpty()) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Get Hands Manual: PostgreSQL DB Name not set! Get Hands cancelled.\n\n");
		MessageBox_Interactive("PostgreSQL DB Name not set!\nGet Hands isn't possible until you provide a DB Name.",
			"Warning", MB_OK);
		return;
	}

	int cur_index = m_poker_networks.GetCurSel();
	if (cur_index < 0) {
		write_log(Preferences()->debug_opentracker(), "[OpenTracker] Get Hands Manual: No Poker Network selected! Get Hands cancelled.\n\n");
		MessageBox_Interactive("No Poker Network selected!\nYou must select the network you want to get hands on.",
			"Warning", MB_OK);
		return;
	}

	CString poknet_name;
	m_poker_networks.GetText(cur_index, poknet_name);

	OT_IMP.GetHandsManual(poknet_name, hh_folder, ts_folder);


	//PQfinish(_pgconn);
}

void CDlgSAPrefs5::OnBnClickedGetHandsLive() {
}
