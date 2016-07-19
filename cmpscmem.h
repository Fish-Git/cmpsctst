/* CMPSCMEM.H   (c) Copyright "Fish" (David B. Trout), 2012-2014     */
/*              Compression Call Memory Access Functions             */
/*                                                                   */
/*   Released under "The Q Public License Version 1"                 */
/*   (http://www.hercules-390.org/herclic.html) as modifications to  */
/*   Hercules.                                                       */

#ifndef _CMPSCMEM_H_
#define _CMPSCMEM_H_    // Code to be compiled ONLY ONCE goes after here

///////////////////////////////////////////////////////////////////////////////
// Operand memory access control block

struct MEMBLK           // Operand memory access control block
{
    REGS*  regs;        // Pointer to register context
    U64    vpagebeg;    // MADDR virtual base address
    U8*    maddr[2];    // Operand page MADDRs
    int    arn;         // Operand register number
    U8     pkey;        // PSW key
};
typedef struct MEMBLK MEMBLK;

///////////////////////////////////////////////////////////////////////////////
// (simple helper macros with more descriptive names)

#ifndef PTR_IS_ALIGNED              // (machdep.h may have already defined it)
#define PTR_IS_ALIGNED( p, n )      (!(((uintptr_t)(p))&((n)-1)))
#define PTR_IS_HW_ALIGNED( p )      PTR_IS_ALIGNED( (p), 2 )
#define PTR_IS_FW_ALIGNED( p )      PTR_IS_ALIGNED( (p), 4 )
#define PTR_IS_DW_ALIGNED( p )      PTR_IS_ALIGNED( (p), 8 )
#endif

#define U16_ALIGNED( addr )         likely( PTR_IS_HW_ALIGNED( addr ))
#define U32_ALIGNED( addr )         likely( PTR_IS_FW_ALIGNED( addr ))
#define U64_ALIGNED( addr )         likely( PTR_IS_DW_ALIGNED( addr ))

///////////////////////////////////////////////////////////////////////////////
// fetch/store hw/fw/dw/noswap compatibility macros for utility

#if defined( NOT_HERC )             // (building tool utility not Hercules?)

  #define FETCH_XX_NOSWAP( UXX, XW, xw, n )                                 \
                                                                            \
    static INLINE UXX fetch_ ## xw ## _noswap( void* ptr )                  \
    {                                                                       \
        UXX value;                                                          \
        memcpy( &value, (BYTE*)ptr, n );                                    \
        return value;                                                       \
    }

  #define STORE_XX_NOSWAP( UXX, XW, xw, n )                                 \
                                                                            \
    static INLINE void store_ ## xw ## _noswap( void* ptr, UXX value )      \
    {                                                                       \
        memcpy( (BYTE*)ptr, (BYTE*)&value, n );                             \
    }

  //---------------------------------------------------------------------------

  FETCH_XX_NOSWAP( U16, HW, hw, 2 )
  STORE_XX_NOSWAP( U16, HW, hw, 2 )

  FETCH_XX_NOSWAP( U32, FW, fw, 4 )
  STORE_XX_NOSWAP( U32, FW, fw, 4 )

  FETCH_XX_NOSWAP( U64, DW, dw, 8 )
  STORE_XX_NOSWAP( U64, DW, dw, 8 )

  // --------------------------------------------------------------------------

  #define  fetch_hw( p )      CSWAP16(fetch_hw_noswap(p))
  #define  store_hw( p, v )   store_hw_noswap((p),CSWAP16(v))

  #define  fetch_fw( p )      CSWAP32(fetch_fw_noswap(p))
  #define  store_fw( p, v )   store_fw_noswap((p),CSWAP32(v))

  #define  fetch_dw( p )      CSWAP64(fetch_dw_noswap(p))
  #define  store_dw( p, v )   store_dw_noswap((p),CSWAP64(v))

#endif // defined( NOT_HERC )

///////////////////////////////////////////////////////////////////////////////
#endif // _CMPSCMEM_H_    // Place all 'ARCH_DEP' code after this statement

