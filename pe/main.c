#include <reg51.h>

void initialize_peripheral(void);
void control_algorithm(void);

float V_ref;
float V_feed;
float error_signal;
float kp = 1.0;
float ki = 0.1;
float signal_after_ki;
float past_signal_after_ki;
float int_out;
float pre_int_out;
float pi_out;
float frac_duty;

sbit pwm = P1^0;

void main(void)
{
    initialize_peripheral();

    while (1)
    {
        control_algorithm();
    }
}

void initialize_peripheral(void)
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;
    ET0 = 1;
    ET1 = 1;

    TH0 = 0xE2; // 226 = 256 - (0.3 * 100)
    TL0 = 0xE2;

    TH1 = 0x9C; // 156
    TL1 = 0x9C;

    TMOD = 0x22; // 8-bit auto-reload for Timer 0 & Timer 1
}

void control_algorithm(void)
{
    error_signal = V_ref - V_feed;
    signal_after_ki = ki * error_signal;

    int_out = pre_int_out + 0.5 * (ki * (past_signal_after_ki + signal_after_ki));
    past_signal_after_ki = signal_after_ki;
    pre_int_out = int_out;

    pi_out = (kp * error_signal) + int_out;
    frac_duty = (pi_out + 468.0) / 936.0;
}

void timer1_isr(void) interrupt 3
{
    pwm = 1;
    TH1 = 0x9C; // 256 - 100 (counts) = 156
    TL1 = 0x9C;
}
