# Ejercicio CiberKillChain - Ataque

## Contenido

- [Ejercicio CiberKillChain - Ataque](#ejercicio-ciberkillchain---ataque)
  - [Contenido](#contenido)
  - [Enunciado](#enunciado)
  - [Alumno](#alumno)
  - [Resumen TP](#resumen-tp)
  - [Resolución](#resolución)
    - [Reconnaissance](#reconnaissance)
    - [Weaponization](#weaponization)
    - [Delivery](#delivery)
    - [Exploitation](#exploitation)
    - [Installation](#installation)
    - [Command \& Control](#command--control)
    - [Action of Objectives](#action-of-objectives)

## Enunciado

Armar una cyberkillchain usando técnicas de la matriz de Att&ck para un escenario relacionado al trabajo práctico de la carrera.

## Alumno

Jose Perez Galindo

## Resumen TP

Se implementará una plataforma para monitorear el rendimiento de computadoras monoplaca (SBC) basadas en Linux, centralizando datos de CPU, RAM, espacio libre en disco, estado de la red, entre otros, en un servidor.

Las SBCs enviarán estos datos al servidor mediante protocolo MQTT. El servidor contará con servicios para recibir y enviar configuraciones, almacenar y procesar datos y generar alertas vía mail. Asimismo, el servidor desplegará una web que permitirá la gestión de SBCs y visualización de datos en tablas y gráficos.

[Planificación del trabajo final](https://drive.google.com/file/d/16kA59A4iBf29dcPQbXB0o-8YjzdNrehf/view?usp=sharing)

## Resolución

Objetivo del ataque: Utilizar correos electrónicos de phishing dirigidos a los administradores del sistema para instalar un backdoor en sus computadoras para mantener acceso persistente y así obtener las credenciales de las SBC y utilizarlas como puntos de entrada a otros objetivos.


### Reconnaissance
  - Realizaré consultas DNS para recopilar información básica sobre los dominios utilizados por la empresa, lo cual ayudará a evitar la detección y mejorar la precisión de los correos de phishing. [T1590.002 - Gather Victim Network Information: DNS](https://attack.mitre.org/techniques/T1590/002/)
  
  - Recopilaré información personal de los usuarios del sistema y sus roles.  [T1593.001 - Search Open Websites/Domains: Social Media](https://attack.mitre.org/techniques/T1593/001/), [T1591.004 - Gather Victim Org Information: Identify Roles](https://attack.mitre.org/techniques/T1591/004/)
  
  - Determinaré el formato de las direcciones de correo electrónico de la organización. [T1589 - Gather Victim Identity Information](https://attack.mitre.org/techniques/T1589/)

### Weaponization
  - Implementaré un software malicioso que incluya un backdoor para mantener acceso persistente y herramientas para la explotación de objetivos de mayor relevancia. [T1027 - Obfuscated Files or Information](https://attack.mitre.org/techniques/T1027/) [T1203 - Exploitation for Client Execution](https://attack.mitre.org/techniques/T1203/) [T1132.001 - Data Encoding: Standard Encoding](https://attack.mitre.org/techniques/T1132/001/)

### Delivery
  - Enviaré correos electrónicos de phishing dirigidos a los administradores del sistema,  conteniendo enlaces o archivos adjuntos que instalen el software malicioso en sus computadoras. [T1566.001 - Phishing: Spearphishing Attachment](https://attack.mitre.org/techniques/T1566/001) [T1566.002 - Phishing: Spearphishing Link](https://attack.mitre.org/techniques/T1566/002/) 

### Exploitation
  - Al hacer clic en el enlace malicioso o abrir el archivo adjunto, se instala el malware en la computadora de la víctima. [T1068 - Exploitation for Privilege Escalation](https://attack.mitre.org/techniques/T1068/) [T1059 - Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059/)

### Installation
  - Instalaré las demás herramientas (keylogger, tareas, etc) que serán ejecutadas como servicios en segundo plano y enmascaradas como legítimas. [T1105 - Ingress Tool Transfer](https://attack.mitre.org/techniques/T1105/) [T1059 - Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059/) [T1036.004 - Masquerading: Masquerade Task or Service](https://attack.mitre.org/techniques/T1036/004/)

### Command & Control
  - Estableceré comunicaciones con un servidor de comando y control a través de un servicio web, utilizando un túnel HTTPS para mantener la comunicación segura. [T1071.001 - Application Layer Protocol: Web Protocols](https://attack.mitre.org/techniques/T1071/001/) [T1090.002 - Proxy: External Proxy](https://attack.mitre.org/techniques/T1090/002/) [T1573.001 - Encrypted Channel: Symmetric Cryptography](https://attack.mitre.org/techniques/T1573/001/)
  
  - Utilizar proxies para ocultar la ubicación real del servidor y dificultar el rastreo. [T1090.002 - Proxy: External Proxy](https://attack.mitre.org/techniques/T1090/002/)

### Action of Objectives
  - Extraeré credenciales de las computadoras de los administradores del sistema, buscando aquellas que permitan el acceso a las SBC. [T1059 - Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059/) [T1552 - Unsecured Credentials](https://attack.mitre.org/techniques/T1552/)

  - Desde las SBC, monitorearé la actividad de las redes comprometidas para identificar objetivos de mayor relevancia, como servidores, bases de datos o sistemas de información sensibles. [T1071.001 - Application Layer Protocol: Web Protocols](https://attack.mitre.org/techniques/T1071/001/) [T1105 - Ingress Tool Transfer](https://attack.mitre.org/techniques/T1105/)
  
  - Utilizaré las SBC comprometidas como puntos de acceso para lanzar ataques a los objetivos identificados. [T1078 - Valid Accounts](https://attack.mitre.org/techniques/T1078/) [T1071.001 - Application Layer Protocol: Web Protocols](https://attack.mitre.org/techniques/T1071/001/) [T1210 - Exploitation of Remote Services](https://attack.mitre.org/techniques/T1210/)

