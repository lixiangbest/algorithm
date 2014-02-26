/*
* ���õ�Ԫ�ռ� P210
* �㷨8.3
* 2012-09-22
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// �ӱ�־��Ĺ�����ͷβ����洢��ʾ
typedef enum{
	ATOM,//ATOM==0:ԭ��
	LIST //LIST==1:�ӱ�
}ElemTag;

typedef char AtomType;//����ԭ������Ϊ�ַ���

// ���������
typedef struct GLNode{
	int mark;//��¼��־��Ϊ0����¼��hp�У�Ϊ1��¼��tp��
	ElemTag tag;//�������֣���������ԭ�ӽ��ͱ���
	union{
		AtomType atom;//atom��ԭ�ӽ���ֵ��AtomType���û�����
		struct{
			struct GLNode *hp,*tp;
		}ptr;//ptr�Ǳ����ָ����,ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
	}a;
}*GList,GLNode;

// ���Ķ���˳���ʾ
#define MaxStrlen 40//�û�����255���ڶ�����󴮳�(1���ֽ�)
typedef char SString[MaxStrlen+1];//0�ŵ�Ԫ��Ŵ��ĵ�ǰ����

//����һ����ֵ����chars�Ĵ�T
int strAssign(SString T,char *chars){
	int i;
	if(strlen(chars)>MaxStrlen) return 0;
	else{
		T[0] = strlen(chars);//��¼����
		//һ��һ���Ŀ������ַ���������Ҳ������
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		T[i] = '\0';
		return 1;
	}
}

//�ɴ�S���Ƶô�T
int strCopy(SString T, SString S){
	int i;
	//һ��һ���Ŀ���
	for(i=0;i<=S[0];i++)
		T[i] = S[i];
	T[i] = '\0';
	return 1;
}

//��SΪ�մ����򷵻�1�����򷵻�0
int strEmpty(SString S){
	if(S[0]==0) return 1;
	else return 0;
}

//��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
int strCompare(SString S,SString T){
	int i;
	for(i=1;i<=S[0]&&i<=T[0];i++){
		if(S[i]!=T[i]) return S[i]-T[i];
	}
	return S[0]-T[0];
}

//���ش���Ԫ�ظ���
int strLength(SString S){
	return S[0];
}

//��S��Ϊ�մ�
int clearString(SString S){
	S[0] = 0;//���Ϊ0
	return 1;
}

//�㷨4.3 P74
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
int subString(SString Sub,SString S,int pos,int len){
	int i;
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1) return 0;
	for(i=1;i<=len;i++){
		Sub[i] = S[pos+i-1];
	}
	Sub[i] = '\0';
	Sub[0] = len;
	return 1;
}

//�㷨5.8 P117
//���ǿմ�str�ָ��������:hsubΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
void sever(SString str,SString hstr){
	int n,i,
		k;//k����δ��Ե������Ÿ���
	SString ch,c1,c2,c3;
	
	n = strLength(str);
	strAssign(c1,",");
	strAssign(c2,"(");
	strAssign(c3,")");
	subString(ch,str,1,1);
	//���������ĵ�һ������
	for(i=1,k=0;i<=n&&strCompare(ch,c1)||k!=0;i++){
		subString(ch,str,i,1);
		if(!strCompare(ch,c2)) k++;
		else if(!strCompare(ch,c3)) k--;
	}
	if(i<=n){
		subString(hstr,str,1,i-2);
		subString(str,str,i,n-i+1);
	}else{
		strCopy(hstr,str);
		clearString(str);
	}
}

//����ͷβ����洢�ṹ���ɹ�������д��ʽ��S���������L����emp="()"
int createMarkGList(GList *L,SString S){
	SString sub,hsub,emp;
	GList p,q;
	strAssign(emp,"()");
	if(!strCompare(S,emp)) *L = NULL;//�����ձ�
	else{
		*L = (GList)malloc(sizeof(GLNode));
		if(!*L) exit(0);//������
		//printf("%d\n",strLength(S));exit(0);
		if(strLength(S)==1){//SΪ��ԭ��
			(*L)->tag = ATOM;//��ԭ�ӱ�־
			(*L)->a.atom = S[1];//������ԭ�ӹ����
			(*L)->mark = 0;//��¼��־��ʼ��Ϊ0
		}else{
			(*L)->tag = LIST;//������־
			(*L)->mark = 0;//��¼��־��ʼ��Ϊ0
			p = *L;
			subString(sub,S,2,strLength(S)-2);//���������
			//printf("%s||%s",S,sub);exit(0);
			do{
				//�ظ���n���ӱ�
				sever(sub,hsub);//��sub�з������ͷ��hsub
				//printf("%s||%s",sub,hsub);exit(0);
				createMarkGList(&p->a.ptr.hp,hsub);
				q = p;
				if(!strEmpty(sub)){//��β����
					p = (GLNode*)malloc(sizeof(GLNode));
					if(!p) exit(0);
					p->tag = LIST;
					p->mark = 0;//��¼��־��ʼ��Ϊ0
					q->a.ptr.tp = p;
				}
			}while(!strEmpty(sub));
			q->a.ptr.tp = NULL;
		}
	}
	return 1;
}

// �㷨8.3 P210
// �����ǿչ����GL(GL!=NULL��GL->mark==0),�Ա�������δ�ӱ�־�Ľ��ӱ�־
// �����Ǵ�ֵ���Ǵ���ַ��GL���䣬����ָ���ֵ���
void markList(GList GL){
	GList t,p,q;
	int finished;
	if(GL!=NULL&&GL->mark==0){
		t = NULL;//tָʾp��ĸ��
		p = GL;//pָ�������ͷ
		finished = 0;//��־�Ƿ����
		while(!finished){
			//���ȶԱ�ͷ���б�־
			while(p->mark==0){//�ж�p��ָ��Ԫ���Ƿ��Ѿ���־��
				//δ��־���������б�־
				p->mark = 1;//markHead(p)��ϸ��
				q = p->a.ptr.hp;//qָ��*p�ı�ͷ
				if(q&&q->mark==0){
					if(q->tag==0){
						q->mark = 1;//ATOM,��ͷΪԭ�ӽ��
					}else{//�Ǳ�
						//���������ӱ�
						p->a.ptr.hp = t;//pͷָ��ָ����ĸ��
						//printf("%d\n",t);exit(0);
						//p�Ѿ���־�ˣ����Ա�־Ϊԭ�ӣ�����û�����ף������˺ܾ�
						p->tag = ATOM;
						t = p;//ĸ��tָ��p
						p = q;//��p��ָ����q
					}
				}
			}
			//��ɶԱ�ͷ�ı�־����ʼ�Ա�β���б�־
			q = p->a.ptr.tp;//qָ��*p�ı�β
			if(q&&q->mark==0){
				//����������β
				p->a.ptr.tp = t;//p��βָ��ָ����ĸ��t
				t = p;//ĸ��tָ��p
				p = q;//��p��ָ����q
			}else{
				while(t&&t->tag==1){//ĸ��t�Ǳ��㣬��ӱ�β����
					q = t;
					//���ڼ�¼��־��1������tָ����ԭ��ָ���Ԫ�ؼ���ʱ��q��βָ��
					t = q->a.ptr.tp;
					q->a.ptr.tp = p;
					p = q;
				}
				if(!t)	finished = 1;//����
				else{
					//�ӱ�ͷ����
					q = t;
					//���ڼ�¼��־��0������tָ����ԭ��ָ���Ԫ�ؼ���ʱ��q��ͷָ��
					t = q->a.ptr.hp;
					q->a.ptr.hp = p;
					p = q;
					p->tag = LIST;
				}
				//����������β
			}
		}
	}
}

// ���õݹ��㷨���������L
void traverse_GL(GList L,void(*v)(GList)){
	if(L){//L����
		//LΪ��ԭ��
		if(L->tag==ATOM) v(L);
		else{//LΪ�����
			v(L);
			traverse_GL(L->a.ptr.hp,v);
			traverse_GL(L->a.ptr.tp,v);
		}
	}else printf("NULL\n");
}

void visit(GList p){
	if(p->tag==ATOM)
		printf("mark=%d %c\n",p->mark,p->a.atom);
	else
		printf("mark=%d list\n",p->mark);
}

main(){
	SString t;
	GList list;
	
	// �����ı�ʾ��ʽ�ǣ��ձ�:(),��ԭ��:a,��:(a,(b),c,(d,(e)))
	//char p[80] = "(a,(b),c,(d,(e)))";
	char *p = "(a,(b),c,(d,(e)))";
	strAssign(t,p);
	createMarkGList(&list,t);
	traverse_GL(list,visit);;
	
	// �ӱ�־
	markList(list);
	printf("\nAfter marked:\n");
	traverse_GL(list,visit);
	
	return 0;
}