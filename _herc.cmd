@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  >  .\work\cmpsctst-ser-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  >  .\work\cmpsctst-ler-a.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  >  .\work\cmpsctst-sar-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  >  .\work\cmpsctst-lar-a.log

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work  -a    -b1 -o1 -r 0 -z  >  .\work\cmpsctst-sen-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work  -a    -b1 -o1 -r 0 -z  >  .\work\cmpsctst-len-a.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work  -a -t -b1 -o1 -r 0 -z  >  .\work\cmpsctst-san-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work  -a -t -b1 -o1 -r 0 -z  >  .\work\cmpsctst-lan-a.log

         call _errors.cmd

  endlocal
  goto :EOF
