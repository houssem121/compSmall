#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CODE_PROGRAM 1
#define CODE_VAR 2
#define CODE_INTEGER 3
#define CODE_CHAR 4
#define CODE_BEGIN 5
#define CODE_END 6
#define CODE_IF 7
#define CODE_THEN 8
#define CODE_ELSE 9
#define CODE_WHILE 10
#define CODE_DO 11
#define CODE_READ 12
#define CODE_READLN 13
#define CODE_WRITE 14
#define CODE_WRITELN 15
#define CODE_ID 16
#define CODE_SEMICOLON 17
#define CODE_OPREL 18
#define CODE_OPADD 19
#define CODE_OPMUL 20
#define CODE_NB 21
#define CODE_PARENTHESIS_LEFT 22
#define CODE_PARENTHESIS_RIGHT 23
#define CODE_EPSILON 24
#define CODE_ASSIGN 25
#define CODE_EOF 26
#define CODE_COLON 27
#define CODE_COMA 28
#define MAX_KEYWORDS 15






















//PARTIE ANALYSEUR LEXICAL



struct Symbole {// Structure d'un symbole
    int UL;
    char att[100];
};
char *keywords[MAX_KEYWORDS] = {"program", "var","integer","char", "begin", "end", "if", "then", "else", "while", "do", "read","readln","write","writeln"};

struct Symbole tableSymbole[100];   // Table des symboles
int idxSym = 0; // Index pour la table des symboles
char chaine[100];
//int debutlex = 0; // Position de début de l'unité lexicale

void Init(char* Chaine) {
    memset(chaine, 0, sizeof(chaine));
}

void Ajouter(char *chaine, char car) {
    while (*chaine) {
        chaine++;
    }

    *chaine = car;
    *(chaine + 1) = '\0';
}
void reculler(FILE *file, int n) {
    fseek(file, -n, SEEK_CUR);
}


struct Symbole* RangerId() {
    for (int i = 0; i < idxSym; i++) {
        if (strcmp(tableSymbole[i].att, chaine) == 0) {// Si le lexeme est trouvé dans la table des symboles
            if (tableSymbole[i].UL == CODE_ID) {// Si le lexeme est un identificateur
                return &tableSymbole[i];
            } else {
                return NULL;// Si le lexeme est un mot clé
            }
        }
    }

    for (int i = 0; i < MAX_KEYWORDS; i++) {// Si le lexeme est un mot clé
        if (strcmp(keywords[i], chaine) == 0) {// Si le lexeme est trouvé dans la table des mots clés
            return NULL;

        }
    }

    //strcpy(tableSymbole[idxSym].att, chaine);
   // tableSymbole[idxSym].UL = CODE_ID;
  //  struct Symbole* newsymbole = &tableSymbole[idxSym];
  //  idxSym++;

  //  return newsymbole;
}

int UniLexId() {
    struct Symbole* entry = RangerId();

    if (entry != NULL) {
        return CODE_ID;
    } else {
        for (int i = 0; i < MAX_KEYWORDS; i++) {
            if (strcmp(keywords[i], chaine) == 0) {
                return i + 1;// Retourner le code du mot clé
            }
        }
    }
}


struct Symbole Return(int unit) {// Retourner un symbole
    struct Symbole symbole;
    symbole.UL = unit;
    strcpy(symbole.att, chaine);
    return symbole;
}
struct Symbole Returns(int unit,char* chaine) {// Retourner un symbole
    struct Symbole symbole;
    symbole.UL = unit;
    strcpy(symbole.att, chaine);
    return symbole;
}

char charsuivant(FILE* file) {
    return fgetc(file);
}

int isletter(char car) {
    return isalpha(car);
}
int ischiffre(char car) {
    return isdigit(car);
}

void Erreur(char *chaine) {
    printf("Erreur lexique à la position %s\n", chaine);
    exit(1);
}

struct Symbole AnalLex(FILE* file) {
    char car;
    int etat = 0;
    struct Symbole symbole;



