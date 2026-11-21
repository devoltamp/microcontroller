/* keypad Controlled PWM Generator */
#include <reg51.h>

sbit PWM = P3^0;            /* PWM output pin */

/* Matrix keypad on Port 1: P1.0..P1.3 = Rows, P1.4..P1.7 = Columns */
sfr KEYPAD_PORT = 0x90;     /* Port 1 SFR address (0x90)[cite: 33] */

volatile bit now_scan = 0;      /* Set every 50 ms by Timer 1 ISR[cite: 33, 35] */
volatile bit pwm_enabled = 0;   /* 1 = PWM active, 0 = stopped/withdrawn */
volatile bit on_off_flag = 0;   /* 0 = next phase is ON, 1 = next phase is OFF */

volatile unsigned char on_time_h  = 0xFF;
volatile unsigned char on_time_l  = 0xCE;
volatile unsigned char off_time_h = 0xFC;
volatile unsigned char off_time_l = 0x2A;

unsigned char sw_no = 0;

void scan_matrix(void);
void set_pwm_duty(unsigned char switch_num);

/* Timer 0 ISR: Alternates ON and OFF intervals for 1000 Hz PWM[cite: 32, 39] */
void tmr0_isr(void) interrupt 1 {
    if (!pwm_enabled) {
        TR0 = 0;
        PWM = 0;
        on_off_flag = 0;
        return;
    }

    if (on_off_flag == 0) {
        PWM = 1;
        TH0 = on_time_h;
        TL0 = on_time_l;
        on_off_flag = 1;
    } else {
        PWM = 0;
        TH0 = off_time_h;
        TL0 = off_time_l;
        on_off_flag = 0;
    }
}

/* Timer 1 ISR: Triggers every 50 ms (0x3CB0) to scan keypad[cite: 32, 34, 35] */
void tmr1_isr(void) interrupt 3 {
    TH1 = 0x3C;
    TL1 = 0xB0;
    now_scan = 1;           /*[cite: 35] */
}

void set_pwm_duty(unsigned char switch_num) {
    unsigned int on_counts;
    unsigned int off_counts;
    unsigned int reload_on;
    unsigned int reload_off;
    unsigned char duty_pct;

    /* Switch 16: stop / withdraw PWM[cite: 32] */
    if (switch_num == 16) {
        pwm_enabled = 0;
        TR0 = 0;
        PWM = 0;
        return;
    }

    /* Switches 1..15 -> 5%, 10%, ..., 75%[cite: 32] */
    if (switch_num >= 1 && switch_num <= 15) {
        duty_pct = switch_num * 5;
        on_counts  = (unsigned int)duty_pct * 10U;      /* 50 to 750 counts[cite: 32, 37] */
        off_counts = 1000U - on_counts;                 /* 950 to 250 counts */

        reload_on  = 65536UL - on_counts;
        reload_off = 65536UL - off_counts;

        EA = 0;
        on_time_h  = (unsigned char)(reload_on >> 8);
        on_time_l  = (unsigned char)(reload_on & 0xFF);
        off_time_h = (unsigned char)(reload_off >> 8);
        off_time_l = (unsigned char)(reload_off & 0xFF);

        if (!pwm_enabled) {
            pwm_enabled = 1;
            on_off_flag = 0;
            PWM = 1;
            TH0 = on_time_h;
            TL0 = on_time_l;
            on_off_flag = 1;
            TR0 = 1;
        }
        EA = 1;
    }
}

void scan_matrix(void) {
    unsigned char row, col;
    unsigned char row_idx = 0xFF, col_idx = 0xFF;

    /* Scan rows (P1.0..P1.3 driven LOW one at a time; P1.4..P1.7 are inputs with pull-ups) */
    for (row = 0; row < 4; row++) {
        KEYPAD_PORT = ~(1 << row);      /* Pull current row LOW, others HIGH */
        col = (KEYPAD_PORT >> 4) & 0x0F;

        if (col != 0x0F) {              /* Active-low key press detected */
            if      ((col & 0x01) == 0) col_idx = 0;
            else if ((col & 0x02) == 0) col_idx = 1;
            else if ((col & 0x04) == 0) col_idx = 2;
            else if ((col & 0x08) == 0) col_idx = 3;

            row_idx = row;
            break;
        }
    }

    KEYPAD_PORT = 0xFF;

    if (row_idx != 0xFF && col_idx != 0xFF) {
        sw_no = (4 * row_idx) + col_idx + 1;    /* Switch number 1..16[cite: 36] */
        set_pwm_duty(sw_no);
    }
}

void main(void) {
    PWM = 0;
    KEYPAD_PORT = 0xFF;

    TMOD = 0x11;        /* Both Timer 0 and Timer 1 in 16-bit Mode 1[cite: 34] */

    /* Load Timer 1 for 50 ms scan period[cite: 32, 34, 35] */
    TH1 = 0x3C;
    TL1 = 0xB0;

    ET0 = 1;            /* Enable Timer 0 interrupt[cite: 34] */
    ET1 = 1;            /* Enable Timer 1 interrupt[cite: 34] */
    EA  = 1;            /* Enable global interrupts[cite: 34] */

    TR1 = 1;            /* Start Timer 1[cite: 35] */

    while (1) {
        if (now_scan) {
            now_scan = 0;
            scan_matrix();
        }
    }
}
