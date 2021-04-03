#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/**
 *
 * A password strength meter and a default password generator, 
 * as defined in the CS221 course website for Project 1.
 *
 */
bool isStrongPassword(const char* username, const char* password) {
    //len counts length of the password
	int len=0;
    int numcount=0;
    int upcount=0;
    int lowcount=0;
    //maxsubStri checks forthe largest substing length in password
    int maxsubStri=0;
    //This nested while loop checks for number, upper case and lower case letters in password as well as checks if there are invalid symbols
    while(*password!=0){
        const char *ch= username;
        //this while loop checks for when the substring in the password has exact characters as username
        while(*ch!=0){
            int userlen=0;
            int subStri=0;
            int counter=0;
            //kgo variable used to continue looping through password as long as cahracters match not case sensitive
            bool kgo=true;
            while((*(password+userlen)!=0)&&kgo==true){
                if(*(password+userlen)-*(ch+userlen)==32){
                    ++userlen;
                }else if(*(password+userlen)-*(ch+userlen)==-32){
                    ++userlen;
                }else if(*(password+userlen)-*(ch+userlen)==0){
                    ++userlen;
                }else{
                    kgo=false;
                }
                
            }
            //counts substring length
            while(*(password+counter)>=65&&*(password+counter)<=122){
                counter++;
                subStri++;
            }
            //updates maxsub if substri is larger
            if(subStri>maxsubStri){
                maxsubStri=subStri;
            }
            //returns false if userlength equals to substring checker
            if(userlen==strlen(username)){
                return false;
            }
            ch++;
            
        }
        //checks if char is a number
        if(*password>=48&&*password<=57){

            len++;
            numcount++;

        }
        //checks if char is lower case letter
        if(*password>=97&&*password<=122){

            len++;
            lowcount++;

        }
        //checks if cahr is an uppercase letter
        if(*password>=65&&*password<=90){

            len++;
            upcount++;

        }
        //returns false if neither a nubmer, upper or lower case letter
        if(*password>=32 && *password<=47){
            return false;
        }
        if(*password>=58 && *password<=64){
            return false;
        }
        if(*password>=91&& *password<=96){
            return false;
        }
        if(*password>=123){
            return false;
        }
        password++;

    }
    //checks if has at least 1 uppercase, 1 lowercase, 1 number, substring>4 else returns false
    if(upcount>=1&&lowcount>=1&&numcount>=1&&len>=8&& maxsubStri>=4){
        //printf("upcount: %d| lowcount: %d | numcount: %d | len: %d | maxsubStri: %d\n", upcount, lowcount,numcount,len,maxsubStri);
        //printf("Password is Strong\n");
        return true;
    }else{
        //printf("upcount: %d| lowcount: %d | numcount: %d | len: %d | maxsubStri: %d\n", upcount, lowcount,numcount,len,maxsubStri);
        //printf("Password is weak\n");
        return false;
    }
}

/** 
 * Example: isStrongDefaultPassword("vahab", "Taher3h") returns false
 */
bool isStrongDefaultPassword(const char* username, const char* password) {
    //this chekcs for number, upper and lower case requirements aswell as length requriement
	int cap=0;
	int low=0;
	int num=0;
    int length=0;
    while(*password!=0){

        const char *ch= username;
        while(*ch!=0){
            //while loop checks if default generated password has username
            int userlen=0;
            bool kgo=true;
            while((*(password+userlen)!=0)&&kgo==true){
                if(*(password+userlen)-*(ch+userlen)==32){
                    ++userlen;
                }else if(*(password+userlen)-*(ch+userlen)==-32){
                    ++userlen;
                }else if(*(password+userlen)-*(ch+userlen)==0){
                    ++userlen;
                }else{
                    kgo=false;
                }

                
            }

            if(userlen==strlen(username)){

                return false;
            }

            ch++;
            
        }
        // increments number count, uppercase count and lowerrcase count if found
        if(*password>=48&&*password<=57){

            length++;
            num++;

        }
        if(*password>=97&&*password<=122){

            length++;
            low++;

        }
        if(*password>=65&&*password<=90){

            length++;
            cap++;

        }
        password++;

    }
    //returns true if there is at least 1 capital, 1 lower, 1 number and legnth greater than 8
    if(cap>0&&low>0&&length>8&&num>0){

        return true;
    }else{

        return false;
    }
    
    
	
}

/** 
 * This function may *not* call isStrongPassword(). 
 * This function must call isStrongDefaultPassword().
 */
void generateDefaultPassword(char* default_password, const char * username) {
	//TODO: your code goes here.
	printf("Generating default Password...\n");
    //bool variable is to make password generator run until isStrongDefault reutnrs true
    bool isStrong=false;
    while(isStrong==false){
        //random number generator for default pass length, goes between 1 and 15
        int deflen= (rand()%(15-1+1))+1;
        //variable cahr is basically password holder, has deflen+1 so null can be added to the end
    	char string[deflen+1];
		int lenCount=0;
        //rUp, rLow and rInt are jsut random number generators to get ASCII values to be placed in default password
		int rUp= (rand()%(90-65+1))+65;
		int rLow= (rand()%(122-97+1))+97;
		int rInt=(rand()%(57-48+1))+48;
		while(lenCount<deflen){
            //whatCh bascially determiens if a number, uppercase or lower case is put in string, all randomly
			int whatCh=(rand()%(3-1+1))+1;
			if(whatCh==1){
				string[lenCount]=(char)rUp;
			}
			if(whatCh==2){
				string[lenCount]=(char)rLow;
			}
			if(whatCh==3){
				string[lenCount]=(char)rInt;
			}
            //after adding characters it then resets r varaibles to get a new number for ASCII value
			rUp= (rand()%(90-65+1))+65;
			rLow= (rand()%(122-97+1))+97;
			rInt=(rand()%(57-48+1))+48;
			lenCount++;
		}
        //makes last item in string a null pointer
		string[lenCount]=0;
		isStrong=isStrongDefaultPassword(username, string);
        //changes isStrong bool vraible depending in is Strongdefault checker
        //if true, it copies string into default password pointer
		if(isStrong==true){
			printf("Default Password Generated: %s\n", string);
			strcpy(default_password,string);
		}
    }
	
	
	

	
}

int main(void) 
{
	char user[51];
    //user input
	char pass[51];
    //pasword input
	char dpass[51];
    //randomly generated password holder
	char firstp[51];
    //user input for generated default password
	srand(time(0));
	printf("Enter User: \n");
	scanf("%s", user);
	
    
	
	
	generateDefaultPassword(dpass,user);
	printf("User: %s \n", user);
	printf("Default password is : %s\n", dpass);
	printf("Enter defualt password\n");
	scanf("%s", firstp);
	if(strcmp(firstp,dpass)==0){
		printf("You entereed it correctly\n");
	}else{
		printf("You typed something wrong\n");
	}
    printf("Enter Password your own password:\n");
	scanf("%s",pass);
    if(isStrongPassword(user,pass)==false){
		printf("Weak password\n");
	}else{
		printf("Strong Password\n");
	}

	return 0;
}