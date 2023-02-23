#include <stdio.h>

/* Zadanie: Napíšte program v jazyku C,
 * ktorý bude simulovať proces pristávania sondy na zvolenom vesmírnom objekte. */

/*
 * m  = Hmotnost sondy (kg).
 * T  = Tah motora (N).
 * v0 = Pociatocna rychlost sondy (m/s).
 * H  = Pociatocna vyska sondy (m).
 * g  = Gravitacne zrychlenie (m/s^2).
 * vsoft = Maximalna povolena rychlost sondy potrebna na bezpecne pristatie (m/s).
 * dt = Casovy krok simulacie (s).
 * df = Optimalna dlzka volneho padu.
 * t  = Uplynuty cas simulacie.
 * h  = Aktualna vyska sondy.
 * v  = Aktualna rychlost sondy.
 * s  = Stav motora (0-vypnuty, 1-zapnuty)
 * total = Vypis celkoveho casu kedy s = 1.
 */

int main()
{
    double m = 0, T = 0, v0 = 0, H = 0, g = 0, vsoft = 0, dt = 0, df, de, A;

    scanf("%lf%lf%lf%lf%lf%lf%lf", &m, &T, &v0, &H, &g, &vsoft, &dt);

    A = T / m;
    df = (A - g) * H / A;
    de = H - df;

    printf("m=%.3lf\n", m);
    printf("T=%.3lf\n", T);
    printf("v0=%.3lf\n", v0);
    printf("H=%.3lf\n", H);
    printf("g=%.3lf\n", g);
    printf("vsoft=%.3lf\n", vsoft);
    printf("dt=%.3lf\n", dt);
    printf("df=%.3lf\n", df);

    double a = 0, t = 0, s, h = H, v = v0, total = 0;

    while (h > 0)
    {
        if (h >= de)
        {
            s = 0;
            a = -g;
        }

        if (v > vsoft)
        {
            s = 0;
            a = -g;
        }

        else if (h <= de && v < vsoft)
        {
            s = 1;
            a = A - g;
            total = total + dt;
        }

        printf("t=%.3lf h=%.3lf v=%.3lf s=%.0lf\n", t, h, v, s);

        h = h + (v * dt) + (a * dt * dt * 0.5);
        v = v + (a * dt);
        t += dt;

        if (h <= 0)
        {
            printf("t=%.3lf h=%.3lf v=%.3lf\n", t, h, v);
            break;
        }
    }
    printf("total=%.3lf", total);
    return 0;
}
