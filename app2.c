#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include <windows.h>
#include <sys/types.h>

//
// ПРОВЕРЯЕМ ЯВЛЯЕТСЯ ЛИ ЧИСЛОМ
//
int test_number(const char * str) {
    char * tail;
    long num;
    
    errno = 0;
    num = strtol(str, &tail, 10);
    
    return ( errno || *tail );
}


int main (int argc, char * argv[]) { 

    // FILE *file, *file1, *file2;
    char result1[90], result2[90], result3[90];
    int new_int, new_int2;
    char new_int_to_char[15], new_int_to_char2[15];
    char new_arg1[16] = "app2.exe ", new_arg2[16] = "app2.exe ";

    //
    // ПРОВЕРЯЕМ КОЛИЧЕСТВО АРГУМЕНТОВ
    //
    if (argc != 2 ) {


        // fprintf(stderr, "Неверное количество параметров\n");
        fprintf(stderr, "1\n");
        return 1;
    }
    else {
        //
        // ПРОВЕРЯЕМ ВСЕ ПЕРЕДАННЫЕ АРГУМЕНТЫ НА СООТВЕТСТВИЕ ЧИСЛОВОМУ ТИПОМ
        //
        for(int i = 1; i < argc; i ++)
            if (test_number(argv[i])) {
                fprintf(stderr, "2\n");
                return 2;
            }

        // printf("%s var", argv[1]);

        if (atoi(argv[1]) < 1 || atoi(argv[1]) > 13) {
            fprintf(stderr, "3\n");
            return 3;

        }
        if (atoi(argv[1]) == 1 || atoi(argv[1]) == 2) {
             fprintf(stderr, "1\n");
            return 1;

        }
        else {

            new_int = atoi(argv[1]) - 1;             
            snprintf(new_int_to_char, 10, "%d", new_int);


            new_int2 = atoi(argv[1]) - 2;
            snprintf(new_int_to_char2, 10, "%d", new_int2);


            strcat_s(new_arg1, sizeof(new_arg1), new_int_to_char);
            strcat_s(new_arg2, sizeof(new_arg2), new_int_to_char2);

            // printf("%s", new_arg1);

         
            STARTUPINFO si;
            PROCESS_INFORMATION child1, child2;
            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            ZeroMemory( &child1, sizeof(child1) );
            ZeroMemory( &child2, sizeof(child2) );
            if (!CreateProcessA(NULL, new_arg1, NULL, NULL, 0, 0, NULL, NULL, &si, &child1))
            {
                fprintf(stderr, "CreateProcessA() error!, %d\n", GetLastError());
            }
            if (!CreateProcessA(NULL, new_arg2, NULL, NULL, 0, 0, NULL, NULL, &si, &child2))
            {
                fprintf(stderr, "CreateProcessA() error!, %d\n", GetLastError());
            }
            WaitForSingleObject(child1.hProcess, INFINITE);
            WaitForSingleObject(child2.hProcess, INFINITE);

            DWORD ec1, ec2;
            GetExitCodeProcess(child1.hProcess, &ec1);
            GetExitCodeProcess(child2.hProcess, &ec2);


            sprintf(result1, " %d\t%d\t%s\t%d\n", GetCurrentProcessId(), child1.dwProcessId, new_int_to_char, ec1);
            sprintf(result2, "%d\t%d\t%s\t%d\n", GetCurrentProcessId(), child2.dwProcessId, new_int_to_char2, ec2);
            sprintf(result3, "%d\t\t\t%d\n", GetCurrentProcessId(), (ec1+ec2));

            CloseHandle(child1.hProcess);
            CloseHandle(child1.hThread);

            CloseHandle(child2.hProcess);
            CloseHandle(child2.hThread);


            printf("%s %s %s", result1, result2, result3);
            return (ec1+ec2);
            // return 0;

        }

    }
    

  	return 0;
}