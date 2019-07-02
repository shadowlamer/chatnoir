int main()
{
    unsigned char *screen = (unsigned char *)0x4000;
    unsigned int screenOffset;

    for ( screenOffset = 0x0000; screenOffset < 0x1800; screenOffset++ )
    {
	screen[screenOffset] = 0xaa;
    }

    return 0;
}
