#include <stdio.h>

enum animal { Dog, Cat, Cow, invalid};

void dog(void)
{
    printf("ワンワン\n");
}

void cat(void)
{
    printf("ニャーニャー\n");
}

void cow(void)
{
    printf("モーー\n");
}

enum animal select(void)
{
    int animal;
    do {
        printf("動物を選んで下さい。(0..dog, 1..cat, 2..cow, 3..quit):");
        scanf("%d", &animal);
    } while (animal < Dog || animal > invalid);
    return animal;
}

int main(void)
{
    enum animal selected;
    do {
        switch (selected = select())
        {
            case Dog: dog(); break;
            case Cat: cat(); break;
            case Cow: cow(); break;
        }
    } while (selected != invalid);

    return 0;
}
