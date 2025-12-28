#include "Roseira.h"
#include "Jardim.h"

Roseira::Roseira() 
    : Planta(Settings::Roseira::inicial_agua, 
             Settings::Roseira::inicial_nutrientes, 
             Beleza::BONITA),
      jardimPtr(nullptr) {}

Roseira::~Roseira() {}

void Roseira::simular(int& aguaSolo, int& nutrientesSolo) {
    removerAgua(Settings::Roseira::perda_agua);
    removerNutrientes(Settings::Roseira::perda_nutrientes);
    
    int aguaAbsorvida = (aguaSolo >= Settings::Roseira::absorcao_agua) 
                        ? Settings::Roseira::absorcao_agua : aguaSolo;
    int nutrientesAbsorvidos = (nutrientesSolo >= Settings::Roseira::absorcao_nutrientes)
                               ? Settings::Roseira::absorcao_nutrientes : nutrientesSolo;
    
    adicionarAgua(aguaAbsorvida);
    adicionarNutrientes(nutrientesAbsorvidos);
    aguaSolo -= aguaAbsorvida;
    nutrientesSolo -= nutrientesAbsorvidos;
    
    adicionarTotalAgua(aguaAbsorvida);
    adicionarTotalNutrientes(nutrientesAbsorvidos);
}

bool Roseira::deveMorrer() const {
    return getAgua() < Settings::Roseira::morre_agua_menor ||
           getNutrientes() < Settings::Roseira::morre_nutrientes_menor ||
           getNutrientes() > Settings::Roseira::morre_nutrientes_maior;
}

Planta* Roseira::tentatMultiplicar(int& aguaSolo, int& nutrientesSolo) {
    if (getNutrientes() > Settings::Roseira::multiplica_nutrientes_maior) {
        Roseira* novaRoseira = new Roseira();
        
        novaRoseira->setNutrientes(Settings::Roseira::nova_nutrientes);
        novaRoseira->setAgua(getAgua() * Settings::Roseira::nova_agua_percentagem / 100);
        
        setNutrientes(Settings::Roseira::original_nutrientes);
        setAgua(getAgua() * Settings::Roseira::original_agua_percentagem / 100);
        
        return novaRoseira;
    }
    return nullptr;
}

char Roseira::getCaracter() const { return 'r'; }
std::string Roseira::getTipo() const { return "Roseira"; }

Planta* Roseira::clone() const {
    Roseira* r = new Roseira();
    r->setAgua(getAgua());
    r->setNutrientes(getNutrientes());
    for (int k = 0; k < getIdade(); ++k) r->incrementaIdade();
    r->setTotalNutrientes(getTotalNutrientes());
    r->setTotalAgua(getTotalAgua());
    r->setPosicao(getLinha(), getColuna());
    // nota: jardimPtr será configurado pelo jardim que estiver a usar a cópia
    return r;
} 

// Adicionados: comportamento ao morrer e utilitários

void Roseira::deixarRecursosNoSolo(int& aguaSolo, int& nutrientesSolo) {
    // Devolve para o solo os recursos totais absorvidos durante a vida
    aguaSolo += getTotalAgua();
    nutrientesSolo += getTotalNutrientes();
    if (aguaSolo < 0) aguaSolo = 0;
    if (nutrientesSolo < 0) nutrientesSolo = 0;
} 

bool Roseira::todasVizinhasOcupadas() const {
    if (jardimPtr == nullptr) return false;
    Jardim* j = static_cast<Jardim*>(jardimPtr);

    int linha = getLinha();
    int coluna = getColuna();
    int direcoes[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for (int d = 0; d < 4; ++d) {
        int nl = linha + direcoes[d][0];
        int nc = coluna + direcoes[d][1];
        if (j->posicaoValida(nl, nc)) {
            const Posicao* pos = j->getPosicao(nl, nc);
            if (!pos->temPlanta()) return false;
        } else {
            // Se posição inválida, consideramos ocupada (bordas contam como ocupadas)
            continue;
        }
    }
    return true;
}

void Roseira::setJardimPtr(void* jardim) {
    jardimPtr = jardim;
}