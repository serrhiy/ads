set pathToHeaders=D:/programming/code/c++/SFML/include
set pathToLibs=D:/programming/code/c++/SFML/lib
set pathToProgramHeaders=%cd%/headers
g++ -std=c++17 -o main.exe main.cpp config.cpp utils.cpp vertex.cpp matrix.cpp draw.cpp graph.cpp -I%pathToHeaders% -L%pathToLibs% -I%pathToProgramHeaders% -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -D SFML_STATIC
main.exe