//-----------------------------------------------------------------------------
// a1.c
//
// This program calculates the number of pumps aswell as their Position.
// It is done so that the target can be supplied with eneugh Water.
//
// Group: Michael Hancianu
//
// Author: 11933108
//-----------------------------------------------------------------------------
//
#include <stdio.h>
#include <math.h>
//------------------------------------------------------------------------------
///
/// The main and only program.
/// It reads the input from the user and returns the value.
///
//
int main(void)
{
    int Flow;
    double Loss;
    int Horizont;
    int Vertikal;

 // An infinite loop that only stops when the user has given the right value
 // This gives us the variable Flow as well as calculates variable Loss
  while(1) 
  {
      printf("Erforderlicher Durchfluss [l/min]: ");
      scanf("%d", &Flow);
      if (Flow >= 100 && Flow <=1200)
      {
              if (Flow <= 200)
              {
                  Loss = 0.001;
                  break;
                  }
              else if (Flow <=400 && Flow > 200)
              {
                  Loss = 0.0025;
                  break;
                  }
              else if (Flow <=600 && Flow > 400)
              {
                  Loss = 0.005;
                  break;
                  }
              else if (Flow <=800 && Flow > 600)
              {
                  Loss = 0.01;
                  break;
                  }
              else if (Flow <=1000 && Flow >800)
              {
                  Loss = 0.015;
                  break;
                  }
              else if (Flow > 1000)
              {
                  Loss = 0.025;
                  break;
                  }
      }
      else
      {
          printf("Invalide Eingabe! Der Durchfluss muss mindestens 100 l/min und maximal 1200 l/min betragen.\n");
      }
  }

    // Our second while loop
    // Gives the variable Horizont set by the user
  while(1)
      {
    printf("Horizontale Distanz [m]: ");
    scanf("%d", &Horizont);
    if (Horizont <= 0)
      {
      printf("Invalide Eingabe!\n");
      }
    else{
      break;
        }
      }

    // The third while loop
    // Gives the variable Vertikal set by the user
    while(1){
        printf("Vertikale Distanz [m]: ");
        scanf("%d", &Vertikal);
        if (Vertikal <= 0){
            printf("Invalide Eingabe!\n");
        }
        else{
            break;
        }
    }

    // New variable Alpha is calculated based on variable Horizont and Vertikal
    // All accumulated values are printed
    printf("\nZiel: (%d, %d)\n", Horizont, Vertikal);
    double Alpha = atan(Vertikal/(double)Horizont);
    printf("Neigung [rad]: %0.4f\n", Alpha);
    printf("Durchfluss [l/min]: %d\n", Flow);
    printf("Reibungsbeiwert [bar/m]: %0.4f\n", Loss);

    // New variables are introduced to help us with the function presented below
    int count = 0;
    double y = Vertikal;
    double Pumpe_Vertikal_1 = 0;
    double Pumpe_Vertikal;
    double Pumpe_Horizontal;
    double Pumpe_Horizontal_1 = 0;
    double Pumpe;

    // Fourth and last while loop
    // Here the Number of Pumps as well as their position is calculated
    while(1){
        Pumpe = 10 - ((0.1 * y) + Loss*(y/sin(Alpha))); // Equation for calculating pump pressure
        if (Pumpe < 6) // New pump is added if the pressure is below 6 bar
        {
            count += 1 ;
            Pumpe_Vertikal = 8.5/(0.1 + Loss/sin(Alpha));
            Pumpe_Vertikal_1 += Pumpe_Vertikal;
            Pumpe_Horizontal = Pumpe_Vertikal / tan(Alpha);
            Pumpe_Horizontal_1 += Pumpe_Horizontal;
            y = y - Pumpe_Vertikal;
            if (Pumpe_Horizontal_1 < Horizont)
            {
                printf("  Pumpe%d: (%0.2f, %0.2f)\n", count, Pumpe_Horizontal_1, Pumpe_Vertikal_1);
            }
            else
            {
                printf("  Pumpe%d: (%0.2f, %0.2f)\n", count, (double) Horizont, (double) Vertikal);
                y = 0;
            }
        }
        else
        {
            break;
        }
    }
    if (count == 0)
    {
      printf("  Keine zusaetzliche Pumpe notwendig!\n");
    }
    printf("Austrittsdruck Zielpunkt [bar]: %0.2f\n", Pumpe);
}
