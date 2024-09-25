#include <stdio.h>

int	test_fetch_bit(void)
{
	int bit;
	int n_bit;
	char char_;

	n_bit = 0;
	char_ = 'x';
	printf("char: %c\n", char_);
	printf("01111000\n");
	while(8 - n_bit)
	{
		bit = char_ >> (7 - n_bit) & 1;
		printf("%d", bit);
		n_bit++;
	}
	printf("\n");
	// TODO: use compare
}

int	test_build_char(void)
{
	int bits[8] = {0, 1, 1, 1, 1, 0, 0, 0};
	int n_bit;
	char char_;

	n_bit = 0;
	char_ = 0;
	printf("01111000\n");
	while(8 - n_bit)
	{
		char_ = (char_ << 1) | bits[n_bit];
		printf("%d", bits[n_bit]);
		n_bit++;
	}
	printf("\n");
	printf("char: %c\n", char_);
	// TODO: use compare
}

int	main(void)
{
	printf("test: fetch_bit\n");
	test_fetch_bit();
	printf("\n");
	printf("test: build_char\n");
	test_build_char();
}