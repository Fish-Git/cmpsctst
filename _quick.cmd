@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  call _herc_random.cmd
  call _herc_random_b00.cmd

  call _me_random.cmd
  call _me_random_b00.cmd

  call _errors.cmd

  endlocal
  goto :EOF
