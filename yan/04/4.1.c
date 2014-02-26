/*����˳��洢��ʾ*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Maxstrlen 40 //�û�����255���ڶ�����󴮳�(һ���ֽ�)
#define error 0 //�쳣�׳�
#define false 0 //�쳣�׳�
#define true 1 //������ȷִ�з���
#define ok 1 //������ȷִ�з���
typedef int status;//�����ͱ�ʾ״̬��������ֵ����
//0�ŵ�Ԫ��Ŵ��ĳ��ȣ�����˳������;���±�Ϊ0�����������Ŵ���ʵ�ʳ���;
//(��������:��ֵĩβ�Ӳ����봮����'\0')
typedef char sString[Maxstrlen+1];

//����һ��ֵ�����chars�Ĵ�T,����ֵ
status strAssign(sString T,char *chars){
	int i;
	//����ַ�������chars�ĳ��ȴ�����󴮳�������
	if(strlen(chars)>Maxstrlen) return error;
	else{
		T[0] = strlen(chars);//0�ŵ�Ԫ��Ŵ��ĳ���
		for(i=1;i<=T[0];i++){//�Ӵ�T��һ��Ԫ������T���Ԫ
			//����ȡ�ַ�������chars�еĸ����ַ���������˳��T
			T[i] = *(chars+i-1);
		}
		return ok;
	}
}

//�ַ����ĸ��ƣ�����S���Ƶô�T
status strCopy(sString S,sString T){
	int i;
	T[0] = S[0];//���ȸ�ֵ
	for(i=1;i<=S[0];i++){
		T[i]=S[i];
	}
	return ok;
}

//�ж��ַ����Ƿ�Ϊ��
status strEmpty(sString S){
	if(S[0]==0) return true;
	else return false;
}

//����Ԫ�صĸ���
int strLength(sString S){
	return S[0];//S[0]�б��洮S�ĳ���
}

//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
status subString(sString S,sString Sub,int pos,int len){
	int i;
	//�Ӵ���һ�ַ��ڸ���S�е����posС��1������ڸ���S����
	//�Ӵ�����С��0������ڸ���S��-��һ�ַ�+1
	//(��pos������Sβ���Ѿ�����ָ�����Ӵ���)��������
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
		return error;
	for(i=1;i<=len;i++){
		//�Ӹ���S�ĵ�pos�ַ���ʼ������ȡlen���ַ��������Ӵ�Sub
		Sub[i] = S[pos+i-1];
	}
	Sub[0] = len;//�޸��Ӵ�Sub����Ϊlen
	return ok;
}

//�����������γ��´�����T����S1��S2���Ӷ��ɵ��´�
status strConcat(sString T,sString S1,sString S2){
	//��δ�ضϣ��򷵻�true������false
	//�ض�(��β)��������󴮳�
	//���Ķ�(��̬)������洢���Կ˷���β
	int i;
	//û������󴮳�
	if(S1[0]+S2[0]<=Maxstrlen){//δ�ض�
		//�Ӵ�S1�ĵ�һ�ַ���ʼ������S1������ַ�Ϊֹ
		for(i=1;i<=S1[0];i++)
			T[i] = S1[i];//���ΰѴ�S1�ĸ����ַ�������T
		//�Ӵ�S2�ĵ�һ�ַ���ʼ������S2������ַ�Ϊֹ
		for(i=1;i<=S2[0];i++)
			//�ڴ�T�д�S1������λ�ü������봮S2�����ΰѴ�S2�ĸ����ַ�������T
			T[S1[0]+i] = S2[i];
		T[0] = S1[0]+S2[0];//�޸Ĵ�T�ĳ���Ϊ��S1����S2�ĳ���֮��
		return true;//��δ�ضϣ��򷵻�true
	}else{//������󴮳����ض�S2
		//�Ӵ�S1�ĵ�һ�ַ���ʼ������S1������ַ�Ϊֹ
		for(i=1;i<=S1[0];i++)
			T[i] = S1[i];//���ΰѴ�S1�ĸ����ַ�������T
		//�Ӵ�S2�ĵ�һ�ַ���ʼ������󴮳�-��S1����ʣ�೤��Ϊֹ
		for(i=1;i<=Maxstrlen-S1[0];i++)
			//�ڴ�T�д�S1������λ�ü������봮S2�����ΰѴ�S2�ĸ����ַ�������T
			T[S1[0]+i] = S2[i];
		T[0] = Maxstrlen;//�޸Ĵ�T�ĳ���Ϊ��󴮳�
		return false;
	}
}

//��������Ƚ�,��ʼ��������S��T����
int strCompare(sString S,sString T){
	//��S>T���򷵻�ֵ>0����S=T���򷵻�=0����S<T���򷵻�ֵ<0
	int i;
	//��S[1]��T[1]��ʼ���� S[����]��T[����]Ϊֹ
	//�Ӵ���һ�ַ�����T��һ�ַ���ʼ������S����ַ�����T����ַ�Ϊֹ
	for(i=1;i<=S[0]&&i<=T[0];i++){
		//���αȽ�S[i]��T[i]
		if(S[i]!=T[i]){
			//���αȽϴ�S����T�и����ַ�
			return S[i]-T[i];//������һ���ַ�
		}
	}
	//�����S�и����ַ�S[i]����T�и����ַ�T[i]����Ӧ���
	//�˳�ѭ���󣬷��ش�S����T�ĳ��Ȳ�ֵ
	return S[0]-T[0];
}

//�ַ����������
void strPrint(sString T){
	int i;
	for(i=1;i<=T[0];i++){//��1��T[0]
		printf("%c",T[i]);//���������T�и����ַ�
	}
	printf("\n");
}

//������S�д��ںʹ�Tֵ��ͬ���Ӵ���
//�򷵻���������S�е�pos���ַ�֮���һ�γ��ֵ�λ�ã�������ֵΪ0
int indexPosition(sString S,sString T,int pos){
	int n,m,i;
	sString sub;
	if(pos>0){
		n = strLength(S);
		m = strLength(T);
		i = pos;
	}
	while(i<=n-m+1){
		subString(S,sub,i,m);
		if(strCompare(sub,T)!=0) i++;
		else return i;
	}
	return 0;
}

//�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
status strInsert(sString S,sString T,int pos){
	//��ʼ��������S��T���ڣ�1<=pos<=strLength(S)+1
	//����������ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��true�����ֲ��뷵��false
	int i,space;
	//���pos��1����������ַ��ĺ�һ��λ��֮��
	if(pos<1||pos>S[0]+1) return error;//û�����룬����
	//��S[0]֮ǰû�����룻��S[1]֮ǰ���Բ���
	//��S[S[0]+1]֮ǰ���Բ���(��������ַ�֮��)��
	//��S[S[0]+2]֮ǰû������
	
	//�������S���Ӵ�T�ĳ���֮��С�ڵ�����󴮳�
	//���Ӵ�T�϶�����ȫ��������S��pos���ַ�֮ǰ
	if(S[0]+T[0]<=Maxstrlen){//��ȫ����
		//������S����ַ���ʼ������pos���ַ�Ϊֹ
		for(i=S[0];i>=pos;i--)
			S[i+T[0]] = S[i];//��������ƶ��Ӵ�T�ĳ��ȸ�λ�ã����Ӵ�T�ڳ��ռ�
		
		//�ӵ�pos���ַ���ʼ������pos+T[0]-1���ַ�Ϊֹ
		for(i=pos;i<pos+T[0];i++)
			S[i] = T[i-pos+1];//���ΰ��Ӵ�T�и����ַ���������Sԭ��pos���ַ�֮ǰ
		S[0] = S[0]+T[0];//�޸���������Ϊ����S���Ӵ�T�ĳ���֮��
		return true;
	}else{
		//�������S���Ӵ�T�ĳ���֮�ʹ�����󴮳�
		//���Ӵ�Tֻ�ܲ��ֲ�������S��pos���ַ�֮ǰ
		//���ֲ���
		space = Maxstrlen-S[0];//ʣ��ռ�
		//iΪMaxstrlenʱS[Maxstrlen-T[0]]����S[Maxstrlen]
		for(i=S[0];i>=pos;i--)
			S[i+space] = S[i];
		//iΪposʱS[pos-T[0]]����S[pos]
		for(i=pos;i<pos+space;i++)//���ֲ���
			S[i] = T[i-pos+1];//iΪposʱT[1]����S[pos]
		S[0] = Maxstrlen;//�޸�����S�ĳ���Ϊ��󴮳�
		return false;
	}
}

void main(){
	sString T1,t1,T2,t2,T;//����һ��������˳��洢�ṹ����ͨ���ַ���
	char *chars1=t1;//��ʼ�����ַ���
	char *chars2=t2;
	int place,pos;
	printf("Please enter the string 1:\n");
	gets(t1);//�����ַ���
	printf("Please enter the string 2:\n");
	gets(t2);
	strAssign(T1,chars1);//����һ����ֵ����chars�Ĵ�T
	strAssign(T2,chars2);
	//�ַ����������
	printf("please input the pos you want:\n");
	scanf("%d",&pos);
	place = indexPosition(T1,T2,pos);
	printf("The result is %d",place);
	//����ַ���T1��T2
	printf("\nThe string T1:\n");
	strPrint(T1);
	printf("The string T2:\n");
	strPrint(T2);
	//��T2���뵽T1
	printf("\nThe inserted string:\n");
	strInsert(T1,T2,3);
	strPrint(T1);
	//�ַ���������
	printf("\nConcat the T1 and T2:\n");
	strConcat(T,T1,T2);
	strPrint(T);
	//�ַ������ƣ���T1���Ƹ�T2
	printf("\nCopy string T1 to string T2:\n");
	strCopy(T1,T2);
	printf("The string T2 after copying:\n");
	if(!strEmpty(T2)) strPrint(T2);
}