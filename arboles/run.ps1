g++ src/main.cpp src/controller/arbol_familia.cpp src/model/gestor_archivo.cpp src/view/interfaz_usuario.cpp -o bin/programa.exe

if (Test-Path .\entrada.txt) {
	Get-Content .\entrada.txt | .\bin\programa.exe
} else {
	.\bin\programa.exe
} 