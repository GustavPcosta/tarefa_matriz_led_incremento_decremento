Projeto de Incremento e Decremento com BitDogLab
Este projeto foi desenvolvido utilizando a placa BitDogLab e tem como objetivo realizar o incremento e decremento de números exibidos em uma matriz de LEDs 5x5. O controle é feito através de dois botões (A e B), e a interface de LEDs inclui conexões RGB para exibir a cor do número, com destaque para o LED vermelho piscando continuamente.

Funcionalidades
Incremento e Decremento dos Números:

Através dos botões A (incrementa) e B (decrementa), o número exibido na matriz de LEDs aumenta ou diminui.
O número exibido pode variar de 0 a 9 e é representado na matriz de LEDs de 5x5.
Matriz de LEDs 5x5:

A matriz de LEDs exibe números de 0 a 9, cada um representado por um padrão de LEDs acesos ou apagados.
Cada número é representado utilizando os LEDs da matriz para formar o padrão correto.
LED RGB:

Um LED RGB (Vermelho, Verde, Azul) é utilizado para indicar a operação realizada.
O LED vermelho pisca continuamente com uma frequência de 5 vezes por segundo para sinalizar a atividade do sistema.
Debouncing dos Botões:

O sistema implementa um mecanismo de debouncing para garantir que os botões não sejam acionados múltiplas vezes por um único clique.
Hardware Utilizado
Placa BitDogLab
Esta placa de desenvolvimento foi utilizada para implementar o código em C, com controle dos LEDs WS2812, botões e LEDs RGB.
Matriz de LEDs 5x5 para exibição dos números.
LEDs RGB (Vermelho, Verde, Azul) para indicar o estado e atividades do sistema.
Botões A e B para controle de incremento e decremento do número exibido.
Código
O código foi implementado em C e utiliza a extensão da Raspberry Pi Pico para controlar os pinos GPIO e os LEDs. As principais funções do código incluem:

Incremento/Decremento de número:

Utilizando interrupções nos botões A e B.
Exibição de números na matriz de LEDs 5x5:

Os números são exibidos por meio de LEDs acesos, com padrões definidos para os números de 0 a 9.
Piscar LED vermelho:

O LED vermelho pisca continuamente 5 vezes por segundo para sinalizar o funcionamento do sistema.
Principais Funções
gpio_irq_handler: Função de interrupção para os botões A e B, responsável pelo incremento e decremento do número.
display_number: Exibe o número atual na matriz de LEDs.
put_pixel: Envia um valor para os LEDs WS2812.
urgb_u32: Converte valores RGB para o formato GRB (necessário para controle de LEDs WS2812).
Instruções de Uso
Conecte a placa BitDogLab ao computador.

Clone do repositório:   https://github.com/GustavPcosta/tarefa_matriz_led_incremento_decremento.git HTTP
                        git@github.com:GustavPcosta/tarefa_matriz_led_incremento_decremento.git SSH


Compile o código no ambiente de desenvolvimento de sua escolha.
Carregue o código na placa BitDogLab.
Pressione o botão A para incrementar o número exibido na matriz de LEDs.
Pressione o botão B para decrementar o número exibido.
Observe o LED vermelho piscando continuamente como sinal de que o sistema está ativo



Link do vídeo
https://www.canva.com/design/DAGdf44ya28/BBJolM4VGM-9hgJ9MmTXNA/watch?utm_content=DAGdf44ya28&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=hc85af70590


OBSERVAÇÕES:
Ocorreram eventuais erros durante a produção do projeto, tendo em vista esses erros, acabei colocando os nomes dos meus arquivos .c com nomes curtos para melhor visualização


