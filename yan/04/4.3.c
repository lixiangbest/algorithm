/*����ģʽƥ���㷨(KMP�㷨)*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���Ӵ�λ�õĶ�λ����
//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0
int index_common(char *S,char *T,int pos){
	//����T�ǿգ�1<=pos<=strlen(S)
	int sLen = strlen(S);
	int tLen = strlen(T);
	int i = pos,j=1;
	unsigned times=0;//�Ƚϴ���
	while(i<=sLen&&j<=tLen){
		if(S[i-1]==T[j-1]){
			++i;++j;//�����ȽϺ���ַ�
		}else{
			i = i-(j-1)+1;//ָ��������¿�ʼ����
		}
		times++;
	}
	printf("\nThe match times:%d\n",times);
	if(j>tLen) return i-tLen;
	else return 0;
}

void main(){
	char *S,*T;
	char s1[80] = "A STRING SEARCHING EXAMPLE CONSISTING OF SIMPLE TEXT";
	char t1[80] = "STING";
	char s2[80] = "00000000000000000000000000000000000000000000000000001";//ǰ52���ַ���Ϊ0
	char t2[80] = "00000001";
	int pos;
	//����ַ���
	S="lixiang";
	T="xi";
	printf("Print the string S and T:\n");
	printf("S=%s\nT=%s\n",S,T);
	
	//�ַ�����λ
	pos = 1;
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(S,T,pos));
	
	//�ַ������¸���
	printf("\nPrint the new string S and T:\n");
	printf("Len=%d, S1=%s\nLen=%d, T1=%s\n",strlen(s1),s1,strlen(t1),t1);
	//�ַ�����λ
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(S,T,pos));
	
	//�ַ������¸���
	printf("\nPrint the new string S and T:\n");
	printf("Len=%d, S=%s\nLen=%d, T=%s\n",strlen(s2),s2,strlen(t2),t2);
	//�ַ�����λ
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(s2,t2,pos));
}


