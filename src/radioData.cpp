#include <radioData.h>


RadioData::RadioData() {
};

RadioData::RadioData(int numFrames, int numLostFrames) {
    setSecond(0);
    setFrames(numFrames);
    setLostFrames(numLostFrames);
};

RadioData::~RadioData() {
};

void RadioData::setSecond(int second) {
    seconds.push_back(second);
}

void RadioData::setFrames(int numFrames) {
    frames.push_back(numFrames);
}

void RadioData::setLostFrames(int numLostFrames) {
    lostFrames.push_back(numLostFrames);
}

void RadioData::run() {
    char inputChar;
    bool isRun = true;
    int countSeconds;

    while (isRun) {
        bool canCalcErr = seconds.size() > 0;
        std::cout << "q - для выхода из программы" << std::endl; 
        std::cout << "i - для ввода данных" << std::endl;

        if (canCalcErr) {
            std::cout << "e - для вычесления ошибки" << std::endl; 
        }

        std::cin >> inputChar;

        switch (inputChar)
        {
        case 'q':
            isRun = false;
            break;

        case 'i':
            input();
            break;

        case 'e':
            if (canCalcErr) {
                computeErrorRate();
            }
            break;
        
        default:
            break;
        }
    }

}

bool RadioData::inputSecond(int *second) {
    
    std::cout << "Введите текущее время в секундах: ";
    std::cin >> *second;

    if (*second <= 0) {
        std::cout << "ОШИБКА: ";
        std::cout << "Тикущее время должно быть больше нуля" << std::endl;
        return false;

    } 

    if (seconds.size() > 0) {
        if (*second <= seconds.back()) {
            std::cout << "ОШИБКА: ";
            std::cout << "Тикущее время должно быть предыдущего" << std::endl;
            return false;
        }
    }

    return true;
}

bool RadioData::inputFrames(int *numFrames) {
    std::cout << "Введите количество переданных кадров: ";
    std::cin >> *numFrames;

    if (*numFrames < 0) {
        std::cout << "ОШИБКА: ";
        std::cout << "Количество переданных кадров должно быть больше или равно нулю" << std::endl;
        return false;
    } 

    return true;

}

bool RadioData::inputLostFrames(int *numLostFrames, int *numFrames) {
    std::cout << "Введите количество потеряных кадров: ";
    std::cin >> *numLostFrames;

    if (*numLostFrames < 0) {
        std::cout << "ОШИБКА: ";
        std::cout << "Количество потеряных кадров должно быть больше или равно нулю" << std::endl;
        return false;
    } 

    if (*numLostFrames > *numFrames) {
        std::cout << "ОШИБКА: ";
        std::cout << "Количество потеряных кадров должно быть меньше или равно количеству переданных кадров" << std::endl;
        return false;
    } 

    return true;
}

void RadioData::input() {
    int second, numFrames, numLostFrames; 
    bool isValidSecond = false;
    bool isValidNumFrames = false;
    bool isValidLostNumFrames = false;

    while (!isValidSecond) {
        isValidSecond = inputSecond(&second);
    }

    while (!isValidNumFrames) {
        isValidNumFrames = inputFrames(&numFrames);
    }

    while (!isValidLostNumFrames) {
        isValidLostNumFrames = inputLostFrames(&numLostFrames, &numFrames);
    }
    
    setSecond(second);
    setFrames(numFrames);
    setLostFrames(numLostFrames);
};

float RadioData::getErrorRate(int totalSeconds){
    float tmpDiffNumFrames;
    float tmpDiffNumLostFrames;
    float tempErr;
    float totalError = 0.0;

    int nowSecond;
    int prewSecond;
    int maxIndex = seconds.size();

    int numSeconds = 0;
    int index = 0;

    nowSecond = seconds[maxIndex-1];
    while (numSeconds < totalSeconds) {
        prewSecond = seconds[maxIndex-index-2];

        tmpDiffNumFrames = frames[maxIndex-index-1] - frames[maxIndex-index-2];
        tmpDiffNumLostFrames = lostFrames[maxIndex-index-1] - lostFrames[maxIndex-index-2];
        tempErr = (tmpDiffNumLostFrames/tmpDiffNumFrames);

        for (int j=nowSecond-1; j>=prewSecond; j--) {
            totalError += tempErr;
            numSeconds++;
        }
        nowSecond = prewSecond;
        index++;
    }

    totalError /= totalSeconds;
    return totalError;
}

void RadioData::computeErrorRate() {
    int numSeconds;
    bool isValidNumSeconds = false;

    while (!isValidNumSeconds) {
        std::cout << "Введите продолжительность временного окна в секундах: ";
        std::cin >> numSeconds;

        if (numSeconds < 0) {
            std::cout << "ОШИБКА: ";
            std::cout << "Продолжительность окна должна быть больше нуля" << std::endl;
            continue;
        } 

        if (numSeconds > seconds.back()) {
            std::cout << "ОШИБКА: ";
            std::cout << "Продолжительность окна должна быть меньше или равно текущего времени" << std::endl;
            continue;
        } 

        isValidNumSeconds = true;
    }

    float error = getErrorRate(numSeconds);
    std::cout << "Отношение ошибочных пакетов к переданным: " << error << std::endl;

}
