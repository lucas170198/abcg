# Atividade 1 - Computação Gráfica

**Nome** : Lucas Silva Amorim

**RA** : 11201720968

**Link vídeo de apresentação**: https://youtu.be/G9Uhh9ErvT8

## Infinite Cardrive
### Descrição da Aplicação
Para a atividade proposta, foi desenvolvido o jogo 2D "infinite car drive". Neste jogo, o jogador pilota um carro por três vias diferentes, e deve se movimentar para esquerda e direita afim de desviar dos outros veículos.

 A velocidade dos veículos aumenta durante o jogo, aumentando assim a dificuldade. Para cada carro ultrapassado, o jogador ganha *10 pontos*. A pontuação é mostrada quando o jogador colide com outro carro.


 ### Organização do Projeto

```
 examples
 |
 |
 |___cardrive
     |
     |
     |___ assets (contém arquivos de fonte e os códigos de programação dos shadders)
     |
     |
     |
     ____car.(hpp/cpp) (Classe responsável pela renderização do carro controlado pelo jogador)
     |
     |
     |___enemycar(hpp/cpp) (classe responsável pela renderização dos carros que o jogador deve desviar)
     |
     |
     |___gamedata.hpp (Contém dados sobre o estado do jogo)
     |
     |
     |___main.cpp (função principal da aplicação)
     |
     |
     |___openglwindow.(cpp/hpp) (Classe que gerencial a janela principal do jogo)

```


### Lógica de movimentação do carro principal
O carro principal se movimenta apenas no eixo X (são os outros carros que se movem, dando a impressão que o carro está em movimeto). Para movimentar o veículo, a função `OpenGLWindow::HandleInput` chama a função `OpenGLWindow::positionStateMachine` que define qual a posição do carro principal na tela, setando o enum `Position`. A função `Car::update` atualiza o m_translaction do carro de acordo com Position.

### Lógica de movimentação dos outros carros
Os demais carros se movem somente no eixo Y, descendo pela tela em direção ao jogador(que deverá desviar dos carros). Para deslocar estes veículos, a função `EnemyCar::update` decrementa o transaction.y, baseado no nível (quanto maior o nível, mais alto o decremento e portanto maior a velocidade) e no deltaTime (para que os quadros se atualizem sincronizados com a máquina que está executando a aplicação).

Para gerar os carros em posições diferentes, (tanto em X quanto em Y) utiliza-se distribuições aleatórias. Três carros são gerados por vez, e reaparecem no começo da tela depois de percorrer toda a tela.

### Colisão
A função `OpenGLWindow::checkCollisions` é responsável por verificar se o carro controlado com o jogador colidiu com algum outro. Para isso o laço de repetição abaixo checa se a distância dentre os veículos é menor que o raio prédefinido de colisão para cada um dos veículos.
 ```c++
     for(const auto enemyCar : m_enemyCars){
        const auto enemyCarTranslation{enemyCar.m_translation};
        const auto distance{glm::distance(m_mainCar.m_translation, enemyCarTranslation)};

        if(distance < m_mainCar.m_scale * 0.9f + enemyCar.m_scale * 0.85f){
            m_gameData.m_state = State::GameOver;
            m_restartWaitTimer.restart();
        }
    }
 ```