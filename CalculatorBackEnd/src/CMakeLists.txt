cmake_minimum_required(VERSION 3.10)
project(CppUTestExample)

# Устанавливаем путь к CppUTest
#set(CPPUTEST_HOME "C:/msys64/mingw64" CACHE PATH "Path to CppUTest")
set(CMAKE_CXX_STANDARD 20)    # Использовать C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Требовать указанный стандарт
set(CMAKE_CXX_EXTENSIONS OFF)  # Отключить нестандартные расширения компилятора (например, GNU extensions)
# Добавляем пути к заголовочным файлам и библиотекам CppUTest
include_directories(C:/msys64/mingw64/include)
include_directories(C:/msys64/mingw64/include/CppUTest)
include_directories(C:/msys64/mingw64/include/CppUTestExt)
link_directories(C:/msys64/mingw64/lib)

include_directories(production/include)

# Находим все файлы .cpp в папке tests и production_code
file(GLOB TEST_SOURCES "tests/*.cpp")
file(GLOB PRODUCTION_SOURCES "production/*.cpp")

# Создаём исполняемый файл для тестов
add_executable(runTests 
    ${TEST_SOURCES}
    ${PRODUCTION_SOURCES}
)

# Линкуем с библиотекой CppUTest
target_link_libraries(runTests CppUTest CppUTestExt)

# Выводим путь к CppUTest для отладки
#message(STATUS "CPPUTEST_HOME is set to: ${CPPUTEST_HOME}")
