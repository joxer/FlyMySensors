// Diego Luca Candido


#include "httplib.h"
#ifndef DEV_SENSOR_H
#define DEV_SENSOR_H
#include "dev_sensor.h"
#endif

char* _options_site[] = {"user",NULL,"password",NULL,"project",NULL,"apikey",NULL,NULL,NULL};


int send_to_site(char* username, char* password, char* project, char* apikey, char* value_name, float value){
	
	TCP_SOCKET* nn = create_http_socket(HOST);

	struct HTTP_HEADER_REQUEST pp;
	pp.method = "POST";
	pp.resource = "/index.php/default/remote_update";
	pp.version = "HTTP/1.1";
	pp.host = "dev.picus.com";
	pp.parameters_size = 10;
	pp.content_type="application/x-www-form-urlencoded";
	
	_options_site[1] = username;
	_options_site[3] = password;
	_options_site[5] = project;
	_options_site[7] = apikey;
	_options_site[8] = value_name;
	
	char mess[10];
	sprintf(mess,"%f",value);
	_options_site[9] = mess;
	
	pp.parameters = _options_site;
	char* request_body = get_http_request(&pp);
	//UARTWrite(1,request_body);
	//char* param[] = {"user","joxer","password","joxer","apikey","02ef724a65a81a715b28e653f","brightness","999","humidity","989","temperature","979"};
	if(nn != NULL){
	do_http_request(nn,request_body);
	char* resp = http_get_response(nn);
	//UARTWrite(1,resp);
	vTaskDelay(50);
	closeSocket(nn);
	free(resp);
	free(request_body);
	}
	else{
		closeSocket(nn);

	}
};