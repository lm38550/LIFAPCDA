#ifndef WINTXT_H
#define WINTXT_H
#include <string.h>

//! \brief une fen�tre texte est un tableau 2D de caract�res
class WinTXT
{
private:
    int dimx;  //!< \brief largeur
    int dimy;  //!< \brief heuteur
    char *win; //!< \brief stocke le contenu de la fen�tre dans un tableau 1D mais on y accede en 2D
    int *c;
    int *bg;

public:
    WinTXT(int dx, int dy);
    void clear(char c = ' ');
    void print(int x, int y, char c);
    void print(int x, int y, char *c);
    void color(int x, int y, int c, int bg);
    void draw(int x = 0, int y = 0);
    void pause();
    char getCh();
};

void termClear();

#endif
