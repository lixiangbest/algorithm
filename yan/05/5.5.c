/*
* ���ݽṹC���԰� ��������չ������洢��ʾ��ʵ��
* P110
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

//��������չ��������洢��ʾ
typedef struct GLNode{
	ElemTag tag;//�������֣���������ԭ�ӽ��ͱ���
	union{
		AtomType atom;//atom��ԭ�ӽ���ֵ��AtomType���û�����
		struct GLNode *hp;//����ı�ͷָ��
	}a;
	struct GLNode *tp;//�൱�����������next,ָ����һ��Ԫ�ؽ��
}*GList,GLNode;//���������GList��һ����չ����������

typedef struct{
	char *ch;//���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length;//������
}HString;

// ��ʼ��(�����մ�)�ַ���T
void initString(HString *T){
	T->length = 0;
	T->ch = NULL;
}

// ����һ����ֵ���ڴ�����chars�Ĵ�T
int strAssign(HString *T,char *chars){
	int i,j;
	if(T->ch) free(T->ch);//�ͷ�Tԭ�пռ�
	i = strlen(chars);//��chars�ĳ���i
	if(!i){//chars�ĳ���Ϊ0
		T->ch = NULL;
		T->length = 0;
	}else{//chars�ĳ��Ȳ�Ϊ0
		T->ch = (char*)malloc((i+1)*sizeof(char));//���䴮�ռ�
		if(!T->ch){
			exit(0);//���䴮�ռ�ʧ��
		}
		for(j=0;j<i;j++){//������
			T->ch[j] = chars[j];
		}
		T->ch[j] = '\0';
		T->length = i;
	}
	return 1;
}

// �ɴ�S���Ƶô�T
int strCopy(HString *T,HString S){
	int i;
	if(T->ch) free(T->ch);//�ͷ�Tԭ�пռ�
	T->ch = (char*)malloc((S.length+1)*sizeof(char));//���䴮�ռ�
	if(!T->ch) exit(0);//���䴮�ռ�ʧ��
	for(i=0;i<S.length;i++){//������
		T->ch[i] = S.ch[i];
	}
	T->ch[i] = '\0';
	(*T).length = S.length;
	return 1;
}

// ��SΪ�մ����򷵻�1�����򷵻�0
int strEmpty(HString S){
	if(S.length==0&&S.ch==NULL)	return 1;
	else return 0;
}

// ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
int strCompare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++){
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
}

// ����S��Ԫ�ظ�������Ϊ���ĳ���
int strLength(HString S){
	return S.length;
}

// ��S��Ϊ�մ�
int clearString(HString *S){
	if(S->ch){
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return 1;
}

//�㷨4.3 P74
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
int subString(HString *Sub,HString S,int pos,int len){
	int i;
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1) return 0;
	if(Sub->ch) free(Sub->ch);//�ͷžɿռ�
	if(!len){//���Ӵ�
		Sub->ch = NULL;
		Sub->length = 0;
	}else{//�����Ӵ�
		Sub->ch = (char*)malloc((len+1)*sizeof(char));
		if(!Sub->ch) exit(0);
		for(i=0;i<len;i++)
			Sub->ch[i] = S.ch[pos-1+i];
		Sub->ch[i] = '\0';
		Sub->length = len;
	}
	return 1;
}

// �����յĹ����L
int initGList(GList *L){
	*L = NULL;
	return 1;
}

// ���ǿմ�str�ָ��������:hstrΪ��һ��','֮ǰ���Ӵ�,strΪ֮����Ӵ�
int sever(HString *str,HString *hstr){
	int n,i=1,
		k=0;//k����δ��Ե������Ÿ���
	HString ch,c1,c2,c3;
	initString(&ch);//��ʼ��HString���͵ı���
	initString(&c1);
	initString(&c2);
	initString(&c3);
	strAssign(&c1,",");
	strAssign(&c2,"(");
	strAssign(&c3,")");
	n = strLength(*str);
	do{
		subString(&ch,*str,i,1);
		if(!strCompare(ch,c2)) k++;
		else if(!strCompare(ch,c3)) k--;
		i++;
	}while(i<=n&&strCompare(ch,c1)||k!=0);
	if(i<=n){
		strCopy(&ch,*str);
		subString(hstr,ch,1,i-2);
		subString(str,ch,i,n-i+1);
	}else{
		strCopy(hstr,*str);
		clearString(str);
	}
	return 1;
}

// ��S���������L
int createGList(GList *L,HString S){
	HString sub,hsub,emp;
	GList p;
	
	initString(&emp);//��ʼ���ַ���
	initString(&sub);
	initString(&hsub);
	strAssign(&emp,"()");//��emp="()"
	*L = (GList)malloc(sizeof(GLNode));
	if(!*L) exit(0);//�����㲻�ɹ�
	
	//�����ձ�
	if(!strCompare(S,emp)){//���Ϊ�ձ�
		(*L)->tag = LIST;
		(*L)->a.hp = NULL;
		(*L)->tp = NULL;
	}else if(strLength(S)==1){//������ԭ�ӹ����
		(*L)->tag = ATOM;
		(*L)->a.atom = S.ch[0];
		(*L)->tp = NULL;
	}else{//����һ���
		(*L)->tag = LIST;
		(*L)->tp = NULL;
		subString(&sub,S,2,strLength(S)-2);//���������
		sever(&sub,&hsub);//��sub�з��������ͷ��hsub
		//printf("\n%s||%s\n",sub.ch,hsub.ch);
		createGList(&(*L)->a.hp,hsub);//������ͷ���
		p = (*L)->a.hp;
		while(!strEmpty(sub)){//��β���գ����ظ���n���ӱ�
			sever(&sub,&hsub);//��sub�з������ͷ��hsub
			//printf("\n%s||%s\n",sub.ch,hsub.ch);exit(0);
			createGList(&p->tp,hsub);//������һ��Ԫ��
			p = p->tp;
		}
	}
	return 1;
}

//���ٹ����L
void destroyGList(GList *L){
	GList ph,pt;
	if(*L){//L��Ϊ�ձ�
		//��ph��pt����L������ָ��
		if((*L)->tag){//���ӱ�
			ph = (*L)->a.hp;
		}else{//��ԭ��
			ph = NULL;
		}
		pt = (*L)->tp;
		free(*L);//�ͷ�L��ָ���
		*L = NULL;//��LΪ��
		destroyGList(&ph);//�ݹ����ٱ�ph
		destroyGList(&pt);//�ݹ����ٱ�pt
	}
}

// �ɹ����L���Ƶõ������T
int copyGList(GList *T,GList L){
	if(!L){//Ϊ�գ����ƿձ�
		*T = NULL;
		return 1;
	}
	*T = (GList)malloc(sizeof(GLNode));//������
	if(!*T) exit(0);
	(*T)->tag = L->tag;//����ö�ٱ���
	if(L->tag==ATOM){//���ƹ����岿��
		(*T)->a.atom = L->a.atom;//���Ƶ�ԭ��
	}else{
		//�����ӱ�
		copyGList(&(*T)->a.hp,L->a.hp);
	}
	if(L->tp==NULL){//����β
		(*T)->tp = L->tp;
	}else{
		copyGList(&(*T)->tp,L->tp);//������һ��Ԫ��
	}
	return 1;
}

// ��������L�ĳ��ȣ���Ԫ�ظ���
int GListLength(GList L){
	int len = 0;
	GList p;
	
	if(L->tag==LIST&&!L->a.hp){//�ձ�
		return 0;//�ձ���0
	}else if(L->tag==ATOM){//��ԭ�ӱ�
		return 1;
	}else{//һ���
		p = L->a.hp;
		do{
			len++;
			p = p->tp;
		}while(p);
		return len;
	}
}

// ������L�����
int GListDepth(GList L){
	int max,dep;
	GList pp;
	if(L==NULL||L->tag==LIST&&!L->a.hp){
		return 1;//�ձ����Ϊ1
	}else if(L->tag==ATOM){
		return 0;//��ԭ�ӱ����Ϊ0
	}else{//��һ�������
		for(max=0,pp=L->a.hp;pp;pp=pp->tp){
			dep = GListDepth(pp);//����ppΪͷָ����ӱ����
			if(dep>max) max = dep;
		}
	}
	return max+1;//�ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1
}

// �ж������L�Ƿ�Ϊ��
int GListEmpty(GList L){
	if(!L||L->tag==LIST&&!L->a.hp) return 1;
	else return 0;
}

// ȡ�����L��ͷ
GList getHead(GList L){
	GList h;
	initGList(&h);
	if(!L||L->tag==LIST&&!L->a.hp){
		printf("\nEmpty table has no head!");
		exit(0);
	}
	h = (GList)malloc(sizeof(GLNode));
	if(!h) exit(0);
	h->tag = L->a.hp->tag;
	h->tp = NULL;
	if(h->tag==ATOM){
		h->a.atom = L->a.hp->a.atom;
	}else{
		copyGList(&h->a.hp,L->a.hp->a.hp);
	}
	return h;
}

// ȡ�����L��β
GList getTail(GList L){
	GList T;
	if(!L){
		printf("Empty table has no head!\n");
		exit(0);
	}
	T = (GList)malloc(sizeof(GLNode));
	if(!T) exit(0);
	T->tag = LIST;
	T->tp = NULL;
	copyGList(&T->a.hp,L->a.hp->tp);
	return T;
}

// ����Ԫ��e��Ϊ�����L�ĵ�һԪ��(��ͷ��Ҳ�������ӱ�)
int insertFirst_GL(GList *L,GList e){
	GList p = (*L)->a.hp;
	(*L)->a.hp = e;
	e->tp = p;
	return 1;
}

// ɾ�������L�ĵ�һԪ�أ�����e������ֵ
int deleteFirst_GL(GList *L,GList *e){
	if(*L){
		*e = (*L)->a.hp;
		(*L)->a.hp = (*e)->tp;
		(*e)->tp = NULL;
	}else *e = *L;
	return 1;
}

// ���õݹ��㷨���������L
void traverse_GL(GList L,void(*v)(AtomType)){
	GList hp;
	if(L){//L����
		if(L->tag == ATOM){//LΪ��ԭ��
			v(L->a.atom);
			//hp = NULL;
		}else{//LΪ�ӱ�
			hp = L->a.hp;
			traverse_GL(hp,v);//������ͷ
		}
		traverse_GL(L->tp,v);//������β
	}else printf("'NULL'");
}

void visit(AtomType e){
	printf("%c ",e);
}

main(){
	// �����ı�ʾ��ʽ�ǣ��ձ�:(),��ԭ��:a,��:(a,(b),c,(d,(e)))
	// char p[80] = {"(a,(b),c,(d,(e)))"};
	char *p;
	GList L,m;
	HString t;
	initString(&t);
	initGList(&L);
	initGList(&m);
	printf("Empty GList L depth = %d;L is empty?%d(1:yes 0:no)\n",GListDepth(L),GListEmpty(L));
	printf("Please enter GList L(type: empty:(),sigle:a,other:(a,(b),c))\n");
	//gets(p);
	p = "(a,(b),c,(d,(e)))";
	
	//�ַ�����ֵ
	strAssign(&t,p);
	//printf("\n%s\n",t);
	createGList(&L,t);
	printf("GList L length = %d\n",GListLength(L));
	printf("GList L depth = %d;L is empty?%d(1:yes 0:no)\n",GListDepth(L),GListEmpty(L));
	printf("Traverse Glist L:\n");
	traverse_GL(L,visit);
	
	//�������
	printf("\n\nCopy GList m=L\n");
	copyGList(&m,L);
	printf("GList m length= %d\n",GListLength(m));
	printf("GList m depth= %d\n",GListDepth(m));
	printf("Traverse Glist m:\n");
	traverse_GL(m,visit);
	destroyGList(&m);
	
	//��ñ�ͷ
	m = getHead(L);
	printf("\n\nm is the header of L,traverse GList m:\n");
	traverse_GL(m,visit);
	// �ظ��õ�ʱ��ǵ����٣��൱�ڳ�ʼ��
	destroyGList(&m);
	
	//��ñ�β
	m = getTail(L);
	printf("\n\nm is the tail of L,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//���뵽��ͷ
	insertFirst_GL(&m,L);
	printf("\n\nL insert into m to the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//ɾ����ͷ
	deleteFirst_GL(&m,&L);
	printf("\n\nDelete the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	printf("\n");
	destroyGList(&m);
	return 0;
}




