#include <stdio.h>
char* longestPalindrome(char* s);
int find_s(char* s, int l, int r);
int main(){

	char s[] =  "cbbd";
	longestPalindrome(s);
	return 0;
}
char* longestPalindrome(char* s) {
	int i=0;
	int l;
	int res = 0;
	int tmp;
	char* ps;
	char flag=1;
	int len;
	int len_ = 0;
	if(s[1]=='\0')
		return s;
	else{
		while(s[i]!='\0'){
			l = find_s(s,i,i);
			tmp = (i-l);
			len = 1+tmp<<1;
			if(len>len_){
				res = tmp;
				ps = &s[l];
				flag=0;
				len_=len;
			}
			
			l = find_s(s,i,i+1);
			if(i-l<0)
				tmp = 0;
			else
				tmp = i-l+1;
			len = tmp<<1;
			if(len>len_){
				res = tmp;
				ps = &s[l];
				flag=1;
				len_=len;
			}
			i++;
		}
		if(res==0) return NULL;
		else{
			if(flag)
				*(ps+(res<<1))='\0';
			else 
				*(ps+(res<<1)+1)='\0';
			printf("i=%d\n",i );
			printf("res=%d\n",res);
			printf("%s\n",ps);
			return ps;
		}
	}
}

int find_s(char* s, int l, int r){
	while(s[l]==s[r] && l>=0 && s[r]!='\0'){
		l-=1;
		r+=1;
		//printf("%d\n",l);
	}

	return l+1;
}