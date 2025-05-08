#include "DisplayTXT.h"
#include "winTxt.h"

int main(int argc, char **argv)
{
    termClear();
    Map map;

    txtBoucle(map);

    termClear();
    return 0;
}