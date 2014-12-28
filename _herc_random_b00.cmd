@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-ser-b00-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-ler-b00-a.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-sar-b00-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-lar-b00-a.log

  endlocal
  goto :EOF
