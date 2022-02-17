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

#include "stdafx.h"
#include "CWhiteInfoBox.h"

#include "CEngineContainer.h"
#include "CHandresetDetector.h"
#include "CSymbolEngineChipAmounts.h"
#include "CSymbolEngineGameType.h"
#include "CSymbolengineTableLimits.h"
#include "CSymbolengineUserchair.h"
#include "CTableState.h"
#include "..\DLLs\StringFunctions_DLL\string_functions.h"

CWhiteInfoBox *p_white_info_box = NULL;

CWhiteInfoBox::CWhiteInfoBox() {
	SetHandrank(0);
	SetGto(0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, FALSE);
	SetnOuts(0);
}

CWhiteInfoBox::~CWhiteInfoBox() {
}

void CWhiteInfoBox::Draw(RECT client_rect, LOGFONT logfont, CDC *pDC,
                         CPen *black_pen, CBrush *white_brush) {
	CPen		*pTempPen = NULL, oldpen;
	CBrush	*pTempBrush = NULL, oldbrush;
	RECT		rect = {0};
	CFont		*oldfont = NULL, cFont;
	int			left = 0, top = 0, right = 0, bottom = 0;
		
	bool sym_playing		= p_table_state->User()->HasKnownCards();
	// "White box" in the OpenHoldem-GUI with basic important info
	const int k_basic_height = 2;				// pixels
	const int k_extra_height_per_line = 16;	// pixels
	const int k_number_of_default_lines = 9;	// hand-number, game-type, ante, pot, gto
	int height = k_basic_height 
		+ k_extra_height_per_line * k_number_of_default_lines;
	if (kMaxLogSymbolsForWhiteBox > 0)	{
		// Extra lines for symbol-logging
		height += k_extra_height_per_line * kMaxLogSymbolsForWhiteBox;
	}
  // Figure placement of box
	left = client_rect.right/2-130;
	top = 175;
	right = client_rect.right/2+130;
	bottom = top+height;

	pTempPen = (CPen*)pDC->SelectObject(&black_pen);
	oldpen.FromHandle((HPEN)pTempPen);					// Save old pen
	pTempBrush = (CBrush*)pDC->SelectObject(&white_brush);
	oldbrush.FromHandle((HBRUSH)pTempBrush);			// Save old brush

	pDC->SetBkMode(OPAQUE);
	pDC->Rectangle(left, top, right, bottom);

	// Set font basics
	logfont.lfHeight = -14;
	logfont.lfWeight = FW_NORMAL;
	cFont.CreateFontIndirect(&logfont);
	oldfont = pDC->SelectObject(&cFont);
	pDC->SetTextColor(COLOR_BLACK);

	// Set rectangle
	rect.left = left;
	rect.top = top+3;
	rect.right = right;
	rect.bottom = bottom;

  CString info_txt = InfoText();
	// Draw it
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(info_txt.GetString(), info_txt.GetLength(), &rect, NULL);

	// Restore original pen, brush and font
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldfont);
	cFont.DeleteObject();

	// Set font basics
	logfont.lfHeight = -14;
	logfont.lfWeight = FW_BOLD;
	cFont.CreateFontIndirect(&logfont);
	oldfont = pDC->SelectObject(&cFont);
	pDC->SetTextColor(COLOR_MAROON);

	info_txt = GtoText();
	// Draw it
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(info_txt.GetString(), info_txt.GetLength(), &rect, NULL);

	// Restore original pen, brush and font
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldfont);
	cFont.DeleteObject();
}

CString CWhiteInfoBox::InfoText() {
  double sym_bblind		= p_engine_container->symbol_engine_tablelimits()->bblind();
	double sym_sblind		= p_engine_container->symbol_engine_tablelimits()->sblind();
	double sym_ante			= p_engine_container->symbol_engine_tablelimits()->ante();
	int sym_lim				  = p_engine_container->symbol_engine_gametype()->gametype();
	CString sym_handnumber = p_handreset_detector->GetHandNumber();
	double sym_pot			= p_engine_container->symbol_engine_chip_amounts()->pot();
  CString result, s;
	// handnumber
	if (sym_handnumber != "") {
		s.Format("  Hand #: %s\n", sym_handnumber);
	}	else 	{
		s.Format("  Hand #: -\n");
	}
	result.Append(s);

  // blinds, game-type
	CString format_string;
  if (IsInteger(sym_sblind) && IsInteger(sym_bblind)) {
    // Display as integer numbers
		format_string = "  %s %.0f/%.0f/%.0f\n";
  }
  else {
		// Fractional nunbers: use 2.00 digits  
		format_string = "  %s %.2f/%.2f/%.2f\n";
	}
	s.Format(format_string,
		p_engine_container->symbol_engine_gametype()->GetGameTypeAsString(),
		sym_sblind, sym_bblind, p_engine_container->symbol_engine_tablelimits()->bigbet());
	result.Append(s);

	// ante + pot
	if (sym_ante != 0) {
		s.Format("  Ante: %s  Pot: %s\n", Number2CString(sym_ante), Number2CString(sym_pot));
		result.Append(s);
	}
	else {
		// Pot
		s.Format("  Pot: %s\n", Number2CString(sym_pot));
		result.Append(s);
	}

	// Pot
	s.Format("  Pot: %s\n", Number2CString(sym_pot));
	if (Preferences()->amounts_in_bb()) {
		s.Format("  Pot: %s %s\n", Number2CString(sym_pot/sym_bblind), "BB");
	}
	result.Append(s);

  // logged symbols
	if (kMaxLogSymbolsForWhiteBox > 0) {
    result.Append("  ");
    result.Append(_custom_log_message);
	}

  return result;
}

CString CWhiteInfoBox::GtoText() {
	CString result;

	//gto
	if (p_table_state->User()->HasKnownCards()) {
		// Format data for display
		// Handrank
		if (_prwin_mustplay)
			_info_handrank.Format("\n\n\n\n  Handrank:  %i / 169   MUST PLAY !\n", _handrank);
		else
			_info_handrank.Format("\n\n\n\n  Handrank:  %i / 169\n", _handrank);
		// PrWin: percentages instead of probabilities
		_info_gto.Format("  PrWin:  %3.1f / %3.1f / %3.1f\n  Outs:  %i    Out Odds:  %3.1f\n  Implied Odds:  %3.1f    PotOdds:  %3.1f\n  My Equity:  %3.1f    Pot Equity:  %3.1f",
			100 * _prwin, 100 * _prtie, 100 * _prlos, _nouts, 100 * _outodds, _impliedodds, 100 * _potodds, _myequity, _potequity);
	}
	result.Append(_info_handrank);
	result.Append(_info_gto);

	return result;
}

void CWhiteInfoBox::SetGto(double prwin, double prtie, double prlos, int nouts, double outodds, double impliedodds, double potodds, double myequity, double potequity, bool prwin_mustplay) {
	_prwin = prwin;
	_prtie = prtie;
	_prlos = prlos;
	_nouts = nouts;
	_outodds = outodds;
	_impliedodds = impliedodds;
	_potodds = potodds;
	_myequity = myequity;
	_potequity = potequity;
	_prwin_mustplay = prwin_mustplay;	
}

void CWhiteInfoBox::SetnOuts(int nouts)
{
	_nouts = nouts;
}