    while (1) {
        switch (etat) {

            case 0 :
               Init(chaine);
               car=charsuivant(file);
                if (car == ' ' || car == '\t' || car == '\n' ) {
                    etat = 0;
                   // debutlex++;
                }


                else if (car =='*'){//Ajouter(chaine,car);
                    etat=1;
                    }
                else if (car =='/'){//Ajouter(chaine,car);
                etat=2;
                }
                else if (car =='%'){//Ajouter(chaine,car);
                etat=3;
                }
                else if (car =='&'){//Ajouter(chaine,car);
                etat=4;
                }
                else if (car =='+'){//Ajouter(chaine,car);
                 etat=6;
                }
                else if (car =='-'){//Ajouter(chaine,car);
                   etat=7;
                }
                else if (car =='|'){//Ajouter(chaine,car);
                     etat=8;
                 }
                 else if (car =='='){//Ajouter(chaine,car);
                     etat=22;
                 }
                 else if (car =='<'){//Ajouter(chaine,car);
                     etat=19;
                 }
                 else if (car =='>'){//Ajouter(chaine,car);
                     etat=15;
                 }
                 else if (car=='('){//Ajouter(chaine,car);
                    etat=24;
                 }
                else if (car==')'){//Ajouter(chaine,car);
                        etat=277;
                    }
                else if (car=='"' || car =='\''){
                    Ajouter(chaine,car);
                    etat=111;
                 }

                 else if (isletter(car)){
                    Ajouter(chaine,car);
                     etat=11;
                 }
                 else if (ischiffre(car)){
                    Ajouter(chaine,car);
                     etat=13;
                     }
                else if (car == ':' ){
                        //Ajouter(chaine,car);
                        etat=28;

                }
                else if (car ==';'){
                    //Ajouter(chaine,car);
                    etat=31;
                }
                else if (car ==',' ){
                    //Ajouter(chaine,car);
                    etat=32;
                }


            else if (car ==EOF){
                etat=30;

                }
            break;

            case 1:
                symbole=Returns(CODE_OPMUL,"*");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;
                //break;
            case 2:
                symbole=Returns(CODE_OPMUL,"/");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 3:
                symbole=Returns(CODE_OPMUL, "%");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 4:
                car=charsuivant(file);
                if (car=='&'){//Ajouter(chaine,car);
                    etat=5;break;
                }
                else{
                    etat=9;
                }
            case 5:
                symbole=Returns(CODE_OPMUL,"&&");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 6:
                symbole=Returns(CODE_OPADD,"+");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 7:
                symbole=Returns(CODE_OPADD,"-");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;
                //break;

            case 8:
                car=charsuivant(file);
                if(car == '|'){//Ajouter(chaine,car);
                    etat=10;break;}
                else{
                    etat=9;
                }
            case 9:
                Erreur(chaine);
            case 10:
                symbole=Returns(CODE_OPMUL,"||");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 11:
                car=charsuivant(file);
                if (isletter(car) || ischiffre(car)){
                    Ajouter(chaine,car);
                    etat=11;break;
                }

                else{
                    etat=12;
                }


            case 12:
                reculler(file,1);
                symbole=Return(UniLexId());
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 13:
                car=charsuivant(file);
                if (ischiffre(car)){
                    Ajouter(chaine,car);
                    etat=13;break;
                }
                else {
                    etat=14;break;
                }
            case 14:
                reculler(file,1);
                symbole = Return(CODE_NB);
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 15:
                car=charsuivant(file);
                if (car == '='){
                    //Ajouter(chaine,car);
                    etat=16;break;
                }
                else if (car == '>'){//Ajouter(chaine,car);
                    etat=9;break;
                }
                else{
                    etat=18;break;
                }
            case 16:
                symbole=Returns(CODE_OPREL,">=");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 17:
                symbole=Returns(CODE_OPREL ,"<>");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 18:
                reculler(file,1);
                symbole=Returns(CODE_OPREL,">");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 19:
                car=charsuivant(file);
                if (car == '='){
                    //Ajouter(chaine,car);
                    etat=20;break;
                }
                else if (car == '>'){//Ajouter(chaine,car);
                    etat=17;break;
                }

                else{
                    etat=21;break;
                }
            case 20:
                symbole=Returns(CODE_OPREL,"<=");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 21:
                reculler(file,1);
                symbole=Returns(CODE_OPREL, "<");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 22:
                car=charsuivant(file);
                if (car == '='){
                    //Ajouter(chaine,car);
                    etat=23;break;
                }
                else{
                    etat=9;break;
                }
            case 23:
                symbole=Returns(CODE_OPREL,"==");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 24:
                car=charsuivant(file);

                if (car == '*'){
                    etat=25;break;
                }
                else {
                    etat=42;
                    break;
                }


            case 25:
                car=charsuivant(file);
                if (car == '*'){
                    etat=26;break;
                }
                else{
                    etat=25;break;
                }
            case 42:
                reculler(file,1);
                symbole=Returns(CODE_PARENTHESIS_LEFT,"(");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;


            case 26:
                car=charsuivant(file);
                if (car == ')'){
                    //Ajouter(chaine,car);
                    etat=27;break;
                }
                else{
                    etat=25;break;
                }
            case 27:
               etat=0;
               break;
            case 277:

                symbole=Returns(CODE_PARENTHESIS_RIGHT,")");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;

            case 28:
                car=charsuivant(file);
                if (car == '='){
                    //Ajouter(chaine,car);
                    etat=29;break;
                }
                else{
                    etat=33;break;
                }
            case 29:
                symbole=Returns(CODE_ASSIGN,":=");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 30:
                symbole=Returns(CODE_EOF,".");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 31:
                symbole=Returns(CODE_SEMICOLON,";");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 33:
                reculler(file,1);
                symbole=Returns(CODE_COLON,":");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;
            case 32:
                symbole=Returns(CODE_COMA,",");
                tableSymbole[idxSym]=symbole;
                idxSym++;
                return symbole;//break;

            case 111:
               car = charsuivant(file);
                while (isletter(car) || ischiffre(car) || car == ' ' || car == '\t' || car == '\n') {
                 Ajouter(chaine, car);
                 car = charsuivant(file);
               }
               if (car == '"' || car == '\'') {
                Ajouter(chaine, car);
                etat = 112;
               } else {
                 etat=9;
               }

           case 112:
             // reculler(file,1);
              symbole = Return(CODE_ID);
              tableSymbole[idxSym] = symbole;
              idxSym++;
              return symbole;








        }
    }






}

