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


// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include <Gdiplus.h>
//#include <gdiplusheaders.h>
//#include <gdiplusgraphics.h>

#include "MainFrm.h"

#include "CRegionCloner.h"
#include "DialogCopyRegion.h"
#include "DialogSelectTable.h"
#include "global.h"
#include "ListOfSymbols.h"
#include "OpenScrape.h"
#include "OpenScrapeDoc.h"
#include "OpenScrapeView.h"
#include "registry.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

const int kHotkeyRefresh = 1234;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CONNECTTOWINDOW, &CMainFrame::OnViewConnecttowindow)
	ON_BN_CLICKED(ID_MAIN_TOOLBAR_GREENCIRCLE, &CMainFrame::OnViewConnecttowindow)
	ON_COMMAND(ID_VIEW_REFRESH, &CMainFrame::OnViewRefresh)
	ON_BN_CLICKED(ID_MAIN_TOOLBAR_REFRESH, &CMainFrame::OnViewRefresh)
	ON_COMMAND(ID_VIEW_PREV, &CMainFrame::OnViewPrev)
	ON_BN_CLICKED(ID_MAIN_TOOLBAR_PREV, &CMainFrame::OnViewPrev)
	ON_COMMAND(ID_VIEW_NEXT, &CMainFrame::OnViewNext)
	ON_BN_CLICKED(ID_MAIN_TOOLBAR_NEXT, &CMainFrame::OnViewNext)
	ON_COMMAND(ID_TOOLS_CLONEREGIONS, &CMainFrame::OnToolsCloneRegions)

	ON_COMMAND(ID_EDIT_UPDATEHASHES, &CMainFrame::OnEditUpdatehashes)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_VIEW_CURRENTWINDOWSIZE, &CMainFrame::OnUpdateViewCurrentwindowsize)
	ON_COMMAND(ID_EDIT_DUPLICATEREGION, &CMainFrame::OnEditDuplicateregion)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DUPLICATEREGION, &CMainFrame::OnUpdateEditDuplicateregion)
	ON_COMMAND(ID_GROUPREGIONS_BYTYPE, &CMainFrame::OnGroupregionsBytype)
	ON_COMMAND(ID_GROUPREGIONS_BYNAME, &CMainFrame::OnGroupregionsByname)
	ON_UPDATE_COMMAND_UI(ID_GROUPREGIONS_BYTYPE, &CMainFrame::OnUpdateGroupregionsBytype)
	ON_UPDATE_COMMAND_UI(ID_GROUPREGIONS_BYNAME, &CMainFrame::OnUpdateGroupregionsByname)
END_MESSAGE_MAP()

static UINT openscrape_indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////
//
// CMainFrame construction/destruction
//
/////////////////////////////////////////////////////

CMainFrame::CMainFrame() {
	// Save startup directory
  ::GetCurrentDirectory(sizeof(_startup_path) - 1, _startup_path);
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms646309%28v=vs.85%29.aspx
  // http://www.cplusplus.com/forum/windows/47266/
  // http://www.codeproject.com/Articles/2213/Beginner-s-Tutorial-Using-global-hotkeys
  RegisterHotKey(NULL, 
    kHotkeyRefresh,
    MOD_CONTROL,
    // https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
    0x52);   // 'r'
}

CMainFrame::~CMainFrame() {
  UnregisterHotKey(NULL, kHotkeyRefresh);
}

/////////////////////////////////////////////////////
//
// Creation of main freame
//
/////////////////////////////////////////////////////

bool CMainFrame::CreateToolbar()
{
	return (m_wndToolBar.CreateEx(this, NULL, 
		WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) 
		&& m_wndToolBar.LoadToolBar(IDR_MAINFRAME));
}

bool CMainFrame::CreateStatusBar()
{
	return (m_wndStatusBar.Create(this) 
		&& m_wndStatusBar.SetIndicators(openscrape_indicators, 
			sizeof(openscrape_indicators)/sizeof(UINT)));
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TBBUTTONINFO	tbi;
	tbi.cbSize = sizeof(TBBUTTONINFO);
	tbi.dwMask = TBIF_STYLE;
	tbi.fsStyle = TBSTYLE_CHECK;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	if (!CreateToolbar())
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!CreateStatusBar())
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// Start timer that blinks selected region
	SetTimer(BLINKER_TIMER, 500, 0);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	Registry	reg;
	int			max_x, max_y;

	WNDCLASS wnd;
	HINSTANCE hInst = AfxGetInstanceHandle();

	// Set class name
	if (!(::GetClassInfo(hInst, "OpenScrape", &wnd)))
	{
		wnd.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wnd.lpfnWndProc      = ::DefWindowProc;
		wnd.cbClsExtra       = wnd.cbWndExtra = 0;
		wnd.hInstance        = hInst;
		wnd.hIcon            = AfxGetApp()->LoadIcon(IDI_ICON1);
		wnd.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wnd.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wnd.lpszMenuName     = NULL;
		wnd.lpszClassName    = "OpenScrape";

		AfxRegisterClass( &wnd );
	}  
	cs.lpszClass = "OpenScrape";

	// Restore window location and size
	reg.read_reg();
	max_x = GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXICON);
	max_y = GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYICON);
	cs.x = min(reg.main_x, max_x);
	cs.y = min(reg.main_y, max_y);
	cs.cx = reg.main_dx;
	cs.cy = reg.main_dy;

	return true;
}

