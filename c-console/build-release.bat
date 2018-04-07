@rd /s /q release
@md release
gcc -fms-extensions -o release\snake.exe *.c
@if errorlevel 1 pause