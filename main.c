#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint motor = 22; //definição de pino
const uint16_t wrap = 50000; //valor máximo do contador - WRAP
const float divisor = 50.0; //divisor do clock para o PWM
const uint16_t passo = 12; //passo de incremento/decremento para o duty cycle do LED
uint16_t atual = 1250; //nível inicial do pwm (duty cycle)
uint16_t minimo = 1250, maximo = 6000; //níveis minimo e maximo de pwm

//-----------------------------------------------------------------------------------------
int main(){
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    gpio_set_function(motor, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(motor); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, divisor); //define o divisor de clock do PWM

    pwm_set_wrap(slice, wrap); //definir o valor de wrap

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente

//-----------------------------------------------------------------------------------------
//  A partir daqui foi utilizada a relação level = (ciclo ativo)*wrap/período
//                                         level = (ciclo ativo)*50000/20000

    pwm_set_gpio_level(motor, 6000); //Coloca o servo a 180º
    sleep_ms(5000);
    pwm_set_gpio_level(motor, 3675); //Coloca o servo a 90º
    sleep_ms(5000);
    pwm_set_gpio_level(motor, 1250); //Coloca o servo a 90º
    sleep_ms(5000);
//-----------------------------------------------------------------------------------------

    while (true) {

        for(atual; atual<maximo; atual+=passo){ //for para o servo realizar o trajeto 0-180º
            pwm_set_gpio_level(motor, atual);
            sleep_ms(10);
        }
        for(atual; atual>minimo; atual-=passo){ //for para o servo realizar o trajeto 180-0º
            pwm_set_gpio_level(motor, atual);
            sleep_ms(10);
        }
    }
}
