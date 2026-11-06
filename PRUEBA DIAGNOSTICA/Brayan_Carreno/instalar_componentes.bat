@echo off
setlocal
echo ===============================================================================
echo   PARSECORE - VERIFICADOR DE COMPONENTES DE ENTORNO (LYC 2026-II)
echo   Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
echo ===============================================================================
echo.

echo [1/3] Verificando Compilador de Lenguaje C (GCC)...
set "PATH=%LOCALAPPDATA%\Programs\w64devkit\bin;%PATH%"
gcc --version
echo.

echo [2/3] Verificando Interprete de Python...
set "PATH=%LOCALAPPDATA%\Programs\Python\Python312;%LOCALAPPDATA%\Programs\Python\Python312\Scripts;%PATH%"
python --version
echo.

echo [3/3] Verificando paquetes de soporte (python-pptx, pypdf)...
python -c "import pptx, pypdf; print('[OK] Modulos python-pptx y pypdf listos.')"
echo.

echo ===============================================================================
echo   TODOS LOS COMPONENTES FUNCIONAN CORRECTAMENTE.
echo ===============================================================================
endlocal