/////////////////////////////////////////////////////
//
// CMainFrame diagnostics
//
/////////////////////////////////////////////////////

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////
//
// CMainFrame message handlers
//
/////////////////////////////////////////////////////

BOOL CMainFrame::DestroyWindow()
{
	Registry		reg;
	WINDOWPLACEMENT wp;

	// Save window position
	reg.read_reg();
	GetWindowPlacement(&wp);

	reg.main_x = wp.rcNormalPosition.left;
	reg.main_y = wp.rcNormalPosition.top;
	reg.main_dx = wp.rcNormalPosition.right - wp.rcNormalPosition.left;
	reg.main_dy = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;
	reg.write_reg();

	// Close the TableMap dialog here so it can save its position properly
	if (theApp.m_TableMapDlg)  theApp.m_TableMapDlg->DestroyWindow();

	return CFrameWnd::DestroyWindow();
}

// TODO: Callers might need to be refactored
void CMainFrame::ForceRedraw()
{
	theApp.m_pMainWnd->Invalidate(true);
	theApp.m_TableMapDlg->Invalidate(true);
}

void CMainFrame::capture_window(HWND window_handle, const std::wstring& output_file_path)
{
	// Init COM
	init_apartment(winrt::apartment_type::multi_threaded);

	// Create Direct 3D Device
	winrt::com_ptr<ID3D11Device> d3d_device;

	winrt::check_hresult(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr, 0, D3D11_SDK_VERSION, d3d_device.put(), nullptr, nullptr));

	winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice device;
	const auto dxgiDevice = d3d_device.as<IDXGIDevice>();
	{
		winrt::com_ptr<IInspectable> inspectable;
		winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgiDevice.get(), inspectable.put()));
		device = inspectable.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
	}

	auto idxgi_device2 = dxgiDevice.as<IDXGIDevice2>();
	winrt::com_ptr<IDXGIAdapter> adapter;
	winrt::check_hresult(idxgi_device2->GetParent(winrt::guid_of<IDXGIAdapter>(), adapter.put_void()));
	winrt::com_ptr<IDXGIFactory2> factory;
	winrt::check_hresult(adapter->GetParent(winrt::guid_of<IDXGIFactory2>(), factory.put_void()));

	ID3D11DeviceContext* d3d_context = nullptr;
	d3d_device->GetImmediateContext(&d3d_context);

	RECT rect{};
	DwmGetWindowAttribute(window_handle, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
	const auto size = winrt::Windows::Graphics::SizeInt32{ rect.right - rect.left, rect.bottom - rect.top };

	winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool m_frame_pool =
		winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::Create(
			device,
			winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized,
			2,
			size);

	const auto activation_factory = winrt::get_activation_factory<
		winrt::Windows::Graphics::Capture::GraphicsCaptureItem>();
	auto interop_factory = activation_factory.as<IGraphicsCaptureItemInterop>();
	winrt::Windows::Graphics::Capture::GraphicsCaptureItem capture_item = { nullptr };
	interop_factory->CreateForWindow(window_handle, winrt::guid_of<ABI::Windows::Graphics::Capture::IGraphicsCaptureItem>(),
		winrt::put_abi(capture_item));

	auto is_frame_arrived = false;
	winrt::com_ptr<ID3D11Texture2D> texture;
	const auto session = m_frame_pool.CreateCaptureSession(capture_item);
	m_frame_pool.FrameArrived([&](auto& frame_pool, auto&)
		{
			if (is_frame_arrived)
			{
				return;
			}
			auto frame = frame_pool.TryGetNextFrame();

			struct __declspec(uuid("A9B3D012-3DF2-4EE3-B8D1-8695F457D3C1"))
				IDirect3DDxgiInterfaceAccess : ::IUnknown
			{
				virtual HRESULT __stdcall GetInterface(GUID const& id, void** object) = 0;
			};

			auto access = frame.Surface().as<IDirect3DDxgiInterfaceAccess>();
			access->GetInterface(winrt::guid_of<ID3D11Texture2D>(), texture.put_void());
			is_frame_arrived = true;
			return;
		});

	session.StartCapture();

	// Message pump
	MSG message;
	while (!is_frame_arrived)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			DispatchMessage(&message);
		}
	}

	//session.Close();

	D3D11_TEXTURE2D_DESC captured_texture_desc;
	texture->GetDesc(&captured_texture_desc);

	captured_texture_desc.Usage = D3D11_USAGE_STAGING;
	captured_texture_desc.BindFlags = 0;
	captured_texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	captured_texture_desc.MiscFlags = 0;

	winrt::com_ptr<ID3D11Texture2D> user_texture = nullptr;
	winrt::check_hresult(d3d_device->CreateTexture2D(&captured_texture_desc, nullptr, user_texture.put()));

	d3d_context->CopyResource(user_texture.get(), texture.get());

	D3D11_MAPPED_SUBRESOURCE resource;
	winrt::check_hresult(d3d_context->Map(user_texture.get(), NULL, D3D11_MAP_READ, 0, &resource));

	BITMAPINFO l_bmp_info;

	// BMP 32 bpp
	ZeroMemory(&l_bmp_info, sizeof(BITMAPINFO));
	l_bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	l_bmp_info.bmiHeader.biBitCount = 32;
	l_bmp_info.bmiHeader.biCompression = BI_RGB;
	l_bmp_info.bmiHeader.biWidth = captured_texture_desc.Width;
	l_bmp_info.bmiHeader.biHeight = captured_texture_desc.Height;
	l_bmp_info.bmiHeader.biPlanes = 1;
	l_bmp_info.bmiHeader.biSizeImage = captured_texture_desc.Width * captured_texture_desc.Height * 4;

	std::unique_ptr<BYTE> p_buf(new BYTE[l_bmp_info.bmiHeader.biSizeImage]);
	UINT l_bmp_row_pitch = captured_texture_desc.Width * 4;
	auto sptr = static_cast<BYTE*>(resource.pData);
	auto dptr = p_buf.get() + l_bmp_info.bmiHeader.biSizeImage - l_bmp_row_pitch;

	UINT l_row_pitch = std::min<UINT>(l_bmp_row_pitch, resource.RowPitch);

	for (size_t h = 0; h < captured_texture_desc.Height; ++h)
	{
		memcpy_s(dptr, l_bmp_row_pitch, sptr, l_row_pitch);
		sptr += resource.RowPitch;
		dptr -= l_bmp_row_pitch;
	}

	BITMAPINFOHEADER bmih = l_bmp_info.bmiHeader;

	void* bits;
	bits = (void*)(p_buf.get());

	HDC hdc = ::GetDC(window_handle);

	HBITMAP hbmp = CreateDIBitmap(hdc, &bmih, CBM_INIT, bits, &l_bmp_info, DIB_RGB_COLORS);

	::ReleaseDC(NULL, hdc);
}

