#include "Cantora.h"
#include "Posicao.h"

Cantora::Cantora()
    : Planta(Settings::Cantora::inicial_agua,
             Settings::Cantora::inicial_nutrientes,
             Beleza::BONITA),
      instantesAoLadoDeBonita(0) {}

Cantora::~Cantora() {}

void Cantora::simular(int& aguaSolo, int& nutrientesSolo) {
    // Absorção simples de recursos
    int aguaAbsorvida = (aguaSolo >= Settings::Cantora::absorcao_agua)
                        ? Settings::Cantora::absorcao_agua : aguaSolo;
    int nutrientesAbsorvidos = (nutrientesSolo >= Settings::Cantora::absorcao_nutrientes)
                               ? Settings::Cantora::absorcao_nutrientes : nutrientesSolo;
    
    aguaAcumulada += aguaAbsorvida;
    nutrientesAcumulados += nutrientesAbsorvidos;
    aguaSolo -= aguaAbsorvida;
    nutrientesSolo -= nutrientesAbsorvidos;
    
    totalAguaAbsorvida += aguaAbsorvida;
    totalNutrientesAbsorvidos += nutrientesAbsorvidos;
}

bool Cantora::deveMorrer() const {
    // Morre se o solo ficar com menos de 10 unidades de água
    // Esta verificação será feita no Jardim antes de chamar simular
    return false; // A verificação real é feita externamente
}

Planta* Cantora::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    // Multiplica-se se estiver ao lado de planta bonita por 5 instantes
    if (instantesAoLadoDeBonita >= Settings::Cantora::multiplica_instantes) {
        Cantora* novaCantora = new Cantora();
        instantesAoLadoDeBonita = 0;
        return novaCantora;
    }
    return nullptr;
}

char Cantora::getCaracter() const {
    return 'x';
}

std::string Cantora::getTipo() const {
    return "Cantora";
}

void Cantora::cantar(Posicao** area, int linha, int coluna, int maxLinhas, int maxColunas) {
    // Regenera +5 água e +5 nutrientes para plantas bonitas num raio de 2
    for (int i = linha - Settings::Cantora::raio_canto; i <= linha + Settings::Cantora::raio_canto; i++) {
        for (int j = coluna - Settings::Cantora::raio_canto; j <= coluna + Settings::Cantora::raio_canto; j++) {
            if (i >= 0 && i < maxLinhas && j >= 0 && j < maxColunas) {
                if (i == linha && j == coluna) continue; // Pula a própria planta
                
                Planta* p = area[i][j].getPlanta();
                if (p != nullptr && p->getBeleza() == Beleza::BONITA) {
                    p->setAgua(p->getAgua() + Settings::Cantora::regeneracao_agua);
                    p->setNutrientes(p->getNutrientes() + Settings::Cantora::regeneracao_nutrientes);
                }
            }
        }
    }
}

bool Cantora::temPlantaBonitaVizinha(Posicao** area, int linha, int coluna, 
                                      int maxLinhas, int maxColunas) {
    // Verifica vizinhos diretos (4 direções)
    int direcoes[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for (int i = 0; i < 4; i++) {
        int novaLinha = linha + direcoes[i][0];
        int novaColuna = coluna + direcoes[i][1];
        
        if (novaLinha >= 0 && novaLinha < maxLinhas && 
            novaColuna >= 0 && novaColuna < maxColunas) {
            
            Planta* p = area[novaLinha][novaColuna].getPlanta();
            if (p != nullptr && p->getBeleza() == Beleza::BONITA) {
                return true;
            }
        }
    }
    return false;
}

void Cantora::incrementarContadorBonita() {
    instantesAoLadoDeBonita++;
}