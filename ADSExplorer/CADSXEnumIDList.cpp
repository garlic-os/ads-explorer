#include "stdafx.h"  // MUST be included first

#include "CADSXEnumIDList.h"

#include <handleapi.h>
#include <winnt.h>

#include "CADSXItem.h"
#include "PidlMgr.h"


// Convert a WIN32_FIND_STREAM_DATA to a PIDL and add it to the output array
// pushin p
static bool PushPidl(
	/* [in]     */ WIN32_FIND_STREAM_DATA *fsd,
	// POINTER! to the destination array cursor because we're going to
	// modify it (advance it).
	// Fun Fact: This is a pointer to an array of pointers to ITEMID_CHILDren.
	// A real triple pointer. How awful is that? :)
	/* [in/out] */ PITEMID_CHILD **ppelt,
	/* [out]    */ ULONG *nActual
) {
	// Reusable item
	static CADSXItem Item;

	// Fill in the item
	Item.m_Filesize = fsd->StreamSize.QuadPart;
	Item.m_Name = fsd->cStreamName;

	// Copy this item into a PIDL and put that into the output array
	PITEMID_CHILD pidl = PidlMgr::Create(Item);
	if (pidl == NULL) {
		SetLastError(ERROR_OUTOFMEMORY);
		return false;
	}
	**ppelt = pidl;

	// Advance the enumerator
	*ppelt += sizeof(PITEMID_CHILD);
	++*nActual;
	return true;
}

// Find one or more items with NextInternal and discard them.
static bool NoOp(WIN32_FIND_STREAM_DATA *fsd, PITEMID_CHILD **ppelt, ULONG *nActual) {
	UNREFERENCED_PARAMETER(fsd);
	UNREFERENCED_PARAMETER(ppelt);
	UNREFERENCED_PARAMETER(nActual);
	return true;
}


CADSXEnumIDList::CADSXEnumIDList()
	: m_hFinder(NULL),
	  m_nTotalFetched(0) {
	DebugPrint("CADSXEnumIDList(0x%08x)::CADSXEnumIDList()\n", this);
}

CADSXEnumIDList::~CADSXEnumIDList() {
	DebugPrint("CADSXEnumIDList(0x%08x)::~CADSXEnumIDList()\n", this);
	if (m_hFinder != NULL) {
		FindClose(m_hFinder);
	}
	SysFreeString(m_pszPath);
}

void CADSXEnumIDList::Init(IUnknown *pUnkOwner, const BSTR pszPath) {
	DebugPrint("CADSXEnumIDList(0x%08x)::Init()\n", this);
	m_pUnkOwner = pUnkOwner;
	m_pszPath = pszPath;
}


// Find one or more items with NextInternal and push them to the
// output array rgelt with PushPidl.
HRESULT CADSXEnumIDList::Next(
	/* [in]  */ ULONG celt,
	/* [out] */ PITEMID_CHILD *rgelt,
	/* [out] */ ULONG *pceltFetched
) {
	DebugPrint("CADSXEnumIDList(0x%08x)::Next(celt=%lu)\n", this, celt);
	return NextInternal(&PushPidl, celt, rgelt, pceltFetched);
}


