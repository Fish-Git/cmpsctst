-------------------------------------------------------------------------------

    NAME

        cmpsctst  -  CMPSC Instruction Testing Tool helper script.

    SYNOPSIS

        cmpsctst.rexx    filesdir  dictsdir  [workdir]  [options]

    DESCRIPTION

        Uses the "CMPSCTST.EXE" Instruction Test Tool to verify
        the sanity of the given compression algorithm to within
        an acceptably high degree of confidence depending on the
        number and variety of files and dictionaries used.

    ARGUMENTS

        filesdir   The name of the directory tree where the set of
                   test files reside. All of the test files in the
                   specified directory and all subdirectories will
                   be processed against all dictionaries found in
                   the dictsdir directory.

        dictsdir   The name of the directory tree where the set of
                   test dictionaries reside. All of the dictionaries
                   in the specified directory and all subdirectories
                   will be processed against all of the test files
                   found in the filesdir directory.

        workdir    The name of a directory where temporary files
                   created during processing should be written. If
                   not specified the current directory is used. The
                   work files created during processing are called
                   "cmpout.bin", "expout.txt" and "md5sum.txt".

    OPTIONS

        -a      Algorithm to be used               (see NOTES below)
        -t      Translate ASCII/EBCDIC             (default = no)
        -r      Number of random tests             (default = 4)
        -r      Number of speed test repeats       (default = 4)
        -n      No hard-coded test cases           (default = all)
        -bn     Use only buffer sizes set 'n'      (default = all)
        -on     Use only buffer offsets set 'n'    (default = all)
        -speed  Speed test; -r = repeats           (see NOTES below)
        -z      Zero Padding [enabled:requested]   (see NOTES below)
        -w      Zero Padding Alignment             (default = 8 bit)
        -bb     Test Buffer Bits option            (default = 1:1)

    EXAMPLES

        cmpsctst  .\files        .\dicts  .\work  -z > EXTREMELY-long-test.log
        cmpsctst  .\files\small  .\dicts  .\work  -r 0 -z -w 3 > VERY-long-non-random-test.log
        cmpsctst  .\files\small  .\dicts  .\work  -n -r 3 -z 0:1 > short-randoms-test.log
        cmpsctst  .\files\large  .\dicts  .\work  -speed -r 100 > speed-test.log
        cmpsctst  .\files\small\ebcdic\ .\dicts\ .\work\ -a 1:0 -r 1 -n -z 0:0 -bb 0:1  >  .\work\cmp2base.txt

    NOTES

        Unless a timing run (speed test) or algorithm comparison
        test (cmp2base) is being done, cmpsctst repeatedly calls
        the CMPSCTST.EXE tool for every test file and dictionary
        found in the two specified directories and all of their
        subdirectories, first asking it to compress a test file
        to a temporary work file followed by expanding it to a
        second work file before finally comparing the MD5 hash
        of the expanded result to ensure it matches bit-for-bit
        with the original input.

        A series of several compress/expand cycles are performed,
        first using a hard-coded range of buffer size and offset
        values known to have caused problems in the past as well
        as a series of randomly generated input and output buffer
        size and offset values. If either of the compression or
        expansion calls fail or if the expanded output fails to
        exactly match the original input a diagnostic message is
        displayed describing the problem but the command does not
        abort. Rather, it continues on with the next set of files
        and dictionaries and does not end until after all passes
        are made against all files and dictionaries using all of
        of the previously mentioned buffer size and offset values.

                             ** WARNING! **

        cmpsctst.rexx produces a VERY large number of messages
        as it runs since the CMPSCTST.EXE tool is always called
        with the '-v' verbose option specified.

        It is therefore HIGHLY RECOMMENDED you redirect its stdout
        output to a log file. Redirecting stderr to a log file is
        optional but NOT recommended since the volume of progress
        messages written to stderr is quite small, being limited
        to notification when each new test is about to start and
        which dictionary it is using. It does NOT notify you when
        each new buffer size and offset value is used however.

                               - Note -

        Because a default test using the many built-in (hard-coded)
        buffer size and offset values can cause cmpsctst to run for
        a *VERY* long time since there are so many of them (33124
        times #of test files, times #of test dictionaries = total
        number of tests, each of which does a full compression and
        expansion) the -n (no-non-random) option allows you to skip
        these tests to allow cmpsctst to finish much more quickly.

        You can also use the -bn and -on options to choose a smaller
        subset of buffer size and/or offset values too. There are 3
        buffer size sets with 3, 6 and 4 values in each of their
        respective sets, and 2 sets of offset values with 9 and 5
        values in each of their respective sets. Specifying -b3 -o2
        for example, will cause 400 total tests to be performed for
        each file/dictionary pair. Thus for a set of 2 files and 3
        dictionaries, a grand total of 2400 tests will be performed.

        The -r value defines either the number of random buffer size
        and offset tests to perform or else the number of repeats to
        perform when the -speed option is specified.

        If the -speed option is not specified (default) the -r value
        defines the number of random generated buffer size and offset
        tests to perform for each file and dictionary pair. Specify 0
        to skip all randomly generated buffer size and offset tests
        and do only the built-in (non-random) tests instead.

        When the -speed option is specified it forces all hard-coded
        built-in and randomly generated buffer size and offset tests
        to be skipped, thereby altering the meaning of the -r option.
        When -speed is specified, the -r option instead defines the
        number of repeated compress and expand cycles to perform for
        each file, each of which always uses default buffer size and
        offset values. To perform a custom timing/speed test using
        specific buffer size and offset values, you need to call the
        CMPSCTST.EXE tool yourself (i.e. don't use cmpsctst.rexx).

        cmpsctst.rexx can also compare one algorithm against another
        by specifying the '-a' option as 'a:b', where 'a' identifies
        the test algorithm (the one being tested) and 'b' identifies
        the base algorithm (to compare the test algorithm's results
        against). As each buffer is either compressed or expanded
        the results are compared against the base algorithm's using
        the same register and buffer values. If any differences are
        found, the test immediately aborts (fails) and, if the '-v'
        verbose option given, the differences and all information
        needed to reproduce the error is then displayed.

        The '-z' (Zero Padding) option controls CMPSC-Enhancement
        Facility. Specify the option as two 0/1 values separated by
        a single colon. The first 0/1 defines whether the facility
        should be simulated as being enabled or not. The second 0/1
        controls whether the Zero Padding option (GR0 bit 46) should
        be set (requested) or not in the compression/expansion call.
        If the -z option is not specified the default is 0:0. If the
        option is specified but without any arguments then it's 1:1.

        The '-w' (Zero Padding Alignment) option controls adjustment
        of the model-dependent storage boundary used by zero padding.
        The value should be specified as a power of 2 number of bytes
        ranging from 1 to 12 (i.e. zero pad to 2-4096 byte boundary).

        The '-bb' (Test Buffer Bits) option indicates whether to check
        for the improper use of o/p or i/p buffer bits that according
        to the CBN should not be used as part of the compressed output
        or input. The option is specified as two 1/0 boolean values
        separated by a single colon. The first one indicates whether
        to perform the o/p buffer test during compression whereas the
        second one indicates whether to perform the same test for the
        i/p buffer during expansion. The default is 1:1 meaning both
        tests should always be performed.

        All dictionaries must be in RAW BINARY format and MUST use
        the following file naming convention:

                     <filename>.FST

        Where:

             F       Dictionary Format     0/1
             S       Symbol Size           1-5
             T       Dictionary Type       C/E

        Thus, for a 13-bit CDSS format-1 dictionary there must be
        two files with whatever name you want, but with filename
        extensions of:

             .15C        Compression dictionary
             .15E        Expansion dictonary

        For example:

            mydict.03C
            mydict.03E
            foobar.15C
            foobar.15E
            ...etc...

        Each dictionary pair MUST have the same name and each MUST
        be in the same directory and MUST be in raw binary format.

    EXIT STATUS

        0    Success.
        1    Failure.

    AUTHOR

        "Fish" (David B. Trout)

    VERSION

        2.6  (January 2014)

-------------------------------------------------------------------------------

CMPSC Instruction Testing Tool, version 2.6.0
Copyright (C) 2012-2014 Software Development Laboratories

Options:

  -c  Compress (default)
  -e  Expand
  -a  Algorithm (see NOTES)
  -r  Repeat Count

  -i  [buffer size:[offset:]] Input filename
  -o  [buffer size:[offset:]] Output Filename

  -d  Compression Dictionary Filename
  -x  Expansion Dictionary Filename

  -0  Format-0 (default)
  -1  Format-1
  -s  Symbol Size  (1-5 or 9-13; default = 2)

  -z  Zero Padding (enabled:requested; see NOTES)
  -w  Zero Padding Alignment (default = 8 bit)

  -t  Translate (ASCII <-> EBCDIC as needed)
  -b  Test proper cmp:exp out:input buffer CBN bit handling
  -v  Verbose [filename]
  -q  Quiet

Returns:

   0  Success
   4  Protection Exception
   7  Data Exception
   n  Other (i/o error, help requested, etc)

Examples:

  CMPSCTST -c -i 8192:*:foo.txt -o *:4095:foo.cmpsc -r 1000 \
           -t -d cdict.bin -x edict.bin -1 -s 10 -v rpt.log -z

  CMPSCTST -e -i foo.cmpsc -o foo.txt -t -x edict.bin -s 10 -q

  CMPSCTST -c -a 1:0 -v -i 22684:2509:in.txt -o 2307:3221:out.bin \
           -d cdict.bin -x edict.bin -s 5 -1 -z 0:0 -b 1:0

NOTES:

  You may specify the buffer size to be used for input or output by
  preceding the filename with a number followed by a colon. Use the
  value '*' for a randomly generated buffer size to be used instead.
  If not specified a default buffer size of 16 MB is used instead.

  Additionally, you may also optionally specify how you want your
  input or output buffer aligned by following a buffer size with a
  page offset value from 0-4095 indicating how many bytes past the
  beginning of the page that you wish the specified buffer to begin.

  Like the buffer size option using an '*' causes a random value to
  be generated instead. Please note however that not specifying an
  offset value does not mean your buffer will then be automatically
  page aligned. To the contrary it will most likely *not* be aligned.
  If you want your buffers to always be page aligned then you need to
  specify 0 for the offset. Dictionaries will always be page aligned.

  The '-z' (Zero Padding) option controls CMPSC-Enhancement Facility.
  Specify the option as two 0/1 values separated by a single colon.
  If the -z option is not specified the default is 0:0. If the option
  is specified but without any arguments then the default is 1:1.
  The first 0/1 defines whether the facility should be enabled or not.
  The second 0/1 controls whether the GR0 zero padding option bit 46
  should be set or not (i.e. whether the zero padding option should be
  requested or not). The two values together allow testing the proper
  handling of the facility since zero padding may only be attempted
  when both the Facility bit and the GR0 option bit 46 are both '1'.

  The '-w' (Zero Padding Alignment) option allows adjusting the model-
  dependent integral storage boundary for zero padding. The value is
  specified as a power of 2 number of bytes ranging from 1 to 12.

  Use the '-t' (Translate) option when testing using ASCII test files
  since most dictionaries are intended for EBCDIC data. If specified,
  the test data is first internally translated from ASCII to EBCDIC
  before being compressed and then from EBCDIC back into ASCII after
  being expanded. Specifying the '-t' option with EBCDIC test files
  will very likely cause erroneous compression/expansion results.

  The '-b' option indicates whether to check for the improper use of
  output/input buffer bits which according to the CBN should not be
  used as part of the compressed output/input. The option is specified
  as two 1/0 boolean values separated by a single colon. The first one
  indicates whether to perform the output buffer test during compression
  and the second one indicates whether to perform the same test for the
  input buffer during expansion. The default is 1:1 meaning both tests
  should be performed.

  The '-a' (Algorithm) option allows you to choose between different
  Compression Call algorithms to allow you to compare implementations
  to see which one is better/faster. The currently defined algorithms
  are as follows:

        default algorithm    0  =  CMPSC 2012
        alternate algorithm  1  =  Legacy CMPSC

  If you specify the -a option without also specifying which algorithm
  to use then the default alternate algorithm 1 will always be chosen.

  The -a option also allows you to perform an algorithm comparison test
  where the results of one algorithm (the one being tested) is compared
  against the results of the other (the base algorithm) using the format
  a:b where 'a' identifies the test algorithm and 'b' the base algorithm.
  As each buffer is compressed or expanded the results are compared with
  the base algorithm's results using the same register and buffer values.
  The test run immediately fails as soon as any difference is detected.
  If the -v option is also specified the detected differences as well as
  all information needed to reproduce the failure are also displayed.

  The '-r' (Repeat) option repeats each compression or expansion call
  the number of times specified. The input/output files are still read
  from and written to however. The repeat option only controls how many
  times to repeatedly call the chosen algorithm for each data block. It
  can be used to either exercise a given algorithm or perform a timing
  run on it for comparison with an alternate algorithm.

  The return code value, CPU time consumed and elapsed time are printed
  at the end of the run when the '-v' verbose option is specified. Else
  only the amount of data read/written and compression ratios are shown.
  The '-q' (Quiet) option runs silently without displaying anything.

-------------------------------------------------------------------------------
