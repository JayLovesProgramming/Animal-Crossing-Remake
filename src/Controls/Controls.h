// Controls/Controls.h
#pragma once

class GameControls
{
public:
    inline static bool nearTree;

    static void UpdateControls(Vector3 *characterPos, float characterSpeed);


private:
    inline static int animFrameCounter = 0;
};
