/** ============================================================================
//
// = LIBRARY
//    ULib - c library
//
// = FILENAME
//    macro.h
//
// = AUTHOR
//    Stefano Casazza
//
// ============================================================================ */

#ifndef ULIB_BASE_MACRO_H
#define ULIB_BASE_MACRO_H 1

/* Manage location info */

#define U_SET_LOCATION_INFO (u_num_line      = __LINE__, \
                             u_name_file     = __FILE__, \
                             u_name_function = __PRETTY_FUNCTION__)

/**
 * Manage debug for C library
 *
 * the token preceding the special `##' must be a comma, and there must be white space between that comma and whatever comes immediately before it
 */

#ifdef DEBUG_DEBUG
#  define U_INTERNAL_TRACE(format,args...) u_internal_print(false, format"\n" , ##args);
#  define U_INTERNAL_PRINT(format,args...) U_INTERNAL_TRACE(format,args)
#else
#  define U_INTERNAL_TRACE(format,args...)
#  define U_INTERNAL_PRINT(format,args...)
#endif

/* Design by contract - if (assertion == false) then stop */

#ifdef DEBUG
#  define U_ASSERT_MACRO(assertion,msg,info) \
      if ((bool)(assertion) == false) { \
         u__printf(STDERR_FILENO, "%W%N%W: %Q%W%s%W\n" \
         "-------------------------------------\n" \
         " pid: %W%P%W\n" \
         " file: %W%s%W\n" \
         " line: %W%d%W\n" \
         " function: %W%s%W\n" \
         " assertion: \"(%W%s%W)\" %W%s%W\n" \
         "-------------------------------------", \
         GREEN, YELLOW, -1, CYAN, msg, YELLOW, \
         CYAN, YELLOW, \
         CYAN, __FILE__, YELLOW, \
         CYAN, __LINE__, YELLOW, \
         CYAN, __PRETTY_FUNCTION__, YELLOW, \
         CYAN, #assertion, YELLOW, MAGENTA, info, YELLOW); }
#elif defined(U_TEST)
#  ifdef HAVE_ASSERT_H
#     include <assert.h>
#     define U_ASSERT_MACRO(assertion,msg,info) assert(assertion);
#  else
#     ifdef __cplusplus
      extern "C" {
#     endif
      void __assert(const char* __assertion, const char* __file, int __line, const char* __function);
#     ifdef __cplusplus
      }
#     endif
#     define U_ASSERT_MACRO(assertion,msg,info) { if ((int)(assertion) == 0) { __assert(#assertion, __FILE__, __LINE__,__PRETTY_FUNCTION__);  } }
#  endif
#endif

#if defined(DEBUG) || defined(U_TEST)
#  define U_INTERNAL_ASSERT(expr)        { U_ASSERT_MACRO(expr,"ASSERTION FALSE","") }
#  define U_INTERNAL_ASSERT_MINOR(a,b)   { U_ASSERT_MACRO((a)<(b),"NOT LESS","") }
#  define U_INTERNAL_ASSERT_MAJOR(a,b)   { U_ASSERT_MACRO((a)>(b),"NOT GREATER","") }
#  define U_INTERNAL_ASSERT_EQUALS(a,b)  { U_ASSERT_MACRO((a)==(b),"NOT EQUALS","") }
#  define U_INTERNAL_ASSERT_DIFFERS(a,b) { U_ASSERT_MACRO((a)!=(b),"NOT DIFFERENT","") }
#  define U_INTERNAL_ASSERT_POINTER(ptr) { U_ASSERT_MACRO((const void*)ptr>(const void*)0x0000ffff,"~NULL POINTER","") }
#  define U_INTERNAL_ASSERT_RANGE(a,x,b) { U_ASSERT_MACRO((x)>=(a)&&(x)<=(b),"VALUE OUT OF RANGE","") }

#  define U_INTERNAL_ASSERT_MSG(expr,info) \
          { U_ASSERT_MACRO(expr,"ASSERTION FALSE",info) }
#  define U_INTERNAL_ASSERT_MINOR_MSG(a,b,info) \
          { U_ASSERT_MACRO((a)<(b),"NOT LESS",info) }
#  define U_INTERNAL_ASSERT_MAJOR_MSG(a,b,info) \
          { U_ASSERT_MACRO((a)>(b),"NOT GREATER",info) }
#  define U_INTERNAL_ASSERT_EQUALS_MSG(a,b,info) \
          { U_ASSERT_MACRO((a)==(b),"NOT EQUALS",info) }
#  define U_INTERNAL_ASSERT_DIFFERS_MSG(a,b,info) \
          { U_ASSERT_MACRO((a)!=(b),"NOT DIFFERENT",info) }
#  define U_INTERNAL_ASSERT_POINTER_MSG(ptr,info) \
          { U_ASSERT_MACRO((const void*)ptr>(const void*)0x0000ffff,"~NULL POINTER",info) }
#  define U_INTERNAL_ASSERT_RANGE_MSG(a,x,b,info) \
          { U_ASSERT_MACRO((x)>=(a)&&(x)<=(b),"VALUE OUT OF RANGE",info) }
#else
#  define U_INTERNAL_ASSERT(expr)
#  define U_INTERNAL_ASSERT_MINOR(a,b)
#  define U_INTERNAL_ASSERT_MAJOR(a,b)
#  define U_INTERNAL_ASSERT_EQUALS(a,b)
#  define U_INTERNAL_ASSERT_DIFFERS(a,b)
#  define U_INTERNAL_ASSERT_POINTER(ptr)
#  define U_INTERNAL_ASSERT_RANGE(a,x,b)

#  define U_INTERNAL_ASSERT_MSG(expr,info)
#  define U_INTERNAL_ASSERT_MINOR_MSG(a,b,info)
#  define U_INTERNAL_ASSERT_MAJOR_MSG(a,b,info)
#  define U_INTERNAL_ASSERT_EQUALS_MSG(a,b,info)
#  define U_INTERNAL_ASSERT_DIFFERS_MSG(a,b,info)
#  define U_INTERNAL_ASSERT_POINTER_MSG(ptr,info)
#  define U_INTERNAL_ASSERT_RANGE_MSG(a,x,b,info)
#endif

/* Manage message info */

# define U_ERROR(fmt,args...) \
{ u_flag_exit = -1; u__printf(STDERR_FILENO, "%W%N%W: %WERROR: %9D (pid %P) " fmt " - Exiting...%W", BRIGHTCYAN, RESET, RED, ##args, RESET); }

#define U_ABORT(fmt,args...) \
{ u_flag_exit = -2; u__printf(STDERR_FILENO, "%W%N%W: %WABORT: %9D (pid %P) " fmt "%W", BRIGHTCYAN, RESET, RED, ##args, RESET); }

#define U_WARNING(fmt,args...) \
{ u_flag_exit = 2; u__printf(STDERR_FILENO, "%W%N%W: %WWARNING: %9D (pid %P) " fmt "%W", BRIGHTCYAN, RESET, YELLOW, ##args, RESET); }

#define U_MESSAGE(fmt,args...) u__printf(STDERR_FILENO, "%W%N%W: " fmt, BRIGHTCYAN, RESET, ##args)

#define   U_ERROR_SYSCALL(msg)      U_ERROR("%R",msg)
#define   U_ABORT_SYSCALL(msg)      U_ABORT("%R",msg)
#define U_WARNING_SYSCALL(msg)    U_WARNING("%R",msg)

/* Get string costant size from compiler */

#define U_CONSTANT_SIZE(str)     (int)(sizeof(str)-1)
#define U_CONSTANT_TO_PARAM(str) str,U_CONSTANT_SIZE(str)
#define U_CONSTANT_TO_TRACE(str)     U_CONSTANT_SIZE(str),str

#define U_STREQ(a,n,b) (n == U_CONSTANT_SIZE(b) && (memcmp((const char* restrict)(a),b,U_CONSTANT_SIZE(b)) == 0))

/* Defs */

#ifndef U_min
#define U_min(x,y) ((x) <= (y) ? (x) : (y))
#endif
#ifndef U_max
#define U_max(x,y) ((x) >= (y) ? (x) : (y))
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif
#ifndef PAGESIZE
#define PAGESIZE 4096U
#endif
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif
#ifndef MAX_FILENAME_LEN
#define MAX_FILENAME_LEN 255U
#endif

#define U_PAGEMASK (PAGESIZE-1)
#define U_NOT_FOUND ((uint32_t)-1)

#define U_ONE_HOUR_IN_SECOND  (60L * 60L)
#define U_ONE_DAY_IN_SECOND   (24L * U_ONE_HOUR_IN_SECOND)
#define U_ONE_WEEK_IN_SECOND  ( 7L * U_ONE_DAY_IN_SECOND)
#define U_ONE_MONTH_IN_SECOND (31L * U_ONE_DAY_IN_SECOND)
#define U_ONE_YEAR_IN_SECOND  (12L * U_ONE_MONTH_IN_SECOND)

#define U_NUM_ELEMENTS(array) (int)(sizeof(array) / sizeof(array[0]))

enum AffermationType {
   U_MAYBE   = 0x0000,
   U_YES     = 0x0001,
   U_NOT     = 0x0002,
   U_PARTIAL = 0x0004,
   U_CLOSE   = 0x0008
};

#define GZIP_MAGIC "\037\213" /* Magic header for gzip files, 1F 8B */

/* MIME type */

#define U_unknow  -1
#define U_know    'K'

#define U_css     'c' /* text/css */
#define U_flv     'f' /* video/x-flv */
#define U_gif     'g' /* image/gif */
#define U_html    'h' /* text/html */
#define U_ico     'i' /* image/x-icon */
#define U_js      'j' /* text/javascript */
#define U_png     'p' /* image/png */
#define U_txt     't' /* text/plain */

#define U_jpg     'J' /* image/jpg */
#define U_gz      'Z' /* gzip */

/* MIME type for dynamic content */

#define U_usp    '0' /* USP (ULib Servlet Page) */
#define U_csp    '1' /* CSP (C    Servlet Page) */
#define U_cgi    '2' /* cgi-bin */
#define U_ssi    '3' /* SSI */
#define U_php    '4' /* PHP  script */
#define U_ruby   '5' /* Ruby script */
#define U_perl   '6' /* Perl script */
#define U_python '7' /* Python script */

#define U_CTYPE_HTML "text/html; charset=UTF-8"
#define U_CTYPE_TEXT "text/plain; charset=UTF-8"

/**
 * Enumeration of Hash (Digest) types
 * 
 * The hash types known to openssl
 */

typedef enum {
   U_HASH_MD2       = 0,
   U_HASH_MD5       = 1,
   U_HASH_SHA       = 2,
   U_HASH_SHA1      = 3,
   U_HASH_SHA224    = 4,
   U_HASH_SHA256    = 5,
   U_HASH_SHA384    = 6,
   U_HASH_SHA512    = 7,
   U_HASH_MDC2      = 8,
   U_HASH_RIPEMD160 = 9
} UHashType;

#define U_PTR2INT(x) ((unsigned int)(long)x)
#define U_INT2PTR(x) (       (void*)(long)x)

union uucflag {
   char c[4];
   uint16_t lo; 
   uint16_t hi; 
   uint32_t u;
};

union uucflag64 {
   char c[8];
   uint16_t lo; 
   uint16_t hi; 
   uint32_t s;
   uint64_t u;
};

/* Type of file sizes and offsets (LFS) */

#if SIZEOF_OFF_T == SIZEOF_LONG
#  define u_strtooff(nptr,endptr,base) (off_t) strtol((nptr),(char**)(endptr),(base))
#else
#  define u_strtooff(nptr,endptr,base) (off_t) strtoll((nptr),(char**)(endptr),(base))

#  if SIZEOF_OFF_T != 8
#     error ERROR: unexpected size of SIZEOF_OFF_T
#  endif
#endif

#ifdef ENABLE_LFS
#  define U_SEEK_BEGIN 0LL
#else
#  define U_SEEK_BEGIN 0L
#endif

/* Line terminator */

#define U_LF    "\n"
#define U_LF2   "\n\n"
#define U_CRLF  "\r\n"
#define U_CRLF2 "\r\n\r\n"

#define U_CONCAT2(a,b)   a##b
#define U_CONCAT3(a,b,c) a##b##c

/* These two macros makes it possible to turn the builtin line expander into a string literal */

#define U_STRINGIFY2(x) #x
#define U_STRINGIFY(x) U_STRINGIFY2(x)

/* Provide convenience macros for handling structure fields through their offsets */

#ifndef offsetof
#define offsetof(st,m) ((long)(&((st*)0)->m))
#endif

#define U_STRUCT_MEMBER_SIZE(type,member)   (sizeof(((type*)0)->member))
#define U_STRUCT_MEMBER_OFFSET(type,member)       (&((type*)0)->member)

#define U_STRUCT_IS_LAST_MEMBER(type,member)    (U_STRUCT_MEMBER_END_OFFSET(type,member) == sizeof(type))
#define U_STRUCT_MEMBER_END_OFFSET(type,member) (U_STRUCT_MEMBER_SIZE(type,member) + U_STRUCT_OFFSET(type,member))

/* Needed for unaligned memory access */

#ifdef HAVE_NO_UNALIGNED_ACCESSES
struct __una_u32 { uint32_t x __attribute__((packed)); };
#  define u_get_unalignedp(ptr)      ((uint32_t)(((const struct __una_u32*)(ptr))->x))
#  define u_put_unalignedp(val, ptr)             ((      struct __una_u32*)(ptr))->x = val
#else
/* The x86 can do unaligned accesses itself */
#  define u_get_unalignedp(ptr)      (*(uint32_t*)(ptr))
#  define u_put_unalignedp(val, ptr) (*(uint32_t*)(ptr) = (val))
#endif

/**
 * u_get_unaligned - get value from possibly mis-aligned location
 *
 * This macro should be used for accessing values larger in size than
 * single bytes at locations that are expected to be improperly aligned
 *
 * Note that unaligned accesses can be very expensive on some architectures.
 */

#define u_get_unaligned(ref) u_get_unalignedp(&(ref))

/**
 * u_put_unaligned - put value to a possibly mis-aligned location
 *
 * This macro should be used for placing values larger in size than
 * single bytes at locations that are expected to be improperly aligned
 *
 * Note that unaligned accesses can be very expensive on some architectures.
 */

#define u_put_unaligned(val, ref) u_put_unalignedp(val,&(ref))

/* Endian order (network byte order is big endian) */

#if __BYTE_ORDER == __LITTLE_ENDIAN /* the host byte order is Least Significant Byte first */
#  define u_test_bit(n,c) (((c) & (1 << n)) != 0)

#  define u_htonll(x) (((uint64_t)htonl((uint32_t)x))<<32 | htonl((uint32_t)(x>>32)))
#  define u_ntohll(x) (((uint64_t)ntohl((uint32_t)x))<<32 | ntohl((uint32_t)(x>>32)))

#  define U_NUM2STR16(ptr,val1)             (((union uucflag*)(ptr))->lo = \
                                             ((union uucflag*)(u_ctn2s+((val1)*2)))->lo)

#  define U_NUM2STR32(ptr,val1,val2)        (((union uucflag*)(ptr))->u = \
                                            (((union uucflag*)(u_ctn2s+((val1)*2)))->lo)|\
                                            (((union uucflag*)(u_ctn2s+((val2)*2)))->lo)<<16)


#  define U_NUM2STR64(ptr,c,val1,val2,val3) (((union uucflag64*)(ptr))->u = \
                                            (((union uucflag*)(u_ctn2s+((val1)*2)))->lo)|\
                                              (int64_t)(c)<<16|\
                                  ((int64_t)(((union uucflag*)(u_ctn2s+((val2)*2)))->lo)<<24)|\
                                              (int64_t)(c)<<40|\
                                  ((int64_t)(((union uucflag*)(u_ctn2s+((val3)*2)))->lo)<<48))

#  define U_MULTICHAR_CONSTANT16(a,b)              ((int16_t)((uint8_t)(a)|\
                                                              (uint8_t)(b)<<8))

#  define U_MULTICHAR_CONSTANT32(a,b,c,d)          ((int32_t)((uint8_t)(a)|\
                                                              (uint8_t)(b)<<8|\
                                                              (uint8_t)(c)<<16|\
                                                              (uint8_t)(d)<<24))

#  define U_MULTICHAR_CONSTANT64(a,b,c,d,e,f,g,h)  ((int64_t)((int64_t)(a)|\
                                                             ((int64_t)(b))<<8|\
                                                             ((int64_t)(c))<<16|\
                                                             ((int64_t)(d))<<24|\
                                                             ((int64_t)(e))<<32|\
                                                             ((int64_t)(f))<<40|\
                                                             ((int64_t)(g))<<48|\
                                                             ((int64_t)(h))<<56))
