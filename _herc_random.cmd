@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  cls && call cmpsctst.cmd  .\files\small\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  >  .\work\cmpsctst-ser-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\EBCDIC  .\dicts  .\work  -a    -n      -r 4 -z  >  .\work\cmpsctst-ler-a.log
  cls && call cmpsctst.cmd  .\files\small\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  >  .\work\cmpsctst-sar-a.log
  cls && call cmpsctst.cmd  .\files\LARGE\ASCII   .\dicts  .\work  -a -t -n      -r 4 -z  >  .\work\cmpsctst-lar-a.log

  endlocal
  goto :EOF
