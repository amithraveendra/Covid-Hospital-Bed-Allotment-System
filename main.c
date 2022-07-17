#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include<mysqld_error.h>
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

char HOST[]="localhost";
char USER[] = "root";
char PASS[]="sairam";

int main()
 {  
 	MYSQL* obj;
 	
 	int P_ID;
	char P_NAME[20];
	long int PH_NO;
	char ADDRESS[100];
	int AGE;
	char RESULT[10];
	int choice;
    char password[10],req[5];
    

	int p,m;
	bool ProgramIsOpened = true;
	int answer;
	
	char consult[1024]={};
	char* sentence;
	char sentence_aux[500];
    printf("\n HOSPITAL BED ALLOTMENT FOR COVID PATIENTS\n\n");
	
	
	if(!(obj = mysql_init(0)))
    	printf("\n Error: MySql object not created \n");
	
	else 
	{
		if(!mysql_real_connect(obj,HOST,USER,PASS,"PBL",3306,NULL,0))
		
			printf("\n Could'nt log in \n");
		
		else
		{
				printf("\n Logged in Successfully!!!\n\n\n");
			    printf("1.Registering the patient \n2.Allotment of bed for registered patient\n3.Displaying the Patient Details\n4.Exit\n\n\n");
	            for(;;)
            	{ 
	            printf("\n-----------------------------------------------------------------------------------------\n");
	            printf("\n Please enter your choice : ");
	            scanf("%d",&choice);
	            switch(choice)
	            {
	        	case 1:  printf("\n REGISTERING A PATIENT");
	    	        printf("\n Please enter the password : ");
	    	        scanf("%s",password);
	    	        if(strcmp(password,"SAIRAM")==0)
	    	        {
                    	if(ProgramIsOpened)
			        	{
					   printf("\n Enter patient ID : ");
					   scanf("%d", &P_ID);
					   printf("\n Enter patient Name : ");
					   scanf("%s", P_NAME);
					   printf("\n Enter patient Phone number : ");
					   scanf("%ld", &PH_NO);
					   printf("\n Enter patient Address : ");
					   scanf("%s", ADDRESS);
					   printf("\n Enter patient's age : ");
					   scanf("%d", &AGE);
					   printf("\n Covid Result : ");
					   scanf("%s", RESULT);
					   
					  
					   snprintf(consult,1024,"INSERT INTO PATIENT(P_ID,P_NAME,PH_NO,ADDRESS,AGE,RESULT) VALUES(%d,'%s',%ld,'%s',%d,'%s')",P_ID,P_NAME,PH_NO,ADDRESS,AGE,RESULT);
					   mysql_query(obj, consult);
					   printf("\nInfo added successfully\n");
				    	}
					    if(strcmp(RESULT,"positive")==0)
					   {
					   	   printf("\n Is the hospital bed required?\n");
					   	   scanf("%s",req);
					   	   if(strcmp(req,"yes")==0)
					   	   {   
					   	      printf("\n Hospital list is of the order\n Hospital Id\n Hospital Name\n District \n Total beds \n Available Beds\n");
							  if (mysql_query(obj, "SELECT * FROM HOSPITAL"))
                              {
                                  finish_with_error(obj);
                              }
                             MYSQL_RES *result = mysql_store_result(obj);

                            if (result == NULL)
                              {
                                   finish_with_error(obj);
                               }

                            int num_fields = mysql_num_fields(result),i;

                            MYSQL_ROW row;

                            while ((row = mysql_fetch_row(result)))
                            {
                                 for( i = 0; i < num_fields; i++)
                                 {
                                     printf("%s ", row[i] ? row[i] : "NULL");
                                 }

                                 printf("\n");
                            }

                             mysql_free_result(result);
                             

                             printf("\n ENTER HOSPITAL ID OF ADMISSION :");
                             int c;
                             char consult2[1024]={};
                             scanf("%d",&c);
                             snprintf(consult2,1024,"SELECT AVAILABLE_BEDS FROM HOSPITAL WHERE H_ID=%d",c);
                             
                             snprintf(consult2,1024,"UPDATE HOSPITAL SET AVAILABLE_BEDS=AVAILABLE_BEDS-1 WHERE H_ID=%d",c);
                             char consult3[1024]={};
                             mysql_query(obj,consult2);
                             snprintf(consult3,1024,"UPDATE PATIENT SET H_ID=%d WHERE P_NAME='%s'",c,P_NAME);
                             mysql_query(obj,consult3);
                             snprintf(consult3,1024,"INSERT INTO TIME VALUES(CURDATE(),CURTIME(),CURDATE()+14,%d,%d)",c,P_ID);
                             mysql_query(obj,consult3);
                             
                             
                            }
						    else
						    printf("\n You are advised 14 days of home isolation. Our officials will check on your health everyday,\n Stay safe\n Hope you'll recover soon!\n We'll pray for your recovery\n THANK YOU!'");
					   	   
					   }
					   else
					   printf("\n Good to know that you are safe. Please wear mask and maintain social distancing.\n THANK YOU!\n");
				
		
	                }
				    else
					{
					
				    printf("\n Wrong password!! \n Please try again\n");
					}
					break;
					
					
				case 2: printf("\n ALLOTMENT OF BED");
	    	            printf("\n Please enter the password : ");
	    	            scanf("%s",password);
	    	            if(strcmp(password,"SAIRAM")==0)
	    	            {
						
				        int a;
				        printf("\n Enter the patient's ID : ");
				        scanf("%d",&a);
				        printf("\n Hospital list is of the order\n Hospital Id\n Hospital Name\n District \n Total beds \n Available Beds\n");
							  if (mysql_query(obj, "SELECT * FROM HOSPITAL"))
                              {
                                  finish_with_error(obj);
                              }
                             MYSQL_RES *result = mysql_store_result(obj);

                            if (result == NULL)
                              {
                                   finish_with_error(obj);
                               }

                            int num_fields = mysql_num_fields(result),i;

                            MYSQL_ROW row;

                            while ((row = mysql_fetch_row(result)))
                            {
                                 for( i = 0; i < num_fields; i++)
                                 {
                                     printf("%s ", row[i] ? row[i] : "NULL");
                                 }

                                 printf("\n");
                            }

                             mysql_free_result(result);
                             

                             printf("\n ENTER HOSPITAL ID OF ADMISSION :");
                             int c;
                             char consult2[1024]={};
                             scanf("%d",&c);
                             snprintf(consult2,1024,"UPDATE HOSPITAL SET AVAILABLE_BEDS=AVAILABLE_BEDS-1 WHERE H_ID=%d",c);
                             char consult3[1024]={};
                             mysql_query(obj,consult2);
                             snprintf(consult3,1024,"UPDATE PATIENT SET H_ID=%d WHERE P_ID=%d",c,a);
                             mysql_query(obj,consult3);
                             snprintf(consult3,1024,"INSERT INTO TIME VALUES(CURDATE(),CURTIME(),CURDATE()+14,%d,%d)",c,a);
                             mysql_query(obj,consult3);
                         }
                         else
                         {
                         	printf("\n Wrong password!! \n Please try again\n");
						 }
						 break;
                case 3:  
                        
				        printf("\n Enter Patient ID : ");
                        scanf("%d",&p);
                        printf("\n \n Patient Name\n Patient ID\n RESULT\n Hospital ID\n Date of admission\n Time of admission\n\n");
                        char consult2[1024]={};
                        snprintf(consult2,1024,"SELECT P_NAME,TIME.P_ID,RESULT,TIME.H_ID,DOA,TOA FROM PATIENT,TIME WHERE PATIENT.P_ID=%d AND PATIENT.P_ID=TIME.P_ID",p);
				            
							 if (mysql_query(obj,consult2))
                              {
                                  finish_with_error(obj);
                              }
                             MYSQL_RES *result = mysql_store_result(obj);

                            if (result == NULL)
                              {
                                   finish_with_error(obj);
                               }

                            int num_fields = mysql_num_fields(result),i;

                            MYSQL_ROW row;

                            while ((row = mysql_fetch_row(result)))
                            {
                                 for( i = 0; i < num_fields; i++)
                                 {
                                     printf("%s ", row[i] ? row[i] : "NULL");
                                 }

                                 printf("\n");
                            }

                             mysql_free_result(result);
                             break;
                            
                                       
	        	case 4: exit(0);  


					    

					   
					   
	


				}
		}
	}

 	
 	
}
 	
 	
	return 0;
}
