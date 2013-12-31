@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work        -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-sen.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work        -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-len.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work     -t -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-san.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work     -t -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-lan.log

  endlocal
  goto :EOF
