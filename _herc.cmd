@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _herc_random.cmd
  call _herc_builtin.cmd
  call _errors.cmd

  endlocal
  goto :EOF
