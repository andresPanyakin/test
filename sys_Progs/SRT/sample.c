#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

extern int errno; // код ошибки, если она возникнет
int fd; //дескриптор файла, имя задается из коммандной строки

//запись в файл 10 чисел
int writeToFile() {
	static int j = 1;
	if (j > 10) return 0;
	write(fd, &j, sizeof(int));
	printf("Write %i to file (fd %i)\t", j++, fd);
	return 1;
}

//чтение из файла 
void readFromFile() {
	int i = 0;
	lseek(fd,-sizeof(int), 1);
	read(fd,&i, sizeof(int));
	printf("Read %i from file (fd %i)\n", i, fd);
}

int main(int argc, char *argv[]) {
	// Раскомментируйте следующую строку для просмотра 
	// списка аргументов командной строки
	//printf("Param count: %i \nParam list : %s, %s \n\n", argc, argv[0],argv[1]);
	// проверить параметры командной строки
	if (argc != 2) { 
			puts("Usage: sample1 <outfile>\n");
				return -1;
	}
	// проверить, не возникло ли ошибки при открытии файла
	if ((fd = open(argv[1], O_CREAT | O_RDWR))==-1) {
			perror("ERROR: ");
				return -1;
	}
	// цикл записи/чтения файла 
	while (writeToFile()) readFromFile(); 
	close(fd);
	return 0;
}
