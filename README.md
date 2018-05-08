# Breakout por Caio Godoy 
_Por Caio Godoy at caioafgod@gmail.com_

Esse arquivo serve como uma pequena documentação com as informações de uso e decisões de implementação do trabalho, bem como uma lista com as principais funcionalidades do jogo.

## Controles
- Mouse: movimenta Paddle
- S: começa o nivel
- W: pausa o jogo (originalmente botão esquerdo do mouse)
- R: reinicia o jogo para a primeira fase
- Q: encerra o programa
- A e D: movimentação alternativa do paddle (apenas para noobs como eu)

## Lista de funcionalidades do jogo

1. A tecla Q, pressionada em qualquer momento, termina o programa.

2. O jogo deve sempre começa no modo pausa, com a “bola” e o “paddle” parados no centro da tela. A tecla R é usada para voltar o jogo para essa configuração inicial a qualquer momento.

3. O jogo tem uma função Pausa (tecla P) que para o jogo durante qualquer momento. Apertar o pause em retoma o jogo com as mesmas propriedades de antes do pause (velocidade e direção do movimento da bola e do paddle).

4. O botão da direita imprime os atributos de todos os objetos, e coloca o jogo em modo pausa. Deve listar o “paddle” com sua posição e velocidade,  a “bola”, e todos os “tijolos”. Pressionado novamente, executa um ciclo do jogo, e novamente imprime todos os atributos.

5. Velocidade progressiva da bola. Cada rebatida aumenta a velocidade da bola em um fator pequeno.

6. 3 niveis de dificuldade. O nivel 2 diminui o tamanho do paddle e o nivel 3 aumenta a velocidade inicial da bola sem voltar o paddle para o tamanho normal, o que faz com o que o nivel seja muito dificil.

7. O paddle muda a direção da bola dependendo de onde a bola bater. Se ela bate nos cantos ela é mandada para o sentido do canto, independente de como ela está vindo, mas se ela bate no meio do paddle ela continua na trajetoria normal.

## Melhorias após a apresentação:

1. O paddle agora se movimenta como deveria pela especificação, ele tem uma velocidade V que aumenta gradualmente baseada na distancia do centro. Se ele estiver dentro de uma area central ele fica com V = 0.

2. A coloração dos blocos agora usa interpolação (vertices possuem cores diferentes)

## Especificação e Implementação

_Wokring on it_

## Maneiras de executar o projeto:

#### Usando Makefile:
```
make run
```
#### Apagando arquivos depois de executar
```
make clean
```

### Pelo terminal:
```
gcc -framework OpenGL -framework GLUT main.cpp -o brickbreak -Wno-deprecated
./brickbreak
```
