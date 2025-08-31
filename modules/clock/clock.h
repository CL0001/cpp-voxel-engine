#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
public:
    static Clock& Instance()
    {
        static Clock instance;
        return instance;
    }

    void Update();
    float GetDeltaTime() const;

private:
    float deltaTime_;

    Clock() = default;
};

#endif // CLOCK_H