void CMainFrame::OnViewConnecttowindow()
{
	LPARAM				lparam;
	CDlgSelectTable		cstd;
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();

	// Clear global list for holding table candidates
	g_tlist.RemoveAll();

	// Populate global candidate table list
	lparam = NULL;
	EnumWindows(EnumProcTopLevelWindowList, lparam);

	// Put global candidate table list in table select dialog variables
	int number_of_tablemaps = (int) g_tlist.GetSize();
	if (number_of_tablemaps==0) 
	{
		MessageBox("No valid windows found", "Cannot find window", MB_OK);
	}
	else 
	{
		for (int i=0; i<number_of_tablemaps; i++) 
		{
			cstd.tlist.Add(g_tlist[i]);
		}

		// Display table select dialog
		if (cstd.DoModal() == IDOK) 
		{
			RECT rc_client = { 0 };
			::GetClientRect(g_tlist[cstd.selected_item].hwnd, &rc_client);
			HWND tst = g_tlist[cstd.selected_item].hwnd;
			if (rc_client == RECT{ 0 })
				return;
			// Obtaining the factory
			auto interopFactory = winrt::get_activation_factory<
				winrt::Windows::Graphics::Capture::GraphicsCaptureItem,
				IGraphicsCaptureItemInterop>();

			winrt::Windows::Graphics::Capture::GraphicsCaptureItem item{ nullptr };

			// Creating a GraphicsCaptureItem from a HWND
			try {
				winrt::check_hresult(interopFactory->CreateForWindow(
					g_tlist[cstd.selected_item].hwnd,
					winrt::guid_of<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>(),
					winrt::put_abi(item)));
			}
			catch (winrt::hresult_error const& ex) {
				return;
			}
			
			//capture_window(g_tlist[cstd.selected_item].hwnd, L"output.bmp");
			
			// Save hwnd and rect of window we are attached to
			pDoc->attached_hwnd = g_tlist[cstd.selected_item].hwnd;
			pDoc->attached_rect.left = g_tlist[cstd.selected_item].crect.left;
			pDoc->attached_rect.top = g_tlist[cstd.selected_item].crect.top;
			pDoc->attached_rect.right = g_tlist[cstd.selected_item].crect.right;
			pDoc->attached_rect.bottom = g_tlist[cstd.selected_item].crect.bottom;

			SaveBmpPbits();
			ResizeWindow(pDoc);	
		}
	}
	ForceRedraw();
}

void CMainFrame::OnEditUpdatehashes()
{
	int		ret;

	COpenScrapeDoc	*pDoc = COpenScrapeDoc::GetDocument();
	CMainFrame		*pMyMainWnd  = (CMainFrame *) (theApp.m_pMainWnd);

	ret = p_tablemap->UpdateHashes(pMyMainWnd->GetSafeHwnd(), _startup_path);

	// Redraw the tree
	theApp.m_TableMapDlg->update_tree("");

	if (ret == SUCCESS)  
		MessageBox("Hashes updated successfully.", "Success", MB_OK);
}

