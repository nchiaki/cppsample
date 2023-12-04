#ifndef _simddef_
#define _simddef_

#include <stddef.h>
#include <stdint.h>

#define USE_SIMD 1  // SIMD機能を利用するかどうか
                    // SIMD機能は更にコンパイルフラグにより、有効にするSIMD命令を選択する
#define CHK_SIMDBLK 0       // USE_SIMD有効時に、SIMDブロックのチェック（SIMD機能を利用しない時の結果との照会）を行うかどうか
                            // 機能評価時以外では、0にすること
#define USE_SIMD_STRING 1   // USE_SIMD有効時に、string.h 関係のライブラリ（memset, memcpy, etc）を使用する
                            // 機能評価時以外では 1 が望ましい
#define	USE_SIMD_ROUND	0   // ume_quant.c:UME_quantIntraBlock() で、SIMD機能を利用した丸め処理(_mm_round_pd() SSE4.1)を行うかどうか
                            // 通常運用時は 0 が望ましい

#if USE_SIMD_ROUND
/** ume_quant.c:UME_quantIntraBlock() で、SIMD機能を利用した丸め処理(_mm_round_pd() SSE4.1)に使用するモード定義
 ** 23/11/08 時点では、いずれのモードを指定しても round() と同じ結果を得られない場合がある
***		(_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC) // round to nearest, and suppress exceptions
***		(_MM_FROUND_TO_NEG_INF |_MM_FROUND_NO_EXC)     // round down, and suppress exceptions
***		(_MM_FROUND_TO_POS_INF |_MM_FROUND_NO_EXC)     // round up, and suppress exceptions
***		(_MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC)        // truncate, and suppress exceptions
**/
#define MMROUNDMODE	(_MM_FROUND_TO_POS_INF |_MM_FROUND_NO_EXC)
#endif

#if USE_SIMD
/* コンパイルフラグに対応していないSIMD命令をスタブで置き換えるかどうか
** 注意：コンパイルフラグが有効なSIMD命令を選択している場合、スタブは使用してはいけない
** 通常運用時は 0 にすること
*/
#if !(__AVX__)
#define SIMD_STUB_AVX    0
#endif
#if !(__AVX2__)
#define SIMD_STUB_AVX2   0
#endif

#if 0
#if !(__AVX512F__)
#define SIMD_STUB_AVX512F   0 // Fixed
#endif
#if !(__AVX512BW__)
#define SIMD_STUB_AVX512BW  0 // Fixed
#endif
#else
/* AVX512F, AVX512BWの機能確認を行う場合は、以下のURLから入手できるエミュレータを使用する
**　https://software.intel.com/en-us/articles/intel-software-development-emulator
*/
#endif

#if SIMD_STUB_AVX
#define __AVX__ 1   // Untouched
#endif  
#if SIMD_STUB_AVX2
#define __AVX2__ 1  // Untouched
#endif
#if SIMD_STUB_AVX512F
#define __AVX512F__ 1   // Untouched
#endif
#if SIMD_STUB_AVX512BW
#define __AVX512BW__ 1  // Untouched
#endif

#define SIMD_STUB_NORTN 0   // 1: スタブの作りを本来、戻り値として返すべきベクトルを、引数で渡すようにする
                            // 現状では1にする事はない
#endif

#define PROCTIMEMEASURE 1

#if PROCTIMEMEASURE
#include <sys/time.h>
#endif

#define SIMD_NEON (1<<0)
#if USE_SIMD && __ARM_NEON
#include <arm_neon.h>
#define SIMD_NEON_BIT SIMD_NEON
#else
#define SIMD_NEON_BIT 0
#endif

#define SIMD_HELIUM (1<<1)
#if USE_SIMD &&  __ARM_HELIUM
#include <arm_helium.h>
#define SIMD_HELIUM_BIT SIMD_HELIUM
#else
#define SIMD_HELIUM_BIT 0
#endif


#define SIMD_MMX (1<<2)
#if USE_SIMD && __MMX__
#include <mmintrin.h>
#define SIMD_MMX_BIT SIMD_MMX
#else
#define SIMD_MMX_BIT 0
#endif

