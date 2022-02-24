/////////////////////////////////////////////////////////////////////////////////////////
//  CMPSCTSTVERS.h  --  defines the build version for the product itself
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMPSCTSTVERS_H
#define CMPSCTSTVERS_H

//////////////////////////////////
#include "AutoBuildCount.h"     //  (where GITCTR_NUM and GITHASH_STR are defined)
//////////////////////////////////

#define VERMAJOR_NUM     2          // MAJOR Release (program radically changed)
#define VERMAJOR_STR    "2"
                       
#define VERINTER_NUM     7          // Minor Enhancements (new features, etc)
#define VERINTER_STR    "7" 
                       
#define VERMINOR_NUM     1          // Bug Fix or rebuild/relink, etc.
#define VERMINOR_STR    "1"

#ifdef _DEBUG
#define VERSION_STR     VERMAJOR_STR "." VERINTER_STR "." VERMINOR_STR "." GITHASH_STR "-D"
#else
#define VERSION_STR     VERMAJOR_STR "." VERINTER_STR "." VERMINOR_STR "." GITHASH_STR
#endif

#endif // CMPSCTSTVERS_H
