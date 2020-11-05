#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:

//a) dinamièki dodaje novi element na poèetak liste,

//b) ispisuje listu,

//c) dinamièki dodaje novi element na kraj liste,

//d) pronalazi element u listi(po prezimenu),

//e) briše odreðeni element iz liste.

//U zadatku se ne smiju koristiti globalne varijable.

//Prethodnom zadatku dodati funkcije: 
//a) dinamički dodaje novi element iza određenog elementa, 
//b) dinamički dodaje novi element ispred određenog elementa,
//c) sortira listu po prezimenima osoba, 
//d) upisuje listu u datoteku,
//e) čita listu iz datoteke. 


struct _student;
typedef struct _student* Position;

struct _student
{
	char ime[128];
	char prezime[128];
	int godina_rodenja;

	Position Next;
};


void Insert(Position);
void PrintList(Position);
void InsertEnd(Position);
Position FindPrez(Position);
void DeletePrez(Position);

void InsertPrev(Position);
Position FindPrevPrez(Position);
void InsertBefore(Position);
void PrintListToFile(Position);
void ReadListFromFile(Position);
void SortList(Position);
int MemFree(Position);

void main(void)
{
	struct _student head;
	Position studentF = NULL;
	char izbor = 0;

	head.Next = NULL;

	while (izbor != 'K' && izbor != 'k')
	{
		printf("****************************************\r\n");
		printf("****************************************\r\n");
		printf("\r\n");
		printf("\t1. Unos\r\n");
		printf("\t2. Ispis\r\n");
		printf("\t3. Unos na kraj\r\n");
		printf("\t4. Pronadji po prezimenu\r\n");
		printf("\t5. Izbrisi po prezimenu\r\n");
		printf("\t6. dodati iza\r\n");
		printf("\t7. dodati prije\r\n");
		printf("\t8. Ispis u datoteku\r\n");
		printf("\t9. Ucitaj iz datoteke\r\n");
		printf("\tA. Sortiraj\r\n");
		printf("\tK. Izlaz iz programa\r\n");
		printf("****************************************\r\n");
		printf("****************************************\r\n");
		printf("\r\n\tIzbor : \r\n");

		scanf_s("%c", &izbor, 1);

		switch (izbor)
		{
		case '1':
			Insert(&head);
			break;
		case '2':
			PrintList(head.Next);
			break;
		case '3':
			InsertEnd(&head);
			break;
		case '4':
			studentF = FindPrez(head.Next);
			if (studentF != NULL)
				printf("\r\n Trazeni student je: \r\n%s %s %d\r\n", studentF->ime, studentF->prezime, studentF->godina_rodenja);
			else
				printf("\r\n Student nije pronaden");
			break;
		case '5':
			DeletePrez(&head);
			PrintList(head.Next);
			break;
		case '6':
			InsertPrev(&head);
			break;
		case '7':
			InsertBefore(&head);
			break;
		case '8':
			PrintListToFile(&head);
			break;
		case '9':
			ReadListFromFile(&head);
			break;
		case 'A':
			SortList(&head);
			PrintList(head.Next);
			break;
		case 'K':
			MemFree(&head);
			exit(0);
		}
	}
}

void Insert(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(struct _student));

	if (q == NULL)
		printf("\r\n Greska\r\n alokacija memorije neuspjela\r\n");
	else
	{
		printf("unesi ime:\r\n");
		scanf_s(" %s", q->ime, 128);
		printf("unesi prezime:\r\n");
		scanf_s(" %s", q->prezime, 128);
		printf("unesi godina rodenja:\r\n");
		scanf_s(" %d", &q->godina_rodenja);

		q->Next = P->Next;
		P->Next = q;
	}
}



void PrintList(Position P)
{
	if (P == NULL)
		printf("\r\n Lista je PRAZNA!\r\n");
	else
	{
		printf("\r\n ispis liste:\r\n");
		while (P != NULL)
		{
			printf("\t %s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
	}
	printf("\r\n\r\n");
}

void InsertEnd(Position P)
{
	while (P->Next != NULL)
		P = P->Next;
	Insert(P);
}

Position FindPrez(Position P)
{
	char prez[128];

	printf("\r\nUnesite prezime koje trazite : ");
	scanf_s(" %s", prez, 128);
	while (P != NULL & _strcmpi(P->prezime, prez) != 0)
		P = P->Next;
	return P;
}

void DeletePrez(Position P)
{
	Position tmp;

	char prez[128];

	printf("\r\n Unesite prezime za izbrisati: ");
	scanf_s(" %s", prez, 128);

	while (P->Next != NULL & _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	tmp = P->Next;
	if (tmp != NULL)
	{
		P->Next = tmp->Next;
		printf("\r\n Iz liste se brise: %s %s %d", tmp->ime, tmp->prezime, &tmp->godina_rodenja);
		free(tmp);
	}
}

void InsertPrev(Position P)
{
	Position tmp;
	tmp = FindPrez(P);
	if (tmp == NULL)
		printf("\r\n Student nije pronaden");
	else
		Insert(tmp);
}

Position FindPrevPrez(Position P)
{
	char prez[128];

	printf("\r\n unesite prezime koje trazite: ");
	scanf_s("%s", prez, 128);
	while (P->Next != NULL & _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	if (P->Next == NULL)
		P = NULL;
	return P;
}

void InsertBefore(Position P)
{
	Position prev;

	prev = FindPrevPrez(P);
	if (prev == NULL)
		printf("\r\n Student nije pronaden");
	else
		Insert(prev);
}

void PrintListToFile(Position P)
{
	FILE* stream;
	char ime_dat[128];

	printf("\r\n Unesite ime datoteke: ");
	scanf_s(" %s", ime_dat, 128);

	fopen_s(&stream, ime_dat, "w+");
	if (stream == NULL)
		printf("\r\n Datoteka %s nije otvorena za pisanje.", ime_dat);
	else
	{
		while (P != NULL)
		{
			fprintf(stream, "%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
		fclose(stream);
	}
}

void ReadListFromFile(Position P)
{
	FILE* stream;
	char ime_dat[128];
	Position q;

	printf("\r\nUnesite ime datoteke : ");
	scanf_s(" %s", ime_dat, 128);

	fopen_s(&stream, ime_dat, "r");
	if (stream == NULL)
		printf("\r\nDatoteka %s nije otvorena za pisanje.", ime_dat);
	else
	{
		while (!feof(stream))
		{
			q = (Position)malloc(sizeof(struct _student));
			if (q == NULL)
				printf("\r\nGRESKA!\r\nAlokacija memorije neuspjela.\r\n");
			else
			{
				fscanf_s(stream, " %s %s %d", q->ime, 128, q->prezime, 128, &q->godina_rodenja);

				q->Next = P->Next;
				P->Next = q;
			}
		}
		fclose(stream);
	}
}

void SortList(Position P)
{
	Position end = NULL, i, j, prev_j, tmp;

	while (P->Next != end)
	{
		i = P;
		prev_j = i->Next;
		j = prev_j->Next;

		while (j != end)
		{
			if (_strcmpi(prev_j->prezime, j->prezime) < 0)
			{
				prev_j->Next = j->Next;
				i->Next = j;
				j->Next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->Next;
		}
		end = prev_j;
	}
}

int MemFree(Position P)
{
	if (P->Next == NULL)
	{
		free(P);
		return 0;
	}
	else
	{
		P = P->Next;
		MemFree(P);
	}
	return 0;
}