#else /* the host byte order is Most Significant Byte first */
#  define u_test_bit(n,c) ((((c) >> n) & 1) != 0)

#  define u_invert32(n) (((n) >> 24)               | \
                        (((n) >>  8) & 0x0000ff00) | \
                        (((n) <<  8) & 0x00ff0000) | \
                        ( (n) << 24))

#  define u_htonll(x) (x)
#  define u_ntohll(x) (x)

#  define U_NUM2STR16(ptr,val1)             (((union uucflag*)(ptr))->lo = \
                                              (int16_t)((uint8_t)(u_ctn2s[((val1)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val1)*2)])<<8))

#  define U_NUM2STR32(ptr,val2,val1)        (((union uucflag*)(ptr))->u = \
                                              (int16_t)((uint8_t)(u_ctn2s[((val1)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val1)*2)])<<8)|\
                                             ((int16_t)((uint8_t)(u_ctn2s[((val2)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val2)*2)])<<8))<<16)

#  define U_NUM2STR64(ptr,c,val3,val2,val1) (((union uucflag64*)(ptr))->u = \
                                             ((int64_t)((uint8_t)(u_ctn2s[((val1)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val1)*2)])<<8))|\
                                            (((int64_t)(c))<<16)|\
                                            (((int64_t)((uint8_t)(u_ctn2s[((val2)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val2)*2)])<<8))<<24)|\
                                            (((int64_t)(c))<<40)|\
                                            (((int64_t)((uint8_t)(u_ctn2s[((val3)*2)+1])|\
                                                        (uint8_t)(u_ctn2s[((val3)*2)])<<8))<<48))