#undef  NOCROSSPAGE
#undef    CROSSPAGE
#define NOCROSSPAGE(a,n)      likely(((int)((a) & PAGEFRAME_BYTEMASK)) <= (PAGEFRAME_BYTEMASK-(n)))
#define   CROSSPAGE(a,n)    unlikely(((int)((a) & PAGEFRAME_BYTEMASK)) >  (PAGEFRAME_BYTEMASK-(n)))
#undef  LASTBYTEOFPAGE
#define LASTBYTEOFPAGE(a)   unlikely(((a) & PAGEFRAME_BYTEMASK) == PAGEFRAME_BYTEMASK)

///////////////////////////////////////////////////////////////////////////////
// MEMBLK helper macros

#undef  MEMBLK_FIRSTPAGE        // (is address in first page?)
#define MEMBLK_FIRSTPAGE( pMEMBLK, pOp )                            \
                                                                    \
    likely((pOp) < ((pMEMBLK)->vpagebeg + PAGEFRAME_PAGESIZE))

#undef  MEMBLK_BUMP             // (bump to next page if needed)
#define MEMBLK_BUMP( pMEMBLK, pOp )                                 \
                                                                    \
    do if (!MEMBLK_FIRSTPAGE((pMEMBLK),(pOp)))                      \
    {                                                               \
        (pMEMBLK)->vpagebeg += PAGEFRAME_PAGESIZE;                  \
        (pMEMBLK)->maddr[0] = (pMEMBLK)->maddr[1];                  \
        (pMEMBLK)->maddr[1] = 0;                                    \
    }                                                               \
    while (0)

///////////////////////////////////////////////////////////////////////////////
// fetch/store hw/fw/dw/chars compatibility macros for utility

#if defined( NOT_HERC )             // (building utility and not Hercules?)

#undef  vfetchb
#undef  vstoreb
#undef  vfetch2
#undef  vstore2
#undef  vfetch4
#undef  vstore4
#undef  vfetch8
#undef  vstore8
#undef  vfetchc
#undef  vstorec

#define vfetchb(           addr, arn, regs )   (*(U8*)(uintptr_t)(addr))
#define vstoreb( byt,      addr, arn, regs )   (*(U8*)(uintptr_t)(addr)) = ((U8)byt)
#define vfetch2(           addr, arn, regs )   fetch_hw((U16*)(addr))
#define vstore2( val,      addr, arn, regs )   store_hw((U16*)(addr),(val))
#define vfetch4(           addr, arn, regs )   fetch_fw((U32*)(addr))
#define vstore4( val,      addr, arn, regs )   store_fw((U32*)(addr),(val))
#define vfetch8(           addr, arn, regs )   fetch_dw((U64*)(addr))
#define vstore8( val,      addr, arn, regs )   store_dw((U64*)(addr),(val))
#define vfetchc( dst, len, addr, arn, regs )   memcpy( (U8*)(uintptr_t)(dst),  (U8*)(uintptr_t)(addr), (len)+1 )
#define vstorec( src, len, addr, arn, regs )   memcpy( (U8*)(uintptr_t)(addr), (U8*)(uintptr_t)(src),  (len)+1 )

#undef  wfetchb
#undef  wfetch2
#undef  wfetch4
#undef  wfetch8
#undef  wfetchc
#undef  wstoreb
#undef  wstore2
#undef  wstore4
#undef  wstore8
#undef  wstorec

#define wfetchb(           addr, arn, regs )   vfetchb(               (addr), (arn), (regs) )
#define wfetch2(           addr, arn, regs )   vfetch2(               (addr), (arn), (regs) )
#define wfetch4(           addr, arn, regs )   vfetch4(               (addr), (arn), (regs) )
#define wfetch8(           addr, arn, regs )   vfetch8(               (addr), (arn), (regs) )
#define wfetchc( dst, len, addr, arn, regs )   vfetchc( (dst), (len), (addr), (arn), (regs) )
#define wstoreb( byt,      addr, arn, regs )   vstoreb( (byt),        (addr), (arn), (regs) )
#define wstore2( val,      addr, arn, regs )   vstore2( (val),        (addr), (arn), (regs) )
#define wstore4( val,      addr, arn, regs )   vstore4( (val),        (addr), (arn), (regs) )
#define wstore8( val,      addr, arn, regs )   vstore8( (val),        (addr), (arn), (regs) )
#define wstorec( src, len, addr, arn, regs )   vstorec( (src), (len), (addr), (arn), (regs) )

