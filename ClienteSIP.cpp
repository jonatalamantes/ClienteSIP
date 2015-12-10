#include <iostream>
#include <sstream>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <csignal>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "List.h"
#include "ClienteSIP.h"

#define redPack 2048

using namespace std;

/**
 * Método que transforma a un número entero en una cadena
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  number  Número a transformar
 * @return         Cadena Resultante
 */
string intToStr(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

void esperarMicrosegundos(int microseg)
{
    struct timeval tv;
    struct timezone tz;

    double gtres = gettimeofday(&tv, &tz);

    double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
    double ptiempo = tiempo;
    bool fin = false;

    while (!fin)
    {
        //Obtenemos la hora actual con los milisegundos
        gtres = gettimeofday(&tv, &tz);

        if (gtres < 0)
        {
            cerr << "Error al llamar a gettimeofday: \"" <<  strerror(errno) << "\"" << endl;
        }
        else
        {
            //Transformamos a un número doble la hora
            tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);

            //Imprimimos un punto si han pasado los microsegundos
            if ((tiempo - ptiempo) > microseg)
            {
                //cout << "*";
                fin = true;
            }
        }
    }
}

///Constructor
ClienteSIP::ClienteSIP()
{
    ClienteSIP::host = "";
    ClienteSIP::puerto = "";
    ClienteSIP::metaCabeceras.nullify();
    ClienteSIP::datoCabeceras.nullify();
    ClienteSIP::versionSIP = "";
    ClienteSIP::codigoSIP = "";
    ClienteSIP::nombreCodigoSIP = "";
    ClienteSIP::ubicacionArchivo = "";
    ClienteSIP::protocolo = "";
    ClienteSIP::url = "";
    ClienteSIP::errorCodigo = 0;
    ClienteSIP::tag = "";
    ClienteSIP::callId = "";

    ClienteSIP::descriptorEsperaSIP = -1;
    ClienteSIP::descriptorEsperaRTP = -1;
    ClienteSIP::descriptorServidorSIP = -1;
    ClienteSIP::descriptorServidorRTP = -1;
}

///Getters
string ClienteSIP::getProtocolo()
{
    return ClienteSIP::protocolo;
}

string ClienteSIP::getUrl()
{
    return ClienteSIP::url;
}

string ClienteSIP::getHost()
{
    return ClienteSIP::host;
}

string ClienteSIP::getPuerto()
{
    return ClienteSIP::puerto;
}

string ClienteSIP::getUbicacionArchivo()
{
    return ClienteSIP::ubicacionArchivo;
}

string ClienteSIP::getVersionSIP()
{
    return ClienteSIP::versionSIP;
}

string ClienteSIP::getCodigoSIP()
{
    return ClienteSIP::codigoSIP;
}

string ClienteSIP::getNombreCodigoSIP()
{
    return ClienteSIP::nombreCodigoSIP;
}

List<string> ClienteSIP::getMetaCabeceras()
{
    return ClienteSIP::metaCabeceras;
}

List<string> ClienteSIP::getDatoCabeceras()
{
    return ClienteSIP::datoCabeceras;
}

int ClienteSIP::getErrorCodigo()
{
    return ClienteSIP::errorCodigo;
}

string ClienteSIP::getCallId()
{
    return ClienteSIP::callId;
}

string ClienteSIP::getTag()
{
    return ClienteSIP::tag;
}

string ClienteSIP::getIpCliente()
{
    return ClienteSIP::ipCliente;
}

int ClienteSIP::getDescriptorEsperaSIP()
{
    return ClienteSIP::descriptorEsperaSIP;
}

int ClienteSIP::getDescriptorEsperaRTP()
{
    return ClienteSIP::descriptorEsperaRTP;
}

int ClienteSIP::getDescriptorServidorSIP()
{
    return ClienteSIP::descriptorServidorSIP;
}

int ClienteSIP::getDescriptorServidorRTP()
{
    return ClienteSIP::descriptorServidorRTP;
}

sockaddr_in ClienteSIP::getClienteSIP()
{
    return ClienteSIP::clienteSIP;
}

sockaddr_in ClienteSIP::getClienteRTP()
{
    return ClienteSIP::clienteRTP;
}

sockaddr ClienteSIP::getServidorSIP()
{
    return ClienteSIP::servidorSIP;
}

sockaddr ClienteSIP::getServidorRTP()
{
    return ClienteSIP::servidorRTP;
}

///Setters
void ClienteSIP::setProtocolo(string x)
{
    ClienteSIP::protocolo = x;
}

void ClienteSIP::setUrl(string x)
{
    ClienteSIP::url = x;
}

void ClienteSIP::setHost(string x)
{
    ClienteSIP::host = x;
}

void ClienteSIP::setPuerto(string x)
{
    ClienteSIP::puerto = x;
}

void ClienteSIP::setUbicacionArchivo(string x)
{
    ClienteSIP::ubicacionArchivo = x;
}

void ClienteSIP::setVersionSIP(string x)
{
    ClienteSIP::versionSIP = x;
}

void ClienteSIP::setCodigoSIP(string x)
{
    ClienteSIP::codigoSIP = x;
}
void ClienteSIP::setNombreCodigoSIP(string x)
{
    ClienteSIP::nombreCodigoSIP = x;
}

void ClienteSIP::setMetaCabeceras(List<string> x)
{
    ClienteSIP::metaCabeceras = x;
}

void ClienteSIP::setDatoCabeceras(List<string> x)
{
    ClienteSIP::datoCabeceras = x;
}

void ClienteSIP::setErrorCodigo(int x)
{
    ClienteSIP::errorCodigo = x;
}

void ClienteSIP::setCallId(string x)
{
    ClienteSIP::callId = x;
}

void ClienteSIP::setTag(string x)
{
    ClienteSIP::tag = x;
}

void ClienteSIP::setIpCliente(string x)
{
    ClienteSIP::ipCliente = x;
}

void ClienteSIP::setDescriptorEsperaSIP(int x)
{
    ClienteSIP::descriptorEsperaSIP = x;
}

void ClienteSIP::setDescriptorEsperaRTP(int x)
{
    ClienteSIP::descriptorEsperaRTP = x;
}

void ClienteSIP::setDescriptorServidorSIP(int x)
{
    ClienteSIP::descriptorServidorSIP = x;
}

void ClienteSIP::setDescriptorServidorRTP(int x)
{
    ClienteSIP::descriptorServidorRTP = x;
}

