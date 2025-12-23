@echo off
REM Remove previous outputs
if exist output_snap_tools.txt del output_snap_tools.txt
if exist output_roseira.txt del output_roseira.txt
if exist output_cantora.txt del output_cantora.txt
if exist output_snap_tools_hand.txt del output_snap_tools_hand.txt

REM Ensure build is up to date
C:\msys64\ucrt64\bin\g++.exe -fdiagnostics-color=always -g Adubo.cpp Cantora.cpp Cato.cpp Erva.cpp Ferramenta.cpp Interface.cpp Jardim.cpp Jardineiro.cpp main.cpp Planta.cpp Posicao.cpp Pulverizador.cpp Regador.cpp Roseira.cpp Tesoura.cpp -o trabalho_jardim.exe

if errorlevel 1 (
  echo Build failed, aborting tests.
  pause
  exit /b 1
)

REM Run tests
.\trabalho_jardim.exe < test_snap_tools.txt > output_snap_tools.txt
.\trabalho_jardim.exe < test_snap_tools_hand.txt > output_snap_tools_hand.txt
.\trabalho_jardim.exe < test_roseira_death.txt > output_roseira.txt
.\trabalho_jardim.exe < test_cantora.txt > output_cantora.txt

echo Tests finished. Output files: output_snap_tools.txt, output_snap_tools_hand.txt, output_roseira.txt, output_cantora.txt
pause