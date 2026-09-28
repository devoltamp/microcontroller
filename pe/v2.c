/* v2 -- almost full implemented code for pe/main.c */
#include <reg51.h>

void setup(void);
void main_loop(void);
void control_algo(void);
void read_adc_inputs(void);
void update_pwm_output(void);

/* control gains */
#define KP 2.5f
#define KI 0.8f

/* output limits -- 0% to 100% PWM duty cycle */
#define PI_OUT_MIN 0.0f
#define PI_OUT_MAX 100.0f

/* sys. variables */
float v_ref = 2.5f;             /* wanted 2.5v */
float v_feed = 0.0f;
float error_signal = 0.0f;
float pi_out = 0.0f;

float signal_after_ki = 0.0f;
float past_signal_after_ki = 0.0f;
float integration_out = 0.0f;
float previous_integration = 0.0f;

volatile bit sample_flag = 0;


void timer0_isr(void) interrupt 1 {
    TH0 = 0xD8;
    TL0 = 0xF0;
    sample_flag = 1;        /* to execute control algorithm */
}

/* PWM -- generator */
void timer1_isr(void) interrupt 3 {
    TH1 = 0xFF;
    TL1 = 0x00;
}

/* emergency stop/reset */
void external0_isr(void) interrupt 0 {
    integration_out = 0.0f;
    previous_integration = 0.0f;
    past_signal_after_ki = 0.0f;
    pi_out = 0.0f;
}


void main(void) {
    setup();
    while (1) {
        main_loop();
    }
}


void setup(void) {
    EA = 1;
    ET0 = 1;
    ET1 = 1;
    EX0 = 1;        /* enable external interrupt 0*/
    IT0 = 1;

    TMOD = 0x11; // Timer 0: 16-bit mode (Mode 1), Timer 1: 16-bit mode (Mode 1)

    /* for 10ms -- load the val. */
    TH0 = 0xD8;
    TL0 = 0xF0;

    /* with initial values */
    TH1 = 0xFF;
    TL1 = 0x00;

    /* start timer 0 & 1 */
    TR0 = 1;
    TR1 = 1;
}


/* †(1) */
void main_loop(void) {
    if (sample_flag) {
        sample_flag = 0;        /* reset the flag */

        read_adc_inputs();
        control_algo();
        update_pwm_output();
    }
}


void control_algo(void) {
    float proportional_part;

    /* error */
    error_signal = v_ref - v_feed;

    /* P - term */
    proportional_part = KP * error_signal;

    /* I - term */
    signal_after_ki = KI * error_signal;
    integration_out = previous_integration + (0.5f * (past_signal_after_ki + signal_after_ki));

    /* limitter */
    if (integration_out > PI_OUT_MAX) {
        integration_out = PI_OUT_MAX;
    }
    else if (integration_out < PI_OUT_MIN) {
        integration_out = PI_OUT_MIN;
    }

    /* total PI out */
    pi_out = proportional_part + integration_out;

    /* overall output clamping */
    if (pi_out > PI_OUT_MAX) {
        pi_out = PI_OUT_MAX;
    }
    else if (pi_out < PI_OUT_MIN) {
        pi_out = PI_OUT_MIN;
    }

    /* update all the variables for next */
    past_signal_after_ki = signal_after_ki;
    previous_integration = integration_out;
}

/* †(2) */
void read_adc_inputs(void) {
    unsigned char adc_raw = P2;
    v_feed = ((float)adc_raw / 255.0f) * 5.0f;
}

/* †(3) */
void update_pwm_output(void) {
    ;
}


/* notes;
 *
 * †(1)
 * 1. read current feedback (v_feed)
 * 2. calculate PI control response
 * 3. write control signal to hardware driver
 *
 * †(2)
 * insert your ADC reading logic -- ADC0809 read on port 2,
 * convert 8-bit digital value (0-255) to voltage float (0.0V - 5.0V)
 *
 * †(3) -- idk
 * map pi_out (0.0 to 100.0) to hardware control or Timer 1 compare value,
 * duty_cycle = (unsigned char)((pi_out / 100.0f) * 255.0f);
 *
 */
