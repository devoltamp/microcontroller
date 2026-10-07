#include <stdio.h>
#include <math.h>

#define N 20             /* Total number of samples */
#define T_STEP 0.001f    /* 1 ms sampling period */
#define DAC_SCALE 25.6f  /* Counts per Volt (256 counts / 10V full range or 51.2 / 2V) */

int main(void) {
    int k;
    float t, v_analog, dac_exact;
    int dac_rounded;

    printf("=========================================================================\n");
    printf("| Index (k) | Time (t) | Continuous V(t) | Exact DAC Val | Rounded Val |\n");
    printf("=========================================================================\n");

    /* t = 0.001 * k */
    for (k = 0; k < N; k++) {
        t = k * T_STEP;

        /* Calculate analog voltage V(t) based on half-period boundary */
        if (k <= 10) {
            /* Rising ramp: 0 <= t <= T/2 */
            v_analog = 100.0f * t;
        } else {
            /* Falling ramp: T/2 < t <= T */
            v_analog = 2.0f - (100.0f * t);
        }

        /* Continuous DAC scaled value */
        dac_exact = v_analog * DAC_SCALE;

        /* Discrete rounded value for 8-bit output */
        dac_rounded = (int)roundf(dac_exact);

        printf("|    %2d     |  %0.3fs  |     %0.3f V    |    %7.3f    |     %2d      |\n",
               k, t, v_analog, dac_exact, dac_rounded);
    }

    printf("=========================================================================\n");

    /* Print ready-to-use C array for 8051 code */
    printf("\nlookup table array: \n");
    printf("code unsigned char signal[%d] = {\n    ", N);
    for (k = 0; k < N; k++) {
        if (k <= 10) {
            v_analog = 100.0f * (k * T_STEP);
        } else {
            v_analog = 2.0f - (100.0f * (k * T_STEP));
        }
        dac_rounded = (int)roundf(v_analog * DAC_SCALE);

        printf("%d%s", dac_rounded, (k == N - 1) ? "" : ", ");
        if ((k + 1) % 10 == 0 && k != N - 1) {
            printf("\n    ");
        }
    }
    printf("\n};\n");

    return 0;
}
