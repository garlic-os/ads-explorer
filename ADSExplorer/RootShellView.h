/*
 * Copyright (c) 2004 Pascal Hurni
 */

#pragma once

#include "StdAfx.h"  // Precompiled header; include first

#include <iomanip>

#include "ShellFolderView.h"

// define some undocumented messages. See "shlext.h" from Henk Devos & Andrew Le
// Bihan, at http://www.whirlingdervishes.com/nselib/public
#define SFVCB_SELECTIONCHANGED 0x0008
#define SFVCB_DRAWMENUITEM 0x0009
#define SFVCB_MEASUREMENUITEM 0x000A
#define SFVCB_EXITMENULOOP 0x000B
#define SFVCB_VIEWRELEASE 0x000C
#define SFVCB_GETNAMELENGTH 0x000D
#define SFVCB_WINDOWCLOSING 0x0010
#define SFVCB_LISTREFRESHED 0x0011
#define SFVCB_WINDOWFOCUSED 0x0012
#define SFVCB_REGISTERCOPYHOOK 0x0014
#define SFVCB_COPYHOOKCALLBACK 0x0015
#define SFVCB_ADDINGOBJECT 0x001D
#define SFVCB_REMOVINGOBJECT 0x001E

#define SFVCB_GETCOMMANDDIR 0x0021
#define SFVCB_GETCOLUMNSTREAM 0x0022
#define SFVCB_CANSELECTALL 0x0023
#define SFVCB_ISSTRICTREFRESH 0x0025
#define SFVCB_ISCHILDOBJECT 0x0026
#define SFVCB_GETEXTVIEWS 0x0028
#define SFVCB_WNDMAIN 46
#define SFVCB_COLUMNCLICK2 0x32

// Debug log prefix for CADSXRootShellView
#define P_RSV L"CADSXRootShellView(0x" << std::hex << this << L")::"

