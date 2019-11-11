# CMPSCTST &nbsp; -- &nbsp; CMPSC Instruction Testing Tool
## Contents

1. [Overview and History](#Overview-and-History)
2. [Building](#Building)
3. [Testing](#Testing)
4. [Test files](#Test-files)
5. [AutoBuildCount.h](#AutoBuildCount-h)
6. [cmpsctst.rexx](#cmpsctst-rexx)
7. [cmpsctst.exe](#cmpsctst-exe)

## Overview-and-History


The z/Architecture "cmpsc" instruction was designed to compress and expand
data, and is a very complicated instruction. So complicated in fact it even
has its own manual (SA22-7208-01).

Hercules's original cmpsc instruction implementation was written by Bernard
van der Helm and is very complicated. Several years ago a rather serious bug
which I was unable to find/fix reared its head in Bernard's implementation
for a paying client of mine.

Due to the way Bernard designed his implementation however, the only way he
could debug it was to first build a special debug version of Hercules which
would, when run, spit out a zillion progress messages which then needed to
be closely examined. This technique was unacceptable to the client since he
was using Hercules for real work. Shutting his system down, installing a new
"test" version of Hercules, bringing it up again, running a test to obtain
the zillions of debug log messages, shutting the system down again, then re-
installing the original non-debug (non-test) version of Hercules again and
bringing his system back up again was simply too painful (too instrusive),
especially since it was unknown how many times this would need to be done
before the bug was finally located. He could not be bouncing his system so
frequently nor installing test/debug versions of Hercules on the whim of a
Hercules developer. He had a business to run.

Since the compression and expansion algorithms were both clearly documented
in the manuals, I managed to convince my client to let me try writing my own
implementation if I could prove that it conformed to the archietcture without
requiring any input from him (i.e. without requiring him to do anything).

That meant I had to first write a program that would test evert aspect of
the instruction which I could then use to unit test my new code "offline"
by myself, outside of Hercules or a guest operating system itself. I.e. it
was to thoroughly test the "cmpsc" instruction itself and nothing else.

That is what **CMPSCTST** is: a program (and helper scripts) designed to test
Hercules's "cmpsc" instruction implementation as thoroughly as possible
for architectural compliance.

I've written it to be as generic as possible so that ANY implementation
can be quickly and easily tested. It's currently designed to test either
Bernard's implementation ("legacy"), and/or my own ("cmpsc_2012").

The program (executable) performs just a single test according to whatever
parameters you provide. The **rexx** helper script simply makes it easier to
call the executable multiple times, each time with a different set of test
parameters, thereby ensuring thorough test coverage.



## Building

### Windows:

  Manually create your own "AutoBuildCount.h" header file (see the section
  AutoBuildCount.h below) and then open the Visual Studio .SLN Solution file
  and click the "Rebuild Solution" button.

### Linux:

  Manually create your own "AutoBuildCount.h" header file (see the section
  AutoBuildCount.h below) and enter the command "make -f cmpsctst.make all".

Tested using Visual Studio 2008 Professional on Windows 7 x64 Ultimate and
using gcc 4.4 within a CentOS 6.4 VMware virtual machine.



## Testing

### Windows:

In addtion to the `cmpsctst.rexx` script and the `cmpsctst.exe` program,
there is also a set of simple Windows batch files that automates calling
the cmpsctst.rexx script for a certain set of high level parameters (ones
known to cause problems). They are designed to make it trivially easy to
test new or updated implementations via a single, simple command, without
having to remember the syntax of the many parameter options each supports.

The "herc" set of batch files tests Bernard's "legacy" implementation and
the "me" set of batch files tests my own improved cmpsc_2012 implemention
(and the "both" set of batch files of course test both implementations).

The "errors" batch file parses the output of the given test(s) to produce
a much simplified "condensed" test results summary file that just lists
the percentage of tests each implementation PASSED or FAILED.

### Linux:

Bash scripts exist with the same names as the previously mentioned Windows
batch files. Tested on CentOS 6.4 VMware virtual machine.

### Example:

To perform a "quick" test of the default "cmpsc_2012" algorithm, execute the
**`_quick_me`** script. Note that even though test is called a "quick" test it
will still run for several minutes. This is the quickest test there is.




## Test-files

Testing the compression call instruction is only as thorough as the data
used to test it with and the parameters used. Thus the CMPSCTST package
comes delivered with a set of test files known to have caused problems in
the past. All test files are organized under the "FILES" directory to make
it easier for the `cmpsctst.rexx` script to choose which set of test files
you wish to use. (Testing with more files and more dictionaries translates
directly into a more thorough test.)

Feel free to add your own set of test files and dictionaries, but be aware
that doing so will increase the run time for certain tests depending on which
set of test files (directories) you tell the cmpsctst.rexx script to use.
(More files == longer test run)

For more information refer to the **cmpsctst.rexx** section further below.




## AutoBuildCount-h

  I have my Visual Studio installation setup so the "AutoBuildCount.h" header
  file is automatically updated by an external tool each time I do a rebuild.

  If you are not me (and you aren't!) then you will need to manually create
  your own "AutoBuildCount.h" header. The header file should look like this:


```C
      #ifndef AUTOBUILDCOUNT
      #define AUTOBUILDCOUNT
      #define BUILDCOUNT_NUM  49
      #define BUILDCOUNT_STR "49"
      #define GITCTR_NUM      79
      #define GITHASH_STR    "79-gfcbebde"
      #endif
```


  The two values "GITCTR_NUM" and "GITHASH_STR" are the number of commits
  and the git hash value of the most recent commit (followed by a string
  indicating whether any local changes exist or not) and are obtained via
  the following git commands:


```bash
      git log --pretty=format:'' | wc -l
      git rev-parse --verify HEAD
      git diff-index --quiet HEAD & echo %errorlevel%
```


  (The BUILDCOUNT_NUM is simply an ever-increasing value I no longer use.)




## cmpsctst-rexx
<pre>

    <b>NAME</b>

        cmpsctst  -  CMPSC Instruction Testing Tool helper script.

    <b>SYNOPSIS</b>

        cmpsctst.rexx    filesdir  dictsdir  [workdir]  [options]

    <b>DESCRIPTION</b>

        Uses the "CMPSCTST.EXE" Instruction Test Tool to verify
        the sanity of the given compression algorithm to within
        an acceptably high degree of confidence depending on the
        number and variety of files and dictionaries used.

    <b>ARGUMENTS</b>

        <i>filesdir</i>   The name of the directory tree where the set of
                   test files reside. All of the test files in the
                   specified directory and all subdirectories will
                   be processed against all dictionaries found in
                   the dictsdir directory.

        <i>dictsdir</i>   The name of the directory tree where the set of
                   test dictionaries reside. All of the dictionaries
                   in the specified directory and all subdirectories
                   will be processed against all of the test files
                   found in the filesdir directory.

        <i>workdir</i>    The name of a directory where temporary files
                   created during processing should be written. If
                   not specified the current directory is used. The
                   work files created during processing are called
                   "cmpout.bin", "expout.txt" and "md5sum.txt".

    <b>OPTIONS</b>

        <b>-a</b>        Algorithm to be used              (see NOTES below)
        <b>-t</b>        Translate ASCII/EBCDIC            (default = no)
        <b>-r</b>        Number of random tests            (default = 4)
        <b>-r</b>        Number of speed test repeats      (default = 4)
        <b>-n</b>        No hard-coded test cases          (default = all)
        <b>-bn</b>       Use only buffer sizes set 'n'     (default = all)
        <b>-on</b>       Use only buffer offsets set 'n'   (default = all)
        <b>-speed</b>    Speed test; -r = repeats          (see NOTES below)
        <b>-z</b>        Zero Padding [enabled:requested]  (see NOTES below)
        <b>-w</b>        Zero Padding Alignment            (default = 8 bit)
        <b>-bb</b>       Test Buffer Bits option           (default = 1:1)

    <b>EXAMPLES</b>

        cls && rexx cmpsctst.rexx .\FILES\              .\DICTS\ .\WORK\ -z                            > .\WORK\EONS-long-test.log
        cls && rexx cmpsctst.rexx .\FILES\SMALL\        .\DICTS\ .\WORK\ -r 0 -z -w 3                  > .\WORK\EONS-long-non-random-test.log
        cls && rexx cmpsctst.rexx .\FILES\SMALL\EBCDIC\ .\DICTS\ .\WORK\ -n -r 3 -z 0:1                > .\WORK\short-randoms-test.log
        cls && rexx cmpsctst.rexx .\FILES\LARGE\        .\DICTS\ .\WORK\ -speed -r 100                 > .\WORK\speed-test.log
        cls && rexx cmpsctst.rexx .\FILES\SMALL\EBCDIC\ .\DICTS\ .\WORK\ -a 1:0 -r 1 -n -z 0:0 -bb 0:1 > .\WORK\cmp2base.txt

    <b>NOTES</b>

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

                             <b>** WARNING! **</b>

        cmpsctst.rexx produces a VERY large number of messages
        as it runs since the CMPSCTST.EXE tool is always called
        with the '<b>-v</b>' verbose option specified.

        It is therefore HIGHLY RECOMMENDED you redirect its stdout
        output to a log file. Redirecting stderr to a log file is
        optional but NOT recommended since the volume of progress
        messages written to stderr is quite small, being limited
        to notification when each new test is about to start and
        which dictionary it is using. It does NOT notify you when
        each new buffer size and offset value is used however.

                               <b>- Note -</b>

        Because a default test using the many built-in (hard-coded)
        buffer size and offset values can cause cmpsctst to run for
        a <i><b>*VERY*</b></i> long time since there are so many of them (33124
        times #of test files, times #of test dictionaries = total
        number of tests, each of which does a full compression and
        expansion) the <b>-n</b> (no-non-random) option allows you to skip
        these tests to allow cmpsctst to finish much more quickly.

        You can also use the <b>-bn</b> and <b>-on</b> options to choose a smaller
        subset of buffer size and/or offset values too. There are 3
        buffer size sets with 3, 6 and 4 values in each of their
        respective sets, and 2 sets of offset values with 9 and 5
        values in each of their respective sets. Specifying <b>-b3 -o2</b>
        for example, will cause 400 total tests to be performed for
        each file/dictionary pair. Thus for a set of 2 files and 3
        dictionaries, a grand total of 2400 tests will be performed.

        The <b>-r</b> value defines either the number of random buffer size
        and offset tests to perform or else the number of repeats to
        perform when the <b>-speed</b> option is specified.

        If the <b>-speed</b> option is not specified (default) the <b>-r</b> value
        defines the number of random generated buffer size and offset
        tests to perform for each file and dictionary pair. Specify 0
        to skip all randomly generated buffer size and offset tests
        and do only the built-in (non-random) tests instead.

        When the <b>-speed</b> option is specified it forces all hard-coded
        built-in and randomly generated buffer size and offset tests
        to be skipped, thereby altering the meaning of the <b>-r</b> option.
        When <b>-speed</b> is specified, the <b>-r</b> option instead defines the
        number of repeated compress and expand cycles to perform for
        each file, each of which always uses default buffer size and
        offset values. To perform a custom timing/speed test using
        specific buffer size and offset values, you need to call the
        CMPSCTST.EXE tool yourself (i.e. don't use cmpsctst.rexx).

        cmpsctst.rexx can also compare one algorithm against another
        by specifying the '<b>-a</b>' option as '<b>a:b</b>', where '<b>a</b>' identifies
        the test algorithm (the one being tested) and 'b' identifies
        the base algorithm (to compare the test algorithm's results
        against). As each buffer is either compressed or expanded
        the results are compared against the base algorithm's using
        the same register and buffer values. If any differences are
        found, the test immediately aborts (fails) and, if the '<b>-v</b>'
        verbose option given, the differences and all information
        needed to reproduce the error is then displayed.

        The '<b>-z</b>' (Zero Padding) option controls CMPSC-Enhancement
        Facility. Specify the option as two 0/1 values separated by
        a single colon. The first 0/1 defines whether the facility
        should be simulated as being enabled or not. The second 0/1
        controls whether the Zero Padding option (GR0 bit 46) should
        be set (requested) or not in the compression/expansion call.
        If the <b>-z</b> option is not specified the default is <b>0:0</b>. If the
        option is specified but without any arguments then it's <b>1:1</b>.

        The '<b>-w</b>' (Zero Padding Alignment) option controls adjustment
        of the model-dependent storage boundary used by zero padding.
        The value should be specified as a power of 2 number of bytes
        ranging from 1 to 12 (i.e. zero pad to 2-4096 byte boundary).

        The '<b>-bb</b>' (Test Buffer Bits) option indicates whether to check
        for the improper use of o/p or i/p buffer bits that according
        to the CBN should not be used as part of the compressed output
        or input. The option is specified as two 1/0 boolean values
        separated by a single colon. The first one indicates whether
        to perform the o/p buffer test during compression whereas the
        second one indicates whether to perform the same test for the
        i/p buffer during expansion. The default is <b>1:1</b> meaning both
        tests should always be performed.

        All dictionaries must be in RAW BINARY format and MUST use
        the following file naming convention:

                     &lt;filename&gt;<b>.FST</b>

        Where:

             <b>F</b>       Dictionary Format     0/1
             <b>S</b>       Symbol Size           1-5
             <b>T</b>       Dictionary Type       C/E

        Thus, for a 13-bit CDSS format-1 dictionary there must be
        two files with whatever name you want, but with filename
        extensions of:

             <b>.15C</b>        Compression dictionary
             <b>.15E</b>        Expansion dictonary

        For example:

            mydict.<b>03C</b>
            mydict.<b>03E</b>
            foobar.<b>15C</b>
            foobar.<b>15E</b>
            ...etc...

        Each dictionary pair MUST have the same name and each MUST
        be in the same directory and MUST be in raw binary format.

    <b>EXIT STATUS</b>

        0    Success.
        1    Failure.

    <b>AUTHOR</b>

        "Fish" (David B. Trout)

    <b>VERSION</b>

        2.6  (January 2014)

</pre>

## cmpsctst-exe

<pre>
CMPSC Instruction Testing Tool, version 2.6.2
Copyright (C) 2012-2014 Software Development Laboratories

<b>Options:</b>

  <b>-c</b>    Compress (default)
  <b>-e</b>    Expand
  <b>-a</b>    Algorithm (see NOTES)
  <b>-r</b>    Repeat Count

  <b>-i</b>    [buffer size:[offset:]] Input filename
  <b>-o</b>    [buffer size:[offset:]] Output Filename

  <b>-d</b>    Compression Dictionary Filename
  <b>-x</b>    Expansion Dictionary Filename

  <b>-0</b>    Format-0 (default)
  <b>-1</b>    Format-1
  <b>-s</b>    Symbol Size  (1-5 or 9-13; default = 2)

  <b>-z</b>    Zero Padding (enabled:requested; see NOTES)
  <b>-w</b>    Zero Padding Alignment (default = 8 bit)

  <b>-t</b>    Translate (ASCII <-> EBCDIC as needed)
  <b>-b</b>    Test proper cmp:exp out:input buffer CBN bit handling
  <b>-v</b>    Verbose [filename]
  <b>-q</b>    Quiet

<b>Returns:</b>

   0    Success
   4    Protection Exception
   7    Data Exception
   n    Other (i/o error, help requested, etc)

<b>Examples:</b>

  CMPSCTST -c -i 8192:*:foo.txt -o *:4095:foo.cmpsc -r 1000 \
           -t -d cdict.bin -x edict.bin -1 -s 10 -v rpt.log -z

  CMPSCTST -e -i foo.cmpsc -o foo.txt -t -x edict.bin -s 10 -q

  CMPSCTST -c -a 1:0 -v -i 22684:2509:in.txt -o 2307:3221:out.bin \
           -d cdict.bin -x edict.bin -s 5 -1 -z 0:0 -b 1:0

<b>NOTES:</b>

  You may specify the buffer size to be used for input or output by
  preceding the filename with a number followed by a colon. Use the
  value '<b>*</b>' for a randomly generated buffer size to be used instead.
  If not specified a default buffer size of 16 MB is used instead.

  Additionally, you may also optionally specify how you want your
  input or output buffer aligned by following a buffer size with a
  page offset value from 0-4095 indicating how many bytes past the
  beginning of the page that you wish the specified buffer to begin.

  Like the buffer size option using an '<b>*</b>' causes a random value to
  be generated instead. Please note however that not specifying an
  offset value does not mean your buffer will then be automatically
  page aligned. To the contrary it will most likely *not* be aligned.
  If you want your buffers to always be page aligned then you need to
  specify 0 for the offset. Dictionaries will always be page aligned.

  The '<b>-z</b>' (Zero Padding) option controls CMPSC-Enhancement Facility.
  Specify the option as two 0/1 values separated by a single colon.
  If the <b>-z</b> option is not specified the default is <b>0:0</b>. If the option
  is specified but without any arguments then the default is <b>1:1</b>.
  The first 0/1 defines whether the facility should be enabled or not.
  The second 0/1 controls whether the GR0 zero padding option bit 46
  should be set or not (i.e. whether the zero padding option should be
  requested or not). The two values together allow testing the proper
  handling of the facility since zero padding may only be attempted
  when both the Facility bit and the GR0 option bit 46 are both '1'.

  The '<b>-w</b>' (Zero Padding Alignment) option allows adjusting the model-
  dependent integral storage boundary for zero padding. The value is
  specified as a power of 2 number of bytes ranging from 1 to 12.

  Use the '<b>-t</b>' (Translate) option when testing using ASCII test files
  since most dictionaries are intended for EBCDIC data. If specified,
  the test data is first internally translated from ASCII to EBCDIC
  before being compressed and then from EBCDIC back into ASCII after
  being expanded. Specifying the '<b>-t</b>' option with EBCDIC test files
  will very likely cause erroneous compression/expansion results.

  The '<b>-b</b>' option indicates whether to check for the improper use of
  output/input buffer bits which according to the CBN should not be
  used as part of the compressed output/input. The option is specified
  as two 1/0 boolean values separated by a single colon. The first one
  indicates whether to perform the output buffer test during compression
  and the second one indicates whether to perform the same test for the
  input buffer during expansion. The default is <b>1:1</b> meaning both tests
  should be performed.

  The '<b>-a</b>' (Algorithm) option allows you to choose between different
  Compression Call algorithms to allow you to compare implementations
  to see which one is better/faster. The currently defined algorithms
  are as follows:

        <b>default algorithm    0  =  CMPSC 2012</b>
        <b>alternate algorithm  1  =  Legacy CMPSC</b>

  If you specify the <b>-a</b> option without also specifying which algorithm
  to use then the default alternate algorithm 1 will always be chosen.

  The <b>-a</b> option also allows you to perform an algorithm comparison test
  where the results of one algorithm (the one being tested) is compared
  against the results of the other (the base algorithm) using the format
  <b>a:b</b> where '<b>a</b>' identifies the test algorithm and 'b' the base algorithm.
  As each buffer is compressed or expanded the results are compared with
  the base algorithm's results using the same register and buffer values.
  The test run immediately fails as soon as any difference is detected.
  If the <b>-v</b> option is also specified the detected differences as well as
  all information needed to reproduce the failure are also displayed.

  The '<b>-r</b>' (Repeat) option repeats each compression or expansion call
  the number of times specified. The input/output files are still read
  from and written to however. The repeat option only controls how many
  times to repeatedly call the chosen algorithm for each data block. It
  can be used to either exercise a given algorithm or perform a timing
  run on it for comparison with an alternate algorithm.

  The return code value, CPU time consumed and elapsed time are printed
  at the end of the run when the '<b>-v</b>' verbose option is specified. Else
  only the amount of data read/written and compression ratios are shown.
  The '<b>-q</b>' (Quiet) option runs silently without displaying anything.

</pre>
