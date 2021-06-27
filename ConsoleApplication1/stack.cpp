#include <string>
using namespace std;

typedef struct Stack* pStack;
struct Stack {
	char data;
	pStack next;
};

void push(pStack* stackp, char data)
{
	pStack newp = (pStack)malloc(sizeof(struct Stack));
	newp->data = data;
	newp->next = *stackp;
	*stackp = newp;
}

void pop(pStack* stackp)
{
	pStack p = (*stackp)->next;
	free(*stackp);
	*stackp = p;
}

int sizeOfStack(const pStack * stackp) {
	pStack pointer = *stackp;
	int count = 0;
	while (pointer) {
		count++;
		pointer = (pointer)->next;
	}
	return count;
}