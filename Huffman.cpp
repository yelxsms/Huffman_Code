# include "stdio.h"
#include "stdlib.h"
#include "string.h"


//哈夫曼树结点
typedef struct Node
{
	int weight;
	char data;
    int parent;
    int lchild;
    int rchild;
};


//哈夫曼编码结点
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
    /*输入字符串,初始化数值*/
    int count[128] = { 0 };
	char input[99];
    int j = 0;
	printf("请输入需要编码的字符串：\n");
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



    /*统计频率*/
    printf("\n");
    printf("\n");
    printf("每个字符及其出现的频率为;\n");
    for (int i = 0; i < j; i++)
    {
        printf("%c:%d\n", list[i].data, list[i].weight);
    }



    /*按出现的频率为权重排序*/
    printf("\n");
    printf("\n");
    printf("以频率为权重排序：\n");
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



    /*新产生的结点赋初值*/
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



    /*不断寻找最小的两个min1和min2,并且min1<min2,权值相加不断产生新节点，搭建哈夫曼树*/
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
    /*走投无路*/
    Huffman[0].parent = j;
    Huffman[n-1].parent = -1;


    /*
    printf("%d,%d\n", min1.weight, min2.weight);
    printf("%d,%d\n", flag_min1,flag_min2);
    printf("%d\n", Huffman[k].weight);
    printf("%d", min1.weight + min2.weight);
    */


    /*打印哈夫曼树表*/
    printf("\n");
    printf("\n");
    printf("\n");
    printf("索引\t字符\t权重\t双亲\t左孩子\t右孩子\n");
    for (int i = 0; i < n; i ++ )
    {
        printf("%d\t%c\t%d\t%d\t%d\t%d\n", i,Huffman[i].data, Huffman[i].weight, Huffman[i].parent, Huffman[i].lchild, Huffman[i].rchild);
    }

    

    /*求每个字符的哈夫曼编码*/
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
    printf("各项字符的哈夫曼编码为：\n");
    for (int i = 0; i < j; i++)
    {
        printf("%c: ", List[i].data);
        for (int t = List[i].start; t<j; t++)
        {
            printf("%c", List[i].bit[t]);
        }
        printf("\n");
    }


    /*将密码文件保存在文件HuffmanPasswords.txt中*/
    printf("\n");
    printf("\n");
    FILE* fp = fopen("C:\\Users\\hase\\Desktop\\数据结构\\HuffmanPasswords.txt", "w");
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
    printf("密码文件成功保存至C:\\Users\\hase\\Desktop\\数据结构\\HuffmanPasswords.txt文件目录下\n");
    fclose(fp);


    /*哈夫曼编码*/
    printf("\n");
    printf("\n");
    printf("需要翻译的字符串为：\n");
    for (int i = 0; i < 99; i++)
    {
        printf("%c", input[i]);
    }
    printf("\n");
    printf("\n");
    printf("哈夫曼译码为：\n");
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



    /*哈夫曼译码*/
    printf("\n");
    printf("\n");
    printf("\n");
    char trans[1000];
    char transchar[300];
    printf("请输入需要翻译的哈夫曼编码：\n");
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
    printf("翻译;\n");
    for (int i = 0; i < count_2; i++)
    {
        printf("%c", transchar[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}