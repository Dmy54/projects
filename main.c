/*
 * FiLCh
 * GNU GPL
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

#define PORT "8080"
#define BACKLOG 10

char *filesInDir();
int initSock();
int sendToClient(int sock, char *str);
int main(void) {
	sendToClient(initSock(), filesInDir());// Вызываем функцию sendToClient(), в которую передаем int sock,
	// возвращаемый функцией initSock(), и  char *str, возвращаемый функцией filesInDir
	return 0;
}
char *filesInDir()
{
	char *str = (char*) malloc (256);// Максимальная длина имени одного файла, сумма символовв именах всех файлов,
									// не должны превышать 256 символов для крректной работы програмы
	memset(str, '\0', 256);// Заполняем строку пустыми символами, иначе в выводе присутствуют непонятные знаки
	DIR *dir;
	struct dirent *entry;
	char *nameDir = "./";// Директория, файлы которой нужно вывести
	dir = opendir(nameDir);
	while ((entry = readdir(dir)) != NULL)
	{
		sprintf(str, "%s %s\n", str, (char*)(entry->d_name));// Заполняем строку именами файлов
	}
	closedir(dir);
	return str;
}
int initSock()
{
	int sock;
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof (hints));
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL , PORT, &hints, &res);
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)// Создаём файловый дескриптор
	{
		printf("1");// При ошибке socket(), програма завершится с кодом 1
	}
	if ((bind(sock, res->ai_addr, res->ai_addrlen)) < 0)// Присваиваем файловому дескриптору адрес
	{
		printf("2");// При ошибке bind(), програма завершится с кодом 2
	}
	return sock;
}
int sendToClient(int sock, char *str)
{
	int new_sock;
	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof (their_addr);
	listen(sock, BACKLOG);//Ждём подключение пользователя
	if ((new_sock = accept(sock, (struct sockaddr *) &their_addr, &addr_size)) < 0)
	{
		printf("3");// При ошибке accept(), програма завершится с кодом 3
	}
	send(new_sock, str, strlen(str), 0);// Посылаем пользователю список файлов из екущей директории.
	free(str);
}