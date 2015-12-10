# ClienteSIP
Cliente SIP en C++ que permite enviar audio cuando la sesión este establecida, el audio debe estar codificado en μ-law 

# Compilación y Dependencias
No depende de ninguna librería especial. Se puede compilar desde una terminal usando el compilador g++ escribiendo "g++ ClienteSIP.cpp -o clienteSIP -Wall".

# Funcionalidad
La aplicación ha sido probada con la aplicación Linphone y se puede lograr enviar el audio cuando la otra persona contesta el teléfono. Este cliente SIP es capaz de reconocer cuando le cuelgan las llamadas y cuando lo deniegan utilizando SIP 2.0