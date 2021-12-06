# include "stdio.h"
#include "stdlib.h"
#include "string.h"


//�����������
typedef struct Node
{
	int weight;
	char data;
    int parent;
    int lchild;
    int rchild;
};


//������������
typedef struct Ma
{
    int bit[20];
    int start;
    char data;
};

struct Node list[26];
struct Ma List[40];

int main()
{
    /*�����ַ���,��ʼ����ֵ*/
    int count[128] = { 0 };
	char input[99];
    int j = 0;
	printf("��������Ҫ������ַ�����\n");
    gets_s(input);
    for (int i = 0; input[i] != '\0'; ++i)
        count[input[i]]++;
    for (int i = 0; i < 128; i++)
        if (count[i] != 0)
        {           
            //printf("%c:%d\n", i, count[i]);
            list[j].data = char(i);
            list[j].weight = count[i];
            list[j].parent = 0;
            list[j].lchild = -1;
            list[j].rchild = -1;
            j++;
        }



    /*ͳ��Ƶ��*/
    printf("\n");
    printf("\n");
    printf("ÿ���ַ�������ֵ�Ƶ��Ϊ;\n");
    for (int i = 0; i < j; i++)
    {
        printf("%c:%d\n", list[i].data, list[i].weight);
    }



    /*�����ֵ�Ƶ��ΪȨ������*/
    printf("\n");
    printf("\n");
    printf("��Ƶ��ΪȨ������\n");
    for (int i = 0; i < j-1; i++)
    {
        for (int k = 0; k < j - i - 1; k++)
        {
            if (list[k].weight > list[k + 1].weight) {
                struct Node temp = list[k + 1];
                list[k + 1] = list[k];
                list[k] = temp;
            }
        }
    }
    for (int i = 0; i < j; i++)
    {
        printf("%c:%d\n", list[i].data, list[i].weight);
    }
    //printf("%d", j);



    /*�²����Ľ�㸳��ֵ*/
    int n = 2*j-1;
    struct Node Huffman[51];
    for (int i = 0; i < j; i++)
    {
        Huffman[i] = list[i];
    }
    for (int i = j; i < n; i++)
    {
        Huffman[i].weight = 0;
        Huffman[i].parent = 0;
        Huffman[i].lchild = 0;
        Huffman[i].rchild = 0;
    }



    /*����Ѱ����С������min1��min2,����min1<min2,Ȩֵ��Ӳ��ϲ����½ڵ㣬���������*/
    struct Node min1, min2, temp;   
    temp.weight = 0;
    //printf("%d,%d", min1.weight, min2.weight);
    int k = j;
    //printf("%d\n", k);   
    for (int m = 0; m < n; m++)
    {
        if (Huffman[m].weight != 0 && Huffman[m].parent==0)
        {
            min1.weight = 99;
            min2.weight = 99;
            int flag_min1 = 0;
            int flag_min2 = 0;
            for (int i = 0; i <= n; i++)
            {
                if (Huffman[i].weight != 0 && Huffman[i].parent == 0)
                {                    
                    temp = Huffman[i];
                    if (temp.weight <= min2.weight)
                    {
                        if (temp.weight >= min1.weight)
                        {
                            min2 = temp;
                            flag_min2 = i;
                        }
                        else
                        {
                            min2 = min1;
                            min1 = temp;
                            flag_min1 = i;
                        }
                    }
                }
            }
            //printf("%d\n", k);
            Huffman[k].weight = min1.weight + min2.weight;
            Huffman[k].lchild = flag_min1;
            Huffman[k].rchild = flag_min2;
            Huffman[k].data = '\0';
            Huffman[flag_min1].parent = k;
            //printf("%d\n", Huffman[flag_min1].parent);
            Huffman[flag_min2].parent = k;
            k++;
        }
    }
    /*��Ͷ��·*/
    Huffman[0].parent = j;
    Huffman[n-1].parent = -1;


    /*
    printf("%d,%d\n", min1.weight, min2.weight);
    printf("%d,%d\n", flag_min1,flag_min2);
    printf("%d\n", Huffman[k].weight);
    printf("%d", min1.weight + min2.weight);
    */


    /*��ӡ����������*/
    printf("\n");
    printf("\n");
    printf("\n");
    printf("����\t�ַ�\tȨ��\t˫��\t����\t�Һ���\n");
    for (int i = 0; i < n; i ++ )
    {
        printf("%d\t%c\t%d\t%d\t%d\t%d\n", i,Huffman[i].data, Huffman[i].weight, Huffman[i].parent, Huffman[i].lchild, Huffman[i].rchild);
    }

    

    /*��ÿ���ַ��Ĺ���������*/
    Ma temp_2;
    for (int i = 0; i < j; i++)
    {
        temp_2.start = j;
        temp_2.data = Huffman[i].data;
        int c = i;
        int p = Huffman[i].parent;
        while (p != -1)
        {
            temp_2.start--;
            if (Huffman[p].lchild == c)
            {
                temp_2.bit[temp_2.start] = '0';
            }
            else
            {
                temp_2.bit[temp_2.start] = '1';
            }
            //flag++;           
            c = p;
            p = Huffman[c].parent;
        }
        List[i] = temp_2;
    }
    printf("\n");
    printf("\n");
    printf("�����ַ��Ĺ���������Ϊ��\n");
    for (int i = 0; i < j; i++)
    {
        printf("%c: ", List[i].data);
        for (int t = List[i].start; t<j; t++)
        {
            printf("%c", List[i].bit[t]);
        }
        printf("\n");
    }


    /*�������ļ��������ļ�HuffmanPasswords.txt��*/
    printf("\n");
    printf("\n");
    FILE* fp = fopen("C:\\Users\\hase\\Desktop\\���ݽṹ\\HuffmanPasswords.txt", "w");
    if (fp == NULL)
        return 0;
    for (int i = 0; i < j; i++)
    {
        fprintf(fp, "%c:", List[i].data);
        for (int t = List[i].start; t < j; t++)
        {
            fprintf(fp,"%c", List[i].bit[t]);
        }
        fprintf(fp, "\n");
    }
    printf("�����ļ��ɹ�������C:\\Users\\hase\\Desktop\\���ݽṹ\\HuffmanPasswords.txt�ļ�Ŀ¼��\n");
    fclose(fp);


    /*����������*/
    printf("\n");
    printf("\n");
    printf("��Ҫ������ַ���Ϊ��\n");
    for (int i = 0; i < 99; i++)
    {
        printf("%c", input[i]);
    }
    printf("\n");
    printf("\n");
    printf("����������Ϊ��\n");
    for (int i = 0; i < 99;i++)
    {
        if (input[i] != '\0')
        {
            for (int w = 0; w < j; w++)
            {
                if (input[i] == List[w].data)
                {
                    for (int x = List[w].start; x < j; x++)
                    {
                        printf("%c", List[w].bit[x]);
                    }
                    printf(" ");
                }  
            }
        }
    }



    /*����������*/
    printf("\n");
    printf("\n");
    printf("\n");
    char trans[1000];
    char transchar[300];
    printf("��������Ҫ����Ĺ��������룺\n");
    gets_s(trans);
    int count_2 = 0;
    int i = n - 1;
    for (int i_2 = 0; trans[i_2]!='\0'; i_2++)
    {
        if (trans[i_2] == '0')
            i = Huffman[i].lchild;
        else if (trans[i_2] == '1')
            i = Huffman[i].rchild;
        if (Huffman[i].lchild == -1 && Huffman[i].rchild == -1)
        {
            transchar[count_2] = Huffman[i].data;
            count_2++;
            i = n - 1;
        }
    }
    transchar[count_2] = '\0';
    printf("\n");
    printf("\n");
    printf("����;\n");
    for (int i = 0; i < count_2; i++)
    {
        printf("%c", transchar[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}