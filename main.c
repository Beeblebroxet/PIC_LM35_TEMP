/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1455
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"



void Clear_Watchdog(){
        CLRWDT();
        
}
void read_port(){
    int test;
    test =PORTCbits.RC5;
    __delay_us(100);



}
void write_number_portc(int value){  //Function for writing to PORTC:s outputs for BDC 
    int dont_touch = 0b11110000;
    int temp;
        temp = LATC;
        temp &= dont_touch;
        temp |= value;
        __delay_us(20);
        PORTC = temp; 
}

/*ADC function*/
int voltage_read(int volt){       
    int  Result;
    long T_Vref;
    long Vref=204800;
    
    /*Starts the ADC and waits until done, maybe change to an interrupt routine*/
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE){
        __delay_us(5);
    
    }
    Vref   = (Vref/1023);
    T_Vref = (int)Vref;
    Result = 0;
    Result = ADRESL>>6;
    Result = Result | (ADRESH<<2);
    T_Vref =  (T_Vref  * Result)/100;    // Stimulus does not support FVR, change this to 2048 when program runs in hardware, bits for VFR already set in program
    __delay_us(50);
    volt = T_Vref;

    return volt;


}


                   //      Main application
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    int temp;
    OSCCONbits.IRCF=0b1101110;
    TRISC = 0b00100000;
    PORTC = 0X00;
    
    int i=0 ;
    int volt;
    
    while(1)
    {
        i = 0;

        
        for( i=0; i<=9; i=i+1) {
            write_number_portc(i);
            Clear_Watchdog();
            __delay_ms(500);

            volt = voltage_read(volt);
            read_port();
            
        }
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();


}
}