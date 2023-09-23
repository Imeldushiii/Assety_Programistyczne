#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define com "COM9"
int main()
{
    //========TWORZENIE PORTU=========
    HANDLE port;

    port = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //OTWIERAMY PORT
    if (port == INVALID_HANDLE_VALUE) { //JEZELI NIE OTWARTO
        printf("[-] Nie otwarto portu\n");
    }
    else { //JEZELI OTWARTO
        printf("[+] Port otwarto\n");
    }
    Sleep(100);

    //======POBIERANIE USTAWIEN=======
    DCB dcbSerial = {0};
    dcbSerial.DCBlength = sizeof(dcbSerial);
    if (!GetCommState(port, &dcbSerial)) {
        printf("[-] Nie pobrano ustawien portu\n");
        CloseHandle(port);
    }
    else {
        printf("[+] Pobrano ustawienia portu\n");
    }
    Sleep(100);
    //=======USTAWIANIE USTAWIEN PORTU=====
    dcbSerial.BaudRate = CBR_9600;
    dcbSerial.ByteSize = 8;
    dcbSerial.Parity = NOPARITY;
    dcbSerial.StopBits = ONESTOPBIT;
    if (!SetCommState(port, &dcbSerial)) {
        printf("[-] Nie ustawiono ustawien portu\n");
        CloseHandle(port);
    }
    else {
        printf("[+] Ustawiono ustawienia portu\n");
    }
    Sleep(100);
    //========USTAWIENIE TIMEOUTOW==========
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(port, &timeouts)) {
        printf("[-] Nie ustawiono Timeningow\n");
        CloseHandle(port);
    }
    else {
        printf("[+] Ustawiono Timeingi\n");
    }
    Sleep(100);
    //========ODCZYT DANYCH========
    char odczyt[256];
    DWORD stat;
    while(1) {
        if (ReadFile(port,odczyt,sizeof(odczyt)-1,&stat,NULL )) {
            if (stat > 0) {
                odczyt[stat] = '\0';
                printf("-> %s", odczyt);
            }
        }
    }
    CloseHandle(port);
    return 0;
}
