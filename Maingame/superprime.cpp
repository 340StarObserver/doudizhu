// superprime v0.3cpp

#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef unsigned int uint;

enum prmode
{ cpu, ram };
enum errtype
{ opt, op_v, f_err, mem };
prmode mode = cpu;
bool stf = false;
bool oflag = false;
char file[256];
char kbd[10];
time_t tm1, tm2;
ofstream f;
clock_t tick1, tick2;

void err(errtype error, char errval[]);
void cputest(uint m);
void ramtest(uint m);
void help(void);


/* in some complier(e.g. C4droid), string.h hasn't got function void strlwr
   (char* s),so I write this. */
// for linux
/*void strlwr(char *s)
{
    uint len = strlen(s);
    for (uint poi = 0; poi < len; poi++)
    {
        if (s[poi] > 0x40 && s[poi] < 0x5b)
            s[poi] += 0x20;
    }
}
*/




int main(int argc, char *argv[])
{

    uint max = 1048575;
    cout << "SuperPrime v0.3cpp (c)ZchSoft 160327" << endl;

    if (argc == 1)
    {
        help();

        cout << "Using default setting?(Y/N)";
        cin >> kbd;
        strlwr(kbd);
        if (kbd[0] == 'n')
        {
            cout << "CPU Mode/RAM Mode?(C/R)";
            cin >> kbd;
            strlwr(kbd);
            if (kbd[0] == 'r')
                mode = ram;

            cout << "Output to flie?(Y/N)";
            cin >> kbd;
            strlwr(kbd);
            if (kbd[0] == 'y')
            {
                oflag = true;
                cout << "File name:";
                cin >> file;
            }

            cout << "Upper limit?( Suggest 1048575)";
            cin >> kbd;
            max = atoi(kbd);
        }
    }
    else
    {
        for (int k = 1; k < argc; k++)
        {
            if ((argv[k][0] == '-' || argv[k][0] == '/') && strlen(argv[k]) == 2)
                switch (argv[k][1])
                {
                case 'c':
                    mode = cpu;
                    break;

                case 'r':
                    mode = ram;
                    break;

                case 'f':
                    oflag = true;
                    k++;
                    if (!(argv[k][0] == '-' || argv[k][0] == '/' && strlen(argv[k]) == 0))
                        strcpy(file, argv[k]);
                    else
                        err(op_v, argv[k]);
                    break;

                case 'u':
                    k++;
                    if (!(argv[k][0] == '-' || argv[k][0] == '/' && strlen(argv[k]) == 0))
                         max = atoi(argv[k]);
                    break;

                case 'h':
                    help();
                    exit(0);
                    break;

                default:
                    err(opt, argv[k]);
                    break;
                }
        }
    }
    cout << "Start" << endl;

    tick1 = clock();
    switch (mode)
    {
    case cpu:
        cputest(max);
        break;

    case ram:
        ramtest(max);
        break;
    }


    tick2 = clock();
    cout << "Finish in " << 1.00 * (tick2 - tick1) / CLOCKS_PER_SEC << " second" << endl;

    // for windows:
    system("pause");

    return 0;
}

void cputest(uint m)
{
    if (oflag)
        f.open(file);

    vector < uint > pr(8192);
    uint prpoi = 0, poi, subpoi, tmp;

    pr[prpoi] = 2;
    prpoi++;

    for (poi = 3; poi <= m; poi++)
    {
        if (prpoi == pr.size())
        {
            pr.resize(prpoi + 8192);
        }
        subpoi = 0;
        tmp = poi / 2;
        while (pr[subpoi] < tmp)
        {
            if (poi % pr[subpoi] == 0)
                break;
            subpoi++;
        }
        if (pr[subpoi] >= tmp)
        {
            f << poi << endl;
            pr[prpoi++] = poi;
        }
    }
}


void ramtest(uint m)
{
    if (oflag)
        f.open(file);

    char emptystr[] = " ";
    bool *is = new bool[m + 1];
    if (is == NULL)
        err(mem, emptystr);
    cout << "Memory allowcation OK" << endl;

    uint poi, fpoi, n, ctr;

    // initlize the array:0 and 1 isn't prime
    for (poi = 0; poi < m; poi++)
        is[poi] = true;
    is[0] = false;
    is[1] = false;

    // scan start from0
    for (poi = 0; poi < m; poi++)
    {
        // on found a prime
        if (is[poi])
        {

            n = m / poi;
            fpoi = (poi << 1);
            f << poi << endl;

            // int n*poi isn't prime
            for (ctr = 1; ctr < n; ctr++)
            {
                is[fpoi] = false;
                fpoi += poi;
            }
        }
    }
}




void err(errtype error, char errval[])
{
    cout << "ERROR:";
    switch (error)
    {
    case opt:
        cout << "Invalid option:";
        break;

    case op_v:
        cout << "Invalid option value:";
        break;

    case f_err:
        cout << "Cannot open file:";
        break;

    case mem:
        cout << "Memory allowcation failed.";
        break;
    }
    cout << errval << endl;
    exit(-1);
}


void help(void)
{
    cout << "Usage: superprime [-c|-r] [-f FILE] [-u UPPER_LIMIT] [-h]" << endl;
    cout << "-c: CPU test(default)" << endl;
    cout << "-r: RAM test(quicker)" << endl;
    cout << "-f: Output to FILE" << endl;
    cout << "-u: Set UPPER_LIMIT(default:1048575)" << endl;
    cout << "-h: Show this help" << endl;
}
