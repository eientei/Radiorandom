#ifndef RADIORANDOM_H
#define RADIORANDOM_H

class radiorandom
{
public:
    radiorandom(int argc, char **argv);

    void execute();

private:
    int m_argc;
    char **m_argv;
};

#endif // RADIORANDOM_H

