#include<stdio.h>

int main(int argc,char **argv){
	int arr[15] = {60,54,51,46,43,40,39,37,36,32,27,20,19,16,8};
	int find=32,start=0,end=14,index=(end+start)/2;
	do{
		if(arr[index]==find){
			printf("the special val index of arr is:%d\n",index);
			break;
		}else if(arr[index]<find){
			end = index-1;
		}else if(arr[index]>find){
			start = index+1;
		}
		index = (end+start)/2;
	}while(start<end);
	if(start>=end) printf("the special val index of arr is not found.");
}