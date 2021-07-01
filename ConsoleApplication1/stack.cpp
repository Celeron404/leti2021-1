#include <string>
using namespace std;

typedef struct charStack * pCharStack;
struct charStack {
	char data;
	pCharStack next;
};

typedef struct stringStack * pStringStack;
struct stringStack {
	string data;
	pStringStack next;
};

typedef struct intStack * pIntStack;
struct intStack {
	int data;
	pIntStack next;
};



void push(pCharStack* stackp, char data)
{
	pCharStack newp = (pCharStack)malloc(sizeof(struct charStack));
	newp->data = data;
	newp->next = *stackp;
	*stackp = newp;
}

void pop(pCharStack* stackp)
{
	pCharStack p = (*stackp)->next;
	free(*stackp);
	*stackp = p;
}

int sizeOfStack(const pCharStack * stackp) {
	pCharStack pointer = *stackp;
	int count = 0;
	while (pointer) {
		count++;
		pointer = (pointer)->next;
	}
	return count;
}

void push(pStringStack* stackp, string data)
{
	pStringStack newp = (pStringStack)malloc(sizeof(struct stringStack));
	newp->data = data;
	newp->next = *stackp;
	*stackp = newp;
}

void pop(pStringStack* stackp)
{
	pStringStack p = (*stackp)->next;
	free(*stackp);
	*stackp = p;
}

int sizeOfStack(const pStringStack * stackp) {
	pStringStack pointer = *stackp;
	int count = 0;
	while (pointer) {
		count++;
		pointer = (pointer)->next;
	}
	return count;
}

void push(pIntStack* stackp, int data) {
	pIntStack newp = (pIntStack)malloc(sizeof(struct intStack));
	newp->data = data;
	newp->next = *stackp;
	*stackp = newp;
}

void pop(pIntStack* stackp) {
	pIntStack p = (*stackp)->next;
	free(*stackp);
	*stackp = p;
}

int sizeOfStack(const pIntStack * stackp) {
	pIntStack pointer = *stackp;
	int count = 0;
	while (pointer) {
		count++;
		pointer = (pointer)->next;
	}
	return count;
}