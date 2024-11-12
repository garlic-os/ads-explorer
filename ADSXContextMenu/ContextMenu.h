/*
 * Copyright (c) 2004 Pascal Hurni
 */

#pragma once


#include "StdAfx.h"  // Precompiled header; include first

#include "ADSXContextMenu_h.h"

#include "resource.h"  // main symbols


//==============================================================================

// Set the return string 'Source' in the STRRET struct.
// Returns false if memory allocation fails.
bool SetReturnString(_In_ PCWSTR pszSource, _Out_ STRRET *strret);


//==============================================================================
// CADSXContextMenu

class ATL_NO_VTABLE CADSXContextMenu
	: public CComObjectRootEx<CComSingleThreadModel>,
	  public CComCoClass<CADSXContextMenu, &CLSID_ADSXContextMenuContextMenu>,
	  public IShellFolder2,
	  public IPersistFolder2,
	  public IShellDetails {
   public:
	CADSXContextMenu();
	virtual ~CADSXContextMenu();

	DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTMENU)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CADSXContextMenu)
		COM_INTERFACE_ENTRY(IShellFolder)
		COM_INTERFACE_ENTRY(IShellFolder2)
		COM_INTERFACE_ENTRY(IPersistFolder)
		COM_INTERFACE_ENTRY(IPersistFolder2)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY_IID(IID_IShellDetails, IShellDetails)
	END_COM_MAP()

	//--------------------------------------------------------------------------
	// IPersist
	STDMETHOD(GetClassID)(_Out_ CLSID*);

	//--------------------------------------------------------------------------
	// IPersistFolder(2)
	STDMETHOD(Initialize)(_In_ PCIDLIST_ABSOLUTE);
	STDMETHOD(GetCurFolder)(_Outptr_ PIDLIST_ABSOLUTE*);

	//--------------------------------------------------------------------------
	// IShellFolder
	STDMETHOD(BindToObject)(_In_ PCUIDLIST_RELATIVE, _In_opt_ IBindCtx*, _In_ REFIID, _COM_Outptr_ void**);
	STDMETHOD(CompareIDs)(_In_ LPARAM, _In_ PCUIDLIST_RELATIVE, _In_ PCUIDLIST_RELATIVE);
	STDMETHOD(CreateViewObject)(_In_ HWND, _In_ REFIID, _COM_Outptr_ void**);
	STDMETHOD(EnumObjects)(_In_ HWND, _In_ SHCONTF, _COM_Outptr_ IEnumIDList**);
	STDMETHOD(GetAttributesOf)(_In_ UINT, _In_ PCUITEMID_CHILD_ARRAY, _Inout_ SFGAOF*);
	STDMETHOD(GetUIObjectOf)(_In_ HWND, _In_ UINT, _In_ PCUITEMID_CHILD_ARRAY, _In_ REFIID, _Inout_ UINT*, _COM_Outptr_ void**);
	STDMETHOD(BindToStorage)(_In_ PCUIDLIST_RELATIVE, _In_ IBindCtx*, _In_ REFIID, _COM_Outptr_ void**);
	STDMETHOD(GetDisplayNameOf)(_In_ PCUITEMID_CHILD, _In_ SHGDNF, _Out_ STRRET*);
	STDMETHOD(ParseDisplayName)(_In_ HWND, _In_opt_ IBindCtx*, _In_ PWSTR, _Out_opt_ ULONG*, _Outptr_ PIDLIST_RELATIVE*, _Inout_opt_ ULONG*);
	STDMETHOD(SetNameOf)(_In_ HWND, _In_ PCUITEMID_CHILD, _In_ PCWSTR, _In_ SHGDNF, _Outptr_ PITEMID_CHILD*);

	//--------------------------------------------------------------------------
	// IShellDetails
	STDMETHOD(ColumnClick)(_In_ UINT);
	STDMETHOD(GetDetailsOf)(_In_opt_ PCUITEMID_CHILD, _In_ UINT, _Out_ SHELLDETAILS*);

	//--------------------------------------------------------------------------
	// IShellFolder2
	STDMETHOD(EnumSearches)(_COM_Outptr_ IEnumExtraSearch**);
	STDMETHOD(GetDefaultColumn)(_In_ DWORD, _Out_ ULONG*, _Out_ ULONG*);
	STDMETHOD(GetDefaultColumnState)(_In_ UINT, _Out_ SHCOLSTATEF*);
	STDMETHOD(GetDefaultSearchGUID)(_Out_ GUID*);
	STDMETHOD(GetDetailsEx)(_In_ PCUITEMID_CHILD, _In_ const SHCOLUMNID*, _Out_ VARIANT*);
	// Already in IShellDetails:
	// STDMETHOD(GetDetailsOf) (PCUITEMID_CHILD, UINT, SHELLDETAILS*);
	STDMETHOD(MapColumnToSCID)(_In_ UINT, _Out_ SHCOLUMNID*);

	//--------------------------------------------------------------------------

   protected:
	
};