void CMainFrame::OnEditDuplicateregion()
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	RMapCI				sel_region = p_tablemap->r$()->end();
	HTREEITEM			parent = NULL;
	CString				sel = "", selected_parent_text = "";
		
	// Get name of currently selected item
	if (theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem())
	{
		sel = theApp.m_TableMapDlg->m_TableMapTree.GetItemText(theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());
		parent = theApp.m_TableMapDlg->m_TableMapTree.GetParentItem(theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());
	}

	// Get name of currently selected item's parent
	if (parent != NULL) 
		selected_parent_text = theApp.m_TableMapDlg->m_TableMapTree.GetItemText(parent);
	else
		return;


	// Get iterator for selected region
	sel_region = p_tablemap->set_r$()->find(sel.GetString());

	// Exit if we can't find the region record
	if (sel_region == p_tablemap->r$()->end())
		return;

	// Present multi-selector region dialog
	CDlgCopyRegion  dlgcopyregion;
	dlgcopyregion.source_region = sel;
	dlgcopyregion.candidates.RemoveAll();

	// Figure out which related regions to provide as copy destination options
	CString	target="";
	if (sel.Mid(0,1)=="p" || sel.Mid(0,1)=="u")
		target=sel.Mid(2);
	else if (sel.Mid(0,1)=="c" && sel.Mid(2,8)=="cardface")
		target=sel.Mid(2,8);
	else if (sel.Mid(0,1)=="c" && sel.Mid(2,10)=="handnumber")
		target=sel.Mid(2,10);
	else if (sel.Mid(0,1)=="c" && sel.Mid(2,3)=="pot")
		target=sel.Mid(2,3);
	else if (sel.Mid(0,1)=="c" && sel.Mid(2,6)=="limits")
		target=sel.Mid(2,6);
	else if (sel.Mid(0,1)=="i" && sel.Mid(1,2)!="86")
		target=sel.Mid(2);
	else if (sel.Mid(0,1)=="i" && sel.Mid(2,2)=="86")
	{
		if (sel.Mid(3,1)>="0" && sel.Mid(3,1)<="9")
			target=sel.Mid(4);
		else
			target=sel.Mid(3);
	}

	// Add them to the dialog
	for (int i=0; i<list_of_regions.size(); i++)
	{
		bool add_it = (strstr(list_of_regions[i], target.GetString())!=NULL);

		CString s = list_of_regions[i];
		for (RMapCI r_iter=p_tablemap->r$()->begin(); r_iter!=p_tablemap->r$()->end(); r_iter++)
		{
			if (r_iter->second.name == s)  
				add_it = false;
		}

		if (add_it)
			dlgcopyregion.candidates.Add(list_of_regions[i]);
	}

	// Show dialog if there are any strings left to add
	if (dlgcopyregion.candidates.GetSize() == 0)
	{
		MessageBox("All related region records are already present.");
	}
	else
	{
		if (dlgcopyregion.DoModal() == IDOK)
		{
			bool added_at_least_one = false;

			// Add new records to internal structure
			for (int i=0; i<dlgcopyregion.selected.GetSize(); i++)
			{
				//MessageBox(dlgcopyregion.selected[i]);
				STablemapRegion new_region;
				new_region.name = dlgcopyregion.selected[i];
				new_region.left = sel_region->second.left + (5*i);
				new_region.top = sel_region->second.top + (5*i);
				new_region.right = sel_region->second.right + (5*i);
				new_region.bottom = sel_region->second.bottom + (5*i);
				new_region.color = sel_region->second.color;
				new_region.radius = sel_region->second.radius;
				new_region.transform = sel_region->second.transform;

				// Insert the new record in the existing array of z$ records
				if (p_tablemap->r$_insert(new_region))
				{
					added_at_least_one = true;

					// Add new record to tree
					HTREEITEM new_hti = theApp.m_TableMapDlg->m_TableMapTree.InsertItem(
						new_region.name, parent ? parent : theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());

					theApp.m_TableMapDlg->m_TableMapTree.SortChildren(parent ? parent : 
						theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());

					theApp.m_TableMapDlg->m_TableMapTree.SelectItem(new_hti);
				}
			}

			if (added_at_least_one)
			{
				pDoc->SetModifiedFlag(true);
				Invalidate(false);
			}
		}
	}

}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	COpenScrapeDoc			*pDoc = COpenScrapeDoc::GetDocument();
	COpenScrapeView			*pView = COpenScrapeView::GetView();
  if (!pDoc) {
    return;
  }
  if (!pView) {
    return;
  }
	if (nIDEvent == BLINKER_TIMER) 
	{
		pDoc->blink_on = !pDoc->blink_on;
		pView->blink_rect();

	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::SetTablemapSizeIfUnknown(int size_x, int size_y)
{
	return;
	if ((size_x > 0) && (size_y > 0)) //!! and tm loaded!
	{
		CString	text;
		text.Format("z$clientsize not yet defined.\nSetting it automatically to (%d, %d).",
			size_x, size_y);
		if (MessageBox(text, "Info: z$clientsize", MB_YESNO) == IDYES)
		{
			//z$clientsize

		}
	}
}

void CMainFrame::BringOpenScrapeBackToFront()
{
	::SetFocus(AfxGetApp()->m_pMainWnd->GetSafeHwnd());
	::SetForegroundWindow(AfxGetApp()->m_pMainWnd->GetSafeHwnd());
	::SetActiveWindow(AfxGetApp()->m_pMainWnd->GetSafeHwnd());
}

LRESULT CMainFrame::OnHotKey(WPARAM wParam, LPARAM lParam) {
  MessageBox("A", "Debug", 0);
  if(wParam == kHotkeyRefresh) {
    MessageBox("B", "Debug", 0);
		OnViewRefresh();
    return true;
	}
  return CallNextHookEx(NULL, WM_HOTKEY, wParam,lParam);
}

void CMainFrame::ResizeWindow(COpenScrapeDoc *pDoc)
{
	RECT newrect;
	::GetClientRect(pDoc->attached_hwnd, &newrect);
	AdjustWindowRect(&newrect, GetWindowLong(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), GWL_STYLE), true);
  // We must use theApp.m_pMainWnd->SetWindowPos()
  // as this function can get indirectly called by OpenScrape.cpp
  // if we use the hotkey to refresh.
  // It still triggers an assertion, but no harm seems to be done.
	theApp.m_pMainWnd->SetWindowPos(NULL, 0, 0, newrect.right-newrect.left+4, newrect.bottom-newrect.top+47, SWP_NOMOVE);
}

