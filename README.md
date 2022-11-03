# TP_FINAL_LPC1769_CORTEXM3

## Electrónica Digital III 2022

- Ivo Gay Caramuti

- Francisco Cabrera

---

## Descripción general del proyecto

    El presente proyecto pretende modelar un sistema automático de carga de camiones cerealeros desde un silo. 

### Funcionalidades implementadas

- Pesaje de camiones

- Control de nivel de silo

- Sistema de gillotina para controlar el flujo de salida del silo

- Comunicación serial a PC

- Interfaz gráfica de visualización de variables

---

## Pin Out LPC 1769

GND               -| j2- 1                    j2- 28 |-
V3.3                -| j2- 2                    j2- 29 |-
                        -| j2- 3                    j2- 30 |-
                        -| j2- 4                    j2- 31 |-
Sensor100     -| j2- 5                    j2- 32 |-
Sensor75       -| j2- 6                    j2- 33 |-
Sensor50       -| j2- 7                    j2- 34 |-
Sensor25       -| j2- 8                    j2- 35 |-
LedVerde       -| j2- 9                    j2- 36 |-
LedRojo         -| j2- 10                  j2- 37 |-
                        -| j2- 11                  j2- 38 |-
                        -| j2- 12                  j2- 39 |-
                        -| j2- 13                  j2- 40 |-
                        -| j2- 14                  j2- 41 |-
LoadCellOut  -| j2- 15                  j2- 42 |-        UartTx
                        -| j2- 16                  j2- 43 |-
                        -| j2- 17                  j2- 44 |-         
                        -| j2- 18                  j2- 45 |-         ServoOut
                        -| j2- 19                  j2- 46 |-
                        -| j2- 20                  j2- 47 |-         
LedAzul          -| j2- 21                  j2- 48 |-
                        -| j2- 22                  j2- 49 |-
                        -| j2- 23                  j2- 50 |-
                        -| j2- 24                  j2- 51 |-        ExtInt0
                        -| j2- 25                  j2- 52 |-        ExtInt1
                        -| j2- 26                  j2- 53 |-        ExtInt2
                        -| j2- 27                  j2- 54 |-        GND

-----

## Circuitos particulares

### Celda de carga

     La celda de carga está compuesta por un puente wheastone que es alimentado con una tensión (en nuestro caso) de 5[v]. La salida del puente tiene una sensibilidad de 1[mV/V], lo que quiere decir que a fondo de escala (10[Kg]) obtendremos una salída de 5[mV]. 

    Para adaptar esta señal y poder procesarla con el ADC de la LPC1769, fue necesario un circuito de amplificación utilizando un amplificador de instrumentación AD620. La etapa de amplificación está referenciada a un voltaje máximo de 3.3[V] para poder conectarlo a la entrada analógica de la placa.<img src="file:///home/francabrera/snap/marktext/9/.config/marktext/images/2022-11-03-11-48-09-image.png" title="" alt="" data-align="center">

### Servo

    El servomotor utilizado para controlar la gillotina de apertura y cierre del silo se controla a través de una señal PWM de 5[V] de amplitud y 50[Hz] de frecuencia.

    Para controlar el grado de apertura se debe modificar el DuttyCycle de la señal, teniendo como referencia la siguiente imágen se implementó el código necesario para los ángulos necesarios. 

<img src="file:///home/francabrera/snap/marktext/9/.config/marktext/images/2022-11-03-11-25-15-image.png" title="" alt="" data-align="center">

    La salida digital de la LPC1769 tiene un valor de tensión de 3.3[V], por lo tanto es necesario una etapa de amplificación para lograr la amplitud de 5[V]. Al contar sólo con transistores BC548 (NPN), se genera una configuración inversora y por lo tanto la señal generada en el software también es negada para lograr el PWM deseado.

<img src="file:///home/francabrera/snap/marktext/9/.config/marktext/images/2022-11-03-11-54-48-image.png" title="" alt="" data-align="left">

### Sensores de nivel

    Los sensores de nivel del silo son de tipo infrarojos, compuestos por un led emisor y un fotoreceptor. Para variar la sensibilidad de detección de presencia se varía el valor de las resistencias que se conecta entre VCC y la señal de salida.

<img src="file:///home/francabrera/snap/marktext/9/.config/marktext/images/2022-11-03-11-59-04-image.png" title="" alt="" data-align="center">

### Uart

    La señal de salida de la uart de la LPC1769, tiene un valor de amplitud de 3.3[V].

    Para la conversión de RS-232 a USB, se realiza con un conversor TTL, que requiere que la señal tenga 5[V] de amplitud para poder recibirla correctamente. Por lo tanto se realizó una etápa de amplificación con transistores BC548 (NPN). Para evitar la inversión de la señal, se conecto los transistores en una configuración Darlington (en corte- saturación).

<img src="file:///home/francabrera/snap/marktext/9/.config/marktext/images/2022-11-03-12-02-41-image.png" title="" alt="" data-align="left">

----

## Posibles mejoras

- Control de lazo cerrado de la apertura del silo en función del peso actual y el peso final.

- Almacenar datos de la cantidad de camiones (y [Kg]) que se cargaron en un tiempo determinado.
