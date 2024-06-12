# Ejercicio CiberKillChain - Defensa

## Contenido

- [Ejercicio CiberKillChain - Ataque](#ejercicio-ciberkillchain---ataque)
  - [Contenido](#contenido)
  - [Enunciado](#enunciado)
  - [Alumno](#alumno)
  - [Resolución](#resolución)
    - [Action of Objectives](#action-of-objectives)
    - [Command \& Control](#command--control)
    - [Installation](#installation)
    - [Exploitation](#exploitation)
    - [Delivery](#delivery)
    - [Weaponization](#weaponization)
    - [Reconnaissance](#reconnaissance)

## Enunciado

Desarrollar la defensa en función del ataque planteado en orden inverso. No es una respuesta a un incidente, hay que detectar el ataque independientemente de la etapa.

Para cada etapa elegir una sola defensa, la más importante, considerar recursos limitados.

## Alumno

Jose Perez Galindo

## Resolución

> A través de la Plataforma de rendmiento de computadoras monoplaca, el usuario administrador se percata que algunos dispositivos tienen usos elevados de CPU y RAM. Es ahí donde decide hacer un troubleshooting de esos equipos para diagnosticar el problema y se da con la sorpresa que hay un intruso utilizando los dispositivos.

### Action of Objectives

- Implementar políticas de contraseñas robustas que incluyan la utilización de gestores de contraseñas, autenticación multifactor (MFA) y requisitos de complejidad, además de realizar auditorías periódicas de contraseñas y forzar cambios regulares. [M1027 - Password Policies](https://attack.mitre.org/mitigations/M1027/)


### Command & Control

- Utilizar soluciones de monitoreo de red avanzadas que incluyan análisis de tráfico en tiempo real, detección de anomalías y herramientas de inteligencia de amenazas para identificar y bloquear comunicaciones sospechosas que puedan indicar el uso de proxies, servidores y/o usuarios desconocidos y VPNs maliciosos. [M1037 - Filter Network Traffic](https://attack.mitre.org/mitigations/M1037/)


### Installation

- Implementar una gestión robusta de cuentas privilegiadas, utilizando herramientas de control de acceso basadas en roles (RBAC) y autenticación multifactor (MFA) para asegurar que solo los administradores de TI autorizados puedan instalar software, minimizando el riesgo de instalación no autorizada. [M1026 - Privileged Account Management](https://attack.mitre.org/mitigations/M1026/)

### Exploitation

- Desarrollar un programa integral y continuo de formación en ciberseguridad para todos los empleados, con un enfoque especial en la identificación de correos electrónicos de phishing y la importancia de no hacer clic en enlaces ni abrir archivos adjuntos de fuentes desconocidas. [M1017 - User Training](https://attack.mitre.org/mitigations/M1017/)

### Delivery 

- Implementar un sistema de prevención de intrusiones en la red que incluya filtrado de correo electrónico, análisis de contenido, y sandboxing para analizar y detener correos electrónicos maliciosos antes de que lleguen a los usuarios. [M1031 - Network Intrusion Prevention](https://attack.mitre.org/mitigations/M1031/)

### Weaponization (editado)

-  Implementar políticas y tecnologías que prevengan la ejecución de archivos y scripts no autorizados. Esto incluye utilizar listas blancas de aplicaciones para permitir solo la ejecución de software aprobado y conocido, así como el uso de soluciones de control de aplicaciones que bloqueen la ejecución de cualquier software no autorizado. [M1038 - Execution Prevention](https://attack.mitre.org/mitigations/M1038/)

### Reconnaissance

- Llevar a cabo una formación continua y detallada para empleados sobre la importancia de proteger la información personal y corporativa, incluyendo prácticas seguras en redes sociales y la minimización de la información disponible públicamente sobre la organización y sus empleados. [M1056 - Pre-compromise](https://attack.mitre.org/mitigations/M1056/), [M1017 - User Training](https://attack.mitre.org/mitigations/M1017/)
