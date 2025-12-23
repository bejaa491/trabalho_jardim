# PowerShell test runner
# Remove old outputs
Remove-Item output_snap_tools.txt -ErrorAction SilentlyContinue
Remove-Item output_roseira.txt -ErrorAction SilentlyContinue
Remove-Item output_cantora.txt -ErrorAction SilentlyContinue

# Build
& 'C:\msys64\ucrt64\bin\g++.exe' -fdiagnostics-color=always -g Adubo.cpp Cantora.cpp Cato.cpp Erva.cpp Ferramenta.cpp Interface.cpp Jardim.cpp Jardineiro.cpp main.cpp Planta.cpp Posicao.cpp Pulverizador.cpp Regador.cpp Roseira.cpp Tesoura.cpp -o trabalho_jardim.exe
if ($LASTEXITCODE -ne 0) { Write-Error "Build failed"; exit 1 }

# Run tests
cmd /c ".\trabalho_jardim.exe < test_snap_tools.txt > output_snap_tools.txt"
cmd /c ".\trabalho_jardim.exe < test_roseira_death.txt > output_roseira.txt"
cmd /c ".\trabalho_jardim.exe < test_cantora.txt > output_cantora.txt"

Write-Host "Tests finished. Output files: output_snap_tools.txt, output_roseira.txt, output_cantora.txt"