================================================================================
COMPILAÇÃO E TESTES - TRABALHO JARDIM
================================================================================

COMO COMPILAR
================================================================================

Opção 1: Usando CMake (Recomendado)
-----------------------------------
cd c:\Users\rodri\Desktop\faculdade\trabalho_jardim
mkdir -p build
cd build
cmake ..
cmake --build .

Opção 2: Usando G++ Direto
---------------------------
cd c:\Users\rodri\Desktop\faculdade\trabalho_jardim
g++ -g -o trabalho_jardim.exe *.cpp

Opção 3: Usar a Task do VS Code
--------------------------------
No VS Code, pressione Ctrl+Shift+B para executar a build task (G++ build).


COMO CORRER OS TESTES
================================================================================

Executar Todos os Testes
------------------------
cd c:\Users\rodri\Desktop\faculdade\trabalho_jardim\test
.\run_all_tests.ps1

Executar um Teste Específico
----------------------------
cd c:\Users\rodri\Desktop\faculdade\trabalho_jardim\build
./trabalho_jardim.exe < ../test/test_adubo.txt


TESTES DISPONÍVEIS
================================================================================

- test_adubo.txt
  Testa a classe Adubo

- test_regador.txt
  Testa a ferramenta Regador

- test_tesoura.txt
  Testa a ferramenta Tesoura

- test_pulverizador.txt
  Testa o Pulverizador

- test_roseira_mult.txt
  Testa multiplicação de Roseiras

- test_roseira_morte_nutrientes.txt
  Testa morte por nutrientes

- test_roseira_vizinhos.txt
  Testa vizinhos de Roseira

- test_cacto_mult.txt
  Testa multiplicação de Cactos

- test_cacto_agua_alta.txt
  Testa Cacto com água alta

- test_erva_mult.txt
  Testa multiplicação de Erva

- test_erva_morte_60.txt
  Testa morte de Erva

- test_cantora_bonita.txt
  Testa Cantora bela

- test_cantora_morte.txt
  Testa morte de Cantora

- test_jardineiro_movimento.txt
  Testa movimento do Jardineiro

- test_jardineiro_plantacao.txt
  Testa plantação

- test_jardineiro_ferramentas.txt
  Testa ferramentas

- test_jardineiro_colheita.txt
  Testa colheita

- test_jardineiro_entrada_saida.txt
  Testa entrada/saída

- test_integration_plants.txt
  Teste integração com plantas

- test_integration_full.txt
  Teste integração completo


ESTRUTURA DO PROJETO
================================================================================

Ficheiros .h
  Headers das classes

Ficheiros .cpp
  Implementação das classes

main.cpp
  Programa principal com interface

CMakeLists.txt
  Configuração do CMake

test/
  Diretório com testes

cmake-build-debug/
  Build output do CMake


REQUISITOS
================================================================================

- G++ (MinGW/MSYS2)
- CMake (opcional, mas recomendado)
- PowerShell (para o script de testes)