#endif // defined( NOT_HERC )

///////////////////////////////////////////////////////////////////////////////
// Operand fetch/store functions

extern U8   (CMPSC_FASTCALL ARCH_DEP( cmpsc_vfetchb ))(                   VADR addr, MEMBLK* pMEMBLK );
extern U16  (CMPSC_FASTCALL ARCH_DEP( cmpsc_vfetch2 ))(                   VADR addr, MEMBLK* pMEMBLK );
extern U32  (CMPSC_FASTCALL ARCH_DEP( cmpsc_vfetch4 ))(                   VADR addr, MEMBLK* pMEMBLK );
extern U64  (CMPSC_FASTCALL ARCH_DEP( cmpsc_vfetch8 ))(                   VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vfetchc ))( U8* dst, U16 len, VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vstoreb ))( U8  byt,          VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vstore2 ))( U16 val,          VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vstore4 ))( U32 val,          VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vstore8 ))( U64 val,          VADR addr, MEMBLK* pMEMBLK );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_vstorec ))( U8* src, U16 len, VADR addr, MEMBLK* pMEMBLK );

///////////////////////////////////////////////////////////////////////////////
// Operand fetch/store macros to call above operand fetch/store functions

#undef  fetch_op_b
#undef  fetch_op_hw
#undef  fetch_op_fw
#undef  fetch_op_dw
#undef  fetch_op_str

#define fetch_op_b(             p, pMEMBLK )    ARCH_DEP( cmpsc_vfetchb )(            (VADR)(p),(pMEMBLK))
#define fetch_op_hw(            p, pMEMBLK )    ARCH_DEP( cmpsc_vfetch2 )(            (VADR)(p),(pMEMBLK))
#define fetch_op_fw(            p, pMEMBLK )    ARCH_DEP( cmpsc_vfetch4 )(            (VADR)(p),(pMEMBLK))
#define fetch_op_dw(            p, pMEMBLK )    ARCH_DEP( cmpsc_vfetch8 )(            (VADR)(p),(pMEMBLK))
#define fetch_op_str( dst, len, p, pMEMBLK )    ARCH_DEP( cmpsc_vfetchc )((dst),(len),(VADR)(p),(pMEMBLK))

#undef  store_op_b
#undef  store_op_hw
#undef  store_op_fw
#undef  store_op_dw
#undef  store_op_str

#define store_op_b(   byt,      p, pMEMBLK )    ARCH_DEP( cmpsc_vstoreb )((byt),      (VADR)(p),(pMEMBLK))
#define store_op_hw(  val,      p, pMEMBLK )    ARCH_DEP( cmpsc_vstore2 )((val),      (VADR)(p),(pMEMBLK))
#define store_op_fw(  val,      p, pMEMBLK )    ARCH_DEP( cmpsc_vstore4 )((val),      (VADR)(p),(pMEMBLK))
#define store_op_dw(  val,      p, pMEMBLK )    ARCH_DEP( cmpsc_vstore8 )((val),      (VADR)(p),(pMEMBLK))
#define store_op_str( src, len, p, pMEMBLK )    ARCH_DEP( cmpsc_vstorec )((src),(len),(VADR)(p),(pMEMBLK))

#undef  fetch_dct_hw
#define fetch_dct_hw( p, pCMPSCBLK )            ARCH_DEP( wfetch2 )((VADR)(p), (pCMPSCBLK)->r2, (pCMPSCBLK)->regs)

///////////////////////////////////////////////////////////////////////////////
// Helper functions to build pCMPSCBLK from REGS or vice-versa

extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_SetREGS  ))( CMPSCBLK* pCMPSCBLK, REGS* regs, int r1, int r2 );
extern void (CMPSC_FASTCALL ARCH_DEP( cmpsc_SetCMPSC ))( CMPSCBLK* pCMPSCBLK, REGS* regs, int r1, int r2 );

#if defined( NOT_HERC ) // (called by the testing tool utility)
extern void (CMPSC_FASTCALL ARCH_DEP( util_cmpsc_SetREGS ))( CMPSCBLK* pCMPSCBLK, REGS* regs, int r1, int r2, U8 expand, U8 zeropad );
#endif

///////////////////////////////////////////////////////////////////////////////