//PARTIE ANALYSEUR SYNTAXIQUE
void ajouter_variable(char* id, int type);
int chercher_variable(char* id);
void add_list_of_type(char* id,int type);
void samelisteappend(char* id);
void p(FILE* file);
void DCL(FILE* file);
void dcl(FILE* file);
void List_id(FILE* file);
void listid(FILE* file);
void type(FILE* file);
void inst_composee(FILE* file);
void inst(FILE* file);
void List_inst(FILE* file);
void listinst(FILE* file);    // List_inst'
void I(FILE* file);
void Exp(FILE* file);
void eexp(FILE* file);
void Exp_simple(FILE* file);
void exp_simple(FILE* file);
void Terme(FILE* file);
void terme(FILE* file);
void Facteur(FILE* file);
void facteur(FILE* file);



//structure and variables

int sortiecounter=0;
struct Symbole symbole;
struct VariableEntry {
    char identifier[100];
    int type;
};
struct VariableEntry variableTable[100];
int idxVar = 0;
int typeo;
char* list[100];
int idxListVar = 0;

#define TYPE_MIXED -1 // Used to indicate that the types are mixed
#define TYPE_UNKNOWN 0 // Used to indicate that the type is unknown
int lastExpressionType = TYPE_UNKNOWN;
//implementation
int type_of_last_expression() {
    return lastExpressionType;
}
void updateLastExpressionType(int newType) {
    if (lastExpressionType == TYPE_UNKNOWN) {
        lastExpressionType = newType;
    } else if (lastExpressionType != newType) {
        lastExpressionType = TYPE_MIXED;
    }
}
int recherche(char* id) {
    for (int i = 0; i < idxVar; i++) {
        if (strcmp(variableTable[i].identifier, id) == 0) {
            return variableTable[i].type;
        }
    }
    return -1;
}
int compatible(int type1, int type2) {
    if (type1 == type2) {
        return 1;
    } else if (type1 == CODE_INTEGER && type2 == CODE_CHAR) {
        return 0;
    } else if (type1 == CODE_CHAR && type2 == CODE_INTEGER) {
        return 0;
    } else {
        return 0;
    }
}
void symbole_suivant(FILE* file) {
    symbole = AnalLex(file);
}

