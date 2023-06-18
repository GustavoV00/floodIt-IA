# Especificação:

O seu programa deve receber uma instância do jogo a partir da entrada
padrão do sistema.

Uma instância é dada por um arquivo texto no seguinte formato:

- a primeira linha do arquivo tem 3 números inteiros n, m e k,
  separados por espaço, onde n é o número de linhas do tabuleiro, m
  é o número de colunas do tabuleiro e k é o número de cores
  presentes no tabuleiro;

- o restante do arquivo contém n linhas com m números inteiros cada,
  separados por espaços, sendo que cada um destes valores pertence
  ao intervalo [1..k];

- o exemplo abaixo é uma instância do jogo com 4 linhas, 5 colunas e
  3 cores:

  4 5 3 <br>
  2 3 2 3 2 <br>
  2 1 2 3 3 <br>
  3 1 2 3 2 <br>
  1 2 2 1 3 <br>

A saída do seu programa deve ser pela saída padrão do sistema e deve
conter duas linhas de texto:

- a primeira linha deve conter um número inteiro que indica o
  tamanho da sequencia de ações da segunda linha;

- a segunda linha deve conter uma sequência de ações separadas por
  espaço e terminada por uma quebra de linha. Cada ação é dada por
  uma letra seguida um número inteiro, separados por espaço. A
  letra, no intervalo [a..d], indica a região correspondente a qual
  canto do tabulerio que terá sua cor alterada. A letra "a" indica o
  canto superior esquerdo, "b" o canto superior direito, "c" o canto
  inferior direito e "d" o canto inferior esquerdo. Os números
  inteiros pertencentes ao intervalo [1..k] indicam a cor que será
  usada para pintar a região que contém o canto do tabuleiro
  indicado pela letra.

Esta sequência de ações representa as cores que devem ser usadas para
pintar o tabuleiro com uma única cor. A operação de pintura muda a cor
da região que contém a célula do canto indicado no tabuleiro.

Por exemplo, considere a seguinte sequência de cores, para o tabuleiro
dado como exemplo:

6 <br>
a 3 d 2 b 3 b 2 b 1 d 3 <br>

Ao aplicar a operação de pintura, usando esta sequência de cores, as
seguintes transformações ocorrem no tabuleiro:

Pintar o canto superior esquerdo (a) com a cor 3:

3 3 2 3 2 <br>
3 1 2 3 3 <br>
3 1 2 3 2<br>
1 2 2 1 3 <br>

Pintar o canto inferior esquerdo (d) com a cor 2:

3 3 2 3 2 <br>
3 1 2 3 3 <br>
3 1 2 3 2 <br>
2 2 2 1 3 <br>

Pintar o canto superior direito (b) com a cor 3:

3 3 2 3 3 <br>  
3 1 2 3 3 <br>
3 1 2 3 2 <br>
2 2 2 1 3 <br>

Pintar o canto superior direito (b) com a cor 2:

3 3 2 2 2 <br>
3 1 2 2 2 <br>
3 1 2 2 2 <br>
2 2 2 1 3 <br>

Pintar o canto superior direito (b) com a cor 1:

3 3 1 1 1 <br>
3 1 1 1 1 <br>
3 1 1 1 1 <br>
1 1 1 1 3 <br>

Pintar o canto inferior esquerdo (d) com a cor 3:

3 3 3 3 3 <br>
3 3 3 3 3 <br>
3 3 3 3 3 <br>
3 3 3 3 3 <br>

Note que ao final o tabuleiro tem uma única cor. Portanto, esta
sequência de ações resolve a instância dada como exemplo.

# Detalhes de implementação.

Para Informações de implementação leia: <b><h2>leiame.txt</h2></b>
