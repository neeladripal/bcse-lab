#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	int roll;
	char name[31];
	float score[5];
	char validity;
};

int search (char *fn, int k) {
	FILE *fp = fopen (fn, "r");
	if(fp == NULL) {
		printf("File cannot be found.\n");
		return -1;
	}
	struct student s;
	int count = 0;
	while (fread(&s, sizeof(struct student), 1, fp) != 0) {
		count++;
		if (s.roll == k && s.validity == 't') {
			fclose(fp);
			return count;
		}
	}
	return 0;
}

void modify (char *fn, int k) {
	int r = search (fn, k);
	if (r == 0)
		printf ("Student does not exist.\n");
	else {
		FILE *fp = fopen (fn, "r+");
		if (fp == NULL) {
			printf("File cannot be found.\n");
			return;
		}
		struct student s;
		int size = sizeof (struct student);
		int offset = (r-1) * size;
		fseek (fp, offset, 0);
		fread (&s, size, 1, fp);
		printf ("Enter name: ");
		scanf (" %[^\n]", s.name);
		printf ("Enter scores: ");
		for (int i = 0; i < 5; i++)
			scanf ("%f", &s.score[i]);
		fseek (fp, (-1) * size, 1);
		fwrite (&s, size, 1, fp);
		fclose (fp);
		printf("Record modified successfully.\n");
	}
}

void add_record (char *fn) {
	FILE* fp = fopen (fn, "a");
	if(fp == NULL) {
		printf("File cannot be found.\n");
		return;
	}
	struct student s;
	printf("Enter roll of record to be added: ");
	scanf("%d", &s.roll);
	if (search(fn, s.roll)) {
		char op;
		printf ("Student already exists.\nWould you like to edit the details? (y/n) ");
		scanf(" %c", &op);
		if (op == 'y' || op == 'Y')
			modify (fn, s.roll);
	}
	else {
		printf ("Enter name: ");
		scanf (" %[^\n]", s.name);
		printf ("Enter score in five subjects: ");
		for (int i = 0; i < 5; i++)
			scanf ("%f", &s.score[i]);
		s.validity = 't';
		fwrite (&s, sizeof(struct student), 1, fp);
		fclose (fp);
		printf("Record added successfully.\n");
	}
}

void display (char *fn) {
	FILE* fp = fopen (fn, "r");
	if(fp == NULL) {
		printf("File cannot be found.\n");
		return;
	}
	struct student s;
	int count = 0;
	while (fread(&s, sizeof(struct student), 1, fp) != 0) {
		if(s.validity == 't') {
			count++;
			float tscore = 0;
			for (int i = 0; i < 5; i++)
				tscore += s.score[i];
			printf ("Student %d, Roll: %d Name: %s Total Score: %f.\n", count, s.roll, s.name, tscore);
		}
	}
	printf ("Number of records: %d.\n", count);
	fclose (fp);
}

void delete (char *fn) {
	FILE *fp1 = fopen (fn, "r+");
	if (fp1 == NULL) {
		printf("File cannot be found.\n");
		return;
	}
	int op;
	printf("1. Logical Deletion 2. Physical Deletion\nEnter your choice: ");
	scanf("%d", &op);
	struct student s;
	int size = sizeof (struct student);
	if (op == 1) {
		int k;
		printf ("Enter roll of record to be logically deleted: ");
		scanf("%d", &k);
		int r = search (fn, k);
		if (r == 0)
			printf ("Student does not exist.\n");
		else {
			int offset = (r-1) * size;
			fseek (fp1, offset, 0);
			fread (&s, size, 1, fp1);
			s.validity = 'f';
			fseek (fp1, (-1) * size, 1);
			fwrite (&s, size, 1, fp1);
			fclose (fp1);
			printf ("Roll no. %d logically deleted.\n", k);
		}
	}
	else if (op == 2) {
		FILE *fp2 = fopen ("temp.dat", "w");
		while (fread (&s, size, 1, fp1) != 0)
			if (s.validity == 't')
				fwrite (&s, size, 1, fp2);
		fclose (fp1);
		fclose (fp2);
		char copy_command[31];
		sprintf (copy_command, "cp temp.dat %s", fn);
		system (copy_command);
		system ("rm temp.dat");
		printf("Physical deletion successful.\n");
	}
}

void delete_all (char *fn) {
	FILE *fp = fopen (fn, "w");
	fclose (fp);
	printf ("All records deleted.\n");
}

int main () {
	char fn[31];
	printf("Enter file name: ");
	scanf("%s", fn);
	char c = 'n';
	do {
		int ch, r;
		printf("1. Add record\n2. Display records\n3. Search for a record\n4. Edit details of a record\n5. Delete student\n6. Delete all records\nEnter your choice: ");
		scanf ("%d", &ch);
		if (ch > 2 && ch < 5) {
			printf ("Enter roll: ");
			scanf("%d", &r);
		}
		switch (ch) {
			case 1: add_record(fn); break;
			case 2:	display(fn); break;
			case 3: 
				if(search (fn, r))
					printf("Record found.\n");
				else
					printf("Record not found.\n");
				break;
			case 4: modify (fn, r); break;
			case 5: delete (fn); break;
			case 6: delete_all (fn); break;
			default: printf("Wrong choice.\n");
		}
		printf("Press y to go to main menu. Press any other key to exit.\n");
		scanf(" %c", &c);
	} while (c == 'y' || c == 'Y');
	return 0;
}