void erreur() {
    printf("Error\n");
    exit(1);
}

void accepter_id(FILE* file) {
    if (symbole.UL == CODE_ID) {
        symbole_suivant(file);
    } else {
        erreur();
    }
}

void accepter(char *s, FILE* file) {
    if (strcmp(symbole.att, s) == 0) {
        symbole_suivant(file);
    } else {
        erreur();
    }
}


void ajouter_variable(char* id, int type) {
    strcpy(variableTable[idxVar].identifier , id);
    variableTable[idxVar].type = type;
    idxVar++;
}

int chercher_variable(char* id) {
    for (int i = 0; i < idxVar; i++) {
        if (strcmp(variableTable[i].identifier, id) == 0) {
            return variableTable[i].type;
        }
    }
    return -1;
}

//list of variables same type //

void samelisteappend(char* id) {
    list[idxListVar]=id;
    idxListVar++;
}
void add_list_of_type(char* id,int type){
    for(int i=0;i<idxListVar;i++){
        ajouter_variable(list[i],type);
    }
    idxListVar=0;
}
//***///



void p(FILE* file) {
    accepter("program", file);
    accepter_id(file);
    accepter(";", file);
    DCL(file);
    inst_composee(file);
    accepter(".", file);
}

void DCL(FILE* file) {
    dcl(file);
}

void dcl(FILE* file) {
    if (strcmp(symbole.att, "var") == 0) {
        accepter("var", file);
        List_id(file);
        accepter(":", file);
        type(file);
        accepter(";", file);
        add_list_of_type(list,typeo);//add list of variables same type
        dcl(file);


    }
}

void List_id(FILE* file) {
    //ajouter
    char* id=tableSymbole[idxSym-1].att;
    samelisteappend(id);
    accepter_id(file);
    listid(file);
}

void listid(FILE* file) {
    if (strcmp(symbole.att, ",") == 0) {
    accepter(",", file);
    //ajouter
    char* id=tableSymbole[idxSym-1].att;
    samelisteappend(id);
    accepter_id(file);
    listid(file);
    }
}

void type(FILE* file) {
    if (strcmp(symbole.att,"integer") == 0) {
        accepter("integer", file);
        typeo = CODE_INTEGER;
    } else if (strcmp(symbole.att, "char") == 0) {
        accepter("char", file);
        typeo = CODE_CHAR;

    } else {
      erreur();
      //return 0;
    }
}

void inst_composee(FILE* file) {
    accepter("begin", file);
    inst(file);
    accepter("end", file);
    accepter(".",file);
}

void inst(FILE* file) {
    List_inst(file);
}

void List_inst(FILE* file) {
    I(file);
    listinst(file);
}

void listinst(FILE* file) {
    if (strcmp(symbole.att, ";") == 0) {
     accepter(";", file);
        I(file);
        listinst(file);
    }
}