#  define U_MULTICHAR_CONSTANT16(b,a)              ((int16_t)((uint8_t)(a)|\
                                                              (uint8_t)(b)<<8))

#  define U_MULTICHAR_CONSTANT32(d,c,b,a)          ((int32_t)((uint8_t)(a)|\
                                                              (uint8_t)(b)<<8|\
                                                              (uint8_t)(c)<<16|\
                                                              (uint8_t)(d)<<24))

#  define U_MULTICHAR_CONSTANT64(h,g,f,e,d,c,b,a)  ((int64_t)((int64_t)(a)|\
                                                             ((int64_t)(b))<<8|\
                                                             ((int64_t)(c))<<16|\
                                                             ((int64_t)(d))<<24|\
                                                             ((int64_t)(e))<<32|\
                                                             ((int64_t)(f))<<40|\
                                                             ((int64_t)(g))<<48|\
                                                             ((int64_t)(h))<<56))
#endif

/* Check for dot entry in directory */

#define U_ISDOTS(d_name) (  d_name[0] == '.'  && \
                          ( d_name[1] == '\0' || \
                           (d_name[1] == '.'  && \
                            d_name[2] == '\0')))

/* Memory alignment for pointer */

#define U_MEMORY_ALIGNMENT(ptr, alignment)  ptr += alignment - ((long)ptr & (alignment - 1))

/* Manage number suffix */

#define U_NUMBER_SUFFIX(number,suffix) \
   switch (suffix) { \
      case 'G': number <<= 10; \
      case 'M': number <<= 10; \
      case 'K': \
      case 'k': number <<= 10; \
      break; }
#endif

/* Optimization if it is enough a resolution of one second */

#ifdef ENABLE_THREAD
#  define U_gettimeofday  { if (u_pthread_time == 0)    (void) gettimeofday(u_now, 0); }
#else
#  define U_gettimeofday                                (void) gettimeofday(u_now, 0);
#endif

/* To print size of class */

#define U_PRINT_SIZEOF(class) printf("%ld sizeof(%s)\n", sizeof(class), #class)

/* Avoid "unused parameter" warnings */

#if defined(DEBUG) || defined(DEBUG_DEBUG)
#  define U_VAR_UNUSED(x)
#else
#  define U_VAR_UNUSED(x) (void)x;
#endif

/* #undef PLATFORM_VAR */

#ifndef PLATFORM_VAR
#define PLATFORM_VAR ""
#endif