#define SIMD_SSE (1<<3)
#if USE_SIMD && __SSE__
#include <xmmintrin.h>
#define SIMD_SSE_BIT SIMD_SSE
#else
#define SIMD_SSE_BIT 0
#endif

#define SIMD_SSE2 (1<<4)
#if USE_SIMD && __SSE2__
#include <emmintrin.h>
#define SIMD_SSE2_BIT SIMD_SSE2
#else
#define SIMD_SSE2_BIT 0
#endif

#define SIMD_SSE3   (1<<5)
#if USE_SIMD && __SSE3__
#include <pmmintrin.h>
#define SIMD_SSE3_BIT SIMD_SSE3
#else
#define SIMD_SSE3_BIT 0
#endif

#define SIMD_SSSE3 (1<<6)
#if USE_SIMD && __SSSE3__
#include <tmmintrin.h>
#define SIMD_SSSE3_BIT SIMD_SSSE3
#else
#define SIMD_SSSE3_BIT 0
#endif

#define SIMD_SSE4_1 (1<<7)
#if USE_SIMD && __SSE4_1__
#include <smmintrin.h>
#define SIMD_SSE4_1_BIT SIMD_SSE4_1
#else
#define SIMD_SSE4_1_BIT 0
#endif

#define SIMD_SSE4_2 (1<<8)
#if USE_SIMD && __SSE4_2__
#include <nmmintrin.h>
#define SIMD_SSE4_2_BIT SIMD_SSE4_2
#else
#define SIMD_SSE4_2_BIT 0
#endif

#define SIMD_AVX (1<<9)
#if USE_SIMD && __AVX__
#if !SIMD_STUB_AVX
#include <immintrin.h>
#endif
#define SIMD_AVX_BIT SIMD_AVX
#else
#define SIMD_AVX_BIT 0
#endif

#define SIMD_AVX2 (1<<10)
#if USE_SIMD && __AVX2__
#if !SIMD_STUB_AVX2
#include <immintrin.h>
#endif
#define SIMD_AVX2_BIT SIMD_AVX2
#else
#define SIMD_AVX2_BIT 0
#endif

#define SIMD_AVX512F (1<<11)
#if USE_SIMD && __AVX512F__
#include <immintrin.h>
#define SIMD_AVX512F_BIT SIMD_AVX512F
#else
#define SIMD_AVX512F_BIT 0
#endif

#define SIMD_AVX512BW (1<<12)
#if USE_SIMD && __AVX512BW__
#include <immintrin.h>
#define SIMD_AVX512BW_BIT SIMD_AVX512BW
#else
#define SIMD_AVX512BW_BIT 0
#endif

#if USE_SIMD
#define SIMD_SSEFAMILY (SIMD_SSE_BIT|SIMD_SSE2_BIT|SIMD_SSE3_BIT|SIMD_SSSE3_BIT|SIMD_SSE4_1_BIT|SIMD_SSE4_2_BIT)
#define SIMD_AVXFAMILY (SIMD_AVX_BIT|SIMD_AVX2_BIT)
#define SIMD_AVX512FAMILY (SIMD_AVX512F_BIT|SIMD_AVX512BW_BIT)
#define SIMD_INTEL (SIMD_MMX_BIT|SIMD_SSEFAMILY|SIMD_AVXFAMILY|SIMD_AVX512FAMILY)
#define SIMD_ARM (SIMD_NEON_BIT|SIMD_HELIUM_BIT)
#else
#undef  CHK_SIMDBLK
#define CHK_SIMDBLK 0

#define SIMD_INTEL 0
#define SIMD_ARM 0
#endif
#define SIMD_ALL    (SIMD_INTEL|SIMD_ARM)

#define isSIMD(x) (SIMD_ALL & (x))

#if isSIMD(SIMD_SSE2_BIT)
#include <emmintrin.h>
#endif
#if isSIMD(SIMD_SSSE3_BIT)
#include <tmmintrin.h> 
#endif

