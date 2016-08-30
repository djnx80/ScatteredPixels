//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegroStart.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <string>


#define PI 3.14159265

void point(unsigned char *pt, int xx, int yy, unsigned char r, unsigned char g, unsigned char b);
void readPointTab(unsigned char *pt, int sX, int sY, int eX, int eY);
void readPoint(unsigned char *pt, int xx, int yy);
void rysujPXY();
void obliczDXY(int ileKrokow);
bool dodajDelteXY();



using namespace std;

allegroStart mA(800,600);
ALLEGRO_DISPLAY *okno = mA.openWindow();
ALLEGRO_BITMAP  *bitmapa = mA.openBitmap(800,600);
ALLEGRO_BITMAP  *bitmapa1 = mA.openBitmap(800,600);
ALLEGRO_KEYBOARD_STATE klawisz;
ALLEGRO_LOCKED_REGION *lr;
unsigned char *ptr;
//unsigned char red[800][600];
//unsigned char green[800][600];
//unsigned char blue[800][600];

unsigned char red[500000];
unsigned char green[500000];
unsigned char blue[500000];
double pX[500000];
double pY[500000];

int h;
double dX[500000];
double dY[500000];
int ileP=0;
int kroki = 0;
int ktoryKrok = 0;

unsigned char rr,gg,bb;

void *__gxx_personality_v0;


int main()
{
    srand( time( NULL ) );
	bitmapa = al_load_bitmap("fotka.bmp");
	bitmapa1 = al_load_bitmap("fotka.bmp");

    lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
    ptr = (unsigned char *)lr->data;
    al_draw_tinted_bitmap(bitmapa,al_map_rgba(255,255,255,120),0,0,0);
    readPointTab(ptr,0,0,800,600);
    obliczDXY(200);

    al_unlock_bitmap(bitmapa);

    while( !al_key_down( & klawisz, ALLEGRO_KEY_ESCAPE ) )    {

        lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
        ptr = (unsigned char *)lr->data;


		if (dodajDelteXY() == true)  {
//                dodajDelteXY();
		al_clear_to_color(al_map_rgb(0,0,0));

            rysujPXY();
		}
		else    {
	//	al_clear_to_color(al_map_rgb(100,0,0));
				    al_draw_tinted_bitmap(bitmapa1,al_map_rgb(255,255,255),0,0,0);
		}


    //    al_draw_tinted_bitmap(bitmapa1,al_map_rgba(255,255,255,120),0,0,0);
        al_draw_bitmap(bitmapa,0,0,0);
        al_unlock_bitmap(bitmapa);

        al_flip_display();
        al_get_keyboard_state( & klawisz );
        al_rest(0.004);
        }

	return 0;
}

void rysujPXY() {
    double ix,iy;
    for (int n=0; n<ileP; n++)  {
        ix = pX[n];
        iy = pY[n];
        rr = red[n];
        gg = green[n];
        bb = blue[n];
        point(ptr, ix, iy, rr, gg, bb);
    }
}

void obliczDXY(int ileKrokow)    {
    float sX=400,sY=300;
    double ix,iy;

    for (int n=0; n<ileP; n++)  {
        ix = pX[n];
        iy = pY[n];
        sX = (rand () % 600)+100;
        sY = (rand () % 400)+100;
        dX[n] = (sX - ix) / ileKrokow;
        dY[n] = (sY - iy) / ileKrokow;
        pX[n] = sX;
        pY[n] = sY;
    }
    kroki = ileKrokow;
}

bool dodajDelteXY() {
    ktoryKrok++;
    if (ktoryKrok > kroki) return false;
    for (int n=0; n<ileP; n++)  {
        pX[n] = pX[n] - dX[n];
        pY[n] = pY[n] - dY[n];
    }
    return true;

  //  cout <<ktoryKrok<<endl;
}

void point(unsigned char *pt, int xx, int yy,unsigned char r, unsigned char g, unsigned char b) {
    // rysuje pixel w (xx,yy) o kolorze (r,g,b) i alfa=250;
    if (xx<mA.screenW && yy<mA.screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        pt[pixel*4] = r;
        pt[pixel*4+1] = g;
        pt[pixel*4+2] = b;
        pt[pixel*4+3] = 250;
    }
}

void readPointTab(unsigned char *pt, int sX, int sY, int eX, int eY)    {
    // odczytaj pixele do tablicy red/green/blue, start:(sx,sy), koniec:(ex,ey)
    int pixel;
    if (sX<0) sX = 0;
    if (sY<0) sY = 0;
    if (sX>mA.screenW) sX = mA.screenW;
    if (sY>mA.screenH) sY = mA.screenH;
    ileP = 0;

    for (int ix=sX; ix<eX; ix++)    {
        for (int iy=sY; iy<eY; iy++)    {
            pixel = ix+iy*mA.screenW;
            red[ileP]     = pt[pixel*4];
            green[ileP]   = pt[pixel*4+1];
            blue[ileP]    = pt[pixel*4+2];
            pX[ileP] = ix;
            pY[ileP] = iy;
            ileP++;
            // pt[pixel*4+3] - przezroczystosc, alfa
        }
    }
}

void readPoint(unsigned char *pt, int xx, int yy)   {
    // odczytaj 1 pixel z (x,y) i zapisz do zmiennych globalnych (rr,gg,bb)
    if (xx<mA.screenW && yy<mA.screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        rr = pt[pixel*4];
        gg = pt[pixel*4+1];
        bb = pt[pixel*4+2];
//        pt[pixel*4+3] = 250;
    }
}
