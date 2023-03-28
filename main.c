#include "headers/Client.h"
#include "headers/Serveur.h"
#include "headers/Packet.h"

#define UDP_port_S 8001
#define IP_addr_S "172.19.70.26"

int main(int argc, char* argv[])
{
    int nb_boucle = 0;
    packet* p = tokenPacket();    

    int udp_socket;
    //char buf[128];
    struct sockaddr_in sa_Serv, sa_Client;
    unsigned int taille_sa;

    udp_socket = socket(PF_INET, SOCK_DGRAM, 0);
    perror("Création socket !\n");

    bzero((char*) &sa_Serv, sizeof(struct sockaddr));
    sa_Serv.sin_family = PF_INET;
    sa_Serv.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_Serv.sin_port = htons(UDP_port_S);

    bind(udp_socket, (struct sockaddr *) &sa_Serv, sizeof(struct sockaddr));
    perror("Bind !\n");

    taille_sa = sizeof(struct sockaddr);

    setData(p, "Coucou toi...");
    client(p);

    while(1)
    {
        recvfrom(udp_socket, p, sizeof(packet*), 0, (struct sockaddr *) &sa_Client, &taille_sa);
        perror("Recvfrom !\n");

        printf("Nombre de boucle : %d\n", nb_boucle);
        nb_boucle++;
        printf("Message envoyé : %s\n", getData(p));
        //buf[5] = nb_boucle + '0';
        client(p);
        sleep(1);
        /*sendto(udp_socket, "Coucou toi...", 128 * sizeof(char), 0, (struct sockaddr *) &sa_Client, taille_sa);
        perror("Sendto !\n");*/
    }

    close(udp_socket);
    perror("Close !\n");

    return 0;
}