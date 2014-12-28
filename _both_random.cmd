@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _me_random.cmd
  call _herc_random.cmd

  call _errors.cmd

  endlocal
  goto :EOF