#if isSIMD(SIMD_NEON_BIT)
#include <arm_neon.h>
#endif
#if isSIMD(SIMD_HELIUM_BIT)
#include <arm_helium.h>
#endif

#if (SIMD_STUB_AVX | SIMD_STUB_AVX2)
#include "simdstubdef.h"
#endif

#if isSIMD(SIMD_SSEFAMILY)
typedef union vector_m64 {
    __m64  vctr;
    uint8_t u8[8];
    int8_t  i8[8];
    uint16_t u16[4];
    int16_t i16[4];
    uint32_t u32[2];
    int32_t i32[2];
    uint64_t u64[1];
    int64_t  i64[1];
} VCTR64i;

typedef union vector_m128i {
    __m128i vctr;
    uint8_t u8[16];
    int8_t  i8[16];
    uint16_t u16[8];
    int16_t i16[8];
    uint32_t u32[4];
    int32_t i32[4];
    uint64_t u64[2];
    int64_t  i64[2];
} VCTR128i;

typedef union vector_m128d {
    __m128d vctr;
    double d64[2];
} VCTR128d;

typedef union vector_m128 {
    __m128 vctr;
    float f32[4];
} VCTR128;

#endif

#if isSIMD(SIMD_AVXFAMILY)
typedef union vector_m256i {
    __m256i vctr;
    uint8_t u8[32];
    int8_t  i8[32];
    uint16_t u16[16];
    int16_t i16[16];
    uint32_t u32[8];
    int32_t i32[8];
    uint64_t u64[4];
    int64_t  i64[4];
} VCTR256i;

typedef union vector_m256d {
    __m256d vctr;
    double d64[4];
} VCTR256d;

typedef union vector_m256 {
    __m256 vctr;
    float f32[8];
} VCTR256;
#endif

#if isSIMD(SIMD_AVX512FAMILY)
typedef union vector_m512i {
    __m512i vctr;
    uint8_t u8[64];
    int8_t  i8[64];
    uint16_t u16[32];
    int16_t i16[32];
    uint32_t u32[16];
    int32_t i32[16];
    uint64_t u64[8];
    int64_t  i64[8];
} VCTR512i;

typedef union vector_m512d {
    __m512d vctr;
    double d64[8];
} VCTR512d;

typedef union vector_m512 {
    __m512 vctr;
    float f32[16];
} VCTR512;

#endif

// SIMDのマクロ
#if isSIMD(SIMD_ALL)
#if USE_SIMD_STRING
#include <string.h>
#define SIMD_u8_copy(p_frm_pix, p_src_pix, hsv_y) {\
    memcpy(p_frm_pix, p_src_pix, hsv_y);\
    p_frm_pix += hsv_y;\
    p_src_pix += hsv_y;\
}
#define SIMD_u8_copy2p(p_frm_pix, p_fld_pix, p_src_pix, hsv_y) {\
    memcpy(p_frm_pix, p_src_pix, hsv_y);\
    memcpy(p_fld_pix, p_src_pix, hsv_y);\
    p_frm_pix += hsv_y;\
    p_fld_pix += hsv_y;\
    p_src_pix += hsv_y;\
}
#define SIMD_u8_set(dstp, val, setz) {\
    memset(dstp, val, setz);\
    dstp += setz;\
}
#define SIMD_u8_set2p(dst2p, dstp, val, setz) {\
    memset(dst2p, val, setz);\
    memset(dstp, val, setz);\
    dst2p += setz;\
    dstp += setz;\
}

#elif isSIMD(SIMD_INTEL)