FILE* file0;
FILE* file1;
void emettre(const char* valgdempl, const char* var, const char* valeur, const int sortie) {
      //FILE* file = fopen("CODE.txt", "a");// Use "a" to append to the file instead of overwriting

    if (file1 == NULL) {
        perror("Error opening file");
        exit(1);
    }

    if (valgdempl != NULL && var != NULL && valeur == NULL) {
        fprintf(file1, "%s  %s\n", valgdempl, var);
    } else if (valgdempl != NULL && var == NULL && valeur != NULL) {
        fprintf(file1, "%s  %s\n", valgdempl, valeur);
    } else if (var != NULL && valeur == NULL) {
        fprintf(file1, "%s\n", var);
    }

    else   {
        fprintf(file1, "%s %d\n",valgdempl ,sortie);
    }



 //   fclose(file);
}
int sortie(){
    return  sortiecounter++;
}
void I(FILE* file) {
    if (symbole.UL == CODE_ID) {
        char* id = symbole.att;
        int idType = recherche(id);
        if (idType == -1) {
            // Handle error: variable not found in the table
            printf("Error: Variable '%s' not declared.\n", id);
            erreur();
        } else {
            emettre("Valeurg",id, NULL, 0);
            accepter_id(file);
            accepter(":=", file);
            Exp_simple(file);
            emettre(NULL,":=", NULL, 0);
            int expType = type_of_last_expression();  //  track the type of the last expression
            if (!compatible(idType, expType)) {
                 printf("Error: Type mismatch for variable .\n");
                erreur();
            }
          lastExpressionType = TYPE_UNKNOWN;

        }
    } else if (strcmp(symbole.att, "if") == 0) {
        accepter("if", file);
        Exp(file);
        int sorties = sortie();
        emettre("Allersifaux",NULL,NULL, sorties);
        accepter("then", file);
        I(file);
        emettre("Etiq",NULL,NULL, sorties);

    } else if (strcmp(symbole.att, "else") == 0) {
        accepter("else", file);
        I(file);

    } else if (strcmp(symbole.att, "while") == 0) {
        accepter("while", file);
        int test = sortie();
        emettre("Etiq",NULL,NULL, test);
        Exp(file);
        
        int sorties = sortie();
        emettre("Allersifaux",NULL,NULL, sorties);
        accepter("do", file);
        I(file);
        emettre("Alle à",NULL,NULL, test);
        emettre("Etiq",NULL,NULL, sorties);
    } else if (strcmp(symbole.att, "read") == 0) {
        accepter("read", file);
        accepter("(", file);
        char* id = symbole.att;
        int idType = recherche(id);
        if (idType == -1) {
            printf("Error: Variable '%s' not declared.\n", id);
            erreur();
        } else {
            accepter_id(file);
            accepter(")", file);
        }
       // accepter_id(file);
    } else if (strcmp(symbole.att, "readln") == 0) {
        accepter("readln", file);
        accepter("(", file);
        char* id = symbole.att;
        int idType = recherche(id);
        if (idType == -1) {
            printf("Error: Variable '%s' not declared.\n", id);
            erreur();
        } else {
            accepter_id(file);
            accepter(")", file);
        }
    } else if (strcmp(symbole.att, "write") == 0) {
        accepter("write", file);
        accepter("(", file);
       char* id = symbole.att;
        int idType = recherche(id);
        if (idType == -1) {
            printf("Error: Variable '%s' not declared.\n", id);
            erreur();
        } else {
            accepter_id(file);
            accepter(")", file);
        }
    } else if (strcmp(symbole.att, "writeln") == 0) {
        accepter("writeln", file);
        accepter("(", file);
       char* id = symbole.att;
        int idType = recherche(id);
        if (idType == -1) {
            printf("Error: Variable '%s' not declared.\n", id);
            erreur();
        } else {
            accepter_id(file);
            accepter(")", file);
        }
    }

}
int leftType;
int rightType;


void Exp(FILE* file) {
    Exp_simple(file);
    leftType = type_of_last_expression();// Get the type of the left expression
    lastExpressionType = TYPE_UNKNOWN;//added last time
    eexp(file);
}

