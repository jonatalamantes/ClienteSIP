#ifndef CLIENTESIP_H
#define CLIENTESIP_H

#define PUERTO_SIP_ESPERA 5060
#define PUERTO_RTP_ESPERA 7078

#include "List.h"

/**
 * Clase encargada de Gestionar la estructura para la comunicación SIP
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
class ClienteSIP
{
    private:
    ///Atributos
        string protocolo;
        string url;
        string host;
        string puerto;
        string ubicacionArchivo;
        string versionSIP;
        string codigoSIP;
        string nombreCodigoSIP;
        List<string> metaCabeceras;
        List<string> datoCabeceras;
        int errorCodigo;
        string callId;
        string tag;
        string ipCliente;

        int descriptorEsperaSIP;
        int descriptorEsperaRTP;
        int descriptorServidorSIP;
        int descriptorServidorRTP;
        sockaddr_in clienteSIP;
        sockaddr_in clienteRTP;
        sockaddr servidorSIP;
        sockaddr servidorRTP;

    ///Metodos privados

        /**
         * Automata de Estado Finito para la validación de una URL del tipo
         * 'protocolo://user@host:puerto/archivo'
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  url     String con la URL a inspecionar
         * @return         URL con los datos correcto, sino regresa "incorrecto".
         */
        string insertarDatosUrl(string url);

        /**
         * Recibe una URL del tipo 'protocolo://user@host:puerto/archivo' para sacar el
         * protocolo, el usuario, el host, el puerto y el nombre del archivo
         *
         * @param urlPast    URL que será analizada
         * @param protocol   Protocolo que resulte
         * @param user       Usuario a donde conectar
         * @param hostname   Host de la URL
         * @param puerto     Puerto de Conexion
         * @param filename   Nombre del archivo a adquirir
         */
        void cargarDatosPagina(string urlPast, string *protocol, string *user,
                               string *hostname, string *puerto, string *filename);

        /**
         * Encargada de enviar los datos por UDP usando el protocolo SIP; requiere haber ejecutado
         * la función 'openConnection' previamente.
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  headerEnviar  Datos que se enviarán por la red
         * @param  tipoHeader    Tipo de Comando que se utiliza (INVITE, ACK ...)
         * @return               Codigo de Error en caso de que hubo fallo, 0 si salio bien
         */
        int  conectarHeaderSIP(string headerEnviar, string tipoHeader);

        /**
         * Se encarga de enviar un archivo con el codec de U-Law por RTP al host y puerto indicado.
         * Necesita tener la función "openConnection" previamente ejecutada
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  host           Host al que se quiere conectar
         * @param  puertoRTP      Puerto a la escucha donde estará el RTP del otro extremo
         * @param  archivoHeader  Nombre/Ubicación del archivo que se enviará por RTP
         * @return                Codigo de Error en caso de que hubo fallo, 0 si salio bien
         */
        int  conectarHeaderRTP(string host, string puertoRTP, string archivoHeader);

        /**
         * Método encargada de Setterar los datos que hubo tras recibir un paquete de SIP
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void procesarPeticion();

        /**
         * Método para armar un paquete usando el estandar de RTP
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param    secuencia       Byte con el número de secuencia del paquete
         * @param    timestamplLast  Bytes para el timestamp que se utilizó
         * @param    datos           Lista con los datos que se enviarán
         * @return                   Conjunto de Bytes resultantes en una lista
         */
        List<uint8_t> armarPaqueteRTP(uint8_t *secuencia, uint32_t *timestampLast, List<uint8_t> datos);

        /**
         * Se abre una conexión por UDP al host indicado y al puerto indicado, Adicionalmente se
         * pone a la escucha el puerto SIP y RTP indicados en los defines
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  hostn    Host al que se pretende conectar por SIP
         * @param  portSIP  Puerto al que se pretende conectar por SIP
         */
        void openConnection(string hostn, string portSIP);

        /**
         * Cierra los descriptores de la clase
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void closeConnection();

    public:
    ///Constructor
        ClienteSIP();

    ///Getters
        string getProtocolo();
        string getUrl();
        string getHost();
        string getPuerto();
        string getUbicacionArchivo();
        string getVersionSIP();
        string getCodigoSIP();
        string getNombreCodigoSIP();
        List<string> getMetaCabeceras();
        List<string> getDatoCabeceras();
        int getErrorCodigo();
        string getCallId();
        string getTag();
        string getIpCliente();
        int getDescriptorEsperaSIP();
        int getDescriptorEsperaRTP();
        int getDescriptorServidorSIP();
        int getDescriptorServidorRTP();
        sockaddr_in getClienteSIP();
        sockaddr_in getClienteRTP();
        sockaddr getServidorSIP();
        sockaddr getServidorRTP();

    ///Setters
        void setProtocolo(string x);
        void setUrl(string x);
        void setHost(string x);
        void setPuerto(string x);
        void setUbicacionArchivo(string x);
        void setVersionSIP(string x);
        void setCodigoSIP(string x);
        void setNombreCodigoSIP(string x);
        void setMetaCabeceras(List<string> x);
        void setDatoCabeceras(List<string> x);
        void setErrorCodigo(int x);
        void setCallId(string x);
        void setTag(string x);
        void setIpCliente(string x);
        void setDescriptorEsperaSIP(int x);
        void setDescriptorEsperaRTP(int x);
        void setDescriptorServidorSIP(int x);
        void setDescriptorServidorRTP(int x);
        void setClienteSIP(sockaddr_in x);
        void setClienteRTP(sockaddr_in x);
        void setServidorSIP(sockaddr x);
        void setServidorRTP(sockaddr x);

    ///Metodos publicos

        /**
         * Toma una cadena y trata de procesarla como una comunicación de SIP
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  url    URL a procesar
         */
        void guardarURL(string *url);
};

#endif // CLIENTESIP_H
