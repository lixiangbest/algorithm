/*
* ���ݽṹC���԰� ������ͷβ����洢��ʾ
* P109
* 2012-09-23
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char AtomType;//����ԭ������Ϊ�ַ���
typedef enum{
	ATOM,//ATOM==0:ԭ��
	LIST //LIST==1:�ӱ�
}ElemTag;

//������ͷβ����洢��ʾ
typedef struct GLNode{
	ElemTag tag;//�������֣���������ԭ�ӽ��ͱ���
	union{
		AtomType atom;//atom��ԭ�ӽ���ֵ��AtomType���û�����
		struct{
			struct GLNode *hp,*tp;
		}ptr;//ptr�Ǳ����ָ����ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
	}a;
}*GList,GLNode;//���������

//�����յĹ����L
int initGList(GList *L){
	*L = NULL;
	return 1;
}

//���ٹ����L
void destroyGList(GList *L){
	GList q1,q2;
	if(*L){
		if((*L)->tag==ATOM){
			free(*L);//ɾ��ԭ�ӽ��
			*L = NULL;
		}else{//�Ǳ��㣬��Ӧ��ɾ����ͷ�ͱ�β���
			q1 = (*L)->a.ptr.hp;
			q2 = (*L)->a.ptr.tp;
			free(*L);//ɾ����ǰ���
			*L = NULL;
			//�ݹ�ɾ����ͷ�ͱ�β���
			destroyGList(&q1);
			destroyGList(&q2);
		}
	}
}

//�㷨5.6 P115
// ����ͷβ����洢�ṹ���ɹ����L���Ƶõ������T
int copyGList(GList *T,GList L){
	if(!L){//Ϊ�գ����ƿձ�
		*T = NULL;
	}else{
		*T = (GList)malloc(sizeof(GLNode));//������
		if(!*T) exit(0);
		(*T)->tag = L->tag;//���Ʊ�ͷ����־
		if(L->tag==ATOM){
			(*T)->a.atom = L->a.atom;//���Ƶ�ԭ��
		}else{//�Ǳ��㣬�����θ��Ʊ�ͷ�ͱ�β
			//���ƹ����L->ptr.hp��һ������T->ptr.hp
			copyGList(&((*T)->a.ptr.hp),L->a.ptr.hp);
			//���ƹ����L->ptr.tp��һ������T->ptr.tp
			copyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
		}
	}
	return 1;
}

//���ع����ĳ��ȣ���Ԫ�ظ���
int GListLength(GList L){
	int len = 0;
	if(!L){
		return 0;
	}
	while(L){
		L = L->a.ptr.tp;//���ݱ�β���ж�
		len++;
	}
	return len;
}

//�㷨5.5 P114
int GListDepth(GList L){
	int max,dep;
	GList pp;
	if(!L){
		return 1;//�ձ����Ϊ1
	}
	if(L->tag==ATOM){
		return 0;//ԭ�����Ϊ0
	}
	//�ݹ�����pp->a.ptr.hpΪͷָ����ӱ����
	for(max=0,pp=L;pp;pp=pp->a.ptr.tp){//��pp��ֵ����һ���ӱ�
		dep = GListDepth(pp->a.ptr.hp);//�ݹ�����һ��
		if(dep>max) max = dep;//��ȡÿ���ӱ��������
	}
	return max+1;//�ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1
}

// �жϹ�����Ƿ�Ϊ��
int GListEmpty(GList L){
	if(!L) return 1;
	else return 0;
}

// ȡ�����L��ͷ
GList getHead(GList L){
	GList h,p;
	if(!L){
		printf("Empty table has no head!\n");
		exit(0);
	}
	p = L->a.ptr.tp;//�����β
	L->a.ptr.tp = NULL;
	copyGList(&h,L);
	L->a.ptr.tp = p;//�黹��β
	return h;
}

// ȡ�����L��β
GList getTail(GList L){
	GList t;
	if(!L){
		printf("Empty table has no tail!\n");
		exit(0);
	}
	copyGList(&t,L->a.ptr.tp);
	return t;
}

// ����Ԫ��e��Ϊ�����L�ĵ�һԪ��(��ͷ��Ҳ�������ӱ�)
int insertFirst_GL(GList *L,GList e){
	GList p = (GList)malloc(sizeof(GLNode));//�������
	if(!p) exit(0);
	p->tag = LIST;
	p->a.ptr.hp = e;//��ͷΪ����Ԫ��
	p->a.ptr.tp = *L;//��βΪԭ����LԪ��
	*L = p;
	return 1;
}

// ɾ�������L�ĵ�һԪ�أ�����e������ֵ
int deleteFirst_GL(GList *L,GList *e){
	GList p;
	*e = (*L)->a.ptr.hp;//��*e���ر�ͷ
	p = *L;//ԭ���Ĺ����Lָ��
	*L = (*L)->a.ptr.tp;//����β���ɱ�L
	free(p);//ɾ����ͷ
	return 1;
}

// ���õݹ��㷨���������L
void traverse_GL(GList L,void(*v)(AtomType)){
	if(L){//L����
		if(L->tag == ATOM){//LΪ��ԭ��
			v(L->a.atom);
		}else{//LΪ�����
			traverse_GL(L->a.ptr.hp,v);//������ͷ
			traverse_GL(L->a.ptr.tp,v);//������β
		}
	}else printf("'NULL'");
}

// ���Ķ���˳��洢��ʾ
#define MaxStrLen 40 //�û�����255���ڶ�����󴮳�(1���ֽ�)
typedef char SString[MaxStrLen+1];//0�ŵ�Ԫ��Ŵ��ĵ�ǰ����

// ����һ����ֵ����chars�Ĵ�T
int strAssign(SString T,char *chars){
	int i;
	if(strlen(chars)>MaxStrLen) return 0;
	else{
		T[0] = strlen(chars);//��¼����
		//һ��һ���Ŀ������ַ�����־��Ҳ������
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		return 1;
	}
}

// �ɴ�S���Ƶô�T
int strCopy(SString T,SString S){
	int i;
	// һ��һ���Ŀ���
	for(i=0;i<=S[0];i++)
		T[i] = S[i];
	T[i] = '\0';//ע������ַ���������
	return 1;
}

// ��SΪ�մ����򷵻�1�����򷵻�0
int strEmpty(SString S){
	if(S[0]==0)	return 1;
	else return 0;
}

// ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
int strCompare(SString S,SString T){
	int i;
	for(i=1;i<=S[0]&&i<=T[0];i++){
		if(S[i]!=T[i]) return S[i]-T[i];
	}
	return S[0]-T[0];
}

// ���ش���Ԫ�ظ���
int strLength(SString S){
	return S[0];
}

// ��S��Ϊ�մ�
int clearString(SString S){
	S[0] = 0;//���Ϊ��
	return 1;
}

//�㷨4.3 P74
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
int subString(SString Sub,SString S,int pos,int len){
	int i;
	//�жϽ�ȡλ��pos�ĺϷ���
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1) return 0;
	//������1��ʼ��ֵ
	for(i=1;i<=len;i++){
		Sub[i] = S[pos+i-1];
	}
	Sub[i] = '\0';//�ǵú�������ַ���������
	Sub[0] = len;
	return 1;
}

//�㷨5.8 P117
//���ǿմ�str�ָ��������:hsubΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
void sever(SString str,SString hstr){
	int n,i,k;//k����δ��Ե������Ÿ���
	SString ch,c1,c2,c3;
	
	n = strLength(str);
	strAssign(c1,",");//����
	strAssign(c2,"(");//������
	strAssign(c3,")");//������
	subString(ch,str,1,1);//��ȡ��һ���ַ�
	//printf("\n%d,%s\n",n,ch);
	
	//���������ĵ�һ������
	//ch,c1�����,ch!=','
	for(i=1,k=0;i<=n&&strCompare(ch,c1)||k!=0;i++){
		subString(ch,str,i,1);//��i��ʼ��ȡһ���ַ�
		//printf("%s|k=%d\n",ch,k);
		//���ch=='('
		if(!strCompare(ch,c2)){
			k++;//�����Ÿ�����1
		}else if(!strCompare(ch,c3)){//���ch==')'
			k--;//�����Ÿ�����1
		}
	}
	//printf("\ni=%d,k=%d\n",i,k);
	if(i<=n){
		subString(hstr,str,1,i-2);
		subString(str,str,i,n-i+1);
	}else{
		strCopy(hstr,str);//��ñ�ͷ
		clearString(str);//��ձ�β
	}
}

//����ͷβ����洢�ṹ���ɹ�������д��ʽ��S���������L����emp="()"
int createGList(GList *L,SString S){
	SString sub,hsub,emp;//sub�洢��������ź���ַ�����hsub��sub��ȡ����ͷ��hsub��emp�洢"()"��ʾ�մ�
	GList p,q;
	
	strAssign(emp,"()");//�ַ����ĸ�ֵ
	if(!strCompare(S,emp)){
		*L = NULL;//�����ձ�
	}else{
		//��̬����
		*L = (GList)malloc(sizeof(GLNode));
		if(!*L){
			exit(0);
		}
		//������
		if(strLength(S)==1){//SΪ��ԭ��
			(*L)->tag = ATOM;//��ԭ�ӱ�־
			(*L)->a.atom = S[1];//������ԭ�ӹ����
			//printf("%c",(*L)->a.atom);
		}else{
			(*L)->tag = LIST;//������־
			p = *L;
			subString(sub,S,2,strLength(S)-2);//���������
			//�ظ���n���ӱ�
			do{
				//printf("%s\n",sub);
				sever(sub,hsub);//��sub�з������ͷ��hsub
				//printf("\n%s||%s\n",sub,hsub);//ԭ����sub�з����ͷ��hsub������ʣ��ĵ�sub
				createGList(&p->a.ptr.hp,hsub);//ʹ�ñ�ͷ�ݹ鴴���ӱ�
				q = p;//qָ���ӱ��ڵ�
				//������β
				if(!strEmpty(sub)){//ͨ��S[0]�жϱ�β����
					p = (GLNode*)malloc(sizeof(GLNode));
					if(!p) exit(0);
					p->tag = LIST;//�ӱ�����
					q->a.ptr.tp = p;//��β
				}
			}while(!strEmpty(sub));
			q->a.ptr.tp = NULL;
		}
	}
	return 1;
}

// ��ӡԭ��
void visit(AtomType e){
	printf("'%c' ",e);
}

int main(){
	// �����ı�ʾ��ʽ�ǣ��ձ�:(),��ԭ��:a,��:(a,(b),c,(d,(e)))
	//char p[80] = "(a,(b),c,(d,(e)))";
	char *p = "(a,(b),c,(d,(e)))";
	SString t;
	GList L,m;
	
	//��ʼ�������
	initGList(&L);
	initGList(&m);
	printf("GList L length = %d\n",GListLength(L));
	printf("GList L depth = %d \nL is empty?%d(1:yes,0:no)\n\n",GListDepth(L),GListEmpty(L));
	strAssign(t,p);//�ַ����ĸ�ֵ
	
	// ���������
	createGList(&L,t);
	printf("\nGList length = %d",GListLength(L));
	printf("\nGList depth = %d \nL is empty?%d(1:yes,0:no)\n",GListDepth(L),GListEmpty(L));
	printf("traverse GList L:\n");
	traverse_GL(L,visit);
	
	printf("\n\nCopy GList m = L\n");
	copyGList(&m,L);
	printf("GList m length = %d\n",GListLength(m));
	printf("GList m depth = %d\n",GListDepth(m));
	printf("traverse GList m:\n");
	traverse_GL(m,visit);
	// �ظ��õ�ʱ��ǵ����٣��൱�ڳ�ʼ��
	destroyGList(&m);
	
	// ��ñ�ͷ
	m = getHead(L);
	printf("\n\nm is the header of L,traverse GList m:\n");
	traverse_GL(m,visit);
	// �ظ��õ�ʱ��ǵ����٣��൱�ڳ�ʼ��
	destroyGList(&m);
	
	//��ñ�β
	m = getTail(L);
	printf("\n\nm is the tail of L,traverse GList m:\n");
	traverse_GL(m,visit);
	
	// ���뵽��ͷ
	insertFirst_GL(&m,L);
	printf("\n\nL insert into m to the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//ɾ����ͷ
	printf("\n\nDelete the header of m,traverse GList L,m:\n");
	deleteFirst_GL(&m,&L);//L���ɾ�����ͷ���
	printf("Deleted header L:\n");
	traverse_GL(L,visit);
	printf("\nDeleted rest M:\n");
	traverse_GL(m,visit);
	
	printf("\n");
	destroyGList(&L);
	destroyGList(&m);
	return 0;
}






