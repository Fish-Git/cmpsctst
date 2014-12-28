@if defined TRACEON (@echo on) else (@echo off)
goto :begin

@REM  If this batch file works then it was written by Fish.
@REM  If it doesn't then I don't know who the heck wrote it.

:----------------------------------------------------------------------
:help

  echo.
  echo     NAME
  echo.
  echo         %~nx0   Searches for a string in the specified file(s).
  echo.
  echo     SYNOPSIS
  echo.
  echo         %~nx0   [options]  "string"  {file [file ...]}
  echo.
  echo     DESCRIPTION
  echo.
  echo         %~n0 is simply a wrapper for the "find.exe" command that
  echo         simply skips displaying the file(s) that do NOT contain
  echo         the specified string.
  echo.
  echo     OPTIONS
  echo.
  echo         /V   Shows only the lines NOT containing the string.
  echo         /C   Shows only the #of lines containing the string.
  echo         /N   Precedes all found lines with its line number.
  echo         /I   Ignores case when searching for the string.
  echo.
  echo     EXIT STATUS
  echo.
  echo         0    if the string was found in ANY of the files.
  echo         1    if the string was found in NONE of the files.
  echo.
  echo     AUTHOR
  echo.
  echo         "Fish" (David B. Trout)
  echo.
  echo     VERSION
  echo.
  echo         1.0  (April 21, 2009)

  endlocal
  goto :EOF

:----------------------------------------------------------------------
:begin

  setlocal
  set "TRACE=if defined DEBUG echo"
  set rc=0

  if    "%~1" == ""       goto :help
  if /i "%~1" == "/?"     goto :help
  if /i "%~1" == "-?"     goto :help
  if /i "%~1" == "--help" goto :help

  set "options="

:options_loop

  set "opt=%~1"

  if     "%opt%"      == ""  goto :options_loop_end
  if not "%opt:~0,1%" == "/" goto :options_loop_end

  set "options=%options% %opt%"

  shift /1
  goto :options_loop

:options_loop_end

  set "string=%~1"
  shift /1

  if "%string%" == "" goto :help
  set "wrkfile=%temp%\find%random%.tmp"
  set "found="

:find_loop

  for %%a in (%1) do call :find_sub "%%a"
  shift /1
  if not "%~1" == "" goto :find_loop

                       %TRACE%.
  if     defined found %TRACE%   ** FOUND! **
  if not defined found %TRACE%   ** NOT found **

  if     defined found set rc=0
  if not defined found set rc=1

  endlocal & set "rc=%rc%"
  set "rc="& exit /b %rc%

:find_sub

  find.exe  %options%  "%string%"  %1  >  "%wrkfile%"
  set rc=%errorlevel%
  if %rc% == 0 set found=1
  if %rc% == 0 type "%wrkfile%"
  del "%wrkfile%"
  goto :EOF
