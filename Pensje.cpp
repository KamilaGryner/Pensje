#include <cstdio>
using namespace std;

const int MAXN = 1000010;

int n; // ilosc pracownikow
int przelozony[MAXN];
int pensja[MAXN]; 
int uzyte[MAXN]; // wartosci uzyte
int ile_podwladnych[MAXN];
int stopien[MAXN];
int podwladny[MAXN]; // bezposredni (jezeli tylko jeden)
int kolejka[MAXN], pocz = 0, kon = 0;

void policz_podwladnych() {
    for (int i = 1; i < n; ++i) stopien[i] = 0;

    for (int i = 1; i < n; ++i)     // ilosc bezposrednich
        ++stopien[przelozony[i]]; 

    for (int i = 1; i < n; ++i)
        if (stopien[i] == 0)
            kolejka[kon++] = i;
    while (pocz < kon) {
        int akt = kolejka[pocz++];
        int przel = przelozony[akt];
        if (pensja[akt] == 0) {
            if (!--stopien[przel]) kolejka[kon++] = przel;
            ile_podwladnych[przel] += ile_podwladnych[akt] + 1;
        }
    }
}

void oznacz_uzyte_pensje() {
    for (int i = 1; i < n; ++i)
        if (pensja[i])
            uzyte[pensja[i]] = i;
        else if (!podwladny[przelozony[i]])
            podwladny[przelozony[i]] = i;
        else podwladny[przelozony[i]] = -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", przelozony + i, pensja + i);
        if (przelozony[i] == i) pensja[i] = n;
        if (pensja[i]) przelozony[i] = n + 1;
    }

    ++n;
    przelozony[n] = n;
    pensja[n] = n;
    policz_podwladnych();
    oznacz_uzyte_pensje();
    int i = 0;
    int ile_wolnych = 0, ile_mozliwych = 0;

    while (i < n - 1) {
        while (i < n - 1 && uzyte[i + 1] == 0) { ++i; ++ile_wolnych; ++ile_mozliwych; }
        while (i < n - 1 && uzyte[i + 1] != 0) {
            ++i;
            int akt = uzyte[i], l = i;
            ile_wolnych -= ile_podwladnych[akt];
            if (ile_wolnych == 0) {
                while (ile_mozliwych-- && podwladny[akt] > 0) {
                    while (uzyte[l]) --l;
                    akt = podwladny[akt];
                    pensja[akt] = l;
                    uzyte[l] = akt;
                }
                ile_mozliwych = 0;
            }
            if (ile_podwladnych[akt] != 0)
                ile_mozliwych = 0;
        }
    }

    for (int i = 1; i < n; ++i)
        printf("%d\n", pensja[i]);
    return 0;
}
