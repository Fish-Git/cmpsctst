@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _me_builtin.cmd
  call _herc_builtin.cmd

  call _errors.cmd

  endlocal
  goto :EOF