void ClienteSIP::setClienteSIP(sockaddr_in x)
{
    ClienteSIP::clienteSIP = x;
}

void ClienteSIP::setClienteRTP(sockaddr_in x)
{
    ClienteSIP::clienteRTP = x;
}

void ClienteSIP::setServidorSIP(sockaddr x)
{
    ClienteSIP::servidorSIP = x;
}

void ClienteSIP::setServidorRTP(sockaddr x)
{
    ClienteSIP::servidorRTP = x;
}

/**
 * Automata de Estado Finito para la validación de una URL del tipo
 * 'protocolo://user@host:puerto/archivo'
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  url     String con la URL a inspecionar
 * @return         URL con los datos correcto, sino regresa "incorrecto".
 */
string ClienteSIP::insertarDatosUrl(string url)
{
    int estado = 1;
    string myUrl = url;

    for (unsigned int i = 0; i < url.size(); i++)
    {
        if (estado == 1)
        {
            if ( isupper(url[i]) || islower(url[i]) || isdigit(url[i]) || url[i] == '[')
            {
                estado = 2;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 2)
        {
            if (url[i] == ':')
            {
                estado = 3;
            }
            else
            {
                estado = 2;
            }
        }
        else if (estado == 3)
        {
            if (url[i] == '/')
            {
                estado = 4;
            }
            else
            {
                estado = 2;
            }
        }
        else if (estado == 4)
        {
            if (url[i] == '/')
            {
                estado = 5;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 5)
        {
            if (isdigit(url[i]))
            {
                estado = 6;
            }
            else if (isupper(url[i]) || islower(url[i]))
            {
                estado = 12;
            }
            else if (url[i] == '[')
            {
                estado = 9;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 6)
        {
            if (isupper(url[i]) || islower(url[i]) || isdigit(url[i]) || url[i] == '.'  ||
                url[i] == '-' || url[i] == '_')
            {
                estado = 6;
            }
            else if (url[i] == ':')
            {
                estado = 7;
            }
            else if (url[i] == '/')
            {
                string cad = "";

                //Obtenemos el nombre del protocolo
                for (unsigned int j = 0; j < url.size(); j++)
                {
                    if (url[j] == ':')
                    {
                        break;
                    }
                    else
                    {
                        cad.push_back(url[j]);
                    }
                }

                if (cad == "sip")
                {
                    cad = "5060";
                }
                else
                {
                    //Sacamos el nombre del puerto
                    struct servent *tmp = getservbyname(cad.c_str(), "upd");
                    cad = intToStr(ntohs(tmp->s_port));
                }

                if (myUrl[myUrl.size()-1] == '/')
                {
                    myUrl = myUrl.substr(0, myUrl.size()-1);
                }

                myUrl = myUrl + ":" + cad + "/";
                myUrl = insertarDatosUrl(myUrl);

                estado = 8;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 7)
        {
            if (isdigit(url[i]))
            {
                estado = 7;
            }
            else if (url[i] == '/')
            {
                estado = 8;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 8)
        {
            estado = 8;
        }
        else if (estado == 9)
        {
            if (url[i] == ':' || isdigit(url[i]))
            {
                estado = 10;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 10)
        {
            if (url[i] == ':' || isdigit(url[i]))
            {
                estado = 10;
            }
            else if (url[i] == ']')
            {
                estado = 11;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 11)
        {
            if (url[i] == '/')
            {
                string cad;

                //Obtenemos el nombre del protocolo
                for (unsigned int j = 0; j < url.size(); j++)
                {
                    if (url[j] == ':')
                    {
                        break;
                    }
                    else
                    {
                        cad.push_back(url[j]);
                    }
                }

                if (cad == "sip")
                {
                    cad = "5060";
                }
                else
                {
                    //Sacamos el nombre del puerto
                    struct servent *tmp = getservbyname(cad.c_str(), "upd");

                    cad = intToStr(ntohs(tmp->s_port));
                }

                myUrl = myUrl + ":" + cad + "/";
                myUrl = insertarDatosUrl(myUrl);

                estado = 8;
            }
            else if (url[i] == ':')
            {
                estado = 7;
            }
            else
            {
                estado = 0;
            }
        }
        else if (estado == 12)
        {
            if (isupper(url[i]) || islower(url[i]) || url[i] == '.' || isdigit(url[i]))
            {
                estado = 12;
            }
            else if (url[i] == '@')
            {
                estado = 6;
            }
            else
            {
                estado = 0;
            }
        }
        else //Asume 0
        {
            //Incorrecto
        }
    }

    if (estado == 2)
    {
        return insertarDatosUrl("sip://" + myUrl);
    }
    else if (estado == 6)
    {
        string cad = "";

        //Obtenemos el nombre del protocolo
        for (unsigned int j = 0; j < url.size(); j++)
        {
            if (url[j] == ':')
            {
                break;
            }
            else
            {
                cad.push_back(url[j]);
            }
        }

        if (cad == "sip")
        {
            cad = "5060";
        }
        else
        {
            //Sacamos el nombre del puerto
            struct servent *tmp = getservbyname(cad.c_str(), "upd");
            cad = intToStr(ntohs(tmp->s_port));
        }

        if (myUrl[myUrl.size()-1] == '/')
        {
            myUrl = myUrl.substr(0, myUrl.size()-1);
        }

        myUrl = myUrl + ":" + cad + "/";
        return insertarDatosUrl(myUrl);
    }
    else if (estado == 7)
    {
        return insertarDatosUrl(myUrl + "/");
    }
    else if (estado == 8)
    {
        return myUrl;
    }
    else
    {
        return "incorrecto";
    }
}

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
void ClienteSIP::cargarDatosPagina(string urlPast, string *protocol, string *user, string *hostname,
                                   string *puerto, string *filename)
{
    //Sacamos el protocolo
    string url = urlPast;
    int posTag = url.find("://");
    *protocol = url.substr(0, posTag);
    url = url.substr(posTag+3, url.size()-posTag);

    posTag = url.find("@");
    *user = url.substr(0, posTag);
    url = url.substr(posTag+1, url.size()-posTag);

    //Sacamos el Host
    posTag = url.find('[');

    if (posTag == -1) //IPv4
    {
        posTag = url.find(":");
        *hostname = url.substr(0, posTag);
        url = url.substr(posTag+1, url.size()-posTag);
    }
    else //IPv6
    {
        posTag = url.find(']');
        *hostname = url.substr(1, posTag-1);
        url = url.substr(posTag+2, url.size()-posTag);
    }

    //Sacamos el puerto
    posTag = url.find("/");
    *puerto = url.substr(0, posTag);
    url = url.substr(posTag, url.size()-posTag);

    //Sacamos la url del archivo
    *filename = url;
}

/**
 * Método para armar un paquete usando el estandar de RTP
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param    secuencia       Byte con el número de secuencia del paquete
 * @param    timestamplLast  Bytes para el timestamp que se utilizó
 * @param    datos           Lista con los datos que se enviarán
 * @return                   Conjunto de Bytes resultantes en una lista
 */
List<uint8_t> ClienteSIP::armarPaqueteRTP(uint8_t *secuencia, uint32_t *timestampLast,
                                          List<uint8_t> datos)
{
    List<uint8_t> query;
    uint8_t oneByte;

    oneByte = 128; //Version
    query.append(oneByte);

    oneByte = 0; //Pay Load
    query.append(oneByte);

    query.append(0);
    query.append(*secuencia);

    *secuencia = *secuencia + 1;

    //Metemos el timestamp
    uint32_t fourBytes = *timestampLast + datos.getSize();
    *timestampLast = fourBytes;

    oneByte = (fourBytes & 0xFF000000) >> 24;
    query.append(oneByte);

    oneByte = (fourBytes & 0x00FF0000) >> 16;
    query.append(oneByte);

    oneByte = (fourBytes & 0x0000FF00) >> 8;
    query.append(oneByte);

    oneByte = (fourBytes & 0x000000FF);
    query.append(oneByte);

    //Metemos el src number
    fourBytes = 724910971;
    oneByte = (fourBytes & 0xFF000000) >> 24;
    query.append(oneByte);

    oneByte = (fourBytes & 0x00FF0000) >> 16;
    query.append(oneByte);

    oneByte = (fourBytes & 0x0000FF00) >> 8;
    query.append(oneByte);

    oneByte = (fourBytes & 0x000000FF);
    query.append(oneByte);

    //Metemos el audio de 320
    for (unsigned i = 0; i < datos.getSize(); i++)
    {
        query.append(datos[i]);
    }

    return query;
}

/**
 * Cierra los descriptores de la clase
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void ClienteSIP::closeConnection()
{
    close(descriptorEsperaRTP);
    close(descriptorEsperaSIP);
    close(descriptorServidorRTP);
    close(descriptorServidorSIP);
}

/**
 * Se abre una conexión por UDP al host indicado y al puerto indicado, Adicionalmente se
 * pone a la escucha el puerto SIP y RTP indicados en los defines
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  hostn    Host al que se pretende conectar por SIP
 * @param  portSIP  Puerto al que se pretende conectar por SIP
 */
void ClienteSIP::openConnection(string hostn, string portSIP)
{
    //Creamos las variables
    int res;
    string host = hostn, puertoSIP = portSIP;
    string hostToConnect;
    List<uint8_t> query;

    //Creamos la estructura del servidor
    char buffer[256], ip_buffer[256], puerto_buffer[64];
    int idServidorSIP;

    //struct sockaddr_storage servidor;
    struct sockaddr servidorSIP;
    struct sockaddr servidorRTP;

    //Rellenamos los datos con valor 0
    memset(&servidorSIP, 0, sizeof(servidorSIP));
    memset(&servidorRTP, 0, sizeof(servidorRTP));

    //Creamos la estructura de para los datos
    struct addrinfo hints, *resStruct, *ressave;

    memset(&hints, 0, sizeof(hints));
    memset(&buffer, 0, sizeof(char[256]));

    //Rellenamos la estructura de hints
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    //Obtenemos los datos del host
    int k1 = getaddrinfo(host.c_str(), puertoSIP.c_str(), &hints, &resStruct);

    if (k1 < 0)
    {
        cerr << "Error al llamar a getaddrinfo: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    //Guardamos el inicio de la estructura
    bool conexion = false;
    ressave = resStruct;

    while (resStruct != NULL && !conexion)
    {
        getnameinfo(resStruct->ai_addr, resStruct->ai_addrlen,
                    ip_buffer, 255,
                    puerto_buffer, 63, NI_NUMERICHOST);

        idServidorSIP = socket(resStruct->ai_family,resStruct->ai_socktype, resStruct->ai_protocol);

        if (idServidorSIP < 0)
        {
            cerr << "Error al llamar a socket: \"" <<  strerror(errno) << "\"" << endl;
            exit(-1);
        }

        //Nos conectamos con el socket
        res = connect(idServidorSIP, resStruct->ai_addr, resStruct->ai_addrlen);

        if (res >= 0)
        {
            servidorSIP = *resStruct->ai_addr;
            conexion = true;
        }
        else
        {
            close(idServidorSIP);
        }

        resStruct = resStruct->ai_next;
    }

    //Liberamos la informacion
    freeaddrinfo(ressave);

    if (!conexion)
    {
        cerr << "Error al encontrar el dominio: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    //Obtenemos los datos del host
    k1 = getaddrinfo(host.c_str(), puertoSIP.c_str(), &hints, &resStruct);

    if (k1 < 0)
    {
        cerr << "Error al llamar a getaddrinfo: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    //Creamos un socket cliente o 'yo' del RTP
    int idEsperaSIP = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in clienteSIP;

    clienteSIP.sin_family      = AF_INET;
    clienteSIP.sin_port        = htons(PUERTO_SIP_ESPERA);
    clienteSIP.sin_addr.s_addr = INADDR_ANY;

    res = bind(idEsperaSIP, (struct sockaddr*)&clienteSIP, sizeof(clienteSIP));

    //Creamos un socket cliente o 'yo'
    int idEsperaRTP = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in clienteRTP;

    clienteRTP.sin_family      = AF_INET;
    clienteRTP.sin_port        = htons(PUERTO_RTP_ESPERA);
    clienteRTP.sin_addr.s_addr = INADDR_ANY;

    res = bind(idEsperaRTP, (struct sockaddr*)&clienteRTP, sizeof(clienteRTP));

    //Creamos el Tag y el CallID
    srand(time(NULL));
    string ta = "", call = "";
    char letra;

    for (int n = 0; n < 10; n++)
    {
        letra = (rand() % 10) + 48;
        call.push_back(letra);
        ta.push_back(letra);
    }

    ClienteSIP::setCallId(call);
    ClienteSIP::setTag(ta);

    //Obtenemos la IP desde donde nos conectamos
    struct sockaddr_in sa;
    socklen_t sa_len = sizeof(sa);

    res = getsockname(idServidorSIP, (sockaddr*)&sa, &sa_len);

    if (res < 0)
    {
        cerr << "Error al llamar a getsockname: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }
    else
    {
        ClienteSIP::setIpCliente(inet_ntoa(sa.sin_addr));
    }

    //Le ponemos los datos de los descriptores
    ClienteSIP::setDescriptorEsperaSIP(idEsperaSIP);
    ClienteSIP::setDescriptorEsperaRTP(idEsperaRTP);
    ClienteSIP::setDescriptorServidorSIP(idServidorSIP);
    ClienteSIP::setClienteSIP(clienteSIP);
    ClienteSIP::setClienteRTP(clienteRTP);
    ClienteSIP::setServidorSIP(servidorSIP);
}

/**
 * Encargada de enviar los datos por UDP usando el protocolo SIP; requiere haber ejecutado
 * la función 'openConnection' previamente.
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  headerEnviar  Datos que se enviarán por la red
 * @param  tipoHeader    Tipo de Comando que se utiliza (INVITE, ACK ...)
 * @return               Codigo de Error en caso de que hubo fallo, 0 si salio bien
 */
int ClienteSIP::conectarHeaderSIP(string headerEnviar, string tipoHeader)
{
    //Creamos la estructura del Poll
    struct pollfd revisar[2];
    revisar[0].fd = descriptorEsperaSIP;
    revisar[0].events = POLLERR | POLLRDNORM | POLLHUP;;

    revisar[1].fd = descriptorServidorSIP;
    revisar[1].events = POLLERR | POLLOUT | POLLHUP;

    int i = 0, n;
    int gtres;

    struct timeval tv;
    struct timezone tz;

    gtres = gettimeofday(&tv, &tz);

    double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
    double ptiempo = tiempo;

    char buffer[redPack];
    memset(&buffer, 0, sizeof(buffer));

    bool fin = false;
    string html;
    int estadoRetorno = 0;
    int maxPuntos = 40;

    while (!fin && i < maxPuntos)
    {
        //Obtenemos la hora actual con los milisegundos
        gtres = gettimeofday(&tv, &tz);

        if (gtres < 0)
        {
            cerr << "Error al llamar a gettimeofday: \"" <<  strerror(errno) << "\"" << endl;
        }
        else
        {
            //Transformamos a un número doble la hora
            tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);

            //Imprimimos un punto si han pasado 500 milisegundos
            if (tiempo - ptiempo > 500000)
            {
                cout << '.';
                cout.flush();
                ptiempo = tiempo;

                i++;
            }
        }

        //Llamamos a poll para revisar si tenemos un evento en 50 milisegundos
        n = poll(revisar, 2, 70);

        if (n < 0)
        {
            cerr << "Error al llamar a poll (n<0): \"" <<  strerror(errno) << "\"" << endl;
        }
        else if (n > 0)
        {
            for (int k = 0; k < 2; k++)
            {
                if ((revisar[k].revents & POLLERR) == POLLERR)
                {
                    cerr << "Error al llamar a (POLLERR): \"" << strerror(errno) << "\"" << endl;
                    return 4;
                }
                else if ((revisar[k].revents & POLLHUP) == POLLHUP)
                {
                    cerr << "Error al llamar a (POLLHUP): \"" <<  strerror(errno) << "\"" << endl;
                }
                else if ((revisar[k].revents & POLLRDNORM) == POLLRDNORM) //Datos recibidos
                {
                    if (tipoHeader == "TRYING" || tipoHeader == "BUSY HERE" ||
                        tipoHeader == "RINGING" || tipoHeader == "OK" ||
                        tipoHeader == "TERMINE") //Recibiendo cabezera
                    {
                        socklen_t tam_sock = sizeof(clienteSIP);

                        memset(&buffer, 0, sizeof(buffer));
                        int res = recvfrom(descriptorEsperaSIP, buffer, redPack, 0,
                                           (sockaddr*)&clienteSIP, &tam_sock);

                        if (res < 0)
                        {
                            if (errno != EAGAIN && errno != EWOULDBLOCK)
                            {
                                cerr << "Error en read: \"" <<  strerror(errno) << "\"" << endl;
                            }
                            else
                            {
                                cerr << "Tendra que internarlo más tarde" << endl;
                            }

                            fin = true;

                            estadoRetorno = 1;
                        }
                        else if (res == 0)
                        {
                            fin = true;
                        }
                        else
                        {
                            //Guardamos el contenido en un archivo llamado "cabeceras.dat"
                            ofstream archivo;
                            archivo.open("cabeceras.dat", ios::trunc|ios::binary);

                            if (archivo.is_open())
                            {
                                for (int n = 0; n < res; n++)
                                {
                                    archivo.put(buffer[n]);
                                }
                            }

                            archivo.close();

                            ClienteSIP::procesarPeticion();
                            fin = true;
                        }
                    }
                }
                else if ((revisar[k].revents & POLLOUT) == POLLOUT) //Datos enviados
                {
                    if (tipoHeader == "INVITE" || tipoHeader == "CANCEL" || tipoHeader == "ACK")
                    {
                        socklen_t tam_sock = sizeof(servidorSIP);

                        //Escribimos una cabezera para SIP
                        string cabezera = headerEnviar;

                        //Leemos los datos del socket
                        int res = sendto(descriptorEsperaSIP, cabezera.c_str(), cabezera.size(), 0,
                                         &servidorSIP, tam_sock);

                        if (res < 0)
                        {
                            if (errno != EAGAIN && errno != EWOULDBLOCK)
                            {
                                cerr << "Error al llamar a write: \"" <<  strerror(errno)
                                     << "\"" << endl;
                            }
                            else
                            {
                                cerr << "Tendra que internarlo más tarde" << endl;
                            }

                            fin = true;

                            estadoRetorno = 1;
                        }
                        else
                        {
                            //Se han enviado los datos
                            fin = true;
                        }
                    }
                }
            }
        }

        if (i == 20) //han pasado 10 segundos sin respuesta
        {
            estadoRetorno = 2;
            fin = true;
        }
    }

    return estadoRetorno;
}

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
int ClienteSIP::conectarHeaderRTP(string host, string puertoRTP, string archivoHeader)
{
    //Creamos las variables
    int res;
    string hostToConnect;
    List<uint8_t> query;

    //Creamos la estructura del servidor
    char ip_buffer[256], puerto_buffer[64];
    int idServidorRTP;

    //struct sockaddr_storage servidor;
    struct sockaddr servidorRTP;

    //Rellenamos los datos con valor 0
    memset(&servidorRTP, 0, sizeof(servidorRTP));

    //Creamos la estructura de para los datos
    struct addrinfo hints, *resStruct, *ressave;

    memset(&hints, 0, sizeof(hints));

    //Rellenamos la estructura de hints
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    //Obtenemos los datos del host
    int k1 = getaddrinfo(host.c_str(), puertoRTP.c_str(), &hints, &resStruct);

    if (k1 < 0)
    {
        cerr << "Error al llamar a getaddrinfo: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    bool conexion = false;
    ressave = resStruct;

    while (resStruct != NULL && !conexion)
    {
        getnameinfo(resStruct->ai_addr, resStruct->ai_addrlen,
                    ip_buffer, 255,
                    puerto_buffer, 63, NI_NUMERICHOST);

        idServidorRTP = socket(resStruct->ai_family,resStruct->ai_socktype, resStruct->ai_protocol);

        if (idServidorRTP < 0)
        {
            cerr << "Error al llamar a socket: \"" <<  strerror(errno) << "\"" << endl;
            exit(-1);
        }

        //Nos conectamos con el socket
        res = connect(idServidorRTP, resStruct->ai_addr, resStruct->ai_addrlen);

        if (res >= 0)
        {
            //cout << "Conectado con " << ip_buffer << endl;
            servidorRTP = *resStruct->ai_addr;
            conexion = true;
        }
        else
        {
            close(idServidorRTP);
        }

        resStruct = resStruct->ai_next;
    }

    //Liberamos la informacion
    freeaddrinfo(ressave);

    if (!conexion)
    {
        cerr << "Error al encontrar el dominio: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    ClienteSIP::descriptorServidorRTP = idServidorRTP;
    ClienteSIP::servidorRTP = servidorRTP;

    //Creamos la estructura del Poll
    struct pollfd revisar[2];
    revisar[0].fd = descriptorEsperaSIP;
    revisar[0].events = POLLERR | POLLRDNORM | POLLHUP;;

    revisar[1].fd = descriptorServidorSIP;
    revisar[1].events = POLLERR | POLLOUT | POLLHUP;

    revisar[2].fd = descriptorEsperaRTP;
    revisar[2].events = POLLERR | POLLRDNORM | POLLHUP;;

    revisar[3].fd = descriptorServidorRTP;
    revisar[3].events = POLLERR | POLLOUT | POLLHUP;

    int i = 0, n;
    int gtres;

    uint8_t secuencia = 0;
    uint32_t timestamp = 800;
    List<uint8_t> datos;

    struct timeval tv;
    struct timezone tz;

    gtres = gettimeofday(&tv, &tz);

    double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
    double ptiempo = tiempo;

    char buffer[redPack];
    memset(&buffer, 0, sizeof(buffer));

    bool fin = false;
    string html;
    int estadoRetorno = 0;
    int maxPuntos = 40;

    //Abrimos el archivo de audio
    ifstream archivoRTP;
    archivoRTP.open(archivoHeader.c_str(), ios::binary);

    int byteSize = 1000;

    while (!fin && i < maxPuntos)
    {
        //Obtenemos la hora actual con los milisegundos
        gtres = gettimeofday(&tv, &tz);

        if (gtres < 0)
        {
            cerr << "Error al llamar a gettimeofday: \"" <<  strerror(errno) << "\"" << endl;
        }
        else
        {
            //Transformamos a un número doble la hora
            tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);

            //Imprimimos un punto si han pasado 500 milisegundos
            if (tiempo - ptiempo > 500000)
            {
                cout << '.';
                cout.flush();
                ptiempo = tiempo;

                i++;
            }
        }

        //Llamamos a poll para revisar si tenemos un evento en 50 milisegundos
        n = poll(revisar, 4, 70);

        if (n < 0)
        {
            cerr << "Error al llamar a poll (n<0): \"" <<  strerror(errno) << "\"" << endl;
        }
        else if (n > 0)
        {
            for (int k = 0; k < 4; k++)
            {
                if ((revisar[k].revents & POLLERR) == POLLERR)
                {
                    cerr << "Error al llamar a (POLLERR): \"" <<  strerror(errno) << "\"" << endl;
                    return 4;
                }

                if ((revisar[k].revents & POLLHUP) == POLLHUP)
                {
                    cerr << "Error al llamar a (POLLHUP): \"" <<  strerror(errno) << "\"" << endl;
                }

                if ((revisar[k].revents & POLLRDNORM) == POLLRDNORM) //Datos recibidos
                {
                    memset(&buffer, 0, sizeof(buffer));

                    if (revisar[k].fd == descriptorEsperaRTP)
                    {
                        //Recibimos un dato RTP
                    }
                    else if (revisar[k].fd == descriptorEsperaSIP)
                    {
                        //Recibimos un dato del SIP (Lo mas probable es que sea un BYE)

                        socklen_t tam_sock = sizeof(clienteSIP);
                        res = recvfrom(descriptorEsperaSIP, buffer, redPack, 0,
                                       (sockaddr*)&clienteSIP, &tam_sock);

                        if (res < 0)
                        {
                            if (errno != EAGAIN && errno != EWOULDBLOCK)
                            {
                                cerr << "Error en read: \"" <<  strerror(errno) << "\"" << endl;
                            }
                            else
                            {
                                cerr << "Tendra que internarlo más tarde" << endl;
                            }

                            fin = true;
                        }
                        else if (res == 0)
                        {
                            fin = true;
                        }
                        else
                        {
                            //Guardamos el contenido en un archivo llamado "cabeceras.dat"
                            ofstream archivo;
                            archivo.open("cabeceras.dat", ios::trunc|ios::binary);

                            if (archivo.is_open())
                            {
                                for (int n = 0; n < res; n++)
                                {
                                    archivo.put(buffer[n]);
                                }
                            }

                            archivo.close();

                            ClienteSIP::procesarPeticion();
                            fin = true;
                        }
                    }
                }

                if ((revisar[k].revents & POLLOUT) == POLLOUT) //Datos enviados
                {
                    if (revisar[k].fd == descriptorServidorSIP)
                    {
                        //Nada con el SIP
                    }
                    else if (revisar[k].fd == descriptorServidorRTP)
                    {
                        int cantidad = 0;

                        //Vaciamos los datos del paquete a enviar
                        socklen_t tam_sock = sizeof(servidorRTP);
                        datos.nullify();

                        //Cargamos 60 bytes en el archivo
                        char letra = archivoRTP.get();
                        bool salir = true;

                        while (cantidad < (byteSize))
                        {
                            letra = archivoRTP.get();

                            datos.append(letra);
                            cantidad++;

                            if (salir)
                            {
                                if (letra != EOF)
                                {
                                    salir = false;
                                    estadoRetorno = 2;
                                }
                            }
                        }

                        if (salir)
                        {
                            fin = true;
                        }

                        //Armamos el paquete
                        List<uint8_t> aEnviar = armarPaqueteRTP(&secuencia, &timestamp, datos);

                        char *arregloDinamico = new char[aEnviar.getSize()];

                        for (unsigned f = 0; f < aEnviar.getSize(); f++)
                        {
                            arregloDinamico[f] = aEnviar[f];
                        }

                        //Leemos los datos del socket
                        res = sendto(descriptorEsperaRTP, arregloDinamico,
                                     aEnviar.getSize(), 0, &servidorRTP, tam_sock);

                        //Eliminamos el arreglo
                        delete [] arregloDinamico;

                        if (res < 0)
                        {
                            if (errno != EAGAIN && errno != EWOULDBLOCK)
                            {
                                cerr << "Error en write: \"" <<  strerror(errno) << "\"" << endl;
                            }
                            else
                            {
                                cerr << "Tendra que internarlo más tarde" << endl;
                            }

                            fin = true;
                        }
                        else
                        {
                            esperarMicrosegundos(byteSize * 100);
                            i = 0;
                            //Mensaje Enviado correctamente
                        }
                    }
                }
            }
        }

        if (i == 20) //han pasado 10 segundos sin respuesta
        {
            estadoRetorno = 1;
            fin = true;
        }
    }

    archivoRTP.close();

    return estadoRetorno;
}

/**
 * Método encargada de Setterar los datos que hubo tras recibir un paquete de SIP
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void ClienteSIP::procesarPeticion()
{
    string definicionEstado = "", user = "";
    string versionSIP = "", estatusResponse = "", significadoResponse = "";

    //Creamos dos listas para el contenido de cabeceras
    List<string> cabecerasMeta, cabecerasDato;

    if (errorCodigo == 0)
    {
        //Abrimos el archivo de las cabeceras
        ifstream file2;
        string contenidoArchivo = "";
        file2.open("cabeceras.dat");

        if (file2.is_open())
        {
            //Obtenemos el archivo
            char actual = file2.get();
            string aux = "";
            bool meta = true;

            //Leemos hasta no encontrar el final de archivo
            while (actual != EOF)
            {
                contenidoArchivo.push_back(actual);

                //Final de linea
                if (actual == '\r')
                {
                    if (aux != "")
                    {
                        cabecerasDato.append(aux.substr(1, aux.size()-1));
                        aux = "";
                        meta = true;
                    }
                }
                else if (actual == ':') //hubo un separador de metadato
                {
                    if (meta)
                    {
                        cabecerasMeta.append(aux.substr(1, aux.size()-1));
                        aux = "";
                        meta = false;
                    }
                    else
                    {
                        aux.push_back(actual);
                    }
                }
                else
                {
                    aux.push_back(actual);
                }

                actual = file2.get();
            }
        }

        //Obtenemos el tipo de Mensaje
        definicionEstado = cabecerasDato.pop(0);

        //Obtenemos la version
        int posTag = definicionEstado.find(" ");
        versionSIP = "S" + definicionEstado.substr(0, posTag);
        definicionEstado = definicionEstado.substr(posTag+1, definicionEstado.size()-posTag);

        //Obtenemos el codigo de respuesta y el significado
        posTag = definicionEstado.find(" ");
        estatusResponse = definicionEstado.substr(0, posTag);
        significadoResponse = definicionEstado.substr(posTag+1, definicionEstado.size()-posTag);

        ClienteSIP::metaCabeceras = cabecerasMeta;
        ClienteSIP::datoCabeceras = cabecerasDato;
        ClienteSIP::versionSIP = versionSIP;
        ClienteSIP::codigoSIP = estatusResponse;
        ClienteSIP::nombreCodigoSIP = significadoResponse;

        file2.close();
    }
}

/**
 * Toma una cadena y trata de procesarla como una comunicación de SIP
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  url    URL a procesar
 */
void ClienteSIP::guardarURL(string *urlRecibida)
{
    //Creamos las variables
    string url = "", pastUrl = "", hostname = "", puerto = "", extension = "", protocol = "";
    string filename = "", user = "";

    url = *urlRecibida;
    url = insertarDatosUrl(url);

    if (url == "incorrecto")
    {
        cout << "Error al procesar la URL" << endl;
        ClienteSIP::setErrorCodigo(5);
    }
    else
    {
        cout << url << endl;

        cargarDatosPagina(url, &protocol, &user, &hostname, &puerto, &filename);

        ClienteSIP::host = hostname;
        ClienteSIP::puerto = puerto;
        ClienteSIP::protocolo = protocol;
        ClienteSIP::url = filename;

        if (protocol != "sip")
        {
            ClienteSIP::setErrorCodigo(6);
        }
        else
        {
            openConnection(hostname, "5060");

            string header2 = string("v=0") + "\r\n" +
                             "s=talk" + "\r\n" +
                             "o=Jonathan 3614 3230 IN IP4 " + getIpCliente() + "\r\n" +
                             "c=IN IP4 " + getIpCliente() + "\r\n" +
                             "t=0 0"  + "\r\n"+
                             "m=audio 7078 RTP/AVP 0 8 101"  + "\r\n"+
                             "a=rtpmap:0 PCMU/8000" + "\r\n"+
                             "a=rtpmap:8 PCMA/8000" + "\r\n"+
                             "a=rtpmap:101 telephone-event/8000" + "\r\n"+ "\r\n";

            string header1 = "INVITE sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                             "Via: SIP/2.0/UDP " + getIpCliente() + ":"
                                    + intToStr(PUERTO_SIP_ESPERA)
                                    + ";rport;branch=z9hG4bK4324324" + "\r\n" +
                             "From: \"Jonathan SIP\" <sip:jonathan@" + getIpCliente()
                                    + ">;tag=" + getTag() + "\r\n" +
                             "To: <sip:" + user + "@" + hostname + ">\r\n" +
                             "Call-ID: " + getCallId() + "\r\n" +
                             "CSeq: 20 INVITE " + "\r\n" +
                             "Contact: <sip:jonathan@" + getIpCliente() + ">" + "\r\n" +
                             "Content-Type: application/sdp" + "\r\n" +
                             "Allow: INVITE, ACK, CANCEL, BYE" + "\r\n" +
                             "Max-Forwards: 2" + "\r\n" +
                             "User-Agent: SiNW" + "\r\n" +
                             "Subject: Phone Call" + "r\n" +
                             "Content-Length: " + intToStr(header2.size()) + "\r\n\r\n" +
                             header2;

            //Obtenemos la cabecera para guardarla en un archivo
            errorCodigo = conectarHeaderSIP(header1, "INVITE");
            cout << "Enviado INVITE" << endl;

            if (errorCodigo == 0)
            {
                //Esperamos el Trying
                errorCodigo = conectarHeaderSIP("", "TRYING");
                cout << "Recibiendo TRYING" << endl;

                cout << nombreCodigoSIP << endl;

                if (!(nombreCodigoSIP == "Trying" || nombreCodigoSIP == "TRYING"))
                {
                    header1 = "ACK sip:" + user + "@" + hostname + " SIP/2.0\r\n";

                    for (unsigned i = 0; i < ClienteSIP::metaCabeceras.getSize(); i++)
                    {
                        header1 = header1 + metaCabeceras[i] + ": " + datoCabeceras[i] + "\r\n";
                    }

                    header1 = header1 + "\r\n";

                    cout << "Recibi un " << ClienteSIP::nombreCodigoSIP << endl;

                    errorCodigo = conectarHeaderSIP(header1, "ACK");

                    cout << "Enviando ACK" << endl;
                }

                if (errorCodigo == 0)
                {
                    procesarPeticion();

                    //Esperamos el RINGING
                    errorCodigo = conectarHeaderSIP("", "RINGING");
                    cout << "Recibiendo RINGING" << endl;

                    if (errorCodigo == 0)
                    {
                        //Buscando el To
                        int posX = -1;
                        string toS = "";
                        for (unsigned int i = 0; i < ClienteSIP::metaCabeceras.getSize(); i++)
                        {
                            if (ClienteSIP::metaCabeceras[i] == "To")
                            {
                                posX = i;
                            }
                        }

                        if (posX == -1)
                        {
                            toS = "To: " + ClienteSIP::datoCabeceras[posX];
                        }
                        else
                        {
                            toS = "To: <sip:" + user + "@" + hostname + ">\r\n";
                        }

                        //Esperamos a que haya un mensaje de contestación
                        errorCodigo = conectarHeaderSIP("", "RINGING");

                        //Me contestaron algo
                        if (errorCodigo == 0)
                        {
                            procesarPeticion();

                            if (ClienteSIP::codigoSIP == "486") //Busy Here
                            {
                                header1 = "ACK sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                                     "Via: SIP/2.0/UDP " + getIpCliente() + ":" +
                                           intToStr(PUERTO_SIP_ESPERA) +
                                           ";rport;branch=z9hG4bK4324324" + "\r\n" +
                                     "From: \"Jonathan SIP\" <sip:jonathan@" + getIpCliente()
                                           + ">;tag=" + getTag() + "\r\n" +
                                     toS +
                                     "Call-ID: " + getCallId() + "\r\n" +
                                     "CSeq: 20 ACK " + "\r\n" +
                                     "Max-Forwards: 2" + "\r\n" +
                                     "User-Agent: SiNW" + "\r\n" +
                                     "Content-Length: 0\r\n\r\n";

                                cout << "Recibi un Busy Here" << endl;

                                errorCodigo = conectarHeaderSIP(header1, "ACK");

                                cout << "Enviando ACK" << endl;
                            }
                            else if (ClienteSIP::codigoSIP == "603") //Decline
                            {
                                header1 = "ACK sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                                     "Via: SIP/2.0/UDP " + getIpCliente() + ":" +
                                            intToStr(PUERTO_SIP_ESPERA)
                                            + ";rport;branch=z9hG4bK4324324" + "\r\n" +
                                     "From: \"Jonathan SIP\" <sip:jonathan@" +
                                            getIpCliente() + ">;tag=" + getTag() + "\r\n" +
                                     toS +
                                     "Call-ID: " + getCallId() + "\r\n" +
                                     "CSeq: 20 ACK " + "\r\n" +
                                     "Max-Forwards: 2" + "\r\n" +
                                     "User-Agent: SiNW" + "\r\n" +
                                     "Content-Length: 0\r\n\r\n";

                                cout << "Recibi un Decline" << endl;

                                errorCodigo = conectarHeaderSIP(header1, "ACK");

                                cout << "Enviando ACK" << endl;
                            }
                            else if (ClienteSIP::codigoSIP == "200") //OK
                            {
                                cout << "Recibi un OK" << endl;

                                header1 = "ACK sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                                     "Via: SIP/2.0/UDP " + getIpCliente() + ":" +
                                           intToStr(PUERTO_SIP_ESPERA)
                                           + ";rport;branch=z9hG4bK4324324" + "\r\n" +
                                     "From: \"Jonathan SIP\" <sip:jonathan@" + getIpCliente()
                                           + ">;tag=" + getTag() + "\r\n" +
                                     toS +
                                     "Call-ID: " + getCallId() + "\r\n" +
                                     "CSeq: 20 ACK " + "\r\n" +
                                     "Max-Forwards: 2" + "\r\n" +
                                     "User-Agent: SiNW" + "\r\n" +
                                     "Content-Length: 0\r\n\r\n";

                                //Buscamos el puerto desde donde se enviará el RTP
                                ifstream archivo;
                                string contenidoArchivo = "";
                                archivo.open("cabeceras.dat");

                                if (archivo.is_open())
                                {
                                    char letra = archivo.get();

                                    while (letra != EOF)
                                    {
                                        contenidoArchivo.push_back(letra);
                                        letra = archivo.get();
                                    }

                                    archivo.close();
                                }

                                int posTag = contenidoArchivo.find("m=audio ");
                                string protocoloUsarRTP = contenidoArchivo.substr(posTag + 8, 10);
                                posTag = protocoloUsarRTP.find(" ");
                                protocoloUsarRTP = protocoloUsarRTP.substr(0, posTag);

                                cout << "Enviando ACK" << endl;
                                errorCodigo = conectarHeaderSIP(header1, "ACK");

                                if (errorCodigo == 0) //Comenzamos la comunicación RTP
                                {
                                    //Recibiendo OK
                                    cout << "Enviando Archivo de Audio" << endl;
                                    errorCodigo = conectarHeaderRTP(hostname, protocoloUsarRTP, "Ulaw.raw");

                                    if (errorCodigo == 2) //Fin de canción
                                    {
                                        procesarPeticion();

                                        //Buscando el To
                                        toS = "To: " + ClienteSIP::datoCabeceras[2] + "\r\n";
                                        
                                        header1 = "BYE sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                                                "Via: SIP/2.0/UDP " + getIpCliente() + ":" +
                                                        intToStr(PUERTO_SIP_ESPERA)
                                                        + ";rport;branch=z9hG4bK4324377" + "\r\n" +
                                                 "From: \"Jonathan SIP\" <sip:jonathan@"
                                                       + getIpCliente() + ">;tag=" + getTag() + "\r\n" +
                                                 toS +
                                                 "Call-ID: " + getCallId() + "\r\n" +
                                                 "CSeq: 21 BYE " + "\r\n" +
                                                 "Contact: <sip:jonathan@" + getIpCliente() + ":" + 
                                                        intToStr(PUERTO_SIP_ESPERA) + ">" + "\r\n" +
                                                 "Max-Forwards: 2" + "\r\n" +
                                                 "User-Agent: SiNW" + "\r\n" +
                                                 "Content-Length: 0\r\n\r\n";

                                        errorCodigo = conectarHeaderSIP(header1, "ACK");

                                        cout << "Enviando BYE" << endl;

                                        errorCodigo = conectarHeaderSIP("", "RINGING");
                                        cout << "Recibiendo OK" << endl;
                                    }
                                    else //Me colgaron
                                    {
                                        cout << "Recibido el BYE" << endl;

                                        //Buscando el From
                                        posX = -1;
                                        toS = "";
                                        for (unsigned i = 0; i < metaCabeceras.getSize(); i++)
                                        {
                                            if (ClienteSIP::metaCabeceras[i] == "From")
                                            {
                                                posX = i;
                                            }
                                        }

                                        if (posX == -1)
                                        {
                                            toS = "From: " + ClienteSIP::datoCabeceras[posX];
                                        }
                                        else
                                        {
                                            toS = "From: <sip:" + user + "@" + hostname + ">\r\n";
                                        }

                                        //Buscando el Via
                                        string toV = "Via: " + ClienteSIP::datoCabeceras[0] + "\r\n";

                                        header1 = string("SIP/2.0 200 OK\r\n") +
                                                 toV +
                                                 "To: \"Jonathan SIP\" <sip:jonathan@"
                                                       + getIpCliente() + ">;tag=" + getTag() + "\r\n" +
                                                 toS +
                                                 "Call-ID: " + getCallId() + "\r\n" +
                                                 "CSeq: 111 BYE " + "\r\n" +
                                                 "Max-Forwards: 2" + "\r\n" +
                                                 "User-Agent: SiNW" + "\r\n" +
                                                 "Content-Length: 0\r\n\r\n";

                                        errorCodigo = conectarHeaderSIP(header1, "ACK");
                                        cout << "Enviando OK" << endl;
                                    }
                                }
                            }
                        }
                        else //La llamada no fue contestada
                        {
                            header1 = "CANCEL sip:" + user + "@" + hostname + " SIP/2.0\r\n" +
                                             "Via: SIP/2.0/UDP " + getIpCliente() + ":" +
                                                   intToStr(PUERTO_SIP_ESPERA)
                                                   + ";rport;branch=z9hG4bK4324324" + "\r\n" +
                                             "From: \"Jonathan SIP\" <sip:jonathan@"
                                                   + getIpCliente() + ">;tag=" + getTag() + "\r\n" +
                                             toS +
                                             "Call-ID: " + getCallId() + "\r\n" +
                                             "CSeq: 20 CANCEL " + "\r\n" +
                                             "Max-Forwards: 2" + "\r\n" +
                                             "User-Agent: SiNW" + "\r\n" +
                                             "Content-Length: 0\r\n\r\n";

                            errorCodigo = conectarHeaderSIP(header1, "CANCEL");
                            cout << endl << "Enviando CANCEL" << endl;

                            if (errorCodigo == 0)
                            {
                                errorCodigo = conectarHeaderSIP("", "OK");
                                cout << "Recibiendo OK" << endl;

                                if (errorCodigo == 0)
                                {
                                    errorCodigo = conectarHeaderSIP("", "TERMINE");
                                    cout << "Recibiendo TERMINE" << endl;

                                    if (errorCodigo == 0)
                                    {
                                        header1 = "ACK sip:"+user + "@" + hostname +" SIP/2.0\r\n" +
                                             "Via: SIP/2.0/UDP " + getIpCliente() + ":"
                                                   + intToStr(PUERTO_SIP_ESPERA)
                                                   + ";rport;branch=z9hG4bK4324324" + "\r\n" +
                                             "From: \"Jonathan SIP\" <sip:jonathan@"
                                                   + getIpCliente() + ">;tag=" + getTag() + "\r\n" +
                                             toS +
                                             "Call-ID: " + getCallId() + "\r\n" +
                                             "CSeq: 20 ACK " + "\r\n" +
                                             "Max-Forwards: 2" + "\r\n" +
                                             "User-Agent: SiNW" + "\r\n" +
                                             "Content-Length: 0\r\n\r\n";

                                        errorCodigo = conectarHeaderSIP(header1, "ACK");
                                        cout << "Enviando ACK" << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //Cerramos la conexión
    closeConnection();
}

int main()
{
    ClienteSIP c;
    string cad;

    cout << "Inserte una URL de SIP 'sip://user@host:puerto/' => ";
    getline(cin, cad);

    c.guardarURL(&cad);

    return 0;
}
