@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _both_random_b00.cmd
  call _both_builtin_b00.cmd

  call _errors.cmd

  endlocal
  goto :EOF
