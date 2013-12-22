@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "opath=%path%"
  set "path=%cd%\x64\Release;%opath%"

  call _me_random.cmd
  call _herc_random.cmd

  call _me_builtin.cmd
  call _herc_builtin.cmd

  call _errors.cmd

  endlocal
  goto :EOF
