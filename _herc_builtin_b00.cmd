@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work  -a    -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-sen-b00-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work  -a    -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-len-b00-a.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work  -a -t -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-san-b00-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work  -a -t -o1 -r 0 -z  -bb 0:0  >  .\work\cmpsctst-lan-b00-a.log

  endlocal
  goto :EOF
