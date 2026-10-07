Continuous Time Equations; 
---

- Rising Ramp ($0 \le t \le \frac{T}{2}$):  
$$V_{\text{dac}} (i/p) = (100 \cdot t * 25.6)  $$

- Falling Ramp ($\frac{T}{2} < t \le T$):
$$V_{\text{dac}} (i/p) = \big((1 - 100 \cdot t) * 25.6 \big)$$
  
<!-- <br> -->
& the rest is done by the `values.c`, just copy from that code & also the code is pretty simillar to the sine one.
