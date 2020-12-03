#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

// Napisati program koji pomoæu vezanih listi simulira rad:
//a) stoga,
//b) reda.
//Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 - 100.

#define min 10
#define max 100

struct node;
typedef struct node* position;

struct node {
	int element;
	position next;
};

int GetValueFromRange(int, int);
void PushRow(position, int);
void PushStack(position, int);
void Pop(position);
void PrintList(position);

int main()
{
	node stack, row;
	stack.next = NULL;
	row.next = NULL;

	int selection = 1;

	while (selection != 0)
	{
		printf("\n\n\t\t Izbornik:\n");
		printf("\n\t 0. za izlaz");
		printf("\n\t 1. za Push na stog");
		printf("\n\t 2. za Pop sa stoga");
		printf("\n\t 3. za push u red");
		printf("\n\t 4. za pop iz reda");
		printf("\n\n Odabir:\t");
		scanf_s("%d", &selection);
		
		switch (selection)
		{
		case 1:
			PushStack(&stack, GetValueFromRange(min, max));
			PrintList(stack.next);
			break;
		case 2:
			Pop(&stack);
			PrintList(stack.next);
			break;
		case 3:
			PushRow(&row, GetValueFromRange(min, max));
			PrintList(row.next);
			break;
		case 4:
			Pop(&row);
			PrintList(row.next);
			break;
		case 0:
			printf("\n Pozdrav!\n"); selection = 0;
			break;
		default:
			printf("\nPogresan unos, pokusajte ponovo.\n");
			break;
		}
	}
	
	system("pause");
	return 0;
}

int GetValueFromRange(int minValue, int maxValue)
{
	int value;
	value = rand() % (maxValue - minValue) + minValue;
	return value;
}

void PrintList(position p)
{
	printf("\n sadrzani elementi: \n");
	while (p)
	{
		printf("%d ", p->element);
		p = p->next;
	}
}

void PushStack(position p, int value)
{
	position temp;
	temp = (position)malloc(sizeof(node));

	if (temp)
	{
		temp->element = value;
		temp->next = p->next;
		p->next = temp;

		printf("\n vrijednost %d ce biti pohranjena na stog\n", value);
	}
}

void PushRow(position p, int value)
{
	position temp;
	static position last;

	if (p->next == NULL)
		last = p;

	temp = (position)malloc(sizeof(struct node));
	
	if (temp)
	{
		temp->element = value;
		temp->next = last->next;
		last->next = temp;
		last = temp;

		printf("\n vrijednost %d ce biti pohranjena u red\n", value);
	}
	
}

void Pop(position p) {

	position temp;

	if (p->next != NULL) {
		temp = p->next;
		printf("\nIzbrisana vrijednost: %d.\n", temp->element);

		p->next = temp->next;
		free(temp);
	}
}