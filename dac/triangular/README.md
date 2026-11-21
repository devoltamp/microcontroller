### continuous time equations
---
$$
V_{dac}(i/p) = 
\begin{cases} 
(100 \cdot t) \times 25.6 & \text{for } 0 \le t \le \frac{T}{2} \\
(1 - 100 \cdot t) \times 25.6 & \text{for } \frac{T}{2} < t \le T 
\end{cases}
$$

$$or$$

$$
{
V_{dac}(i/p) = 
\begin{cases} 
2.56 \cdot n \\ 
(25.6 - 2.56(n - 10)) 
\end{cases}
}
$$

where, $t = n \times 0.001$  
& the rest is done by `values.c`, just copy from that code & also the code is pretty similar to the sine one.
