@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work        -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-ser.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work        -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-ler.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work     -t -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-sar.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work     -t -n      -r 4 -z  -bb 0:0  >  .\work\cmpsctst-lar.log

  endlocal
  goto :EOF
