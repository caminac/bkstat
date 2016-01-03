#ifndef IFVIEWER_H
#define IFVIEWER_H

class ifViewer
{
public:
    virtual void UpdateScoreboard(int item, int value, int player_index = 0) = 0;
};

#endif // IFVIEWER_H
