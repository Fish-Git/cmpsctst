/*-------------------------------------------------------------------*/
/*                       Windows compatibility                       */
/*-------------------------------------------------------------------*/
#if defined(_WIN32) || defined(WIN32)
   /* Normalize WIN32/_WIN32 flags */
#  if !defined(_WIN32) && defined(WIN32)
#    define _WIN32
#  elif defined(_WIN32) && !defined(WIN32)
#    define WIN32
#  endif
   /* Normalize WIN64/_WIN64 flags */
#  if defined(_WIN64) || defined(WIN64)
#    if !defined(_WIN64) && defined(WIN64)
#      define _WIN64
#    elif defined(_WIN64) && !defined(WIN64)
#      define WIN64
#    endif
#  endif
   /* Normalize DEBUG/_DEBUG flags */
#  if defined(_DEBUG) || defined(DEBUG)
#    if !defined(_DEBUG) && defined(DEBUG)
#      define _DEBUG
#    elif defined(_DEBUG) && !defined(DEBUG)
#      define DEBUG
#    endif
#  endif
#endif /* defined(_WIN32) || defined(WIN32) */