#define SIMD_u8_copy(p_frm_pix, p_src_pix, hsv_y) \
while (1) {\
	int x;\
	uint16_t loops = hsv_y >> 4;	/* / 16*/\
	uint16_t remain = hsv_y & 0xf;	/* % 16*/\
	if (loops) {\
        for (x=0; x<loops; ++x){\
            _mm_storeu_si128((__m128i*)p_frm_pix, _mm_loadu_si128((__m128i*)p_src_pix));\
			p_src_pix += 16;p_frm_pix += 16;\
		} \
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                    *p_frm_pix = *p_src_pix;\
                    ++p_src_pix;++p_frm_pix;\
            }\
            break;\
        }\
	}\
    if (!remain) break;\
	loops = remain >> 3;	/* / 8*/\
	remain = remain & 0x7;	/* % 8*/\
	if (loops) {for (x=0; x<loops; ++x){\
            _mm_storeu_si64(p_frm_pix, _mm_loadu_si128( (__m128i*)p_src_pix ));\
			p_src_pix += 8;p_frm_pix += 8;\
		} \
	}\
	if (remain) {for (x=0; x<remain; ++x) {\
        *p_frm_pix = *p_src_pix;\
		++p_src_pix;++p_frm_pix;\
	}}\
    break;\
}

#define SIMD_u8_copy2p(p_frm_pix, p_fld_pix, p_src_pix, hsv_y) \
while (1) {\
	int x;\
	uint16_t loops = hsv_y >> 4;	/* / 16*/\
	uint16_t remain = hsv_y & 0xf;	/* % 16*/\
	if (loops) {__m128i m_src_pix;\
        for (x=0; x<loops; ++x){\
            m_src_pix = _mm_loadu_si128((__m128i*)p_src_pix);\
            _mm_storeu_si128((__m128i*)p_fld_pix, m_src_pix);\
            _mm_storeu_si128((__m128i*)p_frm_pix, m_src_pix);\
			p_src_pix += 16;p_fld_pix += 16;p_frm_pix += 16;\
		} \
	}\
    if (!remain) break;\
	loops = remain >> 3;	/* / 8*/\
	remain = remain & 0x7;	/* % 8*/\
	if (loops) {__m128i m_src_pix;\
        for (x=0; x<loops; ++x){\
            m_src_pix = _mm_loadu_si128((__m128i*)p_src_pix);\
            _mm_storeu_si64(p_fld_pix, m_src_pix);\
            _mm_storeu_si64(p_frm_pix, m_src_pix);\
			p_src_pix += 8;p_fld_pix += 8;p_frm_pix += 8;\
		} \
	}\
	if (remain) {\
        for (x=0; x<remain; ++x) {\
            *p_fld_pix = *p_frm_pix = *p_src_pix;\
            ++p_src_pix;++p_fld_pix;++p_frm_pix;\
        }\
    }\
    break;\
}

#elif isSIMD(SIMD_NEON)

#define SIMD_u8_copy(p_frm_pix, p_src_pix, hsv_y) \
while (1) {\
	int x;\
	uint16_t loops = hsv_y >> 6; /* / 64*/\
	uint16_t remain = hsv_y & 0x3f;	/*	% 64*/\
    if (loops) {\
        for (x=0; x<loops; ++x){\
			vst4q_u8(p_frm_pix, vld4q_u8(p_src_pix));\
			p_src_pix += 64;p_frm_pix += 64;\
		}\
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                    *p_frm_pix = *p_src_pix;\
                    ++p_src_pix;++p_frm_pix;\
            }\
            break;\
        }\
	}\
    if (!remain) break;\
	loops = remain >> 5;	/* / 32*/\
	remain = remain & 0x1f;	/* % 32*/\
	if (loops) {\
        for (x=0; x<loops; ++x){\
			vst2q_u8(p_frm_pix, vld2q_u8(p_src_pix));\
			p_src_pix += 32;p_frm_pix += 32;\
		}\
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                    *p_frm_pix = *p_src_pix;\
                    ++p_src_pix;++p_frm_pix;\
            }\
            break;\
        }\
	}\
    if (!remain) break;\
	loops = remain >> 4;	/* / 16*/\
	remain = remain & 0xf;	/* % 16*/\
	if (loops) {\
        for (x=0; x<loops; ++x){\
			vst1q_u8(p_frm_pix, vld1q_u8(p_src_pix));\
			p_src_pix += 16;p_frm_pix += 16;\
		} \
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                    *p_frm_pix = *p_src_pix;\
                    ++p_src_pix;++p_frm_pix;\
            }\
            break;\
        }\
	}\
    if (!remain) break;\
	loops = remain >> 3;	/* / 8*/\
	remain = remain & 0x7;	/* % 8*/\
	if (loops) {for (x=0; x<loops; ++x){\
			vst1_u8(p_frm_pix, vld1_u8(p_src_pix));\
			p_src_pix += 8;p_frm_pix += 8;\
		} \
	}\
	if (remain) {for (x=0; x<remain; ++x) {\
        *p_frm_pix = *p_src_pix;\
		++p_src_pix;++p_frm_pix;\
	}}\
    break;\
}

