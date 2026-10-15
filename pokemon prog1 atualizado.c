#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[20];
    char tipo;
    int hp, atk, def, spd;
    char golpe1[20]; int pwr1;
    char golpe2[20]; int pwr2;
} PKMN;

//montar as barrinhas de hp com cores
#define VERDE    "\033[32m"
#define AMARELO  "\033[33m"
#define VERMELHO "\033[31m"
#define RESET    "\033[0m"

void barra(int hp, int hp_max) {
    int tam = 20;
    int cheios;
    int pct;
    int i;
    const char *cor;

    if (hp < 0) {
        hp = 0;
    }

    cheios = hp * tam / hp_max; //tipo uma regra de tres para calcular o quanto de hp e perdido na proporcao 

    if (hp > 0 && cheios == 0) {
        cheios = 1;
    }

    pct = hp * 100 / hp_max;

    if (pct > 50) {
        cor = VERDE;
    } else if (pct > 20) {
        cor = AMARELO;
    } else {
        cor = VERMELHO;
    }

    printf("%s[", cor);
    for (i = 0; i < tam; i++) {
        if (i < cheios) {
            printf("#");
        } else {
            printf("-");
        }
    }
    printf("]%s %d/%d\n", RESET, hp, hp_max);
}

void atacar(PKMN *a, PKMN *d, char *n_golpe, int pwr) {
    int dano = (a->atk * pwr / d->def) + (rand() % 6);

    if ((a->tipo == 'F' && d->tipo == 'P') || (a->tipo == 'A' && d->tipo == 'F') || (a->tipo == 'P' && d->tipo == 'A') || (a->tipo == 'E' && d->tipo == 'A')) {
        dano *= 2;
        printf("super effective :D \n");
    } else if ((a->tipo == 'F' && d->tipo == 'A') || (a->tipo == 'A' && d->tipo == 'P') || (a->tipo == 'P' && d->tipo == 'F') || (a->tipo == 'E' && d->tipo == 'P')) {
        dano /= 2;
        printf("Not very effective :( \n");
    }

    d->hp -= dano;
    if (d->hp < 0) {
        d->hp = 0;
    }
    printf("> %s usou %s e causou %d de dano!\n", a->nome, n_golpe, dano);
}

int main() {
    int escolha;
    int i;
    int max1;
    int max2;
    PKMN p1;
    PKMN p2;
    PKMN pokedex[] = {
        {"Charizard", 'F', 180, 60, 40, 100, "Flamethrower", 60, "Scratch", 20},
        {"Blastoise", 'A', 220, 50, 85, 60, "Surf", 40, "Water Gun", 65},
        {"Pikáchu", 'E', 110, 65, 65, 110, "Thundershock", 35, "Thunder", 40},
        {"Jolteon", 'E', 150, 60, 65, 110, "Thundershock", 35, "Quick attack", 20},
        {"Vaporeon", 'A', 190, 55, 75, 80, "Water Gun", 65, "Quick attack", 20},
        {"Flareon", 'F', 100, 60, 35, 50, "Fire Blast", 85, "Quick attack", 20}
    };

    srand(time(NULL));
    system("");   // faz o terminal do Windows entender as cores

    printf("--- POKÉDEX ---\n");
    for (i = 0; i < 6; i++) {
        printf(" %d - %s\n", i + 1, pokedex[i].nome);
    }

    do {
        printf("\nEscolha seu Pokémon pelo número: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 6);

    p1 = pokedex[escolha - 1];
    p2 = pokedex[rand() % 6];
    max1 = p1.hp;
    max2 = p2.hp;

    printf("\n--- É HORA DA BATALHA ---\n%s vs %s!\n", p1.nome, p2.nome);

    while (p1.hp > 0 && p2.hp > 0) {
        int esc1;
        int esc2;
        int golp_pri;
        int golp_seg;
        PKMN *pri;
        PKMN *seg;

        printf("\n%s\n", p1.nome);
        barra(p1.hp, max1);
        printf("%s\n", p2.nome);
        barra(p2.hp, max2);

        printf("1: %s | 2: %s\n> ", p1.golpe1, p1.golpe2);

        esc2 = (rand() % 2) + 1;
        scanf("%d", &esc1);

        pri = (p1.spd >= p2.spd) ? &p1 : &p2;
        seg = (p1.spd < p2.spd) ? &p1 : &p2;

        golp_pri = (pri == &p1) ? esc1 : esc2;
        golp_seg = (seg == &p1) ? esc1 : esc2;

        atacar(pri, seg, golp_pri == 1 ? pri->golpe1 : pri->golpe2, golp_pri == 1 ? pri->pwr1 : pri->pwr2);

        if (seg->hp > 0) {
            atacar(seg, pri, golp_seg == 1 ? seg->golpe1 : seg->golpe2, golp_seg == 1 ? seg->pwr1 : seg->pwr2);
        }
    }

    if (p1.hp > 0) {
        printf("\nVITÓRIA! AGORA VOCE É UM MESTRE POKEMON\n");
    } else {
        printf("\n%s desmaiou... BOA SORTE NA PRÓXIMA PERDEDOR!\n", p1.nome);
    }

    return 0;
}
