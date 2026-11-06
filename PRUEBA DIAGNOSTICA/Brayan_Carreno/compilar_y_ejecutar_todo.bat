@echo off
setlocal
set "BASE_DIR=%~dp0"
set "PATH=%LOCALAPPDATA%\Programs\w64devkit\bin;%LOCALAPPDATA%\Programs\Python\Python312;%LOCALAPPDATA%\Programs\Python\Python312\Scripts;%PATH%"

echo ===============================================================================
echo   PARSECORE - EJECUCION DE PRUEBA DIAGNOSTICA (LYC 2026-II)
echo   Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
echo ===============================================================================
echo.

echo [PASO 1/3] Compilando y ejecutando Ejercicio 1 (Ajedrez - Caballo)...
pushd "%BASE_DIR%Ejercicio_1_Ajedrez_Caballo"
gcc -O3 caballo.c -o caballo.exe
caballo.exe
python caballo.py
popd
echo.

echo [PASO 2/3] Compilando y ejecutando Ejercicio 2 (Pascal y Polinomio)...
pushd "%BASE_DIR%Ejercicio_2_Pascal_Polinomio"
gcc -O3 pascal_polinomio.c -o pascal_polinomio.exe -lm
pascal_polinomio.exe
python pascal_polinomio.py
popd
echo.

echo [PASO 3/3] Compilando y ejecutando Ejercicio 3 (Lexer C a Espanol)...
pushd "%BASE_DIR%Ejercicio_3_Lexer_Traductor_C"
gcc -O3 lexer_traductor.c -o lexer_traductor.exe
lexer_traductor.exe
python lexer_traductor.py
popd
echo.

echo ===============================================================================
echo   EJECUCION COMPLETADA: Todos los ejercicios y benchmarks generados.
echo ===============================================================================
endlocal
