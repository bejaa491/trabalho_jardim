# Script para executar todos os testes do simulador de jardim
# Uso: .\run_all_tests.ps1

$testDir = $PSScriptRoot
$exePath = Join-Path (Split-Path $testDir) "trabalho_jardim.exe"

if (-not (Test-Path $exePath)) {
    Write-Host "[ERRO] Executável nao encontrado: $exePath" -ForegroundColor Red
    exit 1
}

$tests = @(
    "test_roseira_mult.txt",
    "test_roseira_vizinhos.txt",
    "test_roseira_morte_nutrientes.txt",
    "test_cacto_mult.txt",
    "test_cacto_agua_alta.txt",
    "test_erva_mult.txt",
    "test_erva_morte_60.txt",
    "test_cantora_bonita.txt",
    "test_cantora_morte.txt",
    "test_regador.txt",
    "test_adubo.txt",
    "test_tesoura.txt",
    "test_pulverizador.txt",
    "test_jardineiro_movimento.txt",
    "test_jardineiro_plantacao.txt",
    "test_jardineiro_colheita.txt",
    "test_jardineiro_entrada_saida.txt",
    "test_jardineiro_ferramentas.txt",
    "test_integration_plants.txt",
    "test_integration_full.txt"
)

$passedTests = 0
$failedTests = 0
$failedList = @()

Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "  Executor de Testes - Simulador de Jardim" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""

foreach ($testFile in $tests) {
    $fullPath = Join-Path $testDir $testFile
    
    if (-not (Test-Path $fullPath)) {
        Write-Host "[SKIP] $testFile - arquivo nao encontrado" -ForegroundColor Yellow
        continue
    }
    
    Write-Host "[TEST] $testFile" -ForegroundColor Cyan -NoNewline
    
    try {
        $output = Get-Content $fullPath | & $exePath 2>&1
        
        if ($LASTEXITCODE -eq 0 -and $output -notmatch "Erro fatal") {
            Write-Host " ... OK" -ForegroundColor Green
            $passedTests++
        } else {
            Write-Host " ... FALHOU" -ForegroundColor Red
            $failedTests++
            $failedList += $testFile
        }
    } catch {
        Write-Host " ... ERRO" -ForegroundColor Red
        $failedTests++
        $failedList += $testFile
    }
}

Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "  RESUMO" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Testes Passados: $passedTests" -ForegroundColor Green
Write-Host "Testes Falhados: $failedTests" -ForegroundColor Red
Write-Host "Total: $($passedTests + $failedTests)" -ForegroundColor Cyan
Write-Host ""

if ($failedTests -gt 0) {
    Write-Host "Testes Falhados:" -ForegroundColor Red
    foreach ($test in $failedList) {
        Write-Host "  - $test" -ForegroundColor Red
    }
    exit 1
} else {
    Write-Host "Todos os testes passaram!" -ForegroundColor Green
    exit 0
}
