#include <stdio.h>
#include <unistd.h>

int esUnaPalabra(char* line) {
    if (line[0] == '\n') return 0;
    int cantPalabras = 0;
    int eraUnEspacio = 1;
    int i = 0;
    while (line[i] != '\0') {
        int esUnEspacio = (line[i] == ' ' || line[i] == '\n' || line[i] == '\0');
        if(eraUnEspacio && !esUnEspacio) cantPalabras++;
        eraUnEspacio = esUnEspacio;
        if (cantPalabras > 1) return 0;
        i++;
    }
    if (cantPalabras == 1) return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf ("No voy a abrir nada \n");
        return 1;
    }
    printf("Voy a abrir el archivo: %s \n", argv[1]);
    FILE* fp = fopen(argv[1], "r+");
    long posWrite = 0;
    long posRead = 0;
    int fileFinish = 0;
    if (fp == NULL) return 1;
    while (!fileFinish) {
        char buffer[255];
        fseek(fp, posRead, SEEK_SET);
        fgets(buffer, 255, fp);
        posRead = ftell(fp);
        fileFinish = feof(fp);
        if (esUnaPalabra(buffer)) {
            printf("La palabra es: %s", buffer);
        } else {
            printf("No es una palabra: %s", buffer);
            fseek(fp, posWrite, SEEK_SET);
            fputs(buffer, fp);
            posWrite = ftell(fp);
        }
    }
    ftruncate(fileno(fp), posWrite);
    fclose(fp);
    return 0;
}