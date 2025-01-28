#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"//biblioteca gerada para o controle da matriz de led

#define IS_RGBW false
#define NUM_PIXELS 25 // definição da matriz 5x5
#define WS2812_PIN 7 //conexão com gpio 7
#define RGB_RED_PIN 13  //cor vermelha
#define RGB_GREEN_PIN 12//cor verde
#define RGB_BLUE_PIN 11 // cor azul
const uint button_A = 5; //button A
const uint button_B = 6;// button B

#define TEMPO 400

int current_number = 0;
//matriz de leds e os desenhos da numeração
const bool numbers[10][NUM_PIXELS] = {
//Número 0
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},

    // Número 1
    {0, 0, 0, 1, 0,
     0, 0, 1, 0, 0,
     1, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     1, 1, 1, 1, 1},

    //Número 2
     {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},

    // Número 3
    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},

    // // Número 4
    {1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     0, 0, 0, 0, 1},

    // Número 5
    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1},

    // Número 6
    {1, 1, 1, 1, 1,  
    1, 0, 0, 0, 0, 
    1, 1, 1, 1, 1,  
    1, 0, 0, 0, 1,  
    1, 1, 1, 1, 1},

    // Número 7
    {1, 1, 1, 1, 1,
    1, 0, 0, 0, 1,
    0, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 0, 0},


    // Número 8
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},

    // Número 9
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1}



   };
// Prototipação das funções
static void gpio_irq_handler(uint gpio, uint32_t events);
static inline void put_pixel(uint32_t pixel_grb);
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void display_number(int number);

uint32_t last_press_A = 0;
uint32_t last_press_B = 0;

int main()
{
    // Inicialização do sistema e // Configuração dos LEDs WS2812
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

     // Configuração dos botões
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    gpio_init(RGB_RED_PIN);
    gpio_set_dir(RGB_RED_PIN, GPIO_OUT);

    while (true)
    {
        display_number(current_number);  //Exibe o número atual na matriz

        // Piscar o LED vermelho
        gpio_put(RGB_RED_PIN, 1);
        sleep_ms(50);
        gpio_put(RGB_RED_PIN, 0);
        sleep_ms(50);
    }

    return 0;
}
//função relacionada a matriz de leds 
void display_number(int number)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (numbers[number][i])
        {
            put_pixel(urgb_u32(0, 0, 200));
        }
        else
        {
            put_pixel(0);
        }
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    //funções relacionadas ao incremento e decremento
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == button_A && (current_time - last_press_A) > 200)
    {
        last_press_A = current_time;
        current_number = (current_number + 1) % 10;
        printf("Incrementando para: %d\n", current_number);
    }
    else if (gpio == button_B && (current_time - last_press_B) > 200)
    {
        last_press_B = current_time;
        current_number = (current_number - 1 + 10) % 10;
        printf("Decrementando para: %d\n", current_number);
    }
}
// Função para converter RGB para GRB
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}