void CMainFrame::OnViewRefresh()
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	RECT				crect;

	if (pDoc->attached_hwnd && IsWindow(pDoc->attached_hwnd))
	{
		// bring attached window to front
		::SetFocus(pDoc->attached_hwnd);
		::SetForegroundWindow(pDoc->attached_hwnd);
		::SetActiveWindow(pDoc->attached_hwnd);

		SaveBmpPbits();

		// Update saved rect
		::GetClientRect(pDoc->attached_hwnd, &crect);
		pDoc->attached_rect.left = crect.left;
		pDoc->attached_rect.top = crect.top;
		pDoc->attached_rect.right = crect.right;
		pDoc->attached_rect.bottom = crect.bottom;

		ResizeWindow(pDoc);			

		// Instruct table-map dialog to update
		theApp.m_TableMapDlg->update_display();

		ForceRedraw();		
		BringOpenScrapeBackToFront();
	}

	else 
	{
		OnViewConnecttowindow();
	}
}

void CMainFrame::CheckIfOHReplayRunning() {
  // Just a quick and dirty test if a process named "OHReplay.exe" exists.
  // Even some experienced botters didn't know what OHReplay
  // and these buttons are good for.
  //!!!!
  return;
  {
    MessageBox("Unable to switch to preious / next replay-frame.\n"
      "Not connected to OHReplay\n",
      "Warning", 0);
  }
}

void CMainFrame::OnViewPrev()
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	RECT				crect;
  CheckIfOHReplayRunning();
	if (pDoc->attached_hwnd && IsWindow(pDoc->attached_hwnd))
	{
		// bring attached window to front
		::SetFocus(pDoc->attached_hwnd);
		::SetForegroundWindow(pDoc->attached_hwnd);
		::SetActiveWindow(pDoc->attached_hwnd);

		// check if its OHreplay
		char className[20];
		::GetClassName(pDoc->attached_hwnd,className, 20);
		if(strcmp("OHREPLAY", className)==0) 
		{
			// if OHreplay send a tab keypress to goto next screen
			KEYBDINPUT  kb={0};  
			INPUT    Input={0};

			kb.wVk  = VK_SHIFT; 
			Input.type  = INPUT_KEYBOARD;
			Input.ki  = kb;
			::SendInput(1,&Input,sizeof(Input));
			::ZeroMemory(&kb,sizeof(KEYBDINPUT));
			::ZeroMemory(&Input,sizeof(INPUT));

			kb.wVk  = VK_TAB; 
			Input.type  = INPUT_KEYBOARD;
			Input.ki  = kb;
			::SendInput(1,&Input,sizeof(Input)); 
			::ZeroMemory(&kb,sizeof(KEYBDINPUT));
			::ZeroMemory(&Input,sizeof(INPUT));
			
			// generate up 		
			kb.dwFlags  =  KEYEVENTF_KEYUP;
			kb.wVk  = VK_TAB; 
			Input.type  =  INPUT_KEYBOARD;
			Input.ki  =  kb;
			::SendInput(1,&Input,sizeof(Input));
			::ZeroMemory(&kb,sizeof(KEYBDINPUT));
			::ZeroMemory(&Input,sizeof(INPUT));

			kb.dwFlags  =  KEYEVENTF_KEYUP;
			kb.wVk  = VK_SHIFT; 
			Input.type  =  INPUT_KEYBOARD;
			Input.ki  =  kb;
			::SendInput(1,&Input,sizeof(Input));
		}

		Sleep(100); // little time to allow for redraw
		SaveBmpPbits();

		// Update saved rect
		::GetClientRect(pDoc->attached_hwnd, &crect);
		pDoc->attached_rect.left = crect.left;
		pDoc->attached_rect.top = crect.top;
		pDoc->attached_rect.right = crect.right;
		pDoc->attached_rect.bottom = crect.bottom;

		ResizeWindow(pDoc);	

		// Instruct table-map dialog to update
		theApp.m_TableMapDlg->update_display();
		ForceRedraw();
		BringOpenScrapeBackToFront();
	}

	else 
	{
		OnViewConnecttowindow();
	}
}