void eexp(FILE* file) {
    if (strcmp(symbole.att, "==") == 0 || strcmp(symbole.att, "<") == 0 ||
        strcmp(symbole.att, ">") == 0 || strcmp(symbole.att, "<=") == 0 ||
        strcmp(symbole.att, ">=") == 0 || strcmp(symbole.att, "<>") == 0) {
        char* op = tableSymbole[idxSym-1].att;

        accepter(symbole.att, file);
        Exp_simple(file);
        if (strcmp(op, "==") == 0) {
            emettre("Comparer-si-égal",NULL,NULL, 0);
          }
        else if (strcmp(op, "<") == 0) {
           emettre("Comparer-si-inférieur",NULL,NULL,   0);
        }
        else if (strcmp(op, ">") == 0) {
              emettre("Comparer-si-supérieur",NULL,NULL,0);}
          else if (strcmp(op, "<=") == 0) {
                emettre("Comparer-si-inférieur-ou-égal",NULL,NULL,0);}
            else if (strcmp(op, ">=") == 0) {
                emettre("Comparer-si-supérieur-ou-égal",NULL,NULL,0);}
            else if (strcmp(op, "<>") == 0) {
                emettre("Comparer-si-différent",NULL,NULL,0);

                 }
        rightType = type_of_last_expression(); // Get the type of the right expression

         //Type verification
        if ((leftType == CODE_INTEGER && rightType == CODE_INTEGER) || (leftType == CODE_CHAR && rightType == CODE_CHAR)) {
                lastExpressionType = TYPE_UNKNOWN;
       } else {
              printf("Error: Type mismatch for expression '%s'.\n", op);
              erreur();
          }




    }
}

void Exp_simple(FILE* file) {
    Terme(file);
    exp_simple(file);
}

void exp_simple(FILE* file) {
    if (strcmp(symbole.att, "+") == 0 || strcmp(symbole.att, "-") == 0 ||
        strcmp(symbole.att, "||") == 0) {
        char* op = tableSymbole[idxSym-1].att;
        accepter(symbole.att, file);
        Terme(file);
        exp_simple(file);
        emettre(NULL,op,NULL,0);
    }
}

void Terme(FILE* file) {
    Facteur(file);
    terme(file);
}

void terme(FILE* file) {
    if (strcmp(symbole.att, "*") == 0 || strcmp(symbole.att, "/") == 0 ||
        strcmp(symbole.att, "&&") == 0) {
        char* op = tableSymbole[idxSym-1].att;
        accepter(symbole.att, file);
        Facteur(file);
        terme(file);
        emettre(NULL,op,NULL,0);

    }
}

void Facteur(FILE* file) {
    if (symbole.UL == CODE_ID) {
        int idType = recherche(symbole.att);
        //char* id = symbole.att;
        //emettre("Valeurd",id, NULL);
        if (idType == -1) {
            // Handle error: variable not found in the table
            printf("Error: Variable '%s' not declared.\n", symbole.att);
            erreur();

        }else{
            emettre("Valeurd",symbole.att, NULL,0);
            accepter_id(file);
            updateLastExpressionType(idType);
        }
    } else if (symbole.UL == CODE_NB) {
        emettre("Empiler",NULL,symbole.att,0);
        accepter(symbole.att, file);
        updateLastExpressionType(CODE_INTEGER);
    } else if (strcmp(symbole.att, "(") == 0) {
        accepter("(", file);
        Exp_simple(file);
        accepter(")", file);
    }
    else{
        erreur();
    }
}

int main() {
    file0 = fopen("houssem.txt", "r");
   file1 = fopen("CODE.txt", "w");

    if (file0 == NULL) {
        perror("error file cant be opened");
        return 1;
    }

    symbole_suivant(file0);
    p(file0);
    //printf all lines from file1 
    //the intermediate code from file0 is 
    printf("Intermediate code:\n");
    printf("from code file:\n ");
    printf("---------------\n");
    char c1;
    fseek(file0, 0, SEEK_SET);
    while((c1 = fgetc(file0)) != EOF) {
        printf("%c", c1);
    }
    printf("---------------\n");
    char c;
    fseek(file1, 0, SEEK_SET);
    FILE* file2 = fopen("CODE.txt", "r");
    while ((c = fgetc(file2)) != EOF) {
        printf("%c", c);
    }


    fclose(file0);
    fclose(file1);
    return 0;
}
