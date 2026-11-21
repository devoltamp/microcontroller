## 1. Average Output Voltage & Duty Cycle ($D$)

$$V_{\text{out}} = V_{\text{in}} \cdot D \implies V_{\text{dc}} \cdot D = V_m \sin(\omega t)$$

$$D_{\text{req}} = \left(\frac{V_m}{V_{\text{dc}}}\right) \sin(\omega t) = m_a \sin(\omega t)$$

where modulation index,  
$m_a = \frac{V_m}{V_{\text{dc}}} = 0.7$, with $\(V_{\text{dc}} > V_m\)$
## 2. Switching Period ($T_s$) & ON-Time ($t_{\text{on}}$)

- **Switching frequency:** $F_s = 2\text{ kHz} \implies T_s = \dfrac{1}{F_s} = \dfrac{1}{2000} = 0.5\text{ ms}$
    
- **Fundamental frequency:** $f = 50\text{ Hz} \implies \omega = 2\pi f = 100\pi\text{ rad/s}$, period $T = 20\text{ ms}$
    
- **Number of PWM pulses per $50\text{ Hz}$ cycle:**
    
$$N = \frac{T}{T_s} = \frac{20\text{ ms}}{0.5\text{ ms}} = 40\text{ samples}$$
    
- **Instantaneous ON-time:**
    
$$t_{\text{on}} = D_{\text{req}} \cdot T_s = \frac{1}{F_s}\left(\frac{V_m}{V_{\text{dc}}}\right) \sin(\omega t)$$
## 3. 8051 Timer Clock & Reload Count Equations

- **Timer clock frequency** ($12\text{ MHz}$ crystal, 12-clock mode):
    
    $$F_{\text{clk}} = \frac{12\text{ MHz}}{12} = 1\text{ MHz} \quad (T_{\text{clk}} = 1\text{ }\mu\text{s})$$
    
- **Timer 1 (Fixed Switching Period $T_s = 0.5\text{ ms} = 500\text{ }\mu\text{s}$):**
    
    $$\text{Counts} = T_s \cdot F_{\text{clk}} = 0.5\text{ ms} \times 1\text{ MHz} = 500$$
    
    $$\text{Reload}_{T1} = 65536 - 500 = 65036 = \text{0xFE0C} \quad (\text{TH1} = \text{0xFE},\; \text{TL1} = \text{0x0C})$$
    
- **Timer 0 (Variable ON-Time $t_{\text{on}}$):**
    
$$\text{Count}_{\text{on}} = t_{\text{on}} \cdot F_{\text{clk}} = D \left(\frac{F_{\text{clk}}}{F_s}\right) = \left(\frac{V_m}{V_{\text{dc}}} \sin(\omega t)\right)\left(\frac{1\text{ MHz}}{2\text{ kHz}}\right) = 500 \times 0.7 \sin(\omega t) = 350 \sin(\omega t)$$
    
$$\text{Reload}_{T0}[i] = 65536 - 350 \sin(2\pi \cdot 50 \cdot t_i), \quad t_i = i \times 0.5\text{ ms} \quad (i = 0, 1, \dots, 39)$$
