@echo off
REM Script de instalação do SQC no Windows

setlocal

REM Caminho atual (Downloads)
set SRC=%USERPROFILE%\Downloads\sqc.exe

REM Caminho de destino (instalação)
set DEST=%USERPROFILE%\SQC\bin

REM Cria a pasta de destino se não existir
if not exist "%DEST%" (
    mkdir "%DEST%"
)

REM Move o executável para a pasta de destino
move "%SRC%" "%DEST%\sqc.exe"

REM Adiciona ao PATH do sistema (precisa rodar como administrador)
setx PATH "%PATH%;%DEST%" /M

echo.
echo SQC installed em %DEST%
echo You could start SQC with 'sqc init'
echo.
pause