HRESULT CADSXEnumIDList::NextInternal(
	/* [in]  */ FnConsume fnConsume,   // callback on item found
	/* [in]  */ ULONG celt,            // number of pidls requested
	/* [out] */ PITEMID_CHILD *rgelt,  // array of pidls
	/* [out] */ ULONG *pceltFetched    // actual number of pidls fetched
) {
	if (rgelt == NULL || (celt != 1 && pceltFetched == NULL)) {
		DebugPrint("** Bad argument(s)\n");
		return E_POINTER;
	}
	if (celt == 0) {
		DebugPrint("** 0 requested :/ vacuous success\n");
		return S_OK;
	}

	static WIN32_FIND_STREAM_DATA fsd;
	ULONG nActual = 0;
	PITEMID_CHILD *pelt = rgelt;
	bool bPushPidlSuccess;

	// Initialize the finder if it hasn't been already with a call to
	// FindFirstStream instead of FindNextStream.
	// Call the callback on this first item.
	if (m_hFinder == NULL) {
		m_hFinder = FindFirstStreamW(m_pszPath, FindStreamInfoStandard, &fsd, 0);
		if (m_hFinder == INVALID_HANDLE_VALUE) {
			m_hFinder = NULL;
			switch (GetLastError()) {
				case ERROR_SUCCESS:
					DebugPrint(
						"** FindFirstStreamW returned INVALID_HANDLE_VALUE "
						"but GetLastError() == ERROR_SUCCESS\n"
					);
					return E_FAIL;
				case ERROR_HANDLE_EOF:
					DebugPrint("** No streams found\n");
					return S_FALSE;
				default:
					DebugPrint("** latery Eror! Er Erry Err! later\n");
					return HRESULT_FROM_WIN32(GetLastError());
			}
		}
		if (GetLastError() == ERROR_HANDLE_EOF) {
			DebugPrint("** No streams found\n");
			return S_FALSE;
		}
		bPushPidlSuccess = fnConsume(&fsd, &pelt, &nActual);
		if (!bPushPidlSuccess) {
			DebugPrint("** latery Eror! Er Erry Err! later\n");
			return HRESULT_FROM_WIN32(GetLastError());
		}
	}

	// The main loop body that the rest of the calls to Next will skip to.
	// Each loop calls the callback on another stream.
	bool bFindStreamStopped = false;
	while (!bFindStreamStopped && nActual < celt) {
		bFindStreamStopped = !FindNextStreamW(m_hFinder, &fsd);
		if (bFindStreamStopped) {
			if (GetLastError() == ERROR_HANDLE_EOF) {
				// Do nothing and let the loop end
			} else {
				// Stream has stopped unexpectedly
				DebugPrint("** latery Eror! Er Erry Err! later\n");
				return HRESULT_FROM_WIN32(GetLastError());
			}
		} else {
			// Consume stream
			bPushPidlSuccess = fnConsume(&fsd, &pelt, &nActual);
			if (!bPushPidlSuccess) {
				DebugPrint("** latery Eror! Er Erry Err! later\n");
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}
	}
	if (pceltFetched != NULL) {  // Bookkeeping
		*pceltFetched = nActual;
	}
	m_nTotalFetched += nActual;
	if (nActual < celt) {
		DebugPrint("** Ran out\n");
		return S_FALSE;
	}
	return S_OK;
}


HRESULT CADSXEnumIDList::Reset() {
	DebugPrint("CADSXEnumIDList(0x%08x)::Reset()\n", this);
	if (m_hFinder != NULL) {
		BOOL success = FindClose(m_hFinder);
		m_hFinder = NULL;
		m_nTotalFetched = 0;
		if (!success) return HRESULT_FROM_WIN32(GetLastError());
	}
	return S_OK;
}


HRESULT CADSXEnumIDList::Skip(/* [in] */ ULONG celt) {
	DebugPrint("CADSXEnumIDList(0x%08x)::Skip(celt=%lu)\n", this, celt);
	ULONG pceltFetchedFake = 0;
	PITEMID_CHILD *rgeltFake = NULL;
	return NextInternal(&NoOp, celt, rgeltFake, &pceltFetchedFake);
}


HRESULT CADSXEnumIDList::Clone(/* [out] */ IEnumIDList **ppEnum) {
	DebugPrint("CADSXEnumIDList(0x%08x)::Clone()\n", this);
	if (ppEnum == NULL) return E_POINTER;

	CComObject<CADSXEnumIDList> *pNewEnum;
	HRESULT hr = CComObject<CADSXEnumIDList>::CreateInstance(&pNewEnum);
	if (FAILED(hr)) return hr;
	pNewEnum->Init(m_pUnkOwner, m_pszPath);
	
	// Unfortunately I don't see any more an efficient way to do this with
	// the Find Stream API :(
	pNewEnum->Skip(m_nTotalFetched);

	hr = pNewEnum->QueryInterface(IID_IEnumIDList, (void **) ppEnum);
	if (FAILED(hr)) return hr;
	return S_OK;
}
