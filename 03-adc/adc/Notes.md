How long does it take to read a single sample?

- Connect analog out of analog discovery to input of ADC
- Connect digital in of analog discovery to output GPIO
- 1st test code on board
    - Read ADC 100 times
    - Toggle GPIO out
    - Measure time to toggle
- 2nd test code on board
    - Do everything except for actually reading adc 100 times
    - Toggle GPIO out
    - Measure time to toggle
- Subtract both times to find the time for reading the adc, and divide by 100
- Don't print anything to serial out as this takes a lot of time