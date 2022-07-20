void unidade(unsigned short unidade);                                           // declarando a função da unidade
void dezena(unsigned short dezena);                                             // declarando a função da dezena
unsigned short contador = 0x00;                                                 // variavel para contar os digitos
unsigned short memoria;                                                         // variavel para armazenar dados da memoria
unsigned short digito;                                                          // variavel que lera a memoria e informara o digito
unsigned short cont = 0x01;                                                     // variavel auxiliar para inicialização do digito

// --- função de interrupção --- ///
void interrupt(){

     if(T0IF_bit){                                                              // houve o estouro do TMR0?
         T0IF_bit = 0x00;                                                       // reseta a flag do estouro do TMR0
         if(cont){                                                              // se cont entao...
            memoria = EEPROM_Read(0x00);                                        // memoria le eeprom
            delay_ms(10);                                                       // delay necessario para ler eeprom
            digito = memoria;                                                   // digito recebe o valor da memoria
            delay_ms(10);                                                       // delay necessario para armazenar
            cont = 0x00;                                                        // zera a variavel auxiliar de inicialização
         }
         if(!RA4_bit && contador > 3 && abs(memoria - contador) > 3){         // se RA4 desligado contador maior que 3 e diferença entre memoria e contador maior que 3 segundos
             EEPROM_Write(0x00, contador);                                      // entao grava na eeprom o valor de contador
             delay_ms(20);                                                      // delay necessario para gravar na eeprom
             cont = 0x01;                                                       // reinicia varivel auxiliar
             contador = 0x00;
         }

     }
}
// -- função principal -- //
void main() {
     CMCON = 0x07;                                                              // desabilita os comparadores do PIC
     TRISA = 0x30;                                                              // apenas RA4 e RA5 como entrada
     PORTA = 0x10;                                                              // inicia apenas RA4 em high
     TRISB = 0x00;                                                              // faz todas as portas B serem saidas
     PORTB = 0x00;                                                              // faz com que todos os pinos iniciem em low
     GIE_bit = 0x01;                                                            // habilita a interupção global
     PEIE_bit = 0x01;                                                           // habilita a interrupção por perifericos
     T0IE_bit = 0x01;                                                           // habilita a interupção por estouro do TMR0
     OPTION_REG = 0x87;                                                         // prescaler (1: 256) associado ao TMR0 - estouro a cada
     while(1){                                                                  // inicia o sistema
           while(!cont){                                                        // enquanto nao tiver a variavel auxiliar inicial
               if(digito >= 99){                                                // caso digito for maior que 99 segundos
                     unidade(9);                                                // liga unidade no digito 9
                     dezena(9);                                                 // liga dezena no digito 9
                     delay_ms(990);                                             // tempo de 1 segundo
                     contador++;                                                // incrementa contador
                     digito--;                                                  // decrementa digito


               } else if(digito >=1){                                           // caso digito inferior 99 segundos e meior do que 1
                     unidade(digito%10);                                        // manda o valor do digito na unidade
                     dezena((digito/10)-(digito%10/10));                        // manda o valor do digito na dezena
                     delay_ms(990);                                             // delay de 1 segundo
                     contador++;
                     digito--;


               }else{                                                           // caso digito inferior a 1
                     PORTB.RB0 = 0x01;                                          //
                     PORTB.RB1 = 0x01;                                          //
                     PORTB.RB2 = 0x01;                                          //
                     PORTB.RB3 = 0x01;                                          //
                     PORTB.RB4 = 0x01;                                          //
                     PORTB.RB5 = 0x01;                                          //
                     PORTB.RB6 = 0x00;                                          //
                     PORTA.RA0 = 0x01;                                          //
                     PORTA.RA1 = 0x01;                                          //
                     PORTA.RA2 = 0x01;                                          //
                     PORTA.RA3 = 0x01;                                          //
                     PORTA.RA6 = 0x01;                                          //
                     PORTA.RA7 = 0x01;                                          //
                     PORTB.RB7 = 0x00;                                          //
                     delay_ms(1000);                                             // liga o segmento G da dezena e da unidade por 500ms
                     contador++;                                                // incrementa contador
               }
           }
     } // fim while


} // fim do main

void unidade(unsigned short unidade){                                           //função para ligar os segmentos da unidade
       switch(unidade){
            case 0:                                                             // caso unidade seja igual a 0

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x01;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x00;
               break;

            case 1:                                                             // caso unidade seja igual a 1

               PORTB.RB0 = 0x00;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x00;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x00;
               PORTB.RB6 = 0x00;
               break;

            case 2:                                                             // caso unidade seja igual a 2

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x00;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x01;
               PORTB.RB5 = 0x00;
               PORTB.RB6 = 0x01;
               break;

            case 3:                                                             // caso unidade seja igual a 3

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x00;
               PORTB.RB6 = 0x01;
               break;

            case 4:                                                             // caso unidade seja igual a 4

               PORTB.RB0 = 0x00;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x00;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x01;
               break;

            case 5:                                                             // caso unidade seja igual a 5

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x00;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x01;
               break;

            case 6:                                                             // caso unidade seja igual a 6

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x00;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x01;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x01;
               break;

            case 7:                                                             // caso unidade seja igual a 7

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x00;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x00;
               PORTB.RB6 = 0x00;
               break;

            case 8:                                                             // caso unidade seja igual a 8

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x01;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x01;
               break;

            case 9:                                                             // caso unidade seja igual a 9

               PORTB.RB0 = 0x01;
               PORTB.RB1 = 0x01;
               PORTB.RB2 = 0x01;
               PORTB.RB3 = 0x01;
               PORTB.RB4 = 0x00;
               PORTB.RB5 = 0x01;
               PORTB.RB6 = 0x01;
               break;
       } // fim do switch da unidade
}

void dezena(unsigned short dezena){                                             // função para ligar os segmentos das dezenas

     switch(dezena){
           case 0:                                                              // caso dezena seja igual a 0
                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x01;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x00;
                break;

           case 1:                                                              // caso dezena seja igual a 1

                PORTA.RA0 = 0x00;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x00;
                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x00;
                PORTB.RB7 = 0x00;
                break;

           case 2:                                                              // caso dezena seja igual a 2

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x00;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x01;
                PORTA.RA7 = 0x00;
                PORTB.RB7 = 0x01;
                break;

           case 3:                                                              // caso dezena seja igual a 3

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;

                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x00;
                PORTB.RB7 = 0x01;
                break;

           case 4:                                                              // caso dezena seja igual a 4

                PORTA.RA0 = 0x00;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x00;
                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x01;
                break;

           case 5:                                                              // caso dezena seja igual a 5

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x00;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x01;
                break;

           case 6:                                                              // caso dezena seja igual a 6

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x00;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x01;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x01;
                break;

           case 7:                                                              // caso dezena seja igual a 7

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x00;
                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x00;
                PORTB.RB7 = 0x00;
                break;

           case 8:                                                              // caso dezena seja igual a 8

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x01;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x01;
                break;

           case 9:                                                              // caso dezena seja igual a 9

                PORTA.RA0 = 0x01;
                PORTA.RA1 = 0x01;
                PORTA.RA2 = 0x01;
                PORTA.RA3 = 0x01;
                PORTA.RA6 = 0x00;
                PORTA.RA7 = 0x01;
                PORTB.RB7 = 0x01;
                break;
     }

}
