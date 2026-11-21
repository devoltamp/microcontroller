### programmable counter array
---
enhanced 8051 variants (like **AT89C51RD2 / P89V51RD2**) include a **PCA** consisting of a dedicated 16-bit free-running timer (`CH`, `CL`) and **5 Capture/Compare modules** (Modules 0–4, mapped to `P1.3–P1.7`).

|**PCA Mode**|**CCAPMn Value**|**Description**|
|---|---|---|
|**16-Bit Capture**|`0x21` (`0x11` falling)|Captures `CH:CL` into `CCAPnH:CCAPnL` on `CEXn` pin edge + triggers interrupt.|
|**16-Bit Software Timer**|`0x49`|Triggers interrupt when `CH:CL` matches `CCAPnH:CCAPnL`.|
|**High-Speed Output**|`0x4D`|Toggles `CEXn` pin automatically in hardware on compare match (zero jitter).|
|**8-Bit PWM**|`0x42`|Compares `CL` against `CCAPnL` to generate continuous PWM on `CEXn`; `CCAPnH` reloads duty cycle cleanly.|
