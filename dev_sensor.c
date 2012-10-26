// Diego Luca Candido

#define HOST "176.58.109.10"
#include "httplib.h"
#ifndef DEV_SENSOR_H
#define DEV_SENSOR_H
#include "dev_sensor.h"
#endif


int send_to_site(char* request[],int size){
	
	TCP_SOCKET* nn = create_http_socket(HOST);

	struct HTTP_HEADER_REQUEST pp;
	pp.method = "POST";
	pp.resource = "/index.php/default/remote_update";
	pp.version = "HTTP/1.1";
	pp.host = "dev.picus.com";
	pp.parameters_size = size;
		
	pp.content_type="application/x-www-form-urlencoded";
	
	pp.parameters = request;
	char* request_body = get_http_request(&pp);
	UARTWrite(1,request_body);
	//char* param[] = {"user","joxer","password","joxer","apikey","02ef724a65a81a715b28e653f","brightness","999","humidity","989","temperature","979"};
	if(nn != NULL){
	do_http_request(nn,request_body);
	char* resp = http_get_response(nn);
	UARTWrite(1,resp);
	vTaskDelay(50);
	closeSocket(nn);
	free(resp);
	free(request_body);
	}
};