void CMainFrame::OnViewNext()
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	RECT				crect;
  CheckIfOHReplayRunning();
	if (pDoc->attached_hwnd && IsWindow(pDoc->attached_hwnd))
	{
		// bring attached window to front
		::SetFocus(pDoc->attached_hwnd);
		::SetForegroundWindow(pDoc->attached_hwnd);
		::SetActiveWindow(pDoc->attached_hwnd);

		// check if its OHreplay
		char className[20];
		::GetClassName(pDoc->attached_hwnd,className, 20);
		if(strcmp("OHREPLAY", className)==0) 
		{
			// if OHreplay send a tab keypress to goto next screen
			KEYBDINPUT  kb={0};  
			INPUT    Input={0};
			kb.wVk  = VK_TAB; 
			Input.type  = INPUT_KEYBOARD;
			Input.ki  = kb;
			::SendInput(1,&Input,sizeof(Input));
			// generate up 
			::ZeroMemory(&kb,sizeof(KEYBDINPUT));
			::ZeroMemory(&Input,sizeof(INPUT));
			kb.dwFlags  =  KEYEVENTF_KEYUP;
			kb.wVk  = VK_TAB; 
			Input.type  =  INPUT_KEYBOARD;
			Input.ki  =  kb;
			::SendInput(1,&Input,sizeof(Input));
		}

		Sleep(100); // little time to allow for redraw
		SaveBmpPbits();

		// Update saved rect
		::GetClientRect(pDoc->attached_hwnd, &crect);
		pDoc->attached_rect.left = crect.left;
		pDoc->attached_rect.top = crect.top;
		pDoc->attached_rect.right = crect.right;
		pDoc->attached_rect.bottom = crect.bottom;

		// Set
		int size_x = crect.right - crect.left + 1;
		int size_y = crect.bottom - crect.top + 1;
		SetTablemapSizeIfUnknown(size_x, size_y);

		ResizeWindow(pDoc);	

		// Instruct table-map dialog to update
		theApp.m_TableMapDlg->update_display();
		ForceRedraw();
		BringOpenScrapeBackToFront();
	}

	else 
	{
		OnViewConnecttowindow();
	}
}

void CMainFrame::OnToolsCloneRegions()
{
	CRegionCloner *p_region__cloner = new(CRegionCloner);
	p_region__cloner->CloneRegions();
	delete(p_region__cloner);
}

void CMainFrame::OnGroupregionsBytype()
{
	Registry		reg;
	reg.read_reg();
	reg.region_grouping = BY_TYPE;
	reg.write_reg();

	theApp.m_TableMapDlg->region_grouping = BY_TYPE;
	theApp.m_TableMapDlg->UngroupRegions();
	theApp.m_TableMapDlg->GroupRegions();

	HTREEITEM hRegionNode = theApp.m_TableMapDlg->GetTypeNode("Regions");
	theApp.m_TableMapDlg->m_TableMapTree.SortChildren(hRegionNode);
}

void CMainFrame::OnGroupregionsByname()
{
	Registry		reg;
	reg.read_reg();
	reg.region_grouping = BY_NAME;
	reg.write_reg();

	theApp.m_TableMapDlg->region_grouping = BY_NAME;
	theApp.m_TableMapDlg->UngroupRegions();
	theApp.m_TableMapDlg->GroupRegions();

	HTREEITEM hRegionNode = theApp.m_TableMapDlg->GetTypeNode("Regions");
	theApp.m_TableMapDlg->m_TableMapTree.SortChildren(hRegionNode);
}

void CMainFrame::OnUpdateViewCurrentwindowsize(CCmdUI *pCmdUI)
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	CString				text;

	if (pDoc->attached_hwnd)
	{
		text.Format("Current size: %dx%d", pDoc->attached_rect.right - pDoc->attached_rect.left, 
										   pDoc->attached_rect.bottom - pDoc->attached_rect.top);
		pCmdUI->SetText(text.GetString());
		pCmdUI->Enable(true);
	}

	else
	{
		pCmdUI->SetText("Current size: 0x0");
		pCmdUI->Enable(false);
	}
}

void CMainFrame::OnUpdateEditDuplicateregion(CCmdUI *pCmdUI)
{
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();
	HTREEITEM			parent = NULL;
	CString				sel = "", selected_parent_text = "";
		
	// Get name of currently selected item
	if (theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem())
	{
		sel = theApp.m_TableMapDlg->m_TableMapTree.GetItemText(theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());
		parent = theApp.m_TableMapDlg->m_TableMapTree.GetParentItem(theApp.m_TableMapDlg->m_TableMapTree.GetSelectedItem());
	}

	// Get name of currently selected item's parent
	if (parent != NULL) 
		selected_parent_text = theApp.m_TableMapDlg->m_TableMapTree.GetItemText(parent);

	pCmdUI->Enable(selected_parent_text == "Regions");
}

void CMainFrame::OnUpdateGroupregionsBytype(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_TableMapDlg->region_grouping==BY_TYPE);
}

void CMainFrame::OnUpdateGroupregionsByname(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(theApp.m_TableMapDlg->region_grouping==BY_NAME);
}

BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName)
{
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	GetObject(hBitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
		* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}


	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	if (hOldPal2)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void CMainFrame::SaveBmpPbits(void)
{
	HDC					hdc;
	COpenScrapeDoc		*pDoc = COpenScrapeDoc::GetDocument();

	// Clean up from a previous connect, if needed
	if (pDoc->attached_bitmap != NULL)
	{
		DeleteObject(pDoc->attached_bitmap);
		pDoc->attached_bitmap = NULL;
	}

	if (pDoc->attached_pBits) 
	{
		//delete []pDoc->attached_pBits;
		pDoc->attached_pBits = NULL;
	}

	// Get DC for connected window
	hdc = ::GetDC(pDoc->attached_hwnd);

	// Init COM
	winrt::init_apartment(winrt::apartment_type::multi_threaded);

	// Create Direct 3D Device
	winrt::com_ptr<ID3D11Device> d3dDevice;

	winrt::check_hresult(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr, 0, D3D11_SDK_VERSION, d3dDevice.put(), nullptr, nullptr));


	winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice device;
	const auto dxgiDevice = d3dDevice.as<IDXGIDevice>();
	{
		winrt::com_ptr<::IInspectable> inspectable;
		winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgiDevice.get(), inspectable.put()));
		device = inspectable.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
	}


	auto idxgiDevice2 = dxgiDevice.as<IDXGIDevice2>();
	winrt::com_ptr<IDXGIAdapter> adapter;
	winrt::check_hresult(idxgiDevice2->GetParent(winrt::guid_of<IDXGIAdapter>(), adapter.put_void()));
	winrt::com_ptr<IDXGIFactory2> factory;
	winrt::check_hresult(adapter->GetParent(winrt::guid_of<IDXGIFactory2>(), factory.put_void()));

	ID3D11DeviceContext* d3dContext = nullptr;
	d3dDevice->GetImmediateContext(&d3dContext);

	RECT rect {};
	DwmGetWindowAttribute(pDoc->attached_hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
	const auto size = winrt::Windows::Graphics::SizeInt32{ rect.right - rect.left, rect.bottom - rect.top };

	winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool m_framePool =
		winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::Create(
			device,
			winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized,
			2,
			size);

	const auto activationFactory = winrt::get_activation_factory<
		winrt::Windows::Graphics::Capture::GraphicsCaptureItem>();
	auto interopFactory = activationFactory.as<IGraphicsCaptureItemInterop>();
	winrt::Windows::Graphics::Capture::GraphicsCaptureItem captureItem = { nullptr };
	interopFactory->CreateForWindow(pDoc->attached_hwnd, winrt::guid_of<ABI::Windows::Graphics::Capture::IGraphicsCaptureItem>(),
		reinterpret_cast<void**>(winrt::put_abi(captureItem)));

	auto isFrameArrived = false;
	winrt::com_ptr<ID3D11Texture2D> texture;
	const auto session = m_framePool.CreateCaptureSession(captureItem);
	m_framePool.FrameArrived([&](auto& framePool, auto&)
		{
			if (isFrameArrived) return;
			auto frame = framePool.TryGetNextFrame();

			struct __declspec(uuid("A9B3D012-3DF2-4EE3-B8D1-8695F457D3C1"))
				IDirect3DDxgiInterfaceAccess : ::IUnknown
			{
				virtual HRESULT __stdcall GetInterface(GUID const& id, void** object) = 0;
			};

			auto access = frame.Surface().as<IDirect3DDxgiInterfaceAccess>();
			access->GetInterface(winrt::guid_of<ID3D11Texture2D>(), texture.put_void());
			isFrameArrived = true;
			return;
		});


	session.IsCursorCaptureEnabled(false);
	session.StartCapture();


	// Message pump
	MSG msg;
	clock_t timer = clock();
	while (!isFrameArrived)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
			DispatchMessage(&msg);

		if (clock() - timer > 20000)
		{
			// TODO: try to make here a better error handling
			return;
		}
	}

	session.Close();

	D3D11_TEXTURE2D_DESC capturedTextureDesc;
	texture->GetDesc(&capturedTextureDesc);

	capturedTextureDesc.Usage = D3D11_USAGE_STAGING;
	capturedTextureDesc.BindFlags = 0;
	capturedTextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	capturedTextureDesc.MiscFlags = 0;

	winrt::com_ptr<ID3D11Texture2D> userTexture = nullptr;
	winrt::check_hresult(d3dDevice->CreateTexture2D(&capturedTextureDesc, NULL, userTexture.put()));

	d3dContext->CopyResource(userTexture.get(), texture.get());


	D3D11_MAPPED_SUBRESOURCE resource;
	winrt::check_hresult(d3dContext->Map(userTexture.get(), NULL, D3D11_MAP_READ, 0, &resource));

	BITMAPINFO lBmpInfo;

	// BMP 32 bpp
	ZeroMemory(&lBmpInfo, sizeof(BITMAPINFO));
	lBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lBmpInfo.bmiHeader.biBitCount = 32;
	lBmpInfo.bmiHeader.biCompression = BI_RGB;
	lBmpInfo.bmiHeader.biWidth = capturedTextureDesc.Width;
	lBmpInfo.bmiHeader.biHeight = capturedTextureDesc.Height;
	lBmpInfo.bmiHeader.biPlanes = 1;
	lBmpInfo.bmiHeader.biSizeImage = capturedTextureDesc.Width * capturedTextureDesc.Height * 4;

	std::unique_ptr<BYTE> pBuf(new BYTE[lBmpInfo.bmiHeader.biSizeImage]);
	UINT lBmpRowPitch = capturedTextureDesc.Width * 4;
	auto sptr = static_cast<BYTE*>(resource.pData);
	auto dptr = pBuf.get() + lBmpInfo.bmiHeader.biSizeImage - lBmpRowPitch;

	UINT lRowPitch = std::min<UINT>(lBmpRowPitch, resource.RowPitch);

	for (size_t h = 0; h < capturedTextureDesc.Height; ++h)
	{
		memcpy_s(dptr, lBmpRowPitch, sptr, lRowPitch);
		sptr += resource.RowPitch;
		dptr -= lBmpRowPitch;
	}


	void* bits = (void*)(pBuf.get());

	HBITMAP hBmp = CreateDIBitmap(hdc, &lBmpInfo.bmiHeader, CBM_INIT, bits, &lBmpInfo, DIB_RGB_COLORS);
	//SaveHBITMAPToFile(hBmp, "output.bmp");

	// Crop window image to client rect
	RECT rcNonCli = { 0 }; //calculate non-client offsets here
	RECT rcClient = { 0 };
	::GetClientRect(pDoc->attached_hwnd, &rcClient);
	RECT rcWin = { 0 };
	::GetWindowRect(pDoc->attached_hwnd, &rcWin);
	POINT ptClient = { 0 };
	::ClientToScreen(pDoc->attached_hwnd, &ptClient);

	rcNonCli.left = ptClient.x - rcWin.left;
	rcNonCli.top = ptClient.y - rcWin.top;
	rcNonCli.right = rcWin.right - ptClient.x - rcClient.right;
	rcNonCli.bottom = rcWin.bottom - ptClient.y - rcClient.bottom;

	int Width = rcClient.right - rcClient.left;
	int Height = rcClient.bottom - rcClient.top;
	rcClient.top += rcNonCli.top;
	rcClient.left += rcNonCli.left;
	rcClient.right -= rcNonCli.right;;
	rcClient.bottom -= rcNonCli.bottom;

	// Save bitmap of connected window
	HDC hdc_bitmap_orig = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap_orig = (HBITMAP)SelectObject(hdc_bitmap_orig, hBmp);
	HDC hdc_bitmap_transform = CreateCompatibleDC(hdc);
	HBITMAP bitmap_transform = CreateCompatibleBitmap(hdc, Width, Height);
	HBITMAP old_bitmap_transform = (HBITMAP)SelectObject(hdc_bitmap_transform, bitmap_transform);

	BitBlt(hdc_bitmap_transform, 0, 0, Width, Height, hdc_bitmap_orig, rcClient.left, rcClient.top, SRCCOPY);

	//SaveHBITMAPToFile(bitmap_transform, "output.bmp");
	pDoc->attached_bitmap = bitmap_transform;

	// Get pBits of connected window
	// Allocate heap space for BITMAPINFO
	BITMAPINFO* bmi;
	int			info_len = sizeof(BITMAPINFOHEADER) + 1024;
	bmi = (BITMAPINFO*) ::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, info_len);

	// Populate BITMAPINFOHEADER
	bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
	bmi->bmiHeader.biBitCount = 0;
	::GetDIBits(hdc, pDoc->attached_bitmap, 0, 0, NULL, bmi, DIB_RGB_COLORS);

	// Get the actual argb bit information
	bmi->bmiHeader.biHeight = -bmi->bmiHeader.biHeight;
	pDoc->attached_pBits = new BYTE[bmi->bmiHeader.biSizeImage];
	::GetDIBits(hdc, pDoc->attached_bitmap, 0, Height, pDoc->attached_pBits, bmi, DIB_RGB_COLORS);

	// Clean up
	HeapFree(GetProcessHeap(), NULL, bmi);
	SelectObject(hdc_bitmap_transform, old_bitmap_transform);
	::ReleaseDC(pDoc->attached_hwnd, hdc);
	DeleteDC(hdc_bitmap_transform);

	SelectObject(hdc_bitmap_orig, old_bitmap_orig);
	DeleteDC(hdc_bitmap_orig);

	DeleteDC(hdc);
}

