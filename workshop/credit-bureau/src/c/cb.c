
/**
 * gcc cb.c -lws2_32
 * Este aplicacion representa a una entidad crediticia la cual
 * concentra todos los creditos otorgados a los clientes de
 * diferentes entidades.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>

#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 2 /* El número de conexiones permitidas */

void find(char* buff, int sock);
void doprocessing (int sock);

/* ***************************************************************** */

void find(char* buff, int sock)
{
	FILE *archivol;  
	int i,x;
	char data[100];
    archivol = fopen("Loans.txt","r"); //Opening of the file to read
        while (!feof(archivol)) // Loop that will read all the lines until the end of the file
		{
				 for (i=0;i<100;i++) // This loop works to optain all the characters of the file and put them into a array
				 {
					data[i] = fgetc(archivol);
					if (data[i] == '\n') //If a char is a newline  then it get out of the loop
					{
						data[i] = '%';
						data[i+1]='\0';
						break;
					}
					if (data[i] == -1){
						data[i]='%';			
					}
				 }
				 if (strstr(data,buff) != NULL){ //this if works to look the buffer into the array, it will return NULL if there arent any match
					 for (i=0;i<100;i++)
					 {	
						//printf("%c",data[i]); // A print to see if the function works

						if (data[i] == '\0')
						{	
							x=i;
							// send(sock,data,i,0); //It will send all the information that comes before a newline
							 break;
						 }
					 }
					 send(sock,data,x,0); 
				}
        }
    fclose(archivol); //Close of the file  reader
}

void write_f(char* id, char* rfc, char* name, char* add, char* loan,  char* date,  char* qua, char* act)
{
	FILE *archivol;  
    archivol = fopen("Loans.txt","a+"); //Opening of the file to add line
	fseek(archivol,0,2);
	fprintf(archivol,"\n");
	fprintf(archivol,"%s|%s|%s|%s|%s|%s|%s|%s\0",id,rfc,name,add,loan,date,qua,act);
    fclose(archivol); //Close of the file  reader
}

void change_act(char* rfc,char* date)
{
	FILE *archivol;
	archivol = fopen("Loans.txt","r+");
	char data[100];
	int i;
	while (!feof(archivol)) // Loop that will read all the lines until the end of the file
		{
				 for (i=0;i<100;i++) // This loop works to optain all the characters of the file and put them into a array
				 {
					data[i] = fgetc(archivol);
					if ((data[i] == '\n'))  //If a char is a newline  then it get out of the loop
						break;
				 }
 				 if ((strstr(data,rfc) != NULL) && (strstr(data,date) != NULL)){ //this if works to look the buffer into the array, it will return NULL if there arent any match
						if (fgetc(archivol) == -1)
						{
							fseek(archivol,-1,1);
							fputc('N',archivol);
							fseek(archivol,0,2);
						} else {
							fseek(archivol,-4,1);
							fputc('N',archivol);
							fseek(archivol,3,1);						
						}

				} 
        }
	fclose(archivol);
}
	
