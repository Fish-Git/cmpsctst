
CC     = gcc
EXE    = cmpsctst
CFLAGS = -Wall -O2
LFLAGS =

CMPSC_HEADER_FILES =

CMPSC_SOURCE_FILES = \
  cmpsc.c

CMPSC_2012_SOURCE_FILES = \
  cmpsc_2012.c            \
  cmpscdbg.c              \
  cmpscdct.c              \
  cmpscget.c              \
  cmpscmem.c              \
  cmpscput.c              \
  cmpsctst.c

CMPSC_2012_HEADER_FILES = \
  cmpsc.h                 \
  cmpscbit.h              \
  cmpscdbg.h              \
  cmpscdct.h              \
  cmpscget.h              \
  cmpscmem.h              \
  cmpscput.h

CMPSCTST_SOURCE_FILES =   \
  cmpsctst.c              \
  cmpsctst_cmpsc.c        \
  cmpsctst_cmpsc_2012.c   \
  cmpsctst_cmpscdbg.c     \
  cmpsctst_cmpscdct.c     \
  cmpsctst_cmpscget.c     \
  cmpsctst_cmpscmem.c     \
  cmpsctst_cmpscput.c     \
  hexdumpe.c

CMPSCTST_HEADER_FILES =   \
  cmpsctst_stdinc.h       \
  cmpsctst.h              \
  AutoBuildCount.h        \
  CMPSCTSTPROD.h          \
  CMPSCTSTVERS.h          \
  hstdinc.h               \
  hexdumpe.h

ALL_OTHER_FILES =         \
  CMPSCTST.rc             \
  CMPSCTST.rc2            \
  SpecialBuild.rc2        \
  _TODO.txt               \
  NOTES.txt               \
  README.txt              \
  cmpsctst.make           \
  cmpsctst.rexx           \
  cmpsctst.cmd            \
  _quick.cmd              \
  _quick_herc.cmd         \
  _quick_me.cmd           \
  _errors.cmd             \
  ff.cmd                  \
  _both.cmd               \
  _both_b00.cmd           \
  _both_builtin.cmd       \
  _both_builtin_b00.cmd   \
  _both_random.cmd        \
  _both_random_b00.cmd    \
  _herc.cmd               \
  _herc_b00.cmd           \
  _herc_builtin.cmd       \
  _herc_builtin_b00.cmd   \
  _herc_random.cmd        \
  _herc_random_b00.cmd    \
  _me.cmd                 \
  _me_b00.cmd             \
  _me_builtin.cmd         \
  _me_builtin_b00.cmd     \
  _me_random.cmd          \
  _me_random_b00.cmd      \
  _quick                  \
  _quick_herc             \
  _quick_me               \
  _errors                 \
  ff                      \
  _both                   \
  _both_b00               \
  _both_builtin           \
  _both_builtin_b00       \
  _both_random            \
  _both_random_b00        \
  _herc                   \
  _herc_b00               \
  _herc_builtin           \
  _herc_builtin_b00       \
  _herc_random            \
  _herc_random_b00        \
  _me                     \
  _me_b00                 \
  _me_builtin             \
  _me_builtin_b00         \
  _me_random              \
  _me_random_b00

ALL_HEADER_FILES  = $(CMPSC_HEADER_FILES) $(CMPSC_2012_HEADER_FILES) $(CMPSCTST_HEADER_FILES)
ALL_SOURCE_FILES  = $(CMPSC_SOURCE_FILES) $(CMPSC_2012_SOURCE_FILES) $(CMPSCTST_SOURCE_FILES)
ALL_FILES         = $(ALL_HEADER_FILES) $(ALL_SOURCE_FILES) $(ALL_OTHER_FILES)

CMPSCTST_OBJECT_FILES = $(CMPSCTST_SOURCE_FILES:.c=.o)

all: $(EXE)

$(EXE): $(ALL_FILES) $(CMPSCTST_OBJECT_FILES)
	$(CC) $(LFLAGS) $(CMPSCTST_OBJECT_FILES) -o $(EXE)

$(CMPSCTST_OBJECT_FILES): $(CMPSCTST_SOURCE_FILES)
	$(CC) $(CFLAGS) -I. -c $*.c -o $@

clean:
	rm -rf $(CMPSCTST_OBJECT_FILES) $(EXE)

$(ALL_OTHER_FILES):

