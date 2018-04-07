@rd /s /q debug
@md debug
gcc -g -Wall -fms-extensions -DDEBUG -o debug\snake.exe *.c
@if errorlevel 1 pause