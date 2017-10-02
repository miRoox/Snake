@rd /s /q release
@md release
gcc -fms-extensions *.c -o release\snake.exe
@if errorlevel 1 pause