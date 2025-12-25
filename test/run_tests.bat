@echo off
REM Remove previous outputs (in test folder)
if exist test\output_snap_tools.txt del test\output_snap_tools.txt
if exist test\output_roseira.txt del test\output_roseira.txt
if exist test\output_cantora.txt del test\output_cantora.txt
if exist test\output_snap_tools_hand.txt del test\output_snap_tools_hand.txt

REM Ensure build is up to date
C:\msys64\ucrt64\bin\g++.exe -fdiagnostics-color=always -g Adubo.cpp Cantora.cpp Cato.cpp Erva.cpp Ferramenta.cpp Interface.cpp Jardim.cpp Jardineiro.cpp main.cpp Planta.cpp Posicao.cpp Pulverizador.cpp Regador.cpp Roseira.cpp Tesoura.cpp -o trabalho_jardim.exe

if errorlevel 1 (
  echo Build failed, aborting tests.
  pause
  exit /b 1
)

REM Run tests (only if input test files exist)
if exist test\test_snap_tools.txt (
  .\trabalho_jardim.exe < test\test_snap_tools.txt > test\output_snap_tools.txt
) else (
  echo Skipping missing test: test\test_snap_tools.txt
)
if exist test\test_snap_tools_hand.txt (
  .\trabalho_jardim.exe < test\test_snap_tools_hand.txt > test\output_snap_tools_hand.txt
) else (
  echo Skipping missing test: test\test_snap_tools_hand.txt
)
if exist test\test_roseira_death.txt (
  .\trabalho_jardim.exe < test\test_roseira_death.txt > test\output_roseira.txt
) else (
  echo Skipping missing test: test\test_roseira_death.txt
)
if exist test\test_cantora.txt (
  .\trabalho_jardim.exe < test\test_cantora.txt > test\output_cantora.txt
) else (
  echo Skipping missing test: test\test_cantora.txt
)

echo Tests finished. Output files in test\: output_snap_tools.txt, output_snap_tools_hand.txt, output_roseira.txt, output_cantora.txt
pause