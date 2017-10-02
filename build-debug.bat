@rd /s /q debug
@md debug
gcc -g -Wall -fms-extensions -DDEBUG main.c -o debug\snake.exe 
@if errorlevel 1 pause