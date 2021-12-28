#include <stdio.h>
#include <stdlib.h>

struct student {
	int roll;
	char name[31];
	float score;
	struct student* next;
};

struct student* search (struct student *head, int r) {
    struct student *cur;
	for (cur = head; cur != NULL && cur -> roll != r; cur = cur -> next);
	return cur;
}

void modify (struct student *head, int r) {
	struct student *found = search (head, r);
	if (found) {
		printf ("Enter name: ");
		scanf (" %[^\n]", found -> name);
		printf ("Enter score: ");
		scanf ("%f", &found -> score);
		printf("Record updated successfully.\n");
	}
	else
		printf ("Record not found.\n");
}

void insert (struct student* *head, int pos) {
	int r;
	printf("Enter roll of student: ");
	scanf("%d", &r);
	if (search(*head, r)) {
		char op;
		printf("Record already exists. Do you want to modify? (y/n)\n");
		scanf(" %c", &op);
		if(op == 'y' || op == 'Y')
			modify(*head, r);
		return;
	}
	struct student *newNode = (struct student*) malloc (sizeof(struct student));
	if (newNode == NULL) {
		printf ("Memory Error. New record could not be created.\n");
		return;
	}
	newNode -> roll = r;
	printf("Enter name: ");
	scanf(" %[^\n]", newNode -> name);
	printf("Enter score: ");
	scanf("%f", &(newNode -> score));

	if (pos == 1) {
		newNode -> next = *head;
		*head = newNode;
	}
	else {
		struct student *cur = *head, *prev = *head;
		for (int k = 1; (k < pos) && (cur != NULL); k++) {
			prev = cur;
			cur = cur -> next;
		}
		prev -> next = newNode;
		newNode -> next = cur;
	}

	printf("Record added successfully.\n");
}

void display (struct student *head) {
	if (head == NULL) {
		printf("Database is empty.\n");
		return;
	}
	int k = 0;
	for (struct student *cur = head; cur != NULL; cur = cur -> next, k++)
		printf ("Roll: %d Name: %s Score: %f\n", cur -> roll, cur -> name, cur -> score);
	printf("Number of records: %d\n", k);
}

void delete (struct student* *head) {
	if (*head == NULL) {
		printf ("Database is empty.\n");
		return;
	}
	int r;
	printf ("Enter roll: ");
	scanf("%d", &r);
	struct student *cur = *head;
	if ((*head) -> roll == r) {
		*head = (*head) -> next;
		free (cur);
		return;
	}
	else {
		struct student *prev = NULL;
		while (cur != NULL && cur -> roll != r) {
			prev = cur;
			cur = cur -> next;
		}
		if (cur == NULL) {
			printf("Roll number does not exist.\n");
			return;
		}
		else {
			prev -> next = cur -> next;
			int temp = cur -> roll;
			free (cur);
			printf("Roll no. %d deleted.\n", temp);
		}
	}
}

void delete_all (struct student* *head) {
	while (*head != NULL) {
		struct student *auxiliaryNode = *head;
		*head = (*head) -> next;
		free (auxiliaryNode);
	}
	printf("Memory freed successfully.\n");
}

int main() {
	struct student *head = NULL;
	char c = 'n';
	do {
		int ch, r;
		printf("1. Add a student\n2. Display students\n3. Search for a student\n4. Edit details of a student\n5. Delete a student\nEnter your choice: ");
		scanf ("%d", &ch);
		if (ch > 2 && ch < 5) {
			printf ("Enter roll: ");
			scanf("%d", &r);
		}
		struct student *found;
		switch (ch) {
			case 1: insert(&head, 1); break;
			case 2:	display(head); break;
			case 3: found = search (head, r);
				if(found)
					printf("Record found.\nRoll = %d Name = %s Score = %f.\n", found->roll, found->name, found->score);
				else
					printf("Record not found.\n");
				break;
			case 4: modify (head, r); break;
			case 5: delete (&head); break;
			default: printf("Wrong choice.\n");
		}
		printf("Press y to go to main menu. Press any other key to exit.\n");
		scanf(" %c", &c);
	} while (c == 'y' || c == 'Y');
	delete_all (&head);
	return 0;
}