#define SIMD_u8_copy2p(p_frm_pix, p_fld_pix, p_src_pix, hsv_y) \
while (1) {\
	int x;\
	uint16_t loops = hsv_y >> 6; /* / 64*/\
	uint16_t remain = hsv_y & 0x3f;	/*	% 64*/\
	if (loops) {uint8x16x4_t src_data;\
        for (x=0; x<loops; ++x){\
			src_data = vld4q_u8(p_src_pix);\
			vst4q_u8(p_fld_pix, src_data);vst4q_u8(p_frm_pix, src_data);\
			p_src_pix += 64;p_fld_pix += 64;p_frm_pix += 64;\
		} \
        /***\
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                *p_fld_pix = *p_frm_pix = *p_src_pix;\
                ++p_src_pix;++p_fld_pix;++p_frm_pix;\
            }\
            break;\
        }\
        ***/\
	}\
    if (!remain) break;\
	loops = remain >> 5;	/* / 32*/\
	remain = remain & 0x1f;	/* % 32*/\
	if (loops) {uint8x16x2_t src_data;\
        for (x=0; x<loops; ++x){\
			src_data = vld2q_u8(p_src_pix);\
			vst2q_u8(p_fld_pix, src_data);vst2q_u8(p_frm_pix, src_data);\
			p_src_pix += 32;p_fld_pix += 32;p_frm_pix += 32;\
		} \
        /***\
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                *p_fld_pix = *p_frm_pix = *p_src_pix;\
                ++p_src_pix;++p_fld_pix;++p_frm_pix;\
            }\
            break;\
        }\
        ***/\
	}\
    if (!remain) break;\
	loops = remain >> 4;	/* / 16*/\
	remain = remain & 0xf;	/* % 16*/\
	if (loops) {uint8x16_t src_data;\
        for (x=0; x<loops; ++x){\
			src_data = vld1q_u8(p_src_pix);\
			vst1q_u8(p_fld_pix, src_data);vst1q_u8(p_frm_pix, src_data);\
			p_src_pix += 16;p_fld_pix += 16;p_frm_pix += 16;\
		} \
        /***\
        if (remain) {\
            for (x=0; x<remain; ++x) {\
                *p_fld_pix = *p_frm_pix = *p_src_pix;\
                ++p_src_pix;++p_fld_pix;++p_frm_pix;\
            }\
            break;\
        }\
        ***/\
	}\
    if (!remain) break;\
	loops = remain >> 3;	/* / 8*/\
	remain = remain & 0x7;	/* % 8*/\
	if (loops) {uint8x8_t src_data;\
        for (x=0; x<loops; ++x){\
			src_data = vld1_u8(p_src_pix);\
			vst1_u8(p_fld_pix, src_data);vst1_u8(p_frm_pix, src_data);\
			p_src_pix += 8;p_fld_pix += 8;p_frm_pix += 8;\
		} \
	}\
	if (remain) {\
        for (x=0; x<remain; ++x) {\
            *p_fld_pix = *p_frm_pix = *p_src_pix;\
            ++p_src_pix;++p_fld_pix;++p_frm_pix;\
        }\
    }\
    break;\
}

