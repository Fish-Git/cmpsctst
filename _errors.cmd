@if defined TRACEON (@echo on) else (@echo off)

  setlocal

  set "work_dir=.\work"
  set "errors_log=%work_dir%\_errors.log"
  set "cmp_logs=%work_dir%\cmp*.log"

  if exist "%errors_log%" del "%errors_log%"

  (call :echo .)                                 >> "%errors_log%"
  (call :echo Searching log files for errors...) >> "%errors_log%"
  (call :echo .)                                 >> "%errors_log%"

  set  "find_str=ERROR"
  call :find_str "any error"

  set  "find_str=Code 0x0004"
  call :find_str "Protection Exception"

  set  "find_str=Code 0x0007"
  call :find_str "Data Exception"

  set  "find_str=Actual MD5"
  call :find_str "Expanded file does not match original input file"

  (call :echo .)                                         >> "%errors_log%"
  (call :echo DONE!  Errors log "%errors_log%" created.) >> "%errors_log%"

  endlocal
  goto :EOF

:find_str

  (call :echo .)                                        >> "%errors_log%"
  set "@=%~1"
  set "@=****  "%find_str%"  ***        ^^^(i.e. %@%^^^)"
  (call :echo %@%)                                      >> "%errors_log%"
  (call :echo .)                                        >> "%errors_log%"
  (ff.cmd /i "%find_str%" "%cmp_logs%" | find /i "---") >> "%errors_log%"
  (call :echo .)                                        >> "%errors_log%"
  goto :EOF

:echo
  if "%~1" == "." (echo.                 & goto :EOF)
                  (echo %time:~0,-3%   %*& goto :EOF)
