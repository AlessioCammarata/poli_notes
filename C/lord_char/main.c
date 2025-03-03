#include <stdio.h>

int main() {
	FILE *fp_read, *fp_write;
	char file_char, choice;
	if ((fp_read = fopen("./Guide.txt", "r")) == NULL) {
		printf("Error opening file\n");
		return 1;
	}

	if ((fp_write = fopen("./Output.txt", "w")) == NULL) {
		printf("Error opening file\n");
		return 2;
	}

	printf("Print on console (C) or on file (F):");
	choice = getchar();
	while (!feof(fp_read)) {
		file_char = fgetc(fp_read);

		if (!feof(fp_read)) {
			switch (choice) {
				case 'C':
					printf("%c", file_char);
					break;

				case 'F':
					fputc(file_char, fp_write);
					printf("\nChar saved on file: ");
					putchar(file_char);
					break;

				default:
					printf("Wrong choice\n");
					return 3;
			}
		}
	}
	fclose(fp_read);
	fclose(fp_write);
	return 0;
}
