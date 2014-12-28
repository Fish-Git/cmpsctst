@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _both_random.cmd
  call _both_builtin.cmd

  call _errors.cmd

  endlocal
  goto :EOF
