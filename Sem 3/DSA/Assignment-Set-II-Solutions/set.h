#define MAX 100

typedef struct {
	int size;
	int data[MAX];
} set;

bool in_set (set *head, int key)
{
	for (int i = 0; i < head->size; ++i) {
		if (head->data[i] == key)
			return true;
	}
	return false;
}

void insert (set *head, int curr)
{	
	if (in_set(head, curr) == false) {
		if (size < MAX) {
			head -> data[size] = curr;
			++head -> size;
		}
	}
}

void remove (set *head, int key)
{
	if (size <= 0) {
		printf("Empty set.\n");
		return;
	}
	if (in_set(head, key) == false) {
		printf("Data not present in the given set.\n");
		return;
	}
	int ind = -1;
	for (int i = 0; i < head->size; ++i) {
		if (head->data[i] == key) {
			ind = i;
			break;
		}
	}
	for (int i = ind; i < head->size - 1; ++i) {
		head->data[i] = head->data[i + 1];
	}
	--size;
	printf("Successfully removed.\n");
}

void display (set *head)
{
	printf("The set contents are : \n[");
	for (int i = 0; i < head->size; ++i) {
		printf("%d, ", head->data[i]);
	}
	printf("]\n");
}

int get_size (set *head)
{
	return head->size;
}

set union (set *head1, set *head2)
{
	set headu;
	for (int i = 0; i < head1->size; ++i) {
		insert(&headu, head1->data[i]);
	}
	for (int i = 0; i < head2->size; ++i) {
		insert(&headu, head2->data[i]);
	}
	return headu;
}

set intersection (set *head1, set *head2)
{
	set headi;
	for (int i = 0; i < head1->size; ++i) {
		if (in_set(head2, head1->data[i])) {
			insert(&headi, head1->data[i]);
		}
	}
	return headi;
}

set difference (set *head1, set *head2)
{
	set headdiff;
	for (int i = 0; i < head1->size; ++i) {
		if (in_set(head2, head1->data[i]) == false) {
			insert(&headdiff, head1->data[i]);
		}
	}
	return headdiff;
}

bool is_subset (set *head1, set *head2)
{
	for (int i = 0; i < head1->size; ++i) {
		if (in_set(head2, head1->data[i]) == false) {
			return false;
		}
	}
	return true;
}
