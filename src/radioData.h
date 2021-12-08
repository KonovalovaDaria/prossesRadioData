#include<iostream>
#include <vector>


class RadioData {
public:
    RadioData();
    RadioData(int numFrames, int numLostFrames);
    ~RadioData();

    void run(); 
    
    void setSecond(int second);
    void setFrames(int numFrames);
    void setLostFrames(int numLostFrames);

private:
    std::vector <int> seconds;
    std::vector <int> frames;
    std::vector <int> lostFrames;  
    
    void input();
    bool inputSecond(int *second);
    bool inputFrames(int *numFrames);
    bool inputLostFrames(int *numLostFrames, int *numFrames);
    
    void computeErrorRate();
    float getErrorRate(int totalSeconds);
};