void doprocessing (int sock)
{
    char buffer[100];
	char rfc[11];
	char sta[2];
	char id[4];
	char name[10];
	char add[10];
	char loan[10];
	char date[11];
	char qua[10];
	char act[2];
	int i,p[8],c = 0;
    memset(&(buffer), '!', 100);
	memset(&(date), '!', 11);
	memset(&(name), '!', 10);
	memset(&(add), '!', 10);
	memset(&(loan), '!', 10);
	memset(&(qua), '!', 10);
    int recvMsgSize;
	
    /* Receive message from client */
	if ((recvMsgSize = recv(sock, buffer,100, 0)) < 0){
            perror("ERROR reading to socket");
	}
	
	for (i=0;i<100;i++)
	{
		if (buffer[i] == '|'){
			p[c] = i;
			c++;			
		}
		if (buffer[i] == '!')
			break;
		//printf("%c",buffer[i]);
	}
	
	// for (i=0;i<c;i++)
		// printf("%d ",p[i]);
	
	// STATUS AND ACT
	sta[0]=buffer[0];
	act[0]=buffer[p[7]+1];
	sta[1]='\0';
	act[1]='\0';

	// ID
	for (i=0;i<4;i++)
		id[i] = buffer[(p[0]+1)+i];
	id[3] = '\0';

	// RFC	
	for (i=0;i<10;i++)
			rfc[i] = buffer[(p[1]+1)+i];
	rfc[10]='\0';
	
	// NAME
	for (i=0;i<(p[3]-p[2])-1;i++)
		name[i] = buffer[(p[2]+1)+i];
	for (i=0;i<10;i++){
		if (name[i] == '!')
			name[i]='\0';
	}
	
	// ADD
	for (i=0;i<(p[4]-p[3])-1;i++)
		add[i] = buffer[(p[3]+1)+i];
	for (i=0;i<10;i++){
		if (add[i] == '!')
			add[i]='\0';
	}

	// LOAN
	for (i=0;i<(p[5]-p[4])-1;i++)
		loan[i] = buffer[(p[4]+1)+i];
	for (i=0;i<10;i++){
		if (loan[i] == '!')
			loan[i]='\0';
	}

	// DATE
	for (i=0;i<(p[6]-p[5])-1;i++)
		date[i] = buffer[(p[5]+1)+i];
	for (i=0;i<11;i++){
		if (date[i] == '!')
			date[i]='\0';
	}
	
	// QUA
	for (i=0;i<(p[7]-p[6])-1;i++)
		qua[i] = buffer[(p[6]+1)+i];
	for (i=0;i<10;i++){
		if (qua[i] == '!')
			qua[i]='\0';
	}
	
	// for (i=0;i<10;i++)
		// printf("%c",rfc[i]);
		
	printf("%s %s\n",rfc,date);
	
	if (sta[0] == '0')
	{
		//printf("Function 0");
		find(rfc,sock);
	}else if ( sta[0] == '1')
	{
		//printf("Function 1");
		change_act(rfc,date);
	}else {
		//printf("Function 2");
		write_f(id,rfc,name,add,loan,date,qua,act);
	}
	
	//buffer[11] = '\0';

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
		/* Echo message back to client */
         if (send(sock, buffer, recvMsgSize, 0) != recvMsgSize){
			 perror("ERROR writing to socket");
		 } 	
		
        /* See if there is more data to receive */
        if ((recvMsgSize = recv(sock, buffer,10, 0)) < 0){
            perror("ERROR reading to socket");
		} 
    }
    closesocket(sock);    /* Close client socket */
}

BOOL initW32() 
{
		WSADATA wsaData;
		WORD version;
		int error;
		
		version = MAKEWORD( 2, 0 );
		
		error = WSAStartup( version, &wsaData );
		
		/* check for error */
		if ( error != 0 )
		{
		    /* error occured */
		    return FALSE;
		}
		
		/* check for correct version */
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
		     HIBYTE( wsaData.wVersion ) != 0 )
		{
		    /* incorrect WinSock version */
		    WSACleanup();
		    return FALSE;
		}	
}

int main()
{

	 initW32(); /* Necesaria para compilar en Windows */ 
	 	
   int fd, fd2; /* los descriptores de archivos */

   /* para la información de la dirección del servidor */
   struct sockaddr_in server;

   /* para la información de la dirección del cliente */
   struct sockaddr_in client;

   unsigned int sin_size;

   pid_t pid;

   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
      printf("error en socket()\n");
      exit(-1);
   }

   server.sin_family = AF_INET;

   server.sin_port = htons(PORT);

   server.sin_addr.s_addr = INADDR_ANY;
   /* INADDR_ANY coloca nuestra dirección IP automáticamente */

   //bzero(&(server.sin_zero),8);
   memset(&(server.sin_zero), '0', 8);
   /* escribimos ceros en el reto de la estructura */


   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }

   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
      exit(-1);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);
      /* A continuación la llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }

      printf("Se obtuvo una conexion desde %s\n", inet_ntoa(client.sin_addr) );
      /* que mostrará la IP del cliente */

      //send(fd2,"Bienvenido a mi servidor.\n",256,0);
      /* que enviará el mensaje de bienvenida al cliente */
      
      doprocessing(fd2);

   } /* end while */
}
