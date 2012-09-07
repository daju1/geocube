/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Mon Jun 29 11:20:03 1998
 */
/* Compiler settings for D:\BookCode\ex33a\consumebiblio.odl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __Consumebiblio_i_h__
#define __Consumebiblio_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IConsumebiblio_FWD_DEFINED__
#define __IConsumebiblio_FWD_DEFINED__
typedef interface IConsumebiblio IConsumebiblio;
#endif 	/* __IConsumebiblio_FWD_DEFINED__ */


#ifndef __Consumebiblio_FWD_DEFINED__
#define __Consumebiblio_FWD_DEFINED__

#ifdef __cplusplus
typedef class Consumebiblio Consumebiblio;
#else
typedef struct Consumebiblio Consumebiblio;
#endif /* __cplusplus */

#endif 	/* __Consumebiblio_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Consumebiblio_LIBRARY_DEFINED__
#define __Consumebiblio_LIBRARY_DEFINED__

/* library Consumebiblio */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Consumebiblio;

#ifndef __IConsumebiblio_DISPINTERFACE_DEFINED__
#define __IConsumebiblio_DISPINTERFACE_DEFINED__

/* dispinterface IConsumebiblio */
/* [uuid] */ 


EXTERN_C const IID DIID_IConsumebiblio;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("486A1B85-0D94-11D2-8CAA-DF2C53524146")
    IConsumebiblio : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IConsumebiblioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConsumebiblio __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConsumebiblio __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConsumebiblio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IConsumebiblio __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IConsumebiblio __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IConsumebiblio __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IConsumebiblio __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IConsumebiblioVtbl;

    interface IConsumebiblio
    {
        CONST_VTBL struct IConsumebiblioVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConsumebiblio_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConsumebiblio_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConsumebiblio_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConsumebiblio_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConsumebiblio_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConsumebiblio_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConsumebiblio_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IConsumebiblio_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Consumebiblio;

#ifdef __cplusplus

class DECLSPEC_UUID("486A1B83-0D94-11D2-8CAA-DF2C53524146")
Consumebiblio;
#endif
#endif /* __Consumebiblio_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
