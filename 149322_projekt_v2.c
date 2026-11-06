#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* rozsirenie pre lahsiu pracu s stringami */

void v_x(){
    printf("V: Nespravna volba vypisu\n");
}

/* treba davat adresy suborov do funkcie "pointer na pointer" aby sa pripadna hodnota NULL zmenila aj v main */
void v1(FILE **s1,FILE **s2) { 
    /* Kontrolavanie / otvaranie suborov*/
    if(*s1 == NULL) {
        *s1=fopen("zoznamCK.txt","r");
    }
    if(*s2 == NULL) {
        *s2=fopen("checkin1.txt","r");
    }
    if(*s1 == NULL || *s2 == NULL ) {
        printf("V1: Neotvorene txt subory\n");
        return; 
    }

    /* vypysovanie udajov zo suboru */
    char *riadok,*let,*meno,*priezvisko,*sedadlo,*vek;
    int i = 0;

    /*nacitanie pamati +1 miesto pre znak ukoncovania stringu*/
    riadok = malloc(27*sizeof(char)); /* +1 pretoze fgets nacitava aj \n a az potom da \0 */
    let = malloc(7*sizeof(char));
    meno = malloc(16*sizeof(char));
    priezvisko = malloc(26*sizeof(char));
    sedadlo = malloc(4*sizeof(char));

    /* zaujima ma len 2026 - rok narodenia takze len 4 + 1 miest*/
    vek = malloc(5*sizeof(char));

    while(fgets(riadok,27,*s1)!=NULL){
        /* pre pripad prazdneho riadku ho cyklus "preskoci" */
        if(riadok[0]=='\n'){
            continue;
        }
        /* kontroluje ci necitam novy zaznam ak ano resetuje mi cyklus ( i = 0; )*/
        if(riadok[0]=='#'){
            i = 0;
            continue;
        }
        /* prejde moj string a pri 1. naleze '\n' ho nahradi '\0' aby som vedel lepsie manipulovat s tymto stringom*/
        riadok[strcspn(riadok, "\n")] = '\0';
        
        
        if(i==0){ 
            strcpy(let,riadok);     /* kopiruje string */
        }
         if(i==1){
            strcpy(meno,riadok);
        }
         if(i==2){
            strcpy(priezvisko,riadok);
        }
         if(i==3){
            for(int i = 0;i<5;i++) {
                vek[i] = riadok[i+4];
            }
        }
        if(i==4){
            strcpy(sedadlo,riadok);
        }
        /* kedze ma batozina nezaujima mozem rovno tlacit stringy a nechat prebehnut cyklus na prazdno*/
        if(i==5){
            /*atoi mi string zmeni na TYP int */
            printf("Oznacenie letu: %s\nMeno a Priezvisko [vek] %s %s [%d]\nOznacenie sedadla: %s\n\n",let,meno,priezvisko,2026-atoi(vek),sedadlo);
        }
        i+=1;
    }
    rewind(*s1); /* Vrati ma na zaciatok suboru*/
    free(riadok);
    free(meno);
    free(let);
    free(priezvisko);
    free(sedadlo);
    free(vek);
}

void v2(void *p1,void *p2){
    if(p1 == NULL || p2 == NULL ){
        printf("Nenaplnene polia");
    }
}

int v(FILE **s1,FILE **s2,void ***p1,void ***p2){
    int cisloPrikazu;
    scanf("%d",&cisloPrikazu);
    if(cisloPrikazu==1){
        v1(s1,s2);
    }
    if(cisloPrikazu==2){
        v2(p1,p2);
    }
    else{
        v_x();
    }
}
void zorad(int *p1,char *p2,int dlzka){
    
    int cislo;
    char pismeno;

    /* buble sort :3 */

    for(int j = 0;j<(dlzka-1);j++){
        for(int i = 0;i<(dlzka-1-j);i++){  /* -1 pretoze p1[i+1] by pretieklo pri i = dlzka , a -j preto lebo vzdy to (v mojom pripade) najmensie cislo skonci na konci a preto ho uz nemusime riesit */
            if(p1[i]<p1[i+1]){

                /* zoradenie pocetnosti*/
                cislo = p1[i];
                p1[i] = p1[i+1];
                p1[i+1] = cislo;

                /*sucasne rovnako zoradujem aj prislusne znaky*/
                pismeno = p2[i];
                p2[i] = p2[i+1];
                p2[i+1] = pismeno;
            }
        }
    }
}

/* vynuluje mi pole po danu dlzku*/

void nuluj(int *p1,int dlzka){ 
    for(int i = 0;i<dlzka;i++){
        p1[i] = 0;
    }
}
void n(FILE *s1,FILE *s2) {

    /*check ci je subor1 otvoreny ,alebo teda ci bol vykonany prikaz v_1 */

    if(s1 == NULL) {      
        printf("H: Neotvoreny subor\n");
    }

}
void h(FILE *s1) {

    /*check ci je subor1 otvoreny ,alebo teda ci bol vykonany prikaz v_1 */

    if(s1 == NULL) {      
        printf("H: Neotvoreny subor\n");
    }

    else {
        int *malePismena,*velkePismena,*cisla;
        char znak;
        char poradieABC[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char poradie123[] = "0123456789";

        /* polia pre pocetnost */

        malePismena = malloc(26*sizeof(int)); 
        velkePismena = malloc(26*sizeof(int)); 
        cisla = malloc(10*sizeof(int));

        /* vycistenie polií */

        nuluj(malePismena,26);
        nuluj(velkePismena,26);
        nuluj(cisla,10);

        /* pocitanie znakov po koniec suboru (EOF) */

        while(znak!=EOF){
            while ((znak = fgetc(s1)) != EOF) {
                if(znak>='A' && znak<= 'Z'){
                    velkePismena[znak-'A'] += 1;
                }
                else if(znak>='a' && znak<= 'z'){
                    malePismena[znak-'a'] += 1;
                    
                }
                else if(znak>='0' && znak<= '9') {
                    cisla[znak-'0'] += 1;
                }
            }
            
        }

        /* Vypis pocetnosti s dodrzanim formatu */

        zorad(velkePismena,poradieABC,26);

        for(int i = 0;i<26;i++){
            if(velkePismena[i]!=0){
                printf("%c : %d\n",poradieABC[i],velkePismena[i]);
            }
        }

        for(int i = 0;i<26;i++){
            if(malePismena[i]!=0){
                printf("%c : %d\n",('a'+i),malePismena[i]);
            }
        }

        zorad(cisla,poradie123,10);

        for(int i = 0;i<10;i++){
            if(cisla[i]!=0){
                printf("%c : %d\n",poradie123[i],cisla[i]);
            }
        }

        free(malePismena);
        free(velkePismena);
        free(cisla);
    }
    rewind(s1); /* Vrati ma na zaciatok suboru*/
}


int main(void) {

    char prikaz;
    
    /* inicializacia hodnot suborov na NULL */
    FILE *subor1,*subor2;
    subor1 = NULL;
    subor2 = NULL;
    void **pole1,**pole2;
    pole1 = NULL;
    pole2 = NULL;
    
    while(scanf(" %c",&prikaz) == 1){

        if(prikaz =='v') { 
            v(&subor1,&subor2,&pole1,&pole2);
        }
        if(prikaz=='h'){
           h(subor1);
        }
    }
}