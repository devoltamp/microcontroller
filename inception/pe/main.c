/* i'll start tomorrow */
#include <reg51.h>
#include <stdio.h>

void setup();
void control_algo();

float v_ref, v_x, v_feed, error_signal;
float signal_after_ki, integration_out, previous_integration, past_signal_after_ki;

void main(){
    setup();
    while(1){
        main_loop();
    }
}

void setup(){
    EA = 1;
    ET1 = 1;
    ET0 = 1;
    EX0 = 1;
    IT0 = 1;
    TMOD = 0x11;
    TH0 =
    TL0 =
    TH1 =
    TL1 =
    TR0 = 1;
    TR1 = 1;
}

void control_algo(){
    /* // †(1)
    error_signal = v_ref - v_feed;
    PI_out = (kp * error_signal) + (ki * ((previous_integration) + (0.5 * (past_error + error_signal))));
    */

    // es * ki --> ∫
    signal_after_ki = ki * signal_after_ki;
    integration_out = (previous_integration + (0.5 * (past_signal_after_ki + signal_after_ki)));
    past_signal_after_ki = signal_after_ki;
    previous_integration = integration_out;
    /* further equa. pending... */
}

/* notes;
 *
 * †(1)
 * in the PI controller es - error signal -- according to the flow of the es from
 * ki & the integrator - that will lead to two seperate equations for the same
 *
 */
