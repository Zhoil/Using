#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include"string.h"

/*
  �Ӽ��̻�ú��ֵı���
  ������windows�£�Ĭ�ϱ��뷽ʽΪGB2312, ÿ�������������ֽ���ɡ�
  ������Ŀ���ǣ���������ֵĸ��ֽ�д�� pc1ָ���λ�ã����ֽ�д�� pc2ָ���λ��
*/

int get_han_zi(unsigned char* pc1, unsigned char* pc2)

{
	char buf[100];
	printf("\n������һ�����֣�");
	gets(buf);
	if (strlen(buf) != 2) return -1;
	*pc1 = buf[0];
	*pc2 = buf[1];

	if (*pc1 < 0xa1) return -2;

	if (*pc2 < 0xa1) return -2;

	return 0;

}

void load_han_zi(unsigned char* buf, unsigned char c1, unsigned char c2)

{

	int n = (c1 - 0xa1) * 94 + (c2 - 0xa1); // �������ļ��е�λ��
	FILE* fp = fopen("han.dat", "rb");
	if (fp == NULL) {
		printf("���ֿ�򿪴�");
		exit(1);
	}

	fseek(fp, n * 32L, SEEK_SET);

	for (int i = 0; i < 32; i++) {
		buf[i] = (unsigned char)fgetc(fp);
	}

	fclose(fp);

}
/*
  ��ʾ����
  buf: ���ļ��ж����ĺ�����ģ��Ϣ��32�ֽڣ�˵��ͬ��
  italic: =1�����Ҫ��б�壬 =0 ����
  kx: ˮƽ�Ŵ���
  ky: ��ֱ�Ŵ���
  fill: ���������ַ�
*/

void show_han_zi(unsigned char* buf, int italic, int kx, int ky, char fill)
{
	for (int i = 0; i < 16; i++) {
		for (int k1 = 0; k1 < ky; k1++) {
			\
				printf("\n");
			if (italic) {
				for (int k3 = 0; k3 < 15 - i; k3++)
					printf(" ");
			}

			for (int j = 0; j < 16; j++) {
				if (buf[i * 2 + (j / 8)] & (0x80 >> (j % 8)))
					for (int k2 = 0; k2 < kx; k2++)
						printf("%c", fill);

				else
					for (int k2 = 0; k2 < kx; k2++)
						printf(" ");
			}
		}
	}
}

void write_to_file(unsigned char* buf, int italic, int kx, int ky, char fill)

{

	FILE* fp = fopen("han.txt", "w");

	for (int i = 0; i < 16; i++) {
		for (int k1 = 0; k1 < ky; k1++) {
			fputc('\n', fp);
			if (italic) {
				for (int k3 = 0; k3 < 15 - i; k3++)
					fputc(' ', fp);
			}

			for (int j = 0; j < 16; j++) {
				if (buf[i * 2 + (j / 8)] & (0x80 >> (j % 8)))
					for (int k2 = 0; k2 < kx; k2++)
						fputc(fill, fp);
				else
					for (int k2 = 0; k2 < kx; k2++)
						fputc(' ', fp);

			}

		}

	}

	fclose(fp);

}

int set_zoom_k(int* pk)

{
	printf("������Ŵ���(1-4)��");
	char buf[100];
	gets(buf);
	int n = atoi(buf);
	if (n < 1 || n>4) return -1;
	*pk = n;
	return 0;

}

char get_fill_char()

{

	for (;;) {
		printf("���������������ַ�");
		char c = getch();
		if (c > 32 && c < 125) return c;
	}

}

int main(����)

{
	system("title Zhoi ���ֲ���");

	unsigned char han_zi_buf[32];  // �洢16�����ֵ���ģ
	int font_italic = 0;
	int font_kx = 1;  // ˮƽ�Ŵ���
	int font_ky = 1;  // ��ֱ�Ŵ���
	char fill_char = '@';  // ����ַ�

	for (;;) {

		printf("\n ^^^^^^^^^^^Zhoi ���ֳ������^^^^^^^^^^^\nDesigned by han and refered by a nice person\n");

		printf("1. ����һ������\n");

		printf("2. �л�б��\n");

		printf("3. ����ˮƽ�Ŵ�\n");

		printf("4. ���ô�ֱ�Ŵ�\n");

		printf("5. ��������ַ�\n");

		printf("6. ������ļ�han.txt\n");

		printf("7. �˳�\n");

		printf("----------------\n");

		printf("��ѡ����Ӧ������\n");

		char c = (char)getch();

		switch (c) {

		case '1':

		{
			unsigned char c1;
			unsigned char c2;
			if (get_han_zi(&c1, &c2) != 0)
				printf("\n������Ч��\n");
			else {
				load_han_zi(han_zi_buf, c1, c2);
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			}
		}
		break;

		case '2':
			font_italic = (font_italic + 1) % 2;
			show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '3':
			if (set_zoom_k(&font_kx) != 0)
				printf("\n������Ч��\n");
			else
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '4':
			if (set_zoom_k(&font_ky) != 0)
				printf("\n������Ч��\n");
			else
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '5':
			fill_char = get_fill_char();
			show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '6':
			write_to_file(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '7':
			exit(0);
			break;

		default:
			printf("\n����ѡ����Ч��\n");
		}
	}

}