#define SIMD_u8_set(dstp, val, setz) \
while (1) {\
    int x;\
    uint16_t loops = setz >> 6; /* / 64*/\
    uint16_t remain = setz & 0x3f;	/*	% 64*/\
    if (loops) {\
        uint8x16x4_t v_x10	= vld4q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst4q_u8(dstp, v_x10);\
            dstp += 64;\
        }\
        /***\
        if (remain) {for (x=0; x<remain; ++x) {\
            *dstp = *val;\
            ++dstp;\
        }break;}\
        ***/\
    }\
    if (!remain) break;\
    loops = remain >> 5;	/* / 32*/\
    remain = remain & 0x1f;	/* % 32*/\
    if (loops) {\
        uint8x16x2_t v_x10 = vld2q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst2q_u8(dstp, v_x10);\
            dstp += 32;\
        } \
        /***\
        if (remain) {for (x=0; x<remain; ++x) {\
            *dstp = *val;\
            ++dstp;\
        }break;}\
        ***/\
    }\
    if (!remain) break;\
    loops = remain >> 4;	/* / 16*/\
    remain = remain & 0xf;	/* % 16*/\
    if (loops) {\
        uint8x16_t v_x10 = vld1q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst1q_u8(dstp, v_x10);\
            dstp += 16;\
        } \
        /***\
        if (remain) {for (x=0; x<remain; ++x) {\
            *dstp = *val;\
            ++dstp;\
        }break;}\
        ***/\
    }\
    if (!remain) break;\
    loops = remain >> 3;	/* / 8*/\
    remain = remain & 0x7;	/* % 8*/\
    if (loops) {\
        uint8x8_t v_x10	= vld1_u8( val );\
        for (x=0; x<loops; ++x){\
            vst1_u8(dstp, v_x10);\
            dstp += 8;\
        } \
    }\
    if (remain) {for (x=0; x<remain; ++x) {\
        *dstp = *val;\
        ++dstp;\
    }}\
    break;\
}

#define SIMD_u8_set2p(dst2p, dstp, val, setz) \
while (1) {\
    int x;\
    uint16_t loops = setz >> 6; /* / 64*/\
    uint16_t remain = setz & 0x3f;	/*	% 64*/\
    if (loops) {\
        uint8x16x4_t v_x10	= vld4q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst4q_u8(dstp, v_x10);vst4q_u8(dst2p, v_x10);\
            dstp += 64;\
            dst2p += 64;\
        }\
        if (remain) {for (x=0; x<remain; ++x) {\
            *dst2p = *dstp = *val;\
            ++dstp;\
            ++dst2p;\
        }break;}\
    }\
    if (!remain) break;\
    loops = remain >> 5;	/* / 32*/\
    remain = remain & 0x1f;	/* % 32*/\
    if (loops) {\
        uint8x16x2_t v_x10 = vld2q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst2q_u8(dstp, v_x10);vst2q_u8(dst2p, v_x10);\
            dstp += 32;\
            dst2p += 32;\
        } \
        if (remain) {for (x=0; x<remain; ++x) {\
            *dst2p = *dstp = *val;\
            ++dstp;\
            ++dst2p;\
        }break;}\
    }\
    if (!remain) break;\
    loops = remain >> 4;	/* / 16*/\
    remain = remain & 0xf;	/* % 16*/\
    if (loops) {\
        uint8x16_t v_x10 = vld1q_u8( val );\
        for (x=0; x<loops; ++x){\
            vst1q_u8(dstp, v_x10);vst1q_u8(dst2p, v_x10);\
            dstp += 16;\
            dst2p += 16;\
        } \
        if (remain) {for (x=0; x<remain; ++x) {\
            *dst2p = *dstp = *val;\
            ++dstp;\
            ++dst2p;\
        }break;}\
    }\
    if (!remain) break;\
    loops = remain >> 3;	/* / 8*/\
    remain = remain & 0x7;	/* % 8*/\
    if (loops) {\
        uint8x8_t v_x10	= vld1_u8( val );\
        for (x=0; x<loops; ++x){\
            vst1_u8(dstp, v_x10);vst1_u8(dst2p, v_x10);\
            dstp += 8;\
            dst2p += 8;\
        } \
    }\
    if (remain) {for (x=0; x<remain; ++x) {\
        *dst2p = *dstp = *val;\
        ++dstp;\
        ++dst2p;\
    }}\
    break;\
}

#endif
#endif

#endif
