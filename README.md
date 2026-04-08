# ♜ Chess in C - Xadrez no Terminal

[![Linguagem](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-green.svg)](LICENSE)
[![Plataforma](https://img.shields.io/badge/Plataforma-Cross--platform-blue)]()

Um jogo de xadrez completo implementado em C puro, rodando inteiramente no terminal com interface ASCII. Perfeito para aprender conceitos de programação, algoritmos de jogos e regras do xadrez.

![Tabuleiro do jogo](https://i.imgur.com/placeholder.png)

## ✨ Características

- 🎮 **Interface gráfica no terminal** - Tabuleiro desenhado com caracteres ASCII
- ♟️ **Todas as peças implementadas** - Rei, Rainha, Torre, Bispo, Cavalo e Peão
- ✅ **Validação completa de movimentos** - Respeita todas as regras do xadrez
- 🛡️ **Sistema de xeque** - Impede movimentos que deixariam o próprio rei em xeque
- 🔄 **Alternância de turnos** - Sistema de jogadas entre Brancas e Pretas
- 🎯 **Movimentos especiais** - Primeiro movimento do peão (duas casas) e captura diagonal
- 🧹 **Limpeza automática da tela** - Interface limpa a cada jogada

## 🚀 Como Executar

### Pré-requisitos

- Compilador GCC (ou qualquer compilador C)
- Terminal com suporte a ANSI (Linux/Mac) ou CMD/PowerShell (Windows)
###
Aqui está o README atualizado com as informações que você forneceu, organizadas de forma clara e profissional:

```markdown
# ♜ Chess in C - Xadrez no Terminal

[![Linguagem](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Licença](https://img.shields.io/badge/Licen%C3%A7a-MIT-green.svg)](LICENSE)
[![Plataforma](https://img.shields.io/badge/Plataforma-Cross--platform-blue)]()

Um jogo de xadrez completo implementado em C puro, rodando inteiramente no terminal com interface ASCII. Perfeito para aprender conceitos de programação, algoritmos de jogos e regras do xadrez.

## 🎮 Como Jogar

### Comandos Básicos

| Comando | Descrição |
|---------|-----------|
| `e2 e4` | Move a peça da posição e2 para e4 |
| `sair`  | Encerra o jogo |

### Sistema de Coordenadas

O tabuleiro usa o sistema padrão do xadrez:
- **Colunas**: letras de 'a' a 'h' (da esquerda para direita)
- **Linhas**: números de 1 a 8 (de baixo para cima)

```
  +---+---+---+---+---+---+---+---+
8 | r | n | b | q | k | b | n | r |
  +---+---+---+---+---+---+---+---+
7 | p | p | p | p | p | p | p | p |
  +---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
2 | P | P | P | P | P | P | P | P |
  +---+---+---+---+---+---+---+---+
1 | R | N | B | Q | K | B | N | R |
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h
```

### Legenda das Peças

| Peça   | Branca | Preta |
|--------|--------|-------|
| Rei    | K      | k     |
| Rainha | Q      | q     |
| Torre  | R      | r     |
| Bispo  | B      | b     |
| Cavalo | N      | n     |
| Peão   | P      | p     |

## 🧠 Regras Implementadas

### Peças

#### ♙ Peão
- Move uma casa para frente
- Primeiro movimento pode mover duas casas
- Captura na diagonal
- ⚠️ *Promoção ainda não implementada*

#### ♜ Torre
- Move qualquer número de casas na horizontal ou vertical
- Não pode saltar sobre peças

#### ♞ Cavalo
- Move em "L" (2 casas + 1 casa)
- Pode saltar sobre peças

#### ♝ Bispo
- Move qualquer número de casas na diagonal
- Permanece na mesma cor do tabuleiro

#### ♛ Rainha
- Combina movimentos da Torre e do Bispo

#### ♚ Rei
- Move uma casa em qualquer direção
- ⚠️ *Roque ainda não implementado*

### Regras Especiais

| Regra | Status |
|-------|--------|
| ✅ Xeque | Impede movimentos que deixem o rei vulnerável |
| ⚠️ Xeque-mate | Ainda não detectado automaticamente |
| ⚠️ Ro

### Compilação

```bash
# Clone o repositório
git clone https://github.com/seu-usuario/chess-in-c.git

# Entre no diretório
cd chess-in-c

# Compile o jogo
gcc xadrez.c -o xadrez

# Execute
./xadrez     # Linux/Mac
xadrez.exe   # Windows