// Macros to trace the message name instead of its ID
#define BEGIN_TRACE_MSG_NAME() switch (uMsg) {
#define TRACE_MSG_NAME(name)                                                     \
	case name:                                                                   \
		LOG(L"CADSXRootShellView(0x" << std::hex << this << L") " << _T(#name)); \
		break;
#define END_TRACE_MSG_NAME()                                                    \
	default:                                                                    \
		LOG(                                                                    \
			L"CADSXRootShellView(0x" << std::hex << this << L") Msg: " <<       \
			std::setw(2) << uMsg << L":" << std::hex << std::setw(2) << uMsg << \
			L" w=" << static_cast<int>(wParam) << L","                          \
			L" l=" << static_cast<int>(lParam)                                  \
		);                                                                      \
	}


// This class does very little but trace the messages.
// You can add message handlers like the SFVM_COLUMNCLICK.
class CADSXRootShellView : public CShellFolderViewImpl {
   public:
	CADSXRootShellView() {
		LOG(P_RSV << L"CADSXRootShellView()");
	}

	~CADSXRootShellView() {
		LOG(P_RSV << L"~CADSXRootShellView()");
	}

	// If called, the passed object will be held (AddRef()'d) until the View
	// gets deleted.
	void Init(IUnknown *pUnkOwner = NULL) { m_UnkOwnerPtr = pUnkOwner; }

	// The message map
	BEGIN_MSG_MAP(CADSXRootShellView)
		// BEGIN_TRACE_MSG_NAME()
		// 	TRACE_MSG_NAME(SFVM_MERGEMENU)
		// 	TRACE_MSG_NAME(SFVM_INVOKECOMMAND)
		// 	TRACE_MSG_NAME(SFVM_GETHELPTEXT)
		// 	TRACE_MSG_NAME(SFVM_GETTOOLTIPTEXT)
		// 	TRACE_MSG_NAME(SFVM_GETBUTTONINFO)
		// 	TRACE_MSG_NAME(SFVM_GETBUTTONS)
		// 	TRACE_MSG_NAME(SFVM_INITMENUPOPUP)
		// 	TRACE_MSG_NAME(SFVM_FSNOTIFY)
		// 	TRACE_MSG_NAME(SFVM_WINDOWCREATED)
		// 	TRACE_MSG_NAME(SFVM_GETDETAILSOF)
		// 	TRACE_MSG_NAME(SFVM_COLUMNCLICK)
		// 	TRACE_MSG_NAME(SFVM_QUERYFSNOTIFY)
		// 	TRACE_MSG_NAME(SFVM_DEFITEMCOUNT)
		// 	TRACE_MSG_NAME(SFVM_DEFVIEWMODE)
		// 	TRACE_MSG_NAME(SFVM_UNMERGEMENU)
		// 	TRACE_MSG_NAME(SFVM_UPDATESTATUSBAR)
		// 	TRACE_MSG_NAME(SFVM_BACKGROUNDENUM)
		// 	TRACE_MSG_NAME(SFVM_DIDDRAGDROP)
		// 	TRACE_MSG_NAME(SFVM_SETISFV)
		// 	TRACE_MSG_NAME(SFVM_THISIDLIST)
		// 	TRACE_MSG_NAME(SFVM_ADDPROPERTYPAGES)
		// 	TRACE_MSG_NAME(SFVM_BACKGROUNDENUMDONE)
		// 	TRACE_MSG_NAME(SFVM_GETNOTIFY)
		// 	TRACE_MSG_NAME(SFVM_GETSORTDEFAULTS)
		// 	TRACE_MSG_NAME(SFVM_SIZE)
		// 	TRACE_MSG_NAME(SFVM_GETZONE)
		// 	TRACE_MSG_NAME(SFVM_GETPANE)
		// 	TRACE_MSG_NAME(SFVM_GETHELPTOPIC)
		// 	TRACE_MSG_NAME(SFVM_GETANIMATION)

		// 	TRACE_MSG_NAME(SFVCB_SELECTIONCHANGED)
		// 	TRACE_MSG_NAME(SFVCB_DRAWMENUITEM)
		// 	TRACE_MSG_NAME(SFVCB_MEASUREMENUITEM)
		// 	TRACE_MSG_NAME(SFVCB_EXITMENULOOP)
		// 	TRACE_MSG_NAME(SFVCB_VIEWRELEASE)
		// 	TRACE_MSG_NAME(SFVCB_GETNAMELENGTH)
		// 	TRACE_MSG_NAME(SFVCB_WINDOWCLOSING)
		// 	TRACE_MSG_NAME(SFVCB_LISTREFRESHED)
		// 	TRACE_MSG_NAME(SFVCB_WINDOWFOCUSED)
		// 	TRACE_MSG_NAME(SFVCB_REGISTERCOPYHOOK)
		// 	TRACE_MSG_NAME(SFVCB_COPYHOOKCALLBACK)
		// 	TRACE_MSG_NAME(SFVCB_ADDINGOBJECT)
		// 	TRACE_MSG_NAME(SFVCB_REMOVINGOBJECT)
		// 	TRACE_MSG_NAME(SFVCB_GETCOMMANDDIR)
		// 	TRACE_MSG_NAME(SFVCB_GETCOLUMNSTREAM)
		// 	TRACE_MSG_NAME(SFVCB_CANSELECTALL)
		// 	TRACE_MSG_NAME(SFVCB_ISSTRICTREFRESH)
		// 	TRACE_MSG_NAME(SFVCB_ISCHILDOBJECT)
		// 	TRACE_MSG_NAME(SFVCB_COLUMNCLICK2)
		// 	TRACE_MSG_NAME(SFVCB_GETEXTVIEWS)
		// 	TRACE_MSG_NAME(SFVCB_WNDMAIN)
		// END_TRACE_MSG_NAME()

		MESSAGE_HANDLER(SFVM_COLUMNCLICK, OnColumnClick)
		MESSAGE_HANDLER(SFVM_GETDETAILSOF, OnGetDetailsOf)
		MESSAGE_HANDLER(SFVM_DEFVIEWMODE, OnDefViewMode)
	END_MSG_MAP()

	// Offer to set the default view mode
	LRESULT
	OnDefViewMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
		LOG(P_RSV << L"OnDefViewMode()");
		#ifdef FVM_CONTENT
			/* Requires Windows 7+, by Gravis' request */
			DWORD ver, maj, min;
			ver = GetVersion();
			maj = (DWORD) (LOBYTE(LOWORD(dwVersion)));
			min = (DWORD) (HIBYTE(LOWORD(dwVersion)));
			if (maj > 6 || (maj == 6 && min >= 1)) {
				*(FOLDERVIEWMODE *) lParam = FVM_CONTENT;
			}
		#endif
		// return WrapReturn(S_OK);
		return S_OK;
	}

	// When a user clicks on a column header in details mode
	LRESULT
	OnColumnClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
		LOG(P_RSV << L"OnColumnClick(iColumn=" << static_cast<int>(wParam) << L")");

		// Shell version 4.7x doesn't understand S_FALSE as described in the
		// SDK.
		SendFolderViewMessage(SFVM_REARRANGE, wParam);
		// return WrapReturn(S_OK);
		return S_OK;
	}

	// This message is used with shell version 4.7x, shell 5 and above prefer to
	// use IShellFolder2::GetDetailsOf()
	LRESULT
	OnGetDetailsOf(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
		int iColumn = static_cast<int>(wParam);
		auto pDetailsInfo = reinterpret_cast<DETAILSINFO *>(lParam);

		LOG(P_RSV << L"OnGetDetailsOf(iColumn=" << iColumn << L")");

		// if (pDetailsInfo == NULL) return WrapReturn(E_POINTER);
		if (pDetailsInfo == NULL) return E_POINTER;

		HRESULT hr;
		SHELLDETAILS ShellDetails;

		IShellDetails *pShellDetails;
		hr = m_psf->QueryInterface(IID_PPV_ARGS(&pShellDetails));
		if (FAILED(hr)) return hr;

		hr = pShellDetails->GetDetailsOf(pDetailsInfo->pidl, iColumn, &ShellDetails);
		pShellDetails->Release();
		if (FAILED(hr)) return hr;

		pDetailsInfo->cxChar = ShellDetails.cxChar;
		pDetailsInfo->fmt = ShellDetails.fmt;
		pDetailsInfo->str = ShellDetails.str;
		pDetailsInfo->iImage = 0;

		// return WrapReturn(S_OK);
		return S_OK;
	}

   protected:
	CComPtr<IUnknown> m_UnkOwnerPtr;
};
