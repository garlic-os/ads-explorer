/*
 * Copyright (c) 2004 Pascal Hurni
 * Copyright (c) 2024 Nate Kean
 */

#pragma once

#include "StdAfx.h"  // Precompiled header; include first
#include "ADSExplorer_h.h"  // Generated by MIDL
#include "resource.h"  // Resource IDs from the RC file

namespace ADSX {


class ATL_NO_VTABLE CContextMenuEntry
	: public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CContextMenuEntry, &CLSID_ADSXContextMenuEntry>,
	  public IShellExtInit,
	  public IContextMenu {
   public:
	CContextMenuEntry(void);
	virtual ~CContextMenuEntry(void);

	DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTMENUENTRY)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CContextMenuEntry)
		COM_INTERFACE_ENTRY(IShellExtInit)
		COM_INTERFACE_ENTRY(IContextMenu)
	END_COM_MAP()

	//--------------------------------------------------------------------------
	// IShellExtInit
	IFACEMETHOD(Initialize)(
		_In_opt_ PCIDLIST_ABSOLUTE pidlFolder,
		_In_     IDataObject*      pdo,
		_In_     HKEY              hkeyProgID
	);

	//--------------------------------------------------------------------------
	// IContextMenu
	IFACEMETHOD(GetCommandString)(
		_In_                 UINT_PTR idCmd,
		_In_                 UINT     uFlags,
		_In_                 UINT*    puReserved,
		_Out_writes_(cchMax) LPSTR    pszName,
		_In_                 UINT     cchMax
	);

	IFACEMETHOD(InvokeCommand)(
		_In_ CMINVOKECOMMANDINFO* pici
	);

	IFACEMETHOD(QueryContextMenu)(
		_In_ HMENU hmenu,
		_In_ UINT  i,
		_In_ UINT  uidCmdFirst,
		_In_ UINT  uidCmdLast,
		_In_ UINT  uFlags
	);

   protected:
	constexpr static WCHAR szPrefix[] = 
		L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\"
		L"::{ED383D11-6797-4103-85EF-CBDB8DEB50E2}\\";
	PWSTR m_pszADSPath;
};

}  // namespace ADSX
