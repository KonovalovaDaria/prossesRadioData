#include <iostream>
#include <radioData.h>

int main() {
    
    RadioData radioData = RadioData(1000, 1);  // Инициализация начальными
    std::cout << "Инициализировано начальными данными: frames: 1000, lost_frames: 1." << std::endl;

    radioData.run();  //  Запуск передачи данных
}