CArray <STableList, STableList>		g_tlist; 

BOOL CALLBACK EnumProcTopLevelWindowList(HWND hwnd, LPARAM lparam) 
{
	CString				title, winclass;
	char				text[512];
	RECT				crect;
	STableList			tablelisthold;

	// If this is not a top level window, then return
	if (GetParent(hwnd) != NULL)
		return true;

	// If this window is not visible, then return
	if (!IsWindowVisible(hwnd))
		return true;

	/* We use this when we only want windows with title text
	// If there is no caption on this window, then return
	GetWindowText(hwnd, text, sizeof(text));
	if (strlen(text)==0)
		return true;

	title = text;
	*/

	// We use this when we want every existing window
	// by setting the title text of non title text windows as "HWND: " + hwnd
	GetWindowText(hwnd, text, sizeof(text));
	if (strlen(text)==0)
		title.AppendFormat("HWND: %i", hwnd);
	else
		title = text;
	

	// Found a window, get client area rect
	GetClientRect(hwnd, &crect);

	// Save it in the list
	tablelisthold.hwnd = hwnd;
	tablelisthold.title = title;
	tablelisthold.crect.left = crect.left;
	tablelisthold.crect.top = crect.top;
	tablelisthold.crect.right = crect.right;
	tablelisthold.crect.bottom = crect.bottom;
	g_tlist.Add(tablelisthold);

	return true;  // keep processing through entire list of windows
}

