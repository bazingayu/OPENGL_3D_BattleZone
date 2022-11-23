#ifndef _MQOOBJECT_H_
#define	_MQOOBJECT_H_

#include "war_src/GLMetaseq.h"
#include <string.h>

class MqoObject
{
private:
	char mqoFileName[100];
	float scale;
	MQO_MODEL mqoModel;
	
public:
	MqoObject();
	MqoObject(const char *filename, float scale);
	~MqoObject();
	
	void setParameters(const char *filename, float scale);
	void initModel();
	void display();
	void deleteModel();
};

#endif

